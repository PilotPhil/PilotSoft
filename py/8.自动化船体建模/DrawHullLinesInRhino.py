# -*- coding: utf-8 -*-
import xlrd
import xdrlib
import sys
import rhinoscriptsyntax as rs


workBook=xlrd.open_workbook("点数据.xls")
workSheet=workBook.sheets()[0]
nrows=workSheet.nrows # 行数
ncols=workSheet.ncols # 列数

# 生成原始线
series=[]*3
curves=[]
for i in range(0,nrows):
    if workSheet.cell(i,0).value=='': # 空单元格
        #rs.AddInterpCurve(series) # 内插点曲线
        cur=rs.AddCurve(series) # 控制点曲线
        curves.append(cur)
        
        series=[]*3
    else:
        x=float(workSheet.cell(i,0).value)
        y=float(workSheet.cell(i,1).value)
        z=float(workSheet.cell(i,2).value)
        series.append([x,y,z])        

curvesCopy=rs.CopyObjects(curves,[10000,0,0])

for i in curvesCopy:
    rs.RebuildCurve(i,9,21)

print(curvesCopy)

surface=rs.AddLoftSrf(curvesCopy,loft_type=0)


#objs = rs.GetObjects("选取线放样", rs.filter.curve)
#if objs: 
#    rs.AddLoftSrf(objs)




