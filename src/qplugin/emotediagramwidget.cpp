#include "emotediagramwidget.h"

EmoteDiagramWidget::EmoteDiagramWidget ( QWidget * parent, Qt::WindowFlags f )
    : QWidget ( parent, f ), ui ( new Ui::EmoteDiagramWidget() ) {
    ui->setupUi ( this );

    this->updateFromResponse ( FeedbackResponse ( 0,0,0,0 ) );
}

EmoteDiagramWidget::~EmoteDiagramWidget() {
    delete this->ui;
}

const Ui::EmoteDiagramWidget*const EmoteDiagramWidget::getUi() {
    return this->ui;
}

void EmoteDiagramWidget::updateFromResponse ( FeedbackResponse response ) {

    switch ( response.averageRounded() ) {
    case FeedbackResponse::FEEDBACK_OK:
        this->ui->logoWidget->load ( QString ( ":images/images/emotes/face-smile.svg" ) );
        break;
    case FeedbackResponse::FEEDBACK_FASTER:
        this->ui->logoWidget->load ( QString ( ":images/images/emotes/face-wink.svg" ) );
        break;
    case FeedbackResponse::FEEDBACK_SLOWER:
        this->ui->logoWidget->load ( QString ( ":images/images/emotes/face-surprise.svg" ) );
        break;
    case FeedbackResponse::FEEDBACK_AWAY:
        this->ui->logoWidget->load ( QString ( ":images/images/emotes/face-sad.svg" ) );
        break;
    }
}

void EmoteDiagramWidget::resizeEvent ( QResizeEvent* event ) {
    int minEdgeSize = this->size().height() < this->size().width()
                      ? this->size().height()
                      : this->size().width();
    QSize size ( 8, 8 );
    size.scale ( minEdgeSize, minEdgeSize, Qt::KeepAspectRatio );
    ui->logoWidget->resize ( size );

    this->setContentsMargins (
        ( this->width() - minEdgeSize ) / 2,
        0,
        ( this->width() - minEdgeSize ) / 2,
        0
    );
    QWidget::resizeEvent ( event );
}
