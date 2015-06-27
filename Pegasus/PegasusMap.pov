#include "PegasusLaunchCommon3.inc"

union {
#declare I=0;
#while(I<dimension_size(TheBigSITable,1)-1)
  sphere {
	  GetPos(I),20000
	}
	cylinder {
	  GetPos(I),GetPos(I+1),10000
	}
	#declare I=I+1;
#end
  pigment {color rgb <1,0,0>}
  translate -Pos
}
	
#declare Look=<0,0,0>;
#declare CamLoc=AEarth*3*<cos(radians(-120)),0,sin(radians(-120))>;
#declare Sky=y;
#declare Angle=atan(4/3);

union {
Earth(CamLoc,Look,Angle)
}
Camera(CamLoc,Look,0,0,0,Angle)
