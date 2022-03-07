#ifndef LINECHART_UI_H
#define LINECHART_UI_H

#include <QWidget>
#include <QString>
#include <QDebug>
#include <QtCharts>
#include <QPen>

namespace Ui {
class LineChart_UI;
}

class LineChart_UI : public QWidget
{
    Q_OBJECT

public:
    explicit LineChart_UI(QWidget *parent = 0);
    ~LineChart_UI();

    void setAxisRange(int xMin,int xMax,int yMin,int yMax);//设置x,y轴范围
    void setAxisXTitle(QString name="时间");//设置x轴名字
    void setAxisYTitle(QString name="值");//设置x轴名字
    void setMyChartTitle(QString title);//设置图表标题

    void lineChartUpdate1P(qreal data);//图表末尾新增一个点，动态图表
    void setRefreshMode(int mode);


private:
    Ui::LineChart_UI *ui;

    QChart *myChart;//图表
    QLineSeries *mySeries;//线
    QValueAxis *axisx;//x轴
    QValueAxis *axisy;//y轴
    int xMin,xMax,yMin,yMax;
    QPen pen;//画笔

    int refreshMode;
    bool refreshFlag;
};

#endif // LINECHART_UI_H
