/*
 * 作者：Pilot.Phil
 * 时间：2020-11-29
 *
 * 简介：使用WASD控制船舶运动
 *
 * 使用：
 *      1.该脚本挂载于船体上
 *
 * 实现：
 *      1.用wasd控制船舶前进、后退、转弯
 *      2.船舶轮机声音的播放
 */

using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class BoatController : MonoBehaviour
{
    private Rigidbody boat;                                             // 被控制的船 带刚体组件

    private float accel = 0;                                            // 前进加速度
    private float accelBreak;                                           // 刹车加速度

    private float verticalInput = 0F;                                   // 键盘W S输入
    private float horizontalInput = 0F;                                 // 键盘A D输入

    [SerializeField] private List<GameObject> motors;
    [SerializeField] public float finalSpeed = 100F;                    // 船的最大速度
    [SerializeField] public float inertiaFactor = 5F;                   // 惯性因子
    [SerializeField] public float turningFactor = 1000F;                 // 转弯因子
    [SerializeField] public float accelerationTorqueFactor = 35F;       // 直线加速扭矩系数
    [SerializeField] public float turningTorqueFactor = 35F;            // 转弯扭矩系数

    [SerializeField] private bool enableAudio = true;                   // 是否开启声音
    [SerializeField] private AudioSource boatAudioSource;               // 船声音音源
    [SerializeField] private float boatAudioMinPitch = 0.4F;            // 声音最小音调
    [SerializeField] private float boatAudioMaxPitch = 1.2F;            // 声音最大音调

    void Start()
    {
        boat = GetComponent<Rigidbody>();                       // 获取带刚体属性的船
        accelBreak = finalSpeed * 0.3f;
    }

    void Update()
    {
        verticalInput = Input.GetAxisRaw("Vertical");           // W S键输入 返回值由0到1或-1没有渐变
        horizontalInput = Input.GetAxisRaw("Horizontal");       // A D键输入 返回值由0到1或-1没有渐变
    }

    void FixedUpdate()
    {
        if (verticalInput > 0)                                  // ws输入大于零
        {
            if (accel < finalSpeed)                             // 小于最终速度
            {
                accel += finalSpeed * inertiaFactor;            // 准确说，accel并不是加速度，每0.02s时间，accel增加一个量，该量为最终速度乘以惯性因子
                accel *= verticalInput;                         // 使用verticalinpute来确定力的方向
            }

        }
        else if (verticalInput == 0)                            // 
        {
            if (accel > 0)
            {
                accel -= finalSpeed * inertiaFactor;
            }
            if (accel < 0)
            {
                accel += finalSpeed * inertiaFactor;
            }
        }
        else if (verticalInput < 0)
        {
            if (accel > -accelBreak)
            {
                accel -= finalSpeed * inertiaFactor * 2;
            }
        }

        boat.AddRelativeForce(Vector3.forward * accel);      // 向船的前向施加相对力

        boat.AddRelativeTorque(
            verticalInput * -accelerationTorqueFactor,
            horizontalInput * turningFactor,
            horizontalInput * -turningTorqueFactor
        );

        if (motors.Count > 0)
        {
            float motorRotationAngle = 0F;
            float motorMaxRotationAngle = 70;

            motorRotationAngle = -horizontalInput * motorMaxRotationAngle;

            for (int i = 0; i < motors.Count; i++)
            {
                float currentAngleY = motors[i].transform.localEulerAngles.y;
                if (currentAngleY > 180.0f)
                    currentAngleY -= 360.0f;

                float localEulerAngleY = Lerp(currentAngleY, motorRotationAngle, Time.deltaTime * 10);
                motors[i].transform.localEulerAngles = new Vector3(motors[i].transform.localEulerAngles.x, localEulerAngleY, motors[i].transform.localEulerAngles.z);
            }
        }

        if (enableAudio && boatAudioSource != null)// 若打开了声音并且音源非空
        {
            float pitchLevel = boatAudioMaxPitch * Mathf.Abs(verticalInput);
            if (verticalInput < 0) pitchLevel *= 0.7f;

            if (pitchLevel < boatAudioMinPitch) pitchLevel = boatAudioMinPitch;

            float smoothPitchLevel = Lerp(boatAudioSource.pitch, pitchLevel, Time.deltaTime * 0.5f);

            boatAudioSource.pitch = smoothPitchLevel;
        }
    }

    static float Lerp(float from, float to, float value)
    {
        if (value < 0.0f) 
            return from;
        else if (value > 1.0f) 
            return to;

        return (to - from) * value + from;
    }

}
