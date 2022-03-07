## 1.array

```python
# array
import numpy as np
a=np.array([1,2,3])
b=np.array([[1,2,3],[4,5,6]]) #二维
c=np.array([1,2,3,4,5,6],dtype=complex) # 复数

# 性质
# ndarray.ndim	秩，即轴的数量或维度的数量
# ndarray.shape	数组的维度，对于矩阵，n 行 m 列
# ndarray.size	数组元素的总个数，相当于 .shape 中 n*m 的值
# ndarray.dtype	ndarray 对象的元素类型
# ndarray.itemsize	ndarray 对象中每个元素的大小，以字节为单位
# ndarray.flags	ndarray 对象的内存信息
# ndarray.real	ndarray元素的实部
# ndarray.imag	ndarray 元素的虚部
# ndarray.data	包含实际数组元素的缓冲区，由于一般通过数组的索引获取元素，所以通常不需要使用这个属性。

b=np.array([[1,2,3],[4,5,6]]) #二维
b.ndim # n=2
b.shape # (2, 3)两行三列
b.size # 总数6
c.size # 6
```

##  2.创建数组

```python
# 创建数组
# 1.numpy.empty 方法用来创建一个指定形状（shape）、数据类型（dtype）且未初始化的数组：
# order：有"C"和"F"两个选项,分别代表，行优先和列优先，在计算机内存中的存储元素的顺序。
numpy.empty(shape, dtype = float, order = 'C')

x=np.empty([2,3],dtype=int,order='C')
# 注意 − 数组元素为随机值，因为它们未初始化。

# 2.numpy.zeros 创建指定大小的数组，数组元素以 0 来填充：
numpy.zeros(shape, dtype = float, order = 'C')

y=np.zeros([3,4],dtype=float)
np.zeros(12) # array([0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.])

# 3.numpy.ones 创建指定形状的数组，数组元素以 1 来填充：
numpy.ones(shape, dtype = None, order = 'C')

# 4.从已有的数组（a）创建数组
numpy.asarray(a, dtype = None, order = None)
# a	任意形式的输入参数，可以是，列表, 列表的元组, 元组, 元组的元组, 元组的列表，多维数组
# dtype	数据类型，可选
# order	可选，有"C"和"F"两个选项,分别代表，行优先和列优先，在计算机内存中的存储元素的顺序。

v=[3,5,8]
B=np.asarray(v) # 将列表转换为 ndarray:

x =  (1,2,3) 
a = np.asarray(x)  # 将元组转换为 ndarray

# 5.从数值范围创建数组
# 5.1 numpy.arange根据 start 与 stop 指定的范围以及 step 设定的步长，生成一个 ndarray。
numpy.arange(start, stop, step, dtype)
# start	起始值，默认为0
# stop	终止值（不包含）不包含重要
# step	步长，默认为1
# dtype	返回ndarray的数据类型，如果没有提供，则会使用输入数据的类型。

a=np.arange(1,100,1) # 1~99
b=np.arange(1,6,dtype=float) # array([1., 2., 3., 4., 5.])
# c=np.arange(7,1) # 不能倒序

# 5.2 numpy.linspace用于创建一个一维数组，数组是一个等差数列构成的
np.linspace(start, stop, num=50, endpoint=True, retstep=False, dtype=None)
# start	序列的起始值
# stop	序列的终止值，如果endpoint为true，该值包含于数列中
# num	要生成的等步长的样本数量，默认为50  其实就是等分数
# endpoint	该值为 true 时，数列中包含stop值，反之不包含，默认是True。
# retstep	如果为 True 时，生成的数组中会显示间距，反之不显示。
# dtype	ndarray 的数据类型

c=np.linspace(1,10,20)
d=np.linspace(10,1,10,dtype=int) # array([10,  9,  8,  7,  6,  5,  4,  3,  2,  1])可以倒序

# 5.3 numpy.logspace 函数用于创建一个于等比数列
np.logspace(start, stop, num=50, endpoint=True, base=10.0, dtype=None)
# start	序列的起始值为：base ** start
# stop	序列的终止值为：base ** stop。如果endpoint为true，该值包含于数列中
# num	要生成的等步长的样本数量，默认为50
# endpoint	该值为 true 时，数列中中包含stop值，反之不包含，默认是True。
# base	对数 log 的底数。
# dtype	ndarray 的数据类型

e=np.logspace(1,8,8,base=2,dtype=int) # array([  2,   4,   8,  16,  32,  64, 128, 256])
```

