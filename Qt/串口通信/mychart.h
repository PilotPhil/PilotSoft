#ifndef MYCHART_H
#define MYCHART_H

#include <QWidget>
#include <QtCharts>

namespace Ui {
class myChart;
}

class myChart : public QWidget
{
    Q_OBJECT

public:
    explicit myChart(QWidget *parent = nullptr);
    ~myChart();

    void updateChart(qreal data);

private:
    Ui::myChart *ui;
    QChart *chart;//图表
    QLineSeries *mySeries;//线
    QValueAxis *axisx;//x轴
    QValueAxis *axisy;//y轴
    QValueAxis *axisx1;//x轴
    QValueAxis *axisy1;//y轴
};

#endif // MYCHART_H
