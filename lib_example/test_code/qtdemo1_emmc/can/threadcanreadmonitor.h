#ifndef THREADCANREADMONITOR_H
#define THREADCANREADMONITOR_H

#include <QThread>
class QByteArray;

class ThreadCANReadMonitor : public QThread
{
    Q_OBJECT
public:
    explicit ThreadCANReadMonitor(QObject *parent = 0);
    char ifname[10];

signals:
    void signalRecvMsg(QByteArray, uint id);
public slots:
    
protected:
    void run();
};

#endif // THREADCANREADMONITOR_H
