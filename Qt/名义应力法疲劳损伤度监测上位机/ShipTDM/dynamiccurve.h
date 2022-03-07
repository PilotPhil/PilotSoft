#ifndef DYNAMICCURVE_H
#define DYNAMICCURVE_H

/*------What is this------*/
/*动态折线图封装类
*/

/*------How to use?------*/
/*myDynamicChart* mdc=new myDynamicChart(this);
 * mdc->setAxisXRange(0,200);
 * mdc->setAxisYRange(0,30);
 * mdc->setMyChartTitle("XXX图");
 * mdc->setMyChart(ui->chartview);//creator中拖入一个Graphics View并提升为QChartView
*/

/*------Who made this------*/
/*Name:     Phil.Pilot
 *Date:     2020.3.13
*/

#include <QWidget>
#include <QString>
#include <QDebug>
#include <QtCharts>
#include <QPen>
using namespace QtCharts;

namespace Ui {
class DynamicCurve;
}

class DynamicCurve : public QWidget
{
    Q_OBJECT

public:
    explicit DynamicCurve(QWidget *parent = 0);
    ~DynamicCurve();

    void setAxisXRange(qint16 start,qint16 end);//设置x轴范围
    void setAxisYRange(qint16 start,qint16 end);//设置y轴范围
    void setAxisXTitle(QString name="时间");//设置x轴名字
    void setAxisYTitle(QString name="值");//设置x轴名字
    void setMyChartTitle(QString title);//设置图表标题

public slots:
    void chartUpdate1P(qreal data);//图表末尾新增一个点，动态图表

private:
    Ui::DynamicCurve *ui;

    //绘图用
    QChart *myChart;
    QLineSeries *mySeries;//线
    QValueAxis *axisx;//x轴
    QValueAxis *axisy;//y轴
    QPen pen;
};

#endif // DYNAMICCURVE_H
