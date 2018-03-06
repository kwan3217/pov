//#version unofficial Megapov 1.22;
#include "Actors.inc"

#local ShotTime=array[19] {3,5,3,5,5,5,5,5,10,5,5,2,3,4,5,5,5,5,5}

CalcShotTime(ShotTime)

#switch(Shot)
  #case(0) //Title card
    union {
      Text("verdana.ttf","Moment of Inertia",0,Center)
      translate <0,-0.001,1>
      Fade(<0.8,0.8,0.8,0>,ASDR(0,0.25,0.75,1,0,1,ShotClockN))
    }
    #break
#end

camera {
  up y
  right -x*16/9
  sky z
  location <0,-9,0.5>
  look_at <0,0,0.5>
}

light_source {
  <20,-20,20>*1000
  color rgb 1
//  area_light <0,2,0>,<0,0,2> 5 5 circular orient adaptive 1
}


