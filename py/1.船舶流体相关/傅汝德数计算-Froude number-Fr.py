# Fr=V/(g*L)^(1/2)
# V:船速 g:重力加速度 L:船厂
# 1Knot=0.51444m/s=1.852km/h
# 界定 低速船：Fr<0.18
#     中速船：0.18<Fr<0.30
#     高速船：Fr>0.30


def Fr(v,l):# input velicioty &  length  return Fr(float)
    print("if 'knot' press '0' \nif 'm\s'  press '1' \nif 'km\h' press '2'")
    cho=input()#返回string类型
    if cho=='0':
        return (v*0.5144) / (9.8 * l) ** (1 / 2)
    if cho=='1':
        return v / (9.8 * l) ** (1 / 2)
    else:
        return (1000*v)/(60*60) / (09.8 * l) ** (1 / 2)
    
    
temp = Fr(12,115)

if temp<=0.18:
    print('low speed\nthe Fr of the ship is: %f' % temp)
if 0.18<temp<=0.3:
    print('medium speed\nthe Fr of the ship is: %f' % temp)
else:
    print('high speed\nthe Fr of the ship is: %f' % temp)
