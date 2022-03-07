#ifndef RAINFLOWCOUNT_H
#define RAINFLOWCOUNT_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include <QThread>
#include <QtCore/QtMath>

class RainFlowCount : public QObject
{
    Q_OBJECT
public:
    explicit RainFlowCount(QObject *parent = nullptr);

    /*-----------------------------------------------------*/
    //-1.设置参数
    void SetParams(qreal,qreal,qreal);

    //0.集成
    void RunRainFlow(QVector<qreal>);

    //1.去除连续重复数据
    void RemoveContinuousDuplicateData(QVector<qreal>&);

    //2.提取峰谷点
    void ExtractPeakValleyPoints(QVector<qreal>&);

    //3.载荷历程调整
    void LoadHistoryAdjustment(QVector<qreal>&);

    //4.四点计数法
    void FourPointsCounting(QVector<qreal>&);

    //5.平均应力修正
    void MeanStressCorrection();

    //6.损伤度计算
    void DamageCalculation();

    //7.发送结果
    void EmitResults();

private:
    qreal yang;//杨氏模数
    qreal UStress;//极限应力
    qreal SN;//SN曲线

    QVector<qreal> *AMP;//幅值
    QVector<qreal> *AVG;//均值
    QVector<qreal> *MStress;//平均应力修正后的应力范围
    QVector<qreal> *Damage;//损伤度

signals:
    void EmitParams(qreal,qreal,qreal);
    void EmitAMP(QVector<qreal>);
    void EmitAVG(QVector<qreal>);
    void EmitMStress(QVector<qreal>);
    void EmitDamage(QVector<qreal>);
};

#endif // ALGORITHM_THREAD_H
