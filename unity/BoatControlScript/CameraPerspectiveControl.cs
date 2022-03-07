// 此脚本用于设置摄像机跟随船体与视角控制
// 作者：Pilot.Phil
// Gitee：https://gitee.com/pilot12138 ; 632913013@qq.com
// 更新日期：20/9/25

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraPerspectiveControl : MonoBehaviour
{
    // 此脚本挂在摄像机上
    // 用于控制游戏内视角的变化
    // 实现：
    // 1.第三人称视角（船尾后上方）
    // 2.第一人称视角（船前上甲板）
    // 3.俯视视角（直升机俯拍）
    // 4.舷侧视角
    // 5.鼠标拖拽自由视角（自由视角）

    public Transform cam;// 传入摄像机
    public Transform boat;// 传入船
    private Vector3 distanceFromBoat2Cam;// 摄像机与船之间的距离向量
    private int P_flag;//视角切换标志位

    //free pespective所用的成员
    private Vector3 lastPosition;
    private Vector3 direction;
    private float distance;
    private Vector3 movement;
    private Vector3 rotation;

    private void Awake()
    {
        P_flag=4;//

        direction=new Vector3(0,0,(boat.position-cam.position).magnitude);
        cam.SetParent(boat);
        lastPosition=Input.mousePosition;
    }

    private void Update()
    {
        ChoosePerspective();
    }

    private void ThirdPersonPerspective(float z_dis=-2,float y_dis=2)//第三人称视角
    {
        if(boat==null || cam==null)
        {
            Debug.Log("未绑定船只或者摄像头");
            return;
        }

        Debug.Log("第三人称视角");

        //1.摄像机先移动到船的位置重合
        cam.position=boat.position;

        //2.调整摄像机相对于船的位置
        distanceFromBoat2Cam=Vector3.forward*z_dis+Vector3.up*y_dis;//cam距离boat在z轴上-5m//cam距离boat在y轴上2m
        Quaternion rot=Quaternion.Euler(0,boat.eulerAngles.y,0);//cam跟随boat旋转角度y
        cam.position+=rot*distanceFromBoat2Cam;

        //3.使摄像头指向船
        cam.LookAt(boat);
    }

    private void FirstPersonPerspective(float z_dis=0.0f,float y_dis=0.3f)//第一人称视角
    {
        if(boat==null || cam==null)
        {
            Debug.Log("未绑定船只或者摄像头");
            return;
        }

        Debug.Log("第一人称视角");

        //1.摄像机先移动到船的位置重合
        cam.position=boat.position;

        //2.调整摄像机相对于船的位置
        distanceFromBoat2Cam=Vector3.forward*z_dis+Vector3.up*y_dis;//cam距离boat在z轴上-5m//cam距离boat在y轴上2m
        Quaternion rot=boat.rotation;//cam跟随boat旋转x,y,z轴上角度
        cam.position+=rot*distanceFromBoat2Cam;

        //3.使摄像头指向船的前方就是z轴
        cam.LookAt(boat.forward);

    }

    private void DownPerspective(float y_dis=2)// 俯视视角
    {
        if(boat==null || cam==null)
        {
            Debug.Log("未绑定船只或者摄像头");
            return;
        }
        
        Debug.Log("俯视视角");

        //1.摄像机先移动到船的位置重合
        cam.position=boat.position;

        //2.调整摄像机相对于船的位置
        distanceFromBoat2Cam=Vector3.up*y_dis;//cam距离boat在y轴上2m
        Quaternion rot=Quaternion.Euler(0,boat.eulerAngles.y,0);//cam跟随boat旋转角度y
        cam.position+=rot*distanceFromBoat2Cam;

        //3.使摄像头指向船
        cam.LookAt(boat);
    }

    private void SidePerspective(float z_dis=0,float y_dis=1,float x_dis=1)// 舷侧视角,x_dis>0 右舷 x_dis<0 左舷 
    {
        if(boat==null || cam==null)
        {
            Debug.Log("未绑定船只或者摄像头");
            return;
        }

        Debug.Log("舷侧视角");
        
        //1.摄像机先移动到船的位置重合
        cam.position=boat.position;

        //2.调整摄像机相对于船的位置
        distanceFromBoat2Cam=Vector3.up*y_dis+Vector3.forward*z_dis+Vector3.right*x_dis;//
        Quaternion rot=Quaternion.Euler(0,boat.eulerAngles.y,0);//cam跟随boat旋转角度y
        cam.position+=rot*distanceFromBoat2Cam;

        //3.使摄像头指向船
        cam.LookAt(boat);
    }

    private void FreePerspective()//自由视角
    {
         Debug.Log("自由视角");

        Vector3 mouseDelta=Input.mousePosition-lastPosition;

        if(Input.GetMouseButton(0))
        {
            movement+=new Vector3(mouseDelta.x*0.02f,mouseDelta.y*0.02f,0f);
        }
        movement.z+=Input.GetAxis("Mouse ScrollWheel")*-0.3f;

        rotation+=movement;
        rotation.x=rotation.x%360.0f;

        rotation.y=Mathf.Clamp(rotation.y,-80f,-10f);

        direction.z=Mathf.Clamp(movement.z+direction.z,0f,100f);
        cam.position=boat.position+Quaternion.Euler(180f-rotation.y,rotation.x,0)*direction;
        cam.LookAt(boat);

        lastPosition=Input.mousePosition;
        movement*=0.9f;
    }

    private void ChoosePerspective()//按空格切换视角
    {
        if(Input.GetKeyDown(KeyCode.Space))
        {
            P_flag++;
        }
        
        if(P_flag>4)
        {
            P_flag=0;
        }

        switch(P_flag)
        {
            case 0:ThirdPersonPerspective();break;
            case 1:FirstPersonPerspective();break;
            case 2:DownPerspective();break;
            case 3:SidePerspective();break;
            case 4:FreePerspective();break;
            default:break;
        }
    }

}
