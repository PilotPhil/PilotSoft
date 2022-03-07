#include "transferdata.h"
#include "ui_transferdata.h"

TransferData::TransferData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransferData)
{
    ui->setupUi(this);

    ui->AD->setValue(0);
    ui->Gain->setValue(1);
    ui->K->setValue(1);
    ui->Vref->setValue(1);
    ui->yangsNumber->setValue(210);
    ui->Bridge->setCurrentText("2");
}

TransferData::~TransferData()
{
    delete ui;
}

//转化为应变
void TransferData::TransferToStrain(qreal inp)
{
    qDebug()<<"strain:"<<inp;

    qreal Gain=ui->Gain->value();//增益
    qreal Vref=ui->Vref->value();//参考电压
    qreal K=ui->K->value();//灵敏度系数
    qreal AD=ui->AD->value();//AD
    qreal yangsNumber=ui->yangsNumber->value();//杨氏模数---单位GPa--*10^3-->MPa

    qreal strain=0;//应变
    strain=inp*Vref/(Gain*K*Vref*pow(2,AD));

    int bridge=ui->Bridge->currentIndex();//电桥选择
    switch (bridge)
    {
    case 0:
        strain*=4;
        break;
    case 1:
        strain*=2;
        break;
    case 2:
        strain*=1;
        break;
    default:
        break;
    }

    qreal stress=0;//应力
    stress=strain*yangsNumber*1000;//转化为应力

    ui->lcdNumber_stress->display(stress);
    //emit strainData(strain);
    emit stressData(stress);//发送应力
}
