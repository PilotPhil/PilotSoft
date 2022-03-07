#include "myt_serialreadonly.h"

myT_SerialReadOnly::myT_SerialReadOnly(QObject *parent) : QObject(parent)
{

}
void myT_SerialReadOnly::serialRead(QSerialPort *myport)
{
    //接收到串口读取信号后读取串口
    QString msg=myport->readLine();//读取数据
    qreal data=msg.toDouble();
    //qDebug()<<"I have received";
    //qDebug()<<"串口读取子线程号："<<QThread::currentThread();
    emit ReceivedData(data);
}
