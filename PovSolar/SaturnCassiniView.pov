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
#include "CassiniEleJupSat.inc"
#include "CassiniSatCentVec.inc"
#if(Time<=2453170.5)
  //Use the sun-centered osculating elements
  #declare I=1;
  PrintDate("Time: ",Time)
//  PrintDate("Epoch:",CassiniEle[I][0])
  #while((Time>CassiniEle[I][0]))
    #declare I=I+1;
//    PrintDate("Time: ",Time)
//    PrintDate("Epoch:",CassiniEle[I][0])
  #end
  PrintDate("Before Epoch: ",CassiniEle[I-1][0])
  #declare CasPos1=PosInSpace(
     CassiniEle[I-1][ 0],    //Epoch, JDCT
     CassiniEle[I-1][10],    //Semimajor Axis, km
     CassiniEle[I-1][ 1],    //Eccentricity
     CassiniEle[I-1][ 3],    //Inclination, deg
     CassiniEle[I-1][ 4],    //Longitude of Ascending Node, deg
     CassiniEle[I-1][ 5],    //Argument of Periapse, deg
     CassiniEle[I-1][ 8],    //Mean Anomaly, deg
     CassiniEle[I-1][ 7],    //Mean motion, deg/day
	 Time)-PlanetPos[Sa];
	 #declare Time1=CassiniEle[I-1][0];
  PrintDate("After Epoch: ",CassiniEle[I][0])
  #declare CasPos2=PosInSpace(
     CassiniEle[I][ 0],    //Epoch, JDCT
     CassiniEle[I][10],    //Semimajor Axis, km
     CassiniEle[I][ 1],    //Eccentricity
     CassiniEle[I][ 3],    //Inclination, deg
     CassiniEle[I][ 4],    //Longitude of Ascending Node, deg
     CassiniEle[I][ 5],    //Argument of Periapse, deg
     CassiniEle[I][ 8],       //Mean Anomaly, deg
     CassiniEle[I][ 7],   //Mean motion, deg/day
	 Time)-PlanetPos[Sa];
	 #declare Time2=CassiniEle[I][0];
#else
  //Use the Saturn body centered state vectors
  #declare I=1;
  PrintDate("Time: ",Time)
//  PrintDate("Epoch:",CassiniSatCentVec[I][0])
  #while((Time>CassiniSatCentVec[I][0]))
    #declare I=I+1;
//    PrintDate("Time: ",Time)
//    PrintDate("Epoch:",CassiniSatCentVec[I][0])
  #end
  PrintDate("Before Epoch: ",CassiniSatCentVec[I-1][0])
  #declare CasPos1=<0,0,0>;
	#declare CasVel1=<0,0,0>;
	KeplerFG(                  //R0,V0,T,Mu,R,V
    LH(<CassiniSatCentVec[I-1][1],           //Rx, km
        CassiniSatCentVec[I-1][2],           //Ry, km
        CassiniSatCentVec[I-1][3]>),         //Rz, km
    LH(<CassiniSatCentVec[I-1][4],           //Vx, km/s
        CassiniSatCentVec[I-1][5],           //Vy, km/s
        CassiniSatCentVec[I-1][6]>),         //Vz, km/s
     (Time-CassiniSatCentVec[I-1][0])*86400, //Time from epoch, s
		 37931284.5,                      //Saturn GM, km and s
	   CasPos1,CasVel1
	 )
	 #declare Time1=CassiniSatCentVec[I-1][0];
  PrintDate("After Epoch: ",CassiniSatCentVec[I][0])
  #declare CasPos2=<0,0,0>;
	#declare CasVel2=<0,0,0>;
	KeplerFG(                  //R0,V0,T,Mu,R,V
    LH(<CassiniSatCentVec[I][1],           //Rx, km
        CassiniSatCentVec[I][2],           //Ry, km
        CassiniSatCentVec[I][3]>),         //Rz, km
    LH(<CassiniSatCentVec[I][4],           //Vx, km/s
        CassiniSatCentVec[I][5],           //Vy, km/s
        CassiniSatCentVec[I][6]>),         //Vz, km/s
     (Time-CassiniSatCentVec[I][0])*86400, //Time from epoch, s
		 37931284.5,                      //Saturn GM, km and s
	   CasPos2,CasVel2
	 )
	 #declare Time2=CassiniSatCentVec[I][0];
#end	 
#declare CasPos=Linterp(Time1,CasPos1,Time2,CasPos2,Time);
PrintVector("CasPos",CasPos)
#declare CameraPos=CasPos*SystemScale;
#declare LookObj=Pa;
#declare LookAtPos=(PlanetPos[LookObj]-PlanetPos[Sa])*SystemScale;
#declare CameraAngle=0.35;
#declare SaturnPole=RotateV(y,Sa);
#declare CameraSky=SaturnPole;
//#declare CameraSky=y;
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

#declare MoonBoost=1;
#declare I=1;
#while(I<=18)
  #debug "Here\n"
  #if(PlanetIncluded[600+I])
    object {
      PlanetModel[600+I]
      scale SystemScale*MoonBoost 
      PrintVector(concat(PlanetName[600+I]," Pos: "),(PlanetPos[600+I]-PlanetPos[699]))
      translate (PlanetPos[600+I]-PlanetPos[699])*SystemScale
      #debug concat(PlanetName[600+I],"\n")  
    }
  #end
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
