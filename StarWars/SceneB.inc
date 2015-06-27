#include "NASA Meatball.inc"
#declare NASAMeatball=object {
  AllShapes_Z
  finish {phong 0.5}
  translate <-Meatball_CENTER_X,0,-Meatball_CENTER_Y>
  scale 1/Meatball_WIDTH
  rotate -x*90
}
#include "Hampton.inc"
#declare Hampton=object {
  AllShapes_Z
  finish {phong 0.5}
  translate <-AllShapes_CENTER_X,0,-AllShapes_CENTER_Y>
  scale 1/AllShapes_WIDTH
  rotate -x*90
}
#include "NewLASPLogo.inc"
#declare NewLASPLogo=object {
  AllShapes_Z
  finish {phong 0.5}
  translate <-AllShapes_CENTER_X,0,-AllShapes_CENTER_Y>
  scale 1/AllShapes_HEIGHT
  rotate -x*90
}

object {
  NASAMeatball
  translate -x*1.2
}

object {
  Hampton
}

object {
  NewLASPLogo
  translate x*1.5
}

#declare CamLoc=<0,0,-5>;

camera {
//  orthographic
  right x*OutAspect
  location CamLoc
  look_at <0,0,0>
  angle 40
}

#include "KwanMath.inc"
#declare Swing=Linterp(11,0,20,2*pi,clock);

light_source {
  <2*cos(Swing),0.6*sin(Swing*2),-5>
  color 1
}

#if(clock<12)
  sphere {
    CamLoc,0.005
    finish {
      ambient 0 diffuse 0
    } 
    pigment {
      color rgbf<1,1,1,Linterp(11,0,12,1,clock)>
    }
    hollow
  }
#end

#if(clock>19)
  sphere {
    CamLoc,0.005
    finish {
      ambient 0 diffuse 0
    } 
    pigment {
      color rgbf<1,1,1,BLinterp(19,1,20,0,clock)>
    }
    hollow
  }
#end