## 3.切片与索引

```python
a=np.arange(1,10) # array([1, 2, 3, 4, 5, 6, 7, 8, 9])
a[3] # 4 索引从0开始
a[2:] # array([3, 4, 5, 6, 7, 8, 9]) 索引2以后的元素
a[-1] # 9 倒一
a[-2] # 8 倒二
a[2:7:2] # array([3, 5, 7]) 索引2~索引7，间隔为2

s = slice(2,7,2)   # 从索引 2 开始到索引 7 停止，间隔为2
a[s]

b= np.array([[1,2,3],[3,4,5],[4,5,6]])
b[0,:] # array([1, 2, 3]) 第0行
b[0] # array([1, 2, 3]) 第0行
b[:,1] # array([2, 4, 5]) 第2列
b[2,1] # 5 第3行，第2列

# 布尔索引
a=np.arange(1,10) # array([1, 2, 3, 4, 5, 6, 7, 8, 9])
a[a<5] # array([1, 2, 3, 4])

# a>2 且 a<6
a=a[a<6]
a=a[a>2] # array([3, 4, 5])
```

## 4.NumPy 广播(Broadcast)---不重要

广播(Broadcast)是 numpy 对不同形状(shape)的数组进行数值计算的方式， 对数组的算术运算通常在相应的元素上进行。

如果两个数组 a 和 b 形状相同，即满足 **a.shape == b.shape**，那么 a*b 的结果就是 a 与 b 数组对应位相乘。这要求维数相同，且各维度的长度相同。

当运算中的 2 个数组的形状不同时，numpy 将自动触发广播机制。如：

```python
import numpy as np 
 
a = np.array([[ 0, 0, 0],
           [10,10,10],
           [20,20,20],
           [30,30,30]])
b = np.array([1,2,3])
print(a + b)

# 结果为：
[[ 1  2  3]
 [11 12 13]
 [21 22 23]
 [31 32 33]]
```

## 5.迭代数组

NumPy 迭代器对象 numpy.nditer 提供了一种灵活访问一个或者多个数组元素的方式。

迭代器最基本的任务的可以完成对数组元素的访问。

```python
# 1.完成对数组元素的访问
a=np.arange(0,8).reshape(2,4)

for x in np.nditer(a):
    print(x,end=',') # 0,1,2,3,4,5,6,7, 

# 2.转置
a.T # 转置

# 3.修改数组中元素的值？？？？？？？？？？？？？？？？
# nditer 对象有另一个可选参数 op_flags。 默认情况下，nditer 将视待迭代遍历的数组为只读对象（read-only），为了在遍历数组的同时，实现对数组元素值得修改，必须指定 read-write 或者 write-only 的模式。
for x in np.nditer(a, op_flags=['readwrite']): 
    x[...]=2*x 
```

## 6.数组操作

