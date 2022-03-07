% 傅里叶变换分析单边谱(默认绘图)
% 自编函数---封装自Y=fft(X)
% Res=FTTA(signal,Fs)
% signal：信号
% Fs      ：采样率
% Re     ：单边谱结果

function Re=FTTA(signal,Fs)
%输入：1-信号 2-采样率Ws>2Wm奈奎斯特采样定律

if mod(length(signal),2)%若非偶数
    signal(end)=[];
end

Fs;%采样率
T=1/Fs;%采样周期
L=length(signal);%信号长度
t=(0:L-1)*T;%时间向量

H=fft(signal);%快速傅里叶变换
P2=abs(H/L);%双边谱
P1=P2(1:L/2+1);%单边谱
P1(2:end-1)=2*P1(2:end-1);

grid on;hold on;
f=Fs*(0:L/2)/L;
plot(f,P1,'b-');
Re=P1; %
%[pks,locs]=findpeaks(P1,f);%峰值、坐标

title('Single-Sided Amplitude Spectrum');
xlabel('f(Hz)');ylabel('|P1(f)|');
legend('SSAS');
end



%%例子
% clear all;clc;
% 
% Fs=1000;%采样率
% T=1/Fs;%采样周期
% L=1500;%信号长度
% t=(0:L-1)*T;%时间向量
% 
% 
% signal=0.7*sin(50*t)+5*sin(120*t)+2*randn(size(t));
% H=fft(signal);%快速傅里叶变换
% P2=abs(H/L);%双边谱
% P1=P2(1:L/2+1);%单边谱
% P1(2:end-1)=2*P1(2:end-1);
% 
% f=Fs*(0:L/2)/L;
% plot(f,P1);
% title('Single-Sided Amplitude Spectrum of ');
% xlabel('f(Hz)');ylabel('|P1(f)|');
