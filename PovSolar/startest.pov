#declare CelestialSphereRad=1e5*0.99;
#declare StarRad=CelestialSphereRad/600;
#declare LimitMag=5;
#declare BrightMax=1;
#declare ColorSat=1;
#declare Gamma=0.4;

#include "Stars.inc"

object {Stars}

camera {
  location <0,0,0>
  look_at <cos(clock*2*pi),0,sin(clock*2*pi)>
}