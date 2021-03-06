% 雨流计数法--->载荷历程调整
% 自编函数
% 上一步骤：提取波峰波谷
% 下一步骤：平均应力修正
% R=seqadj(X)
% X：载荷序列
% R：结果
%
% 算法：
% 1.判断峰谷点总数是否为奇数，若为奇数，不需要对载荷-时间历程做出调整。若为偶数，则去除最后一个点，这样使得载荷-时间历程的起始均为峰或谷由于实际的监测采集过程中数据量巨大，去除最后一个点不会对整体造成重大影响。
% 2.使载荷时间历程的首尾值相等。若首尾均为峰，则首尾值取两者之间较大的，若首尾均为谷，则首尾值取两者之间较小的。
% 3.遍历载荷时间历程，寻找载荷绝对值最大的点，从此点处将载荷时间历程切开，将左段的末点与右段的起点连接（左段与右段均包含载荷的绝对值最小的点）。

function R=seqadj(X)
% Step1.判断峰谷点总数是否为奇数
L=length(X);
if L%2==0
  X=X(1:end-1);
end

% Step2.首尾取值处理
if X(1)>X(2) % 若首尾均为 峰
    temp=max(X(1),X(end));
    X(1)=temp;
    X(end)=temp;
else % 首尾均为 谷
    temp=min(X(1),X(end));
    X(1)=temp;
    X(end)=temp;
end

% Step3.从荷绝对值最大的点处将载荷时间历程切开，将左段的末点与右段的起点连接
[v,i]=max(X);
R=[X(i:end),X(2:i)];

end