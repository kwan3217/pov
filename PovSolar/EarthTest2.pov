//Earthtest.pov

#declare Ea=0;
#declare AEarth=6378.136;
#declare BEarth=6356.752;
#declare ObjDetail=array[1] {99}

#include "EarthMod.inc"

object {EarthModel rotate -y*36*clock}

light_source {
  <20000*cos(radians(360*clock)),0,-20000*sin(radians(360*clock))>*AEarth
  color rgb 1.5
}

camera {
  location <0,0,-5>*AEarth
  look_at <0,0,0> 
  angle 32
}