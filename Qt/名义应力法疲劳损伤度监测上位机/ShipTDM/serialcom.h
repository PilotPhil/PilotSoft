#ifndef SerialCom_H
#define SerialCom_H

#include <QWidget>
#include<QSerialPort>
#include<QSerialPortInfo>
#include<QString>
#include<QDebug>
#include"dynamiccurve.h"
#include<QVector>

namespace Ui {
class SerialCom;
}

class SerialCom : public QWidget
{
    Q_OBJECT

public:
    explicit SerialCom(QWidget *parent = 0);
    ~SerialCom();

    void searchPorts();//获取所有可用串口
    void openPort();//打开串口
    void closePort();//关闭串口
    void setSerialCom();//设置串口通讯参数
    void readData();//读取数据

private slots:
    void on_bradBox_currentIndexChanged(int index);
    void on_dataBitsBox_currentIndexChanged(int index);
    void on_parityBox_currentIndexChanged(int index);
    void on_stopBitsBox_currentIndexChanged(int index);
    void on_openSerialButton_clicked();
    void on_openSerialButton_searchport_clicked();
    void showRecivedData(qreal);

private:
    Ui::SerialCom *ui;
    QSerialPort* mySerial;
    QStringList* portNames;
    bool isOpenButtonOpen;
    QString receivedMessage;
    qreal data;

signals:
    void serialSend(qreal data);
    void sendSerialPort(QSerialPort *myport);
};

#endif // SerialCom_H
