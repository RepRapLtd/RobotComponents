; pcb2gcode 2.0.0 
; Software-independent Gcode 

; This file uses only one drill bit. Forced by 'onedrill' option 

G94       ;Millimeters per minute feed rate.
G21       ;Units == Millimeters.
G90       ;Absolute coordinates.
;G1 F3000 S10000     ;RPM spindle speed.

G1 F3000 Z3.00000 ;Retract
;T1
;M5      ;Spindle stop.
;G04 P1.00000
;MSG, Change tool bit to drill size 1.00076 mm
;M6      ;Tool change.
;M0      ;Temporary machine stop.
;M3      ;Spindle on clockwise.
G1 F3000 Z3.00000
;G04 P1.00000

;F1000.00000
G1 F3000 X4.34616 Y3.70608
G1 F300 Z-2.50000
G1 F300 Z3.00000
G1 F3000 X2.68500 Y11.57500
G1 F300 Z-2.50000
G1 F300 Z3.00000
G1 F3000 X2.68500 Y14.11500
G1 F300 Z-2.50000
G1 F300 Z3.00000
G1 F3000 X2.68500 Y16.65500
G1 F300 Z-2.50000
G1 F300 Z3.00000
G1 F3000 X6.49500 Y17.29000
G1 F300 Z-2.50000
G1 F300 Z3.00000
G1 F3000 X2.68500 Y19.19500
G1 F300 Z-2.50000
G1 F300 Z3.00000
G1 F3000 X4.59000 Y24.27500
G1 F300 Z-2.50000
G1 F300 Z3.00000
G1 F3000 X14.75000 Y24.27500
G1 F300 Z-2.50000
G1 F300 Z3.00000
G1 F3000 X19.34486 Y24.70426
G1 F300 Z-2.50000
G1 F300 Z3.00000
G1 F3000 X19.83000 Y19.19500
G1 F300 Z-2.50000
G1 F300 Z3.00000
G1 F3000 X19.83000 Y16.65500
G1 F300 Z-2.50000
G1 F300 Z3.00000
G1 F3000 X19.83000 Y14.11500
G1 F300 Z-2.50000
G1 F300 Z3.00000
G1 F3000 X15.38500 Y14.11500
G1 F300 Z-2.50000
G1 F300 Z3.00000
G1 F3000 X19.83000 Y6.49500
G1 F300 Z-2.50000
G1 F300 Z3.00000
G1 F3000 X19.83000 Y3.95500
G1 F300 Z-2.50000
G1 F300 Z3.00000

G1 F3000 Z3.000 ; All done -- retract 

;M5      ;Spindle off.
;G04 P1.000000
;M9      ;Coolant off.
M0      ;Program end.
