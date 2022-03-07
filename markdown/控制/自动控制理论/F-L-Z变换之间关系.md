## 1.连续时间傅里叶变换与拉普拉斯变换之间关系
$$CTFT：\int^{-\infty}_{-\infty}x(t)e^{-j\omega t}dt \tag{1.1}$$
其中$\omega$为一实数

要求时域信号完全可积：

$$\int_{-\infty}^{+\infty}|x(t)|dt<{\infty} \tag{1.2}$$

为了让不符合可积条件的信号也能使用傅里叶变换

给$x(t)$乘以一指数$e^{-\sigma t}$再积分，使其满足可积分条件，即

$$\int_{-\infty}^{\infty}x(t)e^{-j\omega t}e^{-\sigma t}dt$$

即
$$\int_{-\infty}^{\infty}x(t)e^{-(\sigma+j\omega)t}dt \tag{1.3}$$

其中$\sigma+j\omega$为一复数，令$s=\sigma+j\omega$

得拉普拉斯变换：
$$\int^{\infty}_{-\infty}x(t)e^{-st}dt$$

**总结：拉普拉斯变换将频率从实数推广至复数，因此傅里叶变换是拉普拉斯变换的一个特例**

**当$S$为纯虚数时，拉普拉斯变换变为傅里叶变换**

## 2.离散时间傅里叶变换与Z变换之间关系
$$DTFT:\sum_{-\infty}^{\infty}x[n]e^{-j\omega n} \tag{1.4}$$

同样也要满足完全可和的条件，即
$$\sum_{-\infty}^{\infty}|x[t]|<\infty$$

为了让不满足可和条件的信号也能够通过DTFT，乘以一个指数$a^{-n}$再积分,即
$$\sum_{-\infty}^{\infty}x[t]e^{-j\omega n}a^{-n}$$

化简得
$$\sum_{-\infty}^{\infty}x[t]{(ae^{j\omega})}^{-n}$$

其中$ae^{j\omega}$为一极坐标形式的复数，令$z=ae^{j\omega}$，得
$$\sum_{-\infty}^{\infty}x[t]z^{-t} \tag{1.5}$$

即得$z$变换

**总结：$Z$变换将频率从实数推广到复数，DTFT是Z变换的一个特例，当$|Z|=1时$**


