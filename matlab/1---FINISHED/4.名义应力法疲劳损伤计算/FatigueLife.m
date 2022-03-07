% 疲劳寿命分析
% 自编函数
% D=FatigueLife(X)
% X：载荷序列
% D：损伤度
%
% 算法：
% 1.雨流计数法--->提取波峰波谷--->R=findPV(X,P)
% 2.雨流计数法--->载荷历程调整--->R=seqadj(X)
% 3.雨流计数法--->四点计数法--->R=count4P(X)
% 4.平均应力修正--->S=goodman(Sa,Sm,Su)
% 5.计算损伤度--->D=damage(S,i)

function D=FatigueLife(X)
T1=findPV(X,0);
T2=seqadj(T1);
T3=count4P(T2);
T4=goodman(T3(:,2),T3(:,3),235);
T5=damage(T4,1);
D=T5;
end

