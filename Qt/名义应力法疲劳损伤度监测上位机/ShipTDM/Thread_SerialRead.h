#ifndef SERREAD_H
#define SERREAD_H

#include <QObject>
#include <QSerialPort>
#include <QDebug>
#include <QThread>

class SerRead : public QObject
{
    Q_OBJECT
public:
    explicit SerRead(QObject *parent = 0);

signals:
    void ReceivedData(qreal data);

public slots:
    void serialRead(QSerialPort *myport);
};

#endif // SERREAD_H
