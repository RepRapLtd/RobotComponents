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
Wire Wire Line
	6150 2975 6150 3075
Wire Wire Line
	6150 3075 6225 3075
Wire Wire Line
	7150 3075 7150 2975
Wire Wire Line
	6150 1275 6150 1175
Wire Wire Line
	6150 1175 7150 1175
Wire Wire Line
	7150 1175 7150 1275
$Comp
L Connector:Conn_01x02_Male J5
U 1 1 615B3FB9
P 2275 3700
F 0 "J5" H 2383 3881 50  0000 C CNN
F 1 "PWR" H 2383 3790 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 2275 3700 50  0001 C CNN
F 3 "~" H 2275 3700 50  0001 C CNN
	1    2275 3700
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Male J3
U 1 1 615B4674
P 2250 2625
F 0 "J3" H 2358 2906 50  0000 C CNN
F 1 "MOTOR" H 2358 2815 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 2250 2625 50  0001 C CNN
F 3 "~" H 2250 2625 50  0001 C CNN
	1    2250 2625
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x05_Male J2
U 1 1 615B5762
P 2250 1925
F 0 "J2" H 2358 2306 50  0000 C CNN
F 1 "HALL" H 2358 2215 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 2250 1925 50  0001 C CNN
F 3 "~" H 2250 1925 50  0001 C CNN
	1    2250 1925
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 615C4DC4
P 2925 3900
F 0 "#PWR0101" H 2925 3650 50  0001 C CNN
F 1 "GND" H 2930 3727 50  0000 C CNN
F 2 "" H 2925 3900 50  0001 C CNN
F 3 "" H 2925 3900 50  0001 C CNN
	1    2925 3900
	1    0    0    -1  
$EndComp
$Comp
L power:VSS #PWR0102
U 1 1 615C52DE
P 2925 3550
F 0 "#PWR0102" H 2925 3400 50  0001 C CNN
F 1 "VSS" H 2940 3723 50  0000 C CNN
F 2 "" H 2925 3550 50  0001 C CNN
F 3 "" H 2925 3550 50  0001 C CNN
	1    2925 3550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 615C819F
P 6225 3175
F 0 "#PWR0103" H 6225 2925 50  0001 C CNN
F 1 "GND" H 6230 3002 50  0000 C CNN
F 2 "" H 6225 3175 50  0001 C CNN
F 3 "" H 6225 3175 50  0001 C CNN
	1    6225 3175
	1    0    0    -1  
$EndComp
Wire Wire Line
	2475 3700 2925 3700
Wire Wire Line
	2925 3700 2925 3575
Wire Wire Line
	2925 3800 2925 3875
Text GLabel 2600 2725 2    50   Input ~ 0
PHASE3
Text GLabel 2600 2625 2    50   Input ~ 0
PHASE2
Text GLabel 2600 2525 2    50   Input ~ 0
PHASE1
Wire Wire Line
	2600 2725 2450 2725
Wire Wire Line
	2600 2625 2450 2625
Wire Wire Line
	2600 2525 2450 2525
$Comp
L power:GND #PWR0105
U 1 1 615CBCF5
P 2775 2125
F 0 "#PWR0105" H 2775 1875 50  0001 C CNN
F 1 "GND" H 2780 1952 50  0000 C CNN
F 2 "" H 2775 2125 50  0001 C CNN
F 3 "" H 2775 2125 50  0001 C CNN
	1    2775 2125
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0106
U 1 1 615CC61D
P 2525 1725
F 0 "#PWR0106" H 2525 1575 50  0001 C CNN
F 1 "+5V" H 2540 1898 50  0000 C CNN
F 2 "" H 2525 1725 50  0001 C CNN
F 3 "" H 2525 1725 50  0001 C CNN
	1    2525 1725
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 2125 2775 2125
Wire Wire Line
	2450 1725 2525 1725
