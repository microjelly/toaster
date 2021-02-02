EESchema Schematic File Version 4
EELAYER 30 0
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
L Device:LED D2
U 1 1 5FEB80F4
P 6600 3400
F 0 "D2" H 6593 3617 50  0000 C CNN
F 1 "HOT (RED)" H 6593 3526 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric" H 6600 3400 50  0001 C CNN
F 3 "~" H 6600 3400 50  0001 C CNN
	1    6600 3400
	1    0    0    -1  
$EndComp
Text GLabel 7300 3400 2    50   Input ~ 0
3V3
Text GLabel 6250 3400 0    50   Input ~ 0
LED_RED
Wire Wire Line
	7300 3400 7150 3400
Text GLabel 1550 5950 2    50   Input ~ 0
SWIM[ICPCK]
Text GLabel 1550 5850 2    50   Input ~ 0
3V3
Text GLabel 1550 6050 2    50   Input ~ 0
GND
Text GLabel 2950 2900 2    50   Input ~ 0
NRST[RST]
Text GLabel 1450 2150 0    50   Input ~ 0
LED_RED
$Comp
L Switch:SW_Push SW1
U 1 1 5FEBF6AE
P 10150 2150
F 0 "SW1" H 10150 2435 50  0000 C CNN
F 1 "RESET" H 10150 2344 50  0000 C CNN
F 2 "MICROJELLY:TS-1186D-C-A" H 10150 2350 50  0001 C CNN
F 3 "~" H 10150 2350 50  0001 C CNN
	1    10150 2150
	1    0    0    -1  
$EndComp
Text GLabel 10500 2150 2    50   Input ~ 0
GND
Wire Wire Line
	10500 2150 10350 2150
Wire Wire Line
	10350 2150 10350 2350
Connection ~ 10350 2150
Wire Wire Line
	9800 2150 9900 2150
Text GLabel 9500 2350 0    50   Input ~ 0
NRST[RST]
Text GLabel 9500 2150 0    50   Input ~ 0
3V3
$Comp
L Device:LED D3
U 1 1 5FEC417B
P 6900 2550
F 0 "D3" H 6893 2767 50  0000 C CNN
F 1 "POWER (GREEN)" H 6893 2676 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric" H 6900 2550 50  0001 C CNN
F 3 "~" H 6900 2550 50  0001 C CNN
	1    6900 2550
	1    0    0    -1  
$EndComp
Text GLabel 6200 2550 0    50   Input ~ 0
GND
Text GLabel 7250 2550 2    50   Input ~ 0
3V3
Wire Wire Line
	6200 2550 6350 2550
Text GLabel 4600 2650 2    50   Input ~ 0
GND
Text GLabel 4600 3100 2    50   Input ~ 0
GND
Text GLabel 4050 3100 0    50   Input ~ 0
3V3
$Comp
L Regulator_Linear:AMS1117-3.3 U2
U 1 1 5FECBF8A
P 6600 1050
F 0 "U2" H 6600 1292 50  0000 C CNN
F 1 "AMS1117-3.3" H 6600 1201 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 6600 1250 50  0001 C CNN
F 3 "http://www.advanced-monolithic.com/pdf/ds1117.pdf" H 6700 800 50  0001 C CNN
	1    6600 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 1450 6600 1450
Wire Wire Line
	6600 1350 6600 1450
Connection ~ 6600 1450
Wire Wire Line
	6600 1450 6900 1450
Text GLabel 6600 1600 3    50   Input ~ 0
GND
Wire Wire Line
	6600 1600 6600 1450
Text GLabel 7350 1050 2    50   Input ~ 0
3V3
Wire Wire Line
	7200 1450 7200 1050
Wire Wire Line
	7200 1050 6900 1050
Text GLabel 5950 1050 0    50   Input ~ 0
VIN
Wire Wire Line
	6050 1450 6050 1050
Wire Wire Line
	6050 1050 6300 1050
