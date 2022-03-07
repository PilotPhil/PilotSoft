#include "serial.h"
#include "ui_serial.h"

serial::serial(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::serial)
{
    ui->setupUi(this);

    thread_serialSetting=new SerialSetting_thread();
    thread1=new QThread(this);
    thread_serialSetting->moveToThread(thread1);
    thread1->start();

    ui_serialSetting=new SerialSetting_ui(ui->widget);

    connect(ui_serialSetting,&SerialSetting_ui::sendSerialPort,thread_serialSetting,&SerialSetting_thread::serialRead);
    connect(thread_serialSetting,&SerialSetting_thread::SerialReadSend,this,&serial::ReceiveSerialData);


    chart=new myChart(ui->widget_chart);

    connect(this,&serial::sendData,chart,&myChart::updateChart);

}

serial::~serial()
{
    thread1->quit();
    thread1->wait();

    delete ui;
}

void serial::ReceiveSerialData(QString msg)
{
    qDebug()<<msg;

    qreal data=msg.toDouble();
    sendData(data);
}




