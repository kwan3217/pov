#include "AimAttCommon.inc"
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

#macro LH(V)
  (<V.x,-V.z,-V.y>)
#end

union {
  union {
    Vector(LH(x*2))
    pigment {color rgb <1,0,0>}
  }
  union {
    Vector(LH(y*2))
    pigment {color rgb <0,1,0>}
  }
  union {
    Vector(LH(z*2))
    pigment {color rgb <0,0,1>}
  }
  rotate z*180
  AimAtt2()
}

union {
  union {
    Vector(LH(x*2))
    pigment {color rgb <0,1,1>}
  }
  union {
    Vector(LH(y*2))
    pigment {color rgb <1,0,1>}
  }
  union {
    Vector(-LH(z*2))
    pigment {color rgb <1,1,0>}
  }
  scale 0.001
  LocationLookAt(Pos(clockSec),Vel(clockSec),Pos(clockSec))
}

#declare SunVec=<cos(BetaR),-sin(BetaR),0>;
#declare SofieVec=<cos(aR),0,sin(aR)>;

union {
  Vector(LH(SunVec)*2)
  scale 0.001
  #declare SofiePointRot=AimAttV2(SofiePoint0);
  translate SofiePointRot
  pigment {color rgb <1,0.5,0>}
}

union {
  Vector(LH(SofieVec)*2)
  rotate z*180
  translate SofiePoint0
  AimAtt2()
  pigment {color rgb <1,1,1>}
}

object {
  Aim
  AimAtt2()
}

camera {
//  orthographic
  location Pos(clockSec)+<0,0,-5>*0.001
  look_at Pos(clockSec)
}

light_source {
  x*1e8
  color rgb 1
}




