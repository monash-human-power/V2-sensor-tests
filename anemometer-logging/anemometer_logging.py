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
        self.sensor = serial.Serial(port, self.brate)



if __name__=="__main__":
    pass