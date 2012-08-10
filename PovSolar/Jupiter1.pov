#version unofficial MegaPov 1.0;

global_settings {exposure 1.6}

#include "Calendar.inc"

#include "Math.inc"
#include "PlanetConst.inc"
#include "Rotation.inc"

#declare PlanetPos=array[1000]
#declare Time=JulianDate(2001,Jan,1,10,00,00)+clock;
PrintNumber("Time (SMJD): ",Time)
#system concat("java org.kwansystems.ephemeris.PlanetPosPOV ",str(Time,0,6))
#declare SystemScale=0.01;
#declare Detail=-1;
#declare SuDetail=99;
#declare JuDetail=99;
#declare IoDetail=99;
#declare EuDetail=99;
#declare GaDetail=99;
#declare CaDetail=99;
#declare includeAsteroids=0;
#declare IncludeMoons=0;
#declare SunLights=10;
#declare SunBright=2;

#declare JupiterPos=<0,0,0>;
#declare SunPos=PlanetPos[Su]-PlanetPos[Ju];
#declare LookAtPos=JupiterPos;
#declare CasPos=<2.753827632180399E+08, -9.119998774294496E+06,  6.984920061633016E+08>;
#declare CameraPos=CasPos-PlanetPos[Ju];
PrintVector("SunPos",SunPos)
PrintVector("CameraPos",CameraPos)

#include "PlanetMod.inc"

object {
  JupiterModel
  Rotate(Ju)
  translate JupiterPos
  scale SystemScale
}

object {
  SunModel
  Rotate(Su)
  translate SunPos
  scale SystemScale
}

#declare I=1;
#while(I<=4)
  object {
    PlanetModel[500+I]
    Rotate(500+I)
    translate PlanetPos[500+I]-PlanetPos[Ju]
    scale SystemScale
  }
  #declare I=I+1;
#end

camera {
  up y
  right x
  location CameraPos*SystemScale
  look_at LookAtPos*SystemScale
  angle 0.35
}

