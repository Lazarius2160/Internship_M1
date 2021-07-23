#include "ICM20600.h"
#include <Wire.h>

ICM20600 icm20600(true);

float val[3];                            // variable to store the values from sensor(initially zero)
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
  val[0] = icm20600.getAccelerationX();
  val[1] = icm20600.getAccelerationY();
  val[2] = icm20600.getAccelerationZ();

//  Serial.println(val);
  Serial.println("Ax=");
  Serial.println(val[0]);
  Serial.println("Ay=");
  Serial.println(val[1]);
  Serial.println("Az=");
  Serial.println(val[2]);
  Serial.println("-------------------");
  delay(1000);                           // wait for this much time before printing next value
}
