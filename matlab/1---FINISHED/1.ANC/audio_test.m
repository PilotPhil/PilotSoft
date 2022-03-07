clc;
clear all;
suptitle('主动式降噪');

% % % % % % % % % % % 白噪声 % % % % % % % % % % ,[1,fs]
[onise,noise_fs] = audioread( '噪声.wav');
noise_fs
subplot(5,2,1);
plot(onise);%时域波形
title('噪音时域');

y=fft(onise);
subplot(5,2,2);
plot(abs(y));%频域波形
title('噪音频域');

%sound(x,16000);%播放

% % % % % % % % % % % %仅音乐% % % % % % % % % % 
[music, music_fs] = audioread( '素材.wav');
music_fs
subplot(5,2,3);
plot(music);%时域波形
title('音乐时域');

y1=fft(music);
subplot(5,2,4);
plot(abs(y1));%频域波形
title('音乐频域');

%sound(x1,16000);%播放

% % % % % % % % % % % 音乐和白噪声 % % % % % % % % % % % 
[mix, mix_fs] = audioread( '混合.wav');
subplot(5,2,5);
plot(mix);
title('混合时域');

y2=fft(mix);
subplot(5,2,6);
plot(abs(y2));
title('混合频域');

%sound(mix,16000);%播放混合后的

% % % % % % % % % % %开始降噪% % % % % % % % % % %
subplot(5,2,8);
anc=y2-y;
plot(abs(anc));
title('降噪后频域');

anc_res= ifft(anc);
subplot(5,2,7);
plot(anc_res);
title('降噪后时域');

%sound(anc_res);%播放降噪后的
audiowrite('降噪后.wav',anc_res,music_fs);

mix_hand=y1+y;
subplot(5,2,10);
plot(abs(mix_hand));
title('手动混合白噪音和音乐频域');

hand= ifft(mix_hand);
subplot(5,2,9);
plot(hand);
title('手动混合白噪音和音乐时域');
audiowrite('手动混合白噪音和音乐.wav',hand,music_fs);

