t = (-2:0.001:3)'*5;
n = randn(size(t)); % 噪声
signal = sin(t);         % 信号
signal_noise = signal + n;          % 带噪信号
R = cov(n);         % 测量误差协方差

% 【1】预测误差比较大的时候
Q = 10^-7; % 预测误差
res = KalmanFilter(signla_noise,Q,R);
e = signal - res; % 误差

hold on;
plot(t,signal_noise,'g',t,signal,'b',t,res,'r');
legend('含噪声信号','纯信号','滤波后');


function res=KalmanFilter(data,Q,R)
    %----------------------------------------------
    % res=kalmanFilter(data,Q,R)
    % data:采集到的数据点
    % Q   :状态误差协方差矩阵---无法精确建模带来的误差
    % R   :观测误差协方差矩阵---传感器误差（方差）
    %----------------------------------------------

    % 1.各矩阵
    T=1; % 采样间隔1s
    A=[1 T;0 1]; %
    B=[0]; %
    H=[1 0]; %
    Q; % 状态误差协方差矩
    R; % 观测误差协方差矩

    % 2.初始值
    N=length(data);
    Xu = [data(1); 0];
    Pu = [0 0;0 0];
    res  = zeros(N,1);

    % 3.迭代
    for i = 2:N
        Xp = A * Xu;
        Pp = A * Pu * A' + Q;
        K  = Pp * H' * ( H * Pp * H' + R)^-1;
        Xu = Xp - K * H * Xp + K * data(i);
        Pu = Pp - K * H * Pp;
        
        res(i) = Xu(1);
    end
end










