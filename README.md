# V2-sensor-tests

Teensy scripts to test if individual sensors work using the hardware debugger.

## Test Files

- [IMU + GPS Sensor Test](#IMU-+-GPS-Sensor-Test)

- [Reed Switch Test](#reed-switch-test)

- [Wheel RPM Logging](#wheel-rpm-logging)

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

## Wheel RPM Logging
Logs reed switch events to the serial port.
- Baud rate `115200`. The led on pin 13 will flash fast until a serial terminal is opened.
- Press send `'r'` to the teensy to reset it.
- Set `SEPARATOR` to `" "` for space separated values or to `","` for comma separated values (csv).
- See the notion page discussing this [here](https://www.notion.so/monashhumanpower/Converting-the-V2-DAS-for-wheel-speed-bf6dd023d1bb43e9b83206c37f624c6d).
- Each row contains:
  - Time since the teensy started.
  - The number of rotations since the teensy started.
  - The time it took for the last rotation.
  - The revolutions per minute for the last rotation.
- Data is sent and the LED toggled each time the magnet is brought near the switch.
- All times are in microseconds (µs).

### Saving to a file
#### Using PuTTY (Windows, Mac and Linux)
See [here](https://www.eye4software.com/hydromagic/documentation/articles-and-howtos/serial-port-logging/).

#### Minicom (Linux and Mac)
```
minicom -D /dev/ttyACM0 -C "WheelSpeed_$(date +%H-%M-%S).csv"
```
Picocom and other tools will be similar.

#### Arduino IDE (Windows, Mac and Linux)
This is tedious, but is another option. Simply copy and paste from the serial terminal. In the versions we tested, only the area currently visible on screen can be copied at a time.

### Graphing / analysis
#### Python scripts
[`graph.py`](wheel-rpm-logging/graph.py) is a python file that graphs the angular velocity and angular acceleration over time.

#### Excel / spreadsheets
The output format from the DAS is in a CSV format that most software should be able to import.
