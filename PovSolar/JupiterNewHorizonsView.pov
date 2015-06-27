#version unofficial MegaPov 1.0;

global_settings {exposure 1.6}

#include "Calendar.inc"

#include "PlanetConst.inc"
#include "Math.inc"
#include "Rotation.inc"
#include "Kepler.inc"
#include "KeplerGaussFG.inc"
#include "Turn.inc"
#include "../Voyager/Voyager.inc"
#include "../LocLook.inc"

#declare Y=1989;
#declare M=8;
#declare D=25;
#declare H=03;
#declare N=56;
#declare S=36;
#declare Epoch=JulianDate(Y,M,D,H,N,S);
#declare Tfca=clock*3600;
PrintNumber("Tfca:  ",Tfca)
#declare Time=Epoch+Tfca/86400;

#macro HandSwap(V)
  (<V.x,V.z,V.y>)
#end

//Numbers are in horizons right-handed coordinates J2000Ecl, Planet centered
#declare SCPosEpoch=HandSwap(< 1.563938960224927E+04, -5.772175375494156E+03,  2.401745818023366E+04>);
#declare SCVelEpoch=HandSwap(< 6.234806562511218E+00, -2.466038391770538E+01, -9.992359170247795E+00>);
#declare NepMu=6836534.87889192492;
#declare SCPos=<0,0,0>;
#declare SCVel=<0,0,0>;
#declare TrVel2=<0,0,0>;
#declare TrPos2=<0,0,0>;

KeplerFG(SCPosEpoch,SCVelEpoch,Tfca,NepMu,SCPos,SCVel)

PrintDate("Time (SMJDCD): ",Time)
#declare NeptunePos=<0,0,0>;
#declare PlanetPos=array[1000];
#declare CmdLine=concat("java org.kwansystems.pov.PlanetPosPOV ",str(Time,0,9))
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
#declare NeDetail=99;
#declare TrDetail=99;
#declare NrDetail=99;
#declare NaDetail=99;
#declare ThDetail=99;
#declare DsDetail=99;
#declare GlDetail=99;
#declare LaDetail=99;
#declare PrDetail=99;
#declare includeAsteroids=0;
#declare IncludeMoons=0;
#declare SunLights=10;
#declare SunBright=2;
//#declare SunSide=1;

#declare SunPos=-PlanetPos[Ne]+PlanetPos[Su];
#declare EarthPos=-PlanetPos[Ne]+PlanetPos[Ea];
#declare TrPos=-PlanetPos[Ne]+PlanetPos[Tr];

#declare CanopusVec= < -62589.7504489981292863,-959852.7356025419430807, 234233.3219143866444938>;
#declare AlkaidVec=  <-575644.9961344071198255, 804848.7524368714075536,  30843.5426990827327245>;

#declare SkyPerpVec=vnormalize(vcross(vcross(EarthPos,y),EarthPos));
#declare CanopusPerpVec=vnormalize(vcross(vcross(EarthPos,CanopusVec),EarthPos));
#declare CanopusClock=degrees(vangle(CanopusPerpVec, SkyPerpVec));
#declare AlkaidPerpVec=vnormalize(vcross(vcross(EarthPos,AlkaidVec),EarthPos));
#declare AlkaidClock=degrees(vangle(AlkaidPerpVec, SkyPerpVec));

#declare TurnTimeTable1=array[3]  {-9999999,-56*60,110*60}
#declare TurnSpaceTable1=array[3] {CanopusClock, CanopusClock+61,AlkaidClock}
#declare TurnRate=0.18; //deg/sec
#declare ClockAngle=TurnS(TurnTimeTable1,TurnSpaceTable1,TurnRate,Tfca);
PrintNumber("Now:          ",clock*60)
PrintNumber("ClockAngle:   ",ClockAngle)

#declare ViewpointTimeTable=array[2] {0,2*3600};
#declare ViewpointSpaceTable=array[2] {NeptunePos,TrPos}

#declare ViewpointStart=3*60*60;
#declare ViewpointEnd=3.5*60*60;
#declare NeRelVec=vnormalize(NeptunePos-SCPos);
#declare TrRelVec=vnormalize(TrPos-SCPos);
#declare ViewpointAmount=degrees(vangle(NeRelVec,TrRelVec));
#declare ViewpointAxis=vcross(NeRelVec,TrRelVec);

PrintNumber("ViewpointAmount: ",ViewpointAmount)
#if(Tfca<ViewpointStart)
  #declare LookAtPos=NeptunePos;
  #debug "At Neptune\n"
#else
  #if(Tfca<ViewpointEnd)
    #debug "Turning\n"
    #declare ViewpointTurn=Linterp(ViewpointStart,0,ViewpointEnd,ViewpointAmount,Tfca);
    #declare LookAtPos=SCPos+10000*vaxis_rotate(NeRelVec,ViewpointAxis,ViewpointTurn);
  #else
    #debug "At Triton\n"
    #declare LookAtPos=TrPos;
  #end
#end

//#declare LookAtPos=TrPos;
//#declare LookAtPos=SCPos;
PrintVector("SCPos:   ",SCPos)
PrintVector("LookAt:  ",LookAtPos)
#declare SCBoost=100;
#declare LookVec=vnormalize(vnormalize(SCPos-LookAtPos)+0.03*y-0.03*z)*0.06*SCBoost;
PrintVector("LookVec: ",LookVec)
#declare CameraPos=LookVec+SCPos;
//#declare CameraPos=SCPos+z*2;

#include "PlanetMod.inc"

object {
  NeptuneModel
  scale SystemScale
  Rotate(Ne)
}

object {
  SunModel
  translate SunPos
  scale SystemScale
}

SunFlare(SunPos,CameraPos*SystemScale,5)

#declare TrModel=union {
  object {PlanetModel[Tr]}
//	object {Cage scale ATriton}
}

#declare MoonBoost=1;
object {TrModel scale MoonBoost Rotate(Tr) translate (PlanetPos[Tr]-PlanetPos[Ne]) scale SystemScale}
object {TrModel scale MoonBoost Rotate(Tr) translate (PlanetPos[811]-PlanetPos[Ne]) scale SystemScale}
object {PlanetModel[Nr] scale MoonBoost Rotate(Nr) translate (PlanetPos[Nr]-PlanetPos[Ne]) scale SystemScale}
object {PlanetModel[Na] scale MoonBoost Rotate(Na) translate (PlanetPos[Na]-PlanetPos[Ne]) scale SystemScale}
object {PlanetModel[Th] scale MoonBoost Rotate(Th) translate (PlanetPos[Th]-PlanetPos[Ne]) scale SystemScale}
object {PlanetModel[Ds] scale MoonBoost Rotate(Ds) translate (PlanetPos[Ds]-PlanetPos[Ne]) scale SystemScale}
object {PlanetModel[Gl] scale MoonBoost Rotate(Gl) translate (PlanetPos[Gl]-PlanetPos[Ne]) scale SystemScale}
object {PlanetModel[La] scale MoonBoost Rotate(La) translate (PlanetPos[La]-PlanetPos[Ne]) scale SystemScale}
object {PlanetModel[Pr] scale MoonBoost Rotate(Pr) translate (PlanetPos[Pr]-PlanetPos[Ne]) scale SystemScale}

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
#declare StarRad=CelestialSphereRad*sqrt(2)*radians(30)/1024;
#declare LimitMag=5;
#declare BrightMax=1;
#declare ColorSat=0.3;
#declare Gamma=0.4;
#declare J2000Ecl=1;

#include "Stars.inc"

object {Stars translate CameraPos*SystemScale}
