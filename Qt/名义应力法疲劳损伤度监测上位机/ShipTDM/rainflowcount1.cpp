#include "rainflowcount1.h"
#include "ui_rainflowcount.h"

RainFlowCount::RainFlowCount(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RainFlowCount)
{
    ui->setupUi(this);
    tempVector=new QVector<qreal>;
}

RainFlowCount::~RainFlowCount()
{
    delete tempVector;
    delete ui;
}

void RainFlowCount::RF(QVector<qreal> *inp)
{
    NoSame(inp);
    PeakVally(inp);
    PeriodAdjust(inp);
    qDebug()<<"子线程号"<<QThread::currentThread();

}

//去除inp中重复连续数据,保留一个
//去除连续重复的数
void RainFlowCount::NoSame(QVector<qreal> *inp)
{
    qint8 all,index=0;;
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
void RainFlowCount::PeakVally(QVector<qreal> *inp)
{
    uint8_t all=inp->count()-1,index=0;
    while(all!=index+1)
    {
        if((inp->at(index)>inp->at(index+1)&&inp->at(index+1)>inp->at(index+2))||(inp->at(index)<inp->at(index+1)&&inp->at(index+1)<inp->at(index+2)))
        {
            inp->remove(index+1);
        }
        else
        {
            index++;
        }
        all=inp->count()-1;
    }
}

//载荷历程调整
void RainFlowCount::PeriodAdjust(QVector<qreal> *inp)
{
    if(inp->count()%2==0)//总点数为偶数
    {
        //qDebug()<<"雨流计数法中，峰谷点数为偶数";
        inp->remove(inp->count()-1);//抹去最后一个点
    }

    //现在总点数为奇数了
    //首尾取同值
    qreal temp;
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
    for(uint16_t i=0;i<index+1;i++)//将前半段保存
        tempVector->append(inp->at(i));

    for(uint16_t i=0;i<inp->count()-index;i++)
        inp->replace(i,inp->at(i+index));//c-i-1+i=c-1

    for(uint16_t i=inp->count()-index,j=1;i<inp->count();i++,j++)
        inp->replace(i,tempVector->at(j));

}
