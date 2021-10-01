#
# Cycloidal drive creation program
#
# RepRap Ltd
# https://reprapltd.com
#
# Written by Adrian Bowyer
# 30 September 2021
#
# Licence: GPL
#
# This builds all the basic geometry needed for a cycloidal drive.
#
# Note - it makes exact geometry*; it doesn't not offset shapes to allow clearances, so you probably want to
# do things like saying the pins and rollers are 0.1mm bigger than they actually are - experiment.
#
# *Well, exact: the cycloidal disc it creates as a many faceted approximation to the true algebra.
# The faceting can be made as fine as you like though.
# 

import math as maths
import Part
from FreeCAD import Base

#*******************************************************************************************************

# Put numbers in here
# See https://www.tec-science.com/mechanical-power-transmission/planetary-gear/construction-of-the-cycloidal-disc/

D = 40  # Pin circle centres diameter
dp = 5  # Pin diameter
n = 20    # Number of lobes
N = 21  # Number of pins
dr = 5  # inner roller pin diameter
dd = 24  # inner roller pin centres diameter
rollerHoles = 5 # Number of roller holes (must equal n or divide into n exactly)
e = 2    # eccentricity
dc = 10 # Diameter of central hole
thickness = 5 # How thick to make the contracted cycloidal disc
circle = 360 # Sets the facetting to correspond to 1 degree; a 360 faced polygon. Bigger for finer facetting. (use even numbers)

#*******************************************************************************************************

# Work out some parameters and tell the user

i = n/(N-n)
print("transmission ratio: " + str(i))
delta = D/N
print("rolling circle diameter: " + str(delta))
d = i*D/N
print("base circle diamater: " + str(d))
e = delta*0.25
print("eccentricity: " + str(e))
dh = dr + 2*e
print("hole diameter: " + str(dh) + ". There are " + str(n) + " on pitch diameter " + str(dd))

# This is nasty...
def NullSet():
 a = Part.makeBox(1, 1, 1)
 a.translate(Base.Vector(10, 10, 10))
 return a.common(Part.makeBox(1, 1, 1))

# Compute a normal vector using a chord across a curve
def NormalVector(xOld, xNew, yOld, yNew, r):
 dy = xNew - xOld
 dx = yOld - yNew
 s = r/maths.sqrt(dx*dx + dy*dy)
 return (dx*s, dy*s)

# This builds the blank contracted cycloid
def ContractedCycloidBlank():
 offsetCycloid = []
 x = d/2 + delta/2
 y = 0
 circlePi = circle*0.5
 for theta in range(circle+3):
  xNew = ((d + delta)/2)*maths.cos(theta*maths.pi/circlePi)
  yNew = ((d + delta)/2)*maths.sin(theta*maths.pi/circlePi)
  phi =  d*theta/delta
  xNew += e*maths.cos((theta+phi)*maths.pi/circlePi)
  yNew += e*maths.sin((theta+phi)*maths.pi/circlePi)
  if theta >= 2:
   dxy = NormalVector(xOld, xNew, yOld, yNew, dp/2)
   offsetCycloid.append(App.Vector(x + dxy[0], y + dxy[1], 0))
  xOld = x
  yOld = y
  x = xNew
  y = yNew
 wire=Part.makePolygon(offsetCycloid)
 face=Part.Face(wire)
 return face.extrude(Base.Vector(0, 0, thickness))

# This builds the contracted cycloid with the central holes it needs
def ContractedCycloid():
 cc = ContractedCycloidBlank()
 ainc = 360/rollerHoles
 for r in range(rollerHoles):
  roller = Part.makeCylinder(dh/2, thickness+2, Base.Vector(dd/2, 0, -1), Base.Vector(0, 0, 1))
  roller.rotate(Base.Vector(0, 0, 0),Base.Vector(0, 0, 1), r*ainc)
  cc = cc.cut(roller)
 centre = Part.makeCylinder(dc/2, thickness+2, Base.Vector(0, 0, -1), Base.Vector(0, 0, 1))
 cc = cc.cut(centre)
 cc.translate(Base.Vector(-e, 0, 0))
 return cc

# This adds the pins, rollers, and central axis to the model if required
def ShowAncilliaryParts():
 axis = Part.makeCylinder(2, thickness+2, Base.Vector(0, 0, -1), Base.Vector(0, 0, 1))
 Part.show(axis)
 rollers = NullSet()
 ainc = 360/rollerHoles
 for r in range(rollerHoles):
  roller = Part.makeCylinder(dr/2, thickness+2, Base.Vector(dd/2, 0, -1), Base.Vector(0, 0, 1))
  roller.rotate(Base.Vector(0, 0, 0),Base.Vector(0, 0, 1), r*ainc)
  rollers = rollers.fuse(roller)
 Part.show(rollers)
 pins = NullSet()
 ainc = 360/N
 for r in range(N):
  pin = Part.makeCylinder(dp/2, thickness+2, Base.Vector(D/2, 0, -1), Base.Vector(0, 0, 1))
  pin.rotate(Base.Vector(0, 0, 0),Base.Vector(0, 0, 1), r*ainc)
  pins = pins.fuse(pin)
 Part.show(pins)

# Make the parts and show them
cc = ContractedCycloid()
Part.show(cc)
ShowAncilliaryParts()