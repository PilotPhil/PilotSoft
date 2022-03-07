p=0:0.001:1;
n=6.02;%尺度参数scale para
k=0.98;%形状参数shape para
L=icdf('weibull',p,n,k);%载荷值 累积分布函数的逆函数

plot(p,L)