#version unofficial MegaPov 1.0;

global_settings {exposure 1.6}

#include "Calendar.inc"

#include "PlanetConst.inc"
#include "PlanetPos.inc"
#include "Rotation.inc"

#declare Time=JulianDate(2003,Aug,13,15,09,00)+clock;
PrintNumber("Time (SMJD): ",Time)
#declare PlanetPos=array[1000];
#system concat("java -classpath /mnt/f/codebase/java org.kwansystems.ephemeris.PlanetPosPOV ",str(Time,0,6))
PrintVector("EaPos: ",PlanetPos[399])
PrintVector("MoPos: ",PlanetPos[301])
#declare Detail=-1;
#declare SuDetail=99;
#declare MoDetail=99;
#declare MaDetail=99;
#declare includeAsteroids=0;
#declare IncludeMoons=0;
#declare SunLights=10;
#declare SunBright=2;
#declare SystemScale=0.001;

#declare Center=PlanetPos[Ea];
#declare LookAtPos=PlanetPos[Ma]-Center;
#declare Lon=radians(105);
#declare Lat=radians(40);

#include "PlanetMod.inc"
#declare CameraPos=<cos(Lon)*cos(Lat),sin(Lon)*cos(Lat),sin(Lat)>*AEarth;
#declare CameraPos=RotateV(CameraPos,Ea);
PrintVector("CameraPos",CameraPos)

//#include "KeplerGaussFG.inc"

object {
  MoonModel
  Rotate(Mo)
  translate PlanetPos[Mo]-Center
  scale SystemScale
}

object {
  MarsModel
  Rotate(Ma)
  translate PlanetPos[Ma]-Center
  scale SystemScale
}

object {
  SunModel
  translate PlanetPos[Su]-Center
  scale SystemScale
}

camera {
//  up y
//  right x

  location CameraPos*SystemScale
  look_at LookAtPos*SystemScale
  angle 0.5
}

