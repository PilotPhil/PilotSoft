import turtle

turtle.screensize(270,480,'white')#背景设置

turtle.pensize(1)
turtle.color('red')

turtle.penup()
turtle.left(90)#向上
turtle.goto(0,120)
turtle.left(90)#向左
turtle.pendown()

turtle.fillcolor('red')
turtle.begin_fill()####

turtle.goto(-120,120)

turtle.circle(120,90)#1
turtle.goto(-240,-240)

turtle.circle(120,90)#2
turtle.goto(190,-360)

turtle.circle(120,90)#3
turtle.goto(310,0)

turtle.circle(120,90)#4
turtle.goto(0,120)

turtle.end_fill()####

turtle.penup()#抬刀 回零
turtle.goto(0,0)
turtle.pendown()

turtle.pensize(25)

turtle.color('white')

turtle.left(180)

turtle.right(160)#笔头顺旋转160度

turtle.circle(140,155)#画圆

turtle.circle(120,90)

for i in range(100,60,-20):
    turtle.circle(i,90)

turtle.circle(40,180)

turtle.goto(35,5)

turtle.circle(-40,150)


turtle.done()
