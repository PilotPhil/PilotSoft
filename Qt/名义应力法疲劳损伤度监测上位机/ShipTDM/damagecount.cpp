#include "damagecount.h"
#include "ui_damagecount.h"

DamageCount::DamageCount(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DamageCount)
{
    ui->setupUi(this);

    ui->RF_computeNumber->setValue(100);//载入点个数初始化为100个
    emit loadNumer(100);//发送初始的载入点个数

    ui->ultraStress->setValue(235);//设置极限应力
    emit ultraStress(235);
}

DamageCount::~DamageCount()
{
    delete ui;
}

void DamageCount::on_RF_computeNumber_valueChanged(int arg1)
{
    emit loadNumer(arg1);//载入点个数改变后发送此信号更新
}

void DamageCount::on_ultraStress_valueChanged(int arg1)
{
    emit ultraStress(arg1);//极限应力改变后发送此信号用于更新
}
