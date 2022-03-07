#计算平板拖曳的摩擦阻力


def Re(v,l,u):#
    return v*l/u

def Xcr(Recr,u,v):#Recr:临界雷诺数 u:运动粘度 v:拖曳速度
    return Recr*u/v

def cf_ceng_or_tuan(Xcr,length,Re,A):
    if(0.05*length<Xcr<length):
        print('前 %f m为层流，后面为湍流\n按混合边界层计算摩擦阻力系数\nA:%f'%(Xcr,A))
        return ((0.074/Re**(1/5))-A/Re)

    if(Xcr<=0.05*length):
        print('全为湍流，按湍流计算摩擦阻力系数')
        return 0.072/Re**(1/5)

    else:
        print('全为层流，按层流计算摩擦阻力系数')
        return 1.462/Re**(1/2)

#def cf_ceng(Re):#层流边界层摩擦系数
#    return 1.462/Re**(1/2)

#def cf_hunhe(Re,A):#混合边界层摩擦系数
#    return ((0.074/Re**(1/5))-A/Re)

#def cf_tuan(Re):#湍流边界层摩擦系数
#    return 0.072/Re**(1/5)

def A_hun(recr):#混合边界层中的A
    return 0.074*recr**(4/5)-1.328*recr**(1/2)

def rf_double_or_not(cf,p,v,b,l):#p:流体密度 v:拖曳速度 b:平板宽度 l:平板长度
    cho=input('单面输入1\n双面输入2\n')
    if cho=='1':
        return cf*p*(v**2)*b*l*(1/2)
    else:
        return cf*p*(v**2)*b*l

def cal_Rf(l,b,v,u,p,recr):#主程序 l:平板长度（拖曳方向长度） b:平板宽度 v:平板拖曳速度 p:流体密度 A
    xcr=Xcr(recr,u,v)
    re=Re(v,l,u)
    A=A_hun(recr)
    print('Xcr: %f'%xcr)
    print('Re: %f'%re)
    cf=cf_ceng_or_tuan(xcr,l,re,A)
    print('Cf: %f'%cf)
    rf=rf_double_or_not(cf,p,v,b,l)
    print('Rf: %f N'%rf)

#长度 宽度 速度 运动粘度 密度 临界雷诺数  6
cal_Rf(2,2.25,4,1.139*10**-6,1000,10**6)
