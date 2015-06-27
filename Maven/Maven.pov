#include "KwanMath.inc"
#include "LocLook.inc"
#include "hud.inc"
#include "textures.inc"

#version unofficial Megapov 1.22;

#furnsh "generic/generic.tm"
#furnsh "mvn/mvn.tm"
#furnsh "mvn_iuv_fake_drm_f.bc"
#furnsh "trj_o_od018a_140312-151108_reference_v1.bsp"

#declare StartUTC="2015 AUG 03 08:58:30.731 TDB";
#declare StartET=str2et(StartUTC);
PrintNumber("StartET: ",StartET)

//Animation settings
#declare T0=0*3600; //Start of animation relative to StartET
#declare T1=4.5*3600;//End of animation relative to StartET
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

#declare CameraLoc=<0,-10,5>;
#declare CameraLook=<0,0,0>;
#declare CameraSky=<0,0,1>;

/*
union {
  textHud(concat("06 Aug 2012 ",str(h,-2,0),":",str(m,-2,0),":",str(s,-6,3),"UTC SCET (",str(TTT,7,3),"s)"),
          <-16,-8.5>,<1,1,1>,0,-1)           
  textHud(concat("05 Aug 2012 ",str(hlt+6,-2,0),":",str(mlt,-2,0),":",str(slt,-6,3),"pm MDT ERT"),
          <-16,-9>,<1,1,1>,0,-1)           
  scale <0.175,0.175,1>
  no_shadow
  LocationLookAt(CameraLoc,CameraLook,CameraSky)
}
*/

#include "Maven.inc"


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
    Maven(ET)
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
  object {MavenAPP scale 5}
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
