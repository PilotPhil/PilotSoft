## 1. scipy中的weibull 及 其累计分布函数的逆函数

```python
import scipy as sp
cd=sp.stats.exponweib.cdf(x,n,k)
iss=sp.stats.exponweib.ppf(x,n,k) # 百分位函数（累计分布函数的逆函数）
```

## 2. 空数组

```python
used=np.asarray([],dtype=int)  # 被使用过的点
```

## 3. 禁用警告

```python
import warnings
warnings.filterwarnings("ignore")
```

## 4. 开n次方根

```python
pow(a, 1/n)
```

## 5.梯形法积分  [trapz](https://docs.scipy.org/doc/scipy/reference/generated/scipy.integrate.trapz.html?highlight=trapz#scipy.integrate.trapz)

```python
scipy.integrate.trapz(y, x=None, dx=1.0, axis=- 1)
```

## 6.matplotlib在图像中添加文字

```python
import matplotlib.pyplot as plt

plt.plot([0, 2], [0, 2])
plt.text(0.5, 1, 'put some text')
plt.show()
```

## 7.numpy求和

```python
numpy.sum(a, axis=None, dtype=None, out=None, keepdims=, initial=)

#对特定的轴求和
x.sum(axis=0)

#对多个轴求和
x.sum(axis=(1,2))
```

## 8.matplotlib画图系列之设置坐标轴（精度、范围，标签，中文字符显示）

```python
 
#导入包
import matplotlib.pyplot as plt
import numpy as np
#支持中文显示
from pylab import *
mpl.rcParams['font.sans-serif'] = ['SimHei']
 
#创建数据
x = np.linspace(-5, 5, 100)
y1 = np.sin(x)
y2 = np.cos(x)
 
#创建figure窗口
plt.figure(num=3, figsize=(8, 5))
#画曲线1
plt.plot(x, y1)
#画曲线2
plt.plot(x, y2, color='blue', linewidth=5.0, linestyle='--')
#设置坐标轴范围
plt.xlim((-5, 5))
plt.ylim((-2, 2))
#设置坐标轴名称
plt.xlabel('xxxxxxxxxxx')
plt.ylabel('yyyyyyyyyyy')
#设置坐标轴刻度
my_x_ticks = np.arange(-5, 5, 0.5)
my_y_ticks = np.arange(-2, 2, 0.3)
plt.xticks(my_x_ticks)
plt.yticks(my_y_ticks)
 
#显示出所有设置
plt.show()
```

## 9.numpy.ndarray 交换多维数组（矩阵）的行/列

```python
# 交换第 0 行和第 2 行：
 P[[0, 2], :] = P[[2, 0], :]
```

## 10.numpy中二维数组按照某列、某行排序

```python
data = data[data[:,2].argsort()] #按照第3列对行排序
```

