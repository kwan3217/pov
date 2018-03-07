//#version unofficial Megapov 1.22;
#include "Actors.inc"

#local ShotTime=array[2] {3,15}

CalcShotTime(ShotTime)

#switch(Shot)
  #case(0) //Title card
    union {
      Text("verdana.ttf","Moment of Inertia",0,Center)
      translate <0,-0.001,1>
      Fade(<1,1,1,0>,ASDR(0,0.25,0.75,1,0,1,ShotClockN))
    }
    Frame(ShotClockN,1)
    #break
  #case(1)
    #declare R0=<1,2,3>;
    #declare V=<-1,1,1>;
    #declare T=Linterp(0,-3,1,3,ShotClockN);
    #declare F=ASDR(0,0.1,0.9,1,0,1,ShotClockN);
    Particle(R0+V*T,V,0.2, 
      <1,1,0>, //RColor
      <0,1,1>, //VColor
      <1,0,1>, //LColor
      <1,0,0>, //MColor
      <1,0,1>, //PColor
      F,F,F,F,F*0.3)
    Frame(1,1)
    #break
#end


#local CameraPanAngle=Linterp(0,-60,1,-120,SceneClockN);
#local CameraR=9;
#local CameraHeight=Linterp(0,5,1,4,SceneClockN);

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


