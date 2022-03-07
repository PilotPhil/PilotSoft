function index=findEqualPoint(W0,W,S,P)
%%找到序列面积等分点index%%
%%输入：频率轴W0、积分区域频率向量W 、波谱S、是否绘图P？0：1
%%输出：等分点频率值
hold on;
step=W(2)-W(1);%频率轴步进
pl=(W(1)-W0(1))/step;%
pr=(W0(end)-W(end))/step;%
pl=int32(pl);%转化为整型
pr=int32(pr);

% 至左向右进行积分
Aera_L=0;
for i=1:length(W)
    Y=S(1+pl:i+pl);
    A=trapz(Y);
    Aera_L(i)=A*step;%至左向右面积序列
end

% 至右向左进行积分
Aera_R=0;
for i=1:length(W)
    Y=S(length(W0)-i-pr+1:length(W0)-pr);
    A=trapz(Y);
    Aera_R(length(W)-i+1)=A*step;%至右向左面积序列
end

for i=1:length(W)
    error(i)=abs(Aera_L(i)-Aera_R(i));%面积差值
end

[value,id]=min(error);%找到面积差值最小值和其索引

index=step*id+W(1);
fprintf('等面积点：%.4f\n等面积：%.4f\n面积误差最小：%.4f\n',index,Aera_L(id),value);


if P==1%是否要画图
    plot(W,Aera_L,'r.-',W,Aera_R,'b.-',W,error,'K.-');
    stem(index,Aera_L(id));
    legend('自左向右面积','自右向左面积','面积差值','等面积点');
    xlabel('\omega [rad/s]');
    ylabel('E [m^2 s \omega]');
    title('面积等分点求解');
end

end