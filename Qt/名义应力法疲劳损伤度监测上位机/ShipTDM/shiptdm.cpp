#include "shiptdm.h"
#include "ui_shiptdm.h"

ShipTDM::ShipTDM(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShipTDM)
{
    ui->setupUi(this);

    /*------主窗口ui------*/
    this->setWindowTitle("SHIP TDM");
    this->setWindowIcon(QIcon(":/softwareICON/softwareIcon/ship.png"));
    this->setFixedSize(1600,1000);//固定窗口大小
    ui->toolBox->setItemIcon(0,QIcon(":/toolBoxIcon/toolBoxIcon/通信.png"));
    ui->toolBox->setItemIcon(1,QIcon(":/toolBoxIcon/toolBoxIcon/转换.png"));
    ui->toolBox->setItemIcon(2,QIcon(":/toolBoxIcon/toolBoxIcon/裂缝.png"));
    ui->toolBox->setItemIcon(3,QIcon(":/toolBoxIcon/toolBoxIcon/数据库.png"));
    ui->toolBox->setItemIcon(4,QIcon(":/toolBoxIcon/toolBoxIcon/关于.png"));
    ui->toolBox->setItemIcon(5,QIcon(":/toolBoxIcon/toolBoxIcon/日志.png"));
    ui->toolBox->setCurrentIndex(0);//工具箱默认显示第一个

    /*------串口设置与子线程1串口读取------*/
    mySerial=new SerialCom(ui->widget_serialcom);//添加入widget
    serialR=new myT_SerialReadOnly;//串口读取类实例化
    thread1=new QThread(this);//子线程1
    serialR->moveToThread(thread1);//加入子线程1中
    thread1->start();//子线程1启动
    connect(mySerial,SIGNAL(sendSerialPort(QSerialPort*)),serialR,SLOT(serialRead(QSerialPort*)));//信号传递串口号指针以调用串口读取类中读取串口数据的成员函数
    connect(serialR,SIGNAL(ReceivedData(qreal)),mySerial,SLOT(showRecivedData(qreal)));//显示串口接收到的数据

    /*------数据转换------*/
    DataToTransfer=new TransferData(ui->widget_transfer);//添加入widget
    connect(serialR,SIGNAL(ReceivedData(qreal)),DataToTransfer,SLOT(TransferToStrain(qreal)));//转换为应变


    /*------实时更新图表------*/
    rawDataChart=new DynamicCurve(ui->widget_dynamic_curve);//原始应变数据显示图表
    connect(DataToTransfer,SIGNAL(stressData(qreal)),rawDataChart,SLOT(chartUpdate1P(qreal)));//更新图表的信号与槽


    /*----雨流计数法子线程2----*/
    RF=new RF_Thread;//雨流计数法类实例化
    thread2=new QThread(this);//子线程2分配空间
    RF->moveToThread(thread2);//加入子线程2中
    thread2->start();//子线程2开始
    connect(DataToTransfer,SIGNAL(strainData(qreal)),RF,SLOT(PrepareData(qreal)));
    //connect(RF,SIGNAL(RF_AMP(QVector<qreal>*)),this,SLOT(test_AMP(QVector<qreal>*)));
    //connect(RF,SIGNAL(RF_AVG(QVector<qreal>*)),this,SLOT(test_AVG(QVector<qreal>*)));
    connect(RF,SIGNAL(modifiedStress(QVector<qreal>*)),this,SLOT(test_AMP(QVector<qreal>*)));

    /*----损伤度计算----*/
    damage=new DamageCount(ui->widget_damage);//添加入widget发送至雨流计数法
    connect(damage,SIGNAL(loadNumer(int)),RF,SLOT(setLoadNum(int)));//设置载入点个数并
    connect(damage,SIGNAL(ultraStress(int)),RF,SLOT(setUltraStress(int)));//设置极限应力


    /*----工具栏----*/
    realTimeView=new QPushButton(this);
    damageView=new QPushButton(this);

    realTimeView->setText("实时曲线视图");
    realTimeView->setIcon(QIcon(":/toolBarICON/toolBarICON/实时曲线.png"));
    ui->mainToolBar->addWidget(realTimeView);

    ui->mainToolBar->addSeparator();//添加分割符

    damageView->setText("损伤度视图");
    damageView->setIcon(QIcon(":/toolBarICON/toolBarICON/条形图.png"));
    ui->mainToolBar->addWidget(damageView);
    connect(realTimeView,SIGNAL(clicked(bool)),this,SLOT(showRealTimePage()));
    connect(damageView,SIGNAL(clicked(bool)),this,SLOT(showDamagePage()));
    ui->stackedWidget->setCurrentIndex(0);



    qDebug()<<"ui主线程号："<<QThread::currentThread();
}

ShipTDM::~ShipTDM()
{
    //串口读取线程1关闭
    thread1->quit();
    thread1->wait();


    //雨流计数法子线程2关闭
    thread2->quit();
    thread2->wait();

    delete ui;
}


void ShipTDM::test_AMP(QVector<qreal> *INP)
{
    qDebug()<<"AMP in main :\t\t"<<*INP;
}

void ShipTDM::test_AVG(QVector<qreal> *INP)
{
    qDebug()<<"AVG in main :\t\t"<<*INP;
}

void ShipTDM::showRealTimePage()//点击按钮切换到实时应力曲线界面
{
    ui->stackedWidget->setCurrentIndex(0);
}

void ShipTDM::showDamagePage()//点击按钮切换到损伤计算界面
{
    ui->stackedWidget->setCurrentIndex(1);
}


