using UnityEngine;
using System.Collections;

public class BoatController : MonoBehaviour
{
  public PropellerBoats ship;// 实例化对象
  bool forward = true; //前进方向

  void Update()
  {

    if (Input.GetKey(KeyCode.A))
      ship.RudderLeft();// 舵向左
    if (Input.GetKey(KeyCode.D))
      ship.RudderRight();// 舵向右

    if (forward)//是前进方向
    {
      if (Input.GetKey(KeyCode.W))
        ship.ThrottleUp();
      else if (Input.GetKey(KeyCode.S))
      {
        ship.ThrottleDown();
        ship.Brake();
      }
    }

    else//不是前进方向
    {
      if (Input.GetKey(KeyCode.S))
        ship.ThrottleUp();
      else if (Input.GetKey(KeyCode.W))
      {
        ship.ThrottleDown();
        ship.Brake();
      }
    }

    if (!Input.GetKey(KeyCode.W) && !Input.GetKey(KeyCode.S))
      ship.ThrottleDown();

    if (ship.engine_rpm == 0 && Input.GetKeyDown(KeyCode.S) && forward)
    {
      forward = false;
      ship.Reverse();
    }
    else if (ship.engine_rpm == 0 && Input.GetKeyDown(KeyCode.W) && !forward)
    {
      forward = true;
      ship.Reverse();
    }
  }

}
