#include "dynamiccurve.h"
#include "ui_dynamiccurve.h"

DynamicCurve::DynamicCurve(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DynamicCurve)
{
    ui->setupUi(this);

    //动态分配空间
    myChart=new QChart();//chart
    mySeries=new QLineSeries(this);
    axisx=new QValueAxis(this);//x轴
    axisy=new QValueAxis(this);//y轴


    mySeries->setUseOpenGL(true);//使用openGL绘图

    ui->qchartview->setChart(myChart);

    myChart->addSeries(mySeries);//添加线条

    axisx->setRange(0,100);//x轴范围
    axisy->setRange(-100,100);//y轴范围

    axisx->setTitleText("时间点");
    axisy->setTitleText("应力值");

    axisx->setTickCount(11);//控制x轴栅格个数
    axisx->setMinorTickCount(1);
    axisx->setLabelFormat("%d");

    axisy->setTickCount(21);//控制x轴栅格个数

    myChart->setAxisX(axisx,mySeries);
    myChart->setAxisY(axisy,mySeries);
    //myChart->legend()->hide();//设置图例隐藏
    mySeries->setName("载荷-时间");

    pen.setColor(Qt::red);//颜色
    pen.setWidth(2);//曲线宽度
    mySeries->setPen(pen);//设置笔

    for(int i=0;i<=100;i++)//0~max_x赋初始值0
       mySeries->append(i,0);
}

DynamicCurve::~DynamicCurve()
{
    delete myChart;
    delete ui;
}

//更新数据函数，删除第一个元素，尾部添加新的元素
void DynamicCurve::chartUpdate1P(qreal data)
{

    mySeries->remove(0);//删除第一个元素
    mySeries->append(0,data);//尾部添加新的元素

    //更新点x坐标
    for(uint16_t i=0;i<mySeries->count();i++)
       mySeries->replace(i,i,mySeries->at(i).y());
}

void DynamicCurve::setMyChartTitle(QString title)
{
    myChart->setTitle(title);
}

void DynamicCurve::setAxisXRange(qint16 start, qint16 end)//设置x轴范围
{
    axisx->setRange(start,end);
}

void DynamicCurve::setAxisYRange(qint16 start, qint16 end)//设置y轴范围
{
    axisy->setRange(start,end);
}

void DynamicCurve::setAxisXTitle(QString name)//设置x轴标题
{
    axisx->setTitleText(name);
}

void DynamicCurve::setAxisYTitle(QString name)//设置y轴标题
{
    axisy->setTitleText(name);
}
