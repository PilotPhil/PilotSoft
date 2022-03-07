# -*- coding: utf-8 -*-
import rhinoscriptsyntax as rs
import sys


class AutoMove:
    # 数据成员
    LOA = 0  # 船总长
    LPP = 0  # 船垂线间长
    Num = 0  # 站号数目
    Trans = []
    Objects = []

    def __init__(self):
        pass

    def SetParams(self, LPP=129, Num=20):
        self.LPP = LPP * 1000
        self.Num = Num
        print("垂线间长：%f" % self.LPP)
        print("站数：%d" % self.Num)

    def GenerateDistance(self):
        step = self.LPP / self.Num
        for i in range(0, 21):
            self.Trans.append((i * step, 0, 0))
        print(self.Trans)

    def SelectObjects(self):
        for i in range(0, self.Num + 1):
            ID = rs.GetObjects("选择要移动的第【%d】站曲线" % i)
            self.Objects.append(ID)
        print(self.Objects)

    def MultiMove(self):
        for i in range(0, self.Num + 1):
            rs.MoveObject(self.Objects[i], self.Trans[i])

    def HalfSite(self):
        ID = rs.GetObjects("选择要移动的半站曲线")
        it = rs.GetPoint("选择被移动物体的参考点")
        start = rs.GetPoint("选择前一站位参考点")
        end = rs.GetPoint("选择后一站位参考点")
        it[1] = it[2] = start[1] = start[2] = end[1] = end[2] = 0
        tr = (start - it) + 0.5 * (end + start) - start
        rs.MoveObject(ID, tr)

    def FreeMove(self):
        ID = rs.GetObjects("选择要移动的曲线")
        it = rs.GetPoint("选择被移动物体的参考点")
        start = rs.GetPoint("选择前一站位参考点")
        it[1] = it[2] = start[1] = start[2] = 0
        distance = rs.GetString("输入距离")
        tr = start - it
        tr[0] += float(distance)
        rs.MoveObject(ID, tr)


def main():
    test = AutoMove()
    LPP = rs.GetString("输入船的【垂线间长】(单位m)")
    Num = rs.GetString("输入站号数量", "20")

    if float(LPP) > 0 and int(Num) > 0:
        test.SetParams(float(LPP), int(Num))

        while 1:
            mood = rs.GetString("选择模式：【1:整数站移动】  【2:半站移动】   【3:自定义相对移动】  【4:重建曲线并放样】  【E:退出】")  # 交互确定移动模式

            if mood == '1':
                test.GenerateDistance()
                test.SelectObjects()
                test.MultiMove()
            elif mood == '2':
                test.HalfSite()
            elif mood == '3':
                test.FreeMove()
            elif mood == '4':
                pass
            elif mood == 'e' or mood == 'E':
                break

    else:
        print("输入的垂线间长【%f】或站数【%d】不符合要求" % (float(LPP), int(Num)))
        main()


if __name__ == '__main__':
    main()
