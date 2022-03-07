## 0.流程
```
graph LR
   应力 --> id1{计数n个}
   id1{计数n个} --> 应力序列
   应力序列 --> 剔除连续重复元素
   剔除连续重复元素 --> 剔除非峰谷点
   剔除非峰谷点 --> 载荷历程调整
   载荷历程调整 --> 平均应力修正
   平均应力修正 --> 应力范围
```

```
graph LR
    应力范围 --> 最大循环次数
    选取S-N曲线 --> 最大循环次数
    最大循环次数 --> 损伤度
    
```


## 1.雨流计数法入口槽函数
```c++
void Algorithm_Thread::Algorithm_Thread_Enter(qreal INP)
{
    Volt2Strain(INP);//电压转应变
    Strain2Stress();//应变转应力

    //构成数据队列，数量足够了就进行雨流计数法-应力修正-损伤度计算
    if(dataForRF->count()<loadNum)
    {
        dataForRF->append(stress);
    }
    else
    {
        DataZip(dataForRF);//数据压缩
        PeriodAdjust(dataForRF);//载荷历程调整
        Point4Count(dataForRF);//四点计数
        StressModify();//平均应力修正
        DamageCompute();//计算损伤度

        dataForRF->clear();//清理
    }
}
```

## 2.设置相关参数
```c++
void Algorithm_Thread::setAlogorithmParam(QList<qreal> all)
{
    this->V2S=all.at(0);
    this->loadNum=all.at(1);
    this->yang=all.at(2);
    this->ultraStress=all.at(3);
    this->S_N=all.at(4);
}
```

## 3.电压转化为应变
```c++
void Algorithm_Thread::Volt2Strain(qreal volt)//电压转化为应变
{
    strain=volt*V2S;
}
```

## 4.应变转化为应力
```c++
void Algorithm_Thread::Strain2Stress()//应变转化为应力
{
    stress=strain*yang*1000;//转化为应力
    emit sendStress(stress);//发送应力
}
```

## 5.平均应力修正
```
void Algorithm_Thread::StressModify()
{
    MStress->clear();
    for(int i=0;i<AMP->count();i++)
    {
        MStress->append((2*ultraStress*AMP->at(i))/(ultraStress-AVG->at(i)));
    }
}
```

## 6.损伤度计算
```c++
void Algorithm_Thread::DamageCompute()
{
    qreal temp;
    Damage->clear();
    ultraS->clear();

    for(int i=0;i<MStress->count();i++)
    {
        temp=(log(S_N)/log(10))-3*(log(MStress->at(i))/log(10));
        temp=pow(10,temp);
        //temp=1/temp;
        Damage->append(temp);
        ultraS->append(ultraStress);
    }
    qDebug()<<"damage"<<*Damage;

    emit sendAlgorithmRes(AMP,AVG,ultraS,MStress,Damage);//发送算法所有结果
    emit sendAMP(AMP);
}
```

## 7.数据压缩
```c++
void Algorithm_Thread::DataZip(QVector<qreal> *INP)
{
    QMutableVectorIterator<qreal> index(*INP);//迭代器
    qreal i,j,k;//暂存
    qreal a,b;

    /*------------------NO SAME------------------*/
    index.toFront();//迭代器移到最前面（元素0的前面）
    index.next();
    while(index.hasNext())//
    {
        a=index.peekPrevious();
        b=index.next();
        if(a==b)
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
```

## 8.载荷历程调整
```c++
void Algorithm_Thread::PeriodAdjust(QVector<qreal> *INP)
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
```

## 9.四点法
```c++
//四点法提取循环
void Algorithm_Thread::Point4Count(QVector<qreal> *INP)
{
    AMP->clear();
    AVG->clear();

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
        i=0;
        j=1;
    }

    qDebug()<<"计数: \t\t"<<*INP;
    qDebug()<<"均值: \t\t"<<*AVG;
    qDebug()<<"幅值: \t\t"<<*AMP;
}

//四点法循环判断条件
bool Algorithm_Thread::Point4Comp(qreal a, qreal b, qreal c, qreal d)
{
    qreal temp1=abs(a-b);
    qreal temp2=abs(b-c);
    qreal temp3=abs(c-d);

    if(temp1>=temp2&&temp2<=temp3)
        return true;
    else
        return false;
}
```