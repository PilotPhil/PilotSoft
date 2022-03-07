% 雨流计数法--->提取波峰波谷(同时去除连续重复)
% 自编函数
% 上一步骤：这是第一个步骤
% 下一步骤：载荷历程调整
% R=findPV(X,P)
% X：载荷序列
% P：是否绘图
% R：结果
%
% 算法：
% 载荷序列：V=[v1,v2,…,vn]  其中vi,i∈[1,2,…,N]，
% 1.计算V的一阶差分向量 Diffv(i)=V(i+1)?V(i),其中i∈1,2,…,N?1
% 2.对差分向量进行取符号函数运算，Trend=sign(Diffv),即遍历Diffv，若Diffv(i)大于0，则取1；如果小于0，则取-1，否则则值为0。
% 3.从尾部遍历Trend向量,进行如下操作：if Trend(i)=0且Trend(i+1)≥0，则Trend(i)=1if Trend(i)=0且Trend(i+1)<0，则Trend(i)=?1
% 4.对Trend向量进行一阶差分运算，得到R=diff(Trend)。
% 5.遍历得到的差分向量R，如果R(i)=?2，则i+1为投影向量V的一个峰值位，对应的峰值为V(i+1)；如果R(i)=2，则i+1为投影向量V的一个波谷位，对应的波谷为V(i+1)。

function R=findPV(X,P)
copy1=X(1:end-1);% data的拷贝1
copy2=X(2:end);% data的拷贝2

% Step1.第一次差分运算
dif1=copy2-copy1;

% Step2.取符号运算
dif1(dif1>0)=1;
dif1(dif1<0)=-1;

% Step3.反向遍历取符号运算
temp=dif1;
copy3=dif1(1:end-1);
copy4=dif1(2:end);
temp(copy3==0 & copy4>=0)=1;
temp(copy3==0 & copy4<0)=-1;

% Step4.第二次差分
copy5=temp(1:end-1);
copy6=temp(2:end);
dif2=copy6-copy5;

% Step5.首尾处理
a=X(1);b=X(2);c=X(end-1);d=X(end);
dif2=[b-a,dif2,c-d];

% Step6.取符号运算
dif2(dif2>0)=1;dif2(dif2<0)=-1;dif2(dif2==0)=0;
dif2=-dif2;% 相反数 重要

% Step7.结束
PV=dif2;% 峰谷标识 1:峰 -1:谷 0:非
R=X(PV~=0);% 提取出来的峰谷载荷值


% 是否绘图
if P==1
hold on;
plot(1:length(X),X,'b-');
stem(1:length(dif2),abs(PV).*X,'ro');
title('find peak & vally ');xlabel('sequence');ylabel('load');
%legend('load','pv');
end

end