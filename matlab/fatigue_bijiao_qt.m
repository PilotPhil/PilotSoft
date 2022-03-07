% Step1. [0,1]上随机抽样，蒙特卡洛法得到载荷值
p=rand(100,1);%采样点数
n=6.02;%尺度参数scale para
k=0.98;%形状参数shape para
L=icdf('weibull',p,n,k);%载荷值 累积分布函数的逆函数

csvwrite('testData.csv',L)
L=findPV(L',1);

[c,hist,edges,rmm,idx] = rainflow(L);

T = array2table(c,'VariableNames',{'Count','Range','Mean','Start','End'})

S=goodman(c(:,2),c(:,3),235);

D=damage(S,1)