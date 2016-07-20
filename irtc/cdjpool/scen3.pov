#version 3.7;
#include "factor.inc"

#declare InternalBrightness=min(8-clock,1);
#declare AstronautRotate=<0,0,clock*2>;
#include "station.inc"
Mechanic("state2.inc")
#declare CuePointAt=AimPoint;
#declare CuePullBack=max(-clock*5,0);
#debug concat("CuePullBack: ",str(CuePullBack,0,5),"\n")
#include "poolcue.inc"

PoolGame()

camera {
  location (BallPos[0]-vnormalize(BallSpd[0])*3+y)*ScaleFac+TransFac
  look_at (BallPos[TargetBall]+y)*ScaleFac+TransFac
}

