## 1.USE

```python
findpv(X,pf) # 寻找峰谷点
# X 载荷序列
# pf 是否绘图

seqadj(X,pf) # 载荷历程调整
# X 载荷序列
# pf 是否绘图

P4C(a,b,c,d) # 四点法判定条件
# a,b,c,d 四个数据点

count4p(X,pf) # 四点法循环提取
# X 载荷序列
# pf 是否打印

goodman(rang,mean,Su) # Goodman平均应力修正
# rang 幅值
# mean 均值
# Su 极限应力

distribute(X,step,pf) # 应力分布统计
# X 载荷
# step 跨度

damage(X,i) # 线性疲劳损伤
# X 载荷
# i S-N曲线参数K
```

## 2.Example

```python
c=np.random.rand(10000)
n=6.02
k=0.98
iss=myweibull.icdf(c, n, k)
plt.figure()
plt.plot(np.arange(1,1e4+1),iss,'b')
plt.title("载荷序列")

pv,id=findpv(iss,True)         # 提取峰谷点
re=seqadj(pv,True)             # 载荷历程调整
co=count4p(re,True)            # 四点法循环提取
sr=goodman(co[:,1],co[:,2],235) # 经过goodman修正的应力幅值
di=distribute(sr,2,True)        # 分布统计个数
dm=damage(sr,1)                 # 损伤统计

dm100=dm*100                    # 百分比
print('损伤度%.7f%%'%dm100)
```

## 3.fig

<img src=".\pic\1.svg" width="600" />

<img src=".\pic\2.svg" width="600" />

<img src=".\pic\3.svg" width="600" />

<img src=".\pic\4.svg" width="600" />

<img src=".\pic\5.svg" width="600" />

<img src=".\pic\6.svg" width="600" />