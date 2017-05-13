#version 3.7;
#include "factor.inc"

#declare InternalBrightness=min(8-clock,1);
#declare SimpleStation=1;
#declare AstronautRotate=<0,0,clock*2>; 
#include "station.inc"
Mechanic("state1.inc")
#declare CuePointAt=AimPoint;
#declare CuePullBack=max(-clock*5,0);
#debug concat("CuePullBack: ",str(CuePullBack,0,5),"\n")
#include "poolcue.inc"

PoolGame()

camera {
  location CenterPoolModule-z*2.5+z*(clock+1)/4.5+x*2*(clock+1)/9
  look_at CenterPoolModule
}

