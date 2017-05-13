#version 3.7;
#include "factor.inc"

#declare InternalBrightness=1;
#declare SimpleStation=1;
#declare AstronautRotate=<0,0,clock*2>;
#include "station.inc"
Mechanic("state7.inc")
#declare CuePointAt=AimPoint;
#declare CuePullBack=max(-clock*5,0);
#debug concat("CuePullBack: ",str(CuePullBack,0,5),"\n")
#include "poolcue.inc"

PoolGame()

camera {
  location (CueAt-vnormalize(CuePointAt-CueAt)*6+y)*ScaleFac+TransFac
  look_at (CuePointAt)*ScaleFac+TransFac
}

