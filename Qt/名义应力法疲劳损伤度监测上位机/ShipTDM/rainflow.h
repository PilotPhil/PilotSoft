#ifndef RAINFLOW_H
#define RAINFLOW_H

#include <QWidget>
#include <QDebug>

class RainFlow : public QWidget
{
    Q_OBJECT
public:
    explicit RainFlow(QWidget *parent = 0);
    ~RainFlow();

    void NoSame(QVector<qreal> *inp);
    void PeakVally(QVector<qreal> *inp);
    void PeriodAdjust(QVector<qreal> *inp);

signals:

public slots:

private:
    QVector<qreal> *tempVector;//载荷历程交换时的临时数组
};

#endif // RAINFLOW_H
