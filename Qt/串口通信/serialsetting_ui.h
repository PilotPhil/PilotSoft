#ifndef SERIALSETTING_UI_H
#define SERIALSETTING_UI_H

#include <QWidget>
#include <QDebug>
#include <QThread>
#include <QSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class SerialSetting_ui;
}

class SerialSetting_ui : public QWidget
{
    Q_OBJECT

public:
    explicit SerialSetting_ui(QWidget *parent = nullptr);
    ~SerialSetting_ui();

    void searchPorts();
    void setSerialCom();
    void openPort();
    void closePort();
    void startReadData();
    void showRecivedData(qreal inp);

private slots:
    void on_openSerialButton_clicked();

private:
    Ui::SerialSetting_ui *ui;

    QSerialPort* mySerial;//串口指针
    QStringList* portNames;//串口名
    bool isOpenButtonOpen;//串口是否打开标志位
    QString receivedMessage;//接收到的字符串

signals:
    void sendSerialPort(QSerialPort *);
};

#endif // SERIALSETTING_UI_H
