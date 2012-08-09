//Cassini.pov

#include "Cassini.inc"
#declare StarRatio=1920;
#include "Stars.inc"

object {
  Stars
}

object {
  Cassini
  translate y*1.5
  rotate -y*95
  rotate x*85
  rotate y*40
}


light_source {
  <0.1,-0.1,1>*1000
  color 1.5
}

camera {
  up y
  right x*16/10
  location <-20,20,-60>
  look_at <-20,20,0>
//  angle 10
}


