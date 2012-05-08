#ifndef UPDATETIMER_H
#define UPDATETIMER_H

#include <QtCore>

class UpdateTimer : public QObject {
    Q_OBJECT

public:
    explicit UpdateTimer () ;
    void reset();

private:
    QTimer * qtimer;
    int ticks;

private slots:
    void update() ;

signals:
    void tick(int ticks);
};

#endif // UPDATETIMER_H
