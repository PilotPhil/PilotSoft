```c#
public class PID                        // PID类
{
    public float target;                // 控制的目标值
    public float measurement;           // 系统测量值

    public float P;                     // P参数
    public float I;                     // I参数
    public float D;                     // D参数

    public float differ;                // 误差的差分
    public float error;                 // 误差
    public float preError;              // 上一次误差
    public float integral;              // 积分

    public float Pout;                  // P输出
    public float Iout;                  // I输出
    public float Dout;                  // D输出
    public float AllOut;                // 总输出

    public float control()              // 迭代控制函数
    {
        error = target - measurement;   // 求误差
        differ = error - preError;      // 差分

        Pout = P * error;
        Iout = I * integral;
        Dout = D * differ;

        integral += error;              // 求积分
        preError = error;               // 迭代

        AllOut = Pout + Iout + Dout;    // 总输出
        return AllOut;                  // 返回
    }
}


```