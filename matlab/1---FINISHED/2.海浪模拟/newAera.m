allS=trapz(S)*step;
N=20;
sa=allS/N;

start=1;
stop=9;

for i=1:N
    while 1
        index=start;
        A=aeraOfPM(basic,start,index);
        if A==sa
            save(i)=index;
            start=index;
            break;
        else
            index=index+0.001;
        end
    end
end
