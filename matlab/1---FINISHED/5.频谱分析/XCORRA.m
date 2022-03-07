% 相关运算分析(归一化频率)(默认绘图)
% 自编函数---封装自r=xcorr(x,y)
% function Res=XCORRA(x,y)
% x     ：信号1
% y     ：信号2
% Res ：相关运算结果

function Res=XCORRA(x,y)
% Step1.相关运算
[Rxyl,index]=xcorr(x,y);

% Step2.归一化
a=x.*x;
b=y.*y;
Rxx0=sum(a);% Rxx(0)
Ryy0=sum(b);% Ryy(0)
temp=(Rxx0*Ryy0)^0.5;
Rxyl=Rxyl./temp;
Res=Rxyl;
stem(index,Rxyl,'bo');
xlabel('移位参数');
ylabel('归一化后相关度');
title('相关度分析');
end
