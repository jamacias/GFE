# GFE
Güimar Farm Explorer (GFE) is a low cost autonomous rover that aims at performing assisting and supervising remote farms.

The idea of the project is to be able to monitor a farm by commanding the robot to go to a certain known position and perform certain tasks of interest without having a human to be physically on site. Interesting uses may be related to crop health monitoring using NDVI images, apart from actually harvesting fruits (hopefully!).

The most recent version, iteration 2, is based on ["The bubble rebound obstacle avoidance algorithm"](https://ieeexplore.ieee.org/document/5524302). An array of ultrasonic sensors measure the distance to the objects and if any threat is detected the robot moves navigates on the direction with less density of obstacles. This project is designed to be used in semi-structured environments where the map and the way points that are (most probably) free of obstacles are known. The morphology and motion implemented kept in mind that it is designed to work in a winery with limited space, thus high agility is desired.

Please, refer to Thesis.pdf and the rest of the documentation inside the project itself for more information. Note that some of these are written in Spanish as this is the final project of my B.S. in Electronic Engineering. Nevertheless, all the source code is in English.

## Main features:
- Manual control of the robot using diamond coordinates with a Quickshot QS-203 joystick.
- Autonomous navigation through waypoints marked.
- Obstacle avoidance.
- PI controller for the orientation of the robot.

## Known issues:
- Poor robustness on windy conditions - ultrasonic sensors are very sensible to this noise.
- Lack of sensor fusion for higher accuracy, nor Kalman filtering. Thus, kinematic equations are not really considered.
- Lack of encoders to compensate the shift between the wheels. This is compensated by transforming the system from MISO to SISO by using the orientation as the objective and setting the same values to both motors.
- No continuous trajectory is designed. The vehicle enters on either uses a PI controller to rotate to the correct orientation, or just moves forward in such direction. Considering the orography of the terrain where it was conceived, this might be a constraint anyway.

Even though these issues exist, the robot performs relatively well under certain conditions. It is able to navigate to the desired point with relatively good accuracy. The obstacle avoidance also works well under indoor conditions where the disturbance of the wind is minimal.

## BOM:
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

## Libs:
- MOTOR (IMS-1 motor driver) - can be found in libs.
- TinyGPS.
- HMC5883_Simple.

## References:
[NDVI with RPi](https://github.com/robintw/RPiNDVI)

["The bubble rebound obstacle avoidance algorithm"](https://ieeexplore.ieee.org/document/5524302)
