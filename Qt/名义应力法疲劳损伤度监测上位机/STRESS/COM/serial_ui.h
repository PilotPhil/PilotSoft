#ifndef SERIAL_UI_H
#define SERIAL_UI_H

#include <QWidget>
#include<QSerialPort>
#include<QSerialPortInfo>
#include<QString>
#include<QDebug>
#include<QVector>

namespace Ui {
class Serial_UI;
}

class Serial_UI : public QWidget
{
    Q_OBJECT

public:
    explicit Serial_UI(QWidget *parent = 0);
    ~Serial_UI();

    void searchPorts();//获取所有可用串口
    void openPort();//打开串口
    void closePort();//关闭串口
    void setSerialCom();//设置串口通讯参数
    void showRecivedData(qreal);
    void readData();//读取数据

private slots:
    void on_bradBox_currentIndexChanged(int index);
    void on_dataBitsBox_currentIndexChanged(int index);
    void on_parityBox_currentIndexChanged(int index);
    void on_stopBitsBox_currentIndexChanged(int index);
    void on_openSerialButton_clicked();
    void on_openSerialButton_searchport_clicked();


private:
    Ui::Serial_UI *ui;

    QSerialPort* mySerial;//串口指针
    QStringList* portNames;//串口名
    bool isOpenButtonOpen;//串口是否打开标志位
    QString receivedMessage;//接收到的字符串

signals:
    void serialSend(qreal data);//发送串口接收的数据
    void sendSerialPort(QSerialPort *myport);//发送串口指针给串口读取线程
};

#endif // SERIAL_UI_H
