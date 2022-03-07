% 传动比计算
% 2021-1-16
% @Pilot-Phil
% https://github.com/PilotPhil?tab=repositories

front=32;% 牙盘
after=[11,13,16,20,24,28,34,40];% 飞轮
after2=[11,13,15,18,21,24,28,32];% 飞轮

hold on;

figure(1)
ratio=front./after;
plot(after,ratio,'-r');

% figure(2)
ratio2=front./after2;
after2=after+2;
plot(after2,ratio2,'-b');