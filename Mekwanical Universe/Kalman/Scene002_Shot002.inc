#version unofficial Megapov 1.22;

#local Phase=-cos(pi*ShotClockS)*2;
#local vphase=-sin(pi*ShotClockS);
#local State=<vphase*1.5,0,Phase>;
sphere {
  <0,0,Phase>,1
  translate -x*5
  Fade(<1,0,0,0>,BLinterp(0,0,1,1,ShotClockS))
}
box {
  <-0.05-0.01*Phase,-0.001,10>,<0.05+0.01*Phase,-0.01,Phase>
  translate -x*5
  Fade(<1,1,0.5-Phase*0.15>,BLinterp(0,0,1,1,ShotClockS))
}
sphere {
  <0,0,Phase>,1
  Fade(<1,0,0,0>,BLinterp(0,1,1,0,ShotClockS))
}
box {
  <-0.05-0.01*Phase,-0.001,10>,<0.05+0.01*Phase,-0.01,Phase>
  Fade(<1,1,0.5-Phase*0.15>,BLinterp(0,1,1,0,ShotClockS))
}

#include "Scene2D_backdrop.inc"
