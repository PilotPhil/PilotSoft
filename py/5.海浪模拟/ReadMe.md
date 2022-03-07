## 1.USE

```python
S=mPMspec(w,Hs,T1,pf) # ITTC-Modified PM Spec
# w：频率
# Hs：有义波高
# T1：海浪特征周期
# pf：是否绘图
# S：海浪谱数据

al,ar=lrinter(w,S,pf) # 全局积分数据
# w：频率范围
# S：海浪谱
# al：自左向右面积
# ar：自右向左面积

A=aera(al,ar,stat,stop) # 按索引求面积
# al：自左向右面积
# ar：自右向左面积
# stat：起始点索引
# stop：终止点索引
# A：面积

id=parts(al,ar,stat,stop,pf) # 单次按面积等分
# al：自左向右面积
# ar：自右向左面积
# stat：起始点索引
# stop：终止点索引
# pf：是否画图
# id：面积等分点索引

pid=aparts(w,N,al,ar) # 全局按面积等分
# w：频率
# N：等分数2^4
# al：自左向右面积
# ar：自右向左面积
# pid：等分点索引数组
```

## 2.Example

```python
# Step1.选择合适的海浪谱
Hs=1.8 # 有义波高
T1=2   # 海浪特征周期
S=mPMspec(w, Hs, T1, True) 

# Step2.等能量划分频段
al,ar=lrinter(w,S,True) # 全局积分数据 零阶矩
pid=aparts(w,5,al,ar)


# Step3.确定谐波频率---海浪普的一阶矩比零阶矩
alw,arw=lrinter(w,S*w,False) # 全局积分数据 一阶矩

zom=np.array([]) # 零阶矩
for i in np.linspace(0,pid.size-2,pid.size-1,endpoint=True,dtype="int"):
    tem=aera(al, ar, pid[i], pid[i+1])
    zom=np.append(zom,tem)

    oom=np.array([]) # 一阶矩
    for i in np.linspace(0,pid.size-2,pid.size-1,endpoint=True,dtype="int"):
        tem=aera(alw, arw, pid[i], pid[i+1])
        oom=np.append(oom,tem)

        rw=oom/zom # 真实频率

        # Step4.确定各谐波波幅
        amp=(2*zom)**0.5

        # Step5.确定初始相位---随机数[0~2pi]
        iP=2*np.pi*np.random.rand(amp.size)

        # Step6.1.固定空间点仿真x=1
        g=0.98
        k=rw**2/g
        x=1

        t=np.linspace(1,1000,10000,endpoint=True,dtype="int")
        t=t.reshape(10000,1)
        H=amp*np.cos(k*x-rw*t+iP)
        H1=np.sum(H,axis=1)

        plt.figure()
        plt.plot(t,H1)

        # Step6.2.固定时间点仿真t=1
        t=1
        x=np.linspace(1,1000,10000,endpoint=True,dtype="int")
        x=x.reshape(10000,1)
        H=H=amp*np.cos(k*x-rw*t+iP)
        H2=np.sum(H,axis=1)

        plt.figure()
        plt.plot(x,H2)
```

## 3.fig

<img src=".\pic\1.svg" width="600" />

<img src=".\pic\2.svg" width="600" />

<img src=".\pic\3.svg" width="600" />

<img src=".\pic\4.svg" width="600" />