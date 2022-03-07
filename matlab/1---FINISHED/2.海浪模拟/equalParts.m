function index=equalParts(basic,start,stop,plm)
%等能量分割点求解---梯形法---简化运算加快速度%%
%输入：band---波浪谱频段（总的被分割的区间）
%           S---波谱
%           step---频率轴步进
%           start stop---真实被分割区间
%输出：分割点频率坐标
band=basic.band;
S=basic.S;
step=basic.step;

temp1=(start-band(1))/step+1;
temp1=int32(temp1);

temp2=(stop-band(1))/step+1;
temp2=int32(temp2);

%从左向右积分
AL=[];
id=1;
for i=temp1:temp2
    Y1=S(temp1:i);
    AL(id)=trapz(Y1)*step;
    id=id+1;
end

%从右向左积分
AR=[];
id=1;
for i=temp2:-1:temp1
    Y2=S(i:temp2);
    AR(id)=trapz(Y2)*step;
    id=id+1;
end
AR=flip(AR);%倒序处理

ER=[];
for i=1:length(AL)
    ER(i)=abs(AL(i)-AR(i));
end

[value,where]=min(ER);
index=(where-1)*step+start;

if plm==1%是否要绘图
    hold on;
    W=start:step:stop;
    plot(W,AL,'b-',W,AR,'b-',W,ER,'r-');
    stem(index,AL(where),'ko');
    legend('自左向右面积','自右向左面积','面积差值','等面积点');
    xlabel('\omega [rad/s]');
    ylabel('E [m^2 s \omega]');
    title('面积等分点求解');
end

end
