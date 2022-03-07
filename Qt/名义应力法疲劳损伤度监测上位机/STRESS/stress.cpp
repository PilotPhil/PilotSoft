#include "stress.h"
#include "ui_stress.h"

STRESS::STRESS(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::STRESS)
{
    ui->setupUi(this);

    /*------------------------------主窗口ui------------------------------*/
    this->setWindowTitle("STRESS");//窗体标题
    this->setWindowIcon(QIcon(":/softwareIcon/ship.png"));//窗体Icon

    //工具箱默认显示第0个
    ui->toolBox->setCurrentIndex(0);//工具箱默认显示第一个

    //设置工具箱的Icon
    ui->toolBox->setItemIcon(0,QIcon(":/toolBoxIcon/通信.png"));
    ui->toolBox->setItemIcon(1,QIcon(":/toolBoxIcon/裂缝.png"));
    ui->toolBox->setItemIcon(2,QIcon(":/toolBoxIcon/数据库.png"));
    ui->toolBox->setItemIcon(3,QIcon(":/toolBoxIcon/关于.png"));


    /*------------------------------串口ui 与 串口读取线程------------------------------*/
    serial_ui=new Serial_UI(ui->widget_serial);//串口ui对象
    serialRead_thread=new SerialRead_Thread;//串口读取线程对象
    thread1=new QThread(this);//子线程1
    serialRead_thread->moveToThread(thread1);//串口读取线程对象加入到子线程1中
    thread1->start();//子线程1开启

    //串口ui对象发送配置好的串口指针给串口读取线程
    connect(serial_ui,&Serial_UI::sendSerialPort,serialRead_thread,&SerialRead_Thread::serialRead);
    //串口读取线程发送读取的数据给串口ui显示
    connect(serialRead_thread,&SerialRead_Thread::ReceivedData,serial_ui,&Serial_UI::showRecivedData);


    /*------------------------------折线图ui------------------------------*/
    //ui->stackedWidget->setCurrentIndex(0);//堆叠窗口默认显示第0个
    lineChart=new LineChart_UI(ui->widget_curve);//曲线图分配空间，设置其父对象为某widget
    connect(this,&STRESS::sendLineChartAxisParam,lineChart,&LineChart_UI::setAxisRange);//设置折线图的x,y坐标轴范围
    connect(this,&STRESS::sendLineChartRefreshMode,lineChart,&LineChart_UI::setRefreshMode);


    /*------------------------------算法ui 与 算法线程------------------------------*/
    algorithm_ui=new Algorithm_UI(ui->widget_algorithm);//算法ui对象
    algorithm_thread=new Algorithm_Thread;//算法线程对象
    thread2=new QThread(this);//子线程2
    algorithm_thread->moveToThread(thread2);//算法线程对象加入到子线程2中
    thread2->start();//子线程2开启

    //ui控件值发送至算法线程设置参数
    connect(algorithm_ui,&Algorithm_UI::sendAlgorithm,algorithm_thread,&Algorithm_Thread::setAlogorithmParam);
    //串口线程读取的值发送给算法线程
    connect(serialRead_thread,&SerialRead_Thread::ReceivedData,algorithm_thread,&Algorithm_Thread::Algorithm_Thread_Enter);
    //算法线程发送应力给曲线图ui显示
    connect(algorithm_thread,&Algorithm_Thread::sendStress,lineChart,&LineChart_UI::lineChartUpdate1P);


    /*------------------------------表视图------------------------------*/
    table_ui=new Table_UI(ui->widget_for_tabel);//表分配空间，设置其父对象为某widget

    //算法中损伤度计算结果发送给表显示
    connect(algorithm_thread,&Algorithm_Thread::sendAlgorithmRes,table_ui,&Table_UI::updateTable);

}

STRESS::~STRESS()
{
    thread1->quit();//子线程1退出
    thread1->wait();//等待子线程1完全退出

    thread2->quit();//子线程2退出
    thread2->wait();//等待子线程2完全退出

    delete ui;
}

//切换到动态应力曲线视图
void STRESS::on_action_triggered()
{
    //ui->stackedWidget->setCurrentIndex(0);//
}

//切换到损伤度视图
void STRESS::on_action_2_triggered()
{
    //ui->stackedWidget->setCurrentIndex(1);//
}

void STRESS::on_pushButton_clicked()
{
    int linChartAxisxMin=ui->xMin->value();
    int linChartAxisxMax=ui->xMax->value();
    int linChartAxisyMin=ui->yMin->value();
    int linChartAxisyMax=ui->yMax->value();

    //发送x,y坐标轴范围
    emit sendLineChartAxisParam(linChartAxisxMin,linChartAxisxMax,linChartAxisyMin,linChartAxisyMax);


    if (ui->refresh_continous->isChecked())
    {
        emit sendLineChartRefreshMode(0);//发送刷新方式
    }
    else
    {
        emit sendLineChartRefreshMode(1);
    }
}

//两个勾选按钮互斥
void STRESS::on_refresh_continous_clicked()
{
    ui->refresh_repete->setChecked(false);
}
void STRESS::on_refresh_repete_clicked()
{
    ui->refresh_continous->setChecked(false);
}
