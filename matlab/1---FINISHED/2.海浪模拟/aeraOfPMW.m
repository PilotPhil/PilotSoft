function Area=aeraOfPMW(basic,start,stop)
%波谱一阶矩求解（梯形法）
%输入：band---波浪谱频段（总的区间）
%           S---波谱
%           step---频率轴步进
%           start stop---真实积分区间

band=basic.band;
S=basic.S;
step=basic.step;

W=band(1):step:band(2);

for i=1:length(S)
    S(i)=W(i)*S(i);
end

temp1=(start-band(1))/step+1;
temp1=int32(temp1);

temp2=(stop-band(1))/step+1;
temp2=int32(temp2);

Y=S(temp1:temp2);
Area=trapz(Y)*step;
end