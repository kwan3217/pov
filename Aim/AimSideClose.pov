#declare Deploy=1;

#include "LocLook.inc"
#include "Math.inc"
#include "AimAtt4South.inc"
#include "AimAttDerived4South.inc"

#declare Look=Pos(clockSec);
#declare CamLoc=Look-z*0.005;
#declare Sky=y;
#declare Angle=degrees(atan2(4/3,1));
//#declare Angle=10;

#include "Aim.inc"

#macro Vector(V)
  union {
    cylinder {
      0,V*0.75,0.05
    }
    cone {
      V*0.75,0.1,V,0
    }
  }
#end

union {
  Vector(LH(SunVecRH*2))
  pigment {color rgb <1,1,0>}
  finish {ambient 0.5}
  scale 1/1000
  translate Pos(clockSec)
}  

union {
  Vector(-vnormalize(Look))
  pigment {color rgb <0,1,0>}
  finish {ambient 0.5}
  scale 1/1000
  translate Pos(clockSec)
}  

union {
  Vector(LH(SofieVec*2))
  pigment {color rgb <1,0,1>}
  finish {ambient 0.5}
  AimAtt2()
}  

object {
  Aim
  AimAtt2()
  no_shadow
}
light_source {
  SunPoint
  color rgb 1
}

camera {
  location CamLoc
  look_at Look
  sky Sky
}

global_settings {max_trace_level 20}

