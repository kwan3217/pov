//View from the EXI instrument
#include "exi_common.inc"

//object {EMM_Spacecraft QuatTrans(SCQ,<0,0,0>)}

camera {
  up y*1
  right -x*image_width/image_height
  angle 25.39
//  sky z
//  location -vnormalize(PlanetPos)*20
//  look_at PlanetPos
  sky QuatTransV(EXIQ,<0,0,0>,y)
  location <0,0,0>
  look_at QuatTransV(EXIQ,<0,0,0>,z)
}


union {
  text {
    ttf "courbd.ttf"
    timout(ET,"YYYY-MM-DDTHR:MN:SC UTC ::UTC") 0 0
    //In this scale, 1 unit is half the screen width
    scale 0.025
    scale <1,1,1>
    //In this, X is from -1 (left edge) to 1 (right edge)
    //         Y is from -h/w (bottom edge) to h/w (top edge)
    translate <-0.99,-0.74,1>
    scale <-tan(radians(25.39/2)),tan(radians(25.39/2)),1>
  }
/*  plane {
    y,1
    pigment {checker scale 0.1}
    finish {ambient 1 diffuse 0}
  }
  plane {
    y,0.99999
    pigment {checker color rgb <1,1,0> color rgbf <1,1,1,1> scale 0.01}
    finish {ambient 1 diffuse 0}
  }*/
  QuatTrans(EXIQ,<0,0,0>)
  pigment {color rgb <1,1,1>}
  finish {ambient 1 diffuse 0}
  no_shadow
}


