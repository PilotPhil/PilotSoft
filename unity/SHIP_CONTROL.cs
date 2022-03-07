using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SHIP_CONTROL : MonoBehaviour
{
    // 船体运动控制


    private Rigidbody boat;// 船体刚体

    [Range(0,10000)]
    public int surge_force = 1000; // surge上力

    [Range(0, 10000)]
    public int yaw_monment = 1000;// yaw上力矩

    void Start()
    {
        boat = GetComponent<Rigidbody>();// 获取刚体,要给主船体（船体外壳）加上mesh collider,并勾选convex,才能实现碰撞效果
    }

    // Update is called once per frame
    void Update()
    {
        DOF2CONTROL();

    }

    private void DOF2CONTROL()
    {
        // 2DOF船舶控制
        // 1.控制surge方向推进---添加一个相对于刚体的系统坐标力---AddRelativeForce
        // 2.控制yaw航向---施加添加相对于刚体自身的坐标系统的一个力矩---AddRelativeTorque

        // 问题（待解决）：
        // 力应施加在螺旋桨上，其带动整条船运动
        // 力矩应作用在舵上

        //W、A、S、D控制
        if (Input.GetKey("w"))// 按W在surge正向施加力
        {
            boat.AddRelativeForce(0, 0, surge_force * Time.deltaTime);
        }
        else if (Input.GetKey("s"))// 按S在surge负向施加力
        {
            boat.AddRelativeForce(0, 0, -1 * surge_force * Time.deltaTime);
        }

        if (Input.GetKey("a"))// 按A在yaw逆时针施加力矩
        {
            boat.AddRelativeTorque(0, -1 * yaw_monment * Time.deltaTime, 0);
        }
        else if (Input.GetKey("d"))// 按D在yaw顺时针施加力矩
        {
            boat.AddRelativeTorque(0, yaw_monment * Time.deltaTime, 0);
        }
    }
}
