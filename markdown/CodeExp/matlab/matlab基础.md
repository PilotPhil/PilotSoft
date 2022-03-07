## 一.基础

### 1.冒号运算符

  ```matlab
  x=0:2:10	%0 2 4 6 8 10	开始	步长	结束
  
  x=linspace(1,10,10)	%初值	终值	向量长度	生成等间隔向量
  ```

### 2.内置函数初始化

  ```matlab
  zeros(n)	%n*n零矩阵
  zeros(n,m)	%n*m零矩阵
  zeros(size(arr))	%与arr矩阵同阶零矩阵
  ones(n)		%n*n一矩阵
  ones(n,m)	%n*m一矩阵
  eye(n)		%n*n单位矩阵
  eye(n,m)	%n*m单位矩阵
  y=rand		%随机数
  y=rand(x)	%x*x随机矩阵
  y=rand(a,b)
  m=magic(n)	%n*n魔方矩阵
  diag(v)		%以向量v为主对角线生成对角矩阵
  diag(v,k)	%以向量v为第k各对角线生成对角矩阵
  v=diag(x)	%返回矩阵主对角线上元素
  v=diag(x,k)	%返回矩阵第k条对角线上的元素
  size(arr)	%返回arr阶数
  length(arr)	%返回一个向量的长度或者二维数组中最长的一维的长度
  ```

### 3.数组下标

```matlab
%下标从 1 开始
a=[1 2 4;4 5 6;7 8 9];
a(2,2)%5
a(1,:)%1 2 4
a(:,2)%2 5
size(a)%3行3列

a([1 2],:)=a([2 1],:)%交换1 2行
a(1:2,[2 3])=[0 1;0 1]

a=a-1%数组和标量运算 逐个运算
```

### 4.eshape&remat

```
x=[1 2 3;4 5 6];
y=reshape(x,[3,2]);		%将x转换为3行2列矩阵
y=repmat(x,[2,3]);		%以x的内容堆叠在2行3列矩阵中
```

### 4.end函数

```matlab
%返回一个数组中最后一个数的下标
a=[1,2,3,-2];
a(end)

x=[2 3 4 6;3 9 0 2;5 1 2 6];
x(2:end,3:end)
```

### 5.格式化输出：

```matlab
fprintf('test:%.4f\n',3.14159);
%d	整数
%e	科学计数法
%f	浮点数
%g	?
\n	换行
```

### 6.数组和矩阵运算

```matlab
A+B		%数组加法
A-B		%数组减法
A.*B	%数组乘法-AB元素逐个对应相乘
A*B		%矩阵乘法
A./B	%数组右除法-A(i,j)/B(i,j)
A.\B	%数组左除法-B(i,j)/A(i,j)
A/B		%矩阵右除法-A*B^-1
A\B		%矩阵左除法-B*A^-1
A.^B	%数组指数运算-A(i,j)^B(i,j)
A^x		%A为方阵 x为正整数 矩阵A自乘x次
		%		x为负整数 A^-1自乘x次
		%x=m/n 分数 A先自乘m次，在对结果矩阵中每个元素开n次方
A.^x	%x为标量	对A中每个元素求x次方
		%x为同型矩阵 对A中每个元素求x中对应元素的次方
```

### 7.矩阵关系运算

```matlab
%比较两个 同型矩阵 中对应元素的大小关系
A=[1 2;3 4];
B=[2 2;2 ;];
c1=A>B
```

### 8.矩阵逻辑运算       ???

```matlab
%	或	|
%	与	&
%	非	~
%	异或	xor(A,B)
%	先决或	||
%	先决与	&&
```

### 9.矩阵其他常用

```matlab
%转置
x=[1 2 3 4];
x'
y=[3,4,5]'

%翻转
y=flipud(x)		%上下翻转
y=fliplr(x)		%左右翻转
y=rot90(x)		%逆时针旋转90°
```

### 10.运算优先级：

```matlab
%1.括号内先运算，从最里面括号运算
%2.幂运算，从左往右
%3.乘除法，从左往右
%4.加减法，从左往右
```

### 11.常用函数

```matlab
abs(x)		%绝对值
sin(x)
cos(x)
tan(x)
asin(x)
acos(x)
atan(x)
angle(x)	%计算复数x的幅角
real()		%求复数实部
imag()		%求复数虚部
conj()		%求共轭复数
exp(x)		%e^x
log(x)		%log(e,x)
log10(x)
sqrt(x)		%x开方
mod(x,y)	%取模
mean(x)		%求均值
max()
[value index]=max(A)
min()
var()		%求方差
std()		%求标准差
cov()		%求协方差
range()		%求极差
corrcoef()	%求相关系数
[value,index]=max(x)	%返回数组x中最大值和下标
[value,index]=min(x)	%返回数组x中最小值和下标
int2str(x)	%整数转化为字符串
num2str(x)	%带小数点的数转化为字符型数组
str2num(x)	%字符串转换为数
atan2(y,x)	%(tan(y/x))^-2
round(x)	%四舍五入
fix(x)		%朝零取整
floor(x)	%朝负无穷取整
ceil(x)		%朝正无穷取整
isnan(x)	%非数值 返回1
```

### 12.结构体

