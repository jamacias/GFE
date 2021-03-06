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
LIBS:arduino
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
LIBS:ESP8266
LIBS:gy-271
LIBS:gy-gps6mv2
LIBS:hc-sr04
LIBS:ims-1
LIBS:tge589a
LIBS:GFE-cache
EELAYER 25 0
EELAYER END
$Descr A4 8268 11693 portrait
encoding utf-8
Sheet 1 1
Title "Conexionado de los módulos en la iteración 1"
Date ""
Rev "1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Arduino_Mega2560_Shield XA1
U 1 1 5ACA580C
P 4050 4500
F 0 "XA1" V 4150 4500 60  0000 C CNN
F 1 "Arduino_Mega2560_Shield" V 3950 4500 60  0000 C CNN
F 2 "" H 4750 7250 60  0001 C CNN
F 3 "" H 4750 7250 60  0001 C CNN
	1    4050 4500
	0    1    1    0   
$EndComp
$Comp
L HC-SR04 U10
U 1 1 5ACA6762
P 4600 6850
F 0 "U10" V 4150 7050 60  0000 C CNN
F 1 "HC-SR04" V 4250 6900 60  0000 C CNN
F 2 "" H 4600 6850 60  0000 C CNN
F 3 "" H 4600 6850 60  0000 C CNN
	1    4600 6850
	0    -1   -1   0   
$EndComp
$Comp
L ESP-01v090 U13
U 1 1 5ACA6B7A
P 7000 2000
F 0 "U13" H 6400 1600 50  0000 C CNN
F 1 "ESP-01v090" H 6600 2400 50  0000 C CNN
F 2 "" H 7000 2000 50  0001 C CNN
F 3 "" H 7000 2000 50  0001 C CNN
	1    7000 2000
	1    0    0    -1  
$EndComp
$Comp
L GY-GPS6MV2 U12
U 1 1 5ACA7228
P 6900 2800
F 0 "U12" H 6650 2550 60  0000 C CNN
F 1 "GY-GPS6MV2" H 6900 3100 60  0000 C CNN
F 2 "" H 7050 2800 60  0001 C CNN
F 3 "" H 7050 2800 60  0001 C CNN
	1    6900 2800
	1    0    0    -1  
$EndComp
$Comp
L IMS-1 U8
U 1 1 5ACA74DF
P 4100 8450
F 0 "U8" H 3900 8050 60  0000 C CNN
F 1 "IMS-1 (B)" H 4100 8850 60  0000 C CNN
F 2 "" H 3850 8100 60  0001 C CNN
F 3 "" H 3850 8100 60  0001 C CNN
	1    4100 8450
	-1   0    0    -1  
$EndComp
NoConn ~ 7250 1950
NoConn ~ 7250 2050
NoConn ~ 6050 2050
$Comp
L LM317_3PinPackage U6
U 1 1 5ACA8ABF
P 3650 650
F 0 "U6" H 3500 775 50  0000 C CNN
F 1 "LM317T " H 3450 850 50  0000 L CNN
F 2 "" H 3650 900 50  0001 C CIN
F 3 "" H 3650 650 50  0001 C CNN
	1    3650 650 
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 5ACA912E
P 4050 850
F 0 "R3" V 4130 850 50  0000 C CNN
F 1 "200" V 4050 850 50  0000 C CNN
F 2 "" V 3980 850 50  0001 C CNN
F 3 "" H 4050 850 50  0001 C CNN
	1    4050 850 
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 5ACA98AB
P 4050 1250
F 0 "R4" V 4130 1250 50  0000 C CNN
F 1 "330" V 4050 1250 50  0000 C CNN
F 2 "" V 3980 1250 50  0001 C CNN
F 3 "" H 4050 1250 50  0001 C CNN
	1    4050 1250
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 5ACAAF74
P 7400 2150
F 0 "R5" V 7500 2150 50  0000 C CNN
F 1 "1k" V 7400 2150 50  0000 C CNN
F 2 "" V 7330 2150 50  0001 C CNN
F 3 "" H 7400 2150 50  0001 C CNN
	1    7400 2150
	0    1    1    0   
$EndComp
$Comp
L R R6
U 1 1 5ACAAFBA
P 7600 2350
F 0 "R6" V 7680 2350 50  0000 C CNN
F 1 "2k" V 7600 2350 50  0000 C CNN
F 2 "" V 7530 2350 50  0001 C CNN
F 3 "" H 7600 2350 50  0001 C CNN
	1    7600 2350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR5
