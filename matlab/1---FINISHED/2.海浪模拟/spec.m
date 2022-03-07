function res=spec(Hs,T1,band,step)
    range=band(1):step:band(2);
    S=wavespec(4,[Hs,T1],range',0);
    res=S;
end