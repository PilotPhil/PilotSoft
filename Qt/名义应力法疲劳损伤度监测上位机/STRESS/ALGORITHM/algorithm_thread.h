#ifndef ALGORITHM_THREAD_H
#define ALGORITHM_THREAD_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include <QThread>
#include <QtCore/QtMath>

class Algorithm_Thread : public QObject
{
    Q_OBJECT
public:
    explicit Algorithm_Thread(QObject *parent = 0);


    void Algorithm_Thread_Enter(qreal INP);//算法线程入口槽函数
    void setAlogorithmParam(QList<qreal>);//设置算法用到的所有参数
    void Volt2Strain(qreal inp);//电压转应变
    void Strain2Stress();//应变转应力
    void DataZip(QVector<qreal>*);//数据压缩=去除连续相等值+剔除非峰谷点
    void PeriodAdjust(QVector<qreal>*);//载荷历程调整
    void Point4Count(QVector<qreal>*);//四点计数法
    bool Point4Comp(qreal a, qreal b, qreal c, qreal d);//四点计数法循环判断函数
    void StressModify();//平均应力修正
    void DamageCompute();//损伤度计算

private:
    qreal strain;//应变
    qreal stress;//应力
    qreal V2S;//
    qreal yang;//杨氏模数
    qreal loadNum;//载入点个数
    qreal ultraStress;//极限应力
    qreal S_N;//SN曲线

    QVector<qreal> *dataForRF;//为雨流计数法准备的数据

    QVector<qreal> *AMP;//幅值
    QVector<qreal> *AVG;//均值
    QVector<qreal> *MStress;//平均应力修正后的应力范围
    QVector<qreal> *ultraS;//极限应力
    QVector<qreal> *Damage;//损伤度

signals:
    void sendStress(qreal stress);//发送应力
    void dataOK(QVector<qreal> *);//为雨流计数法准备的数据

    //发送算法得到的结果---包含所有
    void sendAlgorithmRes(QVector<qreal> *,QVector<qreal> *,QVector<qreal> *,QVector<qreal> *,QVector<qreal> *);
};

#endif // ALGORITHM_THREAD_H
