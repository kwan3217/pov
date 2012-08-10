#version unofficial MegaPov 1.0;

global_settings {exposure 1.6}

#include "Calendar.inc"

#include "PlanetConst.inc"
#include "KwanMath.inc"
#include "Rotation.inc"
#include "Kepler.inc"
#include "KeplerGaussFG.inc"
#include "Turn.inc"
#include "../Voyager/Voyager.inc"
#include "../LocLook.inc"

#declare Y=1986;
#declare M=1;
#declare D=24;
#declare H=17;
#declare N=59;
#declare S=47;
#declare Epoch=JulianDate(Y,M,D,H,N,S);
#declare Tfca=clock*3600;
PrintNumber("Tfca:  ",Tfca)
#declare Time=Epoch+Tfca/86400;

#macro HandSwap(V)
  (<V.x,V.z,V.y>)
#end

//Numbers are in horizons right-handed coordinates J2000Ecl, Planet centered
#declare SCPosEpoch=HandSwap(<-1.022119495433858E+05, -2.445498510044964E+04, -2.089186768758532E+04>);
#declare SCVelEpoch=HandSwap(< 4.152030394247489E+00, -1.754724491490462E+01,  2.198439939135284E-01>);
#declare UraMu=5793947;
#declare SCPos=<0,0,0>;
#declare SCVel=<0,0,0>;

#if(Tfca!=0)
  KeplerFG(SCPosEpoch,SCVelEpoch,Tfca,UraMu,SCPos,SCVel)
#else
	#declare SCPos=SCPosEpoch;
	#declare SCVel=SCVelEpoch;
#end

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

#declare SunPos=-PlanetPos[Ur]+PlanetPos[Su];
#declare EarthPos=-PlanetPos[Ur]+PlanetPos[Ea];
#declare MrPos=-PlanetPos[Ur]+PlanetPos[Mr];

#declare CanopusVec= < -62589.7504489981292863,-959852.7356025419430807, 234233.3219143866444938>;
#declare AlkaidVec=  <-575644.9961344071198255, 804848.7524368714075536,  30843.5426990827327245>;

#declare SkyPerpVec=vnormalize(vcross(vcross(EarthPos,y),EarthPos));
#declare CanopusPerpVec=vnormalize(vcross(vcross(EarthPos,CanopusVec),EarthPos));
#declare CanopusClock=degrees(vangle(CanopusPerpVec, SkyPerpVec));
#declare AlkaidPerpVec=vnormalize(vcross(vcross(EarthPos,AlkaidVec),EarthPos));
#declare AlkaidClock=degrees(vangle(AlkaidPerpVec, SkyPerpVec));

#macro TTa(H,M)
  ((abs(H)*3600+abs(M)*60)*sgn(H))
#end

#declare TurnTimeTableQ1=array[7]  {   -9999999,       -TTa(9,30),     +TTa(-9,05), +TTa(-8,44),     +TTa(-4,00),    +TTa(-3,15),+TTa(0.001,02)}
#declare TurnSpaceTableQ1=array[7] {AlkaidClock, CanopusClock-107,CanopusClock+127,CanopusClock,CanopusClock+115,CanopusClock-65,CanopusClock}
#declare TurnRate=0.18; //deg/sec
#declare ClockAngle=TurnS(TurnTimeTableQ1,TurnSpaceTableQ1,TurnRate,Tfca);
PrintNumber("Now:          ",clock*60)
PrintNumber("ClockAngle:   ",ClockAngle)

#declare ViewpointTimeTable=array[2] {0,2*3600};
#declare ViewpointSpaceTable=array[2] {UranusPos,MrPos}

#declare ViewpointStart=-2*60*60;
#declare ViewpointEnd=-1.5*60*60;
#declare UrRelVec=vnormalize(UranusPos-SCPos);
#declare MrRelVec=vnormalize(MrPos-SCPos);
#declare ViewpointAmount=degrees(vangle(UrRelVec,MrRelVec));
#declare ViewpointAxis=vcross(UrRelVec,MrRelVec);

PrintNumber("ViewpointAmount: ",ViewpointAmount)
#if(Tfca<ViewpointStart)
  #declare LookAtPos=UranusPos;
  #debug "At Uranus\n"
	#declare LookAtY=0.03;
#else
  #if(Tfca<ViewpointEnd)
    #debug "Turning\n"
    #declare ViewpointTurn=Linterp(ViewpointStart,0,ViewpointEnd,ViewpointAmount,Tfca);
    #declare LookAtPos=SCPos+10000*vaxis_rotate(UrRelVec,ViewpointAxis,ViewpointTurn);
  	#declare LookAtY=Linterp(ViewpointStart,0.03,ViewpointEnd,0.1,Tfca);
  #else
    #debug "At Miranda\n"
    #declare LookAtPos=MrPos;
		#declare LookAtY=0.1;
  #end
#end

PrintVector("SCPos:   ",SCPos)
PrintVector("LookAt:  ",LookAtPos)
#declare SCBoost=100;
#declare LookVec=vnormalize(vnormalize(SCPos-LookAtPos)+LookAtY*y-0.03*z)*0.06*SCBoost;
PrintVector("LookVec: ",LookVec)
#declare CameraPos=LookVec+SCPos;
//#declare CameraPos=SCPos+z*2;

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

SunFlare(SunPos,CameraPos*SystemScale,7)

#declare MoonBoost=1;
#local I=1;
#while(I<=5)
  object {PlanetModel[700+I] scale MoonBoost Rotate(700+I) translate (PlanetPos[700+I]-PlanetPos[Ur]) scale SystemScale}
	#local I=I+1;
#end	

#declare Axes=union {
  cylinder {
    0,x,0.05
    pigment {color rgb <1,0,0>}
    finish {ambient 0.5}
  }
  cylinder {
    0,y,0.05
    pigment {color rgb <0,1,0>}
    finish {ambient 0.5}
  }
  cylinder {
    0,z,0.05
    pigment {color rgb <0,0,1>}
    finish {ambient 0.5}
  }
  scale 0.05
  scale 0.001
  scale SCBoost
}

#declare VoyTransform=transform {scale SCBoost LocationLookAt(SCPos,EarthPos,y) scale SystemScale}

object {
  Voyager 
  rotate y*(180-54) //Put star tracker at +y
  rotate y*ClockAngle
  rotate -z*90 //Point HGA at +x
  transform {VoyTransform}
}
//object {Axes transform {VoyTransform}}

/*
cylinder {
  0,CanopusPerpVec*10,0.2
  pigment {color rgb <1,1,0>}
  scale 0.001
  scale SCBoost
  translate (SCPos)
  scale SystemScale
}
*/

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
#declare StarRad=CelestialSphereRad*sqrt(2)*radians(30)/2048;
#declare LimitMag=5;
#declare BrightMax=1;
#declare ColorSat=0.3;
#declare Gamma=0.4;
#declare J2000Ecl=1;

#include "Stars.inc"

object {Stars translate CameraPos*SystemScale}