U 1 1 5ACAB1C6
P 7600 2550
F 0 "#PWR5" H 7600 2300 50  0001 C CNN
F 1 "GND" H 7600 2400 50  0000 C CNN
F 2 "" H 7600 2550 50  0001 C CNN
F 3 "" H 7600 2550 50  0001 C CNN
	1    7600 2550
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR4
U 1 1 5ACAB7BE
P 7400 1900
F 0 "#PWR4" H 7400 1650 50  0001 C CNN
F 1 "GND" H 7400 1750 50  0000 C CNN
F 2 "" H 7400 1900 50  0001 C CNN
F 3 "" H 7400 1900 50  0001 C CNN
	1    7400 1900
	1    0    0    -1  
$EndComp
Text GLabel 6300 2950 0    60   Input ~ 0
GND
Text GLabel 2100 3200 1    60   Input ~ 0
5V
Text GLabel 2800 3200 1    60   Input ~ 0
GND
Text GLabel 6300 2650 0    60   Input ~ 0
5V
Text GLabel 1900 3200 1    60   Input ~ 0
12V
Text GLabel 3200 650  0    60   Input ~ 0
5V
Text GLabel 4250 650  2    60   Input ~ 0
3V3
$Comp
L LM317_3PinPackage U1
U 1 1 5ACB002F
P 1600 650
F 0 "U1" H 1450 775 50  0000 C CNN
F 1 "LM317T " H 1400 850 50  0000 L CNN
F 2 "" H 1600 900 50  0001 C CIN
F 3 "" H 1600 650 50  0001 C CNN
	1    1600 650 
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5ACB0035
P 2000 850
F 0 "R1" V 2080 850 50  0000 C CNN
F 1 "270" V 2000 850 50  0000 C CNN
F 2 "" V 1930 850 50  0001 C CNN
F 3 "" H 2000 850 50  0001 C CNN
	1    2000 850 
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 5ACB003B
P 2000 1250
F 0 "R2" V 2080 1250 50  0000 C CNN
F 1 "2.7k" V 2000 1250 50  0000 C CNN
F 2 "" V 1930 1250 50  0001 C CNN
F 3 "" H 2000 1250 50  0001 C CNN
	1    2000 1250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR2
U 1 1 5ACB0043
P 2000 1450
F 0 "#PWR2" H 2000 1200 50  0001 C CNN
F 1 "GND" H 2000 1300 50  0000 C CNN
F 2 "" H 2000 1450 50  0001 C CNN
F 3 "" H 2000 1450 50  0001 C CNN
	1    2000 1450
	1    0    0    -1  
$EndComp
Text GLabel 1200 650  0    60   Input ~ 0
17V
Text GLabel 2600 650  2    60   Input ~ 0
13V8
Text GLabel 6050 2150 0    60   Input ~ 0
3V3
Text GLabel 6050 1950 0    60   Input ~ 0
3V3
Text GLabel 5350 950  0    60   Input ~ 0
5V
Text GLabel 5350 1050 0    60   Input ~ 0
GND
$Comp
L GND #PWR3
U 1 1 5ACB501F
P 4050 1450
F 0 "#PWR3" H 4050 1200 50  0001 C CNN
F 1 "GND" H 4050 1300 50  0000 C CNN
F 2 "" H 4050 1450 50  0001 C CNN
F 3 "" H 4050 1450 50  0001 C CNN
	1    4050 1450
	1    0    0    -1  
$EndComp
$Comp
L Battery BT1
U 1 1 5ACB61C5
P 1350 2150
F 0 "BT1" H 1450 2250 50  0000 L CNN
F 1 "12V" H 1450 2150 50  0000 L CNN
F 2 "" V 1350 2210 50  0001 C CNN
F 3 "" V 1350 2210 50  0001 C CNN
	1    1350 2150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR1
U 1 1 5ACB65DE
P 1350 2400
F 0 "#PWR1" H 1350 2150 50  0001 C CNN
F 1 "GND" H 1350 2250 50  0000 C CNN
F 2 "" H 1350 2400 50  0001 C CNN
F 3 "" H 1350 2400 50  0001 C CNN
	1    1350 2400
	1    0    0    -1  
$EndComp
Text GLabel 2050 1900 2    60   Input ~ 0
12V
$Comp
L SW_SPST SW1
U 1 1 5ACB6BF5
P 1800 1900
F 0 "SW1" H 1800 2025 50  0000 C CNN
F 1 "SW_SPST" H 1800 1800 50  0000 C CNN
F 2 "" H 1800 1900 50  0001 C CNN
F 3 "" H 1800 1900 50  0001 C CNN
	1    1800 1900
	1    0    0    -1  
