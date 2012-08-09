#declare ClockMode=1;	
#include "PegasusLaunchCommon2.inc"

#declare Look1=PlanePos-R*100-TA*150;
#declare Look2=Pos;
#if(PegasusClock<5)
  #declare Look=Look1;
#else
  #if(PegasusClock<10)
	  #declare Look=Linterp(5,Look1,10,Look2,PegasusClock);
  #else
	  #declare Look=Look2;
	#end
#end
#declare CamLoc=PlanePos-R*100-TA*150+NA*500;
#declare Angle=radians(45);

Earth(CamLoc,Look,Angle)
Camera(CamLoc,Look,0,1,0,Angle)
