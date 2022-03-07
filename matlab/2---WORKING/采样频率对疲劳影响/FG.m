function res=CD(R)

% Step2.雨流计数法
hold on;
count=rainflow(R);
count(:,2)=count(:,2).*count(:,1);
count(:,3)=count(:,3).*count(:,1);
count(:,1)=1;
T = array2table(count,'VariableNames',{'Count','Range','Mean','Start','End'});

Sa=count(:,2);%幅值
Sm=count(:,3);%均值

% Step3.GoodMan平均应力修正
Su=235;
MS=2*(Su.*Sa)./(Su-Sm);%应力范围
start=ceil(min(MS));
stop=ceil(max(MS));

% Step4.统计应力范围对应的应力循环次数
sRange=start:2:stop;
for i=1:length(sRange)-1
    cycle(i)=length(MS(MS>sRange(i) & MS<sRange(i+1)));
end


bar(sRange(1:end-1),cycle,'b');
plot(sRange(1:end-1),cycle,'rx-');
xlabel('应力范围S (N/mm^2)');ylabel('应力循环次数');

% Step5.损伤度计算
Nmax=log10(5.8e12)-3*log10(MS);
Nmax=10.^Nmax;

damage=MS./Nmax;
res=sum(damage);
fprintf("损伤度：%.10f%%\n",100*res);

end
