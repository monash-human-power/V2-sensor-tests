import serial
import os
import openpyxl
import pandas as pd



class WheelLogger:

    def __init__(self, port: str, baud_rate: int, fname: str) -> None:
        
        self.port = port
        self.baud_rate = baud_rate
        self.fname = fname

    
    def run(self):

        ser = None
        ser_data = []

        try:
            ser = serial.Serial(self.port, self.baud_rate, timeout=1)

        except Exception as e:
            print("{}".format(e))


        try:

            while True:
                
                data = str(ser.readline().decode()).strip()

                if (len(data)>0) and (data != "Time_us,Rotation_Number,Rotation_Time_us,Angular_V_rad_s,Angular_A_rad_s2,RPM"):

                    print(data.split(","))

        
        except KeyboardInterrupt as e:
            print("{}".format(e))

        print("we're stopping")
        ser.close()

    


    




if __name__=="__main__":

    PORT = "COM3"
    BAUD_RATE = 115200
    FNAME = "WHEELRIG"

    wheelLogger = WheelLogger(PORT, BAUD_RATE, FNAME)
    wheelLogger.run()