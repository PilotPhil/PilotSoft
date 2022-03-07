#ifndef SERIALREADTHREAD_H
#define SERIALREADTHREAD_H

#include <QObject>
#include <QSerialPort>
#include <QDebug>

class SerialReadThread : public QObject
{
    Q_OBJECT
public:
    explicit SerialReadThread(QObject *parent = 0);

signals:
    void serialData(qreal data);

public slots:
    void serialRead(QSerialPort *myport);
};

#endif // SERIALREADTHREAD_H
