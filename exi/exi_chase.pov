//View from near the EMM spacecraft
#include "exi_common.inc"

object {EMM_Spacecraft QuatTrans(SCQ,<0,0,0>)}

camera {
  up y*1
  right -x*image_width/image_height
  angle 25.39
  sky z
  location vnormalize(PlanetPos)*20
  look_at -PlanetPos
}

light_source {
  vnormalize(PlanetPos)*20
  color rgb <1,1,1>
}

union {
  text {
    ttf "courbd.ttf"
    etcal(ET) 0 0
    scale 0.005
    rotate x*90
    translate <-0.22,1,-0.16>
  }
//  plane {
//    y,1
//    pigment {checker scale 0.1}
//    finish {ambient 1 diffuse 0}
//  }
//  plane {
//    y,0.99999
//    pigment {checker color rgb <1,1,0> color rgbf <1,1,1,1> scale 0.01}
//    finish {ambient 1 diffuse 0}
//  }
  QuatTrans(EXIQ,<0,0,0>)
  pigment {color rgb <1,1,1>}
  finish {ambient 1 diffuse 0}
  no_shadow
}



