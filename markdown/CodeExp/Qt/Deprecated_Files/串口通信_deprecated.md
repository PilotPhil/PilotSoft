# 串口通信
### 1.pro中加入`QT       += serialport`
### 2.构造函数中
```c++
QSerialPort* mySerial==new QSerialPort(this);//串口动态分配空间
QStringList portNames=new QStringList;//串口名分配空间

searchPorts();//获取可用串口名

connect(mySerial,&QSerialPort::readyRead,this,&STRESS::startReadData);
```

### 3.查找端口
```c++
//查找端口
void STRESS::searchPorts()
{
    portNames->clear();
    foreach (const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        *portNames<<info.portName();
        qDebug()<<"可用串口有"<<info.portName();
    }
    ui->serialPortNameBox->clear();//清空下拉框
    ui->serialPortNameBox->addItems(*portNames);//更新到下拉框中
}
```
### 4.设置串口
```c++
void STRESS::setSerialCom()
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
```

### 5.打开串口
```c++
void STRESS::openPort()
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
```

### 6.关闭串口
```c++
void STRESS::closePort()
{
    mySerial->clear();
    mySerial->close();
    qDebug()<<"串口已关闭";
    ui->openSerialButton->setText("打开串口");
}
```
### 7.开始接收数据-->==发送串口指针让子线程读取==
```c++
void STRESS::startReadData()
{
    emit sendSerialPort(mySerial);
}

//串口读取数据，接收一个数据发送出去
void SerialRead_Thread::serialRead(QSerialPort *myport)
{
    //接收到串口读取信号后读取串口
    msg=myport->readLine();//读取数据
    serialData=msg.toDouble();//

    emit ReceivedData(serialData);
}
```

# 分布统计(条形图)
```c++
//初始化用于存储统计个数的二维数组
//X：分段
//y：出现的个数
QVector<QPoint> *count=new QVector<QPoint>;

//分布求取函数
void dataDistribution(QVector<qreal> *inp)
{
    count->clear();

    qDebug()<<"dataDistributionOK";
    /*---------------校验数据是否合理---------------*/
    if(step!=1&&step!=2&&step!=5&&step!=10)
    {
        qDebug()<<"步长不符合要求";
        return;//退出
    }

    /*---------------找到数组中最小值和最大值---------------*/
    qreal min=inp->at(0),max=inp->at(0);
    for(int idx=0;idx<inp->size();idx++)
    {
        if(min>inp->at(idx))
        {
            min=inp->at(idx);
        }
        if(max<inp->at(idx))
        {
            max=inp->at(idx);
        }
    }
    qDebug()<<"min:"<<min<<"max:"<<max;

    /*---------------取整---------------*/
    int fixMin=min/10,fixMax=max/10;
    fixMin*=10;//最小值向下 取整

    fixMax+=1;//最大值向上 取整
    fixMax*=10;
    qDebug()<<"fixMin"<<fixMin<<"fixMax"<<fixMax;

    /*---------------开始统计分布---------------*/
    QVector<QPoint> *count=new QVector<QPoint>;
    int num=(fixMax-fixMin)/step;
    for(int i=0;i<num;i++)
    {
        count->append(QPoint(i*step,0));//构造用来存储统计个数的数组
    }
    qDebug()<<"存储个数的数组:"<<count;

    int start=fixMin;//比较量
    int i=0;//统计个数的数组索引
    for(int idx=0;idx<inp->size();idx++)
    {
        while(start!=fixMax)
        {
            if(start<=inp->at(idx)&&inp->at(idx)<(start+10))
            {
                count->replace(i,QPoint(count->at(i).x(),count->at(i).y()+1));
            }
            i++;
            start+=step;
        }
        i=0;//复原
        start=fixMin;//复原
    }
    emit distriRes(count);
    qDebug()<<"存储个数的数组:"<<*count;
}
```