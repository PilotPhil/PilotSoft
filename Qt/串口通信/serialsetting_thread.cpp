#include "serialsetting_thread.h"
#include <QMetaType>

SerialSetting_thread::SerialSetting_thread(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<QSerialPort*>("QSerialPort*");//注册类型
}

void SerialSetting_thread::serialRead(QSerialPort *myport)
{
    //接收到串口读取信号后读取串口
    msg=myport->readLine();//读取数据
    emit SerialReadSend(msg);
}
