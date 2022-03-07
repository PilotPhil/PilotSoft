/*
 * 作者：Pilot.Phil
 * 时间：2020-11-29
 *
 * 简介：在游戏内使用C键来循环切换场景中的多个相机
 * 使用：
 *      1.此脚本挂载于一空物体下
 *
 * 实现：
 *      1.动态传入场景中多个相机
 *      2.按C键循环切换机位
 *
 */

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraSwitch : MonoBehaviour
{
    public List<GameObject> cams;           // 相机数组
    private int camFlag;                    // 相机使用、禁用标志位

    private void Start()
    {
        camFlag = 1;                        // 默认初始标志位置一，开启一号摄像机
        _switch();                          //
    }


    void Update()
    {
        if (Input.GetKeyDown(KeyCode.C))    // 每按下C键
        {
            camFlag++;                      // 标志位加一

            if (camFlag > cams.Count)       // 标志位越位
            {
                camFlag = 1;                // 归位
            }

            _switch();                      // 
        }
    }

    // 切换相机
    void _switch()
    {
        for (int i = 0; i < cams.Count; i++)
        {
            if (i == camFlag - 1)
            {
                cams[i].SetActive(true);    // 激活
            }
            else
            {
                cams[i].SetActive(false);   // 关闭
            }
        }
    }
}
