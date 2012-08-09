#declare Deploy=1;

#include "LocLook.inc"
#include "Math.inc"
#include "AimAttCommon.inc"
#include "Aim.inc"
#include "TriBox.inc"

#declare Look=y*(Re+Alt);
#declare CamLoc=Look+y*Re*0.5;
#declare Angle=degrees(atan2(4/3,1));
//#declare Angle=10;

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
  mesh {
    BoxStack(T1,T2,dT)
    pigment {color rgb CVColor}
    finish {brilliance 0 ambient 1 diffuse 0}
    no_shadow
  }
#end

#include "Aim.inc"

object {
  Aim
  translate y*1.2
  scale 2e5
  AimAtt2()
}

//#declare Sky=ZenithPoint-Pos(clockSec);
#declare Sky=Pos(clockSec);

#declare Detail=-1;
#declare SuDetail=99;
#declare SunLights=1;

#include "PlanetMod.inc"

object {
  SunModel
  translate SunPoint
//  scale 1/100
}

camera {
  location CamLoc
  look_at Look
  sky y
}

global_settings {max_trace_level 20}

light_source {
  CamLoc
  color rgb 0
}

#if(clockSec>SofieObsStart & clockSec<SofieCalEnd)
  object {
    SofieFOV
    scale 4e4
    AimAtt2()
    pigment {color rgbt SofieDapatColor}
  }
#else
  #declare SofieStatus="Sofie off"
#end

#if(clockSec>SofieCVStart)
  CV(SofieCVStart,min(SofieCVEnd,clockSec),1)
#end

#declare TransCipsHollowFOVCluster=difference {
  object {CipsHollowFOVCluster AimAtt2()}
  plane {
    #declare b=asin((Re+Hc)/(Re+Alt));
    #declare Q=pow(Re+Hc,2)/(Re+Alt);
    Pos(clockSec),Q
  }
}

sphere {
  0,Re+Hc
  texture {
    object {
      TransCipsHollowFOVCluster
      texture {pigment {color rgbf <1,1,1,1>} finish {ambient 0 diffuse 0}}
      texture {pigment {color rgb CipsDapatColor} finish {ambient 1 diffuse 0}}
    }
  }
} 

