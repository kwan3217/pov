#include "KwanMath.inc"
#include "LocLook.inc"
#include "hud.inc"
#include "textures.inc"

#version unofficial Megapov 1.22;

#furnsh "generic/generic.tm"
#furnsh "Voyager/vgr2.tm"

#declare NWnd=ckcov("Voyager/ck/vg2_ura_version1_type1_iss_sedr.bc",-32100,"INTERVAL",0,"TDB",10000);
PrintNumber("NWnd: ",NWnd)

#declare I=4952+frame_number;
#declare ETScan=ckgetcov(I,0);
PrintNumber("ETScanI: ",I)
PrintNumber(etcal(ETScan),ETScan)
#declare SCQ=pxform("VG2_SCAN_PLATFORM","VG2_SC_BUS",ETScan);
PrintQuat("Scan Platform to Spacecraft: ",SCQ)

#include "SpiceQuat.inc"

camera {
  orthographic
  up y*1.5
  right x*image_width/image_height*1.5
  location <0,-8,0>*10
  look_at <0,0,0>
  sky z
}     

#include "Voyager.inc"
union {
  object{VoyagerQSpice(SCQ)}
  union {
/*
    cylinder {0, x,0.1 pigment {color rgb x}} 
    cylinder {0,-x,0.1 pigment {color rgb <1,1,1>-x}} 
    cylinder {0, y,0.1 pigment {color rgb y}} 
    cylinder {0,-y,0.1 pigment {color rgb <1,1,1>-y}} 
    cylinder {0,z*5,0.1 pigment {color rgb z}}
    cylinder {0,-z,0.1 pigment {color rgb <1,1,1>-z}}
*/
    QuatTrans(SCQ,SPCenter)
  } 
//  union {
//    cylinder {0, x*5,0.5 pigment {color rgb x}} 
//    cylinder {0,-x*5,0.5 pigment {color rgb <1,1,1>-x}} 
//    cylinder {0, y*5,0.5 pigment {color rgb y}} 
//    cylinder {0,-y*5,0.5 pigment {color rgb <1,1,1>-y}} 
//    cylinder {0, z*5,0.5 pigment {color rgb z}}
//    cylinder {0,-z*5,0.5 pigment {color rgb <1,1,1>-z}}
//  } 
  rotate z*90
  rotate y*180
  translate <-SPCenter.y,SPCenter.x,SPCenter.z>
}

background {color rgb <0,0.5,1>}

light_source {
  <0,-5,0>*1000
  color rgb 1
}
