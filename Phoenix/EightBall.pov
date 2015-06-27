#version unofficial Megapov 1.22;

#include "host.inc"
#debug concat("\u001b];EightBall.pov - ",Host," Render - frame ",str(frame_number,0,0)," of ",str(final_frame,0,0),"\a")

global_settings {
  right_handed
}

#include "KwanMath.inc"
#include "PhxLoadVec.inc"

#declare GridMajorRad=2.0;
#declare GridMinorRad=0.025;

#declare J=-1;
union {
  #while(J<2)
    torus {
      GridMajorRad*cos(radians(J*45)),GridMinorRad
      rotate x*90
      translate z*GridMajorRad*sin(radians(J*45))
    }
    torus {
      GridMajorRad,GridMinorRad
      rotate z*(J*45+90)
    }
    #declare J=J+1;
  #end
  torus {
    GridMajorRad,GridMinorRad
    pigment {color rgb <1,0,0>}
    clipped_by {plane {x,0}}
  }
  torus {
    GridMajorRad,GridMinorRad
    clipped_by {plane {x,0}}
    rotate z*180
  }
  pigment {color rgb <1,1,1>}
  rotate y*90
  rotate -y*degrees(CurrentLLA.x)
  rotate  z*degrees(CurrentLLA.y)
}

#macro FreeVector(V)
  cylinder {
    <0,0,0>,V*0.75,0.05
  }
  cone {
    V*0.75,0.1,V,0
  }
#end

#declare RRm1=Rm1-R;
#declare RRm1=RRm1/vlength(RRm1);
#declare RRp1=Rp1-R;
#declare RRp1=RRp1/vlength(RRp1);
#if(Im1!=I)
  cone {
    RRm1*GridMajorRad,0.1,RRm1*(GridMajorRad-0.55),0
    pigment {color rgb <1,1,1>}
  }
#end

cone {
  Lz*GridMajorRad,0,Lz*(GridMajorRad-0.55),0.1
  pigment {color rgb <1,1,0>}
}
cone {
  -Ly*GridMajorRad,0,-Ly*(GridMajorRad-0.55),0.1
  pigment {color rgb <1,0,1>}
}
cone {
  Lx*GridMajorRad,0,Lx*(GridMajorRad-0.55),0.1
  pigment {color rgb <0,1,1>}
}
union {
  FreeVector(M1*GridMajorRad)
  pigment {color rgb <1,0,0>}
}

union {
  FreeVector(M2*GridMajorRad)
  pigment {color rgb <0,1,0>}
}

union {
  FreeVector(M3*GridMajorRad)
  pigment {color rgb <0,0,1>}
}

#if(vlength(Ang)>1)
union {
  FreeVector(Ang/vlength(Ang)*GridMajorRad)
  pigment {color rgb <1,0.5,0>}
}
#end

#declare Look=<0,0,0>;
#declare LocLen=sqrt(3.5*3.5*2+2*2);
#declare Loc=Loc/vlength(Loc)*LocLen;

camera {
  orthographic
  right x
  location Loc+Look
  look_at Look
  sky Sky
  angle 45
}

light_source {
  Sun
  <1,1,1>
  shadowless
}

