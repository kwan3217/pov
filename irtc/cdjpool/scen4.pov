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

#declare OrigVec="state3.inc"
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

#if(clock<0)
light_source {
  CenterPoolModule+<0.9,0.5,0.3>
  color White*0.5
}           
#end
                
camera {
  #if(clock<0)                     
    //Look at person
    location CenterPoolModule+<-0.9,0.75,0.0>
    look_at (CenterPoolModule+<-1.9,0.75,0.0>)
  #else             
    //Look from person's pov
    location CenterPoolModule+<-1.5,0.75,0.0>
    look_at (BallPos[TargetBall])*ScaleFac+TransFac
  #end
}

