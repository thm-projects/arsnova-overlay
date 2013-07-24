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

    // Switch FEEDBACK_FASTER and FEEDBACK_OK
    QList<int> switchedValues = this->_values;
    switchedValues.swap ( FEEDBACK_FASTER, FEEDBACK_OK );

    for ( int i = 0; i < switchedValues.size(); i++ ) {
        sum += ( switchedValues.at ( i ) * i );
    }

    return ( int ) round ( sum / count );
}
