#ifndef SERIALSETTING_THREAD_H
#define SERIALSETTING_THREAD_H

#include <QObject>
#include <QSerialPort>
#include <QDebug>
#include <QThread>

class SerialSetting_thread : public QObject
{
    Q_OBJECT
public:
    explicit SerialSetting_thread(QObject *parent = nullptr);

    void serialRead(QSerialPort *myport);//串口读取数据
signals:
    void SerialReadSend(QString msg);

private:
    QString msg;

};

#endif // SERIALSETTING_THREAD_H
