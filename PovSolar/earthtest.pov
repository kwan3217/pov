#declare LitSide=1;
#include "planetmod.inc"
#include "vgrlego.inc"

//Scene Starter

//global_settings {ambient_light 0}

light_source {
  <20000000,0,-20000000>
  color rgb<1,1,1>*1.5
}

camera {
  location <0,0,-5>
  look_at<0,0,0>
  angle 45
}

#declare Time=JulianDate(1999,1,1,0,0,0)+clock;
object {
  SaturnModel 
  Rotate(6,Time) 
  translate < 0, 0, 500000 >
}
object {VgrLego  rotate z*90 rotate -y*135}