Text GLabel 3650 2025 2    50   Input ~ 0
HALL3
Text GLabel 3275 1925 2    50   Input ~ 0
HALL2
Text GLabel 2925 1825 2    50   Input ~ 0
HALL1
Text GLabel 2550 1025 2    50   Input ~ 0
BRAKE
Text GLabel 2550 925  2    50   Input ~ 0
F-R
Text GLabel 3225 825  2    50   Input ~ 0
ENABLE
Text GLabel 4325 725  2    50   Input ~ 0
VREF
Wire Wire Line
	6225 3175 6225 3075
Connection ~ 6225 3075
Wire Wire Line
	6225 3075 6800 3075
$Comp
L Device:C C2
U 1 1 615D745E
P 3125 3725
F 0 "C2" H 3240 3771 50  0000 L CNN
F 1 "0.1u" H 3240 3680 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3163 3575 50  0001 C CNN
F 3 "~" H 3125 3725 50  0001 C CNN
	1    3125 3725
	1    0    0    -1  
$EndComp
Wire Wire Line
	3125 3575 2925 3575
Connection ~ 2925 3575
Wire Wire Line
	2925 3575 2925 3550
Wire Wire Line
	3125 3875 2925 3875
Connection ~ 2925 3875
Wire Wire Line
	2925 3875 2925 3900
Connection ~ 3125 3875
Wire Wire Line
	3125 3575 3550 3575
Connection ~ 3125 3575
Wire Wire Line
	2550 1025 2450 1025
Wire Wire Line
	2550 925  2450 925 
$Comp
L Diode:1N4148 D1
U 1 1 615ED72A
P 5000 1700
F 0 "D1" V 5046 1620 50  0000 R CNN
F 1 "1N4148" H 5050 1800 50  0000 R CNN
F 2 "Diode_SMD:D_0805_2012Metric" H 5000 1525 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 5000 1700 50  0001 C CNN
	1    5000 1700
	0    -1   -1   0   
$EndComp
$Comp
L Diode:1N4148 D2
U 1 1 615F2F0E
P 5000 2075
F 0 "D2" V 5046 1995 50  0000 R CNN
F 1 "1N4148" V 4955 1995 50  0000 R CNN
F 2 "Diode_SMD:D_0805_2012Metric" H 5000 1900 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 5000 2075 50  0001 C CNN
	1    5000 2075
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5000 1850 5000 1875
$Comp
L Device:R R6
U 1 1 615F443B
P 5300 1875
F 0 "R6" V 5225 1875 50  0000 C CNN
F 1 "100R" V 5300 1875 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5230 1875 50  0001 C CNN
F 3 "~" H 5300 1875 50  0001 C CNN
	1    5300 1875
	0    1    1    0   
$EndComp
Wire Wire Line
	5150 1875 5000 1875
Connection ~ 5000 1875
Wire Wire Line
	5000 1875 5000 1925
$Comp
L Device:C C7
U 1 1 615FA6DF
P 4775 2075
F 0 "C7" H 4650 2150 50  0000 L CNN
F 1 "0.22u" H 4550 2000 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4813 1925 50  0001 C CNN
F 3 "~" H 4775 2075 50  0001 C CNN
	1    4775 2075
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 2225 4875 2225
Wire Wire Line
	5000 1550 4775 1550
Wire Wire Line
	4775 1550 4775 1925
$Comp
L Device:C C8
U 1 1 615FCDFF
P 5675 1875
F 0 "C8" V 5800 1875 50  0000 C CNN
F 1 "10n" V 5514 1875 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5713 1725 50  0001 C CNN
F 3 "~" H 5675 1875 50  0001 C CNN
	1    5675 1875
	0    1    1    0   
$EndComp
Wire Wire Line
	5450 1875 5525 1875
Wire Wire Line
	5825 1875 6150 1875
