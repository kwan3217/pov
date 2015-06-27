#include "MavenFake.inc"
#version unofficial Megapov 1.22;

#local V=<0,0,0>;
#local R=spkezr("MAVEN",StartET,"MAVEN_MME_2000","NONE","499",V);
#local H=vcross(R,V);
#local N=H/vlength(H);
#local P=R/vlength(R);
#local L=vcross(N,P);

PrintVector("PeriapseR: ",R)
PrintVector("PeriapseV: ",V)

#declare Frames=array[7] {"MAVEN_SPACECRAFT","MAVEN_APP_BP","MAVEN_APP_IG","MAVEN_APP_OG","MAVEN_APP","MAVEN_IUVS_BASE","MAVEN_IUVS_SCAN"}

#local I=0;
#while(I<dimension_size(Frames,1))
  #local Q=pxform(Frames[I],"MAVEN_MME_2000",ET);
  PrintQuatAsMatx(concat(Frames[I],": "),Q)
  #local I=I+1;
#end
PrintVector("N: ",N)
PrintVector("P: ",P)
PrintVector("L: ",L)



#local T=Linterp(0,T0,1,T1,clock);
#local I=T0;
#while(I<(T-20)) 
  #local R1=spkezr("MAVEN",StartET+I,"MAVEN_MME_2000","NONE","499");
  #local R2=spkezr("MAVEN",StartET+I+20,"MAVEN_MME_2000","NONE","499");
  sphere {
    R1,50
    pigment {color rgb <1,1,1>}
  }
  cylinder {
    R1,R2,50
    pigment {color rgb <1,1,1>}
  }
  #local I=I+20;
#end

#local R=spkezr("MAVEN",StartET+T,"MAVEN_MME_2000","NONE","499");
sphere {
  R,100
  pigment {color rgb <0,0,1>}
}

union {
  cylinder {
    -x*200,x*200,50 pigment {color rgb <1,0,0>}
  }
  cylinder {
    0,y*500,50 pigment {color rgb <0,1,0>}
  }
  cylinder {
    0,z*200,50 pigment {color rgb <0,0,1>}
  }
  #local Q=pxform("MAVEN_IUVS_SCAN","MAVEN_MME_2000",StartET+T);
  QuatTrans(Q,R)
}

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
  finish {ambient 0.2}
  QuatTrans(pxform("IAU_MARS","MAVEN_MME_2000",StartET+T),<0,0,0>)
}

camera {
  up y
  right x*image_width/image_height
  sky z
  location N*15*3397
  look_at <0,0,0>
  angle 45
}

light_source {
  spkezr("SUN",StartET+T,"MAVEN_MME_2000","LT+S","499")
  color rgb <1,1,1>
  shadowless
}

union {
  Stars                                
  QuatTrans(pxform("J2000","MAVEN_MME_2000",StartET+T),N*15*3397)
}

