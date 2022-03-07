//////////////////////////////////////////////////////////////////

#include "quaternionFilters.h"
#include "MPU9250.h"
#include<dht.h>
#define AHRS true
#define SerialDebug true
#define I2Cclock 400000
#define I2Cport Wire
#define MPU9250_ADDRESS MPU9250_ADDRESS_AD0
#define DHT22_pin 7//定义温湿度针角
dht DHT;//dht对象
MPU9250 myIMU(MPU9250_ADDRESS, I2Cport, I2Cclock);

///////////////////////////////////////////////////////////////////


//初始化
void setup()
{
  Wire.begin();
  Serial.begin(115200);
  byte c = myIMU.readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);
  if (c == 0x71) // WHO_AM_I should always be 0x71
  {
    myIMU.MPU9250SelfTest(myIMU.selfTest);
    myIMU.calibrateMPU9250(myIMU.gyroBias, myIMU.accelBias);
    myIMU.initMPU9250();
    byte d = myIMU.readByte(AK8963_ADDRESS, WHO_AM_I_AK8963);
    //i2C地址，如果出现无法连接，确认陀螺仪接线是否正确
    if (d != 0x48)
    {
      Serial.flush();
      abort();
    }
    myIMU.initAK8963(myIMU.factoryMagCalibration);
    myIMU.getAres();
    myIMU.getGres();
    myIMU.getMres();
  } // if (c == 0x71)
  
  else
  {
    Serial.print("Could not connect to MPU9250: 0x");
    Serial.println(c, HEX);
    Serial.println(F("Communication failed, abort!"));
    Serial.flush();
    abort();
  }
}

//温湿度监测函数
String temhum(){
  DHT.read22(DHT22_pin);
  int tem=int(DHT.temperature)+100;
  int hum=int(DHT.humidity)+100;
  String all=String(tem)+'^'+String(hum)+'^';
  return all;
}

//应变监测函数
String yb(){
  int val=analogRead(2)+100;
  String all=String(val)+'^';
  return all;
}

//陀螺仪函数
String mpu(){
  if (myIMU.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)
  {
    myIMU.readAccelData(myIMU.accelCount);  // Read the x/y/z adc values

    myIMU.ax = (float)myIMU.accelCount[0] * myIMU.aRes; // - myIMU.accelBias[0];
    myIMU.ay = (float)myIMU.accelCount[1] * myIMU.aRes; // - myIMU.accelBias[1];
    myIMU.az = (float)myIMU.accelCount[2] * myIMU.aRes; // - myIMU.accelBias[2];

    myIMU.readGyroData(myIMU.gyroCount);  // Read the x/y/z adc values

    myIMU.gx = (float)myIMU.gyroCount[0] * myIMU.gRes;
    myIMU.gy = (float)myIMU.gyroCount[1] * myIMU.gRes;
    myIMU.gz = (float)myIMU.gyroCount[2] * myIMU.gRes;

    myIMU.readMagData(myIMU.magCount);  // Read the x/y/z adc values

    myIMU.mx = (float)myIMU.magCount[0] * myIMU.mRes
               * myIMU.factoryMagCalibration[0] - myIMU.magBias[0];
    myIMU.my = (float)myIMU.magCount[1] * myIMU.mRes
               * myIMU.factoryMagCalibration[1] - myIMU.magBias[1];
    myIMU.mz = (float)myIMU.magCount[2] * myIMU.mRes
               * myIMU.factoryMagCalibration[2] - myIMU.magBias[2];
  } // if (readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)
  myIMU.updateTime();

  MahonyQuaternionUpdate(myIMU.ax, myIMU.ay, myIMU.az, myIMU.gx * DEG_TO_RAD,
                         myIMU.gy * DEG_TO_RAD, myIMU.gz * DEG_TO_RAD, myIMU.my,
                         myIMU.mx, myIMU.mz, myIMU.deltat);

    myIMU.delt_t = millis() - myIMU.count;
    
    if (myIMU.delt_t > 50)///////////////////////////////////////////////////////////////////////////////////
    {
      myIMU.yaw   = atan2(2.0f * (*(getQ()+1) * *(getQ()+2) + *getQ()
                    * *(getQ()+3)), *getQ() * *getQ() + *(getQ()+1)
                    * *(getQ()+1) - *(getQ()+2) * *(getQ()+2) - *(getQ()+3)
                    * *(getQ()+3));
      myIMU.pitch = -asin(2.0f * (*(getQ()+1) * *(getQ()+3) - *getQ()
                    * *(getQ()+2)));
      myIMU.roll  = atan2(2.0f * (*getQ() * *(getQ()+1) + *(getQ()+2)
                    * *(getQ()+3)), *getQ() * *getQ() - *(getQ()+1)
                    * *(getQ()+1) - *(getQ()+2) * *(getQ()+2) + *(getQ()+3)
                    * *(getQ()+3));
      myIMU.pitch *= RAD_TO_DEG;
      myIMU.yaw   *= RAD_TO_DEG;
      myIMU.yaw  -= 8.5;
      myIMU.roll *= RAD_TO_DEG;

      String yaw = String(int(myIMU.yaw)+280);
      String pitch = String(int(myIMU.pitch)+280);
      String roll = String(int(myIMU.roll)+280);
      String all = yaw+'^'+pitch+'^'+roll;
return all;
      myIMU.count = millis();
      myIMU.sumCount = 0;
      myIMU.sum = 0;
      
    } // if (myIMU.delt_t > 500)
}

//主循环
void loop()
{
  String all = yb()+temhum()+mpu();
  Serial.println(all);
  delay(100);
}