$Comp
L power:VSS #PWR0108
U 1 1 61611806
P 4775 1500
F 0 "#PWR0108" H 4775 1350 50  0001 C CNN
F 1 "VSS" H 4790 1673 50  0000 C CNN
F 2 "" H 4775 1500 50  0001 C CNN
F 3 "" H 4775 1500 50  0001 C CNN
	1    4775 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4775 1550 4775 1500
Connection ~ 4775 1550
$Comp
L Device:R R5
U 1 1 61613E1F
P 5275 2925
F 0 "R5" H 5325 3175 50  0000 R CNN
F 1 "1R" H 5325 3250 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5205 2925 50  0001 C CNN
F 3 "~" H 5275 2925 50  0001 C CNN
	1    5275 2925
	-1   0    0    1   
$EndComp
Connection ~ 6150 3075
Text GLabel 5975 2675 0    50   Input ~ 0
PHASE1
Wire Wire Line
	6150 2675 5975 2675
Text GLabel 6100 1675 0    50   Input ~ 0
PHASE2
Wire Wire Line
	6150 1675 6100 1675
Text GLabel 7275 1675 2    50   Input ~ 0
PHASE3
Wire Wire Line
	7275 1675 7150 1675
Wire Wire Line
	6625 2175 6625 2275
Wire Wire Line
	6625 2275 6150 2275
$Comp
L Device:R R1
U 1 1 61633D6A
P 2925 825
F 0 "R1" V 3025 825 50  0000 C CNN
F 1 "100K" V 2925 825 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 2855 825 50  0001 C CNN
F 3 "~" H 2925 825 50  0001 C CNN
	1    2925 825 
	0    1    1    0   
$EndComp
Wire Wire Line
	2450 825  2775 825 
Wire Wire Line
	3075 825  3125 825 
$Comp
L Device:C C1
U 1 1 61636CEA
P 3125 1050
F 0 "C1" H 3240 1096 50  0000 L CNN
F 1 "5.6n" H 3240 1005 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3163 900 50  0001 C CNN
F 3 "~" H 3125 1050 50  0001 C CNN
	1    3125 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3125 900  3125 825 
Connection ~ 3125 825 
Wire Wire Line
	3125 825  3225 825 
$Comp
L power:GND #PWR0109
U 1 1 6163881B
P 3125 1200
F 0 "#PWR0109" H 3125 950 50  0001 C CNN
F 1 "GND" H 3130 1027 50  0000 C CNN
F 2 "" H 3125 1200 50  0001 C CNN
F 3 "" H 3125 1200 50  0001 C CNN
	1    3125 1200
	1    0    0    -1  
$EndComp
Text GLabel 7275 2175 2    50   Input ~ 0
ENABLE
Text GLabel 6050 2175 0    50   Input ~ 0
HALL1
Text GLabel 6050 2075 0    50   Input ~ 0
HALL3
Text GLabel 6050 1975 0    50   Input ~ 0
HALL2
Wire Wire Line
	6150 1975 6050 1975
Wire Wire Line
	6150 2075 6050 2075
Wire Wire Line
	6150 2175 6050 2175
Text GLabel 7275 2275 2    50   Input ~ 0
F-R
Wire Wire Line
	7275 2275 7150 2275
Text GLabel 7275 1975 2    50   Input ~ 0
BRAKE
Wire Wire Line
	7275 1975 7150 1975
Wire Wire Line
	7150 1875 7750 1875
Wire Wire Line
	7750 1875 7750 3525
Wire Wire Line
	7750 3525 4875 3525
Wire Wire Line
	4875 3525 4875 2225
Connection ~ 4875 2225
Wire Wire Line
	4875 2225 4775 2225
$Comp
L Device:R R8
U 1 1 6164D0DC
P 7375 2675
F 0 "R8" V 7475 2675 50  0000 C CNN
F 1 "1K" V 7375 2675 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7305 2675 50  0001 C CNN
F 3 "~" H 7375 2675 50  0001 C CNN
	1    7375 2675
	0    1    1    0   
$EndComp
Wire Wire Line
	7225 2675 7150 2675
