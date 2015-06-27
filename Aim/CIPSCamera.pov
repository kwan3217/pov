#include "BlueMarbleJava.inc"
#include "Math.inc"

#include "CIPSCameraVectors.inc"

#declare Sky=LH(SkyArray[frame_number]);
#declare Pos=LH(PosArray[frame_number]);
#declare Look=Pos+LH(LookArray[frame_number]);
#declare Theta=ThetaArray[frame_number];
#declare CamLoc=Pos;

//#declare BEarth=AEarth;
#declare Angle=44;
#declare UseTest=0;

#declare Rsc=7000;
#declare HorizonDist=sqrt(Rsc*Rsc-AEarth*AEarth);
PrintNumber("HorizonDist: ",HorizonDist)
#declare Ratio=Rsc/AEarth;
#declare HorizonRad=HorizonDist/Ratio;
PrintNumber("HorizonRad: ",HorizonRad)
#declare HorizonHeight=AEarth/Ratio;
PrintNumber("HorizonHeight: ",HorizonHeight)

torus {
  HorizonRad,20
	rotate z*90
	translate x*HorizonHeight
	pigment {color rgb <1,1,1>}
}

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
    location CamLoc
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
