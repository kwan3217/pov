#declare Deploy=1;
#declare TimeMod=0;

#include "LocLook.inc"
#include "Math.inc"
#include "AimAttCommon.inc"
#include "EarthMod.inc"
#include "TriBox.inc"

#macro LH(V)
  (<V.x,V.z,V.y>)
#end

#macro Arrow(tail,head)
 	cylinder {LH(tail),  LH(tail+(head-tail)*0.8),0.05}
 	cone     {LH(head),0,LH(tail+(head-tail)*0.8),0.1}
#end
  
#macro Frame(cx,cy,cz)
  union {
  	union {
		  Arrow(0*x,x)
			pigment {color cx}
		}
  	union {
		  Arrow(0*x,y)
			pigment {color cy}
		}
  	union {
		  Arrow(0*x,z)
			pigment {color cz}
		}
		finish {ambient 0.5 diffuse 0.5}
  }
#end

#include "Aim.inc"

#macro blinterp(x1,y1,x2,y2,X)
  #local Result=(Linterp(x1,y1,x2,y2,min(max(X,x1),x2)));
	(Result)
#end
	
#macro AimAtt3()
  // pseudoroll=bodyroll=frame x
  rotate -LH(x)*blinterp(0,0,1,RollD,clock)  	
  // pseudopitch=frame y
	#if(clock<3)
  rotate -LH(y)*blinterp(2,0,3,-PitchD,clock)  	
	#else
  rotate -LH(y)*blinterp(3,-PitchD,4,PitchD,clock)  	
	#end
  // pseudoyaw=frame z
  rotate -LH(z)*blinterp(5,0,6,YawD,clock)  	
#end

object {
  Aim
  AimAtt3()
}
/*
union {
  Frame(x,y,z)
	scale 2
}

union {
  Frame(y+z,z+x,x+y)
	union {
  	Arrow(0*x,<cos(aR),0,sin(aR)>)
		pigment {color rgb 1}
	}
	rotate x*180
	scale 1.5
  AimAtt3()
}
*/
union {
	Arrow(0*x,<cos(aR),0,sin(aR)>)
  pigment {color rgb 1}
	rotate x*180
	scale 1.5
  AimAtt3()
}

#switch(clock)
  #range(0,1)
    #declare Lon=0;
    #declare Lat=0;
		#break
  #range(1,2)
	  #declare Lon=Linterp(1,0,2,-90,clock);
		#declare Lat=Quadterp(1,0,1.5,30,2,0,clock);
		#break
  #range(2,4)
	  #declare Lon=-90;
		#declare Lat=0;
		#break
  #range(4,5)
	  #declare Lon=-90;
		#declare Lat=Linterp(4,0,5,89.9999,clock);
		#break
  #range(5,6)
	  #declare Lon=-90;
		#declare Lat=89.9999;
		#break
#end	
union {
	Arrow(0*x,x)
	rotate -y*BetaD
	scale 2
	pigment {color rgb <1,0.5,0>}
}
	
#declare Lon=radians(Lon);
#declare Lat=radians(Lat);	
#declare CamLoc=LH(<cos(Lon)*cos(Lat),sin(Lon)*cos(Lat),sin(Lat)>*5);

camera {
  location CamLoc
  look_at <0,0,0>
}

global_settings {max_trace_level 20}

light_source {
  CamLoc
  color rgb 0.5
}

light_source {
  x*1e6
	color rgb 1.5
	rotate -y*BetaD
}

#if(clock>1)
plane {
  LH(z),0
	pigment {checker color rgbt <1,1,1>+t*0.8 color rgbf <1,1,1,1>}
	finish {ambient 1}
	scale 0.2
  no_shadow
}
#end
