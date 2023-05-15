#!/usr/bin/env python3
"""plot_anemometer.py
Plots a graph of the wind speed, direction and temperature over time.
"""

import pandas as pd
from matplotlib import pyplot as plt
from datetime import datetime
import matplotlib.dates as plt_dates
import numpy as np

event_name = "AARC testing 13/05/2023"
data_file = "WindData_2023-05-13_10-19-18.csv"

# Import the data and process it.
wind_data = pd.read_csv(data_file)
wind_data["DateTime"] = wind_data["Time"].apply(
    lambda t: datetime.fromtimestamp(t))

# Plot the wind speed over time
fig = plt.figure(1)
plt.plot(wind_data["DateTime"], wind_data["Avg Speed (m/s)"]
         * 3.6, "tab:blue", label="Average over 1s")

# Smooth and display the rolling average
ave_length = 300
speed_averaged = np.convolve(
    wind_data["Avg Speed (m/s)"]*3.6, np.ones(ave_length) / ave_length, mode="same")
plt.plot(wind_data["DateTime"], speed_averaged, "tab:orange",
         label="Rolling average over 5m")

# Finishing touches
fig.autofmt_xdate()
date_format = plt_dates.DateFormatter('%H:%M')
plt.gca().xaxis.set_major_formatter(date_format)
plt.xlabel("Time")
# plt.ylabel("Wind speed (m/s)")
plt.ylabel("Wind speed (km/h)")
plt.title(f"{event_name} wind speed")
plt.legend()
plt.grid()
plt.show(block=False)

# Plot the wind direction over time
fig = plt.figure(2)
plt.plot(wind_data["DateTime"], wind_data["Avg Dir (Deg)"], "tab:green",
         label="Average over 1s")

# Smooth and display the rolling average
direction_averaged = np.convolve(
    wind_data["Avg Dir (Deg)"], np.ones(ave_length) / ave_length, mode="same")
plt.plot(wind_data["DateTime"], direction_averaged, "tab:red",
         label="Rolling average over 5m")

# Finishing touches
fig.autofmt_xdate()
plt.gca().xaxis.set_major_formatter(date_format)
plt.xlabel("Time")
plt.ylabel("Wind direction (degrees from North)")
plt.title(f"{event_name} wind direction")
plt.legend()
plt.grid()
plt.show(block=False)

# Plot the temperature over time
fig = plt.figure(3)
plt.plot(wind_data["DateTime"], wind_data["Temp (C)"], "tab:purple",
         label="Raw")

# Smooth and display the rolling average
temp_averaged = np.convolve(
    wind_data["Temp (C)"], np.ones(ave_length) / ave_length, mode="same")
plt.plot(wind_data["DateTime"], temp_averaged, "tab:pink",
         label="Rolling average over 5m")

# Finishing touches
fig.autofmt_xdate()
plt.gca().xaxis.set_major_formatter(date_format)
plt.xlabel("Time")
plt.ylabel("Temperature")
plt.title(f"{event_name} anemometer temperature")
plt.legend()
plt.grid()
plt.show(block=True)
