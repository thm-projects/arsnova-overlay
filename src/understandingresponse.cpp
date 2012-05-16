#include "understandingresponse.h"

UnderstandingResponse::UnderstandingResponse ( int a, int b, int c, int d ) {
    this->_values.append ( a );
    this->_values.append ( b );
    this->_values.append ( c );
    this->_values.append ( d );
}

UnderstandingResponse::~UnderstandingResponse() {
    qDebug() << "UnderstandingResponse destroy";
}

QList< int > UnderstandingResponse::values() {
    return this->_values;
}
