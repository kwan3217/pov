#version unofficial Megapov 1.22;

text {
  ttf "verdana.ttf" 
  "Part 1 - State Vector" 0 0
  h_align_center
  rotate -y*90
  rotate -z*90
  translate <1,-0.001,3>
  Fade(<0.1,0.1,0.1,0>,ASDR(0,0.25,0.75,1,0,1,ShotClockN))
}
#local Phase=cos(pi*ShotClockS);
#local vphase=-sin(pi*ShotClockS);
#local State=<vphase*1.5,0,Phase>;
sphere {
  <-5,0,-2+Phase>,1
  Fade(<1,0,0,0>,ASDR(0,0.25,0.75,1,0,1,ShotClockN))
}
box {
  <-5.05-0.01*Phase,-0.001,10>,<-4.95+0.01*Phase,-0.01,-1+Phase>
  Fade(<1,1,0.5-Phase*0.15,0>,ASDR(0,0.25,0.75,1,0,1,ShotClockN))
}
merge {
  cylinder {
    <0,0,0>,State*0.8,0.05
  }
  cone {
    State*0.8,0.1,State,0
  }
  translate <3,0,-1>
  Fade(<1,1,1,0>,ASDR(0,0.25,0.75,1,0,1,ShotClockN))
}

merge {
  cylinder {
    <0,0,0>,z*2*0.8,0.05
  }
  cone {
    z*2*0.8,0.1,z*2,0
  }
  translate <3,0,-1>
  Fade(<0,1,0,0>,ASDR(0,0.25,0.75,1,0,1,ShotClockN))
}

merge {
  cylinder {
    <0,0,0>,x*2*0.8,0.05
  }
  cone {
    x*2*0.8,0.1,x*2,0
  }
  translate <3,0,-1>
  Fade(<0,1,0,0>,ASDR(0,0.25,0.75,1,0,1,ShotClockN))
}



#include "Scene2D_backdrop.inc"
