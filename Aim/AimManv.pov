#declare Deploy=1;
#declare TimeMod=0;

#include "LocLook.inc"
#include "Math.inc"
#include "AimAttCommon.inc"
#include "EarthMod.inc"
#include "TriBox.inc"

#macro Box(I,Corner)
  #local NN=vnormalize(SunPoint);
  #local dR=-125;
  #local dL= 125;
  #local VF=vrotate(SunPoint,y*3/60);
  #local VA=vrotate(SunPoint,-y*3/60);
  #local R=Pos(I);
  #local T=(dR-vdot(NN,R))/vdot(NN,VF);
  #declare Corner[0]=R+VF*T; //URF
  #local T=(dR-vdot(NN,R))/vdot(NN,VA);
  #declare Corner[1]=R+VA*T; //URA
  #local T=(dL-vdot(NN,R))/vdot(NN,VF);
  #declare Corner[2]=R+VF*T; //ULF
  #local T=(dL-vdot(NN,R))/vdot(NN,VA);
  #declare Corner[3]=R+VA*T; //ULA
#end

#macro CV(T1,T2,dT)
  #if(T1<=T2)
    mesh {
      BoxStack(T1,T2,dT)
      pigment {color rgbt <CVColor.x,CVColor.y,CVColor.z,0>}
      finish {brilliance 0}
      no_shadow
      double_illuminate
    }
  #end
#end

#macro Frame(cx,cy,cz)
  union {
  	union {
    	cylinder {<0,0,0>,  <0.8,0,0>,0.05}
    	cone     {<1,0,0>,0,<0.8,0,0>,0.1}
			pigment {color cx}
		}
  	union {
    	cylinder {<0,0,0>,  <0,0.8,0>,0.05}
    	cone     {<0,1,0>,0,<0,0.8,0>,0.1}
			pigment {color cy}
		}
  	union {
    	cylinder {<0,0,0>,  <0,0,0.8>,0.05}
    	cone     {<0,0,1>,0,<0,0,0.8>,0.1}
			pigment {color cz}
		}
		finish {ambient 0.5 diffuse 0.5}
  }
#end

#if (clockSec<-90)
  #declare FlyAround=-90;
  #declare FlyOver=0;
#else
  #if(clockSec<90)
    #declare FlyAround=Linterp(-90,-90,90,-270,clockSec);
    #declare FlyOver=Quadterp(-90,0,0,1,90,0,clockSec);
  #else
    #declare FlyAround=-270;
    #declare FlyOver=0;
  #end
#end

#declare CamDiff=vaxis_rotate(OrbitNorm,Pos(clockSec),FlyAround)*0.010+vnormalize(Pos(clockSec))*(0.005+FlyOver*0.005);
PrintVector("CamDiff: ",CamDiff)
#declare CamLoc=Pos(clockSec)+CamDiff*1;
//#declare CamLoc=<0,2,-5>*Re;
#declare Look=Pos(clockSec)-y*(9-BetaD)*0.002*FlyOver;
#declare Angle=degrees(atan2(4/3,1));
//#declare Angle=10;

#switch(CipsState)
  #case(0) //Cips off
    #break
  #case(1) //Cips on
  #case(2) //Cips Exposure
    #declare CipsOn=1;
    #declare CipsColor=<CipsDapatColor.x,CipsDapatColor.y,CipsDapatColor.z,0.8>;
    #break
#end

#include "Aim.inc"

object {
  Aim
  AimAtt2()
}

union {
  Frame(x,y,z)
	scale 0.002
	translate Pos(clockSec)
}

union {
  Frame(y+z,z+x,x+y)
	scale 1.5
	rotate x*180
  AimAtt2()
}

#declare Sky=Pos(clockSec);

#declare Detail=-1;
#declare SuDetail=99;
#declare SunLights=1;

#include "PlanetMod.inc"

object {
  SunModel
  translate SunPoint
}

camera {
  location CamLoc
  look_at Look
  sky Sky
}

global_settings {max_trace_level 20}


light_source {
  CamLoc
  color rgb 0
}

CV(SofieCVStart,SofieCVEnd,2)

#declare TransCipsHollowFOVCluster=difference {
  object {CipsHollowFOVCluster AimAtt2()}
  plane {
    #declare b=asin((Re+Hc)/(Re+Alt));
    #declare Q=pow(Re+Hc,2)/(Re+Alt);
    Pos(clockSec),Q
  }
}

sphere {
  0,Re+0.00001
  texture {
    object {
      TransCipsHollowFOVCluster
      texture {pigment {color rgbf <1,1,1,1>} finish {ambient 0 diffuse 0}}
      texture {pigment {color rgb CipsDapatColor} finish {ambient 1 diffuse 0}}
    }
  }
  no_shadow
} 

sphere {
  0,Re
	pigment {color rgb <0,0,1>}
	finish {ambient 0.5 diffuse 0.5 brilliance 0}
}
