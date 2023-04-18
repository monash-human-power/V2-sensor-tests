
#Imports
import serial
import xlwt
from datetime import datetime
import pandas as pd


class WheelLogger:

    def __init__(self, port: str, baud_rate: int, fname: str) -> None:
        
        self.port = port
        self.baud_rate = baud_rate
        self.fname = fname

    
    def run(self):

        ser = None
        ser_data = []

        #Try to set up serial reader
        try:
            ser = serial.Serial(self.port, self.baud_rate, timeout=1)

        except Exception as e:
            print("{}".format(e))

        print("STARTING LOGGING \nPRESS CTRL+C TO STOP\n\n")

        #Read data via serial port
        try:
            while True:
                
                #Convert data from byte to string
                data = str(ser.readline().decode()).strip()

                if (len(data)>0) and (data != "Time_us,Rotation_Number,Rotation_Time_us,Angular_V_rad_s,Angular_A_rad_s2,RPM"):
                    
                    #Format properly and add to data array
                    format_data = list(map(float, data.split(",")))
                    print(format_data)
                    ser_data.append(format_data)

        #Keyboard interrupt
        except KeyboardInterrupt as e:
            print("{}".format(e))
        
        #Once we hit CTRL+C we do the rest of the conversion to excel
        finally:

            #Close serial connnection
            ser.close()

            #File name for excel file
            file_name = self.fname + "_" + datetime.now().strftime("%Y-%m-%d_%H-%M-%S") + ".xlsx"

            #Append to excel file
            df = pd.DataFrame(ser_data, columns=['Time_us' ,' Rotation_Number', 'Rotation_Time_us', 'Angular_V_rad_s', 'Angular_A_rad_s2', 'RPM'])
            df.to_excel(file_name, sheet_name='new_sheet_name', index=False)

            print("\nCTRL+C PRESSED \nWE ARE DONE WITH LOGGING")
    


if __name__=="__main__":

    PORT = "SOME_PORT" #PORT THAT WHEEL RIG IS CONNECTED TO, CHANGE IF YOU HAVEN'T ALREADY
    BAUD_RATE = 115200 #BAUD RATE, DON'T CHANGE UNLESS NECESSARY
    FNAME = "WHEELRIG" #FILENAME CONVENTION

    wheelLogger = WheelLogger(PORT, BAUD_RATE, FNAME)
    wheelLogger.run()