#ifndef UPDATETIMER_H
#define UPDATETIMER_H

#include <QtCore>

class UpdateTimer : public QObject {
    Q_OBJECT

public:
    explicit UpdateTimer ();
    virtual ~UpdateTimer();
    void reset();

private:
    QTimer * qtimer;
    int ticks;
    static int tickDuration;

private slots:
    void update() ;

signals:
    void tick ( int ticks );
};

#endif // UPDATETIMER_H