Text GLabel 2450 1350 2    50   Input ~ 0
3V3
Text GLabel 1950 3350 2    50   Input ~ 0
GND
$Comp
L Device:R_Small R1
U 1 1 5FED7A89
P 9700 2150
F 0 "R1" V 9504 2150 50  0000 C CNN
F 1 "10K" V 9595 2150 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 9700 2150 50  0001 C CNN
F 3 "~" H 9700 2150 50  0001 C CNN
	1    9700 2150
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C1
U 1 1 5FED8E6C
P 10150 2350
F 0 "C1" V 10250 2350 50  0000 C CNN
F 1 "0.1uF" V 10350 2350 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 10150 2350 50  0001 C CNN
F 3 "~" H 10150 2350 50  0001 C CNN
	1    10150 2350
	0    1    1    0   
$EndComp
Wire Wire Line
	10250 2350 10350 2350
Wire Wire Line
	9500 2150 9600 2150
Wire Wire Line
	9500 2350 9900 2350
Wire Wire Line
	9900 2150 9900 2350
Connection ~ 9900 2150
Wire Wire Line
	9900 2150 9950 2150
Connection ~ 9900 2350
Wire Wire Line
	9900 2350 10050 2350
$Comp
L Device:R_Small R8
U 1 1 5FEDD604
P 6450 2550
F 0 "R8" V 6646 2550 50  0000 C CNN
F 1 "1K" V 6555 2550 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 6450 2550 50  0001 C CNN
F 3 "~" H 6450 2550 50  0001 C CNN
	1    6450 2550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7050 2550 7250 2550
$Comp
L Device:R_Small R9
U 1 1 5FEDFA7F
P 7050 3400
F 0 "R9" V 7246 3400 50  0000 C CNN
F 1 "51" V 7155 3400 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 7050 3400 50  0001 C CNN
F 3 "~" H 7050 3400 50  0001 C CNN
	1    7050 3400
	0    1    1    0   
$EndComp
Wire Wire Line
	6450 3400 6250 3400
$Comp
L Device:C_Small C5
U 1 1 5FEE1D89
P 4350 2650
F 0 "C5" V 4121 2650 50  0000 C CNN
F 1 "1uF[DNP]" V 4212 2650 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4350 2650 50  0001 C CNN
F 3 "~" H 4350 2650 50  0001 C CNN
	1    4350 2650
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C6
U 1 1 5FEE24BB
P 4350 3100
F 0 "C6" V 4121 3100 50  0000 C CNN
F 1 "0.1uF" V 4212 3100 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4350 3100 50  0001 C CNN
F 3 "~" H 4350 3100 50  0001 C CNN
	1    4350 3100
	0    1    1    0   
$EndComp
Wire Wire Line
	4050 2650 4100 2650
Wire Wire Line
	4050 3100 4250 3100
Wire Wire Line
	4450 3100 4600 3100
Wire Wire Line
	4450 2650 4600 2650
$Comp
L Device:C_Small C7
U 1 1 5FEE58D5
P 6250 1450
F 0 "C7" V 6021 1450 50  0000 C CNN
F 1 "1uF" V 6112 1450 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6250 1450 50  0001 C CNN
F 3 "~" H 6250 1450 50  0001 C CNN
	1    6250 1450
	0    1    1    0   
$EndComp
$Comp
L Device:CP_Small C8
U 1 1 5FEE6095
P 7000 1450
F 0 "C8" V 6775 1450 50  0000 C CNN
F 1 "10uF" V 6866 1450 50  0000 C CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-3216-18_Kemet-A" H 7000 1450 50  0001 C CNN
F 3 "~" H 7000 1450 50  0001 C CNN
	1    7000 1450
	0    1    1    0   
$EndComp
Wire Wire Line
	5950 1050 6050 1050
Connection ~ 6050 1050
Wire Wire Line
	6050 1450 6150 1450
Wire Wire Line
	7100 1450 7200 1450
Wire Wire Line
	7200 1050 7350 1050
