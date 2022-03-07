#ifndef SHIPTDM_H
#define SHIPTDM_H

#include <QMainWindow>
#include "serialcom.h"
#include "dynamiccurve.h"
#include "transferdata.h"
#include "QRainFlow/rf_thread.h"
#include "myt_serialreadonly.h"
#include "damagecount.h"
#include "QPushButton"

namespace Ui {
class ShipTDM;
}

class ShipTDM : public QMainWindow
{
    Q_OBJECT
public:
    explicit ShipTDM(QWidget *parent = 0);
    ~ShipTDM();

private:
    Ui::ShipTDM *ui;

    //主线程0
    DynamicCurve *rawDataChart;//动态图
    SerialCom *mySerial;//串口

    //串口读取子线程1
    myT_SerialReadOnly *serialR;
    QThread *thread1;

    //数据转换
    TransferData *DataToTransfer;

    //雨流计数法子线程2
    RF_Thread *RF;
    QThread *thread2;

    //损伤度计算
    DamageCount *damage;

    //工具栏
    QPushButton *realTimeView;//实时图表视图按钮
    QPushButton *damageView;//损伤度显示视图

public slots:    
    void test_AMP(QVector<qreal> *);
    void test_AVG(QVector<qreal> *);

    void showRealTimePage();
    void showDamagePage();

signals:

};

#endif // SHIPTDM_H