$Comp
L power:+5V #PWR0110
U 1 1 6164F7E1
P 7525 2625
F 0 "#PWR0110" H 7525 2475 50  0001 C CNN
F 1 "+5V" H 7540 2798 50  0000 C CNN
F 2 "" H 7525 2625 50  0001 C CNN
F 3 "" H 7525 2625 50  0001 C CNN
	1    7525 2625
	1    0    0    -1  
$EndComp
Wire Wire Line
	7525 2625 7525 2675
$Comp
L Device:R R9
U 1 1 61662839
P 8025 2625
F 0 "R9" H 7875 2675 50  0000 L CNN
F 1 "47K" H 7825 2575 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 7955 2625 50  0001 C CNN
F 3 "~" H 8025 2625 50  0001 C CNN
	1    8025 2625
	1    0    0    -1  
$EndComp
$Comp
L Device:C C10
U 1 1 6166283F
P 8275 2625
F 0 "C10" H 8390 2671 50  0000 L CNN
F 1 "10n" H 8390 2580 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 8313 2475 50  0001 C CNN
F 3 "~" H 8275 2625 50  0001 C CNN
	1    8275 2625
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 61664F92
P 4250 2625
F 0 "R4" H 4100 2700 50  0000 L CNN
F 1 "33K" H 4050 2600 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4180 2625 50  0001 C CNN
F 3 "~" H 4250 2625 50  0001 C CNN
	1    4250 2625
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 61664F98
P 4500 2625
F 0 "C6" H 4615 2671 50  0000 L CNN
F 1 "1n" H 4615 2580 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4538 2475 50  0001 C CNN
F 3 "~" H 4500 2625 50  0001 C CNN
	1    4500 2625
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 2475 8025 2475
Wire Wire Line
	8275 2475 8025 2475
Connection ~ 8025 2475
Wire Wire Line
	8275 2775 8150 2775
$Comp
L power:GND #PWR0111
U 1 1 6166CEAF
P 8150 2825
F 0 "#PWR0111" H 8150 2575 50  0001 C CNN
F 1 "GND" H 8155 2652 50  0000 C CNN
F 2 "" H 8150 2825 50  0001 C CNN
F 3 "" H 8150 2825 50  0001 C CNN
	1    8150 2825
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 2825 8150 2775
Connection ~ 8150 2775
Wire Wire Line
	8150 2775 8025 2775
Wire Wire Line
	5275 3075 5375 3075
Wire Wire Line
	5275 2375 5275 2775
Wire Wire Line
	6150 2475 4500 2475
Wire Wire Line
	4500 2475 4250 2475
Connection ~ 4500 2475
Wire Wire Line
	4500 2775 4375 2775
$Comp
L power:GND #PWR0112
U 1 1 61687439
P 4375 2825
F 0 "#PWR0112" H 4375 2575 50  0001 C CNN
F 1 "GND" H 4380 2652 50  0000 C CNN
F 2 "" H 4375 2825 50  0001 C CNN
F 3 "" H 4375 2825 50  0001 C CNN
	1    4375 2825
	1    0    0    -1  
$EndComp
Wire Wire Line
	4375 2825 4375 2775
Connection ~ 4375 2775
Wire Wire Line
	4375 2775 4250 2775
$Comp
L Device:R R2
U 1 1 616BEFCD
P 3800 725
F 0 "R2" V 3725 725 50  0000 C CNN
F 1 "56K" V 3800 725 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3730 725 50  0001 C CNN
F 3 "~" H 3800 725 50  0001 C CNN
	1    3800 725 
	0    1    1    0   
$EndComp
$Comp
L Device:R R3
U 1 1 616BF67A
P 4000 1000
F 0 "R3" H 4150 950 50  0000 R CNN
F 1 "15K" H 4200 1050 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3930 1000 50  0001 C CNN
F 3 "~" H 4000 1000 50  0001 C CNN
	1    4000 1000
	-1   0    0    1   
