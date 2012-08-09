#include "colors.inc"
#include "metals.inc"
#include "KwanMath.inc"
#include "casquat.inc"
#include "Flame.inc"

#declare white=texture {pigment {color rgb<1,1,1>}}
#declare silver=texture {T_Chrome_5C}
#declare anod_aluminum=texture {T_Chrome_2A}
#declare gold=texture {T_Gold_5C}
#declare red_orange=texture {pigment {color rgb<1,0.25,0>}}
#declare aluminum=texture {T_Chrome_3A}
#declare black=texture {pigment {color rgb<0.3,0.3,0.3>}}
#declare grey=texture {pigment {color rgb<0.5,0.5,0.5>}}
#declare Mark=texture {pigment {color rgb<1,0,0>}}

#declare NaN=1;
//The official unit of a spacecraft is meters
//The official orientation of Cassini is HGA towards +Y, RSP boresight towards +Z
//The CAD data was in inches.
//The origin is on the HGA boresight, on the interace plane between the bus and USS
//Seperation plane is -123.134178*y inches
//                    -  3.127608*y meters
#declare Cassini=union {  
  union {#include "ant_assy.inc"}
  union {#include "rsp_assy.inc"}
  union {#include "uss_assy.inc"}
  union {#include "lvr_assy.inc"}
  union {#include "pm_assy.inc"}
  union {#include "rtg_assy.inc"}
  union {#include "bus_assy.inc"}
  union {#include "rocket_assy.inc"}
  union {#include "sci_assy.inc"}     
//  union {#include "huy_assy.inc"}     
  union {#include "tank_assy.inc"}
/*
  object {
    Flame
		rotate -x*90
		scale 10
	  translate <0,210,0> 
	  rotate x*2.9
	  translate <-1.5,-60,0>
	}
*/

  rotate x*180   
  scale 0.0254 //convert inches to m
}

#macro OrientCassini(q1,q2,q3,q4)
  //Transform from "official" orientation to JPL orientation
	matrix <
	//Old +x becomes new +x (away from Huygens)
	1,0,0
	//Old +y becomes new -z (towards HGA boresight)
	0,0,-1
	//Old -z (Mag boom) becomes new +y
	0,-1,0
	0,0,0>
	quat2matx(q1,q2,q3,q4)

  //switch handedness
  matrix <1,0,0,
	        0,0,1,
					0,1,0,
					0,0,0>
#end					

#macro OrientCassini2(T)
  //Transform from "official" orientation to JPL orientation
	matrix <
	//Old +x becomes new +x (away from Huygens)
	1,0,0
	//Old +y becomes new -z (towards HGA boresight)
	0,0,-1
	//Old -z (Mag boom) becomes new +y
	0,-1,0
	0,0,0>
	#declare syscmd=concat("/home/chrisj/bin/useIndex.pl ",str(T,15,7)," \"#declare OC\"")
	#debug concat(syscmd,"\n")
	#system syscmd
  PrintVector("Row0: ",OCRow0)
  PrintVector("Row1: ",OCRow1)
  PrintVector("Row2: ",OCRow2)
	matrix <OCRow0.x,OCRow0.y,OCRow0.z,
	        OCRow1.x,OCRow1.y,OCRow1.z,
					OCRow2.x,OCRow2.y,OCRow2.z,
					0,0,0>

  //switch handedness
  matrix <1,0,0,
	        0,0,1,
					0,1,0,
					0,0,0>
#end					

