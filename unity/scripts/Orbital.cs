using UnityEngine;
using System.Collections;

public class Orbital : MonoBehaviour// 用来控制摄像头视角旋转的？？？
{
  public Transform target;// 传入摄像机跟踪目标
  Vector3 lastPosition;// 暂存上一次（最近）的鼠标指针的位置
  Vector3 direction;// 
  float distance;// 

  Vector3 movement;// 
  Vector3 rotation;

	void Awake ()
  {
    direction = new Vector3(0, 0, (target.position - transform.position).magnitude);// 跟踪目标-摄像机的Z轴旋转角，再乘以幅值magnitude？？？
    transform.SetParent(target);// 设置跟踪目标target为摄像机的父对象
    lastPosition = Input.mousePosition;// 鼠标位置赋值给最近位置 （当前所在像素坐标的鼠标位置，屏幕上鼠标指针位置）
  }
	
	void Update ()
  {
    Vector3 mouseDelta = Input.mousePosition - lastPosition;// 再次获取鼠标指针位置，减去上次暂存的位置
    if (Input.GetMouseButton(0))// 当指定的鼠标按钮被按下时返回true,0对应左键 ， 1对应右键 ， 2对应中键。
    {
      movement += new Vector3(mouseDelta.x * 0.1f, mouseDelta.y * 0.05f, 0F);// 鼠标指针x,y坐标构建欧拉转角
    }
    movement.z += Input.GetAxis("Mouse ScrollWheel") * -2.5F;// 

    rotation += movement;
    rotation.x = rotation.x % 360.0f;
    
    rotation.y = Mathf.Clamp(rotation.y, -80F, -10F);// 限定y轴旋转在-80~-10之间

    //direction.z = Mathf.Clamp(direction.z - movement.z * 50F, 15F, 180F);
    direction.z = Mathf.Clamp(movement.z + direction.z, 15F, 100F);//
    transform.position = target.position + Quaternion.Euler(180F - rotation.y, rotation.x, 0) * direction;
    transform.LookAt(target.position);

    lastPosition = Input.mousePosition;
    movement *= 0.9F;


  }
}
