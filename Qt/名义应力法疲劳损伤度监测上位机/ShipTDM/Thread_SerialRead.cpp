#include "Thread_SerialRead.h"

SerRead::SerRead(QObject *parent) : QObject(parent)
{

}
void SerRead::serialRead(QSerialPort *myport)
{
    //接收到串口读取信号后读取串口
    QString msg=myport->readLine();//读取数据
    qreal data=msg.toDouble();
    qDebug()<<"I have received";
    emit ReceivedData(data);
}
