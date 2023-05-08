import serial 
from datetime import datetime
import pandas as pd
import time

class WindLogger:
    """
    Class to log anemometer code to the terminal.
    """

    def __init__(self, port):
        """
        Initialise to read data from anemometer and display in console.
        :param port: Serial port the anemometer is connected to.
        """

        self.brate = 19200
        self.sensor = None
        self.port = port
        self.fname = "WindData_" + datetime.now().strftime("%Y-%m-%d_%H-%M-%S") + ".xlsx"
        self.col = ["Time", "Min Dir (Deg)", "Avg Dir (Deg)", "Max Dir (Deg)", "Min Speed (m/s)", "Avg Speed (m/s)", "Max Speed (m/s)", "Temp (C)"] 
        

    def run(self, units=1, rolling_max=5, log_freq=5):
        """
        Run the anemometer logger.

        :param units: either 0 for m/s or 1 for km/h, defaults to 1.
        :param rolling_max: gives the max within a given number of data points, defaults to 5.
        :param log_freq: how frequently we log to the excel file, defaults to every 5 logs.
        """
        
        #Try to set up our serial reader
        try:
            self.sensor = serial.Serial(self.port, self.brate)
        except Exception as e:
            print("{}".format(e))

        #Start out logging
        print("STARTING LOGGING \nPRESS CTRL+C TO STOP\n\n")

        start_max = 0
        roll_max = 0
        factor = 1
        unit_text = "M/S"
        sensor_data = []

        if (units == 1):
            factor = 3.6
            unit_text = "KM/H"

        try:
            while True:
                
                #Convert data from byte to string
                data = self.sensor.readline().decode('utf-8')

                # extract wind direction (deg) data
                min_dir = float(data[7:10])
                avg_dir = float(data[15:18])
                max_dir = float(data[23:26])

                # extract wind speed (m/s) data
                min_speed = float(data[31:34])
                avg_speed = float(data[39:42])
                max_speed = float(data[47:50])

                # extract temp (C)
                temp = float(data[55:59])
                
                #Overall Max Speed
                if max(avg_speed, max_speed) > start_max:
                    start_max = max(avg_speed, max_speed)

                #Rolling Max
                if len(sensor_data) >= rolling_max:
                    roll_data = sensor_data[-rolling_max:]
                    roll_max = max([max(d[5], d[6]) for d in roll_data])

                #Nice print to the console
                print(f"Speed Units: {unit_text}")
                print(f"Current Avg: {round(avg_speed*factor, 2)} \nOverall Max: {round(start_max*factor, 2)} \nRolling Max: {round(roll_max*factor, 2)}\n")
                
                # append new data to our sensor data
                all_data = [time.time(), min_dir, avg_dir, max_dir, min_speed, avg_speed, max_speed, temp]
                sensor_data.append(all_data)

                #every 5 sensor entries we write to excel spreadsheet
                if len(sensor_data) % log_freq == 0:
                    #write to excel file
                    df = pd.DataFrame(sensor_data, columns=self.col)
                    df.to_excel(self.fname, sheet_name="wind_data_sheet", index=False)

        #Keyboard interrupt
        except KeyboardInterrupt as e:
            print("{}".format(e))
            
        #Once we hit CTRL+C we do the rest of the conversion to excel
        finally:

            self.sensor.close()

            #write to excel file
            df = pd.DataFrame(sensor_data, columns=self.col)
            df.to_excel(self.fname, sheet_name="wind_data_sheet", index=False)
            
            #Tell user that logging is done
            print("\nCTRL+C PRESSED \nWE ARE DONE WITH LOGGING")




if __name__=="__main__":
    
    PORT = "SOME_PORT"
    WIND_LOGGER = WindLogger(PORT)
    WIND_LOGGER.run()