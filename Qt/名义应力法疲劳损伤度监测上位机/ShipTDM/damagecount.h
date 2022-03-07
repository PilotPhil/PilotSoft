#ifndef DAMAGECOUNT_H
#define DAMAGECOUNT_H

#include <QWidget>

namespace Ui {
class DamageCount;
}

class DamageCount : public QWidget
{
    Q_OBJECT

public:
    explicit DamageCount(QWidget *parent = 0);
    ~DamageCount();

private:
    Ui::DamageCount *ui;

signals:
    void loadNumer(int num);//载入点个数信号
    void ultraStress(int UStress);//极限应力信号

private slots:
    void on_RF_computeNumber_valueChanged(int arg1);
    void on_ultraStress_valueChanged(int arg1);
};

#endif // DAMAGECOUNT_H
