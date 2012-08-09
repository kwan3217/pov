#include "L1011.inc"
#include "KwanMath.inc"

object {
  L1011
}

/*
camera {
  orthographic
  up y*L1011_Max.y
  right x*(L1011_Max.x-L1011_Min.x)
  direction z*1000
  location <0,L1011_Max.y/2,-1000>
  look_at <0,L1011_Max.y/2,0>
}
*/

camera {
  location <26,3,-20>
  look_at <26,3,0>
  angle 20
}

light_source {
  <20,20,-20>*1000
  color rgb 1
}
