; pcb2gcode 2.0.0 
; Software-independent Gcode 

G94 ; Millimeters per minute feed rate. 
G21 ; Units == Millimeters. 

G90 ; Absolute coordinates. 
;G1 F3000 S10000 ; RPM spindle speed. 
G1 F300 F600.00000 ; Feedrate. 


G1 F3000 Z3.00000 ;Retract to tool change height
;T0
;M5      ;Spindle stop.
;G04 P1.00000 ;Wait for spindle to stop
;MSG, Change tool bit to cutter diameter 0.12000mm
;M6      ;Tool change.
;M0      ;Temporary machine stop.
;M3 ; Spindle on clockwise. 
;G04 P1.00000 ;Wait for spindle to get up to speed
;G04 P0 ; dwell for no time -- G64 should not smooth over this point 
G1 F3000 Z3.00000 ; retract 

G1 F3000 X0.08501 Y39.28622 ; rapid move to begin. 
G1 F300 Z-0.07000 F300.00000 ; plunge. 
;G04 P0 ; dwell for no time -- G64 should not smooth over this point 
G1 F300 F600.00000
G1 F300 X0.10253 Y39.32879
G1 F300 X0.14505 Y39.34642
G1 F300 X0.21439 Y39.33372
G1 F300 X57.04092 Y39.38452
G1 F300 X57.07432 Y39.37441
G1 F300 X57.10099 Y39.32442
G1 F300 X57.05019 Y0.14492
G1 F300 X57.04006 Y0.11165
G1 F300 X56.99020 Y0.08501
G1 F300 X0.27200 Y0.08501
G1 F300 X0.23873 Y0.09509
G1 F300 X0.21198 Y0.14482
G1 F300 X0.08501 Y39.28622

;G04 P0 ; dwell for no time -- G64 should not smooth over this point 
G1 F3000 Z3.000 ; retract 

;M5 ; Spindle off. 
;G04 P1.000000
;M9 ; Coolant off. 
M0 ; Program end. 

