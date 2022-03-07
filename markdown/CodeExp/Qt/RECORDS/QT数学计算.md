包含头文件
```c++
#include <qmath.h>
```



如求log4^3，Qt中不存在以4为底的log函数，可用logx(y)=ln(y)/ln(x)来代替
`double tem=log(3)/log(4)`


其他常用
```c++
qreal qCos(qreal v)  qreal qAcos(qreal v) //余弦、反余弦
qreal qSin(qreal v)  qreal qAsin(qreal v)  //正弦、反正弦
qreal qTan(qreal v) qqreal qAtan(qreal v) //tan函数，arctan函数 
real qAtan2(qreal y, qreal x) //求一个坐标点的反正切函数
int qCeil(qreal v) //返回大于或者等于指定表达式的最小整数
qreal qFabs(qreal v) //求浮点数x的绝对值
int qFloor(qreal v) //其功能是“向下取整”，或者说“向下舍入”，即取不大于x的最大整数（与“四舍五入”不同，下取整是直接去掉小数部分）
qreal qLn(qreal v) qqreal qExp(qreal v)//自然对数以及相反值
qreal qPow(qreal x, qreal y) //计算x的y次幂
qreal Sqrt(qreal v) //平方根计算
const T &qMax(const T &a, const T &b)//返回最大值
const T &qMin(const T &a, const T &b)//返回最小值
T qAbs(const T &t)//返回絕對值
const T &qBound(const T &min, const T &val, const T &max)//返回极限不超過 min , max 的值 qBound(2,10,6)
int qRound(double d)//四舍五入
bool qFuzzyCompare(qfloat16 p1, qfloat16 p2)//Compares the floating point value p1 and p2 and returns true if they are considered equal, otherwise false
int qrand()//This function is obsolete(过时的). It is provided to keep old source code working. We strongly advise against using it in new code.
void qsrand(uint seed)//This function is obsolete. It is provided to keep old source code working. We strongly advise against using it in new code.

```