Connection ~ 7200 1050
$Comp
L Device:D D1
U 1 1 5FEFB9A6
P 9800 1150
F 0 "D1" V 9754 1230 50  0000 L CNN
F 1 "IN4148WS" V 9845 1230 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-323" H 9800 1150 50  0001 C CNN
F 3 "~" H 9800 1150 50  0001 C CNN
	1    9800 1150
	0    1    1    0   
$EndComp
$Comp
L Device:Buzzer BZ1
U 1 1 5FEFC705
P 10450 1150
F 0 "BZ1" H 10602 1179 50  0000 L CNN
F 1 "Buzzer" H 10602 1088 50  0000 L CNN
F 2 "MICROJELLY:MLT-8530" V 10425 1250 50  0001 C CNN
F 3 "~" V 10425 1250 50  0001 C CNN
	1    10450 1150
	1    0    0    -1  
$EndComp
Text GLabel 9650 1300 0    50   Input ~ 0
GND
Text GLabel 9650 1000 0    50   Input ~ 0
BUZZER
NoConn ~ 3500 5750
Text GLabel 4600 5650 2    50   Input ~ 0
GND
Wire Wire Line
	4450 6350 4500 6350
Wire Wire Line
	4500 6350 4500 6250
Wire Wire Line
	4500 5650 4600 5650
Wire Wire Line
	4450 5650 4500 5650
Connection ~ 4500 5650
Wire Wire Line
	4450 5750 4500 5750
Connection ~ 4500 5750
Wire Wire Line
	4500 5750 4500 5650
Wire Wire Line
	4450 5850 4500 5850
Connection ~ 4500 5850
Wire Wire Line
	4500 5850 4500 5750
Wire Wire Line
	4450 5950 4500 5950
Connection ~ 4500 5950
Wire Wire Line
	4500 5950 4500 5850
Wire Wire Line
	4450 6050 4500 6050
Connection ~ 4500 6050
Wire Wire Line
	4500 6050 4500 5950
Wire Wire Line
	4450 6150 4500 6150
Connection ~ 4500 6150
Wire Wire Line
	4500 6150 4500 6050
Wire Wire Line
	4450 6250 4500 6250
Connection ~ 4500 6250
Wire Wire Line
	4500 6250 4500 6150
Text GLabel 3350 5550 0    50   Input ~ 0
GND
Wire Wire Line
	3500 5650 3450 5650
Wire Wire Line
	3450 5650 3450 5550
Wire Wire Line
	3450 5550 3350 5550
Wire Wire Line
	3450 5550 3500 5550
Connection ~ 3450 5550
Wire Wire Line
	3450 5550 3450 5350
Wire Wire Line
	3450 5350 3500 5350
Text GLabel 4600 6950 2    50   Input ~ 0
GND
Text GLabel 4600 6750 2    50   Input ~ 0
3V3
Text GLabel 4600 6450 2    50   Input ~ 0
SPI_SCK
Wire Wire Line
	4600 6450 4450 6450
Text GLabel 4600 6550 2    50   Input ~ 0
SPI_MOSI
Wire Wire Line
	4600 6550 4450 6550
Text GLabel 1450 2650 0    50   Input ~ 0
SPI_MOSI
Text GLabel 4600 5250 2    50   Input ~ 0
LCD_CS
Wire Wire Line
	4600 5250 4450 5250
Text GLabel 2950 2400 2    50   Input ~ 0
TX
Text GLabel 4600 5450 2    50   Input ~ 0
LCD_CD
Wire Wire Line
	4600 5450 4450 5450
Text GLabel 4600 5350 2    50   Input ~ 0
LCD_RES
Wire Wire Line
	4600 5350 4450 5350
Text GLabel 8700 4850 1    50   Input ~ 0
3V3
Text GLabel 8700 5900 3    50   Input ~ 0
GND
Text GLabel 9200 5200 2    50   Input ~ 0
SPI_SCK
Text GLabel 1450 2750 0    50   Input ~ 0
SPI_MISO
Text GLabel 9200 5300 2    50   Input ~ 0
SPI_MISO
Wire Wire Line
	9100 5200 9200 5200
Wire Wire Line
	9200 5300 9100 5300
Wire Wire Line
	8700 5800 8700 5900
