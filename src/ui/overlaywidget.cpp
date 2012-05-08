#include "overlaywidget.h"

const int OverlayWidget::ySize = 160;
const int OverlayWidget::httpUpdateInterval = 10;

OverlayWidget::OverlayWidget ( QWidget* parent, Qt::WindowFlags f )
    : QWidget ( parent, f ) , ui ( new Ui::OverlayWidget() ) {
    ui->setupUi ( this );

    this->updateTimer = new UpdateTimer();
    this->httpClient = new QHttp ( "ars.thm.de", QHttp::ConnectionModeHttps, 443 );

    connect ( this->updateTimer, SIGNAL ( tick ( int ) ), this, SLOT ( updateHttpResponse ( int ) ) );
    connect ( this->httpClient, SIGNAL ( requestFinished ( int,bool ) ), this, SLOT ( updateGraphicsScene() ) );
    connect ( ui->sessionIdEdit, SIGNAL ( editingFinished() ), this, SLOT ( sessionLogin() ) );
    connect ( ui->loginButton, SIGNAL ( pressed() ), this, SLOT ( sessionLogin() ) );
    
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);

    ui->progressBar->setMaximum ( OverlayWidget::httpUpdateInterval );

    this->graphicsScene = new QGraphicsScene();

    ui->loginButton->setFocus();
    ui->graphicsView->hide();
    ui->onlineUsersLabel->hide();
    ui->progressBar->hide();
    ui->sessionNameLabel->hide();

    this->createGraphicsScene();
    this->setMouseTracking ( true );
        
    ui->graphicsView->setMouseTracking ( true );

    ui->graphicsView->setScene ( this->graphicsScene );

    ui->menuWidget->hide();
}

