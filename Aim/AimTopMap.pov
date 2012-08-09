#declare Deploy=1;

#include "LocLook.inc"
#include "Math.inc"
#include "AimAttCommon.inc"
#include "EarthMod.inc"

#declare Look=y*(Re+Alt);
#declare CamLoc=Look+y*Re*0.5;
#declare Angle=degrees(atan2(4/3,1));

#declare Detail=-1;
#declare SuDetail=99;
#declare SunLights=1;

#include "PlanetMod.inc"

object {
  SunModel
  translate SunPoint
}

camera {
  location CamLoc
  look_at Look
  sky y
}

global_settings {max_trace_level 20}

light_source {
  CamLoc
  color rgb 0
}

EarthMod()