Text GLabel 10550 5600 2    50   Input ~ 0
3V3
Text GLabel 10050 5600 0    50   Input ~ 0
GND
Text GLabel 9200 5500 2    50   Input ~ 0
K_CS
Wire Wire Line
	9100 5500 9200 5500
Text GLabel 8150 5300 0    50   Input ~ 0
T+
Text GLabel 1600 4950 2    50   Input ~ 0
T+
Text GLabel 1600 5050 2    50   Input ~ 0
T-
Text GLabel 8150 5500 0    50   Input ~ 0
T-
Text GLabel 1600 4550 2    50   Input ~ 0
VIN
Text GLabel 1600 4650 2    50   Input ~ 0
GND
Text GLabel 1450 2050 0    50   Input ~ 0
SW0
Text GLabel 2950 2500 2    50   Input ~ 0
RX
Text GLabel 1050 6050 0    50   Input ~ 0
GND
Text GLabel 1050 6250 0    50   Input ~ 0
TX
Text GLabel 1050 6150 0    50   Input ~ 0
RX
$Comp
L Transistor_FET:2N7002 Q1
U 1 1 5FF88B00
P 6550 4750
F 0 "Q1" H 6754 4796 50  0000 L CNN
F 1 "2N7002" H 6754 4705 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 6750 4675 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/NDS7002A-D.PDF" H 6550 4750 50  0001 L CNN
	1    6550 4750
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:2N7002 Q2
U 1 1 5FF8F9B7
P 6550 5700
F 0 "Q2" H 6754 5746 50  0000 L CNN
F 1 "2N7002" H 6754 5655 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 6750 5625 50  0001 L CIN
F 3 "https://www.onsemi.com/pub/Collateral/NDS7002A-D.PDF" H 6550 5700 50  0001 L CNN
	1    6550 5700
	1    0    0    -1  
$EndComp
Text GLabel 1600 4750 2    50   Input ~ 0
SSR0
Text GLabel 6800 5500 2    50   Input ~ 0
SSR1
Text GLabel 6800 4550 2    50   Input ~ 0
SSR0
Text GLabel 1600 4850 2    50   Input ~ 0
SSR1
Wire Wire Line
	6650 4550 6800 4550
Wire Wire Line
	6800 5500 6650 5500
$Comp
L Device:R_Small R6
U 1 1 5FFAE1FA
P 6200 4900
F 0 "R6" H 6259 4946 50  0000 L CNN
F 1 "10K" H 6259 4855 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 6200 4900 50  0001 C CNN
F 3 "~" H 6200 4900 50  0001 C CNN
	1    6200 4900
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW2
U 1 1 5FFF837C
P 10150 3400
F 0 "SW2" H 10150 3685 50  0000 C CNN
F 1 "ACTION" H 10150 3594 50  0000 C CNN
F 2 "MICROJELLY:UK-B0229-G2.5-B-250" H 10150 3600 50  0001 C CNN
F 3 "~" H 10150 3600 50  0001 C CNN
	1    10150 3400
	1    0    0    -1  
$EndComp
Text GLabel 10500 3400 2    50   Input ~ 0
GND
Wire Wire Line
	10500 3400 10350 3400
Wire Wire Line
	10350 3400 10350 3600
Connection ~ 10350 3400
Wire Wire Line
	9800 3400 9900 3400
Text GLabel 9500 3600 0    50   Input ~ 0
SW0
Text GLabel 9500 3400 0    50   Input ~ 0
3V3
$Comp
L Device:R_Small R2
U 1 1 5FFF87D3
P 9700 3400
F 0 "R2" V 9504 3400 50  0000 C CNN
F 1 "10K" V 9595 3400 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 9700 3400 50  0001 C CNN
F 3 "~" H 9700 3400 50  0001 C CNN
	1    9700 3400
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C2
U 1 1 5FFF87DD
P 10150 3600
F 0 "C2" V 10250 3600 50  0000 C CNN
F 1 "0.1uF" V 10350 3600 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 10150 3600 50  0001 C CNN
F 3 "~" H 10150 3600 50  0001 C CNN
	1    10150 3600
	0    1    1    0   
