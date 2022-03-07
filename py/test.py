# -*- coding: utf-8 -*-

import sys
sys.path.append(r"D:/★Repo/pyRepo/7.频谱分析")

import numpy as np
import spec
import matplotlib
from matplotlib import pyplot as plt

data=np.loadtxt("data2.txt")
plt.figure()
plt.plot(data)


spec.saft(data,20,True)

