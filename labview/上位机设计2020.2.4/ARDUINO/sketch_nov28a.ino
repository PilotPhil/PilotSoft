#include <math.h>
#define pi 3.14159265
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {

  int i=0;
  double degree=0.0;
  String send;
  while(i<181)
  {
    degree=100*sin((i*pi)/180);
    send=String(degree);
    Serial.println(send);
    i++;
    if(i==180)
    {
      i=0;
    }

    delay(100);
  }
}