$EndComp
Wire Wire Line
	10250 3600 10350 3600
Wire Wire Line
	9500 3400 9600 3400
Wire Wire Line
	9500 3600 9900 3600
Wire Wire Line
	9900 3400 9900 3600
Connection ~ 9900 3400
Wire Wire Line
	9900 3400 9950 3400
Connection ~ 9900 3600
Wire Wire Line
	9900 3600 10050 3600
Text GLabel 6800 5050 2    50   Input ~ 0
GND
Text GLabel 6100 4750 0    50   Input ~ 0
_SSR0
Text GLabel 6100 5700 0    50   Input ~ 0
_SSR1
Wire Wire Line
	6800 5050 6650 5050
Wire Wire Line
	6650 5050 6650 4950
Wire Wire Line
	6200 5000 6200 5050
Wire Wire Line
	6200 5050 6650 5050
Connection ~ 6650 5050
Wire Wire Line
	6350 4750 6200 4750
Wire Wire Line
	6200 4750 6200 4800
Wire Wire Line
	6200 4750 6100 4750
Connection ~ 6200 4750
Text GLabel 6800 6050 2    50   Input ~ 0
GND
Wire Wire Line
	6650 6050 6650 5900
Wire Wire Line
	6650 6050 6800 6050
Wire Wire Line
	6100 5700 6250 5700
$Comp
L Device:R_Small R7
U 1 1 60034F59
P 6250 5900
F 0 "R7" H 6309 5946 50  0000 L CNN
F 1 "10K" H 6309 5855 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 6250 5900 50  0001 C CNN
F 3 "~" H 6250 5900 50  0001 C CNN
	1    6250 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 5800 6250 5700
Connection ~ 6250 5700
Wire Wire Line
	6250 5700 6350 5700
Wire Wire Line
	6250 6000 6250 6050
Wire Wire Line
	6250 6050 6650 6050
Connection ~ 6650 6050
$Comp
L Device:R_Small R3
U 1 1 5FF2AAD0
P 3250 5250
F 0 "R3" V 3054 5250 50  0000 C CNN
F 1 "15" V 3145 5250 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 3250 5250 50  0001 C CNN
F 3 "~" H 3250 5250 50  0001 C CNN
	1    3250 5250
	0    1    1    0   
$EndComp
Wire Wire Line
	3350 5250 3500 5250
$Comp
L Device:R_POT_Small RV1
U 1 1 5FF34C3B
P 2900 5250
F 0 "RV1" H 2840 5296 50  0000 R CNN
F 1 "1K" H 2840 5205 50  0000 R CNN
F 2 "MICROJELLY:Potentiometer_Bourns_TC33X_Vertical" H 2900 5250 50  0001 C CNN
F 3 "~" H 2900 5250 50  0001 C CNN
	1    2900 5250
	1    0    0    -1  
$EndComp
Text GLabel 2900 5050 1    50   Input ~ 0
3V3
Wire Wire Line
	2900 5050 2900 5150
Wire Wire Line
	3000 5250 3150 5250
NoConn ~ 2900 5350
Wire Wire Line
	6550 2550 6750 2550
Wire Wire Line
	6950 3400 6750 3400
$Comp
L MICROJELLY:MAX6675ISA+T U3
U 1 1 600B9718
P 8700 5400
F 0 "U3" H 8450 5900 50  0000 C CNN
F 1 "MAX6675ISA+T" H 8250 5800 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 9700 5050 50  0001 C CIN
F 3 "http://datasheets.maximintegrated.com/en/ds/MAX31855.pdf" H 8700 5400 50  0001 C CNN
	1    8700 5400
	1    0    0    -1  
$EndComp
$Comp
L MICROJELLY:ERC12864-10 J1
U 1 1 600D30D4
P 4000 6150
F 0 "J1" H 3975 7337 60  0000 C CNN
F 1 "ERC12864-10" H 3975 7231 60  0000 C CNN
F 2 "MICROJELLY:ER-CON30HB-1" H 3500 7050 60  0001 C CNN
F 3 "" H 3500 7050 60  0001 C CNN
	1    4000 6150
	1    0    0    -1  
