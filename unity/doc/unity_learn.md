## 1.脚本

- 为了连接到 Unity 的内部架构，脚本将实现一个类。每次将脚本组件附加到游戏对象时，都会创建该蓝图定义的对象的新实例。类的名称取自创建文件时提供的名称。类名和文件名必须相同才能使脚本组件附加到游戏对象。
- 在游戏开始之前（即第一次调用 Update 函数之前），Unity 将调用 **Start** 函数；此函数是进行所有初始化的理想位置。
- **Update** 函数是放置代码的地方，用于处理游戏对象的帧更新。这可能包括移动、触发动作和响应用户输入，基本上涉及游戏运行过程中随时间推移而需要处理的任何事项。
- 没有使用构造函数来完成对象的初始化。这是因为对象的构造由编辑器处理，不会像您可能期望的那样在游戏运行过程开始时进行。如果尝试为脚本组件定义构造函数，将会干扰 Unity 的正常运行，并可能导致项目出现重大问题。

- ```Debug.Log("I am alive!")```将消息输出到 Unity 的控制台

- ```C#
  // 在 C# 中，必须将变量声明为 public 才能在 Inspector 中查看该变量。
  public class MainPlayer : MonoBehaviour 
  {
      public string myName;
      void Start () 
      {
          Debug.Log("I am alive and my name is " + myName);
      }
  }
  ```

- **Unity 实际上允许您在游戏运行时更改脚本变量的值。此功能很有用，无需停止和重新启动即可直接查看更改的效果。**


## 2.Awake & Start

Awake():

- 初始化函数，游戏开始时自动调用
- 一般用来创建变量
- **无论脚本是否被激活都能调用**

Start():

- 在所有Awake()运行完，Update()之前执行
- 一般用来给变量赋值
- 只要脚本组件激活时才能调用

## 3.Update & FixedUpdate

Update：

- 每帧调用一次
- 一般用于非物理运动

FixedUpdate：

- 每隔固定时间调用一次
- 一般用于物理的运动

## 4.事件响应

![image-20200919084246122](C:\Users\63291\AppData\Roaming\Typora\typora-user-images\image-20200919084246122.png)

## 5.物理层

```c#
OnTriggerEnter();//当Collider(碰撞体)进入trigger（触发器）时调用
```



## 6.欧拉角

- 使用三个角度保存方位
- X，Z沿自身坐标系旋转，Y沿世界坐标系旋转
- ```Vector3 eulerAngle = transform.eulerAngles```

优点：

- 使用三个数字表示，占用空间小
- 沿坐标轴旋转，符合人类思考方式
- 任意三个数字是合法的，不存在不合法的欧拉角

缺点：

- 表达方式不唯一，同一个方位，存在多个欧拉角的描述，无法判断多个欧拉角代表的角位移是否相同(0,5,0)与(0,355,0)
- 万向节死锁：物体沿X旋转正负90度，自身坐标系Z轴与世界坐标系Y轴重合，此时再沿Y或Z旋转时，将失去一个自由度。

总之，使用欧拉加无法360度无死角的旋转，所以要使用四元数。

## 7.四元数

- Quaternion在3D图形学中代表旋转，由一个三维向量x,y,z和一个标量w组成。
- 旋转轴为v，旋转弧度为$\theta$，如果用四元数表示，四个分量为：$x=sin(\theta/2)*V.x;y=sin(\theta/2)*V.y;z=sin(\theta/2)*V.z;w=cos(\theta/2)$
- x,y,z,w的取值为$[-1,1]$


缺点
- 难于使用，不建议单独修改某个数值
- 存在不合法的四元数
- 欧拉角和四元数是互补的


用法
- 两个四元数相乘表示组合旋转的效果
```C#
transform.rotation=Quaternion.Euler(0,20,0)*Quaternion.Euler(0,30,0);
// 相当于
transform.rotation=Quaternion.Euler(0,50,0)
```

- 四元数左乘向量，表示将向量按照四元数表示的角度旋转
```C#
Vector3 point=new Vector3(0,0,10);
Vector3 newPoint=Quaternion.Euler(0,30,0)*point;
```


```c#
public class NewBehaviourScript : MonoBehaviour
{
    private Vector3 vect;

    private void Awake()
    {
        vect = new Vector3(10, 10, 10);
    }

    private void OnGUI()
    {
        if(GUILayout.Button("用法1"))
        {
            //旋转轴
            Vector3 axis = Vector3.up;
            //旋转角度
            float rad = 45*Mathf.Deg2Rad;

            Quaternion qt = new Quaternion();

            qt.x = Mathf.Sin(rad / 2) * axis.x;// 极少情况下涉及到直接给x,y,z,w赋值
            qt.y = Mathf.Sin(rad / 2) * axis.y;
            qt.z = Mathf.Sin(rad / 2) * axis.z;
            qt.w = Mathf.Cos(rad / 2);

            transform.rotation = qt;
        }

        if (GUILayout.Button("用法2"))
        {
            this.transform.rotation = Quaternion.Euler(0, 90, 0);// 绕y轴转50度，欧拉角转化为四元数
        }

        if (GUILayout.RepeatButton("用法3"))
        {
            // this.transform.rotation += Quaternion.Euler(1, 0, 0);// 错误 四元数无法累加
            // 应该改用 乘
            this.transform.rotation *= Quaternion.Euler(1, 0, 0);//绕x轴每次执行都转1度

            //this.transform.Rotate(1, 0, 0);// rotate也是用的四元数
        }
    }
    
    private void Update()
    {
        Debug.DrawLine(this.transform.position, vect);

        //先在物体自身位置下叠加向量（0，0，10），再左乘四元数，实现将此向量沿z轴旋转30度
        //vect = this.transform.position + Quaternion.Euler(0, 30, 0)*new Vector3(0,0,10);

        //在上面基础上，还想让向量跟随物体旋转，就要继续乘
        vect = this.transform.position + Quaternion.Euler(0, 30, 0) *this.transform.rotation* new Vector3(10, 10, 10);//因为rotation本身就是调用的四元数，所以两者相乘就是角度的叠加
    }
}
```