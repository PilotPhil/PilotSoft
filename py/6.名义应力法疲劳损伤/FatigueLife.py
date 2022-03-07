# -*- coding: utf-8 -*-
"""
-------------------------------------------------
   文件名：     life
   描述：       疲劳损伤寿命计算
   作者：       Pilot.Phil
   日期：       Tue Aug 11 23:14:37 2020
-------------------------------------------------

----------------------使用-----------------------
pv,id=findpv(iss,False)         # 峰谷点
re=seqadj(pv,False)             # 载荷历程调整
co=count4p(re,False)            # 四点法循环提取
sr=goodman(co[:,1],co[:,2],235) # 经过goodman修正的应力幅值
di=distribute(sr,2,True)        # 分布统计
dm=damage(sr,1)                 # 损伤统计
-------------------------------------------------
"""
import warnings
warnings.filterwarnings("ignore")
import myweibull
import matplotlib
import numpy as np
from matplotlib import pyplot as plt
matplotlib.rcParams['font.family'] = 'SimHei'

#----------------------寻找峰谷点----------------------#
def findpv(X,pf):
    # X 载荷序列
    # pf 是否绘图
    
    copy1=X[0:-1] # 序列的拷贝1
    copy2=X[1:] # 序列的拷贝2
    
    # Step1.第一次差分运算
    dif1=copy2-copy1 
    
    # Step2.取符号运算
    dif1[dif1>0]=1
    dif1[dif1<0]=-1
    
    # Step3.反向遍历取符号运算
    tem=dif1
    n=np.size(tem)-2
    for i in np.linspace(n,0,n+1,dtype=int):
        if tem[i]==0 and tem[i+1]>=0:
            tem[i]=1
        elif tem[i]==0 and tem[i+1]<0:
            tem[i]=-1
        else:
            pass
    
    # Step4.第二次差分
    copy3=tem[0:-1]
    copy4=tem[1:]
    dif2=copy4-copy3
    
    # Step5.首尾处理
    a=X[0]
    b=X[1]
    c=X[-2]
    d=X[-1]
    
    dif2=np.insert(dif2,0,b-a)
    dif2=np.append(dif2,c-d)
    
    # Step6.取符号运算
    dif2[dif2>0]=1
    dif2[dif2<0]=-1
    dif2[dif2==0]=0
    dif2=-1*dif2 # 相反数 重要
    
    # Step7.结束
    id=dif2 # 峰谷标识 1:峰 -1:谷 0:非
    PV=X[id!=0] # 峰谷点
    
    id2=np.argwhere(id!=0)+1
    
    # Step.plot 绘图
    if pf==True:
        plt.figure()
        plt.plot(np.arange(1,X.size+1),X,'r-')
        plt.plot(id2,PV,':bx')
        plt.title("寻找峰谷点")
        plt.xlabel("序列")
        plt.ylabel("载荷")
        plt.show()
    else:
        pass

    return PV,id # 返回峰谷点、峰谷标识

#---------------------载荷历程调整---------------------#
def seqadj(X,pf):
    # X 载荷序列
    # pf 是否绘图
    
    # Step1.判断峰谷点总数是否为奇数
    L=X.size
    if L%2==0:
        X=np.delete(X,L-1)
        
    # Step2.首尾取值处理
    if X[0]>X[1]: # 若首尾均为 峰
        tem=max(X[0],X[-1])
        X[0]=tem
        X[-1]=tem
    elif X[0]<X[1]: # 首尾均为 谷
        tem=min(X[0],X[-1])
        X[0]=tem
        X[-1]=tem
    else:
        pass
    
    # Step3.从载荷荷绝对值最大的点处将载荷时间历程切开，将左段的末点与右段的起点连接
    tem2=np.abs(X)
    i=np.argmax(tem2)
    s1=X[0:i+1] # 0~i
    s2=X[i:-1] # i~end-1
    res=np.concatenate((s2,s1)) # 连接数组
    
    # Step.plot 绘图
    if pf==True:
        plt.figure()
        plt.plot(np.arange(1,res.size+1),res,'b-')
        plt.title("载荷历程调整")
        plt.xlabel("序列")
        plt.ylabel("载荷")
        plt.show()
    else:
        pass
    
    return res # 返回调整后载荷序列

