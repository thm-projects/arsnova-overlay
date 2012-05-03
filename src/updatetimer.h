#ifndef UPDATETIMER_H
#define UPDATETIMER_H

#include <QtCore>

class UpdateTimer : public QObject {
    Q_OBJECT

public:
    explicit UpdateTimer () ;

private:
    QTimer * qtimer;
    static const int updateInterval; 

private slots:
    void update() ;

signals:
    void tick();
};

#endif // UPDATETIMER_H
