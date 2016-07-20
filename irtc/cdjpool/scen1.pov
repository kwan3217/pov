#version 3.7;
#include "factor.inc"

#declare InternalBrightness=min(8-clock,1);
#declare UseShuttle=1;
#include "station.inc"
#include "state1.inc"

#declare CuePointAt=AimPoint;
#declare CuePullBack=5;
#warning concat("CuePullBack: ",str(CuePullBack,0,5),"\n")
#include "poolcue.inc"

#declare ScaleFac=0.03;  
#declare TransFac=CenterPoolModule;
#declare EarthPos=<0,0,0>;
Earth(120+30+clock*8)

light_source {
  <10000000,0,-10000000>
  color <1,1,1>*InternalBrightness
}

PoolGame()

//Scene 1 Camera  
#declare A=3.6888794541139;
#declare B=2.995732273554;
camera {
  #declare KlockA=1-clock;
  #declare KlockB=(0.75-clock)*4/3;
  #if(clock<0.75)
    #declare L=vrotate(<0,2.5*exp(KlockB*B)-2.5,-2.5*exp(KlockA*A)>,<0,-360*KlockB,0>);
    location L+CenterPoolModule
    look_at CenterPoolModule+z*20*sin(clock*pi)
  #else
    #declare L=<0,0,-2.5*exp(KlockA*A)>;
    location L+CenterPoolModule
    look_at CenterPoolModule
  #end               
  DispReal("KlockA",KlockA)
  DispReal("KlockB",KlockB)
  DispVec("Camera Location",L) 
}                


