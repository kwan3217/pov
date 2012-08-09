#declare Re=6378.140;
#declare Hc=820;
#declare CamLoc=<0,0,-5>*Re/2;
#declare Look=<0,0,0>;
#declare Angle=degrees(atan(4/3));
#include "EarthMod.inc"
EarthMod()

global_settings{max_trace_level 20}

light_source {
  x*149000000
  color rgb 1
  rotate y*45
}

camera {
  orthographic
  location CamLoc
  look_at Look
}

