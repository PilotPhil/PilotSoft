#include "linechart_ui.h"
#include "ui_linechart_ui.h"

LineChart_UI::LineChart_UI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LineChart_UI)
{
    ui->setupUi(this);

    myChart=new QChart();//chart分配空间
    mySeries=new QLineSeries(this);//曲线系列
    axisx=new QValueAxis(this);//x轴
    axisy=new QValueAxis(this);//y轴

    mySeries->setUseOpenGL(true);//设置使用openGL绘图

    ui->graphicsView->setChart(myChart);//表加入到画布中，由graphicView提升为chartView

    myChart->addSeries(mySeries);//添加线条

    xMin=0;xMax=100;yMin=0;yMax=100;
    axisx->setRange(xMin,xMax);//x轴范围
    axisy->setRange(yMin,yMax);//y轴范围

    axisx->setTitleText("时间点");
    axisy->setTitleText("应力值");

    axisx->setTickCount(11);//控制x轴栅格个数
    axisx->setMinorTickCount(1);//设置小栅格数量
    axisx->setLabelFormat("%d");//设置x轴单位个数

    axisy->setTickCount(11);//控制x轴栅格个数

    myChart->setAxisX(axisx,mySeries);//设置x轴坐标轴
    myChart->setAxisY(axisy,mySeries);//设置y轴坐标轴
    //myChart->legend()->hide();//设置图例隐藏
    mySeries->setName("载荷-时间");//设置图表标题

    pen.setColor(Qt::red);//颜色-红色
    pen.setWidth(2);//曲线宽度
    mySeries->setPen(pen);//设置笔

    refreshMode=1;//刷新方式初始化为0
    refreshFlag=false;//刷新标志位
}

LineChart_UI::~LineChart_UI()
{
    delete ui;
}

//更新数据函数，删除第一个元素，尾部添加新的元素
void LineChart_UI::lineChartUpdate1P(qreal data)
{
    switch (refreshMode)
    {
    case 0://连续刷新
        static int num=0;

        if(refreshFlag==true)
        {
            mySeries->clear();
            refreshFlag=false;
        }

        if(mySeries->count()<xMax)//还不够x轴范围，就先增加点
        {
            mySeries->append(num,data);
            num++;
        }
        else
        {
            mySeries->remove(0);//删除第一个元素
            mySeries->append(0,data);//尾部添加新的元素（0，data) 0是随意的，因为下面要重新排列x坐标

            //更新点x坐标
            for(int i=0;i<mySeries->count();i++)
            {
                mySeries->replace(i,i,mySeries->at(i).y());
            }
        }
        break;

    case 1:
        if(refreshFlag==true)
        {
            mySeries->clear();
            refreshFlag=false;
        }

        static int num2=0;
        if(num2<=xMax)
        {
            mySeries->append(num2,data);
            num2++;
        }
        else if(num2==xMax+1)
        {
            mySeries->clear();
            num2=0;
        }
        else{}

        break;

    default:
        break;

    }
}

void LineChart_UI::setRefreshMode(int mode)
{
    refreshMode=mode;
    refreshFlag=true;
}

void LineChart_UI::setMyChartTitle(QString title)
{
    myChart->setTitle(title);
}

void LineChart_UI::setAxisRange(int xMin,int xMax,int yMin,int yMax)//设置x轴范围
{
    axisx->setRange(xMin,xMax);
    axisy->setRange(yMin,yMax);
    this->xMax=xMax;
    this->xMin=xMin;
    this->yMax=yMax;
    this->yMin=yMin;
}

void LineChart_UI::setAxisXTitle(QString name)//设置x轴标题
{
    axisx->setTitleText(name);
}

void LineChart_UI::setAxisYTitle(QString name)//设置y轴标题
{
    axisy->setTitleText(name);
}
