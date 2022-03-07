# -*- coding: utf-8 -*-
"""
-------------------------------------------------
   文件名：      
   描述：       
   作者：       Pilot.Phil
   日期：       Wed Aug 12 10:16:07 2020
-------------------------------------------------

----------------------使用-----------------------
S=mPMspec(w,Hs,T1,pf)           # 生成波浪谱
al,ar=lrinter(w,S,pf)           # 全局积分
id=parts(al,ar,stat,stop,pf)    # 按面积等分

-------------------------------------------------
#-----------------xxxxxxxxxxxxxx-----------------#
"""

import numpy as np
import scipy as sp
import matplotlib
from matplotlib import pyplot as plt
matplotlib.rcParams['font.family'] = 'SimHei'




#-----------------ITTC-Modified PM Spec-----------------#
def mPMspec(w,Hs,T1,pf):
    # w：频率
    # Hs：有义波高
    # T1：海浪特征周期
    # pf：是否绘图
    
    A=173*Hs**2/T1**4
    B=691/T1**4
    S=A*w**(-5)*np.exp(-B/w**4)
    
    if pf==True:
        plt.figure()
        plt.plot(w,S,'b-')
        plt.title("ITTC-Modified PM Spectrum")
        plt.xlabel("w rad/s")
        plt.ylabel("S(w) m^2 s")
        
        str='Hs=%.2fm\nT1=%.2fs'%(Hs,T1)
        plt.legend([str])
    else:
        pass

    return S

#----------------------全局积分数据----------------------#
def lrinter(w,S,pf):
    # w：频率范围
    # S：海浪谱
    
    L=w.size        # 长度
    
    al=np.array([]) # 自左向右面积
    for i in np.linspace(1,L,L,endpoint=True,dtype="int"):
        tem=np.trapz(S[0:i],w[0:i]) # 梯形法
        al=np.append(al,tem)
    
    ar=np.array([]) # 自右向左面积
    for j in np.linspace(L-1,0,L,endpoint=True,dtype="int"):
        tem=np.trapz(S[j:L],w[j:L])
        ar=np.append(ar,tem)
    
    ar=np.flip(ar)  # 翻转
    
    if pf==True:
        er=np.abs(al-ar)
        id=np.argmin(er) # 等分点索引
        str='w=%.6f'%w[id]
        
        plt.figure()
        plt.plot(w,al,'b')
        plt.plot(w,ar,'r')
        plt.title("全局积分")
        plt.xlabel("w rad/s")
        plt.ylabel("Aera")
        plt.legend(['自左向右面积','自右向左面积'])
        plt.text(w[id],S[id],str)
    else:
        pass
        
    return al,ar

#----------------------按索引求面积----------------------#
def aera(al,ar,stat,stop):
    # al：自左向右面积
    # ar：自右向左面积
    # stat：起始点索引
    # stop：终止点索引
    
    A=al[stop]-al[stat]
    return A
#---------------------单次按面积等分---------------------#
def parts(al,ar,stat,stop,pf):
    # al：自左向右面积
    # ar：自右向左面积
    # stat：起始点索引
    # stop：终止点索引
    # pf：是否画图
    
    a=al[stat:stop]
    a=a-a[0]
    
    b=ar[stat:stop]
    b=b-b[-1]
    
    er=np.abs(a-b)
    id=np.argmin(er)
    id=id+stat # 注意加上起始点索引
    pw=w[id] # 等分点 频率
    
    if pf==True:
        str='w=%.6f'%pw
        
        plt.figure()
        plt.plot(w[stat:stop],a,'b')
        plt.plot(w[stat:stop],b,'r')
        plt.title("面积等分")
        plt.xlabel("w rad/s")
        plt.ylabel("Aera")
        plt.legend(['自左向右面积','自右向左面积'])
        plt.text(w[id],al[id],str)
    else:
        pass
    
    return id

#---------------------全局按面积等分---------------------#
def aparts(w,N,al,ar):
    # w：频率
    # N：等分数2^4
    
    pid=np.array([0,w.size-1]) # 存储等分点索引

    for i in np.linspace(1,N,N,endpoint=True,dtype="int"):
        L=pid.size
        for j in np.linspace(0,L-2,L-1,endpoint=True,dtype="int"):
            id=parts(al, ar, pid[j], pid[j+1], False)
            pid=np.append(pid,id)
            
        pid=np.sort(pid) # 从小到大排序
        
    # wp=w[pid] # 从索引恢复频率
    
    
    return pid

#-------------------------测试--------------------------#



#-------------------------测试--------------------------#
if __name__ == "__main__":
    # Step1:选择合适的波谱---ITTC-Modified Pierson-Moskowitz (Hs,T1)
    Hs=1.8 # 有义波高
    T1=2   # 海浪特征周期
    w=np.arange(1.5,8.501,0.001)
    S=mPMspec(w, Hs, T1, True) 
    
    # Step2.等能量划分频段
    al,ar=lrinter(w,S,True) # 全局积分数据 零阶矩
    pid=aparts(w,5,al,ar)
    

    # Step3.确定谐波频率---海浪普的一阶矩比零阶矩
    alw,arw=lrinter(w,S*w,False) # 全局积分数据 一阶矩
    
    zom=np.array([]) # 零阶矩
    for i in np.linspace(0,pid.size-2,pid.size-1,endpoint=True,dtype="int"):
        tem=aera(al, ar, pid[i], pid[i+1])
        zom=np.append(zom,tem)
    
    oom=np.array([]) # 一阶矩
    for i in np.linspace(0,pid.size-2,pid.size-1,endpoint=True,dtype="int"):
        tem=aera(alw, arw, pid[i], pid[i+1])
        oom=np.append(oom,tem)
    
    rw=oom/zom # 真实频率
    
    # Step4.确定各谐波波幅
    amp=(2*zom)**0.5
    
    # Step5.确定初始相位---随机数[0~2pi]
    iP=2*np.pi*np.random.rand(amp.size)
    
    # Step6.1.固定空间点仿真x=1
    g=0.98
    k=rw**2/g
    x=1
    
    t=np.linspace(1,1000,10000,endpoint=True,dtype="int")
    t=t.reshape(10000,1)
    H=amp*np.cos(k*x-rw*t+iP)
    H1=np.sum(H,axis=1)
    
    plt.figure()
    plt.plot(t,H1)
    
    # Step6.2.固定时间点仿真t=1
    t=1
    x=np.linspace(1,1000,10000,endpoint=True,dtype="int")
    x=x.reshape(10000,1)
    H=H=amp*np.cos(k*x-rw*t+iP)
    H2=np.sum(H,axis=1)
    
    plt.figure()
    plt.plot(x,H2)
    
    
    
    
    
    
    
    
    



