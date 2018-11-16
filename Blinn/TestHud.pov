#include "Hud2018.inc"

#declare CamRight=image_width/image_height;
#declare CamAngle=45;

#declare HudObject=union {
  cylinder {
    0,x*CamRight/2,0.01
    pigment {color rgb <1,0,0>}
    finish {ambient 1 diffuse 0}
  }
  sphere {
    x*CamRight/2,0.02
    pigment {color rgb <1,0,0>}
    finish {ambient 1 diffuse 0}
  }
  cylinder {
    0,y/2,0.01
    pigment {color rgb <0,1,0>}
    finish {ambient 1 diffuse 0}
  }
  sphere {
    y/2,0.02
    pigment {color rgb <0,1,0>}
    finish {ambient 1 diffuse 0}
  }
  cylinder {
    0,z/2,0.01
    pigment {color rgb <0,0,1>}
    finish {ambient 1 diffuse 0}
  }
  sphere {
    z/2,0.02
    pigment {color rgb <0,0,1>}
    finish {ambient 1 diffuse 0}
  }
  text {
    ttf "arial.ttf"
    "Hud" 0 0
    scale 0.1
    translate <0.1,0.1,0>
    pigment {color rgb <1,1,0>}
    finish {ambient 1 diffuse 0}
  }
}

//TestHud(HudObject,1,CamRight,CamAngle)

#declare CamLoc=<4,5,6>;
#declare CamLook=<1,2,3>;
#declare CamSky=z;
#declare CamUp=1;
sphere {
  0,0.1
  pigment {color rgb <1,1,1>}
  finish {ambient 1 diffuse 0}
}  

camera {
  sky CamSky
  up y*CamUp
  right -x*CamRight
  angle CamAngle
  location CamLoc
  look_at CamLook
}

Hud(HudObject,CamUp,CamRight,CamAngle,CamSky,CamLoc,CamLook,1)

  

