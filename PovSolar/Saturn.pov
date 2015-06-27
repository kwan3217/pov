#version unofficial MegaPov 1.0;

global_settings {exposure 1.6}

#include "Calendar.inc"

#include "PlanetConst.inc"
#include "PlanetPos.inc"
#include "Rotation.inc"

#declare Time=JulianDate(2004,Jul,0,00,00,00)+clock;
CalcPlanetPos(Time)
#declare SaturnPos=<0,0,0>;
#declare SaturnPole=<0,1,0>;
RotateV(SaturnPole,Sa,Time)
PrintVector("SaturnPole",SaturnPole)
#declare Detail=-1;
#declare SuDetail=99;
#declare SaDetail=99;
#declare includeAsteroids=0;
#declare IncludeMoons=0;
#declare SystemScale=0.001;
#declare SunLights=10;
#declare SunBright=2;
//#declare SunSide=1;

#declare SunPos=AUtoKm(-PlanetPos[Sa]*SystemScale);
PrintVector("SunPos",SunPos)
#declare CameraPos=<sin(clock*2*pi),0,-cos(clock*2*pi)>*300000*SystemScale;
PrintVector("CameraPos",CameraPos)

/*
cylinder {
  SaturnPole*100000*SystemScale,-SaturnPole*100000*SystemScale,1000*SystemScale
  pigment {color rgb <1,0,0>}
}
*/
#include "PlanetMod.inc"
#include "KeplerGaussFG.inc"

#include "CassiniTourVec.inc"
#include "MimasVec.inc"
#include "EnceladusVec.inc"
#include "TethysVec.inc"
#include "DioneVec.inc"
#include "RheaVec.inc"
#include "TitanVec.inc"
#include "HyperionVec.inc"
#include "IapetusVec.inc"
#include "PhoebeVec.inc"

object {
  SaturnModel
  scale SystemScale
  Rotate(Sa,Time)
}

object {
  SunModel
  scale SystemScale
  translate SunPos
}

#warning "Here2"

camera {
  location CameraPos
  look_at <0,0,0>
}

#declare CelestialSphereRad=1e6*0.99;
#declare StarRad=CelestialSphereRad/1000;
#declare LimitMag=5;
#declare BrightMax=1;
#declare ColorSat=0.3;
#declare Gamma=0.4;

#include "Stars.inc"

object {Stars rotate x*EarthTilt translate CameraPos}
