加上头文件

`#include <QVector>`

```c++
 QVector <double> data {11.0, 44.0, 22.0, 33.0, 10.0,65.0};
     //第一种表示最大值：
     // QVector<double>::iterator max = std::max_element(std::begin(data), std::end(data));
     //第二种表示最大值：
     auto max = std::max_element(std::begin(data), std::end(data));
     //最小值表示：
     auto min = std::min_element(std::begin(data), std::end(data));
     //直接赋值表示
     double biggest = *max;
     double smallest = *min;
     //最大值和最小值的位置的表示方式：
     auto positionmax = std::distance(std::begin(data),max);
     auto positionmin = std::distance(std::begin(data),min);
     int posmax = positionmax;
     int posmin = positionmin;
     
     qDebug()<<"biggest = "<<biggest;
     qDebug()<<"smallest = "<<smallest;
     qDebug()<<"pos ="<<posmax;
     qDebug()<<"posmin = "<<posmin;
```