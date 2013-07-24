#ifndef UPDATETIMER_H
#define UPDATETIMER_H

#include <QtCore>
#include <memory>

class UpdateTimer : public QObject {
    Q_OBJECT

public:
    explicit UpdateTimer ();
    virtual ~UpdateTimer();
    void reset();

private:
    std::unique_ptr<QTimer> qtimer;
    int ticks;
    static int tickDuration;

private slots:
    void update() ;

signals:
    void tick ( int ticks );
};

#endif // UPDATETIMER_H
