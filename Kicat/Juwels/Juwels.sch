EESchema Schematic File Version 4
LIBS:Juwels-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L RF_Module:ESP-12F ESP8266
U 1 1 5DB1BBC0
P 1500 1850
F 0 "ESP8266" H 1500 2828 50  0000 C CNN
F 1 "ESP-12F" H 1500 2737 50  0000 C CNN
F 2 "RF_Module:ESP-12E" H 1500 1850 50  0001 C CNN
F 3 "http://wiki.ai-thinker.com/_media/esp8266/esp8266_series_modules_user_manual_v1.1.pdf" H 1150 1950 50  0001 C CNN
	1    1500 1850
	1    0    0    -1  
$EndComp
Text GLabel 6700 1450 2    50   Input ~ 0
VCC_Juwels
Text GLabel 6700 1650 2    50   Input ~ 0
DIn_Juwels
Text GLabel 6700 1850 2    50   Input ~ 0
GND_Juwels
Wire Wire Line
	6200 2550 6200 1850
Wire Wire Line
	6200 1850 6700 1850
$Comp
L Switch:SW_Push SWPRG
U 1 1 5DB20BA9
P 3300 2150
F 0 "SWPRG" H 3300 2435 50  0000 C CNN
F 1 "Program_select" H 3300 2344 50  0000 C CNN
F 2 "" H 3300 2350 50  0001 C CNN
F 3 "" H 3300 2350 50  0001 C CNN
	1    3300 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 2150 3750 1450
$Comp
L Device:R R?
U 1 1 5DB44287
P 2600 2350
F 0 "R?" V 2393 2350 50  0000 C CNN
F 1 "10k" V 2484 2350 50  0000 C CNN
F 2 "" V 2530 2350 50  0001 C CNN
F 3 "~" H 2600 2350 50  0001 C CNN
	1    2600 2350
	-1   0    0    1   
$EndComp
Wire Wire Line
	2100 1650 6700 1650
Wire Wire Line
	1500 1050 3750 1050
Wire Wire Line
	3500 2150 3750 2150
Connection ~ 3750 1450
Wire Wire Line
	3750 1450 3750 1050
Wire Wire Line
	3750 1450 6700 1450
Wire Wire Line
	2100 2150 2600 2150
Wire Wire Line
	1500 2550 2600 2550
Wire Wire Line
	2600 2500 2600 2550
Connection ~ 2600 2550
Wire Wire Line
	2600 2550 6200 2550
Wire Wire Line
	2600 2200 2600 2150
Connection ~ 2600 2150
Wire Wire Line
	2600 2150 3100 2150
$EndSCHEMATC
