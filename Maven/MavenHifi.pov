#include "KwanMath.inc"
#include "LocLook.inc"
#include "hud.inc"
#include "textures.inc"

#version unofficial Megapov 1.22;
global_settings{right_handed}
#include "SpiceQuat.inc"
#include "MavenHifi.inc"

#furnsh "generic/generic.tm"
#furnsh "mvn/mvn.tm"
#furnsh "mvn_iuv_fake_drm_f.bc"
#furnsh "trj_o_od018a_140312-151108_reference_v1.bsp"

#declare StartCal="2015 AUG 03 08:58:30.731 TDB"
#declare StartET=str2et(StartCal);

#declare ET=StartET+frame_number;

#local V=<0,0,0>;
#local R=1000*spkezr("MAVEN",ET,"MAVEN_MME_2000","NONE","MARS",V);
#local V=1000*V;
#local N=vnormalize(vcross(R,V));
light_source {
  vnormalize(spkezr("SUN",ET,"MAVEN_MME_2000","LT+S","MAVEN"))*1e11
  color rgb <1,1,1>
  shadowless
}

#local cameraSky=vnormalize(R);

//object {MavenBus}
union {
  MavenHiFi(ET)
  QuatTrans(pxform("MAVEN_SPACECRAFT","MAVEN_MME_2000",ET),<0,0,0>)
}

union {Vector(0,vnormalize(R)*3,0.1) pigment {color rgb <1,0.5,0>}}
union {Vector(0,vnormalize(V)*3,0.1) pigment {color rgb <1,1,1>}}
  

sphere {
  -R,3397*1000
  pigment {color rgb <1,0.5,0>}
}


#local cameraAngle=1;
#local cameraDist=30;
#local cameraLoc=vnormalize(10*vnormalize(V)+0*vnormalize(R)-0*vnormalize(N))*cameraDist;
camera {
  up y
  right x*image_width/image_height
  sky cameraSky
  location cameraLoc
  angle 45
  look_at 0
}

light_source {
  cameraLoc
  color rgb <0.5,0.5,0.5>
  shadowless
}
