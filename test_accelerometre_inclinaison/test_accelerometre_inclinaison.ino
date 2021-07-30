#include "ICM20600.h"
#include <Wire.h>

ICM20600 icm20600(true);

void setup() {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    Wire.begin();

    Serial.begin(9600);
    icm20600.initialize();
    icm20600.setAccScaleRange(RANGE_2G);
    //icm20600.reset();
}

void loop() {
    // Serial.print("DeviceID: ");
    // Serial.println(icm20600.getDeviceID(), HEX);

    //--------- To get the acceleration----------
//    Serial.print("x = ");
//    Serial.print(icm20600.getAccelerationX());
//    Serial.println(" mg");
//    Serial.print("y = ");
//    Serial.print(icm20600.getAccelerationY());
//    Serial.println(" mg");
//    Serial.print("z = ");
//    Serial.print(icm20600.getAccelerationZ());
//    Serial.println(" mg");

    //--------- To get the angles ----------
    char xVal, yVal, zVal;
    float angleX, angleY, angleZ, total;
    
    xVal=xVal+icm20600.getAccelerationX();
    yVal=yVal+icm20600.getAccelerationY();
    zVal=zVal+icm20600.getAccelerationZ();
    
    total = sqrt(xVal * xVal + yVal * yVal + zVal * zVal);
    
    angleX = round(asin(xVal / total ) * 180.0 / 3.1416);
    angleY = round(asin(yVal / total ) * 180.0 / 3.1416);
    angleZ = round(acos(zVal / total ) * 180.0 / 3.1416);
    
    Serial.print("Ax = ");
    Serial.print(angleX);
    Serial.print("Ay = ");
    Serial.print(angleY);
    Serial.print("Az = ");
    Serial.print(angleZ);

    Serial.println("-------------------------");
    delay(1000);
}
