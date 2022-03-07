file='奈热乐队 - 走马.mp3'
[audio1,fs] = audioread(file);
subplot(2,2,1);
plot(audio1);

y=fft(audio1);
y=5*y;%%%
subplot(2,2,2);
plot(abs(y));

y1=y;%%%%%
subplot(2,2,3);
plot(abs(y1));

audio2=ifft(y1);
subplot(2,2,4);
plot(audio2);
audiowrite('res.wav',audio2,fs);