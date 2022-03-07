#include "RainFlowCount.h"

RainFlowCount::RainFlowCount(QObject *parent) : QObject(parent)
{
    yang=0.001;//杨氏模数
    UStress=235;//极限应力
    SN=5.8E12;//SN曲线

    AMP=new QVector<qreal>;
    AVG=new QVector<qreal>;
    MStress=new QVector<qreal>;
    Damage=new QVector<qreal>;
}

//-1.设置参数
void RainFlowCount::SetParams(qreal yang, qreal UStress, qreal SN)
{
    this->yang=yang;
    this->UStress=UStress;
    this->SN=SN;
}

//0.集成
void RainFlowCount::RunRainFlow(QVector<qreal> INP)
{
    RemoveContinuousDuplicateData(INP);
    ExtractPeakValleyPoints(INP);
    LoadHistoryAdjustment(INP);
    FourPointsCounting(INP);
    MeanStressCorrection();
    DamageCalculation();
}

//1.去除连续重复数据
void RainFlowCount::RemoveContinuousDuplicateData(QVector<qreal> &dataSequence)
{
    QMutableVectorIterator<qreal> index(dataSequence);//迭代器
    qreal a,b;

    index.toFront();//迭代器移到最前面（元素0的前面）
    index.next();
    while(index.hasNext())//
    {
        a=index.peekPrevious();
        b=index.next();
        if(a==b)
            index.remove();
    }
    qDebug()<<"去除连续重复数据后："<<dataSequence;
}

//2.提取峰谷点
void RainFlowCount::ExtractPeakValleyPoints(QVector<qreal> &dataSequence)
{
    QMutableVectorIterator<qreal> index(dataSequence);//迭代器
    qreal i,j,k;//暂存

    /*----------------提取峰谷数据点-----------------*/
    index.toFront();
    index.next();
    index.next();//迭代器前面有两个元素
    while (index.hasNext())
    {
        k=index.peekNext();//
        j=index.previous();
        i=index.peekPrevious();

        if((i>j&&j>k)||(i<j&&j<k))//如果j非峰非谷
        {
            index.remove();//去掉j元素
            index.next();//向后位移一个，确保下一次循环时，迭代器前面有两个元素
        }
        else
        {
            index.next();
            index.next();//向后位移两个，确保下一次循环时，迭代器前面有两个元素
        }
    }
    qDebug()<<"提取峰谷："<<dataSequence;
}

//3.载荷历程调整
void RainFlowCount::LoadHistoryAdjustment(QVector<qreal> &INP)
{
    /*----------------PERIOD ADJUST-----------------*/
    qreal temp;
    QVector<qreal> tempVector;

    //为确保首尾同为峰，或同为谷,峰谷点总数需为奇数
    if(INP.count()%2==0)//总点数为偶数
    {
        INP.remove(INP.count()-1);//抹去最后一个点
    }

    //现在总点数为奇数了,首尾取同值
    if(INP.at(0)<INP.at(1))//首尾为谷-【0】<【1】
    {
        temp=INP.at(0)<INP.at(INP.count()-1)?INP.at(0):INP.at(INP.count()-1);
        INP.replace(0,temp);
        INP.replace(INP.count()-1,temp);
    }
    else//首尾为峰-【0】>【1】
    {
        temp=INP.at(0)>INP.at(INP.count()-1)?INP.at(0):INP.at(INP.count()-1);
        INP.replace(0,temp);
        INP.replace(INP.count()-1,temp);
    }

    //找到INP中绝对值最大的值
    temp=abs(INP.at(0));//保存元素0的绝对值
    int where=0;//保存绝对值最小的元素的下标
    for(int i=0;i<INP.count();i++)
    {
        if(temp<abs(INP.at(i)))
        {
            where=i;
            temp=abs(INP.at(i));
        }
    }
    qDebug()<<"最小值在："<<where<<"并且最小值为:"<<INP.at(where);

    //从绝对值最大点处交换
    tempVector.clear();
    for(int i=0;i<where+1;i++)//将前半段保存
    {
        tempVector.append(INP.at(i));
    }

    for(int i=0;i<INP.count()-where;i++)
    {
        INP.replace(i,INP.at(i+where));//c-i-1+i=c-1
    }

    for(int i=INP.count()-where,j=1;i<INP.count();i++,j++)
    {
        INP.replace(i,tempVector.at(j));
    }

    qDebug()<<"载荷历程调整："<<'\t'<<INP;

}

//4.四点法计数
void RainFlowCount::FourPointsCounting(QVector<qreal> &INP)
{
    //四点法判断条件
    auto judge=[](qreal a,qreal b,qreal c,qreal d)->bool
    {
        if((abs(a-b)>=abs(b-c))&&(abs(b-c)<=abs(c-d)))
            return true;
        else
            return false;
    };

    AMP->clear();//幅值清空
    AVG->clear();//均值清空

    int i=0,j=1;
    while(INP.count()!=3)
    {
        while (j+3<=INP.count())
        {
            if(judge(INP.at(i),INP.at(j),INP.at(j+1),INP.at(j+2))==true)
            {
                AMP->append(0.5*abs(INP.at(j)-INP.at(j+1)));
                AVG->append(0.5*(INP.at(j)+INP.at(j+1)));

                INP.remove(j);
                INP.remove(j);
                qDebug()<<"过程：\t\t"<<INP;
            }
            else
            {
                i+=1;
                j+=1;
            }
        }
        i=0;
        j=1;
    }

    qDebug()<<"计数: \t\t"<<INP;
    qDebug()<<"均值: \t\t"<<*AVG;
    qDebug()<<"幅值: \t\t"<<*AMP;
}

//5.平均应力修正
void RainFlowCount::MeanStressCorrection()
{
    MStress->clear();
    for(int i=0;i<AMP->count();i++)
    {
        MStress->append((2*UStress*AMP->at(i))/(UStress-AVG->at(i)));
    }
}

//6.损伤度计算
void RainFlowCount::DamageCalculation()
{
    qreal temp;
    Damage->clear();

    for(int i=0;i<MStress->count();i++)
    {
        temp=(log(SN)/log(10))-3*(log(MStress->at(i))/log(10));
        temp=pow(10,temp);
        temp=1/temp;
        Damage->append(temp);
    }

    qDebug()<<"损伤度"<<'\t'<<'\t'<<*Damage;
}

//7.发送结果
void RainFlowCount::EmitResults()
{
    EmitParams(yang,UStress,SN);
    EmitAMP(*AMP);
    EmitAVG(*AVG);
    EmitMStress(*MStress);
    EmitDamage(*Damage);
}










