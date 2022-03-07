#ifndef SERIALREAD_THREAD_H
#define SERIALREAD_THREAD_H

#include <QObject>
#include <QSerialPort>
#include <QDebug>
#include <QThread>


class SerialRead_Thread : public QObject
{
    Q_OBJECT
public:
    explicit SerialRead_Thread(QObject *parent = 0);

    void serialRead(QSerialPort *myport);//串口读取数据

signals:
    void ReceivedData(qreal data);

private:
    QString msg;//接收到的消息
    qreal serialData;//消息转化为数值类型

};

#endif // SERIALREAD_THREAD_H
