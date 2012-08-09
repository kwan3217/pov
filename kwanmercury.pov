global_settings {max_trace_level 20}

#include "PovSolar/KwanMath.inc"
#macro bound(X,lo,hi)
  (min(hi,max(lo,X)))
#end

#macro blinterp(x1,y1,x2,y2,X)
  (bound(Linterp(x1,y1,x2,y2,X),min(y1,y2),max(y1,y2)))
#end

#local W="/h>m8X=X7KJXFXWhjhKMa$Q$AD390$&<";

#macro K()
  #declare A=A+1;
	asc(substr(W,A,1))/16-2
#end

#local A=0;

#while(A<strlen(W))
  PrintVector("",<K(),K(),0>)
#end

#local A=0;

camera{
  right x*16/9
  sky z 
	location<6*clock-3,8>
	look_at 0
}

light_source{
  y*9,1.5
	shadowless
}

sky_sphere{
  pigment{
	  gradient z 
		color_map{
		  [0 rgb<2,3,4>/4]
			[1 rgb 1]
		}
	}
}

plane{
  z,-2
  normal{ripples blinterp(3.5,1,4.5,0,clock*5) phase -clock*5}
	finish{reflection .5}
	pigment{rgb z}
}

difference{
  cylinder{-y/8,y/8,2}
	prism{
	  -9,9,16
		#while(A<32)
		  <K(),K()>-<17,22>/8
		#end
	}
	pigment{ 
    color rgb <1,0.5,0>
	}
	translate -z*4
	translate z*blinterp(0,0,4,4,clock*5)
}

#if(clock*5>2.5)
text {
  ttf "verdanab.ttf" "Kwan Heavy Industries" 0.25 0
	pigment {color rgbt <1,0.5,0,blinterp(2.5,1,3.5,0,clock*5)>}
	rotate x*90
	scale 0.5
	translate -z*1.75
	translate y*2
	translate -x*3
}
#end

#if(clock*5>3)
text {
  ttf "verdanab.ttf" "a division of Kwan Systems" 0.25 0
	pigment {color rgbt <1,1,1,blinterp(3,1,4,0,clock*5)>}
	rotate x*90
	scale 0.25
	translate -z*1.75
	translate y*3
	translate -x*1.5
}
#end

#if(clock*5>4.5)
sphere {
  0,0.0001
	 translate <6*clock-3,8>
  finish {ambient 0 diffuse 0}
	#local I=blinterp(4.5,1,5,0,clock*5);
	pigment {color rgbf <I,I,I,1>}
}
#end

#if(clock*5<0.5)
sphere {
  0,0.0001
	 translate <6*clock-3,8>
  finish {ambient 0 diffuse 0}
	#local I=blinterp(0.0,0,0.5,1,clock*5);
	pigment {color rgbf <I,I,I,1>}
}
#end