```matlab
%通过struct结构体定义
s=struct('name','sth','age',23)
s.name='what';

%直接赋值定义
stru(1).name='what';
stru(2).age=12;
```

### 13.元胞数组

```matlab
%将不同类型、不同大小的数组放在同一个数组中
c1={[1 2;3 4],'what',[1 2 3 4]};

cell(n)		%n*n空元胞数组
cell(m,n)	%m*n
cell(size(A))
```

### 14.数组转换

```matlab
mat2cell
cell2mat
num2cell
cell2struct
struct2cell
```

### 15.方正行列式

```matlab
A=[1 2;3 4];
d1=det(A)
```

### 16.逆矩阵和广义逆矩阵

```matlab
inv(x)		%求方阵逆矩阵
pinv(x)		%求一般矩阵广义逆矩阵
```

### 17.方阵特征值和特征向量

```matlab
d=eig(A)	%求A特征值
d=eig(A,B)	%求方阵A,B的广义特征值
[V,D]=eig(A)%求方阵A的特征值矩阵D和特征向量矩阵V，满足AV=VD
[V,D]=eig(A,B)%AV=BVD
```

### 18.微积分

```matlab
y=limit(fun,x,x())%函数-自变量-自变量取值

syms x a
r=limit('(tan(x)-tan(a))/(x-a)',x,a)
```

```matlab
diff(f,x,n)%函数-对x求导-n阶导数

syms x y
f=sym('exp(-2*x)*cos(3*x^(1/2))')
diff(f,x,1);
```

```matlab
int(f,r,x0,x1)%积分表达式-积分变量-上限-下限
```





## 二.二维绘图

### 1.简单绘图

```matlab
x=0:1:10;
y=x.^2-10*x+15;
plot(x,y);
title('plot of v=x.^2-10*x+15');%标题
xlabel('x');%标尺x
ylabel('y');%标尺y
grid on;%网格线打开
```

### 2.联合绘图

```matlab
x=0:pi/100:2*pi;
y1=sin(2*x);
y2=2*cos(2*x);
plot(x,y1,x,y2);	%两条曲线

title('plot');
xlabel('x');
ylabel('y');
grid on;
```

### 3.颜色形式线型等

```matlab
plot(x,y,'yv-')		%没有顺序限制

%颜色
%	y	黄色
%	m	品红色
%	c	青绿色
%	r	红色
%	g	绿色
%	b	蓝色
%	w	白色
%	k	黑色

%标记类型
%	.	点
%	o	圈
%	x	叉
%	s	正方形
%	d	菱形
%	v	倒三角
%	^	正三角
%	>	向右三角
%	<	向左三角
%	p	五角星
%	h	六角星
%	none   无

%线型
%	-	实线
%	:	点线
%	-.	点划线
%	--	虚线
%	none  无
```

### 4.图列

```matlab
legend('string1','string2','string3'……,pos);%pos代表图例位置
legend('f(x)','d/df(x)');

%	0	自动寻找最佳位置，至少不与数据冲突
%	1	图像右上角
%	2	图像左上角
%	3	图像左下角
%	4	图像右下角
%	-1	图像右边
```

### 5.plot函数

```matlab
plot(y)		%绘制y的各列
plot(x1,y1,x2,y2)		%绘制多条线条
plot(x,y,LineSpec)		%设置线的参数
```

### 6.hold函数

```matlab
hold on		%开启图形保持，可以在同一图形窗口绘制多个图形
hold off
```

### 7.axis函数：设置坐标系的刻度和显示方式

```matlab
缺省		p63
```

### 8.box函数：显示或隐藏坐标边框

```matlab
box on		%显示坐标边框
box off
box			%改变坐标框的显示状态
box(axes_handle,……)		%
```

### 9.grid函数：开启、关闭网格

```matlab
grid on
grid off
```

### 10.title函数：添加标题

```matlab
title('whatever')
```

### 11.xlabel	ylabell

```matlab
xlabel('时间');
ylabel('载荷值');
```

### 12.text函数：当前坐标系下添加文本对象

```matlab
text(x,y,'something');		%在点(x,y)添加字符串
text(x,y,z,'sonething');
```

### 13.gtext函数：交互式添加文本对象

```matlab
gtext('string');		%按下鼠标，人为指定文本插入位置
gtext('string1','string2','string3');		%一键加入多个字符串
```

## 三.程序设计

### 1.函数

```
function [out1,out2,out3]=funname(in1,in2.in3)
%		函数名最好和文件名相同
%		函数名不与内部函数重名
```

### 2.老几样

```matlab
%if
if a>0
	……
elseif a<0
	……
else
	……
end
```

```matlab
%switch
switch num
	case 0
	……
	case 1
	……
	case 2
	……
end
```

```matlab
%for
for i=0:1:100
	disp(i)
end
```

```matlab
%while
while 1
	……
end
```

```matlab
%try
try
	command1		%执行command1若发生错误，就执行command2
catch ME
	command2
end
```

```matlab
%		continue & break

for i=0:2:100
	if i>=20&i<=60
		continue;		% 跳过，执行下一次迭代
	end
end

i=100;
while 1
	i=i-1;
	if i<10
		break;
	end
end
	
```























