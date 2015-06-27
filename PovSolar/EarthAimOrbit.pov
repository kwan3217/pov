//Earthtest.pov

#declare Ea=0;
#declare AEarth=6378.136;
#declare BEarth=6356.752;
#declare ObjDetail=array[1] {99}

#include "EarthMod.inc"
#declare Deploy=1;
#include "Aim.inc"

object {EarthModel rotate -y*36*clock}
object {Aim scale 1000 rotate y*90 rotate -z*90 translate x*(AEarth+1000) rotate y*20rotate z*97.8 }
cone { <0,0,0>,0,<0,0,200>,50 pigment {color rgb <1,1,1>} rotate y*90translate x*(AEarth+1000) rotate y*45rotate z*97.8 }

torus {
  AEarth+600, 25
  rotate z*97.6
  pigment {color rgb <1,1,1>}
}

light_source {
  -z*200000*AEarth
  color rgb 1.5
}

camera {
  location <-3,2,-5>*AEarth
  look_at <0,0,0> 
  angle 32
}
