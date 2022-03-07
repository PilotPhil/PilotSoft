# -*- coding: utf-8 -*-
import xlrd
import xdrlib
import sys
import rhinoscriptsyntax as rs


class drawXY_test:
    # 数据成员
    excel = 0  # 打开的excel表格 【兼容模式.xls】
    sheet = 0  # 打开的sheet 必须在第一页上
    rowNum = 0  # 表格行数
    colNum = 0  # 表格列数
    nullNum = 0  # 空单元格数量
    path = 'D:\\test.xls'
    axis_x = 0  # x轴数据的索引
    axis_y = 0  # y轴数据的索引
    vessel_x = 0
    vessel_y = 0
    pointsVessel = 0

    # 成员函数
    # 构造函数
    def __init__(self):
        pass

    # 确定excel路径
    def choosePath(self):
        self.path = rs.OpenFileName()  # 索引表格路径

    # 确定x,y数据索引
    def chooseAxisIndex(self):
        x = rs.GetString('输入X轴的索引', '1')
        y = rs.GetString('输入Y轴的索引', '2')
        if int(x) > self.colNum or int(y) > self.colNum:
            print('【X轴Y轴索引不能超过表格内总列数】 【共%d列】  【重新选择】' % self.colNum)
            self.chooseAxisIndex()
        else:
            self.axis_x = int(x) - 1
            self.axis_y = int(y) - 1



    # 打开excel文件
    def LoadExcel(self):
        try:
            self.excel = xlrd.open_workbook(self.path)
            print('已加载表格文件【%s】' % self.path)
            self.sheet = self.excel.sheet_by_index(0)  # 由索引确定工作表，当只有一个工作表，索引为0
            self.rowNum = self.sheet.nrows  # 工作表行数
            self.colNum = self.sheet.ncols  # 工作表行数
            print('表格有%d行' % self.rowNum)
            print('表格有%d列' % self.colNum)
        except:
            print('无法打开表格文件【%s】【重新选择表格文件】' % self.path)
            self.choosePath()
            self.LoadExcel()

    # 将有空单元格的列切片  sheet-选择行数据还是列数据-选择哪一列、行数据
    def segment(self):
        self.nullNum = 0

        data_x = self.sheet.col_values(self.axis_x)
        data_y = self.sheet.col_values(self.axis_y)

        for i in range(0, self.rowNum):  # 查找空单元格数量
            if data_x[i] == '':
                self.nullNum += 1
        if self.nullNum:
            print('共有%d个空单元格' % self.nullNum)

        self.vessel_x = []
        self.vessel_y = []

        for i in range(0, self.nullNum + 1):  # 分配空间
            self.vessel_x.append([])
            self.vessel_y.append([])

        index = 0
        for i in range(0, self.rowNum):
            if data_x[i] != '':
                self.vessel_x[index].append(data_x[i])
                self.vessel_y[index].append(data_y[i])
            else:
                index += 1

        print('X轴数据集')
        print(self.vessel_x)
        print('Y数据集')
        print(self.vessel_y)

    # 转化为点数据
    # 输入 原始值容器vessel 步长乘数step
    # 输出 分段后的点数据
    def convertToPoints(self):
        self.pointsVessel = []

        if len(self.vessel_x) == len(self.vessel_y):  # x y坐标必须等长
            for i in range(0, len(self.vessel_x)):
                points = []
                index = 0
                if not self.vessel_x[i]:
                    index += 1
                else:
                    temp_x = self.vessel_x[i]
                    temp_y = self.vessel_y[i]

                    for j in range(0, len(temp_x)):
                        points.append((temp_x[j], temp_y[j], 0))
                        index += 1
                    self.pointsVessel.append(points)
            print('组合后')
            print(self.pointsVessel)
        else:
            print('错误：【X Y坐标长度不一致】 【检查表格】')
            sys.exit()  # 直接退出

    # 画曲线
    def drawCurves(self):
        print('pointsVessel len:%d' % len(self.pointsVessel))
        for i in range(0, len(self.pointsVessel)):
            cur = rs.AddCurve(self.pointsVessel[i])
            rs.ObjectColor(cur, (0, 0, 255))


def main():
    print("【Draw XY Lines From Excel To Rhino Is Working】")

    test = drawXY_test()
    test.choosePath()
    test.LoadExcel()  # 读取型值表格

    while 1:
        test.chooseAxisIndex()
        test.segment()  # 获取x轴数据
        test.segment()  # 获取Y轴数据
        test.convertToPoints()  # 转化为点数据
        test.drawCurves()  # 根据点数据画线

        flag = rs.GetString('继续【Y】还是退出【N】', 'Y')  # 交互是否要继续或退出
        if flag == 'N' or flag == 'n':
            break

    print("【Draw XY Lines From Excel To Rhino Exited】")


if __name__ == "__main__":
    main()
