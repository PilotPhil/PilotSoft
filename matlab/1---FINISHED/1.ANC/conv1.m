clc;
clear all;

[IR,fs1]=audioread('IR.wav');%冲激响应
[talk,fs2]=audioread('talk.wav');%说的话

mix=conv(talk,IR);%卷积

audiowrite('conv_res.wav',mix,fs1);%生成音频

y1=fft(IR);
y2=fft(talk);
y3=fft(mix);
y4=y3-y1;
y5=ifft(y4);
audiowrite('nc_res.wav',y5,fs1);%生成音频