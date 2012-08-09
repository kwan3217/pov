#macro Linterp(X1,Y1,X2,Y2,X)
  (Y1+(Y2-Y1)*(X-X1)/(X2-X1))
#end

#declare Deploy=0;
#declare FairingDeploy=0;
#include "Aim.inc"
#declare PegasusClock=91;
#include "Pegasus.inc"

#declare Pegasus=union {
difference {
  object {Pegasus1}
  box {<9.5,-2,-2>,<14,0,0> pigment {color rgb <1,1,1>}}
}
/*
object {
  Pegasus1Inter
}
*/
difference {
  object {
    Pegasus2
  }
  box {<12.5,-2,-2>,<14,0,0> pigment {color rgb <1,1,1>}}
}
object {
  Pegasus3
}

object {
  Avionics
}
object {
  PegasusFairingLeft
}
/*
object {
  PegasusFairingRight
}
*/
#ifdef(Aim) 
  object {
    Aim 
    rotate z*90 
    translate 14.975*x
  } 
#end
}

object {
  Pegasus 
}

plane {
  y,-2
  pigment {checker color rgb <0.5,0.5,0.5>,color rgb<0,0,0>}
  no_shadow
}

plane {
  y,-1.999
  pigment {checker color rgbf <1,1,1,1>,color rgb <1,1,1> scale 0.1}
  no_shadow
}

camera {
  orthographic
  up y*8
  right x*18
  direction z*10
  location <9,100,0>
  look_at <9,0,0>
}

light_source {
  <9,0,-100>*1000
  color rgb 1
}

light_source {
  <-200,100,100>*1000
  color rgb 1
}
/*
background {
  color rgb <0,0.5,1>
}
*/