```python
# 1.修改数组形状
# 1.1numpy.reshape 函数可以在不改变数据的条件下修改形状
a=np.arange(0,8).reshape(2,4)

# 1.2numpy.ravel() 展平的数组元素，顺序通常是"C风格"，返回的是数组视图
a.ravel() # array([0, 1, 2, 3, 4, 5, 6, 7])

# 2.翻转数组
# 2.1numpy.transpose 函数用于对换数组的维度
numpy.transpose(arr, axes)
# arr：要操作的数组
# axes：整数列表，对应维度，通常所有维度都会对换。
a.transpose() # 类似于转置
a.T #

# 2.2numpy.swapaxes 函数用于交换数组的两个轴
numpy.swapaxes(arr, axis1, axis2)

# 3连接数组
# 3.1numpy.concatenate 函数用于沿指定轴连接相同形状的两个或多个数组
numpy.concatenate((a1, a2, ...), axis)
# a1, a2, ...：相同类型的数组
# axis：沿着它连接数组的轴，默认为 0

a = np.array([[1,2],[3,4]])
b = np.array([[5,6],[7,8]])
np.concatenate((a,b)              
```

```python
# 4.数组元素的添加与删除
# 4.1numpy.resize 函数返回指定大小的新数组。如果新数组大小大于原始大小，则包含原始数组中的元素的副本。
numpy.resize(arr, shape)
# arr：要修改大小的数组
# shape：返回数组的新形状

# 5.numpy.append 函数在数组的末尾添加值。 追加操作会分配整个数组，并把原来的数组复制到新数组中。 此外，输入数组的维度必须匹配否则将生成ValueError。
# append 函数返回的始终是一个一维数组。
numpy.append(arr, values, axis=None)

a=np.arange(0,8)
a=np.append(a,11)

# 6.numpy.insert 函数在给定索引之**前**，沿给定轴在输入数组中插入值。
# 如果值的类型转换为要插入，则它与输入数组不同。 插入没有原地的，函数会返回一个新数组。 此外，如果未提供轴，则输入数组会被展开。
numpy.insert(arr, obj, values, axis)
# arr：输入数组
# obj：在其之前插入值的索引
# values：要插入的值
# axis：沿着它插入的轴，如果未提供，则输入数组会被展开

a=np.arange(0,8)
a=np.insert(a,3,99) # array([ 0,  1,  2, 99,  3,  4,  5,  6,  7])

# 7.numpy.delete 函数返回从输入数组中删除指定子数组的新数组。 与 insert() 函数的情况一样，如果未提供轴参数，则输入数组将展开。
Numpy.delete(arr, obj, axis)
# arr：输入数组
# obj：可以被切片，整数或者整数数组，表明要从输入数组删除的子数组
# axis：沿着它删除给定子数组的轴，如果未提供，则输入数组会被展开

a=np.arange(0,8)
a=np.delete(a,4) # array([0, 1, 2, 3, 5, 6, 7])

# 8.numpy.unique 函数用于去除数组中的重复元素。
numpy.unique(arr, return_index, return_inverse, return_counts)
# arr：输入数组，如果不是一维数组则会展开
# return_index：如果为true，返回新列表元素在旧列表中的位置（下标），并以列表形式储
# return_inverse：如果为true，返回旧列表元素在新列表中的位置（下标），并以列表形式储
# return_counts：如果为true，返回去重数组中的元素在原数组中的出现次数

a=np.arange(0,8)
a=np.append(a,7)
a=np.unique(a)
```

## 7.NumPy 数学函数

```python
# 1.三角函数
sin()
cos()
tan()
arcsin()
arccos()
arctan()

numpy.degrees() # 函数将弧度转换为角度。

# 2.舍入函数
# 2.1numpy.around() 函数返回指定数字的四舍五入值。
numpy.around(a,decimals)
# a: 数组
# decimals: 舍入的小数位数。 默认值为0。 如果为负，整数将四舍五入到小数点左侧的位置

np.around(12.55,1) # 12.6

# 2.2numpy.floor() 返回小于或者等于指定表达式的最大整数，即向下取整。
np.floor(12.88) # 12

# 2.3numpy.ceil() 返回大于或者等于指定表达式的最小整数，即向上取整。
np.ceil(13.11) # 14
```

## 8.NumPy 统计函数

