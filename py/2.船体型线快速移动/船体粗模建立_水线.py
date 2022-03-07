# -*- coding: utf-8 -*-
import rhinoscriptsyntax as rs
import sys


class AutoMove:
    # 数据成员
    spacing = 0  # 水线间距
    Num = 0  # 等距水线个数
    Trans = []
    Objects = []

    def __init__(self):
        pass

    def SetParams(self, spacing=1000, Num=20):
        self.spacing = spacing
        self.Num = Num
        print("水线间距：%f" % self.spacing)
        print("等距水线个数：%d" % self.Num)

    def GenerateDistance(self):
        for i in range(0, self.Num):
            self.Trans.append((0, 0, i * self.spacing))
        print(self.Trans)

    def SelectObjects(self):
        for i in range(0, self.Num):
            ID = rs.GetObjects("选择要移动的第【%d】条水线" % i)
            self.Objects.append(ID)
        print(self.Objects)

    def MultiMove(self):
        for i in range(0, self.Num):
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
    spacing = rs.GetString("输入等距的【水线间距】(单位mm)")
    Num = rs.GetString("输入水线数量 包括基线", "20")

    if float(spacing) > 0 and int(Num) > 0:
        test.SetParams(float(spacing), int(Num))

        while 1:

            mood = rs.GetString("选择模式：【1:整数站移动】  【E:退出】")

            if mood == '1':
                test.GenerateDistance()
                test.SelectObjects()
                test.MultiMove()

            elif mood == 'E' or mood == 'e':
                break

    else:
        print("输入的垂线间长【%f】或站数【%d】不符合要求" % (float(spacing), int(Num)))
        main()


if __name__ == '__main__':
    main()
