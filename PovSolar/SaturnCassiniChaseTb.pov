#version unofficial MegaPov 1.11;
#include "Terminal.inc"


global_settings {exposure 1.6}

#include "Calendar.inc"

#include "PlanetConst.inc"
#include "Math.inc"
#include "Rotation.inc"
#include "Kepler.inc"
#include "KeplerGaussFG.inc"

#declare Time=JulianDate(2004,12,13,08,00,64.184)+clock*10/24;
//#declare Time=JulianDate(2004,10,26,08,00,64.184)+clock*10/24;
#declare PlanetPos=array[1000];
PrintDate("Time (JDCT): ",Time)
#declare SaturnPos=<0,0,0>;
#declare CmdLine=concat("java org.kwansystems.ephemeris.PlanetPosPOV ",str(Time,0,6))
#debug concat("\n",CmdLine,"\n")
#system CmdLine
#declare SystemScale=0.01;
#declare Detail=-1;
#declare SuDetail=99;
#declare SaDetail=99;
#declare MiDetail=99;
#declare EnDetail=99;
#declare TeDetail=99;
#declare DiDetail=99;
#declare RhDetail=99;
#declare TiDetail=99;
#declare HyDetail=99;
#declare IaDetail=99;
#declare includeAsteroids=0;
#declare IncludeMoons=0;
#declare SunLights=10;
#declare SunBright=2;
//#declare SunSide=1;

#declare SunPos=-PlanetPos[Sa];
#declare TitanPos=PlanetPos[Ti]-PlanetPos[Sa];
PrintVector("SaPos",PlanetPos[Sa])
PrintVector("SunPos",SunPos)
PrintVector("TitanPos",TitanPos)
#declare CasPos=<0,0,0>;
#declare CasVel=<0,0,0>;
#include "CasPosVel.inc"
CasPosVel(Time,CasPos,CasVel)
PrintVector("CasPos",CasPos)
PrintVector("CasVel",CasVel)

#declare CameraPos=CasPos;
#declare LookAtPos=TitanPos;
#declare SaturnPole=RotateV(y,Sa);
#declare CameraSky=y;
//#declare CameraSky=y;
PrintVector("CameraPos",CameraPos)
PrintVector("CameraSky",CameraSky)

#include "PlanetMod.inc"

object {
  SaturnModel
  scale SystemScale
  Rotate(Sa)
}

object {
  SunModel
	rotate(Su)
  translate SunPos
  scale SystemScale
}

#declare I=1;
#while(I<=8)
  object {
    PlanetModel[600+I]
    PrintVector(concat(PlanetName[600+I]," Pos: "),(PlanetPos[600+I]-PlanetPos[Sa]))
    translate (PlanetPos[600+I]-PlanetPos[Sa])
    scale SystemScale
    #debug concat(PlanetName[600+I],"\n")
  }
  #declare I=I+1;
#end

camera {
//  up y
//  right x
//  sky vnormalize(SunPos-CameraPos)
  sky CameraSky
  location CameraPos
  look_at LookAtPos
	scale SystemScale
//  angle 0.35	 
//  angle 1
//  angle 25
//  angle 10
//   angle 3.5
}

#declare CelestialSphereRad=1e6*0.99;
#declare StarRad=CelestialSphereRad/1000;
#declare LimitMag=5;
#declare BrightMax=1;
#declare ColorSat=0.3;
#declare Gamma=0.4;
#declare J2000Ecl=1;

#include "Stars.inc"

object {Stars rotate x*EarthTilt translate CameraPos*SystemScale}

#include "Cassini.inc"

//Since the official spacecraft unit is meter, and the
//official planet unit is km, and since both are being 
//used without scaling, either Cassini is 6km big or
//Saturn is 60km big. And I am fine with this.
object {
  Cassini
	OrientCassini2(Time)
	translate vnormalize(LookAtPos-CameraPos)*40
  translate -y*10
  scale 0.01
	translate CameraPos
  scale SystemScale
}

PrintVector("Distance: ",TitanPos-CasPos)	
