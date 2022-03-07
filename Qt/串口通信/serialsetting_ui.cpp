#include "serialsetting_ui.h"
#include "ui_serialsetting_ui.h"

SerialSetting_ui::SerialSetting_ui(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialSetting_ui)
{
    ui->setupUi(this);

    mySerial=new QSerialPort(this);
    portNames=new QStringList;

    searchPorts();
    isOpenButtonOpen=false;
    void (QComboBox::*comboBoxIndexChanged)(int)=&QComboBox::currentIndexChanged;
    connect(ui->serialPortNameBox,comboBoxIndexChanged,this,&SerialSetting_ui::setSerialCom);
    connect(ui->bradBox,comboBoxIndexChanged,this,&SerialSetting_ui::setSerialCom);
    connect(ui->dataBitsBox,comboBoxIndexChanged,this,&SerialSetting_ui::setSerialCom);
    connect(ui->parityBox,comboBoxIndexChanged,this,&SerialSetting_ui::setSerialCom);
    connect(ui->stopBitsBox,comboBoxIndexChanged,this,&SerialSetting_ui::setSerialCom);
    connect(ui->searchPortButton,&QPushButton::clicked,this,&SerialSetting_ui::searchPorts);

    connect(mySerial,&QSerialPort::readyRead,this,&SerialSetting_ui::startReadData);


}

SerialSetting_ui::~SerialSetting_ui()
{
    delete ui;
}

//查找端口
void SerialSetting_ui::searchPorts()
{
    portNames->clear();
    foreach (const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        *portNames<<info.portName();
        qDebug()<<"可用串口有"<<info.portName();
    }
    ui->serialPortNameBox->clear();
    ui->serialPortNameBox->addItems(*portNames);
}
//设置串口
void SerialSetting_ui::setSerialCom()
{
    if(mySerial->isOpen())
    {
        //设置波特率
        switch(ui->bradBox->currentIndex())
        {
        case 0:
            mySerial->setBaudRate(9600);
            break;
        case 1:
            mySerial->setBaudRate(14400);
            break;
        case 2:
            mySerial->setBaudRate(19200);
            break;
        case 3:
            mySerial->setBaudRate(38400);
            break;
        case 4:
            mySerial->setBaudRate(57600);
            break;
        case 5:
            mySerial->setBaudRate(115200);
            break;
        case 6:
            mySerial->setBaudRate(128000);
            break;
        default:
            break;
        }

        //设置数据位
        switch(ui->dataBitsBox->currentIndex())
        {
        case 0:
            mySerial->setDataBits(QSerialPort::Data8);
            break;
        case 1:
            mySerial->setDataBits(QSerialPort::Data7);
            break;
        case 2:
            mySerial->setDataBits(QSerialPort::Data6);
            break;
        case 3:
            mySerial->setDataBits(QSerialPort::Data5);
            break;
        default:
            break;
        }

        //设置校验位
        switch(ui->parityBox->currentIndex())
        {
        case 0:
            mySerial->setParity(QSerialPort::NoParity);
            break;
        case 1:
            mySerial->setParity(QSerialPort::EvenParity);
            break;
        case 2:
            mySerial->setParity(QSerialPort::MarkParity);
            break;
        case 3:
            mySerial->setParity(QSerialPort::OddParity);
            break;
        default:
            break;
        }

        //设置停止位
        switch(ui->stopBitsBox->currentIndex())
        {
        case 0:
            mySerial->setStopBits(QSerialPort::OneStop);
            break;
        case 1:
            mySerial->setStopBits(QSerialPort::OneAndHalfStop);
            break;
        case 2:
            mySerial->setStopBits(QSerialPort::TwoStop);
            break;
        default:
            break;
        }
    }
}
//打开串口
void SerialSetting_ui::openPort()
{
    if(mySerial->isOpen())//如果已经打开了
    {
        mySerial->clear();//先关闭
        mySerial->close();
    }

    mySerial->setPortName(ui->serialPortNameBox->currentText());//设置串口名

    if(!mySerial->open(QIODevice::ReadWrite))
        qDebug()<<"打开失败";
    else
        qDebug()<<"串口已打开";

    setSerialCom();//设置串口通信参数
    ui->openSerialButton->setText("关闭串口");//设置按钮显示内容为 关闭串口
}
//关闭串口
void SerialSetting_ui::closePort()
{
    mySerial->clear();
    mySerial->close();
    qDebug()<<"串口已关闭";
    ui->openSerialButton->setText("打开串口");
}
//读取数据
void SerialSetting_ui::startReadData()
{
    emit sendSerialPort(mySerial);
}
//显示接收到的数据
void SerialSetting_ui::showRecivedData(qreal inp)
{
    //ui->serialDataRead->setText(QString::number(inp));
}
//串口开关 复用
void SerialSetting_ui::on_openSerialButton_clicked()
{
    qDebug()<<"pressed";
    if(isOpenButtonOpen)//
    {
        closePort();
        isOpenButtonOpen=false;
    }
    else
    {
        openPort();
        isOpenButtonOpen=true;
    }
}
