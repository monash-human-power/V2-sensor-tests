# V2-sensor-tests

Teensy scripts to test if individual sensors work using the hardware debugger.

## Test Files

- [IMU + GPS Sensor Test](#IMU-+-GPS-Sensor-Test)

- [Reed Switch Test](#reed-switch-test)

## IMU + GPS Sensor Test

### Libraries

You will need the following libraries installed:

- SparkFun LSM6DS3 Breakout
- TinyGPS++ ([Download Link](http://arduiniana.org/libraries/tinygpsplus/))

### Common Problems

#### GPS module has no Red Light

GPS Module is not powered on properly. Your GPS module is probably broken.

#### IMU data values do not change

Your IMU is probably broken.

## Reed Switch Test

### Common Problems

#### No velocity or distance data

Check the following:

- Reed switch mount is close to the magnet located in the rear wheel
- RJ45 cable coupler is correctly connecting the two RJ45 cables together