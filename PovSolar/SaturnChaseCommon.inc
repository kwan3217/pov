#version unofficial MegaPov 1.11;

global_settings {exposure 1.6}


#include "KwanMath.inc"
#include "Rotation.inc"
#include "Kepler.inc"
#include "KeplerGaussFG.inc"

#ifndef(Time) #declare Time=JulianDate(2004,10,26,08,00,64.184)+clock*10/24; #end
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
#declare JaDetail=99;
#declare EpDetail=99;
#declare PmDetail=99;
#declare PaDetail=99;
#declare includeAsteroids=0;
#declare IncludeMoons=0;
#declare SunLights=10;
#declare SunBright=2;

#declare SunPos=-PlanetPos[Sa];
#declare TargetPos=PlanetPos[Target]-PlanetPos[Sa];
PrintVector("SaPos",PlanetPos[Sa])
PrintVector("SunPos",SunPos)
PrintVector("TargetPos",TargetPos)
#declare CasPos=<0,0,0>;
#declare CasVel=<0,0,0>;
#declare HuyPos=<0,0,0>;
#declare HuyVel=<0,0,0>;
#include "CasPosVel.inc"
#include "HuygensSatCentVec.inc"
CasPosVel(Time,CasPos,CasVel)
TablePosVel(HuygensSatCentVec,Time,HuyPos,HuyVel)
PrintVector("CasPos",CasPos)
PrintVector("CasVel",CasVel)

#declare CameraPos=CasPos;
#declare LookAtPos=TargetPos;
#declare SaturnPole=RotateV(y,Sa);
#ifdef(CameraSkyMode)
  #switch(CameraSkyMode)
    #case(0)  //J2000
	    #declare CameraSky=y;
  	#case(1)  //Saturn Pole
	    #declare CameraSky=SaturnPole;
  	#case(2)  //Target Pole
	    #declare CameraSky=RotateV(y,Target);
  #end
#end
#ifndef(CameraSky) #declare CameraSky=y; #end
//#ifndef(CameraAngle) #declare CameraAngle=degrees(atan2(2,3)*2);
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
#while(I<=18)
  #if(PlanetIncluded[600+I])
    object {
      PlanetModel[600+I]
      Rotate(600+I)
      PrintVector(concat(PlanetName[600+I]," Pos: "),(PlanetPos[600+I]-PlanetPos[Sa]))
      translate (PlanetPos[600+I]-PlanetPos[Sa])
      scale SystemScale
      #debug concat(PlanetName[600+I],"\n")
    }
  #else
	  #debug "No model\n"
  #end
  #declare I=I+1;
#end

camera {
//  up y
//  right x
//  sky vnormalize(SunPos-CameraPos)
  sky CameraSky
  location CameraPos
  look_at LookAtPos
#ifdef (CameraAngle)	angle CameraAngle #end
	scale SystemScale
}

#ifdef(UseStars)

#declare CelestialSphereRad=1e6*0.99;
#declare StarRad=CelestialSphereRad/1000*CameraAngle/degrees(atan(4/3));
#declare LimitMag=5;
#declare BrightMax=1;
#declare ColorSat=0.3;
#declare Gamma=0.4;
#declare J2000Ecl=1;

#include "Stars.inc"

object {Stars rotate x*EarthTilt translate CameraPos*SystemScale}
#end

#ifdef(UseScModel)
#include "Cassini.inc"

//Since the official spacecraft unit is meter, and the
//official planet unit is km, and since both are being 
//used without scaling, either Cassini is 6km big or
//Saturn is 60km big. And I am fine with this.
object {
  Cassini
	OrientCassini2(Time)
	translate vnormalize(LookAtPos-CameraPos)*ChaseDistance
  translate ChaseOffset
  scale ChaseScale
	translate CameraPos
  scale SystemScale
}

#end

#ifdef(UseHuygens)
  PrintVector("Distance: ",HuyPos-CasPos)	
  sphere {
	  0,100
		translate HuyPos
    scale SystemScale
		pigment {color rgb <1,0,0>}
	}
#end
