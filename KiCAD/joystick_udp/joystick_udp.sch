EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:arduino
LIBS:ESP8266
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
LIBS:joystick_udp-cache
EELAYER 25 0
EELAYER END
$Descr A4 8268 11693 portrait
encoding utf-8
Sheet 1 1
Title "Conexionado joystick para comunicación UDP"
Date "2018-04-26"
Rev "1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Arduino_Nano_Socket XA1
U 1 1 5AE1D149
P 3900 3950
F 0 "XA1" V 4000 3950 60  0000 C CNN
F 1 "Arduino_Nano_Socket" V 3800 3950 60  0000 C CNN
F 2 "" H 5700 7700 60  0001 C CNN
F 3 "" H 5700 7700 60  0001 C CNN
	1    3900 3950
	1    0    0    -1  
$EndComp
$Comp
L LM317_3PinPackage U1
U 1 1 5AE1D1EA
P 1950 1100
F 0 "U1" H 1800 1225 50  0000 C CNN
F 1 "LM317_3PinPackage" H 1950 1225 50  0000 L CNN
F 2 "" H 1950 1350 50  0001 C CIN
F 3 "" H 1950 1100 50  0001 C CNN
	1    1950 1100
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5AE1D279
P 2300 1300
F 0 "R1" V 2380 1300 50  0000 C CNN
F 1 "200" V 2300 1300 50  0000 C CNN
F 2 "" V 2230 1300 50  0001 C CNN
F 3 "" H 2300 1300 50  0001 C CNN
	1    2300 1300
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 5AE1D2C4
P 2300 1700
F 0 "R2" V 2380 1700 50  0000 C CNN
F 1 "330" V 2300 1700 50  0000 C CNN
F 2 "" V 2230 1700 50  0001 C CNN
F 3 "" H 2300 1700 50  0001 C CNN
	1    2300 1700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR2
U 1 1 5AE1D362
P 2300 1900
F 0 "#PWR2" H 2300 1650 50  0001 C CNN
F 1 "GND" H 2300 1750 50  0000 C CNN
F 2 "" H 2300 1900 50  0001 C CNN
F 3 "" H 2300 1900 50  0001 C CNN
	1    2300 1900
	1    0    0    -1  
$EndComp
Text GLabel 2350 1100 2    60   Input ~ 0
3V3
Text GLabel 1600 1100 0    60   Input ~ 0
Vin
Text GLabel 2600 4850 0    60   Input ~ 0
Vin
$Comp
L GND #PWR3
U 1 1 5AE1D7FE
P 2450 4500
F 0 "#PWR3" H 2450 4250 50  0001 C CNN
F 1 "GND" H 2450 4350 50  0000 C CNN
F 2 "" H 2450 4500 50  0001 C CNN
F 3 "" H 2450 4500 50  0001 C CNN
	1    2450 4500
	1    0    0    -1  
$EndComp
$Comp
L ESP-01v090 U2
U 1 1 5AE1D876
P 6200 3900
F 0 "U2" H 5600 3500 50  0000 C CNN
F 1 "ESP-01v090" H 5800 4300 50  0000 C CNN
F 2 "" H 6200 3900 50  0001 C CNN
F 3 "" H 6200 3900 50  0001 C CNN
	1    6200 3900
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR5
U 1 1 5AE1D8DF
P 5850 4100
F 0 "#PWR5" H 5850 3850 50  0001 C CNN
F 1 "GND" H 5850 3950 50  0000 C CNN
F 2 "" H 5850 4100 50  0001 C CNN
F 3 "" H 5850 4100 50  0001 C CNN
	1    5850 4100
	1    0    0    -1  
$EndComp
Text GLabel 5200 3350 2    60   Input ~ 0
button1
Text GLabel 5200 3450 2    60   Input ~ 0
button2
Text GLabel 7300 3750 2    60   Input ~ 0
3V3
NoConn ~ 7150 3850
NoConn ~ 5950 3950
NoConn ~ 5950 3850
$Comp
L R R3
U 1 1 5AE1E569
P 5500 3950
F 0 "R3" V 5580 3950 50  0000 C CNN
F 1 "2k" V 5500 3950 50  0000 C CNN
F 2 "" V 5430 3950 50  0001 C CNN
F 3 "" H 5500 3950 50  0001 C CNN
	1    5500 3950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR4