$EndComp
$Comp
L MICROJELLY:STM8S[N76E] U1
U 1 1 60155462
P 2200 2350
F 0 "U1" H 2200 3531 50  0000 C CNN
F 1 "STM8S[N76E]" H 2200 3440 50  0000 C CNN
F 2 "Package_SO:TSSOP-20_4.4x6.5mm_P0.65mm" H 2250 3450 50  0001 L CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00024550.pdf" H 2150 1950 50  0001 C CNN
	1    2200 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 1350 2450 1350
Wire Wire Line
	1900 3350 1950 3350
$Comp
L Device:R_Small R5
U 1 1 60167B52
P 4350 2250
F 0 "R5" V 4550 2250 50  0000 L CNN
F 1 "DNP[0]" V 4450 2100 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 4350 2250 50  0001 C CNN
F 3 "~" H 4350 2250 50  0001 C CNN
	1    4350 2250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4250 2250 4100 2250
Wire Wire Line
	4100 2250 4100 2650
Connection ~ 4100 2650
Wire Wire Line
	4100 2650 4250 2650
Text GLabel 4600 2250 2    50   Input ~ 0
ICPDAT
Wire Wire Line
	4600 2250 4450 2250
Text GLabel 2950 3000 2    50   Input ~ 0
VCAP[ICPDA]
Wire Wire Line
	2950 3000 2800 3000
Text GLabel 4050 2650 0    50   Input ~ 0
VCAP[ICPDA]
Wire Wire Line
	2800 2900 2950 2900
Text GLabel 1550 6150 2    50   Input ~ 0
NRST[RST]
Text GLabel 2950 3100 2    50   Input ~ 0
SWIM[ICPCK]
Wire Wire Line
	2800 3100 2950 3100
Wire Wire Line
	1600 2050 1450 2050
Wire Wire Line
	1450 2150 1600 2150
Wire Wire Line
	1600 2750 1450 2750
Text GLabel 1550 6250 2    50   Input ~ 0
ICPDAT
$Comp
L Connector:Conn_01x03_Male J5
U 1 1 601FC65E
P 1100 7150
F 0 "J5" H 1208 7431 50  0000 C CNN
F 1 "SERVO" H 1208 7340 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 1100 7150 50  0001 C CNN
F 3 "~" H 1100 7150 50  0001 C CNN
	1    1100 7150
	1    0    0    -1  
$EndComp
Text GLabel 1450 7250 2    50   Input ~ 0
GND
Wire Wire Line
	1450 7250 1300 7250
Text GLabel 1450 7150 2    50   Input ~ 0
3V3
Wire Wire Line
	1300 7150 1450 7150
Wire Wire Line
	2800 2400 2950 2400
Wire Wire Line
	2800 2500 2950 2500
$Comp
L Connector:Conn_01x06_Male J2
U 1 1 60223278
P 1250 4750
F 0 "J2" H 1358 5131 50  0000 C CNN
F 1 "Terminal Block" H 1358 5040 50  0000 C CNN
F 2 "MICROJELLY:HT396V-3.96-6p" H 1250 4750 50  0001 C CNN
F 3 "~" H 1250 4750 50  0001 C CNN
	1    1250 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 4550 1600 4550
Wire Wire Line
	1450 4650 1600 4650
Wire Wire Line
	1600 4750 1450 4750
Wire Wire Line
	1450 4850 1600 4850
Wire Wire Line
	1600 4950 1450 4950
Wire Wire Line
	1450 5050 1600 5050
Text GLabel 1450 7050 2    50   Input ~ 0
SRV0
Wire Wire Line
	1300 7050 1450 7050
Text GLabel 1450 2350 0    50   Input ~ 0
SRV0
Wire Wire Line
	1450 2350 1600 2350
Text GLabel 1450 2450 0    50   Input ~ 0
LCD_CS
Wire Wire Line
	1450 2450 1600 2450
