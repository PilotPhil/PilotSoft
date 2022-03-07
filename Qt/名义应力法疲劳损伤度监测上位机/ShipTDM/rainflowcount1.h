#ifndef RAINFLOWCOUNT_H
#define RAINFLOWCOUNT_H

#include <QWidget>
#include <QDebug>
#include <QThread>

namespace Ui {
class RainFlowCount;
}

class RainFlowCount : public QWidget
{
    Q_OBJECT

public:
    explicit RainFlowCount(QWidget *parent = 0);
    ~RainFlowCount();


    void NoSame(QVector<qreal> *inp);
    void PeakVally(QVector<qreal> *inp);
    void PeriodAdjust(QVector<qreal> *inp);

public slots:
    void RF(QVector<qreal> *inp);
private:
    Ui::RainFlowCount *ui;

    QVector<qreal> *tempVector;//载荷历程交换时的临时数组
};

#endif // RAINFLOWCOUNT_H
