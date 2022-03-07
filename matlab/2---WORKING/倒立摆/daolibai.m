mPend = 0.2; % 摆的质量
mCart = 0.5; % 小车质量
b = 0.1; % 阻尼系数
I = 0.018; % 摆的转动惯量
g = 9.8; % 重力加速度
L = 0.3; % 摆的重心到关节的角度

q = (mCart+mPend)*(I+mPend*L^2)-(mPend*L)^2; % 

s = tf('s'); % 构造s

% 1.摆角度/输入力 传递函数
P_cart = (((I+mPend*L^2)/q)*s^2 - (mPend*g*L/q))/(s^4 + (b*(I + mPend*L^2))*s^3/q - ((mCart + mPend)*mPend*g*L)*s^2/q - b*mPend*g*L*s/q);

% 1.车位置/输入力 传递函数
P_pend = (mPend*L*s/q)/(s^3 + (b*(I + mPend*L^2))*s^2/q - ((mCart + mPend)*mPend*g*L)*s/q - b*mPend*g*L/q);

sys_tf = [P_cart ; P_pend] % 构造传递函数

inputs = {'u'}; % 定义输入为u

outputs = {'x'; 'phi'};% 定义输出为角度与位移

set(sys_tf,'InputName',inputs) % 设置输入输出
set(sys_tf,'OutputName',outputs)


Kp = 100;
Ki = 1;
Kd = 30;
C = pid(Kp,Ki,Kd);
T1 = feedback(P_pend,C);
t=0:0.01:4;
impulse(T1,t)
