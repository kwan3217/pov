//#version unofficial Megapov 1.22;
//global_settings {right_handed}
#include "SpiceQuat.inc"
#include "Voyager.inc"

object {
  VoyagerQSpice(<0,0,0,1>)
  rotate z*90
  rotate y*180
  translate <-SPCenter.y,SPCenter.x,SPCenter.z>
}               

camera {
  orthographic
  up y*2.5
  right x*16/9*2.5
  location <0,8,0>*10
  look_at <0,0,0>
  sky z
}     

background {color rgb <0,0.5,1>}

light_source {
  <0,5,0>*1000
  color rgb 1
}
