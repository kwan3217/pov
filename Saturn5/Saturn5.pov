#include "shapes.inc"
#include "colors.inc"
#include "metals.inc"
#declare SmallPipes=0;
#include "Saturn5.inc"
global_settings{assumed_gamma 2.2}
//background {color rgb<0.5,0.5,1>}

object {
  Saturn5
  //rotate -y*45
  rotate -z*60
  translate -x*50
}

camera {
  up y
  right x*image_width/image_height
  location <0,25,-65>
  look_at <0,25,0>
}

light_source {
  <2000,0,-2000> *10000
  color rgb 0.75
}

light_source {
  <2000,-2000,-2000> *10000
  color rgb 0.75
}
