#version unofficial MegaPov 1.11;
#include "/home/chrisj/host.inc"
#debug concat("\u001b];",Host," Render - frame ",str(frame_number,0,0)," of ",str(final_frame,0,0),"\a")

#include "PlanetConst.inc"
#include "Calendar.inc"

#declare Target=Ti;
#declare Time=JulianDate(2005,1,14,08,00,64.184)+(clock)*6/24;
#declare ChaseDistance=40;
#declare ChaseOffset=-y*10;
#declare ChaseScale=0.1;
#declare UseHuygens=1;

#declare CameraAngle=10;

#include "SaturnChaseCommon.inc"

#declare HuygensLat=radians(-10.7);
#declare HuygensLon=radians(-197);
#declare HuygensVec=lla2xyz(<HuygensLat,HuygensLon,0>,0);
PrintVector("HuygensVec: ",HuygensVec)
#declare HuygensVec=RotateV(HuygensVec,Target);
PrintVector("HuygensVec: ",HuygensVec)

#declare SaturnDirection=vnormalize(PlanetPos[Sa]-PlanetPos[Target]);

sphere {
  0,100
	translate HuygensVec*APlanet[Target]
	translate (PlanetPos[Target]-PlanetPos[Sa])
	scale SystemScale
	pigment {color rgb <1,0,0>}
}
  
cylinder {
  SaturnDirection*APlanet[Target]*2,-SaturnDirection*APlanet[Target]*2,100
  translate (PlanetPos[Target]-PlanetPos[Sa])
	pigment {color rgb <1,1,0>}
	scale SystemScale
}
	