$EndComp
$Comp
L SW_SPST SW2
U 1 1 5ACB764D
P 2300 650
F 0 "SW2" H 2300 775 50  0000 C CNN
F 1 "SW_SPST" H 2300 550 50  0000 C CNN
F 2 "" H 2300 650 50  0001 C CNN
F 3 "" H 2300 650 50  0001 C CNN
	1    2300 650 
	1    0    0    -1  
$EndComp
Text GLabel 1250 1900 0    60   Input ~ 0
13V8
NoConn ~ 4550 8650
NoConn ~ 4550 8750
Text GLabel 3650 8250 0    60   Input ~ 0
12V
Text GLabel 3650 8350 0    60   Input ~ 0
GND
Text GLabel 4550 8250 2    60   Input ~ 0
GND
NoConn ~ 4550 8150
$Comp
L IMS-1 U9
U 1 1 5ACBB6FF
P 4100 9400
F 0 "U9" H 3900 9000 60  0000 C CNN
F 1 "IMS-1 (A)" H 4100 9800 60  0000 C CNN
F 2 "" H 3850 9050 60  0001 C CNN
F 3 "" H 3850 9050 60  0001 C CNN
	1    4100 9400
	-1   0    0    -1  
$EndComp
NoConn ~ 4550 9600
NoConn ~ 4550 9700
Text GLabel 3650 9200 0    60   Input ~ 0
12V
Text GLabel 3650 9300 0    60   Input ~ 0
GND
Text GLabel 4550 9200 2    60   Input ~ 0
GND
NoConn ~ 4550 9100
$Comp
L GY-271 U11
U 1 1 5ACBE875
P 5800 1150
F 0 "U11" H 5700 850 50  0000 C CNN
F 1 "GY-271" H 5800 1500 50  0000 C CNN
F 2 "" H 5300 900 50  0001 C CNN
F 3 "" H 5300 900 50  0001 C CNN
	1    5800 1150
	1    0    0    -1  
$EndComp
$Comp
L TGE589A U2
U 1 1 5ACBEC3D
P 2750 8600
F 0 "U2" H 2650 8300 50  0000 C CNN
F 1 "TGE589A" H 2750 8950 50  0000 C CNN
F 2 "" H 2250 8350 50  0001 C CNN
F 3 "" H 2250 8350 50  0001 C CNN
	1    2750 8600
	-1   0    0    -1  
$EndComp
NoConn ~ 3200 8700
NoConn ~ 3200 8600
NoConn ~ 3200 8500
$Comp
L TGE589A U3
U 1 1 5ACBF270
P 2750 9550
F 0 "U3" H 2650 9250 50  0000 C CNN
F 1 "TGE589A" H 2750 9900 50  0000 C CNN
F 2 "" H 2250 9300 50  0001 C CNN
F 3 "" H 2250 9300 50  0001 C CNN
	1    2750 9550
	-1   0    0    -1  
$EndComp
NoConn ~ 3200 9650
NoConn ~ 3200 9550
NoConn ~ 3200 9450
$Comp
L DB15_Female J1
U 1 1 5ACC36FB
P 4100 2500
F 0 "J1" V 4300 3100 50  0000 C CNN
F 1 "DB15_Female" V 4300 2500 50  0000 C CNN
F 2 "" H 4100 2500 50  0001 C CNN
F 3 "" H 4100 2500 50  0001 C CNN
	1    4100 2500
	0    -1   -1   0   
$EndComp
Text GLabel 3400 2800 3    60   Input ~ 0
5V
Text GLabel 4000 2800 3    60   Input ~ 0
GND
Text GLabel 3600 2800 3    60   Input ~ 0
D5
Text GLabel 5900 5800 3    60   Input ~ 0
D5
Wire Wire Line
	4050 1000 4050 1100
Connection ~ 4050 1050
Wire Wire Line
	7600 2550 7600 2500
Wire Wire Line
	7550 2150 7600 2150
Wire Wire Line
	7600 1550 7600 2200
Wire Wire Line
	7400 1900 7400 1850
Wire Wire Line
	7400 1850 7250 1850
Wire Wire Line
	6000 3200 6000 2850
Wire Wire Line
	5900 2750 5900 3200
Wire Wire Line
	5900 2750 6300 2750
Wire Wire Line
	6000 2850 6300 2850
Wire Wire Line
	4050 650  4050 700 
Connection ~ 4050 650 
Wire Wire Line
	2000 1000 2000 1100
