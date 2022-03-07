连接
**要把信号成功连接到槽，它们的参数必须具有相同的顺序和相同的类型，或者允许信号的参数比槽多，槽会自动忽略掉多出来的参数而进行调用。**

### 一个信号可以连接多个槽
使用QObject::connect可以把一个信号连接到多个槽，而当信号发射时，将按声明联系时的顺序依次调用槽。


```
MyStr  a;
 MyStr  b;
 MyStr  c;
//信号连接到两个槽
 QObject::connect(&a,SIGNAL(valueChanged(QString)),&b,SLOT(setValue(QString)));
 QObject::connect(&a,SIGNAL(valueChanged(QString)),&c,SLOT(setValue(QString)));
 a.setValue("this is A");
//依次调用b.setValue()、c.setValue()
```

### 多个信号可以连接同一个槽
### 同样的，可以让多个信号连接到同一个槽上 ，而且其中的每一个信号的发送，都会调用了那个槽。


```
MyStr  a;
 MyStr  b;
 MyStr  c;
//两个信号连接到同一个槽
 QObject::connect(&a,SIGNAL(valueChanged(QString)),&c,SLOT(setValue(QString)));
 QObject::connect(&b,SIGNAL(valueChanged(QString)),&c,SLOT(setValue(QString)));
//下面的操作皆会调用到槽c.setValue()
 a.setValue("this is A");
b.setValue("this is B");
```

### 一个信号可以和另外一个信号相连接
### 当发射第一个信号的时候，也会把第二个信号一个发送出去。


```
MyStr  a;
MyStr  b;
MyStr  c;
//两个信号相连接
QObject::connect(&a,SIGNAL(valueChanged(QString)),&b,SIGNAL(valueChanged(QString)));
//再建立b与c的连接
QObject::connect(&b,SIGNAL(valueChanged(QString)),&c,SLOT(setValue(QString)));
//下面的操作同时发送了信号a.valueChanged与b.valueChanged
a.setValue("this is A");
//从而信号b.valueChanged被槽c.setValue所接收
连接可以被移除
//移除b 与 c之间的连接
QObject::disconnect(&b,SIGNAL(valueChanged(QString)),&c,SLOT(setValue(QString)));
```

实际上当对象被delete时，其关联的所有链接都会失效，QT会自动移除和这个对象的所有链接。

实例：
```c++
void FATIGUE::allConnect()
{
    //接受多个数据，成员拷贝其元素
    connect(rf,&FATIGUE_RAINFLOW::sendIndex,this,&FATIGUE::receiveIndex);
    connect(rf,&FATIGUE_RAINFLOW::sendPeakVally,this,&FATIGUE::receivePeakVally);
    connect(rf,&FATIGUE_RAINFLOW::sendRange,this,&FATIGUE::receiveRange);
    connect(rf,&FATIGUE_RAINFLOW::sendMean,this,&FATIGUE::receiveMean);
    connect(rf,&FATIGUE_RAINFLOW::sendCount,this,&FATIGUE::receiveCount);
    connect(rf,&FATIGUE_RAINFLOW::sendStart,this,&FATIGUE::receiveStart);
    connect(rf,&FATIGUE_RAINFLOW::sendEnd,this,&FATIGUE::receiveEnd);

    connect(rf,&FATIGUE_RAINFLOW::sendDamage,this,&FATIGUE::receiveDamage);

    connect(this,&FATIGUE::sendKValues,rf,&FATIGUE_RAINFLOW::receiveSetKValue);//K值的发送与接收
    connect(this,&FATIGUE::sendUltraStress,rf,&FATIGUE_RAINFLOW::receiveSetUltraStress);//屈服应力的发送与接收

    connect(this,&FATIGUE::sendAll2Table,myTable,&MYTABLE::UpdateTable);//发送所有数据到表格显示

    connect(this,&FATIGUE::sendCsvFileName,readCsv,&DOCSV::receiveFileNameRead);//发送选取的文件名
    connect(readCsv,&DOCSV::sendCsvData,this,&FATIGUE::receiveCsvData);//接受csv读取的数据
}
```
