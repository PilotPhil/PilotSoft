using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PID_control : MonoBehaviour
{
    public Rigidbody boat;      // 被控制的船

    public GameObject AimPoint;  // 航行目标

    public PID PID_Yaw;         // 航向控制
    public PID PID_Surge;       // 纵向控制

    public float force;         // 纵向推力
    public float torque;        // 转矩     

    public bool yawControlFinished;
    public bool surgeControlFinished;

    void Start()
    {
        PID_Yaw = new PID();    // 航向控制PID实例化
        PID_Surge = new PID();  // 纵向控制PID实例化

        torque = 0;             // 转矩设初值
        PID_Yaw.preError = 0;
        PID_Yaw.integral = 0;
        PID_Yaw.target = 0;

        PID_Yaw.P = 30;
        PID_Yaw.I = 0;
        PID_Yaw.D = 15;

        force = 0;
        PID_Surge.preError = 0;
        PID_Surge.integral = 0;
        PID_Surge.target = 0;        // 距离的稳态值为零

        PID_Surge.P = 1.5f;
        PID_Surge.I = 0;
        PID_Surge.D = 4f;

        yawControlFinished = true;
        surgeControlFinished = true;
    }

    void Update()
    {
        
    }

    private void FixedUpdate()
    {
        YawControl();

        SurgrControl();
    }

    private void YawControl()                                       // 航向控制
    {
        float degree = Vector3.Angle(AimPoint.transform.position - boat.position, boat.transform.forward);
        Vector3 normal = Vector3.Cross(AimPoint.transform.position - boat.position, boat.transform.forward);
        degree *= Mathf.Sign(Vector3.Dot(normal, Vector3.up));

        PID_Yaw.measurement = degree;

        if (Mathf.Abs(PID_Yaw.measurement)>1)
        {
            torque = PID_Yaw.control();                                 // 计算转矩大小
            if (yawControlFinished == false)
            {
                boat.AddTorque(torque * this.transform.up, ForceMode.Force);  // 施加转矩
            }
        }
    }

    private void SurgrControl()
    {
        float distance = (AimPoint.transform.position - boat.transform.position).magnitude;

        Vector3 tem = AimPoint.transform.position - boat.transform.position;
        Vector3 local = boat.transform.forward;

        distance *= -1 * Mathf.Sign(Vector3.Dot(tem, local));

        PID_Surge.measurement = distance;

        if (Mathf.Abs(PID_Surge.measurement) > 1)
        {
            force = PID_Surge.control();

            if (surgeControlFinished == false)
            {
                boat.AddForce(force * boat.transform.forward, ForceMode.Force);
            }
        }
    }

    private void OnGUI()
    {
        if(GUI.Button(new Rect(0,10,100,30),"启用航向控制"))
        {
            yawControlFinished = false;
        }

        if (GUI.Button(new Rect(0, 50, 100, 30), "关闭航向控制"))
        {
            yawControlFinished = true;
        }

        if (GUI.Button(new Rect(0, 90, 100, 30), "启用纵向控制"))
        {
            surgeControlFinished = false;
        }

        if (GUI.Button(new Rect(0, 130, 100, 30), "关闭纵向控制"))
        {
            surgeControlFinished = true;
        }

    }
}


[System.Serializable]
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

        integral += error;
        preError = error;

        AllOut = Pout + Iout + Dout;    // 总输出
        return AllOut;
    }
}

