#include "dynamicchart.h"
#include "ui_dynamicchart.h"

DynamicChart::DynamicChart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DynamicChart)
{
    ui->setupUi(this);

    chart=new QChart();
    series=new QSplineSeries(this);
    axisX=new QValueAxis(this);
    axisY=new QValueAxis(this);

    ui->graphicsView->setChart(chart);

    QPen green(Qt::red);
    green.setWidth(3);
    series->setPen(green);
    series->append(x,y);

    chart->addSeries(series);
    chart->addAxis(axisX,Qt::AlignBottom);
    chart->addAxis(axisY,Qt::AlignLeft);

    series->attachAxis(axisX);
    series->attachAxis(axisY);

    axisX->setTickCount(5);
    axisX->setRange(0,10);
    axisY->setRange(-5,10);


}

DynamicChart::~DynamicChart()
{
    delete ui;
}

void DynamicChart::Draw(qreal dp)
{
    qDebug()<<"Draw";

    if(chart->isVisible()==true)
    {
        qreal _x=chart->plotArea().width()/axisX->tickCount();
        qreal _y=(axisX->max()-axisX->min())/axisX->tickCount();

        x+=_y;
        y=dp;

        series->append(x,y);

        chart->scroll(x,0);
    }
    else
    {
        qDebug()<<"图表被隐藏，图表将不更新";
    }


}

