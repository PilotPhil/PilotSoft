## 1.USE

```python
saft(signal,Fs,pf) 
# signal:信号
# Fs：采样率
# pf：是否绘图
```

## 2.Example

```python
x=np.arange(0,1000)*1/100 # 时间向量
signal=30*np.sin(26*x)+15*np.sin(40*x)+40*np.sin(60*x)+60*np.sin(50*x) # 信号    
saft(signal,100,True)
```

## 3.fig

<img src=".\pic\1.svg" width="600" />