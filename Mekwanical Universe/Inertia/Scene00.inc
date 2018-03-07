//#version unofficial Megapov 1.22;
#include "Actors.inc"

#local ShotTime=array[3] {3,15,15}

CalcShotTime(ShotTime)

#switch(Shot)
  #case(0) //Title card
    union {
      Text("verdana.ttf","Moment of Inertia",0,Center)
      translate <0,-0.001,1>
      Fade(<1,1,1,0>,ASDR(0,0.25,0.75,1,0,1,ShotClockN))
    }
    #break
#end

Frame(ShotClockN,1)

#local CameraPanAngle=Linterp(0,-60,1,-120,ShotClockN);
#local CameraR=9;
#local CameraHeight=Linterp(0,5,1,4,ShotClockN);

camera {
  up y
  right -x*16/9
  sky z
  location <cos(radians(CameraPanAngle))*CameraR,sin(radians(CameraPanAngle))*CameraR,CameraHeight>
  look_at <0,0,0>
}

light_source {
  <20,-20,20>*1000
  color rgb 1
}


