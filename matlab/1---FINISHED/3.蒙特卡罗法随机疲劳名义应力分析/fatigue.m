clc;clear all;

% Step1. [0,1]上随机抽样，蒙特卡洛法得到载荷值
p=rand(1e4,1);%采样点数
n=6.02;%尺度参数scale para
k=0.98;%形状参数shape para
L=icdf('weibull',p,n,k);%载荷值 累积分布函数的逆函数
L=findPV(L',0);
L=seqadj(L);
L=L';

figure(2); 
subplot(3,2,1);plot(1:length(L),L,'b-');title('未加噪声的载荷时间序列');ylabel('载荷值');
subplot(3,2,2);FTTA(L,100);

% Step E.混入噪声
t=(0:length(L)-1)*0.01;
Ln=L+25*sin(50*t');
subplot(3,2,3);plot(1:length(Ln),Ln,'b-');title('加噪声后的载荷时间序列');ylabel('载荷值');
subplot(3,2,4);FTTA(Ln,100);

% Step E.2 滤波
R=filter(bp,Ln);%
subplot(3,2,5);plot(1:length(R),R,'b-');title('滤波后的载荷时间序列');ylabel('载荷值');
subplot(3,2,6);FTTA(R,100);

figure(3);A=CD(L);
figure(4);B=CD(Ln);
figure(5);C=CD(R);

er=(A-C)/A;
fprintf("损伤度误差：%.5f%%\n",er*100);























% % Step E.3 误差分析
% er=R-L;

% % Step2.雨流计数法
% count=rainflow(R);
% count(:,2)=count(:,2).*count(:,1);
% count(:,3)=count(:,3).*count(:,1);
% count(:,1)=1;
% T = array2table(count,'VariableNames',{'Count','Range','Mean','Start','End'});
% 
% Sa=count(:,2);%幅值
% Sm=count(:,3);%均值
% 
% % Step3.GoodMan平均应力修正
% Su=235;
% MS=(Su.*Sa)./(Su-Sm);%应力范围
% start=ceil(min(MS));
% stop=ceil(max(MS));
% 
% % Step4.统计应力范围对应的应力循环次数
% sRange=start:2:stop;
% for i=1:length(sRange)-1
%     cycle(i)=length(MS(MS>sRange(i) & MS<sRange(i+1)));
% end
% 
% figure(3);hold on;
% bar(sRange(1:end-1),cycle,'b');
% plot(sRange(1:end-1),cycle,'rx-');
% xlabel('应力范围S (N/mm^2)');ylabel('应力循环次数');
% 
% % Step5.损伤度计算
% Nmax=log10(5.8e12)-3*log10(MS);
% Nmax=10.^Nmax;
% 
% damage=MS./Nmax;
% life=sum(damage);
% fprintf("损伤度：%.10f%%",100*life);


