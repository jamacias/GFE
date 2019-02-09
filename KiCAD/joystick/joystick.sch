EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:joystick-cache
EELAYER 25 0
EELAYER END
$Descr A4 8268 11693 portrait
encoding utf-8
Sheet 1 1
Title "Circuito interior del joystick"
Date ""
Rev "1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L R R1
U 1 1 5ACB559B
P 4500 4850
F 0 "R1" V 4580 4850 50  0000 C CNN
F 1 "2k" V 4500 4850 50  0000 C CNN
F 2 "" V 4430 4850 50  0001 C CNN
F 3 "" H 4500 4850 50  0001 C CNN
	1    4500 4850
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 5ACB561B
P 5100 4850
F 0 "R2" V 5180 4850 50  0000 C CNN
F 1 "2k" V 5100 4850 50  0000 C CNN
F 2 "" V 5030 4850 50  0001 C CNN
F 3 "" H 5100 4850 50  0001 C CNN
	1    5100 4850
	1    0    0    -1  
$EndComp
$Comp
L POT RV1
U 1 1 5ACB563B
P 2400 5050
F 0 "RV1" V 2225 5050 50  0000 C CNN
F 1 "0-100k" V 2300 5050 50  0000 C CNN
F 2 "" H 2400 5050 50  0001 C CNN
F 3 "" H 2400 5050 50  0001 C CNN
	1    2400 5050
	1    0    0    -1  
$EndComp
$Comp
L POT RV2
U 1 1 5ACB5673
P 3150 5050
F 0 "RV2" V 2975 5050 50  0000 C CNN
F 1 "0-100k" V 3050 5050 50  0000 C CNN
F 2 "" H 3150 5050 50  0001 C CNN
F 3 "" H 3150 5050 50  0001 C CNN
	1    3150 5050
	1    0    0    -1  
$EndComp
$Comp
L POT RV3
U 1 1 5ACB56A1
P 3900 5050
F 0 "RV3" V 3725 5050 50  0000 C CNN
F 1 "0-100k" V 3800 5050 50  0000 C CNN
F 2 "" H 3900 5050 50  0001 C CNN
F 3 "" H 3900 5050 50  0001 C CNN
	1    3900 5050
	1    0    0    -1  
$EndComp
$Comp
L SW_Push SW1
U 1 1 5ACB56EA
P 4500 5300
F 0 "SW1" H 4550 5400 50  0000 L CNN
F 1 "SW_Push" H 4500 5240 50  0000 C CNN
F 2 "" H 4500 5500 50  0001 C CNN
F 3 "" H 4500 5500 50  0001 C CNN
	1    4500 5300
	0    1    1    0   
$EndComp
$Comp
L SW_Push SW2
U 1 1 5ACB5805
P 5100 5300
F 0 "SW2" H 5150 5400 50  0000 L CNN
F 1 "SW_Push" H 5100 5240 50  0000 C CNN
F 2 "" H 5100 5500 50  0001 C CNN
F 3 "" H 5100 5500 50  0001 C CNN
	1    5100 5300
	0    1    1    0   
$EndComp
$Comp
L DB15_Male J1
U 1 1 5ACB5952
P 6350 5100
F 0 "J1" H 6370 5950 50  0000 C CNN
F 1 "DB15_Male" H 6350 4225 50  0000 C CNN
F 2 "" H 6350 5100 50  0001 C CNN
F 3 "" H 6350 5100 50  0001 C CNN
	1    6350 5100
	1    0    0    -1  
$EndComp
Text GLabel 3900 4550 1    60   Input ~ 0
5V
Text GLabel 6050 5800 0    60   Input ~ 0
5V
Text GLabel 4050 5050 2    60   Input ~ 0
z_axis
Text GLabel 3300 5050 2    60   Input ~ 0
y_axis
Text GLabel 2550 5050 2    60   Input ~ 0
x_axis
Text GLabel 4600 5050 2    60   Input ~ 0
button1
Text GLabel 5200 5050 2    60   Input ~ 0
button2
Wire Wire Line
	4500 5000 4500 5100
Wire Wire Line
	4600 5050 4500 5050
Connection ~ 4500 5050
Wire Wire Line
	5100 5000 5100 5100
Wire Wire Line
	5200 5050 5100 5050
Connection ~ 5100 5050
Wire Wire Line
	5100 5550 5100 5500
Wire Wire Line
	2400 5550 5100 5550
Wire Wire Line
	2400 5550 2400 5200
Wire Wire Line
	3150 5200 3150 5550
Connection ~ 3150 5550
Wire Wire Line
	3900 5200 3900 5650
Connection ~ 3900 5550
Wire Wire Line
	4500 5500 4500 5550
Connection ~ 4500 5550
Wire Wire Line
	5100 4650 5100 4700
Wire Wire Line
	2400 4650 5100 4650
Wire Wire Line
	2400 4650 2400 4900
Wire Wire Line
	3150 4900 3150 4650
Connection ~ 3150 4650
Wire Wire Line
	3900 4550 3900 4900
Connection ~ 3900 4650
Wire Wire Line
	4500 4700 4500 4650
Connection ~ 4500 4650
Text GLabel 3900 5650 3    60   Input ~ 0
GND
Text GLabel 6050 5200 0    60   Input ~ 0
GND
Text GLabel 6050 5600 0    60   Input ~ 0
button1
Text GLabel 6050 5400 0    60   Input ~ 0
x_axis
Text GLabel 6050 4800 0    60   Input ~ 0
y_axis
Text GLabel 6050 4900 0    60   Input ~ 0
z_axis
Text GLabel 6050 4600 0    60   Input ~ 0
button2
NoConn ~ 6050 4400
NoConn ~ 6050 4500
NoConn ~ 6050 4700
NoConn ~ 6050 5000
NoConn ~ 6050 5100
NoConn ~ 6050 5500
NoConn ~ 6050 5300
NoConn ~ 6050 5700
$EndSCHEMATC
