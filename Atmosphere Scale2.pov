#include "PovSolar/KwanMath.inc"

camera {
  up y*3/4
  right x
  direction z
  #declare Pos=Linterp(1,<0,3/4,0>,0,<1,3/4,-2>/2,clock);
  location Pos
  look_at Pos*<1,1,0>
}

plane {
  z,0
  pigment {image_map {png "Atmosphere Scale.png" interpolate 2} scale <1,3/4,1>}
  finish {ambient 1 diffuse 0}
}
