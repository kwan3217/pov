#version unofficial Megapov 1.22;

text {
  ttf "verdana.ttf" 
  "Kalman Filter" 0 0
  h_align_center
  rotate -y*90
  rotate -z*90
  translate <0,-0.001,1>
  Fade(<0.1,0.1,0.1,0>,ASDR(0,0.25,0.75,1,0,1,ShotClockN))
}
text {
  ttf "verdana.ttf" 
  concat(chr(169)," 2011 Kwan Heavy Industries") 0 0
  h_align_center
  scale 0.5
  rotate -y*90
  rotate -z*90
  translate <0,-0.001,-1>
  Fade(<0.1,0.1,0.1,0>,ASDR(0,0.25,0.75,1,0,1,ShotClockN))
}

#include "Scene2D_backdrop.inc"
