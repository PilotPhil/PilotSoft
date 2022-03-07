import turtle
import math#导入数学用于e


#平面进行波的水质点以半径r=Ae**(k*z)作轨圆运动
#水平面上z=0,半径为波幅A
#绘制轨圆变化示意图
def R(A,k,z):
    return A*math.e**(k*z)

for i in range(6):
    if i%2==0:
        turtle.goto(0, -R(1, 1, i + 1))#平移半径距离
        turtle.pensize(3)
        turtle.color('blue')
        turtle.circle(R(1,1,i+1))#画圆
        turtle.goto(0,0)#回到零点
    else:
        turtle.goto(0, -R(1, 1, i+1))
        turtle.pensize(3)
        turtle.color('green')
        turtle.circle(R(1, 1, i+1))
        turtle.goto(0, 0)
