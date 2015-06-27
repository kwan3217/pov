#declare Deploy=1;

#include "LocLook.inc"
#include "Math.inc"
#include "AimAttCommon.inc"
#include "EarthMod.inc"
#include "Aim.inc"
#include "TriBox.inc"

#declare Look=y*(Re+Alt);
#declare CamLoc=Look+y*Re*0.5;
#declare Angle=degrees(atan2(4/3,1));

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
    pigment {color rgbt <CVColor.x,CVColor.y,CVColor.z,0.8>}
    finish {brilliance 1 ambient 1}
    no_shadow
  }
#end

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
  up y
  right x
  location <0,0,0>
  look_at <0,1,0>
  sky z
  angle CipsFovSize
  #switch(CipsView)
    #case(0)
      #debug "Cips Forward"
      rotate z*CipsFwdAngle
      #break
    #case(1)
      #debug "Cips Aft"
      rotate -z*CipsFwdAngle
      #break
    #case(2)
      #debug "Cips Left"
      rotate x*CipsSideAngle
      #break
    #case(3)
      #debug "Cips Right"
      rotate -x*CipsSideAngle
      #break
  #end
  rotate z*180
  AimAtt2()
}

global_settings {max_trace_level 20}

#if(clockSec>SofieCVStart)
  CV(SofieCVStart,min(SofieCVEnd,clockSec),1)
#end

//Ozone Layer
sphere {
  0,Re+OzoneHeight
  texture {pigment {color rgb 0} finish {ambient 0 diffuse 0}}
} 

CloudDeck()
