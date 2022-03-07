#include "algorithm_ui.h"
#include "ui_algorithm_ui.h"
#include <QMetaType>

Q_DECLARE_METATYPE(QList<qreal>)

Algorithm_UI::Algorithm_UI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Algorithm_UI)
{
    ui->setupUi(this);

    qRegisterMetaType <QList<qreal>>("QList<qreal>");//注册类型

    //设置初始值
    ui->AD->setValue(0);//AD精度
    ui->Bridge->setCurrentIndex(2);//电桥初始为 1/4桥
    ui->K->setValue(1);//灵敏度
    ui->Vref->setValue(1);//参考电压
    ui->Gain->setValue(1);//增益
    ui->yangs->setValue(0.001);//杨氏模数
    ui->loadNum->setValue(100);//载入点个数
    ui->ultraStress->setValue(235);//极限应力
    ui->comboBox_SN->setCurrentIndex(0);//S_N曲线

    //所有控件一旦改动并触发 读取这些控件当前值并发送至算法线程
    connect(ui->AD,&QDoubleSpinBox::editingFinished,this,&Algorithm_UI::getAlgorithmParam);
    connect(ui->Bridge,SIGNAL(currentIndexChanged(int)),this,SLOT(getAlgorithmParam()));
    connect(ui->K,&QDoubleSpinBox::editingFinished,this,&Algorithm_UI::getAlgorithmParam);
    connect(ui->Vref,&QDoubleSpinBox::editingFinished,this,&Algorithm_UI::getAlgorithmParam);
    connect(ui->Gain,&QDoubleSpinBox::editingFinished,this,&Algorithm_UI::getAlgorithmParam);
    connect(ui->yangs,&QDoubleSpinBox::editingFinished,this,&Algorithm_UI::getAlgorithmParam);
    connect(ui->loadNum,&QDoubleSpinBox::editingFinished,this,&Algorithm_UI::getAlgorithmParam);
    connect(ui->ultraStress,&QDoubleSpinBox::editingFinished,this,&Algorithm_UI::getAlgorithmParam);
    connect(ui->comboBox_SN,SIGNAL(currentIndexChanged(int)),this,SLOT(getAlgorithmParam()));

}

Algorithm_UI::~Algorithm_UI()
{
    delete ui;
}

void Algorithm_UI::getAlgorithmParam()
{
    AD=ui->AD->value();
    K=ui->K->value();
    Vref=ui->Vref->value();
    Gain=ui->Gain->value();

    switch (ui->Bridge->currentIndex())
    {
    case 0:
        Bridge=4;
        break;
    case 1:
        Bridge=2;
        break;
    case 2:
        Bridge=1;
        break;
    default:
        Bridge=1;
        break;
    }

    V2S=(Bridge*Vref)/(Gain*K*qPow(2,AD));//1
    loadNum=ui->loadNum->value();//2
    yangs=ui->yangs->value();//3
    ultraStress=ui->ultraStress->value();//4

    switch (ui->comboBox_SN->currentIndex())
    {
    case 0:
        S_N=5.8E12;
        break;
    case 1:
        S_N=3.464E12;
        break;
    case 2:
        S_N=1.52E12;
        break;
    case 3:
        S_N=1.026E12;
        break;
    case 4:
        S_N=6.319E11;
        break;
    case 5:
        S_N=4.33E11;
        break;
    case 6:
        S_N=2.481E11;
        break;
    case 7:
        S_N=9.279E10;
        break;
    default:
        break;
    }

    allParam.clear();//先清除

    allParam<<V2S<<loadNum<<yangs<<ultraStress<<S_N;//加入list中

    emit sendAlgorithm(allParam);//发送全部
}


