#!/bin/bash

# Export pins to userspace
sudo echo "26" > /sys/class/gpio/export
sleep 0.1
echo "19" > /sys/class/gpio/export
sleep 0.1

# Set pins as an output
sudo echo "out" > /sys/class/gpio/gpio26/direction
sleep 0.1
echo "out" > /sys/class/gpio/gpio19/direction
sleep 0.1

sudo echo "1" > /sys/class/gpio/gpio26/value # Enable = 1 (default); Disable = 0
sleep 0.1
echo "0" > /sys/class/gpio/gpio19/value # Manual = 0 (default); Automatic = 1
