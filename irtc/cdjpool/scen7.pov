#version 3.7;
#include "factor.inc"

#declare InternalBrightness=1;
#declare SimpleStation=1;
#declare AstronautRotate=<0,0,clock*2>;
#include "station.inc"
#if(clock<8)
#declare MClock=clock;
#end
#declare MaxIters=20; 

#declare OrigVec="state6.inc"
#if(clock<0)
  #include OrigVec
#else
  #include "mechanic.inc"
#end
#declare CuePointAt=AimPoint;
#declare CuePullBack=max(-clock*5,0);
#debug concat("CuePullBack: ",str(CuePullBack,0,5),"\n")
#include "poolcue.inc"

#declare ScaleFac=0.03;  
#declare TransFac=CenterPoolModule;
#declare EarthPos=<0,0,0>;
Earth(30+clock)

light_source {
  <10000000,0,-10000000>
  color <1,1,1>*InternalBrightness
}

PoolGame()

camera {
  location CenterPoolModule+<0,1,-1.6>
  look_at (CenterPoolModule)
}

