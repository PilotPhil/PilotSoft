#include "serialcom.h"
#include "ui_SerialCom.h"

SerialCom::SerialCom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialCom)
{
    ui->setupUi(this);

    //动态空间
    mySerial=new QSerialPort(this);//串口动态分配空间
    portNames=new QStringList;

    //初始化
    searchPorts();//获取可用串口名
    isOpenButtonOpen=false;
    ui->progressBar->setTextVisible(false);//设置进度条数字不显示

    //信号与槽连接
    connect(mySerial,&QSerialPort::readyRead,this,&SerialCom::readData);

    ui->openSerialButton_searchport->setIcon(QIcon(":/查找.png"));
}

SerialCom::~SerialCom()
{
    if(mySerial->isOpen())
    {
        mySerial->close();
    }
    delete portNames;
    delete mySerial;
    delete ui;
}

void SerialCom::on_bradBox_currentIndexChanged(int index)
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

void SerialCom::on_dataBitsBox_currentIndexChanged(int index)
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

void SerialCom::on_parityBox_currentIndexChanged(int index)
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

void SerialCom::on_stopBitsBox_currentIndexChanged(int index)
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

void SerialCom::on_openSerialButton_clicked()
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

void SerialCom::setSerialCom()
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

void SerialCom::searchPorts()
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

void SerialCom::openPort()
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

void SerialCom::closePort()
{
    mySerial->clear();
    mySerial->close();
    qDebug()<<"串口已关闭";
    ui->openSerialButton->setText("打开串口");
}

void SerialCom::readData()
{
    //receivedMessage=mySerial->readLine();
    //data=receivedMessage.toDouble();
    //ui->serialDataRead->setText(receivedMessage);//显示读取到的数据
    //emit serialSend(data);//发送给实时显示图表数据信号，挤入更新

    emit sendSerialPort(mySerial);
}

void SerialCom::on_openSerialButton_searchport_clicked()
{
    searchPorts();
}

void SerialCom::showRecivedData(qreal inp)
{
    ui->serialDataRead->setText(QString::number(inp));
}

