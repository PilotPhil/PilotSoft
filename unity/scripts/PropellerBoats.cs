using UnityEngine;
using UnityEditor;

public class PropellerBoats : MonoBehaviour
{
  public Transform[] propellers;// 传入推进器，可能有多个？
  public Transform[] rudder;// 传入舵，可能有多个？
  private Rigidbody rb;// 传入船体

  public float engine_rpm { get; private set; }// 引擎转速
  float throttle;// 油门
  int direction = 1;

  public float propellers_constant = 0.6F;
  public float engine_max_rpm = 600.0F;// 引擎最大转速
  public float acceleration_cst = 1.0F;
  public float drag = 0.01F;

  float angle;// 舵的角度

  void Awake()
  {
    engine_rpm = 0F;// 初始引擎转速为0
    throttle = 0F;// 初始油门为0
    rb = GetComponent<Rigidbody>();// 传入刚体性质的船体
  }

  void Update()
  {
    float frame_rpm = engine_rpm * Time.deltaTime;// 每一帧的转速？在update中执行，要乘以deltatime

    for (int i = 0; i < propellers.Length; i++)// 针对每一个推进器，循环
    {
      // 每个推进器的局部旋转=和每帧转速相关的一个四元数？
      propellers[i].localRotation = Quaternion.Euler(propellers[i].localRotation.eulerAngles + new Vector3(0, 0, -frame_rpm));
      // 在船体上某处施加力？
      rb.AddForceAtPosition(Quaternion.Euler(0, angle, 0) * propellers[i].forward * propellers_constant * engine_rpm, propellers[i].position);
    }

    throttle *= (1.0F - drag * 0.001F);

    engine_rpm = throttle * engine_max_rpm * direction;

    angle = Mathf.Lerp(angle, 0.0F, 0.02F);// 线性插值函数Lerp (from : float, to : float, t : float)基于浮点数t返回a到b之间的插值，t限制在0～1之间。当t = 0返回from，当t = 1 返回to。当t = 0.5 返回from和to的平均值。
    
    for (int i = 0; i < rudder.Length; i++)// 针对每一个舵，使其旋转
    {
        rudder[i].localRotation = Quaternion.Euler(0, angle, 0);
    }
  }

  public void ThrottleUp()// 加大油门---相当于一个百分数
  {
    throttle += acceleration_cst * 0.001F;// 油门自加
    if (throttle > 1)
      throttle = 1;
  }

  public void ThrottleDown()// 减小油门
  {
    throttle -= acceleration_cst * 0.001F;// 油门自减
    if (throttle < 0)
      throttle = 0;
  }

  public void Brake()// 刹车
  {
    throttle *= 0.9F;// 刹车为啥油门乘以90%？？？
  }

  public void Reverse()// 调头
  {
    direction *= -1;// 逆转方向
  }

  public void RudderRight()// 舵向右边摆
  {
    angle -= 0.9F;
    angle = Mathf.Clamp(angle, -90F, 90F);// 限定舵只能在-90~90度之间。clamp(x,low,high )若X在[low,high]范围内，则等于X；如果X小于low，则返回low；如果X大于high，则返回high。
  }

  public void RudderLeft()// 舵向左边摆
  {
    angle += 0.9F;
    angle = Mathf.Clamp(angle, -90F, 90F);
  }

  void OnDrawGizmos()
  {
    Handles.Label(propellers[0].position, engine_rpm.ToString());// 将引擎转速显示在label上
  }
}
