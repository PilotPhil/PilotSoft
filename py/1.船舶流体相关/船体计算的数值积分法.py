#在无法得知船体型线情况下计算
#包含 梯形法 辛式一法（141法） 辛式二法（1331法


#梯形法 传入 总长  纵坐标值
def txf(L,Y=[]):
    A=0.0
    factor=[1/2,1/2]
    for i in range(len(Y)):#首尾固定系数1/2，非 插入系数 1
        if 0<i<len(Y):
            factor.insert(i,1)#插入1
            Y[i]*=factor[i]#乘以系数
        else:
            pass
    for i in range(len(Y)):#累加
        A+=Y[i]

    return L*A/len(Y)


#辛式一法（141法） 传入 总长 纵坐标list  等分数目为 偶数时才能用
def SM_1(L,Y=[]):
    if len(Y)%2==0:
        print('等分数目为偶数时才能用辛式一法')
        return 0
    else:
        factor = [1, 1]
        A = 0.0
        B = 0.0
        #print(Y)
        for i in range(len(Y)):  # 首尾固定系数1，非 奇数插入系数4 偶数插入2
            if 0 < i < len(Y):
                if i % 2 == 0:
                    factor.insert(i, 2)
                    Y[i] *= factor[i]
                else:
                    factor.insert(i, 4)
                    Y[i] *= factor[i]
            else:
                pass

        for i in range(len(Y)):
            A += Y[i]
            B += factor[i]

        return L * A / B


#辛式二法（1331法） 传入 总长 纵坐标list  等分数目为 奇数时才能用
def SM_2(l,Y=[]):
    if len(Y) % 2 == 0:
        factor = [1, 1]
        A = 0.0
        B = 0.0
        #print(Y)
        for i in range(len(Y)):#首尾固定 1 中间先全插 3 遇到3的倍数的替换为 2
            if 0<i<len(Y):
                factor.insert(i, 3)
            else:
                pass
        for i in range(len(Y)):
            if i!=0 and i % 3 == 0:
                factor[i] = 2
            else:
                pass
            A+=Y[i]*factor[i]
            B+=factor[i]

        return l * A / B

    else:
        print('等分数目为奇数时才能用辛式二法')


#辛式二法（1331法） 传入 总长 纵坐标list  等分数目为 奇数时才能用

print('用梯形法计算结果为:%f'%txf(220,[0,6.3,8.6,9.2,9.4,9,8.1,6.7,4.6,2.4,0.2]))
print('用辛式一法计算结果为:%f'%SM_1(220,[0,6.3,8.6,9.2,9.4,9,8.1,6.7,4.6,2.4,0.2]))
print('用辛式二法计算结果为:%f'%SM_2(220,[0,6.3,8.6,9.2,0,9.4,9,8.1,6.7,4.6,2.4,0.2]))
