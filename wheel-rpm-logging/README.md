
# Logging Serial Data

An introduction on how to log wheel rpm data.

## Setup

1. First the latest version of [python](https://www.python.org/downloads/) must be installed on your device. 
2. The following commands must be run on your terminal to install the necessary libraries.
```
pip install pandas
pip install serial
pip install xlwt
```

3. The serial port the device connects to will be different for different devices, check which port it is connected to and change the line in the file, as show below.
```
PORT = "SOME_PORT"
```


## Running Logger

1. To run the logger first ensure that the spinning wheel rig is connected to your device.
2. Ensure all the setup steps have been completed.
3. Open a terminal and navigate to the folder where the wheel_logger.py file is located.
4. Run the below command
```
python .\wheel_logger.py
```
5. Test as you see fit.
6. On your keyboard press **CTRL + C** to end logging, when you are ready.
7. Excel files with the required data should be created.