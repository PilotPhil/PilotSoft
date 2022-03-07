#ifndef MYT_SERIALREADONLY_H
#define MYT_SERIALREADONLY_H

#include <QObject>
#include <QSerialPort>
#include <QDebug>
#include <QThread>

class myT_SerialReadOnly : public QObject
{
    Q_OBJECT
public:
    explicit myT_SerialReadOnly(QObject *parent = 0);

signals:
    void ReceivedData(qreal data);

public slots:
    void serialRead(QSerialPort *myport);
};

#endif // MYT_SERIALREADONLY_H