```python
# 1.numpy.amin() 用于计算数组中的元素沿指定轴的最小值。
#   numpy.amax() 用于计算数组中的元素沿指定轴的最大值。

a = np.array([[3,7,5],[8,4,3],[2,4,9]]) 
np.amin(a,1) # [3 3 2]
np.amin(a,0) # [2 4 3]

# 2.numpy.ptp()函数计算数组中元素最大值与最小值的差（最大值 - 最小值）。
a=np.arange(0,8)
np.ptp(a) # 7

# 3.numpy.percentile()百分位数是统计中使用的度量，表示小于这个值的观察值的百分比
numpy.percentile(a, q, axis)
# a: 输入数组
# q: 要计算的百分位数，在 0 ~ 100 之间
# axis: 沿着它计算百分位数的轴

# 4.numpy.median() 函数用于计算数组 a 中元素的中位数（中值）

# 5.numpy.mean() 函数返回数组中元素的算术平均值

# 6.numpy.average() 函数根据在另一个数组中给出的各自的权重计算数组中元素的加权平均值
```

## 9.NumPy 排序、条件刷选函数

```python
# 1.numpy.sort() 函数返回输入数组的排序副本
numpy.sort(a, axis, kind, order)
# a: 要排序的数组
# axis: 沿着它排序数组的轴，如果没有数组会被展开，沿着最后的轴排序， axis=0 按列排序，axis=1 按行排序
# kind: 默认为'quicksort'（快速排序）
# order: 如果数组包含字段，则是要排序的字段

# 2.numpy.argsort() 函数返回的是数组值从小到大的索引值。

# 3.numpy.lexsort() 用于对多个序列进行排序

# 4.numpy.nonzero() 函数返回输入数组中非零元素的索引。

# 5.numpy.nonzero() 函数返回输入数组中非零元素的索引。

# 6.numpy.extract() 函数根据某个条件从数组中抽取元素，返回满条件的元素。
x = np.arange(9.).reshape(3,  3)  
condition = np.mod(x,2)  ==  0  
y=np.extract(condition, x)


```

## 10.实践中记录---重要

```python
# 1.获取满足某条件的数组索引
a=np.arange(0,12)
id=np.argwhere(a>3)
id=np.argwhere(np.logical_and(a>2, a<4)) # 使用逻辑与

# 2.获取数组中最大值的索引
id=np.argmax(a)

# 3.python3 print不换行
# python3中print函数中的参数end默认值为'\n'，表示换行，给end赋值为空，就不会换行了，例如：
print (123,end='')
print (456,end='')

# 4.python基础_格式化输出（%用法和format用法）
print('%f' % 1.11)  # 默认保留6位小数 1.110000
print('%.1f' % 1.11)  # 取1位小数 1.1
print('%e' % 1.11)  # 默认6位小数，用科学计数法 1.110000e+00
print('%.3e' % 1.11)  # 取3位小数，用科学计数法 1.110e+00
print('%g' % 1111.1111)  # 默认6位有效数字 1111.11
print('%.7g' % 1111.1111)  # 取7位有效数字 1111.111
print('%.2g' % 1111.1111)  # 取2位有效数字，自动转换为科学计数法 1.1e+03

# 字符串输出
%s
%10s——右对齐，占位符10位
%-10s——左对齐，占位符10位
%.2s——截取2位字符串
%10.2s——10位占位符，截取两位字符串

>>> print('%s' % 'hello world')  # 字符串输出
hello world
>>> print('%20s' % 'hello world')  # 右对齐，取20位，不够则补位
         hello world
>>> print('%-20s' % 'hello world')  # 左对齐，取20位，不够则补位
hello world
>>> print('%.2s' % 'hello world')  # 取2位
he
>>> print('%10.2s' % 'hello world')  # 右对齐，取2位
        he
>>> print('%-10.2s' % 'hello world')  # 左对齐，取2位
he


```

