#include "rf_thread.h"

RF_Thread::RF_Thread(QObject *parent) : QObject(parent)
{
    dataForRF=new QVector<qreal>;

    num=100;//预先设定载入点个数为100

    //数据准备好就发送给雨流计数法总成槽函数
    connect(this,SIGNAL(dataOK(QVector<qreal>*)),this,SLOT(RainFlow(QVector<qreal>*)));

    //幅值均值发送给平均应力修正
    connect(this,SIGNAL(RF_AMP_AVG(QVector<qreal>*,QVector<qreal>*)),this,SLOT(StressModify(QVector<qreal>*,QVector<qreal>*)));
}

RF_Thread::~RF_Thread()
{
    delete dataForRF;
}

//设置雨流计数法一次计数载入数据点个数
void RF_Thread::setLoadNum(int num)
{
    this->num=num;
}

void RF_Thread::setUltraStress(int UStress)
{
    this->ultraStress=UStress;//设置极限应力
}

//为雨流计数法准备数据流
void RF_Thread::PrepareData(qreal INP)
{
    if(dataForRF->count()<num)
    {
        dataForRF->append(INP);
    }
    else if(dataForRF->count()==num)
    {
        emit dataOK(dataForRF);
        dataForRF->clear();
    }
    else
    {}
}

//1.数据压缩
void RF_Thread::DataZip(QVector<qreal> *INP)
{
    QMutableVectorIterator<qreal> index(*INP);//迭代器
    qreal i,j,k;//暂存

    /*------------------NO SAME------------------*/
    index.toFront();//迭代器移到最前面（元素0的前面）
    index.next();
    while(index.hasNext())//
    {
        if(index.peekPrevious()==index.next())
            index.remove();
    }
    qDebug()<<"去除连续重复数据："<<*INP;

    /*----------------PEAK VALLY-----------------*/
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
    qDebug()<<"提取峰谷："<<*INP;
}

//2.载荷历程调整
void RF_Thread::PeriodAdjust(QVector<qreal> *INP)
{
    /*----------------PERIOD ADJUST-----------------*/
    qreal *temp=new qreal;
    QVector<qreal> *tempVector=new QVector<qreal>;

    //为确保首尾同为峰，或同为谷,峰谷点总数需为奇数
    if(INP->count()%2==0)//总点数为偶数
    {
        INP->remove(INP->count()-1);//抹去最后一个点
    }

    //现在总点数为奇数了,首尾取同值
    if(INP->at(0)<INP->at(1))//首尾为谷-【0】<【1】
    {
        *temp=INP->at(0)<INP->at(INP->count()-1)?INP->at(0):INP->at(INP->count()-1);
        INP->replace(0,*temp);
        INP->replace(INP->count()-1,*temp);
    }
    else//首尾为峰-【0】>【1】
    {
        *temp=INP->at(0)>INP->at(INP->count()-1)?INP->at(0):INP->at(INP->count()-1);
        INP->replace(0,*temp);
        INP->replace(INP->count()-1,*temp);
    }

    //找到INP中绝对值最大的值
    *temp=abs(INP->at(0));//保存元素0的绝对值
    int where=0;//保存绝对值最小的元素的下标
    for(int i=0;i<INP->count();i++)
    {
        if(*temp<abs(INP->at(i)))
        {
            where=i;
            *temp=abs(INP->at(i));
        }
    }
    qDebug()<<"min at: "<<where<<"and value is:"<<INP->at(where);

    //从绝对值最大点处交换
    tempVector->clear();
    for(int i=0;i<where+1;i++)//将前半段保存
    {
        tempVector->append(INP->at(i));
    }

    for(int i=0;i<INP->count()-where;i++)
    {
        INP->replace(i,INP->at(i+where));//c-i-1+i=c-1
    }

    for(int i=INP->count()-where,j=1;i<INP->count();i++,j++)
    {
        INP->replace(i,tempVector->at(j));
    }

    qDebug()<<"载荷历程调整："<<*INP;

    //释放
    delete temp;
    delete tempVector;
}

void RF_Thread::Point3Count(QVector<qreal> *INP)
{
    QVector<qreal> *AMP=new QVector<qreal>;
    QVector<qreal> *AVG=new QVector<qreal>;

    int i=0,j=1;
    while(INP->count()!=2)
    {
        while(j+2<=INP->count())
        {
            if(Point3Comp(INP->at(i),INP->at(j),INP->at(j+1))==true)
            {
                AMP->append(0.5*abs(INP->at(i)-INP->at(j)));
                AVG->append(0.5*(INP->at(i)+INP->at(j)));

                INP->remove(i);
                INP->remove(i);
            }
            else
            {
                i++;
                j++;
            }
        }
        i=0;j=1;
    }

    emit RF_AMP(AMP);
    emit RF_AVG(AVG);

    delete AVG;
    delete AMP;
}

//三点法循环判断条件
bool RF_Thread::Point3Comp(qreal a, qreal b, qreal c)
{
    qreal temp1=abs(a-b);
    qreal temp2=abs(b-c);
    if(temp1<=temp2)
        return true;
    else
        return false;
}

//四点计数法
void RF_Thread::Point4Count(QVector<qreal> *INP)
{
    QVector<qreal> *AMP=new QVector<qreal>;
    QVector<qreal> *AVG=new QVector<qreal>;

    int i=0,j=1;

    while(INP->count()!=3)
    {

        while (j+3<=INP->count())
        {
            if(Point4Comp(INP->at(i),INP->at(j),INP->at(j+1),INP->at(j+2))==true)
            {
                AMP->append(0.5*abs(INP->at(j)-INP->at(j+1)));
                AVG->append(0.5*(INP->at(j)+INP->at(j+1)));

                INP->remove(j);
                INP->remove(j);
                qDebug()<<"过程：\t\t\t"<<*INP;
            }
            else
            {
                i+=1;
                j+=1;
            }
        }
        i=0,j=1;
    }

    emit RF_AMP(AMP);
    emit RF_AVG(AVG);
    emit RF_AMP_AVG(AMP,AVG);

    qDebug()<<"计数: \t\t"<<*INP;
    qDebug()<<"均值: \t\t"<<*AVG;
    qDebug()<<"幅值: \t\t"<<*AMP;

    delete AVG;
    delete AMP;
}

//四点法循环判断条件
bool RF_Thread::Point4Comp(qreal a, qreal b, qreal c, qreal d)
{
    qreal temp1=abs(a-b);
    qreal temp2=abs(b-c);
    qreal temp3=abs(c-d);

    if(temp1>=temp2&&temp2<=temp3)
        return true;
    else
        return false;
}

//4.雨流计数法集成
void RF_Thread::RainFlow(QVector<qreal> *INP)
{
    qDebug()<<"雨流计数法子线程："<<QThread::currentThread();//输出雨流计数法子线程号

    //数据压缩
    DataZip(INP);
    //载荷历程调整
    PeriodAdjust(INP);
    //四点计数
    Point4Count(INP);
}

//5.平均应力修正
void RF_Thread::StressModify(QVector<qreal> *AMP, QVector<qreal> *AVG)
{
    QVector<qreal> *MStress=new QVector<qreal>;

    for(int i=0;i<AMP->count();i++)
    {
        MStress->append((2*ultraStress*AMP->at(i))/(ultraStress-AVG->at(i)));
    }
    emit modifiedStress(MStress);

    delete MStress;
}






