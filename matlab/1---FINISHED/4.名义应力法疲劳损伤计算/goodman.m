% Goodman法平均应力修正
% 自编函数
% 上一步骤：四点计数法
% 下一步骤：损伤计算
% S=goodman(Sa,Sm,Su)
% Sa：   应力幅值
% Sm：  应力均值
% Su：   极限应力
% S：     应力范围
%
% 算法：
% S=2*Su*Sa/(Su-Sm)


function S=goodman(Sa,Sm,Su)
Su;% 极限应力
Sa;% 应力幅值
Sm;% 应力均值

%S=Su.*Sa./(Su-Sm);
S=2*Su.*Sa./(Su-Sm);
end