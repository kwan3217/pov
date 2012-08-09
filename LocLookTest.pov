#include "LocLook.inc"

union {
  cylinder {
    <0,0,0>,<5,0,0>,1
    pigment {color rgb <1,0,0>}
  }
  cylinder {
    <0,0,0>,<-1,-3,0>,1
    pigment {color rgb <0,0,1>}
  }
  scale 0.1
  LocationLookAt(<3,4,5>,<6,7,8>,<0,0,-1>)
}

sphere {
  <6,7,8>,0.1
  pigment {color rgb <0,1,0>}
}

light_source {
  <20,20,-20>*1000
  color 1
}

camera {
  location <0,0,-10>
  look_at <0,0,0>
}