Connection ~ 2000 1050
Wire Wire Line
	2000 1450 2000 1400
Wire Wire Line
	1600 950  1600 1050
Wire Wire Line
	2000 650  2000 700 
Connection ~ 2000 650 
Wire Wire Line
	1300 650  1200 650 
Wire Wire Line
	6050 1850 5800 1850
Wire Wire Line
	5800 1850 5800 3200
Wire Wire Line
	5700 3200 5700 1550
Wire Wire Line
	5700 1550 7600 1550
Connection ~ 7600 2150
Wire Wire Line
	5200 1250 5350 1250
Wire Wire Line
	5350 1150 5100 1150
Wire Wire Line
	3650 950  3650 1050
Wire Wire Line
	3650 1050 4050 1050
Wire Wire Line
	3950 650  4250 650 
Wire Wire Line
	3200 650  3350 650 
Wire Wire Line
	4050 1450 4050 1400
Wire Wire Line
	1350 1950 1350 1900
Wire Wire Line
	1350 2350 1350 2400
Wire Wire Line
	1250 1900 1600 1900
Wire Wire Line
	2050 1900 2000 1900
Wire Wire Line
	1600 1050 2000 1050
Wire Wire Line
	1900 650  2100 650 
Wire Wire Line
	2600 650  2500 650 
Connection ~ 1350 1900
Wire Wire Line
	4900 5800 4900 8350
Wire Wire Line
	4900 8350 4550 8350
Wire Wire Line
	5200 5800 5200 8450
Wire Wire Line
	5200 8450 4550 8450
Wire Wire Line
	5300 5800 5300 8550
Wire Wire Line
	5300 8550 4550 8550
Wire Wire Line
	5000 5800 5000 9300
Wire Wire Line
	5000 9300 4550 9300
Wire Wire Line
	5400 5800 5400 9400
Wire Wire Line
	5400 9400 4550 9400
Wire Wire Line
	5500 5800 5500 9500
Wire Wire Line
	5500 9500 4550 9500
Wire Wire Line
	3200 8400 3300 8400
Wire Wire Line
	3300 8400 3300 8550
Wire Wire Line
	3300 8550 3650 8550
Wire Wire Line
	3650 8650 3300 8650
Wire Wire Line
	3300 8650 3300 8800
Wire Wire Line
	3300 8800 3200 8800
Wire Wire Line
	3200 9350 3300 9350
Wire Wire Line
	3300 9350 3300 9500
Wire Wire Line
	3300 9500 3650 9500
Wire Wire Line
	3650 9600 3300 9600
Wire Wire Line
	3300 9600 3300 9750
Wire Wire Line
	3300 9750 3200 9750
Wire Wire Line
	4800 3200 4800 3100
Wire Wire Line
	4800 3100 3800 3100
Wire Wire Line
	3800 3100 3800 2800
Wire Wire Line
	4400 2800 4400 3050
Wire Wire Line
	4400 3050 4700 3050
Wire Wire Line
	4700 3050 4700 3200
Wire Wire Line
	5100 1150 5100 3200
Wire Wire Line
	5200 3200 5200 1250
Text GLabel 4600 2800 3    60   Input ~ 0
D6
Text GLabel 5800 5800 3    60   Input ~ 0
D6
Wire Wire Line
	4300 2800 4300 3150
Wire Wire Line
	4300 3150 4500 3150
Wire Wire Line
	4500 3150 4500 3200
NoConn ~ 4800 2800
NoConn ~ 4700 2800
NoConn ~ 4500 2800
NoConn ~ 4200 2800
NoConn ~ 4100 2800
NoConn ~ 3900 2800
NoConn ~ 3700 2800
NoConn ~ 3500 2800
Text GLabel 4450 6650 1    60   Input ~ 0
5V
Text GLabel 4750 6650 1    60   Input ~ 0
GND
$Comp
L HC-SR04 U7
U 1 1 5ACBB243
P 4000 6850
F 0 "U7" V 3550 7050 60  0000 C CNN
F 1 "HC-SR04" V 3650 6900 60  0000 C CNN
F 2 "" H 4000 6850 60  0000 C CNN
F 3 "" H 4000 6850 60  0000 C CNN
	1    4000 6850
	0    -1   -1   0   
$EndComp
Text GLabel 3850 6650 1    60   Input ~ 0
5V
Text GLabel 4150 6650 1    60   Input ~ 0
GND
$Comp
L HC-SR04 U5
U 1 1 5ACBB2C9
P 3400 6850
F 0 "U5" V 2950 7050 60  0000 C CNN
F 1 "HC-SR04" V 3050 6900 60  0000 C CNN
F 2 "" H 3400 6850 60  0000 C CNN
F 3 "" H 3400 6850 60  0000 C CNN
	1    3400 6850
	0    -1   -1   0   
