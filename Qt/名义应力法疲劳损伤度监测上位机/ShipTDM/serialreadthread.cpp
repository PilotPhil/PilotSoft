#include "serialreadthread.h"

SerialReadThread::SerialReadThread(QObject *parent) : QObject(parent)
{




}

void SerialReadThread::serialRead(QSerialPort *myport)
{
    //接收到串口读取信号后读取串口
    QString msg=myport->readLine();//读取数据
    qreal data=msg.toDouble();
    qDebug()<<"I have received";
    emit serialData(data);
}


