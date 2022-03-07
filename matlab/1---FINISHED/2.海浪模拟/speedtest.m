%PM零次矩计算
% aeraOfPM(band,S,step,1.5,8.5)
% 0.005 s
% 
% PMInter(1.5,8.5)
% 0.410 s

%PM一次矩计算
% aeraOfPMW(band,S,step,1.5,8.5)
% 0.006 s
% 
% PMWInter(1.5,8.5)
% 0.637 s

%排序
% test=2000*rand(7000,1)
% sort(test)
% 0.045 s

%等分
% equalParts(basic,start,stop,1)
% 0.534 s

% solveEqual(start,stop)
% 2.699 s

% for i=1:length(omg)-1
%     area(i)=aeraOfPM(basic,omg(i),omg(i+1));
% end
% plot(area);
% 0.130 s

% syms x t;
% wave=0;
% g=9.81;
% for i=1:length(W)-1
%     temp=amp(i)*cos((Wc(i)^2*x/g)-Wc(i)*t+ip(i));
%     wave=wave+temp;
% end
% F(x,t)=wave
% 
% H1=[];%x=1 t:1-100
% for t=1:100
%     temp=F(1,t)
%     H1(t)=temp;
% end
% % 9.530s

g=9.81;
x=1.76;
for t=1:100
    wave=0;
    for i=1:length(W)-1
        temp=amp(i)*cos((Wc(i)^2*x/g)-Wc(i)*t+ip(i))
        wave=temp+wave;
    end
    
    Ft(t)=wave
end

%t=35;
% A=Wc.^2.*(x/g);
% B=Wc.*t;
% C=ip';
% D=A-B+C;
% E=cos(D);
% F=amp.*E;
% sum(F)
        
t=1:1000;
f=amp.*cos(Wc.^2.*(x/g)-Wc.*t'+ip');
wave=sum(f,2)


