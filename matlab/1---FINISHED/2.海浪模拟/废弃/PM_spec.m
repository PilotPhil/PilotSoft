%%PM谱的仿真曲线%%
clc;clear all;

w=0:0.001:2;%频率范围

S10=PM(10,w);%v=10m/s
S12=PM(12,w);%v=12m/s
S15=PM(15,w);%v=15m/s

plot(w,S10,'b-',w,S12,'r-',w,S15,'g-');

xlabel('\omega[rad/s]');
ylabel('S(\omega) [m^2 s]');
legend('10m/s','12m/s','15m/s');
title('不同风速下的海浪的PM谱');


function S=PM(v,w)
%PM波谱函数
g=9.8;
for i=1:length(w)
    S(i)=(8.1*10^-3*g^2/w(i)^5)*exp(-0.74*(g/(v*w(i)))^4);
end
end



