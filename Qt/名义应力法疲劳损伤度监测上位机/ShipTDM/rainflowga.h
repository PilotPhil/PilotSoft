#ifndef RAINFLOWGA_H
#define RAINFLOWGA_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QtCharts>

class RainFlowGA : public QObject
{
    Q_OBJECT
public:
    explicit RainFlowGA(QObject *parent = 0);
    ~RainFlowGA();

    void NoSame(QVector<qreal> *inp);
    void PeakVally(QVector<qreal> *inp);
    void PeriodAdjust(QVector<qreal> *inp);


public slots:
    void RF(QVector<qreal> *inp);
    void dataForRF_Ready(qreal data,int num);

private:
    qreal temp;
    QVector<qreal> *tempVector;//载荷历程交换时的临时数组
    QVector<qreal> *seriesData_RF;

signals:
    void dataForRF_Prepared(QVector<qreal> *data);
};

#endif // RAINFLOWGA_H
