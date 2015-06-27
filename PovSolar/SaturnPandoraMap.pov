#version unofficial MegaPov 1.0;

global_settings {exposure 1.6}

#include "Calendar.inc"

#include "PlanetConst.inc"
#include "Math.inc"
#include "Rotation.inc"
#include "Kepler.inc"
#include "KeplerGaussFG.inc"

#declare Y=val(date("%Y"));
#declare M=val(date("%m"));
#declare D=val(date("%d"));
#declare H=val(date("%H"))-val(date("%z"))/100;
#declare N=val(date("%M"));
#declare S=val(date("%S"))+64.184;
#declare Time=JulianDate(Y,M,D,H,N,S)+clock;
#declare Time=JulianDate(2004,10,11,00,00,00);
#fopen ouf "SaturnCassiniView.html" write
#write(ouf,"<html><head><title>Saturn - Cassini View - ",StringDate(Time),"</title></head><body>")
#write(ouf,"<h1>Saturn - Simulated Cassini View</h1>")
#write(ouf,"<h2>TDB Date: ",StringDate(Time),"</h2>")
#write(ouf,"<h2>TDB Julian Day Number: 24",str(Time,0,6),"</h2>") 
#write(ouf,"<img src=\"SaturnCassiniView.png\"><br>")
#write(ouf,"<a href=\"http://space.jpl.nasa.gov/cgi-bin/wspace?tbody=6&vbody=-90&month=",M,"&day=",D,"&century=20&decade=0&year=",Y-2000,"&hour=",H,"&minute=",N,"&rfov=15&fovmul=-1&bfov=15&sorbs=1\">")
#write(ouf,"JPL Space Simulator, same time</a>")
#fclose ouf
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
#declare JaDetail=99;
#declare EpDetail=99;
#declare PmDetail=99;
#declare PaDetail=99;
#declare includeAsteroids=0;
#declare IncludeMoons=0;
#declare SunLights=10;
#declare SunBright=2;
//#declare SunSide=1;

#declare SunPos=-PlanetPos[Sa]*SystemScale;
PrintVector("SaPos",PlanetPos[Sa])
PrintVector("SunPos",SunPos)
#declare CameraPos=y*1e7*SystemScale;
#declare LookObj=Sa;
#declare LookAtPos=(PlanetPos[LookObj]-PlanetPos[Sa])*SystemScale;
#declare CameraAngle=2;
#declare SaturnPole=RotateV(y,Sa);
//#declare CameraSky=SaturnPole;
#declare CameraSky=y;
PrintVector("CameraPos",CameraPos)
PrintVector("LookAtPos",LookAtPos)
PrintVector("CameraSky",CameraSky)

#include "PlanetMod.inc"

object {
  SaturnModel
  scale SystemScale
  Rotate(Sa)
}

object {
  SunModel
  scale SystemScale
  translate SunPos
}

#declare CmdLine=concat("java org.kwansystems.ephemeris.PlanetPosPOVSeries ",str(Time,0,6)," ",str(Time+1,0,6)," 101 617 PandoraPos")
#debug concat("\n",CmdLine,"\n")
#system CmdLine
#declare CmdLine=concat("java org.kwansystems.ephemeris.PlanetPosPOVSeries ",str(Time,0,6)," ",str(Time+1,0,6)," 101 699 SaturnPos")
#debug concat("\n",CmdLine,"\n")
#system CmdLine

#declare MoonBoost=100;
#declare I=0;
#while(I<dimension_size(PandoraPos,1))
  object {
    PlanetModel[617]
    scale SystemScale*MoonBoost 
    PrintVector("",(PandoraPos[I]-SaturnPos[I]))
    translate (PandoraPos[I]-SaturnPos[I])*SystemScale
    }
  #declare I=I+1;
#end

camera {
  up y
  right x
//  sky vnormalize(SunPos-CameraPos)
 sky CameraSky
  location CameraPos
  look_at LookAtPos
  angle CameraAngle
//  angle 1
//  angle 25
}

#declare CelestialSphereRad=1e6*0.99;
#declare StarRad=CelestialSphereRad/1000;
#declare LimitMag=5;
#declare BrightMax=1;
#declare ColorSat=0.3;
#declare Gamma=0.4;
#declare J2000Ecl=1;

#include "Stars.inc"

object {Stars rotate x*EarthTilt translate CameraPos}
