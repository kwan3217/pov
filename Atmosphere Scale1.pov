#include "PovSolar/KwanMath.inc"

camera {
  up y*3/4
  right x
  direction z
  #declare SegLength=2/3;
  #declare Close=0.055;
  #declare Dist=BLinterp(0,Close,SegLength,Close*1.5,clock);
  #if(clock<SegLength)
    #declare Pos=Linterp(0,<1,3/4,-2>*Dist,SegLength,<1*Dist,3/4*(1-Dist),-2*(Dist)>,clock);
  #else
    #declare Pos=Linterp(SegLength,<1*Dist,3/4*(1-Dist),-2*(Dist)>,1,<1/2,3/8,-1>,clock);
  #end  
  location Pos
  look_at Pos*<1,1,0>
}

plane {
  z,0
  pigment {image_map {png "Atmosphere Scale.png" interpolate 2} scale <1,3/4,1>}
  finish {ambient 1 diffuse 0}
}
plane {
  z,0.00001
  pigment {image_map {png "rect3421.png" interpolate 2} scale <1,3/4,1>}
  finish {ambient 1 diffuse 0}
}
