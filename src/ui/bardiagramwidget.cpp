#include "bardiagramwidget.h"

BarDiagramWidget::BarDiagramWidget ( QWidget * parent, Qt::WindowFlags f ) {
    this->setSource ( QUrl ( "qrc:/qml/ui/bardiagram.qml" ) );
    item = qobject_cast<QDeclarativeItem *> ( this->rootObject() );
}

BarDiagramWidget::~BarDiagramWidget() {
    delete this->item;
}

QGraphicsScene * const BarDiagramWidget::getUi() {
    return this->scene();
}

void BarDiagramWidget::updateGraphicsBar ( int index, int value ) {
    QDeclarativeItem * okBar = item->findChild<QDeclarativeItem *> ( "okBar" );
    QDeclarativeItem * toSlowBar = item->findChild<QDeclarativeItem *> ( "toSlowBar" );
    QDeclarativeItem * toFastBar = item->findChild<QDeclarativeItem *> ( "toFastBar" );
    QDeclarativeItem * awayBar = item->findChild<QDeclarativeItem *> ( "awayBar" );

    switch ( index ) {
    case 0:
        okBar->setProperty ( "height", value );
        break;
    case 1:
        toSlowBar->setProperty ( "height", value );
        break;
    case 2:
        toFastBar->setProperty ( "height", value );
        break;
    case 3:
        awayBar->setProperty ( "height", value );
        break;
    }
}

void BarDiagramWidget::updateFromResponse ( FeedbackResponse response ) {
    int max = 0;
    for ( int i = 0; i < response.values().size(); i++ ) {
        max = response.values().at ( i ) > max ? response.values().at ( i ) : max;
    }
    for ( int i = 0; i < response.values().size(); i++ ) {
        if ( response.count() > 0 && max > 0) {
            this->updateGraphicsBar ( i, ( response.values().at ( i ) * 100 ) / max );
        } else {
            this->updateGraphicsBar ( i, 0 );
        }
    }
}

void BarDiagramWidget::mousePressEvent ( QMouseEvent* event ) {
    QGraphicsView::mousePressEvent ( event );
    emit this->clicked();
}
