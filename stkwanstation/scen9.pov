#version 3.7;
#include "factor.inc"

#if(clock<8.75)
#declare UseShuttle=1;
#end

#include "station.inc"

//Floors and ceilings
#declare Floor=array[2] {-1800,1800}

//Walls
#declare WallX=array[2] {-3600,3600}
#declare WallZ=array[2] {-1800,1800}
                      
#declare AirResist=0;
#declare OrigVec="earthvec.inc";
#include "mechanic.inc"

#declare EarthPos=BallPos[1];
Earth(30+clock)

#if(clock>15)
#declare BallNumber=9;
#include "poolball.inc"
object {
  Ball
  rotate BallPos[1]*10
  translate BallPos[0]+(1.5*z)
  scale 637814
}
#end

light_source {
  <10000000,0,-10000000>
  color <1,1,1>
}

#declare CreditClock=clock*2.2; 
#declare CreditScale=exp(clock/5);

UseStation(1)
    
object {
  #include "credits.inc"
  #translate <0,0,-exp(min(clock,17))*0.1>
}

camera {
  location <0,0,-exp(min(clock,17))*0.1>
  look_at <0,0,0>
}                                


