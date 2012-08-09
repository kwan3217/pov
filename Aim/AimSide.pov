#declare Deploy=1;

#include "LocLook.inc"
#include "Math.inc"
#include "AimAttCommon.inc"
#include "EarthMod.inc"
#include "TriBox.inc"

//#declare OrbitLeadSec=140;
#declare Look=Pos(clockSec);
#declare CamLoc=Look-z*Re*0.75;
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
  #if(T2>=T1)
    mesh {
      BoxStack(T1,T2,dT)
      pigment {color rgb CVColor}
      no_shadow
      double_illuminate
      finish {brilliance 0 ambient 0.5}
    }
  #end
#end

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

light_group {
  object {
    Aim
    translate y*1.2
    scale 2e5
    AimAtt2()
    no_shadow
  }
  light_source {
    SunPoint
    color rgb 1
  }
  global_lights off
}

difference {
  object {
    CipsFOVCluster
    AimAtt2()
  }
  plane {
    #declare Q=pow(Re+Hc,2)/(Re+Alt);
    Pos(clockSec),Q
    pigment {color rgbf <1,1,1,1>}
  }
}

#declare Sky=y;

camera {
  location CamLoc
  look_at Look
  sky y
}

global_settings {max_trace_level 20}

PrintVector("Pos:        ",Pos(clockSec))
#if(SofieState>0)
  object {
    SofieFOV
    translate -SofiePoint0
    scale 2e5
    AimAtt2()
    pigment {color SofieDapatColor}
  }
#end


CV(SofieCVStart,min(SofieCVEnd,clockSec),1)

light_group {
  union {
    EarthMod()
  }
  light_source {
    SunPoint
    color rgb 1
  }
  global_lights off
}
