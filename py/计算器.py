# -*- coding: utf-8 -*-
"""
-------------------------------------------------
   文件名：      
   描述：       
   作者：       Pilot.Phil
   日期：       Wed Aug 12 20:54:58 2020
-------------------------------------------------

----------------------使用-----------------------

-------------------------------------------------
#-----------------xxxxxxxxxxxxxx-----------------#
"""

import numpy as np
import scipy as sp
import matplotlib
from matplotlib import pyplot as plt
matplotlib.rcParams['font.family'] = 'SimHei'



def dynamic(s,w):
    # 上升时间tr：
    tr=(np.pi-np.arccos(s))/(w*(1-s**2)**0.5)
    print("上升时间tr：%.3fs"%tr)
    
    # 峰值时间tp：
    tp=np.pi/(w*(1-s**2)**0.5)
    print("峰值时间tp：%.3fs"%tp)

    # 超调量p：
    p=np.exp((-1*np.pi*s)/(1-s**2)**0.5)
    print("超调量p：%.3f%%"%(p*100))

    # 调节时间ts：
    ts1=3.5/(s*w)
    ts2=4.4/(s*w)
    print("调节时间ts1：%.3fs,%.3fs"%(ts1,ts2))
    
    





#---------------------测试-----------------------#
if __name__ == "__main__":
    dynamic(0.1732,1.732)
     
