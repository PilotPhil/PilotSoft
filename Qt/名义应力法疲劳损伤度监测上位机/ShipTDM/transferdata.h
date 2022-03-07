#ifndef TRANSFERDATA_H
#define TRANSFERDATA_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class TransferData;
}

class TransferData : public QWidget
{
    Q_OBJECT

public:
    explicit TransferData(QWidget *parent = 0);
    ~TransferData();

private:
    Ui::TransferData *ui;

public slots:
    void TransferToStrain(qreal inp);//转化为应变

signals:
    void strainData(qreal strain);//发送应变
    void stressData(qreal stress);//发送应力
};

#endif // TRANSFERDATA_H
