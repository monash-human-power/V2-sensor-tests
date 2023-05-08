from typing import Any
import serial 
import time

class WindLogger:
    """
    Class to log anemometer code to the terminal.
    """

    def __init__(self, port) -> None:
        """
        Initialise to read data from anemometer and display in console.
        :param port: Serial port the anemometer is connected to.
        """

        self.brate = 19200
        self.sensor = None
        self.port = port
        self.fname = "WindData"
        

    def run(self):
        
        sensor_data = []

        #Try to set up our serial reader
        try:
            self.sensor = serial.Serial(self.port, self.brate)
        except Exception as e:
            print("{}".format(e))

        #Start out logging
        print("STARTING LOGGING \nPRESS CTRL+C TO STOP\n\n")

        try:
            while True:
                
                #Convert data from byte to string
                data = self.sensor.readline().decode('utf-8')
                print(data)

        #Keyboard interrupt
        except KeyboardInterrupt as e:
            print("{}".format(e))
            
        #Once we hit CTRL+C we do the rest of the conversion to excel
        finally:
            pass




if __name__=="__main__":
    
    PORT = "COM7"
    WIND_LOGGER = WindLogger(PORT)
    WIND_LOGGER.run()