$EndComp
$Comp
L Device:C C5
U 1 1 616BFB8B
P 4200 1000
F 0 "C5" H 4315 1046 50  0000 L CNN
F 1 "0.1u" H 4315 955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4238 850 50  0001 C CNN
F 3 "~" H 4200 1000 50  0001 C CNN
	1    4200 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 725  3650 725 
Wire Wire Line
	3950 725  4000 725 
Wire Wire Line
	4000 850  4000 725 
Connection ~ 4000 725 
Wire Wire Line
	4000 725  4200 725 
Wire Wire Line
	4200 850  4200 725 
Connection ~ 4200 725 
Wire Wire Line
	4200 725  4325 725 
Wire Wire Line
	4000 1150 4100 1150
$Comp
L power:GND #PWR0113
U 1 1 616D5E52
P 4100 1225
F 0 "#PWR0113" H 4100 975 50  0001 C CNN
F 1 "GND" H 4105 1052 50  0000 C CNN
F 2 "" H 4100 1225 50  0001 C CNN
F 3 "" H 4100 1225 50  0001 C CNN
	1    4100 1225
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 1225 4100 1150
Connection ~ 4100 1150
Wire Wire Line
	4100 1150 4200 1150
Text GLabel 7275 2075 2    50   Input ~ 0
VREF
Wire Wire Line
	7275 2075 7150 2075
$Comp
L power:GND #PWR0114
U 1 1 616E2A61
P 7325 1175
F 0 "#PWR0114" H 7325 925 50  0001 C CNN
F 1 "GND" H 7330 1002 50  0000 C CNN
F 2 "" H 7325 1175 50  0001 C CNN
F 3 "" H 7325 1175 50  0001 C CNN
	1    7325 1175
	1    0    0    -1  
$EndComp
Wire Wire Line
	7325 1175 7150 1175
Connection ~ 7150 1175
$Comp
L Device:R R10
U 1 1 61701AD2
P 2725 1725
F 0 "R10" V 2850 1675 50  0000 L CNN
F 1 "10K" V 2725 1650 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 2655 1725 50  0001 C CNN
F 3 "~" H 2725 1725 50  0001 C CNN
	1    2725 1725
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2875 1825 2875 1725
Wire Wire Line
	2450 1825 2875 1825
Wire Wire Line
	2575 1725 2525 1725
Connection ~ 2525 1725
$Comp
L Device:R R11
U 1 1 617501EE
P 3075 1725
F 0 "R11" V 3200 1675 50  0000 L CNN
F 1 "10K" V 3075 1650 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3005 1725 50  0001 C CNN
F 3 "~" H 3075 1725 50  0001 C CNN
	1    3075 1725
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R12
U 1 1 617506DC
P 3450 1725
F 0 "R12" V 3575 1700 50  0000 L CNN
F 1 "10K" V 3450 1650 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3380 1725 50  0001 C CNN
F 3 "~" H 3450 1725 50  0001 C CNN
	1    3450 1725
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2575 1725 2575 1650
Wire Wire Line
	2575 1650 2925 1650
Wire Wire Line
	2925 1650 2925 1725
Connection ~ 2575 1725
Wire Wire Line
	2925 1650 3300 1650
Wire Wire Line
	3300 1650 3300 1725
Connection ~ 2925 1650
Wire Wire Line
	3225 1925 3225 1725
Wire Wire Line
	2450 1925 3225 1925
Wire Wire Line
	3600 2025 3600 1725
Wire Wire Line
	2450 2025 3600 2025
Wire Wire Line
	2925 1825 2875 1825
Connection ~ 2875 1825
Wire Wire Line
	3225 1925 3275 1925
Connection ~ 3225 1925
Wire Wire Line
	3650 2025 3600 2025
Connection ~ 3600 2025
Text GLabel 2550 1125 2    50   Input ~ 0
TACHO
Wire Wire Line
	2550 1125 2450 1125
