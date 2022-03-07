#1957年国际船模试验会议实船-船模换算公式 ITTC
#用于船模与实船之间的阻力转换
#Cf=0.075/(lgRe-2)^2
#math.log(a,b)---logb a

import math

def ittc(re):#input re
    return 0.075/(math.log(re,10)-2)**2

print(ittc(120.0))
