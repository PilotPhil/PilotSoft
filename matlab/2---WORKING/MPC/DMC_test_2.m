sim.predict_length = 20;%预测步长
sim.monitor_length = 10;%控制步长
sim.num = 2;%传递函数增益
sim.den = [1,5,1];%传递函数分母（包含时间常数）
sim.Ts = 0.4;%采样时间0.4s
sim.N = 400;%仿真步长
sim.Q = diag(1.^[1:sim.predict_length]);%误差权重矩阵
sim.R = diag(0.05.^[1:sim.monitor_length]);%控制权重矩阵
sim.h = diag(1.^[1:20]);%矫正参数向量
sim.c = [1,zeros(1,sim.monitor_length-1)];%取第一个值
sim.s = [[zeros(sim.predict_length-1,1),eye(sim.predict_length-1)];
[zeros(1,sim.predict_length-1),1]];%位移矩阵
[A,a] = get_a_matrix(sim.num,sim.den,sim.Ts,sim.predict_length,sim.monitor_length,sim.predict_length);%计算动态矩阵以及建模向量
sim.A = A;%动态矩阵
sim.y0 = a;%初始预测输出
sim.a = a';%建模参数
sim.d = sim.c*(sim.A'*sim.Q*sim.A+sim.R)^(-1)*sim.A'*sim.Q;%输入增量算符
sim.h = 1.^[1:sim.predict_length]';%校正向量


myP=myProcess(2,[1,5,1],0.4);
myP.setStateGrid(-100,100,0.1);%%%建立控制过程,方法很多,这里是我们自己建立的算法
target = [1*ones(1,100),1.3*ones(1,100),-2.3*ones(1,120),1.8*ones(1,80)];%设定目标值
yn_0 = sim.y0';%设置初始预测值
u_k = 0;%设置初始输入
delta_u = 0;%设置输出输入增量
y = zeros(1,sim.N);%设置输出buffer
error = zeros(1,sim.N);%设置误差buffer
%%%% 开始仿真 %%%%
for t = 1:sim.N%%%仿真,步长400步,采样时间0.4s
    if t+19<=sim.N
        w = target(t:t+19);
    else
        w = [target(t:sim.N),1.8*ones(1,t+19-sim.N)];%获取设定轨迹
    end
    delta_u = sim.d*(w'-yn_0);%%计算delta u
    u_k = u_k+delta_u;%%计算输入
    y_k = myP.DMC(u_k);%% 计算真实输出
    yn_1 = sim.a*delta_u+yn_0;%%计算预测输出
    yn_1k = yn_1(1);%取预测输出第一个元素
    predict_error = y_k - yn_1k;%%计算预测误差
    revise_error=predict_error*sim.h;%%校正预测输出
    y_cor = yn_1+revise_error;%%计算校正估计输出
    yn_0 = sim.s*y_cor;%% 更新初始预测输出
    y(t)=y_k;%%记录真实输出
    error(t)=target(t)-y(t);%记录实时误差
end
%%%% 绘制结果  %%%%
plot_result(y,target,error);%%%绘图程序


function [A,a] = get_a_matrix(num,den,Ts,N,M,P)
G = tf(num,den);%建立传递函数
G = c2d(G,Ts);%将传递函数离散化
% [num,den] = tfdata(G,'v');
a = step(G,1*Ts:Ts:N*Ts);%对离散的模型做阶跃响应，得到响应输出，采样时间为0.4s，20步之后达到稳定
a = a';%对参数向量a进行转置
A = zeros(P,M);%开始建立动态矩阵
for i = 1:P
    for j= 1:M
        if j>i
            A(i,j)=0;
        else
            A(i,j)=a(i-j+1);%对建模向量进行反向排序,计算得到动态矩阵
        end
    end
end
end