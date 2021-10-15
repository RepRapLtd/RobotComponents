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
# Note - it makes exact geometry*; it doesn't offset shapes to allow clearances, so you probably want to
# do things like saying the pins and rollers are 0.1mm bigger than they actually are - experiment.
#
# *Well, exact: the cycloidal disc it creates is a many-faceted approximation to the true algebra.
# The faceting can be made as fine as you like though.
# 

import math as maths
import Part
from FreeCAD import Base

#*****************************************************************************************************************************

# Put numbers in here.
# See https://www.tec-science.com/mechanical-power-transmission/planetary-gear/construction-of-the-cycloidal-disc/
# All dimensions are in mm.

D = 50  # Pin circle centres diameter
dp = 5.3  # Pin diameter
n = 8    # Number of lobes
N = 9  # Number of pins
dr = 5.3  # inner roller pin diameter
dd = 34 # inner roller pin centres diameter
rollerHoles = 4 # Number of roller holes (must equal n or divide into n exactly)
eFactor = 0.3 # Sets the eccentricity. Must be less than 0.5. If it's too big the faceting will be inaccurate, so increase circle below.
dc = 24.1 # Diameter of central hole
bearingLength = 3 # How thick to make the contracted cycloidal disc
lip = 0.25 # Create a lip to constrain axial drift. Set to -1 to supress.
circle = 800 # Sets the faceting to correspond to 1 degree; a 360-faced polygon. Bigger for finer faceting (use even numbers).

#***************************************************************************************************************************

# Work out some parameters and tell the user

i = n/(N-n)
print("Transmission ratio: " + str(i))
delta = D/N
print("Rolling circle diameter: " + str(delta))
d = i*D/N
print("Base circle diamater: " + str(d))
e = delta*eFactor
print("Eccentricity: " + str(e))
dh = dr + 2*e
print("Hole diameter: " + str(dh) + ". There are " + str(rollerHoles) + " on pitch diameter " + str(dd) + ".")

# This is nasty...
def NullSet():
 a = Part.makeBox(1, 1, 1)
 a.translate(Base.Vector(10, 10, 10))
 return a.common(Part.makeBox(1, 1, 1))

# Compute a normal vector length r using a chord across a curve (i.e. 2nd degree approximation).
def NormalVector(xOld, xNew, yOld, yNew, r):
 dy = xNew - xOld
 dx = yOld - yNew
 s = r/maths.sqrt(dx*dx + dy*dy)
 return (dx*s, dy*s)

# This builds the blank contracted cycloid.
# Note we use the first three of times round the loop
# to get the numbers for the curve-normal calculation,
# so we have to go +3 at the end to join up.
def ContractedCycloidBlank():
 offsetCycloid = []
 if lip > 0:
  lipWire = []
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
   if lip > 0:
    dxy = NormalVector(xOld, xNew, yOld, yNew, dp/2 - lip)
    lipWire.append(App.Vector(x + dxy[0], y + dxy[1], 0))
  xOld = x
  yOld = y
  x = xNew
  y = yNew
 offsetCycloidWire=Part.makePolygon(offsetCycloid)
 face=Part.Face(offsetCycloidWire)
 result = face.extrude(Base.Vector(0, 0, bearingLength))
 if lip > 0:
  lipWire=Part.makePolygon(lipWire)
  lipWire.translate(Base.Vector(0, 0, -lip))
  lipFace1 = Part.Face(lipWire)
  lipExtrude1 = lipFace1.extrude(Base.Vector(0, 0, -lip))
  lipExtrude2 = lipExtrude1.copy().translate(Base.Vector(0, 0, bearingLength+3*lip))
  loft = [lipWire, offsetCycloidWire]
  loft = Part.makeLoft(loft, True, False)
  lipWire.translate(Base.Vector(0, 0, bearingLength+2*lip))
  offsetCycloidWire.translate(Base.Vector(0, 0, bearingLength))
  loft2 = [lipWire, offsetCycloidWire]
  loft2 = Part.makeLoft(loft2, True, False)
  result = result.fuse(loft).fuse(loft2).fuse(lipExtrude1).fuse(lipExtrude2)
 return result

def RollerHole():
 roller = Part.makeCylinder(dh/2, bearingLength, Base.Vector(0, 0, 0), Base.Vector(0, 0, 1))
 if lip > 0:
  roller = roller.fuse(Part.makeCone(dh/2, dh/2-lip, lip, Base.Vector(0, 0, bearingLength), Base.Vector(0, 0, 1)))
  roller = roller.fuse(Part.makeCone(dh/2, dh/2-lip, lip, Base.Vector(0, 0, 0), Base.Vector(0, 0, -1)))
  roller = roller.fuse(Part.makeCylinder(dh/2-lip, lip, Base.Vector(0, 0, bearingLength+lip), Base.Vector(0, 0, 1)))
  roller = roller.fuse(Part.makeCylinder(dh/2-lip, lip, Base.Vector(0, 0, -lip), Base.Vector(0, 0, -1)))
 return roller

# This builds the contracted cycloid with the central holes it needs.
def ContractedCycloid():
 cc = ContractedCycloidBlank()
 ainc = 360/rollerHoles
 for r in range(rollerHoles):
  roller = RollerHole().translate(Base.Vector(dd/2, 0, 0))
  roller.rotate(Base.Vector(0, 0, 0),Base.Vector(0, 0, 1), r*ainc)
  cc = cc.cut(roller)
 centre = Part.makeCylinder(dc/2, bearingLength+2, Base.Vector(0, 0, -1), Base.Vector(0, 0, 1))
 cc = cc.cut(centre)
 cc.translate(Base.Vector(-e, 0, 0))
 return cc

# This adds the pins, rollers, and central axis to the model if required
def ShowAncilliaryParts():
 axis = Part.makeCylinder(2, bearingLength+2, Base.Vector(0, 0, -1), Base.Vector(0, 0, 1))
 Part.show(axis)
 rollers = NullSet()
 ainc = 360/rollerHoles
 for r in range(rollerHoles):
  roller = Part.makeCylinder(dr/2, bearingLength, Base.Vector(dd/2, 0, 0), Base.Vector(0, 0, 1))
  roller.rotate(Base.Vector(0, 0, 0),Base.Vector(0, 0, 1), r*ainc)
  rollers = rollers.fuse(roller)
 Part.show(rollers)
 pins = NullSet()
 ainc = 360/N
 for r in range(N):
  pin = Part.makeCylinder(dp/2, bearingLength, Base.Vector(D/2, 0, 0), Base.Vector(0, 0, 1))
  pin.rotate(Base.Vector(0, 0, 0),Base.Vector(0, 0, 1), r*ainc)
  pins = pins.fuse(pin)
 Part.show(pins)

# Make the parts and show them
cc = ContractedCycloid()
Part.show(cc)
ShowAncilliaryParts()