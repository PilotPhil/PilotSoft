#include "rainflowga.h"

RainFlowGA::RainFlowGA(QObject *parent) : QObject(parent)
{
    tempVector=new QVector<qreal>;
    seriesData_RF=new QVector<qreal>;
}

RainFlowGA::~RainFlowGA()
{
    delete tempVector;
}

//为雨流计数法准备num个数据组
void RainFlowGA::dataForRF_Ready(qreal data,int num)//运行时间长后，会造成延迟，可能出现在prepareData()里
{

    qDebug()<<"子线程号："<<QThread::currentThread();
    if(seriesData_RF->count()<num)
    {
        seriesData_RF->append(data);//增加数据点
       // qDebug()<<data;
    }
    else
    {
        //qDebug()<<*seriesData_RF;
        emit dataForRF_Prepared(seriesData_RF);
        seriesData_RF->clear();
    }
}


void RainFlowGA::RF(QVector<qreal> *inp)
{
    //QVector<qreal> *tempData=new QVector<qreal>;
    QVector<qreal> *ID=new QVector<qreal>;
    QVector<qreal> *ID2=new QVector<qreal>;
    QVector<qreal> *ID3=new QVector<qreal>;
    uint16_t index=0;

    for(index=0;index<inp->count()-1;index++)//一阶差分
    {
        ID->append(inp->at(index+1)-inp->at(index));
    }
    qDebug()<<"ID:"<<*ID;//ok

    for(index=0;index<ID->count();index++)//取符号运算
    {
        if(ID->at(index)>0)
            ID->replace(index,1);
        else if(ID->at(index)<0)
            ID->replace(index,-1);
        else
        {}
    }
    qDebug()<<"IDD:"<<*ID;//ok

    for(index=ID->count()-2;index>0;index--)//反向遍历
    {
        if(ID->at(index)==0)
        {
            if(ID->at(index+1)>=0)
                ID->replace(index,1);
            else
                ID->replace(index,-1);
        }

        //qDebug()<<index;
    }
    qDebug()<<"IDDD:"<<*ID;//ok

    for(index=0;index<ID->count()-1;index++)
    {
        ID2->append(ID->at(index+1)-ID->at(index));
    }
    ID2->prepend(1);
    ID2->remove(ID2->count()-1);
    ID2->replace(ID2->count()-1,1);
    qDebug()<<"ID2: "<<*ID2;

    for(index=0;index<ID2->count();index++)
    {
        if(ID2->at(index)!=0)
        {
            ID3->append(inp->at(index));
        }
    }

    qDebug()<<"ID3:"<<*ID3;

    ID->clear();
    ID2->clear();
    ID3->clear();

    delete ID;
    delete ID2;
    delete ID3;
}

//去除inp中重复连续数据,保留一个
//去除连续重复的数
void RainFlowGA::NoSame(QVector<qreal> *inp)
{
    qint8 all,index=0;
    while(all!=index)
    {
        if(inp->at(index)==inp->at(index+1))
            inp->remove(index);
        else
            index++;
        all=inp->count()-1;
        //qDebug()<<"index="<<index<<",all="<<all;
    }
}

//峰谷提取
void RainFlowGA::PeakVally(QVector<qreal> *inp)
{
    uint8_t all,index=0;
    while(all!=index+1)
    {
        if((inp->at(index)>inp->at(index+1)&&inp->at(index+1)>inp->at(index+2))||(inp->at(index)<inp->at(index+1)&&inp->at(index+1)<inp->at(index+2)))
        {
            inp->remove(index+1);
        }
        else if(inp->count()-1-index==1)
        {
            break;
        }
        else
        {
            index++;
        }
        all=inp->count()-1;
    }
}

//载荷历程调整
void RainFlowGA::PeriodAdjust(QVector<qreal> *inp)
{
    if(inp->count()%2==0)//总点数为偶数
    {
        //qDebug()<<"雨流计数法中，峰谷点数为偶数";
        inp->remove(inp->count()-1);//抹去最后一个点
    }

    //现在总点数为奇数了
    //首尾取同值
    if(inp->at(0)<inp->at(1))//首尾为谷
    {
        temp=inp->at(0)<inp->at(inp->count()-1)?inp->at(0):inp->at(inp->count()-1);
        inp->replace(0,temp);
        inp->replace(inp->count()-1,temp);
    }
    else
    {
        temp=inp->at(0)>inp->at(inp->count()-1)?inp->at(0):inp->at(inp->count()-1);
        inp->replace(0,temp);
        inp->replace(inp->count()-1,temp);
    }

    temp=abs(inp->at(0));
    uint16_t index=0;
    for(uint16_t i=0;i<inp->count()-1;i++)
    {
        if(temp>=abs(inp->at(i)))
        {
            index=i;
            temp=abs(inp->at(i));
        }
    }

    qDebug()<<"min at: "<<index<<"and value is:"<<inp->at(index);

    //交换
    tempVector->clear();
    for(uint16_t i=0;i<index+1;i++)//将前半段保存
        tempVector->append(inp->at(i));

    qDebug()<<"aaa";

    for(uint16_t i=0;i<inp->count()-index;i++)
        inp->replace(i,inp->at(i+index));//c-i-1+i=c-1

    qDebug()<<"bbb";

    for(uint16_t i=inp->count()-index,j=1;i<inp->count();i++,j++)
        inp->replace(i,tempVector->at(j));

    qDebug()<<"ccc";

}
