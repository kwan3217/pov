#declare Deploy=1;

#include "LocLook.inc"
#include "Math.inc"
#include "AimAtt4.inc"
#include "AimAttDerived4.inc"

#declare Look=0;
#declare CamLoc=vnormalize(<5,5,-5>)*5;
#declare Angle=degrees(atan2(4/3,1));

#include "Aim.inc"

#local SunPointRH=<cos(BetaR),sin(BetaR),0>;

PrintVector("SunPoint: ",SunPointRH)

box {
  <-2,0,-2>,<2,0,2>
  pigment {checker color rgbt <1,1,1,1> color rgbf <1,1,1,0.5> translate y*0.5 scale 0.2 }
  finish {ambient 1 diffuse 0}
  no_shadow
}

#local A=AimAttInvRHV(clockSec,vnormalize(SunPointRH)*2);
PrintVector("A: ",A)
PrintVector("L: ",LH(A))
PrintVector("M: ",<A.x,0,A.y>)
#if(abs(A.z)>0.00001)
  cylinder {
    <A.x,-0.1*Sgn(A.z),A.y>,LH(A),0.025
    pigment {color rgb <1,0,0>}
    no_shadow
    double_illuminate
  }
#end

object {
  Aim
  scale 0.3
  no_shadow
}
union {
  light_source {
    <0,0,0>
    color rgb 1
  } 
  sphere {0,0.1 pigment {color rgb <1,1,0>} double_illuminate no_shadow}
  translate LH(vnormalize(SunPointRH)*2)
  AimAttInv(clockSec)
}

#declare Sky=y;

camera {
  orthographic
  location CamLoc
  look_at Look
  sky y
}

global_settings {max_trace_level 20}