| 符号 |       说明       |
| :--: | :--------------: |
|  %s  |      字符串      |
|  %c  |       字符       |
|  %d  |  十进制（整数）  |
|  %i  |       整数       |
|  %u  |    无符号整数    |
|  %o  |    八进制整数    |
|  %x  |   十六进制整数   |
|  %X  | 十六进制整数大写 |
|  %e  |   浮点数格式1    |
|  %E  |   浮点数格式2    |
|  %f  |   浮点数格式3    |
|  %g  |   浮点数格式4    |
|  %G  |   浮点数格式5    |
|  %%  |      文字%       |

| 转义字符 |                             说明                             |
| :------: | :----------------------------------------------------------: |
|    \n    |              换行符，将光标位置移到下一行开头。              |
|    \r    |               回车符，将光标位置移到本行开头。               |
|    \t    |        水平制表符，也即 Tab 键，一般相当于四个空格。         |
|    \a    | 蜂鸣器响铃。注意不是喇叭发声，现在的计算机很多都不带蜂鸣器了，所以响铃不一定有效。 |
|    \b    |          退格（Backspace），将光标位置移到前一列。           |
|    \\    |                            反斜线                            |
|    \'    |                            单引号                            |
|    \"    |                            双引号                            |
|    \     |     在字符串行尾的续行符，即一行未完，转到下一行继续写。     |

```python
# 5.numpy.delete删除一系列数组
import numpy as np
a = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9])
index = [2, 3, 6] #-------------------------------
new_a = np.delete(a, index)
print(new_a) #Prints `[1, 2, 5, 6, 8, 9]

# 6.NaN nan inf 
>>> a = float('nan')
>>> math.isnan(a)
True

# 用decimal模块
>>> from decimal import Decimal
>>> a = Decimal('nan')
>>> math.isnan(a)
True

# numpy模块
>>> a = np.nan
>>> math.isnan(a)
True

# inf不是nan，inf-inf或者-inf+inf是nan。inf是∞，一个比其他所有值都大的值
>>> 2*float('inf')
>>> inf
>>> -2*float('inf')
>>> -inf
>>> float('inf') == float('inf')
>>> True
>>> float('inf') - float('inf')
nan
>>> float('inf')/float('inf')
nan

# 7.创建空数组
a=[]
a=np.asarray(a)
```

### plot()线形

| 字符   | 描述       |
| :----- | :--------- |
| `'-'`  | 实线样式   |
| `'--'` | 短横线样式 |
| `'-.'` | 点划线样式 |
| `':'`  | 虚线样式   |

| 字符   | 描述                                         |
| :----- | :--------- |
| `'.'`  | 点标记                                       |
| `','`  | 像素标记                                     |
| `'o'`  | 圆标记                                       |
| `'v'`  | 倒三角标记                                   |
| `'^'`  | 正三角标记                                   |
| `'<'`  | 左三角标记                                   |
| `'>'`  | 右三角标记                                   |
| `'1'`  | 下箭头标记                                   |
| `'2'`  | 上箭头标记                                   |
| `'3'`  | 左箭头标记                                   |
| `'4'`  | 右箭头标记                                   |
| `'s'`  | 正方形标记                                   |
| `'p'`  | 五边形标记                                   |
| `'*'`  | 星形标记                                     |
| `'h'`  | 六边形标记 1                                 |
| `'H'`  | 六边形标记 2                                 |
| `'+'`  | 加号标记                                     |
| `'x'`  | X 标记                                       |
| `'D'`  | 菱形标记                                     |
| `'d'`  | 窄菱形标记                                   |
| `'|'`  | 竖直线标记                                   |
| `'_'`  | 水平线标记                                   |

| 字符  | 颜色   |
| :---- | :----- |
| `'b'` | 蓝色   |
| `'g'` | 绿色   |
| `'r'` | 红色   |
| `'c'` | 青色   |
| `'m'` | 品红色 |
| `'y'` | 黄色   |
| `'k'` | 黑色   |
| `'w'` | 白色   |

```python
# 7.为每个图建立一个figure,这样每个图会单独显示在一个窗口中；然后等所有图代码都写好后在最后面加上plt.show(),这样每张图就可以在不同窗口中同时显示了。

 # 绘制图1
 plt.figure() # ---------------------
 plt.plot(y, 'b-', linewidth=2)
 plt.legend()
 plt.grid(True)
 
 # 绘制图2
 plt.figure() # ---------------------
 plt.plot(z, 'b-', linewidth=2)
 plt.legend()
 plt.grid(True)
 plt.show()
