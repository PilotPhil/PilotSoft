function res=PMWInter(a,b)
%构建方程来求海浪谱的一次矩，使用连续积分，速度很慢，弃用
syms w;
Hs=1.8;%有义波高
T1=2.5;%海浪特征周期
A=173*Hs^2/(T1^4);
B=691/(T1^4);

WS(w)=w*(A/w^5)*exp(-B/w^4);%

res=int(WS,w,a,b);
res=vpa(res,4);
end