 %%海浪模拟%%
clc;clear all;hold on;g=9.81;

% Step1:选择合适的波谱---ITTC-Modified Pierson-Moskowitz (Hs,T1)
fprintf('Step1:选择合适的波谱\n');
Hs=1.8;
T1=2;
step=0.001;%步进
band=[1.5 8.5];%对1.5~8.5Hz频段进行等能量分割
range=band(1):step:band(2);
S=wavespec(4,[Hs,T1],range',0);%有义波高Hs=1.5m 海浪特征周期T1=2s 不绘图
basic=struct('band',band,'S',S,'step',step);%基础数据

% Step2:等能量划分频段---trapz(y)梯形法积分
fprintf('Step2:等能量划分频段\n');

N=5;%等分数 2^N
fprintf('等分数：%d 等分能量：%.5f\n',2^N,trapz(S)*step/2^N);
W=band;%等分点数组
for n=1:N
    for i=1:length(W)-1%等分
        new(i)=equalParts(basic,W(i),W(i+1),0);%不绘图
    end
    W=[W,new];%新等分点加入
    W=sort(W);%排序
end

figure(1);
str=['N=',int2str(2^N)];%等分数
plot(range,S,'b-');%画海浪谱
stem(W,wavespec(4,[Hs,T1],W',0),'rx')%画等分线
legend('Hs=1.5m, T1=2s',str);xlabel('\omega [rad/s]');ylabel('S(\omega) [m^2 s]');title('PM频谱与其等能量分割');

% Step3:确定谐波频率---海浪普的一阶矩比零阶矩
fprintf('Step3:确定谐波频率\n');
for i=1:length(W)-1
    oom(i)=aeraOfPMW(basic,W(i),W(i+1));%一阶矩
    zom(i)=aeraOfPM(basic,W(i),W(i+1));%零阶矩
end
Wc=oom./zom;
Wc=2*pi*Wc;% 转化为角频率

% Step4:确定各谐波波幅
fprintf('Step4:确定各谐波波幅\n');
amp=(2*zom).^0.5;

% Step5:确定初始相位---随机数[0~2pi]
fprintf('Step5:确定初始相位\n');
ip=(pi*2).*rand(length(amp),1,'double');%initial phase

% Step6.1:固定空间点仿真x=1
wave=[];
x=1;
fprintf('Step6.1:固定空间点仿真x=%.3fm\n',x);
t=(1:999)*0.2;
f=amp.*cos(Wc.^2.*(x/g)-Wc.*t'+ip');
wave1=sum(f,2);


figure(3);
plot(wave1);title('固定空间点仿真');xlabel('t/s');ylabel('\zeta(x)/m');

% Step6.2:固定时间点仿真t=1
wave=[];
t=1;
fprintf('Step6.2:固定时间点仿真t=%ds\n',t);
x=0:0.01:999;
f=amp.*cos(Wc.^2.*(x'./g)-Wc.*t+ip');
wave2=sum(f,2);

figure(4);
plot(wave2);title('固定时间点仿真');xlabel('x/m');ylabel('\zeta(t)/m');

