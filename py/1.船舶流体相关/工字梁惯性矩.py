import turtle as t
import math
import easygui as g

#绘图 类似于数控切割方式
def plot(a_1,b_1,a_2,b_2,a_3,b_3):
    t.pensize(4)
    t.color('blue')
    t.speed(20)

    t.penup()
    t.goto(a_2/2,0)
    t.pendown()
    t.left(90)

    t.goto(a_2/2,b_2/2)
    t.right(90)

    t.goto(a_1/2,b_2/2)
    t.left(90)

    t.goto(a_1/2,b_2/2+b_1)
    t.left(90)

    t.goto(-a_1/2,b_2/2+b_1)
    t.left(90)

    t.goto(-a_1/2,b_2/2)
    t.left(90)

    t.goto(-a_2/2,b_2/2)
    t.right(90)

    t.goto(-a_2/2,-b_2/2)
    t.right(90)

    t.goto(-a_3/2,-b_2/2)
    t.left(90)

    t.goto(-a_3/2,-b_2/2-b_3)
    t.left(90)

    t.goto(a_3/2,-b_2/2-b_3)
    t.left(90)

    t.goto(a_3/2,-b_2/2)
    t.left(90)

    t.goto(a_2/2,-b_2/2)
    t.right(90)

    t.goto(a_2/2,0)

   #标距
    t.color('red')
    t.penup()
    t.goto(0,b_2/2+b_1)
    t.pendown()
    t.write('%f'%a_1)

    t.penup()
    t.goto(a_1/2,b_1/2+b_2/2)
    t.pendown()
    t.write('%f'%b_1)

    t.penup()
    t.goto(0,b_2/4)
    t.pendown()
    t.write('%f'%a_2)

    t.penup()
    t.goto(a_2/2,0)
    t.pendown()
    t.write('%f'%b_2)

    t.penup()
    t.goto(a_3/2,-b_2/2-b_3/2)
    t.pendown()
    t.write('%f'%b_3)

    t.penup()
    t.goto(0,-b_2/2-b_3)
    t.pendown()
    t.write('%f'%a_3)

    t.penup()
    t.color('black')
    t.goto(0,-40-b_2/2-b_3)
    t.pendown()
    t.write('形心： %f' % xingxin(a_1, b_1, a_2, b_2, a_3, b_3))
    t.penup()
    t.goto(0,-60-b_2/2-b_3)
    t.pendown()
    t.write('惯性矩： %f' % I_y(a_1, b_1, a_2, b_2, a_3, b_3))
    t.done()

#求形心 单个面积乘以形心纵坐标之和除以总面积
def xingxin(a_1,b_1,a_2,b_2,a_3,b_3):

    s_1=a_1*b_1#面积
    s_2=a_2*b_2
    s_3=a_3*b_3

    y=(s_1*(b_2/2+b_1/2)+s_2*0+s_3*(-b_2/2-b_3/2))/(s_1+s_2+s_3)#形心纵坐标

    return y

#惯性矩求解 平行移轴定理
def I_y(a_1,b_1,a_2,b_2,a_3,b_3):

    I_2=a_2*b_2**3/12#原1

    I_1=a_1*b_1**3/12#原2

    I_3=a_3*b_3**3/12#原3

    I_1_y=I_1+a_1*b_1*((b_2/2+b_1/2)-xingxin(a_1,b_1,a_2,b_2,a_3,b_3))**2#移轴1

    I_2_y=I_2+a_2*b_2*(0-xingxin(a_1,b_1,a_2,b_2,a_3,b_3))**2#移轴2

    I_3_y=I_3+a_3*b_3*((-b_3/2-b_2/2)-xingxin(a_1,b_1,a_2,b_2,a_3,b_3))**2#移轴3


    return I_2_y+I_1_y+I_3_y#和

#主程序
def guanxingjumain():

    try:
        msg = "输入工字梁尺寸"
        title = "工字梁惯性矩计算(默认单位：mm)"

        fieldNames = ["A1:", "B1:", "A2:", "B2:", "A3:", "B3:"]
        fieldValues = []
        fieldValues = g.multenterbox(msg, title, fieldNames)

        a_1 = eval(fieldValues[0])
        b_1 = eval(fieldValues[1])
        a_2 = eval(fieldValues[2])
        b_2 = eval(fieldValues[3])
        a_3 = eval(fieldValues[4])
        b_3 = eval(fieldValues[5])

        out1 = '形心坐标：' + str(xingxin(a_1, b_1, a_2, b_2, a_3, b_3)) + '惯性矩：' + str(I_y(a_1, b_1, a_2, b_2, a_3, b_3))

        choices=g.buttonbox(msg=out1, title=' ', choices=('显示绘图','再次计算', '退出'), image=None)



        if choices=='显示绘图':
            plot(a_1, b_1, a_2, b_2, a_3, b_3)
            guanxingjumain()
        elif choices=='再次计算':
            guanxingjumain()
        else:
            exit()

#异常处理
    except:

        choice=g.buttonbox(msg='ERROR', title='PROGRAMN DEAD', choices=('再次计算', '退出'), image=None)
        if choice=='再次计算':
            guanxingjumain()
        elif choice=='退出':
            exit()
        else:
            exit()


guanxingjumain()
