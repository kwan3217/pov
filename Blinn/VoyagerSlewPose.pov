#include "KwanMath.inc"
#include "LocLook.inc"
#include "hud.inc"
#include "textures.inc"

//#version unofficial Megapov 1.22;

#furnsh "generic/generic.tm"
#furnsh "Voyager/vgr2.tm"
#furnsh "Voyager/fk/vg2_slew.tf"
#furnsh "Voyager/ck/v2j_slew.bc"

#declare NWnd=ckcov("Voyager/ck/vg2_jup_version1_type1_iss_sedr.bc",-32100,"INTERVAL",0,"TDB",100000);
PrintNumber("NWnd: ",NWnd)

#declare I=12104+293;
#declare I0=I-5;
#declare I1=I+5;
#declare ET0=ckgetcov(I0,0);
#declare ET1=ckgetcov(I1,0);
#declare ET=Linterp(0,ET0,1,ET1,clock);
#declare I=0;
#while(ckgetcov(I,0)<ET) 
  #declare I=I+1;
#end
#declare ETScan=ckgetcov(I-1,0);
PrintNumber("ETScanI: ",I)
PrintNumber(etcal(ETScan),ETScan)
PrintNumber("ET0: ",I0)
PrintNumber(etcal(ET0),ET0)
PrintNumber("ET1: ",I1)
PrintNumber(etcal(ET1),ET1)
PrintNumber("ET: ",I)
PrintNumber(etcal(ET),ET)
#declare SCQ=pxform("VG2_SCAN_PLATFORM","VG2_SC_BUS",ETScan);
//#declare SCQ=pxform("VG2_AZ_EL","VG2_SC_BUS",0);
#declare SCQS=pxform("VG2_SLEW_PLATFORM","VG2_SC_BUS",ET);
PrintQuat("Scan Platform to Spacecraft: ",SCQ)
PrintQuat("Slew Platform to Spacecraft: ",SCQS)

#include "SpiceQuat.inc"

camera {
  orthographic
  up y*8
  right -x*image_width/image_height*8
  location -8*y*10
  look_at <0,0,0>
  sky z
}     

#include "Voyager.inc"
#declare LocalVoyager=union {
  object{VoyagerQSpice(SCQ)}
  object{VoyagerQSpice(SCQS)}
  cylinder {0,x*2.1,0.1 pigment {color rgb x}}
  cylinder {0,y*2.1,0.1 pigment {color rgb y}}
  cylinder {0,z*2.1,0.1 pigment {color rgb z}}
  sphere {x*2.1 0.2 pigment {color rgb <1,1,1>}}
  sphere {y*2.1 0.2 pigment {color rgb <1,1,1>}}
  sphere {z*2.1 0.2 pigment {color rgb <1,1,1>}}
  union {
    cylinder {0,x*1.3,0.05 pigment {color rgb x}}
    cylinder {0,y*1.3,0.05 pigment {color rgb y}}
    cylinder {0,z*1.3,0.05 pigment {color rgb z}}
    sphere {x*1.3 0.1 pigment {color rgb <1,1,0>}}
    sphere {y*1.3 0.1 pigment {color rgb <1,1,0>}}
    sphere {z*1.3 0.1 pigment {color rgb <1,1,0>}}
    QuatTrans(pxform("VG2_AZ_EL","VG2_SC_BUS",0),SPCenter)
  }
  rotate z*90
  rotate y*180
  translate <-SPCenter.y,SPCenter.x,SPCenter.z>
}

object {
  LocalVoyager 
  translate -x*1.5
  translate -z*1.7
}

object {
  LocalVoyager 
  rotate x*90
  translate -x*1.5
  translate  z*1.7
}

object {
  LocalVoyager 
  rotate -z*90
  translate  x*1.5
  translate -z*1.7
}



background {color rgb <0,0.5,1>}

light_source {
  -5*y*1000
  color rgb 1
}
