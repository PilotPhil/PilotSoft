#ifndef SERIALCFG_H
#define SERIALCFG_H

#include <QWidget>
#include <QDebug>
#include <QThread>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

namespace Ui {
class SerialCfg;
}

class SerialCfg : public QWidget
{
    Q_OBJECT

public:
    explicit SerialCfg(QWidget *parent = nullptr);
    ~SerialCfg();

    void searchPorts();//查找端口
    void setSerial();//配置串口参数
    bool openPort();//打开端口
    void closePort();//关闭端口
    void readData();//读取数据

private:
    Ui::SerialCfg *ui;

    QSerialPort* serialPort;    // 串口指针
    QStringList* portNames;     // 端口名列表
    bool portOpenFlag;          // 端口是否开启
    QString data;               // 接收到的数据

signals:
    void sendSerialData(QString data);

private slots:
    void on_PB_openSerial_clicked();
};

#endif // SERIALCFG_H
