#include "overlaywidget.h"

const int OverlayWidget::ySize = 80;
const int OverlayWidget::xSize = 180;
const int OverlayWidget::httpUpdateInterval = 10;

OverlayWidget::OverlayWidget ( QWidget* parent, Qt::WindowFlags f )
    : QWidget ( parent, f ) , ui ( new Ui::OverlayWidget() ) {
    ui->setupUi ( this );

    this->updateTimer = new UpdateTimer();
    this->httpClient = new QHttp ( "ars.thm.de", QHttp::ConnectionModeHttps, 443 );
    this->httpConnection = new HttpConnection ( this->httpClient );

    this->svgLogo = new SvgLogo();
    ui->logoWidget = this->svgLogo->widget();

    connect ( this->updateTimer, SIGNAL ( tick ( int ) ), this, SLOT ( updateHttpResponse ( int ) ) );
    connect ( this->httpConnection, SIGNAL ( requestFinished ( SessionResponse ) ), this, SLOT ( onSessionResponse ( SessionResponse ) ) );
    connect ( this->httpConnection, SIGNAL ( requestFinished ( UnderstandingResponse ) ), this, SLOT ( onUnderstandingResponse ( UnderstandingResponse ) ) );
    connect ( this->httpConnection, SIGNAL ( requestFinished ( LoggedInResponse ) ), this, SLOT ( onLoggedInResponse ( LoggedInResponse ) ) );
    connect ( ui->sessionIdEdit, SIGNAL ( editingFinished() ), this, SLOT ( sessionLogin() ) );
    connect ( ui->loginButton, SIGNAL ( pressed() ), this, SLOT ( sessionLogin() ) );
    connect ( ui->actionChangeSession, SIGNAL ( triggered ( bool ) ), this, SLOT ( showSessionIdForm() ) );
    connect ( ui->actionMakeTransparent, SIGNAL ( triggered ( bool ) ), this, SLOT ( makeTransparent ( bool ) ) );
    connect ( ui->actionFullscreen, SIGNAL ( triggered ( bool ) ), this, SLOT ( makeFullscreen ( bool ) ) );
    connect ( ui->actionExit, SIGNAL ( triggered ( bool ) ), this, SLOT ( close() ) );

    this->setWindowFlags ( Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint );

    ui->progressBar->setMaximum ( OverlayWidget::httpUpdateInterval );

    this->graphicsScene = new QGraphicsScene();

    ui->loginButton->setFocus();
    ui->graphicsView->hide();
    ui->onlineUsersLabel->hide();
    ui->progressBar->hide();
    ui->sessionNameLabel->hide();
    ui->menuWidget->hide();
    ui->logoWidget->hide();

    this->createGraphicsScene();
    this->setMouseTracking ( true );

    ui->graphicsView->setMouseTracking ( true );

    ui->graphicsView->setScene ( this->graphicsScene );
    this->moveToBottomRightEdge();
}

void OverlayWidget::moveToBottomRightEdge() {
    this->resize ( QSize ( xSize+20, ( ySize*2 ) + 32 ) );
    int xPos = QApplication::desktop()->screenGeometry().width() - this->size().width() - 8;
    int yPos = QApplication::desktop()->screenGeometry().height() - this->size().height() - 8;
    this->move ( xPos, yPos );
}

void OverlayWidget::createGraphicsScene() {
    this->bars = new QList<QGraphicsRectItem*>();

    QPen whitePen ( qRgb ( 200,200,200 ) );
    QBrush greyBrush ( qRgb ( 100,100,100 ) );

    this->drawPercentageLines();

    // Bars
    for ( int i = 1; i <= 4; i++ ) {
        int xSpace = OverlayWidget::xSize / 13;
        this->bars->append ( this->graphicsScene->addRect ( QRectF ( ( xSpace * i ) + ( xSpace * ( i-1 ) * 2 ), ySize,xSpace*2,0 ) ) );
    }

    // Shadows
    for ( int i = 1; i <= 4; i++ ) {
        int xSpace = OverlayWidget::xSize / 13;
        this->bars->append ( this->graphicsScene->addRect ( QRectF ( ( xSpace * i ) + ( xSpace * ( i-1 ) * 2 ), ySize,xSpace*2,0 ) ) );
    }

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

    QGraphicsLineItem * xAxis = this->graphicsScene->addLine ( QLineF ( 0,ySize,OverlayWidget::xSize,ySize ), whitePen );

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
        this->graphicsScene->addLine ( QLineF ( 0,y,OverlayWidget::xSize,y ), whiteDottedPen );
    }
}

