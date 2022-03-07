#ifndef RF_THREAD_H
#define RF_THREAD_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include <QPointF>
#include <QThread>

class RF_Thread : public QObject
{
    Q_OBJECT
public:
    explicit RF_Thread(QObject *parent = 0);
    ~RF_Thread();

    //1.数据压缩=去除连续相等值+剔除非峰谷点
    void DataZip(QVector<qreal>*);

    //2.载荷历程调整
    void PeriodAdjust(QVector<qreal>*);

    //3.计数
    void Point3Count(QVector<qreal>*);//三点计数法
    bool Point3Comp(qreal a,qreal b,qreal c);//三点计数法循环判断
    void Point4Count(QVector<qreal>*);//四点计数法
    bool Point4Comp(qreal a, qreal b, qreal c, qreal d);//四点计数法循环判断函数



signals:
    void dataOK(QVector<qreal> *);//为雨流计数法准备的数据
    void RF_Result(QVector<QPointF>);//信号 发送雨流计数法计数结果
    void RF_AMP(QVector<qreal> *);//幅值
    void RF_AVG(QVector<qreal> *);//均值
    void RF_AMP_AVG(QVector<qreal> *,QVector<qreal> *);//幅值、均值
    void modifiedStress(QVector<qreal> *);//经过平均应力修正的应力


public slots:
    void setLoadNum(int num);//设置雨流计数法一次载入点个数
    void PrepareData(qreal INP);//准备数据
    void RainFlow(QVector<qreal>*);//4.雨流计数法总成
    void setUltraStress(int UStress);//设置极限应力
    void StressModify(QVector<qreal> *,QVector<qreal> *);//平均应力修正

private:
    QVector<qreal> *dataForRF;
    int num;//设定雨流计数法一次载入的数据点个数
    int ultraStress;//极限应力

};

#endif // RF_THREAD_H