Text GLabel 1450 1750 0    50   Input ~ 0
LCD_RES
Wire Wire Line
	1450 1750 1600 1750
Text GLabel 2950 1850 2    50   Input ~ 0
LCD_CD
Wire Wire Line
	2800 1850 2950 1850
Text GLabel 1450 2550 0    50   Input ~ 0
SPI_SCK
Wire Wire Line
	1600 2550 1450 2550
Wire Wire Line
	1600 2650 1450 2650
Text GLabel 1450 1650 0    50   Input ~ 0
K_CS
Wire Wire Line
	1450 1650 1600 1650
Text GLabel 2950 2050 2    50   Input ~ 0
BUZZER
Wire Wire Line
	2950 2050 2800 2050
Text GLabel 4600 1500 2    50   Input ~ 0
GND
Text GLabel 4050 1500 0    50   Input ~ 0
SRV0
Wire Wire Line
	4050 1500 4250 1500
Wire Wire Line
	4450 1500 4600 1500
$Comp
L Device:R_Small R4
U 1 1 602F4E9D
P 4350 1500
F 0 "R4" V 4546 1500 50  0000 C CNN
F 1 "10K" V 4455 1500 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 4350 1500 50  0001 C CNN
F 3 "~" H 4350 1500 50  0001 C CNN
	1    4350 1500
	0    1    1    0   
$EndComp
Text GLabel 2950 1950 2    50   Input ~ 0
_SSR0
Wire Wire Line
	2950 1950 2800 1950
Text GLabel 1450 1850 0    50   Input ~ 0
_SSR1
Wire Wire Line
	1450 1850 1600 1850
$Comp
L Device:C_Small C10
U 1 1 6030A57B
P 10300 5600
F 0 "C10" V 10071 5600 50  0000 C CNN
F 1 "1uF" V 10162 5600 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 10300 5600 50  0001 C CNN
F 3 "~" H 10300 5600 50  0001 C CNN
	1    10300 5600
	0    1    1    0   
$EndComp
Wire Wire Line
	10050 5600 10200 5600
Wire Wire Line
	10400 5600 10550 5600
$Comp
L Device:C_Small C9
U 1 1 6031D01B
P 10300 5100
F 0 "C9" V 10071 5100 50  0000 C CNN
F 1 ".01uF" V 10162 5100 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 10300 5100 50  0001 C CNN
F 3 "~" H 10300 5100 50  0001 C CNN
	1    10300 5100
	0    1    1    0   
$EndComp
Text GLabel 10050 5100 0    50   Input ~ 0
T+
Text GLabel 10550 5100 2    50   Input ~ 0
T-
Wire Wire Line
	10050 5100 10200 5100
Wire Wire Line
	10550 5100 10400 5100
Wire Wire Line
	8150 5500 8300 5500
Wire Wire Line
	8300 5300 8150 5300
Wire Wire Line
	8700 4850 8700 5000
Wire Notes Line
	7600 4250 11050 4250
Wire Notes Line
	11050 4250 11050 6350
Wire Notes Line
	11050 6350 7600 6350
Wire Notes Line
	7600 6350 7600 4250
$Comp
L Device:C_Small C3
U 1 1 6039E003
P 3050 6250
F 0 "C3" V 2821 6250 50  0000 C CNN
F 1 "10uF" V 2912 6250 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3050 6250 50  0001 C CNN
F 3 "~" H 3050 6250 50  0001 C CNN
	1    3050 6250
	0    1    1    0   
$EndComp
Text GLabel 3250 6250 2    50   Input ~ 0
3V3
Text GLabel 2850 6250 0    50   Input ~ 0
GND
Wire Wire Line
	2850 6250 2950 6250
Wire Wire Line
	3150 6250 3250 6250
$Comp
L Device:C_Small C4
U 1 1 603B13C8
P 3050 6650
F 0 "C4" V 2821 6650 50  0000 C CNN
F 1 "0.1uF" V 2912 6650 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3050 6650 50  0001 C CNN
F 3 "~" H 3050 6650 50  0001 C CNN
	1    3050 6650
	0    1    1    0   
