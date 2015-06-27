#include "BlueMarbleJava.inc"
#include "KwanMath.inc"

#declare Rsc=6500*exp(1-clock);

#declare Sky=y;
#declare Pos=LLA2XYZ(radians(40),radians(-105),Rsc);
#declare ActualPos=Pos;//LH(<20000,0,0>);
#declare Look=<0,0,0>;
#declare Theta=0;
#declare CamLoc=Pos;

#declare BEarth=AEarth;
#declare Angle=44;
#declare UseTest=0;

text {
  ttf "arialn.ttf" str(Rsc,0,1) 0 0
	pigment {color rgb <1,1,1>}
	rotate -y*90
	scale 2
	translate ActualPos-x*20
}

#declare HorizonDist=sqrt(Rsc*Rsc-AEarth*AEarth);
PrintNumber("HorizonDist: ",HorizonDist)
#declare Ratio=Rsc/AEarth;
#declare HorizonRad=HorizonDist/Ratio;
PrintNumber("HorizonRad: ",HorizonRad)
#declare HorizonHeight=AEarth/Ratio;
PrintNumber("HorizonHeight: ",HorizonHeight)

#macro Earth(CamLoc,Look,Angle)
	union {
   	EarthMod(vrotate(CamLoc,y*Theta),vrotate(Look,y*Theta),Angle)
   	rotate -y*Theta
 	}
#end

Earth(CamLoc,Look,Angle)

light_source {
  1000*Pos
	color rgb 1.5
}

#declare Pov=true;

#if(Pov)
  camera {
    up y
  	right x
    location ActualPos
    look_at Look
	  sky Sky
  	angle Angle
  }
#else
  sphere {
    CamLoc,100
  	pigment {color rgb 1}
  }

	cone {
  	CamLoc,100,CamLoc+Sky*500,0
		pigment {color rgb <1,0,0>}
	}

	cone {
  	CamLoc,100,(Look-Pos)*500+Pos,0
		pigment {color rgb <1,1,0>}
	}

	camera {
  	up y
		right x
  	location CamLoc*2
		look_at CamLoc
	}
#end
