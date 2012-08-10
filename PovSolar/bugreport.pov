#include "colors.inc"
#include "textures.inc"
#include "shapes.inc"

#declare Voyager =intersection {
         object{
           Paraboloid_Y
           translate <0,0.95,0>
         }
         object {
           plane {y , 1.86}
         }
           pigment {White}
           finish {Dull}
           scale <3,1.5,3>

scale 0.000622
}

#declare VgrScale=1; 
#declare LightScale=1000;

light_source {
  <-20000*LightScale*VgrScale,0,-20000*LightScale*VgrScale>
  color rgb<1,1,1>*1.5
}               

camera {
  location <0,0,-0.05*VgrScale>
  look_at<0,0,0>
  angle 10
}

object {
  Voyager 
  rotate y*180 
  rotate z*90 
  rotate -y*45   
  scale VgrScale
  translate -x*0.002*VgrScale 
}

cylinder {
  <0,0.002,0>*VgrScale,<-0.001,0.002,-0.001>*VgrScale,0.0001*VgrScale
  pigment {color Red}
  finish {ambient 0.5}
}

cone {
  <-0.001, 0.002,-0.001 >*VgrScale,0.0002*VgrScale,
  <-0.0013,0.002,-0.0013>*VgrScale,0*VgrScale
  pigment {color Red}
}

object {
  Voyager
  rotate z*90 
  rotate -y*45
  scale VgrScale
  translate x*0.002*VgrScale
}
