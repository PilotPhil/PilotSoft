# -*- coding: utf-8 -*-
"""
-------------------------------------------------
   文件名：      
   描述：       
   作者：       Pilot.Phil
   日期：       Thu Aug 13 22:22:35 2020
-------------------------------------------------

----------------------使用-----------------------

-------------------------------------------------
#-----------------xxxxxxxxxxxxxx-----------------#
"""

import xlrd
import xlwt
import numpy as np
import scipy as sp
import matplotlib
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
matplotlib.rcParams['font.family'] = 'SimHei'
 
#-----------------从表格复制指定页的数据-----------------#
def copyData(name,sheetIndex):
    xls = xlrd.open_workbook(name) # 打开表格name  xxx.xlsx
    table = xls.sheets()[sheetIndex] # 打开某张表
    nrows = table.nrows # 行数
    ncols = table.ncols # 列数
    
    data=np.zeros([nrows,ncols],dtype="float")
    
    for i in range(0,nrows): # 将表格读取到数组
        for j in range(0,ncols):
            rawVal=table.cell(i, j).value 
            if isinstance(rawVal,str)==True: # 空单元格其实是空字符串 如果是字符串
                data[i,j]=np.nan
            else:
                data[i,j]=float(rawVal)
    
    return data # 返回表格中数据

#--------------------封装的三维散点图-------------------#
def scatter3D(points):
    x = points[:, 0]  
    y = points[:, 1]  
    z = points[:, 2]  
        
    # 绘制散点图
    fig = plt.figure()
    ax = Axes3D(fig)
    ax.scatter(x, y, z)
    
    # 添加坐标轴(顺序是Z, Y, X)
    ax.set_zlabel('Z', fontdict={'size': 15, 'color': 'red'})
    ax.set_ylabel('Y', fontdict={'size': 15, 'color': 'red'})
    ax.set_xlabel('X', fontdict={'size': 15, 'color': 'red'})
    plt.title("船左舷（坐标压缩）")
    plt.show()

#------------------第一部分数据点生成-------------------#
def generate1(data):
    wData=data[1:,1:] # 复制半宽值 二维数组
    sData=data[1:,0] # 复制站号*站距
    hData=data[0,1:] # 复制高度值
    
    nrows,ncols=wData.shape # 获取半宽值行列数
    
    Points=np.zeros([nrows*ncols,3],dtype="float")
    
    for i in range(0,nrows):
        for j in range(0,ncols):
            Points[i*ncols+j,0]=wData[i,j]
            Points[i*ncols+j,1]=sData[i]
            Points[i*ncols+j,2]=hData[j]
    
    # 去除nan元素
    s=np.sum(Points,axis=1)
    id=np.argwhere(np.isnan(s))
    Points=np.delete(Points,id,axis=0)
    
    return Points

#------------------第二部分数据点生成-------------------#
def generate2(data):
    # 沿用第一部分生成函数
    # 但需要交换点数组中的半宽和高度数据列
    Points=generate1(data)
    Points[:,[0,2]]=Points[:,[2,0]] # 交换0列与2列
    
    return Points

#------------------第三部分数据点生成-------------------#
def generate3(data):
    sData=data[:,0]
    temp=data[:,1:] # wData 和 hData
    nrows,ncols=temp.shape
    
    wData=temp[:,0:int(ncols/2)]
    hData=temp[:,int(ncols/2):]
    
    nrows,ncols=wData.shape # 重新
    
    Points=np.zeros([nrows*ncols,3],dtype="float")
    
    for i in range(0,nrows):
        for j in range(0,ncols):
            Points[i*ncols+j,0]=wData[i,j]
            Points[i*ncols+j,1]=sData[i]
            Points[i*ncols+j,2]=hData[i,j]

    # 去除nan元素
    s=np.sum(Points,axis=1)
    id=np.argwhere(np.isnan(s))
    Points=np.delete(Points,id,axis=0)
    
    return Points

#---------------------数据点总生成---------------------#
def generatePoints(name):
    data1=copyData(name,0) # 复制数据0
    Points1=generate1(data1)
    
    data2=copyData(name,1) # 复制数据1
    Points2=generate2(data2)
    
    data3=copyData(name,2) # 复制数据2
    Points3=generate3(data3)

    allPoints=np.concatenate((Points1,Points2,Points3),axis=0) # 按行组合
    allPoints=allPoints[allPoints[:,1].argsort(),:] # 按站号排序
    
    return allPoints

#------------------结果写入到excel表格-----------------#
def writeData(allPoints,workBookName):
    workbook=xlwt.Workbook()
    worksheet = workbook.add_sheet("test") # 创建sheet
    
    sData=allPoints[:,1] # 按站号
    sData=np.unique(sData) # 去除重复
    
    L=sData.size

    id=0 # 要写入的表格索引
    
    for r in range(0,L):
        slc=allPoints[allPoints[:,1]==sData[r]] # 被选中的数组部分
        slc=slc[slc[:,2].argsort(),:] # 再次按高度排序（前面已经按站号排序）
        
        nr,nc=slc.shape
        
        for i in range(0,nr):
            worksheet.write(id,0,slc[i,0])
            worksheet.write(id,1,slc[i,1])
            worksheet.write(id,2,slc[i,2])
            
            id+=1
        
        id+=1
        
    workbook.save(workBookName)
    


#---------------------测试-----------------------#
if __name__ == "__main__":
    
    allPoints=generatePoints("改造后型值表.xlsx")    # 从raw.xlsx型值表生成点

    writeData(allPoints,"点数据.xls")               # 写入点数据到points.xls
    
    scatter3D(allPoints)                           # 三维散点图
    
    
    

    
















