#version unofficial Megapov 1.22;

#local PullerX=ASDR(1,2,4,5,0,2,ShotClockS);
#local PullerY=BLinterp(2,0,4,-2,ShotClockS);
#if(ShotClockS<4)
  #local Phase=BLinterp(2,0,4,-2,ShotClockS);
#else
  #local Phase=-cos(pi*ShotClockS)*2;
#end

cylinder {
  <-150,0,0>,<-2,0,0>,0.1
  translate <PullerX,0,PullerY>
  Fade(<0,1,0,0>,ASDR(0,1,4,5,0,1,ShotClockS))
}
sphere {
  <0,0,Phase>,1
  Fade(<1,0,0,0>,BLinterp(0,0,1,1,ShotClockS))
}
box {
  <-0.05-0.01*Phase,-0.001,10>,<0.05+0.01*Phase,-0.01,Phase>
  Fade(<1,1,0.5-Phase*0.15>,BLinterp(0,0,1,1,ShotClockS))
}

#include "Scene2D_backdrop.inc"
