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
