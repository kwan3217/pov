#version unofficial MegaPov 0.71;

#ifndef(Time)
#include "Calendar.inc"

#declare Detail=-1;
#declare SuDetail=99;
#declare EaDetail=99;
#declare includeAsteroids=0;
#declare IncludeMoons=0;
#declare SystemScale=1;
#declare CasBoost=2;
#declare CameraDist=0.025; //km
#declare SunLights=1;

#include "PlanetMod.inc"
#include "PlanetPos.inc"
#include "Rotation.inc"
#include "KeplerGaussFG.inc"

#include "CassiniDepart.inc"

#include "Cassini.inc"

#include "stars.inc"

#declare StarField=object {
  Stars
  rotate x*23.45  //Convert from equatorial to eccliptic coordinates
}

#end
#declare Time=JulianDate(1997,Oct,15,9,17,00)+clock;
#warning "Here1"
CalcPlanetPos(Time)

#macro PlotOrbit(V,T1,T2)
  #local Flat=1000;
  #local MinStep=1/1440;
  #local I=T1;
  #while((I<=T2))
    #local Step=2;
    #local Off=1e99;
    #while((Off>Flat)&(Step>MinStep))
      #local Step=Step/2;
      #local R1=PlotPos(V,I);
      #local R3=PlotPos(V,I+Step);
      #local R2=PlotPos(V,I+Step/2);
      #local Off=vlength((R1+R3)/2-R2);
    #end
    cylinder {
      R1,R3,Flat*1
      scale SystemScale
    }
    #local I=I+Step;
  #end
#end

#macro PlotPosVel(Vec,T,RR,VV)
  #local I=0;
  #local done=false;
  #local Mu=2.9755362875583355E+15;
  #if(T>=Vec[0][0])
    #while(!done)
      #if((T>=Vec[I][0]) & (T<Vec[I][7]+Vec[I][0]))
        #local done=true;
      #end
      #if(Vec[I][7]=0)
        #local done=true;
      #end
      #local I=I+1;
    #end
    #local I=I-1;
  #end
  #local R0=<Vec[I][1],Vec[I][2],Vec[I][3]>;
  #local V0=<Vec[I][4],Vec[I][5],Vec[I][6]>;
  #local R=<0,0,0>;
  #local V=<0,0,0>;
  #warning "before"
  PosVelToElePrint(R0,V0,0,Mu)
  KeplerFG(R0,V0,T-Vec[I][0],Mu,R,V)
  #warning "after"
  #declare RR=R;
  #declare VV=V;
#end

#macro PlotPos(Vec,T)
  #local R=<0,0,0>;
  #local V=<0,0,0>;
  PlotPosVel(Vec,T,R,V)
  (R);
#end


object {
  EarthModel
  scale SystemScale
  Rotate(Ea,Time)
}

object {
  SunModel
  translate AUtoKm(-PlanetPos[Ea])
  scale SystemScale
}

#macro LocationLookAt(Location,LookAt)
  #local NY=vnormalize(LookAt-Location);
  #local NX=vnormalize(vcross(NY,-y)); // z is down in this example
  #local NZ=vcross(NX,NY);
  matrix < NX.x,NX.y,NX.z, NY.x,NY.y,NY.z, NZ.x,NZ.y,NZ.z, Location.x,Location.y,Location.z >
#end

#declare CasPos=<0,0,0>;
#declare CasVel=<0,0,0>;
PlotPosVel(CassiniVec,Time,CasPos,CasVel)

#declare SunPoint=vnormalize(-AUtoKm(PlanetPos[Ea])); //its really sun-point for now. its pretty close to superior conjunction anyway
PrintDate("Time: ",Time)
#declare Time1=JulianDate(1997,Oct,15,9,22,00)
#declare Time2=JulianDate(1997,Oct,15,9,32,00)
#if(Time<Time1)
  #declare CasRoll=0;
  #declare CasPoint=vnormalize(CasVel)*5000;
#else
  #if(Time<Time2)
    #declare CasRoll=Linterp(Time1,0,Time2,90,Time);
    #declare CasPoint=Linterp(Time1,vnormalize(CasVel)*5000,Time2,SunPoint*5000,Time);
  #else
    #declare CasRoll=90;
    #declare CasPoint=SunPoint*5000;
  #end
#end

PrintVector("CasPoint: ",CasPoint)
PrintNumber("CasRoll: ",CasRoll)
PrintNumber("FlightAngle: ",90-degrees(vangle(CasPos,CasVel)))

#declare TitanPos=<0,0,0>;
#declare CameraPos=CasPos-(vnormalize(TitanPos-CasPos)*CameraDist*CasBoost*SystemScale);

PrintVector("min: ",min_extent(Cassini))
PrintVector("max: ",max_extent(Cassini))

union {
  object {Cassini scale 1/1000*CasBoost*SystemScale rotate -x*90 rotate y*CasRoll}
  LocationLookAt(CasPos*SystemScale,(CasPos+CasPoint)*SystemScale)
}

cylinder {
  CasPos+vnormalize(CasVel)*0.015,CasPos,0.0002
  pigment {color rgb <1,0,0>}
}
cone {
  CasPos+vnormalize(CasVel)*0.015,0.0004,CasPos+vnormalize(CasVel)*0.02,0
  pigment {color rgb <1,0,0>}
}

object {StarField translate CameraPos*SystemScale}

camera {
  location CameraPos*SystemScale
  //direction 2
  look_at TitanPos*SystemScale
}
