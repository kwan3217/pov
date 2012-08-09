#version unofficial Megapov 1.22;

text {
  ttf "verdana.ttf" 
  "Part 1 - Random Variables" 0 0
  h_align_center
  rotate -y*90
  rotate -z*90
  translate <0,-0.001,3>
  Fade(<0.1,0.1,0.1,0>,ASDR(0,0.25,0.75,1,0,1,ShotClockN))
}
cylinder {
  <0,-0.001,-1>,<0,-0.1,-1>,2
  Fade(<1,1,1,0>,ASDR(0,0.25,0.75,1,0,1,ShotClockN))
}
merge {
  box {
    <-1,-0.101,-0.05>,<1,-0.2,0.05>
  }
  cylinder {
    <-1,-0.101,0>,<-1,-0.2,0>,0.2
  }
  prism {
    -0.101,-0.2,4
    <1,0>,<0.9,0.2>,<1.2,0>,<0.9,-0.2>
  }
  rotate y*(1440*exp(-ShotClockN*4)+45)
  translate -z
  Fade(<0,0,1,0>,ASDR(0,0.25,0.75,1,0,1,ShotClockN))
}

#include "Scene2D_backdrop.inc"
