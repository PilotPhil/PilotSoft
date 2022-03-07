% 雨流计数法--->四点计数法
% 自编函数
% 上一步骤：载荷历程调整
% 下一步骤：平均应力修正
% R=count4P(X)
% X：载荷序列
% R：结果
%
% 算法：
% 使用四峰谷值雨流计数判定条件进行循环提取时，
% 4个点的选取遵循单向选取、循环进行的原则，
% 即在进行一次计数判定之后，只选择该次判定
% 所使用的4个点之后的点与该次计数判定使用的
% 点中没有被抹掉的点重新组成4个连续的峰谷值
% 点进行计数判定；当判定至载荷时间历程的末尾时，
% 如果计数尚未完成，则转至剩下的峰谷值点序列的
% 首端4个点重新开始以上判定过程，直至最终计数完毕。
% 这种处理方法使得雨流计数判定只向一个方向进行，
% 避免回退取点来进行计数判定的情况的出现降低了程序实现的复杂性。

function R=count4P(X)
Mean=[];% 均值
Rang=[];% 幅值
Start=[];% 起始位置
Stop=[];% 终止位置
used=[];% 被使用过的点

next=X;
L=length(X);
i=1;j=2;

while L>3
  while j<=L-2
    [flag,Me,Ra]=P4C(next(i),next(j),next(j+1),next(j+2));
    if flag==1 % 满足循环条件
      Mean=[Mean Me];% 均值
      Rang=[Rang Ra];% 幅值
      Start=[Start i];
      Stop=[Stop j+2];
      used=[used j j+1];
      
      j=j+2;
    else
      i=j;
      j=j+1;
    end
  end

  temp=next;
  temp(used)=nan;
  next=[];
  next=temp(temp>0);
  L=length(next);
  i=1;
  j=2;
  
  end

R=[ones(length(Rang),1),Rang',Mean',Start',Stop'];% 循环次数 均值 幅值 起始位 终止位

end