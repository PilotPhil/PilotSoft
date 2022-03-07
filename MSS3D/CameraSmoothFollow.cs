/*
 * 作者：Pilot.Phil
 * 时间：2020-11-29
 *
 * 简介：相机平滑跟踪物体
 *
 * 使用：
 *      1.此脚本挂载于摄像机下
 *
 * 实现：
 * 		1.摄像机平滑跟踪物体
 * 		2.调教相机与物体之间距离、相机高度等
 */

using UnityEngine;
using System.Collections;

public class CameraSmoothFollow : MonoBehaviour
{
	public Transform targetBoat;				// 跟踪目标
	public float distance = 3.0f;				// 与目标之间距离
	public float height = 3.0f;					// 相机高度
	public float damping = 5.0f;				// 跟随阻尼
	public bool smoothRotation = true;			// 是否平滑旋转
	public float rotationDamping = 10.0f;		// 旋转阻尼

	void FixedUpdate ()
	{
		Vector3 camPosition = targetBoat.TransformPoint(0, height, -distance);                                              // 以船的位置为世界中心，相机相对于船的坐标为参量，求出相机的世界坐标

		this.transform.position = Vector3.Lerp (this.transform.position, camPosition, Time.deltaTime * damping);			// 从相机现在的位置线性插值过渡到计算得的下一时刻相机位置，使用deltatime乘以阻尼控制速度

		if (smoothRotation)																									// 如果要平滑旋转的话
		{
			Quaternion wantedRotation = Quaternion.LookRotation(targetBoat.position - transform.position, targetBoat.up);	//
			transform.rotation = Quaternion.Slerp (transform.rotation, wantedRotation, Time.deltaTime * rotationDamping);	//
		}
		else
        {
			transform.LookAt(targetBoat, targetBoat.up);
		}
	}

	void Update()
	{
		if ( Input.GetKeyDown(KeyCode.Escape  ))		// 按下esc键
		{
			Application.Quit();							// 退出程序
		}
	}
}