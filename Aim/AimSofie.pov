#declare Deploy=1;

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
  #local VF=vaxis_rotate(VF,SunPoint,-22);//ScRoll(-200));
  #local VA=vrotate(SunPoint,-y*3/60);
  //#local VA=vaxis_rotate(VA,SunPoint,-22);//ScRoll(-200));
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
    finish {brilliance 0}
    no_shadow
    double_illuminate
  }
#end

#declare CamLoc=Pos(clockSec);

#if(clockSec<SofieCalEnd)
  #declare Look=SunPoint;
#else
  #if(clockSec<SofieCalEnd+300)
    #declare Look=Pos(clockSec)+Linterp(SofieCalEnd,vnormalize(SunPoint),SofieCalEnd+300,vnormalize(Vel(clockSec)),clockSec);
  #else
    #declare Look=Pos(clockSec)+Vel(clockSec);
  #end
#end
//#declare Angle=degrees(atan2(4/3,1));
#declare Angle=2;

#include "Aim.inc"

#declare Detail=-1;
#declare SuDetail=99;
#declare SunLights=1;

#include "PlanetMod.inc"

#declare SunPoint=<0,0,0>;
object {
  SunModel
  TranslateAlso(x*149500000,SunPoint)
  RotateAlso(-y*BetaD,SunPoint)
}

camera {
  location 0
  look_at x
  sky y
  angle Angle
  rotate -z*14
  AimRot2()
  translate Pos(clockSec)
}

global_settings {max_trace_level 20}


light_source {
  CamLoc
  color rgb 0
}

#if(SofieState>0)
  box {
    <0,-tan(radians(1/60)),-tan(radians(3/60))>*100,<0,tan(radians(1/60)),tan(radians(3/60))>*100
    translate x*100
    rotate -z*14
    AimRot2()
    translate Pos(clockSec)
    pigment {color rgbt SofieDapatColor}
  }
#end

#if(clockSec>SofieCVStart)
  CV(SofieCVStart,min(SofieCVEnd,clockSec),2)
#end


//EarthMod()
CloudDeck()
sphere {
  0,Re
  pigment {color rgb <0,0,1>}
  finish {ambient 0.5 brilliance 0}
}