U 1 1 5AE1ED36
P 5500 4150
F 0 "#PWR4" H 5500 3900 50  0001 C CNN
F 1 "GND" H 5500 4000 50  0000 C CNN
F 2 "" H 5500 4150 50  0001 C CNN
F 3 "" H 5500 4150 50  0001 C CNN
	1    5500 4150
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 5AE1ED71
P 5700 3750
F 0 "R4" V 5780 3750 50  0000 C CNN
F 1 "1k" V 5700 3750 50  0000 C CNN
F 2 "" V 5630 3750 50  0001 C CNN
F 3 "" H 5700 3750 50  0001 C CNN
	1    5700 3750
	0    1    1    0   
$EndComp
NoConn ~ 2600 3050
NoConn ~ 2600 3150
NoConn ~ 2600 3450
NoConn ~ 2600 3550
NoConn ~ 2600 3650
NoConn ~ 2600 3850
NoConn ~ 2600 4150
NoConn ~ 2600 4250
NoConn ~ 2600 4550
NoConn ~ 2600 4650
NoConn ~ 5200 4650
NoConn ~ 5200 4750
NoConn ~ 5200 4150
NoConn ~ 5200 4050
NoConn ~ 5200 3950
NoConn ~ 5200 3850
NoConn ~ 5200 3550
NoConn ~ 5200 3250
NoConn ~ 5200 3150
NoConn ~ 5200 3050
$Comp
L DB15_Female J1
U 1 1 5B2E7DD5
P 1800 2450
F 0 "J1" H 1820 3300 50  0000 C CNN
F 1 "DB15_Female" H 1800 1575 50  0000 C CNN
F 2 "" H 1800 2450 50  0001 C CNN
F 3 "" H 1800 2450 50  0001 C CNN
	1    1800 2450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1950 1400 1950 1500
Wire Wire Line
	1950 1500 2300 1500
Wire Wire Line
	2300 1450 2300 1550
Connection ~ 2300 1500
Wire Wire Line
	2300 1900 2300 1850
Wire Wire Line
	2250 1100 2350 1100
Wire Wire Line
	2300 1100 2300 1150
Connection ~ 2300 1100
Wire Wire Line
	1650 1100 1600 1100
Wire Wire Line
	2600 4450 2450 4450
Wire Wire Line
	2450 4450 2450 4500
Wire Wire Line
	7150 3950 7250 3950
Wire Wire Line
	7250 3950 7250 3750
Wire Wire Line
	7150 3750 7300 3750
Connection ~ 7250 3750
Wire Wire Line
	5950 4050 5850 4050
Wire Wire Line
	5850 4050 5850 4100
Wire Wire Line
	7550 3350 7550 4050
Wire Wire Line
	7550 4050 7150 4050
Wire Wire Line
	5500 4150 5500 4100
Wire Wire Line
	5200 3750 5550 3750
Wire Wire Line
	5500 3800 5500 3750
Connection ~ 5500 3750
Wire Wire Line
	5850 3750 5950 3750
Wire Wire Line
	7550 3350 5900 3350
Wire Wire Line
	5900 3350 5900 3650
Wire Wire Line
	5900 3650 5200 3650
Wire Wire Line
	1100 2750 1100 4750
Wire Wire Line
	1100 4750 2600 4750
$Comp
L GND #PWR1
U 1 1 5B2E8DC8
P 1700 3200
F 0 "#PWR1" H 1700 2950 50  0001 C CNN
F 1 "GND" H 1700 3050 50  0000 C CNN
F 2 "" H 1700 3200 50  0001 C CNN
F 3 "" H 1700 3200 50  0001 C CNN
	1    1700 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 2750 1700 3200
Wire Wire Line
	2600 4050 1500 4050
Wire Wire Line
	1500 4050 1500 2750
Wire Wire Line
	2600 3950 2100 3950
Wire Wire Line
	2100 3950 2100 2750
Wire Wire Line
	2600 3750 2000 3750
Wire Wire Line
	2000 3750 2000 2750
Text GLabel 1600 2750 3    60   Input ~ 0
button1
Text GLabel 2300 2750 3    60   Input ~ 0
button2
NoConn ~ 2500 2750
NoConn ~ 2400 2750
NoConn ~ 2200 2750
NoConn ~ 1900 2750
NoConn ~ 1800 2750
NoConn ~ 1400 2750
NoConn ~ 1300 2750
NoConn ~ 1200 2750
$EndSCHEMATC
