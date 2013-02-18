#include "MSLDescentStage.inc"
#include "KwanMath.inc"

#declare Time=frame_number/24;
#declare Throttle=ASDR(2,45,55,98,0,1,Time);
object {
  MLE(Throttle,Time)
  rotate -x*90
}

camera {
  orthographic
  location <0,-2,-5>
  look_at <0,-2,0>
}

background {color rgb <187,136,115>/255}

light_source {
  <20,20,-20>*1000
  color rgb <1,1,1>
}

/*
plane {
  z,0
  pigment {checker}
}
*/

text {
  ttf "lucon.ttf" concat("Throttle: ",str(Throttle,0,3)) 0,0
  scale 0.1
  translate <1,-1,-1>
  no_shadow
  pigment {color rgb <1,1,1>}
  finish {ambient 1 diffuse 0}
}
  
text {
  ttf "lucon.ttf" concat("Throttle: ",str(Time,0,3)) 0,0
  scale 0.1
  translate <1,-0.9,-1>
  no_shadow
  pigment {color rgb <1,1,1>}
  finish {ambient 1 diffuse 0}
}
  
