% 雨流计数法--->四点计数判定
% 自编函数
% [flag Me Ra]=P4C(a,b,c,d)
% a    ：载荷点1
% Me ：均值
% Ra  ：幅值
% flag：是否构成循环
%
% 算法：
% 1.载荷点a,b,c,d
% 2.变程：S1=|a-b|,S2=|b-c|,S3=|c-d|
% 3.满足条件：S1>=S2且S2<=S3时
% 4.提取均值：0.5*(b+c)  幅值：|b-c|

function [flag Me Ra]=P4C(a,b,c,d)
  S1=abs(a-b);
  S2=abs(b-c);
  S3=abs(c-d);
  
  if S1>=S2 && S2<=S3
    flag=1;
    Me=0.5*(b+c);% 均值
    Ra=0.5*abs(b-c);% 幅值
  else
    flag=0;Me=0;Ra=0;
  end
  
end