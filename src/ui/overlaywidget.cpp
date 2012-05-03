#include "overlaywidget.h"

const int OverlayWidget::ySize = 160;

OverlayWidget::OverlayWidget ( QWidget* parent, Qt::WindowFlags f )
    : QWidget ( parent, f ) , ui ( new Ui::OverlayWidget() ) {
    ui->setupUi ( this );

    this->updateTimer = new UpdateTimer();
    this->httpClient = new QHttp ( "ars.thm.de", QHttp::ConnectionModeHttps, 443 );

    connect ( this->updateTimer, SIGNAL ( tick() ), this, SLOT ( updateHttpResponse() ) );
    connect ( this->httpClient, SIGNAL ( requestFinished ( int,bool ) ), this, SLOT ( updateGraphicsScene() ) );
    //this->setWindowFlags(Qt::FramelessWindowHint);

    this->httpClient->get ( "/couchdb/arsnova/_design/session/_view/by_keyword?key=\"81545518\"" );

    this->createGraphicsScene();
}

void OverlayWidget::createGraphicsScene() {
    this->bars = new QList<QGraphicsRectItem*>();
    this->graphicsScene = new QGraphicsScene();

    QPen whitePen ( qRgb ( 200,200,200 ) );
    QBrush greyBrush ( qRgb ( 100,100,100 ) );

    //ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    this->drawPercentageLines();

    this->bars->append ( this->graphicsScene->addRect ( QRectF ( 20,ySize,40,0 ) ) );
    this->bars->append ( this->graphicsScene->addRect ( QRectF ( 80,ySize,40,0 ) ) );
    this->bars->append ( this->graphicsScene->addRect ( QRectF ( 140,ySize,40,0 ) ) );
    this->bars->append ( this->graphicsScene->addRect ( QRectF ( 200,ySize,40,0 ) ) );

    this->bars->append ( this->graphicsScene->addRect ( QRectF ( 20,ySize,40,0 ) ) );
    this->bars->append ( this->graphicsScene->addRect ( QRectF ( 80,ySize,40,0 ) ) );
    this->bars->append ( this->graphicsScene->addRect ( QRectF ( 140,ySize,40,0 ) ) );
    this->bars->append ( this->graphicsScene->addRect ( QRectF ( 200,ySize,40,0 ) ) );

    this->bars->at ( 0 )->setBrush ( QBrush ( qRgb ( 140,240,100 ) ) );
    this->bars->at ( 1 )->setBrush ( QBrush ( qRgb ( 240,240,100 ) ) );
    this->bars->at ( 2 )->setBrush ( QBrush ( qRgb ( 240,100,100 ) ) );
    this->bars->at ( 3 )->setBrush ( QBrush ( qRgb ( 200,200,200 ) ) );

    QGraphicsBlurEffect * effectA = new QGraphicsBlurEffect();
    effectA->setBlurRadius ( 6 );
    QGraphicsBlurEffect * effectB = new QGraphicsBlurEffect();
    effectB->setBlurRadius ( 6 );
    QGraphicsBlurEffect * effectC = new QGraphicsBlurEffect();
    effectC->setBlurRadius ( 6 );
    QGraphicsBlurEffect * effectD = new QGraphicsBlurEffect();
    effectD->setBlurRadius ( 6 );

    this->bars->at ( 4 )->setZValue ( -2 );
    this->bars->at ( 4 )->setBrush ( QBrush ( Qt::black ) );
    this->bars->at ( 4 )->setGraphicsEffect ( effectA );

    this->bars->at ( 5 )->setZValue ( -2 );
    this->bars->at ( 5 )->setBrush ( QBrush ( Qt::black ) );
    this->bars->at ( 5 )->setGraphicsEffect ( effectB );

    this->bars->at ( 6 )->setZValue ( -2 );
    this->bars->at ( 6 )->setBrush ( QBrush ( Qt::black ) );
    this->bars->at ( 6 )->setGraphicsEffect ( effectC );

    this->bars->at ( 7 )->setZValue ( -2 );
    this->bars->at ( 7 )->setBrush ( QBrush ( Qt::black ) );
    this->bars->at ( 7 )->setGraphicsEffect ( effectD );

    QGraphicsLineItem * xAxis = this->graphicsScene->addLine ( QLineF ( 0,ySize,260,ySize ), whitePen );
    QGraphicsLineItem * yAxis = this->graphicsScene->addLine ( QLineF ( 0,0,0,ySize ), whitePen );

    this->graphicsScene->update();

    ui->graphicsView->setScene ( this->graphicsScene );
}

void OverlayWidget::drawPercentageLines() {
    QPen whiteDottedPen ( qRgb ( 140,140,140 ) );
    QVector<qreal> dashes;
    dashes << 1 << 4;
    whiteDottedPen.setDashPattern ( dashes );

    for ( int i = 0; i < 4; i++ ) {
        int y = ( ySize * i ) / 4;
        this->graphicsScene->addLine ( QLineF ( 0,y,260,y ), whiteDottedPen );
    }
}


void OverlayWidget::updateGraphicsScene() {

    QByteArray response = this->httpClient->readAll();
    if ( this->httpClient->currentRequest().path().contains ( "by_keyword" ) ) {
        QScriptEngine scriptEngine;
        QScriptValue scriptValue = scriptEngine.evaluate ( QString ( "(" ) + response.data() + ")" );
        this->sessionId = scriptValue.property ( "rows" ).property ( 0 ).property ( "id" ).toString();

        this->updateHttpResponse();
    } else if ( this->httpClient->currentRequest().path().contains ( "by_session" ) ) {
        QScriptEngine scriptEngine;
        QScriptValue scriptValue = scriptEngine.evaluate ( QString ( "(" ) + response.data() + ")" );

        int values[4] = {0,0,0,0};

        for ( int i = 0; i <= 3; i++ ) {
            QString key = scriptValue.property ( "rows" ).property ( i ).property ( "key" ).property ( 1 ).toString();
            if ( key == "Bitte schneller" ) values[0] = scriptValue.property ( "rows" ).property ( i ).property ( "value" ).toInteger();
            if ( key == "Kann folgen" ) values[1] = scriptValue.property ( "rows" ).property ( i ).property ( "value" ).toInteger();
            if ( key == "Zu schnell" ) values[2] = scriptValue.property ( "rows" ).property ( i ).property ( "value" ).toInteger();
            if ( key == "Nicht mehr dabei" ) values[3] = scriptValue.property ( "rows" ).property ( i ).property ( "value" ).toInteger();
        }

        int sum = values[0] + values[1] + values[2] + values[3];

        for ( int i = 0; i <= 3; i++ ) {
            if ( sum > 0 ) this->updateGraphicsBar ( i, ( values[i] * ySize ) / sum );
        }
    }
}

void OverlayWidget::updateHttpResponse() {
    this->httpClient->get ( "/couchdb/arsnova/_design/understanding/_view/by_session?group=true&startkey=[\"" + this->sessionId + "\"]&endkey=[\"" + this->sessionId + "\",{}]" );
}

void OverlayWidget::updateGraphicsBar ( int index, int value ) {
    QGraphicsRectItem * item = this->bars->at ( index );

    int x = item->rect().x();
    int y = ySize - value;
    int width = item->rect().width();
    int height = value;
    item->setRect ( QRectF ( x,y,width,height ) );
    item->update();

    item = this->bars->at ( index + 4 );
    item->setRect ( QRectF ( x,y,width,height ) );
    item->update();

    this->graphicsScene->update();
}

