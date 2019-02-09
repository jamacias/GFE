# GFE
Güimar Farm Explorer (GFE) is a low cost autonomous rover that aims at performing assisting and supervising remote farms.

The idea of the project is to be able to monitor a farm by commanding the robot to go to a certain known position and perform certain tasks of interest without having a human to be physically on site. The most recent version, iteration 2, is based on "The bubble rebound obstacle avoidance algorithm" [2]. An array of ultrasonic sensors measure the distance to the objects and if any threat is detected the robot moves navigates on the direction with less density of obstacles. This project is designed to be used in semi-structured environments where the map and the way points that are (most probably) free of obstacles are known.

Please, refer to the documentation inside the project itself for more information.

# BOM:
- Arduino MEGA 2560.
- Raspberry PI.
- 2x Windshield wiper DC motors (TGE5889A).
- 2x IMS-1 motor driver modules.
- 8x Ultrasonic sensors HC-SR04.
- 12V battery.
- LM317T voltage regulator.
- HMC5883L magnetometer.
- GY-GPS6MV2 GPS.
- Quickshot QS-203 joystick.
- Raspberry Pi NoIR camera.

# Libs:
- MOTOR (IMS-1 motor driver) - can be found in libs.
- TinyGPS.
- HMC5883_Simple.

# References:
[1] NDVI with RPi: https://github.com/robintw/RPiNDVI

[2] "The bubble rebound obstacle avoidance algorithm": https://ieeexplore.ieee.org/document/5524302
