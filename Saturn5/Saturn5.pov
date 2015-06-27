#include "shapes.inc"
#include "colors.inc"
#include "metals.inc"
#declare SmallPipes=0;
#include "Saturn5.inc"

//background {color rgb<0.5,0.5,1>}

object {
  Saturn5
  //rotate -y*45
  //rotate -z*53
  //translate -x*130
}

camera {
  location <0,55,-20>
  look_at <0,55,0>
}

light_source {
  <2000,0,-2000> *10000
  color rgb 0.75
}

light_source {
  <2000,-2000,-2000> *10000
  color rgb 0.75
}
