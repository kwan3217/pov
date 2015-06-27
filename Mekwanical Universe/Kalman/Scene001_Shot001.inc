#version unofficial Megapov 1.22;

#declare Slope=1/4;
cylinder {
  <-9,0,-9*Slope>,Linterp(0,<-9,0,-9*Slope>,1,<9,0,9*Slope>,ShotClockN*1.5),0.05
  pigment {color rgb <0,1,0>}
}

plane {
  -y,0
  pigment {checker color rgb 1 color rgb 0.75}
}


camera {
  right x*16/9
  sky z
  location <0,-9,0.5>
  look_at <0,0,0.5>
}

light_source {
  <20,-20,20>*1000
  color rgb 1
//  area_light <0,2,0>,<0,0,2> 5 5 circular orient adaptive 1
}


