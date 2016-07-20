#version 3.7;
#include "factor.inc"

#declare InternalBrightness=min(8-clock,1);
#declare UseShuttle=1;
#include "station.inc"
#if(clock<8)
#declare MechanicClock=clock;
#end

#declare OrigVec="state0.inc"
#declare AirResist=0;
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
Earth(30+clock*0.9)

light_source {
  <10000000,0,-10000000>
  color <1,1,1>*InternalBrightness
}

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
                