#--------------------四点法判定条件--------------------#
def P4C(a,b,c,d):
    s1=abs(a-b)
    s2=abs(b-c)
    s3=abs(c-d)
    
    if s1>=s2 and s2<=s3:
        flag=True
        me=0.5*(b+c) # 均值
        ra=0.5*abs(b-c) # 幅值
    else:
        flag=False
        me=0
        ra=0
    return flag,me,ra # 返回 判断标志 均值 幅值

#--------------------四点法循环提取--------------------#
def count4p(X,pf):
    # X 载荷序列
    # pf 是否打印
    
    next=X
    L=X.size
    i=0
    j=1
    
    mean=np.asarray([])            # 均值
    rang=np.asarray([])            # 幅值
    start=np.asarray([],dtype=int) # 起始位置
    stop=np.asarray([],dtype=int)  # 终止位置
    used=np.asarray([],dtype=int)  # 被使用过的点
    
    while L>3:
        while j<=L-3:
            flag,me,ra=P4C(next[i],next[j],next[j+1],next[j+2])
            
            if flag==True:
                mean=np.append(mean,me)
                rang=np.append(rang,ra)
                start=np.append(start,i)
                stop=np.append(stop,j+2)
                used=np.append(used,j)
                used=np.append(used,j+1)
                
                j=j+2
            else:
                i=j
                j=j+1
        
        next=np.delete(next,used)
        used=np.asarray([],dtype=int) # 恢复空状态
        L=next.size
        i=0
        j=1
        
    l=mean.size
    cycle=np.ones([l,1],dtype=int)
    mean=np.reshape(mean,[l,1])
    rang=np.reshape(rang,[l,1])
    start=np.reshape(start,[l,1])
    stop=np.reshape(stop,[l,1])
    
    re=np.concatenate((cycle,rang,mean,start,stop),axis=1)
    
    if pf==True:
        d=["次数","幅值","均值","起始","结束"]
        d=np.asarray(d).reshape(1,5)
        d=np.concatenate((d,re))
        
        n=d.shape[1]
        m=re.shape[0]
        
        for j in np.arange(0,n):
            print(d[0,j]+'\t\t',end='')
        print()
        
        for i in np.arange(0,m):
            for j in np.arange(0,n):
                print('%.2f\t'%re[i,j],end='')
               
            print()
                    
    return re

#-----------------Goodman平均应力修正------------------#
def goodman(rang,mean,Su):
    S=2*Su*rang/(Su-mean)
    return S

#---------------------应力分布统计---------------------#
def distribute(X,step,pf):

    # step=2 # buchang
    st=np.max(X)
    st=np.ceil(st)+step
    axis=np.arange(0,st,step)
    cot=[]
    cot=np.asarray(cot)
    
    for i in np.arange(0,axis.size-1):
        tem=X[np.logical_and(X>=axis[i],X<axis[i+1])]
        cot=np.append(cot,tem.size)  
    
    # print('x总数：%d'%X.size)
    # print('总数：%d'%np.sum(cot))
    
    if pf==True:
        plt.figure()
        plt.bar(np.arange(0,axis.size-1),cot)
        plt.title("应力统计分布")
        plt.xlabel("应力值序列")
        plt.ylabel("次数")
    else:
        pass
    
    return cot

#---------------------线性疲劳损伤---------------------#
def damage(X,i):
    K=np.array([5.8E12,3.464E12,1.52E12,1.026E12,6.319E11,4.33E11,2.481E11,9.279E10])
    Nmax=np.log10(K[i])-3*np.log10(X)
    Nmax=np.power(10,Nmax)
    tem=X/Nmax
    Dam=np.sum(tem)
    
    return Dam


#-------------------------测试-------------------------#
if __name__ == "__main__":
    
    c=np.random.rand(10000)
    n=6.02
    k=0.98
    iss=myweibull.icdf(c, n, k)
    plt.figure()
    plt.plot(np.arange(1,1e4+1),iss,'b')
    plt.title("载荷序列")
    
    pv,id=findpv(iss,True)         # 提取峰谷点
    re=seqadj(pv,True)             # 载荷历程调整
    co=count4p(re,True)            # 四点法循环提取
    sr=goodman(co[:,1],co[:,2],235) # 经过goodman修正的应力幅值
    di=distribute(sr,2,True)        # 分布统计个数
    dm=damage(sr,1)                 # 损伤统计
    
    dm100=dm*100                    # 百分比
    print('损伤度%.7f%%'%dm100)