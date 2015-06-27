#version unofficial MegaPov 1.0;

global_settings {exposure 1.6}

#include "Calendar.inc"

#include "PlanetConst.inc"
#include "Math.inc"
#include "Rotation.inc"
#include "Kepler.inc"
#include "KeplerGaussFG.inc"
#include "../Voyager/voyager.inc"
#include "../LocLook.inc"

#declare Y=1986;
#declare M=1;
#declare D=24;
#declare H=17;
#declare N=59;
#declare S=47;
#declare Epoch=JulianDate(Y,M,D,H,N,S);
#declare Tfca=(clock*10-10)*3600;
#declare Time=Epoch+Tfca/86400;

//Swapped to left handed coords
#declare SCPosEpoch=<-1.022119495433858E+05, -2.089186768758532E+04, -2.445498510044964E+04>;
#declare SCVelEpoch=< 4.152030394247489E+00,  2.198439939135284E-01, -1.754724491490462E+01>;
#declare UraMu=5793950.0;
#declare SCPos=<0,0,0>;
#declare SCVel=<0,0,0>;

KeplerFG(SCPosEpoch,SCVelEpoch,Tfca,UraMu,SCPos,SCVel)

PrintDate("Time (SMJDCD): ",Time)
#declare UranusPos=<0,0,0>;
#declare PlanetPos=array[1000];
#declare CmdLine=concat("java org.kwansystems.ephemeris.PlanetPosPOV ",str(Time,0,9))
#debug CmdLine
#system CmdLine
#declare I=0;
#while(I<1000) 
  #if(defined(PlanetPos[I])) PrintVector(concat("PlanetPos[",str(I,0,0),"]: "),PlanetPos[I]) #end
  #declare I=I+1;
#end
#declare SystemScale=0.01;
#declare Detail=-1;
#declare SuDetail=99;
#declare UrDetail=99;
#declare ArDetail=99;
#declare UmDetail=99;
#declare TtDetail=99;
#declare ObDetail=99;
#declare MrDetail=99;
#declare includeAsteroids=0;
#declare IncludeMoons=0;
#declare SunLights=10;
#declare SunBright=2;
//#declare SunSide=1;

#declare SunPos=-PlanetPos[Ur];
#declare MirandaPos=PlanetPos[Mr]-PlanetPos[Ur];
#declare LookAtPos=UranusPos;
PrintVector("SCPos:   ",SCPos)
#declare SCBoost=100;
#declare LookVec=vnormalize(vnormalize(SCPos-LookAtPos)+0.03*y-0.03*z)*0.06*SCBoost;
PrintVector("LookVec: ",LookVec)
#declare CameraPos=LookVec+SCPos;
//#declare LookAtPos=MirandaPos;

#include "PlanetMod.inc"

object {
  UranusModel
  scale SystemScale
  Rotate(Ur)
}

object {
  SunModel
  translate SunPos
  scale SystemScale
}

#declare MoonBoost=1;
#declare I=701;
#while(I<=705)
  object {PlanetModel[I] scale MoonBoost Rotate(I) translate (PlanetPos[I]-PlanetPos[Ur]) scale SystemScale}
  #declare I=I+1;
#end

object {Voyager rotate y*45 rotate -z*90 scale SCBoost LocationLookAt(SCPos,SunPos,y) scale SystemScale}

camera {
  up y
  right x*4/3
//  sky vnormalize(SunPos-CameraPos)
  location CameraPos*SystemScale
  look_at LookAtPos*SystemScale
//  angle 0.35	
  angle 30
//  angle 3.169
}

#declare CelestialSphereRad=1e6*0.99;
#declare StarRad=CelestialSphereRad/2000;
#declare LimitMag=5;
#declare BrightMax=1;
#declare ColorSat=0.3;
#declare Gamma=0.4;
#declare WatchStars=array[] {1,  //Canopus,   Alpha Carinae
                             8,  //Archenar,  Alpha Eridani
			     16, //Fomalhaut, Alpha Piscis Austrini
			     38};//Alkaid,    Eta Ursae Majoris
#include "Stars.inc"

object {Stars rotate x*EarthTilt translate CameraPos}