void OverlayWidget::onSessionResponse ( SessionResponse response ) {
    this->sessionId = response.sessionId();

    if ( ! this->sessionId.isNull() ) {
        ui->sessionIdEdit->hide();
        ui->loginButton->hide();
        ui->onlineUsersLabel->show();
        ui->progressBar->show();
        ui->graphicsView->show();
        ui->sessionNameLabel->show();
        ui->menuWidget->show();
        this->setWindowFlags ( Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint );
        this->show();
        this->updateHttpResponse ( OverlayWidget::httpUpdateInterval );
        ui->sessionNameLabel->setText (
            response.shortName()
            + "\n("
            + response.sessionId()
            + ")"
        );
    }
}

void OverlayWidget::onUnderstandingResponse ( UnderstandingResponse response ) {
    int values[4];
    for ( int i = 0; i <= 3; i++ ) {
        values[i] = response.values().at ( i );
    }

    this->latestUnderstandingResponses = values[0] + values[1] + values[2] + values[3];

    for ( int i = 0; i <= 3; i++ ) {
        if ( this->latestUnderstandingResponses > 0 ) {
            this->updateGraphicsBar ( i, ( values[i] * ySize ) / this->latestUnderstandingResponses );
        } else {
            this->updateGraphicsBar ( i, 0 );
        }
    }
}

void OverlayWidget::onLoggedInResponse ( LoggedInResponse response ) {
    this->loggedInUsers = response.value();
    ui->onlineUsersLabel->setText (
        QString ( "(" ) + QString::number ( this->latestUnderstandingResponses, 10 ) + "/"
        + QString::number ( this->loggedInUsers, 10 ) + ")"
    );
}

void OverlayWidget::updateHttpResponse ( int ticks ) {
    ui->progressBar->setValue ( ticks );
    if ( ticks == OverlayWidget::httpUpdateInterval ) {
        this->httpConnection->requestUnderstanding();
        this->httpConnection->requestLoggedIn();
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

void OverlayWidget::sessionLogin() {
    this->httpConnection->requestSession ( ui->sessionIdEdit->text() );
    this->makeTransparent ( true );
    this->moveToBottomRightEdge();
}

void OverlayWidget::makeTransparent ( bool enabled ) {
    ui->actionMakeTransparent->setChecked ( enabled );
    if ( enabled ) {
        this->setWindowOpacity ( .5 );
        return;
    }
    this->setWindowOpacity ( 1 );
}

void OverlayWidget::makeFullscreen ( bool enabled ) {
    if ( enabled ) {

        this->move ( 0,0 );
        this->setMaximumSize ( QApplication::desktop()->screenGeometry().width(),QApplication::desktop()->screenGeometry().height() );
        this->resize ( QApplication::desktop()->screenGeometry().width(),QApplication::desktop()->screenGeometry().height() );
        this->setWindowState ( this->windowState() ^ Qt::WindowFullScreen );
        this->show();

        int yScale = ( this->size().height() / ySize ) - 2;
        int xScale = ( this->size().width() / xSize ) - 2;

        ui->graphicsView->resetMatrix();
        ui->graphicsView->scale ( xScale, yScale );
        ui->graphicsView->update();
        return;
    }

    this->setWindowState ( this->windowState() & ~Qt::WindowFullScreen );
    this->show();

    this->moveToBottomRightEdge();
    ui->graphicsView->resetMatrix();
}

void OverlayWidget::showSessionIdForm() {
    this->makeTransparent ( false );

    ui->loginButton->setFocus();

    ui->sessionIdEdit->show();
    ui->loginButton->show();
    ui->onlineUsersLabel->hide();
    ui->progressBar->hide();
    ui->graphicsView->hide();
    ui->sessionNameLabel->hide();
    ui->menuWidget->hide();

    this->setWindowFlags ( Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint );
    this->show();

    this->moveToBottomRightEdge();
}

