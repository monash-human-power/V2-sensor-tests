#include <SPI.h>
#include <SparkFunLSM6DS3.h>

// Set up Accelerometer
const int LMS6DS3chipSelect = 6; // CS Pin
LSM6DS3 myIMU(SPI_MODE, LMS6DS3chipSelect);
float aX, aY, aZ;

void setup() {
  Serial.begin(9600);

   // Set Up IMU
  SPI1.setMOSI(0); // SDA Pin
  SPI1.setMISO(1); // SAD Pin
  SPI1.setSCK(20); // SCL Pin
  myIMU.begin();
}

void loop() {
  aX = myIMU.readFloatAccelX();
  aY = myIMU.readFloatAccelY();
  aZ = myIMU.readFloatAccelZ();

  Serial.println("IMU");
  Serial.println("aX:" + String(aX, 5));
  Serial.println("aY:" + String(aY, 5));
  Serial.println("aZ:" + String(aZ, 5));
  Serial.println();
  delay(100);
}
