#version unofficial MegaPov 1.0;

global_settings {exposure 1.6}

#include "Calendar.inc"

#include "PlanetConst.inc"
#include "Math.inc"
#include "Rotation.inc"
#include "Kepler.inc"
#include "KeplerGaussFG.inc"

/*
#declare Y=val(date("%Y"));
#declare M=val(date("%m"));
#declare D=val(date("%d"));
#declare H=val(date("%H"))-val(date("%z"))/100;
#declare N=val(date("%M"));
#declare S=val(date("%S"))+64.184;
#declare Time=JulianDate(Y,M,D,H,N,S)+clock;
*/

#declare Time=JulianDate(2004,6,30,00,00,00);
#declare PlanetPos=array[1000];
PrintDate("Time (JDCD): ",Time)
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
#declare TimeAdd=0;
#while(TimeAdd<2)
  CasPosVel(Time+TimeAdd,CasPos,CasVel)
  PrintVector("CasPos",CasPos)
  PrintVector("CasVel",CasVel)
  sphere {
	  CasPos,1000
		scale SystemScale
		pigment {color rgb <1-TimeAdd/2,((TimeAdd-1)>=(1+12/60)/24 & (TimeAdd-1)<(2+48/60)/24),TimeAdd/2>}
		finish {ambient 1 diffuse 0}
	}
	#declare TimeAdd=TimeAdd+0.001;
#end
#declare CameraPos=y*1e6;
#declare LookAtPos=SaturnPos;
#declare SaturnPole=RotateV(y,Sa);
//#declare CameraSky=SaturnPole;
#declare CameraSky=y;
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

camera {
  sky CameraSky
  location CameraPos
  look_at LookAtPos
	scale SystemScale
}
