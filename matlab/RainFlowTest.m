%val=[1,2,3,4,8,4,3,2,6,4,5,5,78,32,5,9,1,6,3,4,1,8,3,1,0]
val=[4,7,2,54,3,9,5,6,2,1,5,3,2,7,8,9,5,3,5,8,0,8,4,5,734,5,5,6,78,32,45];

csvwrite('save.csv',val')

[c,hist,edges,rmm,idx] = rainflow(val);

T = array2table(c,'VariableNames',{'Count','Range','Mean','Start','End'})

b=0:length(val)-1
plot(b,val,'-x')