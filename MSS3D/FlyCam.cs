/*
 * 作者：Pilot.Phil
 * 时间：2020-11-29
 *
 * 简介：在游戏内使用WASDQE来控制摄像机的3自由度运动
 *
 * 使用：
 *      1.此脚本挂载于要漫游摄像机下
 *
 * 实现：
 * 		1.WASD移动摄像机
 * 		2.Q上升、E下降
 * 		3.按住Shift：更快
 * 		4.按住control：更慢
 * 		5.end键：是否锁定光标
 *
 */


using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Obsolete]


public class FlyCam : MonoBehaviour
{
	public float cameraSensitivity = 90;		// 摄像机灵敏度
	public float climbSpeed = 4;				// 上升速度
	public float normalMoveSpeed = 10;			// 普通移动速度
	public float slowMoveFactor = 0.25f;		// 更慢移动速度（control）
	public float fastMoveFactor = 3;			// 更快移动速度（shift）

	private float rotationX = 0.0f;
	private float rotationY = 0.0f;


    void Start()
	{
		Screen.lockCursor = true;
	}

	void Update()
	{
		rotationX += Input.GetAxis("Mouse X") * cameraSensitivity * Time.deltaTime;
		rotationY += Input.GetAxis("Mouse Y") * cameraSensitivity * Time.deltaTime;
		rotationY = Mathf.Clamp(rotationY, -90, 90);

		transform.localRotation = Quaternion.AngleAxis(rotationX, Vector3.up);
		transform.localRotation *= Quaternion.AngleAxis(rotationY, Vector3.left);

		if (Input.GetKey(KeyCode.LeftShift) || Input.GetKey(KeyCode.RightShift))
		{
			transform.position += transform.forward * (normalMoveSpeed * fastMoveFactor) * Input.GetAxis("Vertical") * Time.deltaTime;
			transform.position += transform.right * (normalMoveSpeed * fastMoveFactor) * Input.GetAxis("Horizontal") * Time.deltaTime;
		}
		else if (Input.GetKey(KeyCode.LeftControl) || Input.GetKey(KeyCode.RightControl))
		{
			transform.position += transform.forward * (normalMoveSpeed * slowMoveFactor) * Input.GetAxis("Vertical") * Time.deltaTime;
			transform.position += transform.right * (normalMoveSpeed * slowMoveFactor) * Input.GetAxis("Horizontal") * Time.deltaTime;
		}
		else
		{
			transform.position += transform.forward * normalMoveSpeed * Input.GetAxis("Vertical") * Time.deltaTime;
			transform.position += transform.right * normalMoveSpeed * Input.GetAxis("Horizontal") * Time.deltaTime;
		}


		if (Input.GetKey(KeyCode.Q)) { transform.position += transform.up * climbSpeed * Time.deltaTime; }
		if (Input.GetKey(KeyCode.E)) { transform.position -= transform.up * climbSpeed * Time.deltaTime; }

		if (Input.GetKeyDown(KeyCode.End))
		{
			Screen.lockCursor = (Screen.lockCursor == false) ? true : false;
		}
	}
}