#include "bardiagramwidget.h"

const int BarDiagramWidget::ySize = 100;
const int BarDiagramWidget::xSize = 180;

class BarDiagramWidget::BarDiagramWidgetPrivate {

public:
    ~BarDiagramWidgetPrivate() {
        delete this->graphicsScene;
        delete this->bars;
    }

private:
    QList<QGraphicsRectItem *> * bars;
    QGraphicsScene * graphicsScene;

public:
    QGraphicsScene * createGraphicsScene() {
        this->graphicsScene = new QGraphicsScene();
        this->bars = new QList<QGraphicsRectItem*>();

        QPen whitePen ( qRgb ( 200,200,200 ) );
        QBrush greyBrush ( qRgb ( 100,100,100 ) );

        this->drawPercentageLines();

        // Bars
        for ( int i = 1; i <= 4; i++ ) {
            int xSpace = BarDiagramWidget::xSize / 13;
            this->bars->append ( this->graphicsScene->addRect ( QRectF ( ( xSpace * i ) + ( xSpace * ( i-1 ) * 2 ), ySize,xSpace*2,0 ) ) );
        }

        // Shadows
        for ( int i = 1; i <= 4; i++ ) {
            int xSpace = BarDiagramWidget::xSize / 13;
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

        this->graphicsScene->addLine ( QLineF ( 0,ySize,BarDiagramWidget::xSize,ySize ), whitePen );
        this->graphicsScene->update();

        return this->graphicsScene;
    }

    void updateGraphicsBar ( int index, int value ) {
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

private:
    void drawPercentageLines() {
        QPen whiteDottedPen ( qRgb ( 140,140,140 ) );
        QVector<qreal> dashes;
        dashes << 1 << 4;
        whiteDottedPen.setDashPattern ( dashes );

        for ( int i = 0; i < 4; i++ ) {
            int y = ( ySize * i ) / 4;
            this->graphicsScene->addLine ( QLineF ( 0,y,BarDiagramWidget::xSize,y ), whiteDottedPen );
        }
    }
};

BarDiagramWidget::BarDiagramWidget ( QWidget* parent, Qt::WindowFlags f )
    : QWidget ( parent, f ), ui ( new Ui::BarDiagramWidget() ) {
    ui->setupUi ( this );
    this->_private = new BarDiagramWidgetPrivate ();
    ui->graphicsView->setScene ( this->_private->createGraphicsScene() );
}

BarDiagramWidget::~BarDiagramWidget() {
    delete this->_private;
    delete this->ui;
}

const Ui::BarDiagramWidget * const BarDiagramWidget::getUi() {
    return this->ui;
}

void BarDiagramWidget::updateGraphicsBar ( int index, int value ) {
    _private->updateGraphicsBar ( index, value );
}

void BarDiagramWidget::updateFromResponse ( UnderstandingResponse response ) {
    for ( int i = 0; i < response.values().size(); i++ ) {
        if ( response.count() > 0 ) {
            this->updateGraphicsBar ( i, ( response.values().at ( i ) * ySize ) / response.count() );
        } else {
            this->updateGraphicsBar ( i, 0 );
        }
    }
}

void BarDiagramWidget::resizeEvent ( QResizeEvent * event ) {
    ui->graphicsView->resetMatrix();

    int yScale = ( this->size().height() / ySize );
    int xScale = ( this->size().width() / xSize );

    ui->graphicsView->resetMatrix();
    ui->graphicsView->scale ( xScale, yScale );
    ui->graphicsView->update();
    QWidget::resizeEvent ( event );
}
