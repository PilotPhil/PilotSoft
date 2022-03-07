## 1.BUG-坐标轴和数据不对应、密集的散点图无法显示等
数据系列中的点（4，10）在坐标系中的坐标不是（4，10）

原因在于，轴和数据系列没有连接。

一个图表QChart中可以有多个数据系列（也即一个图表中可以有多条曲线，甚至可以同时包含散点图和折线），每个数据系列都必须与两个坐标轴相连接。

连接方法有两种：

（1）在给图表设置轴时，顺便与数据系列相连
lineChart->setAxisX(axisX, lineseries);//把轴添加到图表中,同时把数据系列与这个轴相连
lineChart->setAxisY(axisY, lineseries);//
（2）单独的语句把数据系列和轴相连（只有series已经被添加进chart之后，再执行attachAxis才能有效）
lineseries->attachAxis(axisX);
lineseries->attachAxis(axisY);
实例：

```c++
void MYCHART::myAddSeries(QLineSeries *series)
{
    chart->addSeries(series);//先添加series

    series->attachAxis(axisX);//再设置坐标轴
    series->attachAxis(axisY);
}
```


## 2.BUG-No rule to make target needed by
打开工程的pro文件

```
SOURCES += \
        main.cpp \
        fatigue.cpp \
        fatigue_rainflow.cpp \
        mychart.cpp\
        mytable.cpp \
        docsv.cpp

HEADERS += \
        fatigue.h \
        fatigue_rainflow.h \
        mychart.h\
        mytable.h \
        docsv.h

FORMS += \
        fatigue.ui \
        mychart.ui\
        mytable.ui
```
        
查看是否有已删除文件，但是pro文件中依然添加的文件，有就删除
