#include "serial_ui.h"
#include "ui_serial_ui.h"

Serial_UI::Serial_UI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Serial_UI)
{
    ui->setupUi(this);

    mySerial=new QSerialPort(this);//串口动态分配空间
    portNames=new QStringList;//串口名分配空间

    searchPorts();//获取可用串口名
    isOpenButtonOpen=false;//串口是否打开标志位为 否

    //串口准备好读取，就发送信号读取--->发送串口指针，让串口读取线程去读取
    connect(mySerial,&QSerialPort::readyRead,this,&Serial_UI::readData);

    //设置串口查找按钮图标
    ui->openSerialButton_searchport->setIcon(QIcon(":/COM/查找.png"));
}

Serial_UI::~Serial_UI()
{
    delete ui;
}

void Serial_UI::setSerialCom()
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

void Serial_UI::searchPorts()
{
    portNames->clear();
    foreach (const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        *portNames<<info.portName();
        qDebug()<<"可用串口有"<<info.portName();
    }
    ui->comBox_serialPortName->clear();
    ui->comBox_serialPortName->addItems(*portNames);
}

void Serial_UI::openPort()
{
    if(mySerial->isOpen())//如果已经打开了
    {
        mySerial->clear();//先关闭
        mySerial->close();
    }

    mySerial->setPortName(ui->comBox_serialPortName->currentText());//设置串口名

    if(!mySerial->open(QIODevice::ReadWrite))
        qDebug()<<"打开失败";
    else
        qDebug()<<"串口已打开";

    setSerialCom();//设置串口通信参数
    ui->openSerialButton->setText("关闭串口");//设置按钮显示内容为 关闭串口
}

void Serial_UI::on_openSerialButton_clicked()
{
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

void Serial_UI::closePort()
{
    mySerial->clear();
    mySerial->close();
    qDebug()<<"串口已关闭";
    ui->openSerialButton->setText("打开串口");
}

void Serial_UI::readData()
{
    emit sendSerialPort(mySerial);
}

void Serial_UI::on_openSerialButton_searchport_clicked()
{
    searchPorts();
}

void Serial_UI::showRecivedData(qreal inp)
{
    ui->serialDataRead->setText(QString::number(inp));
}

void Serial_UI::on_bradBox_currentIndexChanged(int index)
{
    if(mySerial->isOpen())
    {
        //设置波特率
        switch(index)
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
    }
}

void Serial_UI::on_dataBitsBox_currentIndexChanged(int index)
{
    if(mySerial->isOpen())
    {
     switch(index)
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
     }
}

void Serial_UI::on_parityBox_currentIndexChanged(int index)
{
    if(mySerial->isOpen())
    {
        switch(index)
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
    }
}

void Serial_UI::on_stopBitsBox_currentIndexChanged(int index)
{
    if(mySerial->isOpen())
    {
        switch(index)
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

