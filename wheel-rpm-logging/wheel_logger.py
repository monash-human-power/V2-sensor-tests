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
                print("hey")
        
        except KeyboardInterrupt as e:
            print("{}".format(e))

    


    




if __name__=="__main__":

    PORT = "COM3"
    BAUD_RATE = 115200
    FNAME = "WHEELRIG"

    wheelLogger = WheelLogger(PORT, BAUD_RATE, FNAME)
    wheelLogger.run()