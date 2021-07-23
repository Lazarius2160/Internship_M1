#include "ICM20600.h"
#include <Wire.h>

ICM20600 icm20600(true);

int16_t x,y,z;
float val[3];                            // met en float mais a jamais de nombre a virgule ( fait ca que pour pouvor plot)
// only float data type can be plot
//float val = 0.0;

void setup()
{
  Wire.begin();
  Serial.begin(9600);                   // starts the serial monitor
  icm20600.initialize();
  icm20600.setAccScaleRange(RANGE_8G);
}

void loop()
{

//  val = icm20600.getAccelerationY();
//  val[0] = icm20600.getAccelerationX();
//  val[1] = icm20600.getAccelerationY();
//  val[2] = icm20600.getAccelerationZ();

//  Serial.println(val);
//  Serial.println("Ax=");
//  Serial.println(val[0]);
//  Serial.println("Ay=");
//  Serial.println(val[1]);
//  Serial.println("Az=");
//  Serial.println(val[2]);
  icm20600.getAcceleration(&x,&y,&z);
  val[0] = x;
  val[1] = y;
  val[2] = z;
//  
//  Serial.println("test val X:");
//  Serial.println(val[0]);
//  Serial.println("test X:");
//  Serial.println(x);
//  Serial.println("test val Y:");
//  Serial.println(val[1]);
//  Serial.println("test y:");
//  Serial.println(y);
//  Serial.println("test Z:");
//  Serial.println(val[2]);
  Serial.println(val[0]);
  Serial.println(val[1]);
  Serial.println(val[2]);
  Serial.println("-------------------");
  delay(1000);                           // wait for this much time before printing next value
}
