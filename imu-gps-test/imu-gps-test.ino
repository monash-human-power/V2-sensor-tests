#include <TinyGPS++.h>
#include <SparkFunLSM6DS3.h>

#include <SoftwareSerial.h>
#include <SPI.h>

// Set up Accelerometer
static const int LMS6DS3chipSelect = 6; // CS Pin
LSM6DS3 myIMU(SPI_MODE, LMS6DS3chipSelect);
float aX, aY, aZ;

// Set up GPS
static const int GPS_RXPin = 7, GPS_TXPin = 8;
static const uint32_t GPS_Baud = 9600;

SoftwareSerial ss(GPS_RXPin, GPS_TXPin);
TinyGPSPlus tinyGPS;

void setup() {
  Serial.begin(9600);

   // Set Up IMU
  SPI1.setMOSI(0); // SDA Pin
  SPI1.setMISO(1); // SAD Pin
  SPI1.setSCK(20); // SCL Pin
  myIMU.begin();

  // Set Up GPS
  ss.begin(GPS_Baud);

}

void loop() {
  // Get IMU data
  aX = myIMU.readFloatAccelX();
  aY = myIMU.readFloatAccelY();
  aZ = myIMU.readFloatAccelZ();

  Serial.println("IMU");
  Serial.println("aX:" + String(aX, 5));
  Serial.println("aY:" + String(aY, 5));
  Serial.println("aZ:" + String(aZ, 5));
  Serial.println();

  // Get GPS data
  if ((ss.available() > 0)) {
    if (tinyGPS.encode(ss.read())) {
      Serial.println("GPS");
      if (tinyGPS.satellites.value() > 0) {
        Serial.println("Lat: " + String(tinyGPS.location.lat(), 8));
        Serial.println("Lon: " + String(tinyGPS.location.lng(), 8));
      } else {
        Serial.println("No GPS Satellites");
      }
    }
  }
  delay(100);
}
