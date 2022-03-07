% Step1. [0,1]上随机抽样，蒙特卡洛法得到载荷值
p=rand(1e4,1);%采样点数
n=6.02;%尺度参数scale para
k=0.98;%形状参数shape para
L=icdf('weibull',p,n,k);%载荷值 累积分布函数的逆函数

D=FatigueLife(L');

fprintf("损伤：%.6f%%",100*D)