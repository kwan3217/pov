#version 3.7;
#include "factor.inc"

#declare InternalBrightness=min(8-clock,1);
#declare UseShuttle=1;
#include "station.inc"

#declare AirResist=0;
Mechanic("state0.inc")
#declare CuePointAt=AimPoint;
#declare CuePullBack=max(-clock*5,0);
#debug concat("CuePullBack: ",str(CuePullBack,0,5),"\n")
#include "poolcue.inc"

PoolGame()

camera {
#if(clock<3)
  location <0,65,0>*ScaleFac+TransFac
#else
  location vrotate(<0,65,0>,-x*(clock-3)*90/5+y*(clock-3)*15/5)*ScaleFac+TransFac
#end
  look_at <0,0,0>*ScaleFac+TransFac 
#if(clock<3) 
  angle 42
#else   
  angle 42+(clock-3)*12/5
#end
}
                

