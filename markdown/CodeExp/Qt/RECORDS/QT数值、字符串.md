## 1.格式化字符串
1. 使用`QString::sprintf()`
```c++
QString str;
QString name="Tom";
int age=18;
str=str.sprintf("my name is %s,and my age is %d",name,age);
qDebug()<<str;
```
2. 使用`QString::arg()` **首选**
```c++
QString s1="my",s2="name""",s3="is",s4="Tom,all;
all=QString("%1 %2 %3 %4").arg(s1,s2,s3,s4);
qDebug()<<all;
```
### 占位符

转换符|说明
--- |   ---
%s  |   字符串
%c  |   字符
%b  |   布尔
%d  |   十进制
%x  |   十六进制
%o  |   八进制
%f  |   浮点数
%a  |   十六进制浮点数
%e  |   指数类型
%g  |   通用浮点类型
%h  |   散列码
%n  |   换行符
%tx |   日期与时间


## 2.字符串常用函数

函数名|功能
---|---
append()|尾部增加
prepend()|首部增加
toUpper()|转为大写
toLower()|转为小写
count()、size()、length()|字符个数（汉字算一个字符）
trimmed()|去掉字符串首尾空格
simplified()|去掉首尾空格以及中间连续的空格
indexOf()|查找出现字符的所有位置
lastIndexOf()|某字符串最后出现的位置
contains()|是否包含
endWith()|以-结尾？
startWith()|以-开头？
left()|从左边截取？个字符串
rignt()|从右边截取？个字符串
section()|以？作为分割符分割字符串

