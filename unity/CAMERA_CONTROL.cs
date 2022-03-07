using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CAMERA_CONTROL : MonoBehaviour
{
    public Transform boat;// 传入要被跟随的船体
    public GameObject FPP_LOOKAT_OBJ;

    private int P_FLAG = 1;//视角切换

    private void Update()
    {
        // 根据标志位切换视角
        switch (P_FLAG)
        {
            case 1:
                TPP();
                break;

            case 2:
                FPP();
                break;

            case 3:
                SKYP();
                break;

            default:
                break;
        }
    }

    // 第三人称视角，船尾视角
    private void TPP()
    {
        // 0.如果跟随的目标不存在，就直接返回
        if (this.boat == null)
            return;

        // 1.摄像机移动到当前的物体所在的位置
        this.transform.position = this.boat.position;

        // 2.摄像机方向对船尾往后拉4米
        //欧拉角转四元素，旧的Quaternion.EulerAngles已经废弃，旧的表示的是弧度，不是角度
        Quaternion rot = Quaternion.Euler(0, this.boat.eulerAngles.y, 0);
        //target的四元素旋转矩阵*摄像机自己的正Z方向=target的方向，target的方向*4=一个三维坐标向量
        this.transform.position -= rot * Vector3.forward * 6;

        // (3)将摄像机抬高一米
        Vector3 position = this.transform.position;
        position.y += 2;
        this.transform.position = position;

        // (4) 摄像机对准某个物体，将自己的Z轴对准目标
        this.transform.LookAt(this.boat);
    }

    // 第一人称视角---未完工
    private void FPP()
    {
        // 0.如果跟随的目标不存在，就直接返回
        if (this.boat == null)
            return;

        // 1.摄像机移动到当前的物体所在的位置
        this.transform.position = this.boat.position;

        // 2.摄像机方向对船尾往前拉？米
        //欧拉角转四元素，旧的Quaternion.EulerAngles已经废弃，旧的表示的是弧度，不是角度
        Quaternion rot = Quaternion.Euler(0, this.boat.eulerAngles.y, 0);
        //target的四元素旋转矩阵*摄像机自己的正Z方向=target的方向，target的方向*4=一个三维坐标向量
        this.transform.position += rot * Vector3.forward * 2;

        // (3)将摄像机抬高一米
        Vector3 position = this.transform.position;
        position.y += 1;
        this.transform.position = position;

        // (4) 摄像机对准某个物体，将自己的Z轴对准目标
        this.transform.LookAt(this.FPP_LOOKAT_OBJ.transform);// BOAT根下添加一空物体，让摄像机指向位于船前面的空物体即可
    }

    // 天空视角，俯视图
    private void SKYP()
    {
        // 0.如果跟随的目标不存在，就直接返回
        if (this.boat == null)
            return;

        // 1.摄像机移动到当前的物体所在的位置
        this.transform.position = this.boat.position;

        // 2.摄像机方向对船尾往前拉？米
        //欧拉角转四元素，旧的Quaternion.EulerAngles已经废弃，旧的表示的是弧度，不是角度
        Quaternion rot = Quaternion.Euler(0, this.boat.eulerAngles.y, 0);
        //target的四元素旋转矩阵*摄像机自己的正Z方向=target的方向，target的方向*4=一个三维坐标向量
        this.transform.position += rot * Vector3.forward * 1;

        // (3)将摄像机抬高11米
        Vector3 position = this.transform.position;
        position.y += 11;
        this.transform.position = position;

        // (4) 摄像机对准某个物体，将自己的Z轴对准目标
        this.transform.LookAt(this.boat);
    }

    // 视角标志位设置
    private void OnGUI()
    {
        if(GUILayout.Button("第三人称视角"))
        {
            P_FLAG = 1;
        }
        else if(GUILayout.Button("第一人称视角"))
        {
            P_FLAG = 2;
        }
        else if (GUILayout.Button("俯视视角"))
        {
            P_FLAG = 3;
        }

    }

}
