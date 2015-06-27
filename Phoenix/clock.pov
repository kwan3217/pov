#version unofficial Megapov 1.22;
global_settings {
  right_handed
}
#include "KwanMath.inc"
#include "clock.inc"

#declare T0=23*3600+30*60+57.920;

Clock(T0+frame_number/30)

camera {
  right y*1
  direction z*1000
  location <0,-2000,0>
  look_at <0,0,0>
}

light_source {
  <0,-1,0>*1000
  color rgb 1
}
