#include "serialread_thread.h"
#include <QMetaType>

Q_DECLARE_METATYPE(QSerialPort*)

SerialRead_Thread::SerialRead_Thread(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<QSerialPort*>("QSerialPort*");//注册类型
}

//串口读取数据，接收一个数据发送出去
void SerialRead_Thread::serialRead(QSerialPort *myport)
{
    //接收到串口读取信号后读取串口
    msg=myport->readLine();//读取数据
    serialData=msg.toDouble();//

    emit ReceivedData(serialData);
}
