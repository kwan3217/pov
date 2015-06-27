#include "KwanMath.inc"
#include "LocLook.inc"
#include "hud.inc"
#include "textures.inc"

#version unofficial Megapov 1.22;
global_settings{right_handed}
#include "SpiceQuat.inc"
#include "MavenHifi.inc"

#furnsh "generic/generic.tm"
#furnsh "mvn/fk/maven_v04_draft02.tf"
#furnsh "mvn/ik/maven_iuvs_v01.ti"
#furnsh "mvn_sc_rec_141112_141113_v03.bc"
#furnsh "mvn_app_rec_141112_141113_v03.bc"
#furnsh "mvn_iuv_all_l0_20141112_v002.bc"
#furnsh "trj_orb_00226-00228_00312_v1.bsp"
#furnsh "MVN_SCLKSCET.00012.tsc"

#declare StartCal="2014 Nov 12 19:42:17.97401UTC"
#declare StopCal ="2014 Nov 12 20:03:56.21638UTC"
#declare StartET=str2et(StartCal);
#declare StopET =str2et(StopCal );

#declare ET=Linterp(StartET,0,StopET,1,clock);

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