Text GLabel 7275 2925 2    50   Input ~ 0
TACHO
Wire Wire Line
	7275 2925 7225 2925
Wire Wire Line
	7225 2925 7225 2675
Connection ~ 7225 2675
Wire Wire Line
	5300 1575 5300 1550
Wire Wire Line
	5300 1550 5000 1550
Connection ~ 5000 1550
$Comp
L Device:CP C3
U 1 1 615C8FC6
P 3550 3725
F 0 "C3" H 3668 3771 50  0000 L CNN
F 1 "100u" H 3668 3680 50  0000 L CNN
F 2 "Capacitor_THT:C_Radial_D8.0mm_H7.0mm_P3.50mm" H 3588 3575 50  0001 C CNN
F 3 "~" H 3550 3725 50  0001 C CNN
	1    3550 3725
	1    0    0    -1  
$EndComp
Wire Wire Line
	3125 3875 3550 3875
$Comp
L Device:R R7
U 1 1 615C6A29
P 5150 2925
F 0 "R7" H 5300 2900 50  0000 R CNN
F 1 "1R" H 5300 2975 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5080 2925 50  0001 C CNN
F 3 "~" H 5150 2925 50  0001 C CNN
	1    5150 2925
	-1   0    0    1   
$EndComp
$Comp
L Device:R R13
U 1 1 615C6F4F
P 5375 2925
F 0 "R13" H 5305 2879 50  0000 R CNN
F 1 "1R" H 5305 2970 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 5305 2925 50  0001 C CNN
F 3 "~" H 5375 2925 50  0001 C CNN
	1    5375 2925
	-1   0    0    1   
$EndComp
Connection ~ 5375 3075
Wire Wire Line
	5375 3075 6150 3075
Wire Wire Line
	5275 3075 5150 3075
Connection ~ 5275 3075
Wire Wire Line
	5150 2775 5275 2775
Connection ~ 5275 2775
Wire Wire Line
	5375 2775 5275 2775
$Comp
L reprapltd-kicad:L6235PD U1
U 1 1 616A35F1
P 6650 2125
F 0 "U1" H 6650 3200 50  0000 C CNN
F 1 "L6235PD" H 6650 3109 50  0000 C CNN
F 2 "reprapltd-kicad:SOIC-36_11mmx16mmx3.6mm" H 6650 2125 50  0001 C CNN
F 3 "" H 6650 2125 50  0001 C CNN
	1    6650 2125
	1    0    0    -1  
$EndComp
Wire Wire Line
	5275 2375 6150 2375
Wire Wire Line
	6625 2175 7150 2175
Wire Wire Line
	5300 1575 6150 1575
Connection ~ 7150 2175
Wire Wire Line
	7150 2175 7275 2175
Wire Wire Line
	6650 3125 6800 3125
Wire Wire Line
	6800 3125 6800 3075
Connection ~ 6800 3075
Wire Wire Line
	6800 3075 7150 3075
$Comp
L power:+5V #PWR0104
U 1 1 616EFB17
P 6200 4075
F 0 "#PWR0104" H 6200 3925 50  0001 C CNN
F 1 "+5V" H 6215 4248 50  0000 C CNN
F 2 "" H 6200 4075 50  0001 C CNN
F 3 "" H 6200 4075 50  0001 C CNN
	1    6200 4075
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 616F017A
P 6325 4225
F 0 "C4" H 6440 4271 50  0000 L CNN
F 1 "0.1u" H 6440 4180 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6363 4075 50  0001 C CNN
F 3 "~" H 6325 4225 50  0001 C CNN
	1    6325 4225
	1    0    0    -1  
