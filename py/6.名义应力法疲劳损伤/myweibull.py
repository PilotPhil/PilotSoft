# -*- coding: utf-8 -*-
"""
-------------------------------------------------
   文件名：      myweibull
   描述：       自编weibull分布的pdf cdf icdf
   作者：       Pilot.Phil
   日期：       Tue Aug 11 23:18:09 2020
-------------------------------------------------

----------------------使用-----------------------
p=pdf(x,n,k)   # 概率密度函数
c=cdf(x,n,k)   # 累积分布函数
ic=icdf(c,n,k) # 累积分布函数的逆函数
-------------------------------------------------
"""

import matplotlib
import numpy as np
import scipy as sp
from matplotlib import pyplot as plt
matplotlib.rcParams['font.family'] = 'SimHei'

#------------------概率密度函数------------------#
def pdf(x,n,k):
    p=(k/n)*(x/n)**(k-1)*np.exp(-(x/n)**k)
    return p

#------------------累积分布函数------------------#
def cdf(x,n,k):
    c=1-np.exp(-(x/n)**k)
    return c

#--------------累积分布函数的逆函数--------------#
def icdf(c,n,k):
    x=n*np.power(-1*np.log(1-c),1/k)
    return x



#---------------------测试---------------------#
if __name__ == "__main__":
    n=6.02 # 尺度参数
    k=0.98 # 形状参数
    
    
    plt.figure()
    x=np.arange(0.001,31,0.001)
    p=pdf(x,n,k)
    plt.plot(x,p,'b-')
    
    c=cdf(x,n,k)
    plt.plot(x,c,'r-')
    plt.title("pdf & cdf")
    plt.legend(['plt','cdf'])
    
    plt.figure()
    c=np.arange(0.001,1.00,0.001)
    ic=icdf(c, n, k)
    plt.plot(c,ic,'g-')
    plt.title("icdf")
    plt.legend(['icdf'])
    # plt.savefig('basics_python.svg')
