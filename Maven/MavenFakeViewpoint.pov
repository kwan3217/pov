#include "MavenFake.inc"
#version unofficial Megapov 1.22;

#local T=Linterp(0,T0,1,T1,clock);
#local R=spkezr("MAVEN",StartET+T,"MAVEN_MME_2000","NONE","499");
#local Q=pxform("MAVEN_IUVS_SCAN","MAVEN_MME_2000",StartET+T);


union {
  sphere {
    0,3397
    pigment {
      image_map {
        png "../PovSolar/Data/MarsMap.png"
        map_type spherical
      }
      rotate x*90
    }
  }
  cylinder {
    0,x*5000,100
    pigment {color rgb <1,0,0>}
  }
  cylinder {
    0,y*5000,100
    pigment {color rgb <0,1,0>}
  }
  cylinder {   
    0,z*5000,100
    pigment {color rgb <0,0,1>}
  }
  cylinder {
    0,-x*5000,100
    pigment {color rgb <1,1,1>-<1,0,0>}
  }
  cylinder {
    0,-y*5000,100
    pigment {color rgb <1,1,1>-<0,1,0>}
  }
  cylinder {   
    0,-z*5000,100
    pigment {color rgb <1,1,1>-<0,0,1>}
  }
  finish {ambient 0.4}
  QuatTrans(pxform("IAU_MARS","MAVEN_MME_2000",StartET+T),<0,0,0>)
}

union {
  prism {
    100,100.1,12
    < 1.2/2,-19.7/2-1.5>,
    < 1.2/2,-19.7/2>,
    < 0.1/2,-19.7/2>,
    < 0.1/2, 19.7/2>,
    < 0.5/2, 19.7/2>,
    < 0.5/2, 19.7/2+0.8>,
    <-0.5/2, 19.7/2+0.8>,
    <-0.5/2, 19.7/2>,
    <-0.1/2, 19.7/2>,
    <-0.1/2,-19.7/2>,
    <-1.2/2,-19.7/2>,
    <-1.2/2,-19.7/2-1.5>
    pigment {color rgbf <1,0,0,0>}
    finish {ambient 1 diffuse 0 specular 0}
    rotate y*90
  }
  QuatTrans(Q,R)
}

camera {
  up y
  right x*image_width/image_height
  sky QuatTransV(Q,<0,0,0>,z)
  location R
  look_at QuatTransV(Q,R,y)
  angle 45
}

light_source {
  spkezr("SUN",StartET+T,"MAVEN_MME_2000","LT+S","499")
  color rgb <1,1,1>*1.5
  shadowless
}

sphere {
  #local SunR=spkezr("SUN",StartET+T,"MAVEN_MME_2000","LT+S","MAVEN");
  vnormalize(SunR)*1E6+R,695500*1e6/vlength(SunR)
  pigment {color rgb <1,1,0.8>}
  finish {ambient 1}
}

union {
  Stars
  QuatTrans(pxform("J2000","MAVEN_MME_2000",StartET+T),R)
}