```

### 8.np.random随机数

```python
# 1.numpy.random.rand(d0, d1, …, dn)，产生[0,1)之间均匀分布的随机浮点数，其中d0，d1....表示传入的数组形状。
# 均匀分布 均匀分布均匀分布均匀分布均匀分布均匀
#产生形状为(2,)的数组，也就是相当于有2个元素的一维数组。
temp=np.random.rand(2)
print(temp)  #[0.70284298 0.40041697]
print(type(temp)) # 查看数据类型，<class 'numpy.ndarray'>
print(temp[0])  #查看第一个数
print(type(temp[0])) #查看具体元素的数据类型，<class 'numpy.float64'>
 
'''
结果如下：
[0.70284298 0.40041697]
<class 'numpy.ndarray'>
0.7028429826756175
<class 'numpy.float64'>
'''

# 在rand()里面也可以没有参数，返回一个[0,1)之间的随机浮点数
#产生一个[0,1)之间的随机数
temp=np.random.rand() #0.6143086490875544
print(temp) #<class 'float'>
print(type(temp)) # 查看数据类型，<<class 'float'>

# 2.numpy.random.randn(d0, d1, …, dn)从标准正态分布中返回一个或多个样本值。 参数表示样本的形状。所谓标准正态分布就是指这个函数产生的随机数，服从均值为0，方差为1的分布，使用方法和rand()类似。
arr1=np.random.randn(2,4)  #二行四列，或者说一维大小为2，二维大小为4
#均值为0，方差为1
print(arr1)
print(type(arr1)) #<class 'numpy.ndarray'>
 
arr2=np.random.rand()
print(arr2) #0.37338593251088137
print(type(arr2))  #<class 'float'>
 
 
'''
结果如下：
[[ 0.56538481  0.41791992  0.73515441  1.73895318]
 [ 2.27590795 -1.17933538 -1.02008043  0.15744222]]
<class 'numpy.ndarray'>
0.37338593251088137
<class 'float'>
'''

# 3.指定数学期望和方差的正态分布
# 很多时候，我们不满足于仅仅产生服从标准正态分布的一组随机数，而是希望能够灵活的指定均值和方差，可用如下方法实现：

# 产生的一组随机数，服从均值为mu，方差为sigma^2的正态分布
#Two-by-four array of samples from N(3, 6.25):
arr3=2.5 * np.random.randn(2,4)+3  #2.5是标准差，3是期望
print(arr3)
"""
结果如下：
[[ 2.58150052  6.20108311  1.58737197  9.64447208]
 [ 2.68126136  0.63854145 -1.34499681  1.68725191]]
"""

# 4.numpy.random.random()方法返回随机生成的一个实数（浮点数），它在[0,1)范围内。
import numpy as np
 
x1=np.random.random()
print(x1)  #0.14775128911185142
print(type(x1))  #<class 'float'>
 
x2=np.random.random((3,3))
print(x2)
'''
[[0.07151945 0.00156449 0.66673237]
 [0.89764384 0.68630955 0.21589147]
 [0.50561697 0.27617754 0.5553978 ]]
'''
print(type(x2))  #<class 'numpy.ndarray'>
print(x2[1,1])  #0.68630955

# 30个[0,30）范围随机浮点数
X=10*np.random.random(30) # 载荷序列

```