$EndComp
Text GLabel 3250 6650 1    60   Input ~ 0
5V
Text GLabel 3550 6650 1    60   Input ~ 0
GND
$Comp
L HC-SR04 U4
U 1 1 5ACBB2D1
P 2800 6850
F 0 "U4" V 2350 7050 60  0000 C CNN
F 1 "HC-SR04" V 2450 6900 60  0000 C CNN
F 2 "" H 2800 6850 60  0000 C CNN
F 3 "" H 2800 6850 60  0000 C CNN
	1    2800 6850
	0    -1   -1   0   
$EndComp
Text GLabel 2650 6650 1    60   Input ~ 0
5V
Text GLabel 2950 6650 1    60   Input ~ 0
GND
Wire Wire Line
	4650 6650 4650 5850
Wire Wire Line
	4650 5850 4200 5850
Wire Wire Line
	4200 5850 4200 5800
Wire Wire Line
	4550 6650 4550 6000
Wire Wire Line
	4550 6000 4800 6000
Wire Wire Line
	4800 6000 4800 5800
Wire Wire Line
	4050 6650 4050 5850
Wire Wire Line
	4050 5850 4000 5850
Wire Wire Line
	4000 5850 4000 5800
Wire Wire Line
	3950 6650 3950 5900
Wire Wire Line
	3950 5900 4600 5900
Wire Wire Line
	4600 5900 4600 5800
Wire Wire Line
	3450 6750 3450 6000
Wire Wire Line
	3450 6000 3600 6000
Wire Wire Line
	3600 6000 3600 5800
Wire Wire Line
	3500 5800 3500 5950
Wire Wire Line
	3500 5950 3350 5950
Wire Wire Line
	3350 5950 3350 6750
Wire Wire Line
	3400 5800 3400 5900
Wire Wire Line
	3400 5900 2850 5900
Wire Wire Line
	2850 5900 2850 6650
Wire Wire Line
	2750 6650 2750 5850
Wire Wire Line
	2750 5850 3300 5850
Wire Wire Line
	3300 5850 3300 5800
NoConn ~ 6200 3200
NoConn ~ 6100 3200
NoConn ~ 5600 3200
NoConn ~ 5500 3200
NoConn ~ 5400 3200
NoConn ~ 5300 3200
NoConn ~ 4900 3200
NoConn ~ 4600 3200
NoConn ~ 4400 3200
NoConn ~ 4300 3200
NoConn ~ 4200 3200
NoConn ~ 4100 3200
NoConn ~ 4000 3200
NoConn ~ 3900 3200
NoConn ~ 3800 3200
NoConn ~ 3700 3200
NoConn ~ 3600 3200
NoConn ~ 3500 3200
NoConn ~ 3400 3200
NoConn ~ 3300 3200
NoConn ~ 3100 3200
NoConn ~ 3000 3200
NoConn ~ 2700 3200
NoConn ~ 2600 3200
NoConn ~ 2500 3200
NoConn ~ 2400 3200
NoConn ~ 2300 3200
NoConn ~ 2200 3200
NoConn ~ 2000 3200
NoConn ~ 1900 5800
NoConn ~ 2000 5800
NoConn ~ 2100 5800
NoConn ~ 2200 5800
NoConn ~ 2300 5800
NoConn ~ 2400 5800
NoConn ~ 2500 5800
NoConn ~ 2600 5800
NoConn ~ 2700 5800
NoConn ~ 2800 5800
NoConn ~ 2900 5800
NoConn ~ 3000 5800
NoConn ~ 3100 5800
NoConn ~ 3200 5800
NoConn ~ 3700 5800
NoConn ~ 3800 5800
NoConn ~ 3900 5800
NoConn ~ 4100 5800
NoConn ~ 4500 5800
NoConn ~ 4400 5800
NoConn ~ 4300 5800
NoConn ~ 4700 5800
NoConn ~ 5100 5800
NoConn ~ 5600 5800
NoConn ~ 5700 5800
NoConn ~ 6000 5800
NoConn ~ 6100 5800
NoConn ~ 6200 5800
NoConn ~ 6650 4750
NoConn ~ 6650 4650
NoConn ~ 6650 4550
NoConn ~ 6650 4450
NoConn ~ 6650 4350
NoConn ~ 6650 4250
$EndSCHEMATC
