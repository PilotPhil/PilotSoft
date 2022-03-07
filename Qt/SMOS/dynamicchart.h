#ifndef DYNAMICCHART_H
#define DYNAMICCHART_H

#include <QWidget>
#include <QString>
#include <QDebug>
#include <QtCharts>
#include <QPen>
#include <QTimer>
#include <QRandomGenerator>

using namespace QtCharts;

namespace Ui {
class DynamicChart;
}

class DynamicChart : public QWidget
{
    Q_OBJECT

public:
    explicit DynamicChart(QWidget *parent = nullptr);
    ~DynamicChart();

public slots:
    void Draw(qreal dp);


private:
    Ui::DynamicChart *ui;

    QChart *chart;
    QSplineSeries *series;
    QStringList titles;
    QValueAxis *axisX;
    QValueAxis *axisY;
    qreal step;
    qreal x;
    qreal y;

};

#endif // DYNAMICCHART_H
