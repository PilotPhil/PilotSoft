p=rand(1e4,1);%采样点数
n=6.02;%尺度参数scale para
k=0.98;%形状参数shape para
L=icdf('weibull',p,n,k);%载荷值 累积分布函数的逆函数
L=findPV(L',0);
L=seqadj(L);
L=L';
csvwrite('testData.csv',L)