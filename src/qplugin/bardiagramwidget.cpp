#include "bardiagramwidget.h"

const int BarDiagramWidget::ySize = 100;
const int BarDiagramWidget::xSize = 180;

class BarDiagramWidget::BarDiagramWidgetPrivate {

public:
    explicit BarDiagramWidgetPrivate()
        : bars ( std::shared_ptr<QList<QGraphicsRectItem*>> ( new QList<QGraphicsRectItem*>() ) ),
          _graphicsScene ( new QGraphicsScene() ) {
        this->fillGraphicsScene();
    }

    explicit BarDiagramWidgetPrivate ( BarDiagramWidgetPrivate * obj )
        : bars ( obj->bars ),
          _graphicsScene ( obj->_graphicsScene ) {
    }

    ~BarDiagramWidgetPrivate() {
        delete this->_graphicsScene;
    }

    QGraphicsScene * graphicsScene() {
        return this->_graphicsScene;
    }

private:
    std::shared_ptr<QList<QGraphicsRectItem *>> bars;
    QGraphicsScene * _graphicsScene;

    void fillGraphicsScene() {
        QPen whitePen ( qRgb ( 200,200,200 ) );
        QBrush greyBrush ( qRgb ( 100,100,100 ) );

        this->drawPercentageLines();

        // Bars
        for ( int i = 1; i <= 4; i++ ) {
            int xSpace = BarDiagramWidget::xSize / 13;
            this->bars->append ( this->_graphicsScene->addRect ( QRectF ( ( xSpace * i ) + ( xSpace * ( i-1 ) * 2 ), ySize,xSpace*2,0 ) ) );
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

        this->_graphicsScene->addLine ( QLineF ( 0,ySize,BarDiagramWidget::xSize,ySize ), whitePen );
        this->_graphicsScene->update();
    }

public:
    void updateGraphicsBar ( int index, int value ) {
        QGraphicsRectItem * item = this->bars->at ( index );

        int x = item->rect().x();
        int y = ySize - value;
        int width = item->rect().width();
        int height = value;
        item->setRect ( QRectF ( x,y,width,height ) );
        item->update();

        this->_graphicsScene->update();
    }

private:
    void drawPercentageLines() {
        QPen whiteDottedPen ( qRgb ( 140,140,140 ) );
        QVector<qreal> dashes;
        dashes << 1 << 4;
        whiteDottedPen.setDashPattern ( dashes );

        for ( int i = 0; i < 4; i++ ) {
            int y = ( ySize * i ) / 4;
            this->_graphicsScene->addLine ( QLineF ( 0,y,BarDiagramWidget::xSize,y ), whiteDottedPen );
        }
    }
};

BarDiagramWidget::BarDiagramWidget ( QWidget* parent, Qt::WindowFlags f )
    : QWidget ( parent, f ), ui ( new Ui::BarDiagramWidget() ) {
    ui->setupUi ( this );
    this->_private = std::unique_ptr< BarDiagramWidgetPrivate > ( new BarDiagramWidgetPrivate () );
    ui->graphicsView->setScene ( this->_private->graphicsScene() );
}

BarDiagramWidget::~BarDiagramWidget() {
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
