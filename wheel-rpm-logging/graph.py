#!/usr/bin/env python3
"""graph.py
File that generates a graph of the angular velocity and acceleration over time.
"""
import pandas as pd
from matplotlib import pyplot as plt
import matplotlib
import sys

def print_help():
    print(f"Usage: {sys.argv[0]} CSV_FILE.csv [optional start index] [optional end index]")
    print("If the indexes are not provided, all data is plotted.")
    print("If the indexes are negative, they are relative to the end (-1 is the end, -2 is second last...)")
    exit()

# Configure matplotlib to not cut the right y label off: https://stackoverflow.com/a/17390833
matplotlib.rcParams.update({'figure.autolayout': True})

# Check that the arguments are correct and interpret them
if len(sys.argv) < 2:
    print(f"No arguments given.")
    print_help()

start = 0
end = -1

if len(sys.argv) > 3:
    start = int(sys.argv[2])
    print(f"Start is specified as {start}")

if len(sys.argv) > 3:
    end = int(sys.argv[3])
    print(f"End is specified as {end}")

print(f"Start is {start} and end is {end}.")

if len(sys.argv) > 4:
    print("Too many arguments.")
    print_help()

# Read the csv file
file = sys.argv[1]
print(f"Graphing '{file}'")
data = pd.read_csv(file)

# Graph RPM over time
plt.figure(file)
ax_left = plt.subplot()
ax_right = ax_left.twinx()

# Angular velocity
av = ax_left.plot(data.Time_us[start:end], data.Angular_V_rad_s[start:end], "b", label="Angular velocity")
ax_left.set_ylabel("Angular velocity [rad/s]")

# Angular acceleration
aa = ax_right.plot(data.Time_us[start:end], data.Angular_A_rad_s2[start:end], "r--", label="Angular acceleration")
ax_right.set_ylabel("Angular acceleration [rad/s²]")

# Formatting
ax_left.set_xlabel("System time [μs]")
plt.title("Wheel angular velocity and acceleration over time")

# Ask matplotlib for the plotted objects and their labels
# https://stackoverflow.com/a/10129461
lines_left, labels_left = ax_left.get_legend_handles_labels()
lines_right, labels_right = ax_right.get_legend_handles_labels()
ax_right.legend(lines_left + lines_right, labels_left + labels_right, loc=0)

plt.show()