#version 3.7;
#include "factor.inc"

#declare InternalBrightness=min(8-clock,1);
#declare UseShuttle=1;
#include "station.inc"
#include "state1.inc"

#declare CuePointAt=AimPoint;
#declare CuePullBack=5;
#debug concat("CuePullBack: ",str(CuePullBack,0,5),"\n")
#include "poolcue.inc"

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


