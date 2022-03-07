% 雨流计数法--->主函数
% 自编函数
% R=myrainflow(X)
% X：载荷序列
% R：[循环次数 均值 幅值 起始位 终止位]
%
% 算法：
% 1.提取波峰波谷--->R=findPV(X,P)
% 2.载荷历程调整--->R=seqadj(X)
% 3.四点计数法--->R=count4P(X)

function R=myrainflow(X)
% Step1.提取峰谷
tem1=findPV(X,0);
% Step2.载荷历程调整
tem2=seqadj(tem1);
% Step3.计数  [Mean',Rang',Start',Stop'];% 循环次数 均值 幅值 起始位 终止位
R=count4P(tem2);% 四点计数法
end