$EndComp
Text GLabel 3250 6650 2    50   Input ~ 0
3V3
Text GLabel 2850 6650 0    50   Input ~ 0
GND
Wire Wire Line
	2850 6650 2950 6650
Wire Wire Line
	3150 6650 3250 6650
Wire Wire Line
	4450 6750 4600 6750
Wire Wire Line
	4450 6950 4600 6950
Wire Notes Line
	7450 4250 7450 6350
Wire Notes Line
	7450 6350 5450 6350
Wire Notes Line
	5450 6350 5450 4250
Wire Notes Line
	5450 4250 7450 4250
Wire Notes Line
	5300 4250 5300 7550
Wire Notes Line
	5300 7550 2500 7550
Wire Notes Line
	2500 7550 2500 4250
Wire Notes Line
	2500 4250 5300 4250
Wire Notes Line
	10900 4050 9150 4050
Wire Notes Line
	9150 4050 9150 2900
Wire Notes Line
	9150 2900 10900 2900
Wire Notes Line
	10900 2900 10900 4050
Wire Notes Line
	10900 1600 10900 2750
Wire Notes Line
	10900 1450 9150 1450
Wire Notes Line
	9150 1450 9150 750 
Wire Notes Line
	9150 750  10900 750 
Wire Notes Line
	10900 750  10900 1450
Wire Wire Line
	9650 1000 9800 1000
Wire Wire Line
	9800 1000 10050 1000
Wire Wire Line
	10050 1000 10050 1050
Wire Wire Line
	10050 1050 10350 1050
Connection ~ 9800 1000
Wire Wire Line
	9650 1300 9800 1300
Wire Wire Line
	9800 1300 10050 1300
Wire Wire Line
	10050 1300 10050 1250
Wire Wire Line
	10050 1250 10350 1250
Connection ~ 9800 1300
Wire Notes Line
	600  4050 600  600 
Wire Notes Line
	600  600  5300 600 
Wire Notes Line
	5300 600  5300 4050
Wire Notes Line
	600  4050 5300 4050
Wire Notes Line
	5450 4050 7750 4050
Wire Notes Line
	7750 4050 7750 2100
Wire Notes Line
	7750 2100 5450 2100
Wire Notes Line
	5450 2100 5450 4050
Wire Notes Line
	5450 1950 5450 600 
Wire Notes Line
	5450 600  7750 600 
Wire Notes Line
	7750 600  7750 1950
Wire Notes Line
	7750 1950 5450 1950
Wire Notes Line
	600  4150 600  5350
Wire Notes Line
	600  5350 2200 5350
Wire Notes Line
	2200 5350 2200 4150
Wire Notes Line
	2200 4150 600  4150
Wire Notes Line
	8900 1600 8900 2750
Wire Notes Line
	8900 2750 10900 2750
Wire Notes Line
	8900 1600 10900 1600
$Comp
L Connector_Generic:Conn_02x05_Odd_Even J3
U 1 1 6016ECE9
P 1250 6050
F 0 "J3" H 1300 6467 50  0000 C CNN
F 1 "ISP/UART" H 1300 6376 50  0000 C CNN
F 2 "MICROJELLY:TRUDEAU_C2X5_SMD" H 1250 6050 50  0001 C CNN
F 3 "~" H 1250 6050 50  0001 C CNN
	1    1250 6050
	1    0    0    -1  
$EndComp
Text GLabel 1050 5850 0    50   Input ~ 0
3V3
Text GLabel 1050 5950 0    50   Input ~ 0
GND
Wire Notes Line
	2200 5500 600  5500
Wire Notes Line
	600  5500 600  6550
Wire Notes Line
	600  6550 2200 6550
Wire Notes Line
	2200 6550 2200 5500
Wire Notes Line
	600  6700 2200 6700
Wire Notes Line
	2200 6700 2200 7550
Wire Notes Line
	2200 7550 600  7550
Wire Notes Line
	600  7550 600  6700
$EndSCHEMATC
