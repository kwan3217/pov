#include "KwanMath.inc"
#include "LocLook.inc"
#include "hud.inc"
#include "textures.inc"

#version unofficial Megapov 1.22;

//global_settings {right_handed}

#furnsh "generic/generic.tm"
#furnsh "mvn/mvn.tm"

#declare StartUTC="2015-08-03 10:40:30.773UTC";
#declare StartET=str2et(StartUTC);
PrintNumber("StartET: ",StartET)

//Animation settings
#declare T0=1.1*3600; //Start of animation relative to StartET
#declare T1=1.55*3600;//End of animation relative to StartET
#declare ET=StartET+Linterp(0,T0,1,T1,clock); //ET of this frame
PrintNumber("This ET: ",ET)

#include "SpiceQuat.inc"

#local V=<0,0,0>;
#local R=1000*spkezr("MAVEN",ET,"MARSIAU","NONE","499",V);
#local V=1000*V;

light_source {
  vnormalize(spkezr("SUN",ET,"MARSIAU","LT+S","MAVEN"))*1e6
  color rgb <1,1,1>
}

global_settings{max_trace_level 10}

#declare CameraLoc=<-10,0,5>;
#declare CameraLook=<0,0,0>;

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

object{
  MavenBus
  #local W=<0,0,0>;
  #local Q=ckgpav(-202000,sce2c(-202,ET),0,"MARSIAU",W);
  #if(qlength(Q)>0)
    QuatTrans(Q,<0,0,0>)
  #end
}

#macro Vector(V0,V1,R)
  cylinder {
    V0,Linterp(0,V0,1,V1,0.75),R
  }
  cone {
    Linterp(0,V0,1,V1,0.75),R*2,V1,0
  }
#end
union {
  Vector(0,vnormalize(spkezr("SUN",ET,"MARSIAU","LT+S","MAVEN"))*4,0.1)
  pigment {color rgb <1,1,0>}
}
union {
  Vector(0,vnormalize(spkezr("399",ET,"MARSIAU","LT+S","MAVEN"))*4,0.1)
  pigment {color rgb <0,0,1>}
}
union {
  Vector(0,vnormalize(-R)*4,0.1)
  pigment {color rgb <1,0,0>}
}
union {
  Vector(0,vnormalize(V)*4,0.1)
  pigment {color rgb <1,1,1>}
}
union {
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
  #local Q=ckgpav(-202000,sce2c(-202,ET),0,"MARSIAU",W);
  QuatTrans(Q,<0,0,0>)
}

camera {
  up y
  right x*image_width/image_height
  location CameraLoc 
  look_at CameraLook
}
