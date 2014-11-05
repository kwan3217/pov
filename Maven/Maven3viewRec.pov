#include "KwanMath.inc"
#include "LocLook.inc"
#include "hud.inc"
#include "textures.inc"

#version unofficial Megapov 1.22;

#furnsh "generic/generic.tm"
#furnsh "mvn/ck/mvn_iuv_all_l0_20141018_v002.bc"
#furnsh "mvn/ck/mvn_iuv_all_l0_20141019_v002.bc"
#furnsh "mvn/ck/mvn_app_rec_141018_141019_v03.bc"
#furnsh "mvn/ck/mvn_sc_rec_141018_141019_v03.bc"
#furnsh "mvn/spk/trj_orb_00094-00098_00413_v1.bsp"
#furnsh "mvn/fk/maven_v04_draft2.tf"
#furnsh "mvn/sclk/MVN_SCLKSCET.00011.tsc"

//#declare StartUTC="2015 NOV 01 00:00:00.000 TDB";
#declare StartUTC="2014 OCT 18 19:37:00 TDB";
#declare StartET=str2et(StartUTC);
PrintNumber("StartET: ",StartET)
#declare StopUTC="2014 OCT 19 17:26:00 TDB";
#declare StopET=str2et(StopUTC);
PrintNumber("StopET:  ",StopET)

//Animation settings
#declare T0=0*3600; //Start of animation relative to StartET
#declare T1=StopET-StartET;//End of animation relative to StartET
#declare T=Linterp(0,T0,1,T1,clock); //Seconds from start of animation
#declare ET=StartET+T; //ET of this frame
PrintNumber("This ET: ",ET)

#include "SpiceQuat.inc"

#local V=<0,0,0>;
#local R=1000*spkezr("MAVEN",ET,"MARSIAU","NONE","499",V);
#local V=1000*V;

light_source {
  vnormalize(spkezr("SUN",ET,"MARSIAU","LT+S","MAVEN"))*1e6
  color rgb <1,1,1>
  shadowless
}

global_settings{max_trace_level 10}

#declare CameraLoc=<0,10,5>;
#declare CameraLook=<0,0,0>;
#declare CameraSky=<0,0,1>;

union {
  textHud("Test the HUD",<0,0>,<1,1,1>,0,-1)           
  scale <0.175,0.175,1>
  no_shadow
  translate z*10
  LocationLookAt(CameraLoc,CameraLook,CameraSky)
}

#include "MavenHifi.inc"

union {
  #local I=0;
  #local R=spkezr("MAVEN",StartET+I,"MARSIAU","NONE","499",V)/1000;
  #while(I<T)
    sphere {
      R,0.05
    }
    cylinder {
      R,
      #local I=min(I+10,T+0.01);    
      #local R=spkezr("MAVEN",StartET+I,"MARSIAU","NONE","499",V)/1000;
      R,0.05
    }
  #end
  sphere {
    R,0.08
    pigment {color rgb <0,0,1>}
  }
  sphere {
    0,1
    #local MarsA=gdpool("BODY499_RADII",0);
    #local MarsB=gdpool("BODY499_RADII",1);
    scale <MarsA,MarsA,MarsB>/1000 
    pigment {color rgb <1,0.7,0.3>}
  } 
  pigment {color rgb <1,1,1>}
  translate x*10
}

union {
  union {
    Vector(0,vnormalize(spkezr("SUN",ET,"MARSIAU","LT+S","MAVEN"))*4,0.1)
    pigment {color rgb <1,1,0>}
  }
  union {
    Vector(0,vnormalize(spkezr("399",ET,"MARSIAU","LT+S","MAVEN"))*4,0.1)
    pigment {color rgb <0,0,1>}  
  }
  union {
    #local V=<0,0,0>;
    Vector(0,vnormalize(-spkezr("MAVEN",ET,"MARSIAU","LT+S","499",V))*4,0.1)
    pigment {color rgb <1,0.7,0.3>}
  }
  union {
    Vector(0,vnormalize(V)*4,0.1)
    pigment {color rgb <1,1,1>}  
  }
  union {
    MavenHiFi(ET)
    union {
      Vector(0,x*5,0.05)
      pigment {color rgb <1,0,0>} 
    }
    union {
      Vector(0,y*5,0.05)
      pigment {color rgb <0,1,0>}
    }
    union {
      Vector(0,z*5,0.05)
      pigment {color rgb <0,0,1>}
    }
    #local Q=pxform("MAVEN_SPACECRAFT","MARSIAU",ET);
    QuatTrans(Q,<0,0,0>)
  }
  translate <-10,0,5>
}

union {
  union {MavenAPP(pxform("MAVEN_IUVS_SCAN","MAVEN_IUVS_BASE",ET)) scale 5}
  #local Q=pxform("MAVEN_IUVS_BASE","MARSIAU",ET);
  QuatTrans(Q,<-10,0,-5>)
}

union {
  union {Vector(0,y*2,0.02) pigment {color rgb 1}}
  scale 5
  #local Q=pxform("MAVEN_IUVS_SCAN","MARSIAU",ET);
  QuatTrans(Q,<-10,0,-5>)
}

union {
  #declare I=0;
  #local R=<Linterp(T0,-20,T1,20,I)*image_width/image_height,0,(vlength(spkezr("MAVEN",StartET+I,"MARSIAU","NONE","499",V))-MarsA)/1000-20>*0.5;
  #while(I<T)
    sphere {
      R,0.05
    }
    cylinder {
      R,
      #local I=min(I+10,T+0.01);    
      #local R=<Linterp(T0,-20,T1,20,I)*image_width/image_height,0,(vlength(spkezr("MAVEN",StartET+I,"MARSIAU","NONE","499",V))-MarsA)/1000-20>*0.5;
      R,0.05
    }
  #end
  PrintVector("R: ",R)
  sphere {
    R,0.08
    pigment {color rgb <0,0,1>}
  }
  cylinder {
    <-20*image_width/image_height,0,-20>*0.5,
    < 20*image_width/image_height,0,-20>*0.5,
    0.05
    pigment {color rgb <1,0.7,0.3>}
  }
  pigment {color rgb <1,1,1>}
}

camera {
  orthographic
  up y*20
  right x*image_width/image_height*20
  sky CameraSky
  location CameraLoc 
  look_at CameraLook
}