void OverlayWidget::createGraphicsScene() {
    this->bars = new QList<QGraphicsRectItem*>();

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

    QLinearGradient linearGradient;
    linearGradient.setStart ( 0,0 );
    linearGradient.setFinalStop ( 0, ySize );

    linearGradient.setColorAt ( 0, qRgb ( 122, 184, 68 ) );
    linearGradient.setColorAt ( 1, qRgb ( 82, 144, 28 ) );
    this->bars->at ( 0 )->setBrush ( QBrush ( linearGradient ) );

    linearGradient.setColorAt ( 0, qRgb ( 254, 201, 41 ) );
    linearGradient.setColorAt ( 1, qRgb ( 214, 161, 0 ) );
    this->bars->at ( 1 )->setBrush ( QBrush ( linearGradient ) );

    linearGradient.setColorAt ( 0, qRgb ( 237, 96, 28 ) );
    linearGradient.setColorAt ( 1, qRgb ( 197, 56, 0 ) );
    this->bars->at ( 2 )->setBrush ( QBrush ( linearGradient ) );

    linearGradient.setColorAt ( 0, qRgb ( 235, 235, 235 ) );
    linearGradient.setColorAt ( 1, qRgb ( 195,195,195 ) );
    this->bars->at ( 3 )->setBrush ( QBrush ( linearGradient ) );


    QGraphicsBlurEffect * effectA = new QGraphicsBlurEffect();
    effectA->setBlurRadius ( 3 );
    QGraphicsBlurEffect * effectB = new QGraphicsBlurEffect();
    effectB->setBlurRadius ( 3 );
    QGraphicsBlurEffect * effectC = new QGraphicsBlurEffect();
    effectC->setBlurRadius ( 3 );
    QGraphicsBlurEffect * effectD = new QGraphicsBlurEffect();
    effectD->setBlurRadius ( 3 );

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
    QScriptEngine scriptEngine;
    QScriptValue scriptValue = scriptEngine.evaluate ( QString ( "(" ) + response.data() + ")" );
    if ( this->httpClient->currentRequest().path().contains ( "by_keyword" ) ) {

        this->sessionId = scriptValue.property ( "rows" ).property ( 0 ).property ( "id" ).toString();

        if ( ! this->sessionId.isNull() ) {
            ui->sessionIdEdit->hide();
            ui->loginButton->hide();
            ui->onlineUsersLabel->show();
            ui->progressBar->show();
            ui->graphicsView->show();
            ui->sessionNameLabel->show();
            this->updateHttpResponse ( OverlayWidget::httpUpdateInterval );
            ui->sessionNameLabel->setText (
                scriptValue.property ( "rows" ).property ( 0 ).property ( "value" ).property ( "shortName" ).toString()
                + "\n("
                + scriptValue.property ( "rows" ).property ( 0 ).property ( "key" ).toString()
                + ")"
            );
        }

    } else if ( this->httpClient->currentRequest().path().contains ( "by_session" ) ) {
        int values[4] = {0,0,0,0};

        for ( int i = 0; i <= 3; i++ ) {
            QString key = scriptValue.property ( "rows" ).property ( i ).property ( "key" ).property ( 1 ).toString();
            if ( key == "Bitte schneller" ) values[0] = scriptValue.property ( "rows" ).property ( i ).property ( "value" ).toInteger();
            if ( key == "Kann folgen" ) values[1] = scriptValue.property ( "rows" ).property ( i ).property ( "value" ).toInteger();
            if ( key == "Zu schnell" ) values[2] = scriptValue.property ( "rows" ).property ( i ).property ( "value" ).toInteger();
            if ( key == "Nicht mehr dabei" ) values[3] = scriptValue.property ( "rows" ).property ( i ).property ( "value" ).toInteger();
        }

        this->latestUnderstandingResponses = values[0] + values[1] + values[2] + values[3];

        for ( int i = 0; i <= 3; i++ ) {
            if ( this->latestUnderstandingResponses > 0 ) this->updateGraphicsBar ( i, ( values[i] * ySize ) / this->latestUnderstandingResponses );
        }
    } else if ( this->httpClient->currentRequest().path().contains ( "logged_in" ) ) {
        this->loggedInUsers = scriptValue.property ( "rows" ).property ( 0 ).property ( "value" ).toInteger();
        ui->onlineUsersLabel->setText (
            QString ( "(" ) + QString::number ( this->latestUnderstandingResponses, 10 ) + "/"
            + QString::number ( this->loggedInUsers, 10 ) + ")"
        );
    }
}

void OverlayWidget::updateHttpResponse ( int ticks ) {
    ui->progressBar->setValue ( ticks );
    if ( ticks == OverlayWidget::httpUpdateInterval ) {
        this->httpClient->get ( "/couchdb/arsnova/_design/understanding/_view/by_session?group=true&startkey=[\"" + this->sessionId + "\"]&endkey=[\"" + this->sessionId + "\",{}]" );
        this->httpClient->get ( "/couchdb/arsnova/_design/logged_in/_view/count?group=true&startkey=[\"" + this->sessionId + "\"]&endkey=[\"" + this->sessionId + "\",{}]" );
        this->updateTimer->reset();
    }
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

void OverlayWidget::mouseMoveEvent ( QMouseEvent* event ) {
    if (
        ( event->pos().y() >= this->size().height() - 20 )
        && ui->progressBar->isVisible()
    ) {
        ui->menuWidget->show();
    } else {
        ui->menuWidget->hide();
    }
    QWidget::mouseMoveEvent ( event );
}

void OverlayWidget::resizeEvent ( QResizeEvent* event ) {
    int yScale = event->size().height() / 210;
    int xScale = event->size().width() / 320;

    qDebug() << event->size() << xScale << yScale;

    ui->graphicsView->resetMatrix();
    ui->graphicsView->scale ( xScale, yScale );
    ui->graphicsView->update();

    QWidget::resizeEvent ( event );
}


void OverlayWidget::sessionLogin() {
    this->httpClient->get ( "/couchdb/arsnova/_design/session/_view/by_keyword?key=\"" + ui->sessionIdEdit->text() + "\"" );
}
