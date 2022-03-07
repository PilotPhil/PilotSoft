#include "mychart.h"
#include "ui_mychart.h"

myChart::myChart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myChart)
{
    ui->setupUi(this);

    chart=ui->graphicsView->chart();
    mySeries=new QLineSeries(this);
    axisx=new QValueAxis(this);
    axisy=new QValueAxis(this);
    axisx1=new QValueAxis(this);
    axisy1=new QValueAxis(this);

    mySeries->setUseOpenGL(true);

    chart->addSeries(mySeries);

    axisx->setRange(0,100);
    axisy->setRange(0,100);
    axisx1->setRange(0,100);
    axisy1->setRange(0,100);


    chart->legend()->hide();

    chart->addAxis(axisx,Qt::AlignBottom);
    chart->addAxis(axisy,Qt::AlignLeft);
    chart->addAxis(axisx1,Qt::AlignTop);
    chart->addAxis(axisy1,Qt::AlignRight);



}

myChart::~myChart()
{
    delete ui;
}

void myChart::updateChart(qreal data)
{
    static int num=0;

    if(mySeries->count()<100)
    {
        mySeries->append(num,data);
        num++;
    }
    else
    {
        mySeries->remove(0);
        mySeries->append(0,data);

        for(int i=0;i<100;i++)
        {
            mySeries->replace(i,i,mySeries->at(i).y());
        }
    }

}
