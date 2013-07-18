#include "feedbackresponse.h"

FeedbackResponse::FeedbackResponse ( int a, int b, int c, int d ) {
    this->_values.append ( a );
    this->_values.append ( b );
    this->_values.append ( c );
    this->_values.append ( d );

    this->_count = a+b+c+d;
}

FeedbackResponse::~FeedbackResponse() {

}

QList< int > FeedbackResponse::values() {
    return this->_values;
}

int FeedbackResponse::count() {
    return this->_count;
}

int FeedbackResponse::averageRounded() {
    if ( this->count() == 0 ) return 0;

    double count = this->count();
    double sum = 0;
    for ( int i = 0; i < values().size(); i++ ) {
        sum += ( values().at ( i ) * i );
    }

    return ( int ) round ( sum / count );
}
