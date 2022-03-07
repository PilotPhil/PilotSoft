function res=weibull(n,k)
%%Weibull distribution
hold on;

n;%尺度参数scale para
k;%形状参数shape para
% pd=makedist('weibull','a',n,'b',k)%使用指定的参数值创建一个概率分布对象

x=0:0.01:5;
f=pdf('weibull',x,n,k);%概率密度函数Probability density function
F=cdf('weibull',x,n,k);%累计分布函数Cumulative Distribution Function

plot(x,f,'b-')
plot(x,F,'r-')
title('概率密度与累计分布函数');legend('pdf','cdf');
xlabel('随机变量');ylabel('概率');
end