$EndComp
$Comp
L power:VSS #PWR0107
U 1 1 616F094C
P 5025 4075
F 0 "#PWR0107" H 5025 3925 50  0001 C CNN
F 1 "VSS" H 5040 4248 50  0000 C CNN
F 2 "" H 5025 4075 50  0001 C CNN
F 3 "" H 5025 4075 50  0001 C CNN
	1    5025 4075
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C9
U 1 1 616F1027
P 6775 4225
F 0 "C9" H 6893 4271 50  0000 L CNN
F 1 "100u" H 6893 4180 50  0000 L CNN
F 2 "Capacitor_THT:C_Radial_D8.0mm_H7.0mm_P3.50mm" H 6813 4075 50  0001 C CNN
F 3 "~" H 6775 4225 50  0001 C CNN
	1    6775 4225
	1    0    0    -1  
$EndComp
Wire Wire Line
	2475 3800 2925 3800
$Comp
L power:GND #PWR0115
U 1 1 616F6BB6
P 5625 4425
F 0 "#PWR0115" H 5625 4175 50  0001 C CNN
F 1 "GND" H 5630 4252 50  0000 C CNN
F 2 "" H 5625 4425 50  0001 C CNN
F 3 "" H 5625 4425 50  0001 C CNN
	1    5625 4425
	1    0    0    -1  
$EndComp
Wire Wire Line
	5625 4375 5625 4425
Wire Wire Line
	6200 4075 6325 4075
Connection ~ 6200 4075
Wire Wire Line
	6775 4075 6325 4075
Connection ~ 6325 4075
Wire Wire Line
	6775 4375 6325 4375
Wire Wire Line
	6325 4375 5625 4375
Connection ~ 6325 4375
$Comp
L Mechanical:MountingHole H4
U 1 1 616F56E4
P 1150 1200
F 0 "H4" H 1250 1246 50  0000 L CNN
F 1 "MountingHole" H 1250 1155 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 1150 1200 50  0001 C CNN
F 3 "~" H 1150 1200 50  0001 C CNN
	1    1150 1200
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H1
U 1 1 617216E4
P 1525 875
F 0 "H1" H 1625 921 50  0000 L CNN
F 1 "MountingHole" H 1625 830 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 1525 875 50  0001 C CNN
F 3 "~" H 1525 875 50  0001 C CNN
	1    1525 875 
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 61721E3F
P 1150 875
F 0 "H2" H 1250 921 50  0000 L CNN
F 1 "MountingHole" H 1250 830 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 1150 875 50  0001 C CNN
F 3 "~" H 1150 875 50  0001 C CNN
	1    1150 875 
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 6172253A
P 1525 1200
F 0 "H3" H 1625 1246 50  0000 L CNN
F 1 "MountingHole" H 1625 1155 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 1525 1200 50  0001 C CNN
F 3 "~" H 1525 1200 50  0001 C CNN
	1    1525 1200
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:L7805 U2
U 1 1 61E6127E
P 5625 4075
F 0 "U2" H 5625 4317 50  0000 C CNN
F 1 "L7805" H 5625 4226 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:TO-252-2" H 5650 3925 50  0001 L CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 5625 4025 50  0001 C CNN
	1    5625 4075
	1    0    0    -1  
$EndComp
Connection ~ 5625 4375
Wire Wire Line
	5925 4075 6200 4075
Wire Wire Line
	5025 4075 5325 4075
$Comp
L Connector:Conn_01x06_Male J1
U 1 1 61E8B4F3
P 2250 925
F 0 "J1" H 2358 1306 50  0000 C CNN
F 1 "Conn_01x06_Male" H 2358 1215 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 2250 925 50  0001 C CNN
F 3 "~" H 2250 925 50  0001 C CNN
	1    2250 925 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0116
U 1 1 61E9687C
P 2450 1225
F 0 "#PWR0116" H 2450 975 50  0001 C CNN
F 1 "GND" H 2455 1052 50  0000 C CNN
F 2 "" H 2450 1225 50  0001 C CNN
F 3 "" H 2450 1225 50  0001 C CNN
	1    2450 1225
	1    0    0    -1  
$EndComp
$EndSCHEMATC
