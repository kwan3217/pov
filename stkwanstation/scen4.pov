#version 3.7;
#include "factor.inc"

#declare InternalBrightness=1;
#declare SimpleStation=1;
#declare AstronautRotate=<0,0,clock*2>;
#include "station.inc"
Mechanic("state3.inc")
#declare CuePointAt=AimPoint;
#declare CuePullBack=max(-clock*5,0);
#debug concat("CuePullBack: ",str(CuePullBack,0,5),"\n")
#include "poolcue.inc"

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

