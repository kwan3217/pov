#version unofficial MegaPov 0.71;

#ifndef(Time)
#include "Calendar.inc"

#declare Detail=-1;
#declare SuDetail=99;
#declare SaDetail=99;
#declare includeAsteroids=0;
#declare IncludeMoons=0;
#declare SystemScale=1;
#declare CasBoost=1000;
#declare CameraDist=0.05; //km
#declare SunLights=1;

#include "PlanetMod.inc"
#include "PlanetPos.inc"
#include "Rotation.inc"
#include "KeplerGaussFG.inc"

#include "CassiniVec.inc"
#include "MimasVec.inc"
#include "EnceladusVec.inc"
#include "TethysVec.inc"
#include "DioneVec.inc"
#include "RheaVec.inc"
#include "TitanVec.inc"
#include "HyperionVec.inc"
#include "IapetusVec.inc"
#include "PhoebeVec.inc"

#end
#declare Time=JulianDate(2004,Jul,0,00,00,00)+clock;
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

#macro PlotPos(Vec,T)
  #local I=0;
  #local done=false;
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
  PrintNumber("Last Element Accessed: ",I)
  PrintNumber("JDE: ",T)
  #local R=<0,0,0>;
  #local V=<0,0,0>;
//  #warning "before"
  KeplerFG(<Vec[I][1],Vec[I][2],Vec[I][3]>,<Vec[I][4],Vec[I][5],Vec[I][6]>,T-Vec[I][0],2.8315537846051E+17,R,V)
//  #warning "after"
  (R)
#end

#macro PlotPosVel(Vec,T,RR,VV)
  #local I=0;
  #local done=false;
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
  PrintNumber("Last Element Accessed: ",I)
  PrintNumber("JDE: ",T)
  #local R=<0,0,0>;
  #local V=<0,0,0>;
//  #warning "before"
  KeplerFG(<Vec[I][1],Vec[I][2],Vec[I][3]>,<Vec[I][4],Vec[I][5],Vec[I][6]>,T-Vec[I][0],2.8315537846051E+17,R,V)
//  #warning "after"
  #declare RR=R;
  #declare VV=V;
#end

object {
  SaturnModel
  scale SystemScale
  Rotate(Sa,Time)
}

object {
  SunModel
  translate AUtoKm(-PlanetPos[Sa])
  scale SystemScale
}

#warning "Here2"

#local EndTime=Time+4;
#while(Time<EndTime)
/*
sphere {
  PlotPos(MimasVec,Time),198.8
  pigment {color rgb 0.5}
  scale SystemScale
}

sphere {
  PlotPos(EnceladusVec,Time),249.1
  pigment {color rgb 1}
  scale SystemScale
}

sphere {
  PlotPos(TethysVec,Time),529.9
  pigment {color rgb 0.5}
  scale SystemScale
}

sphere {
  PlotPos(DioneVec,Time),560
  pigment {color rgb 0.5}
  scale SystemScale
}

sphere {
  PlotPos(RheaVec,Time),764
  pigment {color rgb <1,0.5,0>}
  scale SystemScale
}

sphere {
  PlotPos(TitanVec,Time),2575
  pigment {color rgb <1,0.5,0>}
  scale SystemScale
}

sphere {
  0,1
  scale <185,140,113>
  translate PlotPos(HyperionVec,Time)
  pigment {color rgb <1,0.5,0>}
  scale SystemScale
}

sphere {
  PlotPos(IapetusVec,Time),718
  pigment {color rgb <1,0.5,0>}
  scale SystemScale
}

sphere {
  0,1
  scale <115,110,105>
  translate PlotPos(HyperionVec,Time)
  pigment {color rgb <1,0.5,0>}
  scale SystemScale
}
*/
#macro LocationLookAt(Location,LookAt)
  #local NY=vnormalize(LookAt-Location);
  #local NX=vnormalize(vcross(NY,-y)); // -y is down in this example
  #local NZ=vcross(NX,NY);
  matrix < NX.x,NX.y,NX.z, NY.x,NY.y,NY.z, NZ.x,NZ.y,NZ.z, Location.x,Location.y,Location.z >
#end

#declare CasPos=<0,0,0>;
#declare CasVel=<0,0,0>;
PlotPosVel(CassiniVec,Time,CasPos,CasVel)
#macro VecToStr(V)
  concat("<",str(V.x,0,6),",",str(V.y,0,6),",",str(V.z,0,6),">")
#end
#debug concat(str(2400000+Time,0,6),",",VecToStr(CasPos),"\n")
#declare EarthPoint=vnormalize(CasPos-PlanetPos[Sa]); //its really sun-point for now. its pretty close to superior conjunction anyway

//Nominal SOI burn 2004-Jul-01 01:10 (0.048611111) - 02:40 (0.1111111111)
#if(clock<0)
  #declare CasRoll=0;
  #declare CasPoint=EarthPoint;
#else
  #if(clock<0.048611111)
    #declare CasRoll=Linterp(0,0,0.048611111,90,clock);
    #declare CasPoint=Linterp(0,EarthPoint,0.048611111,vnormalize(-CasVel),clock);
  #else
    #if(clock<0.111111111)
      #declare CasRoll=90;
      #declare CasPoint=vnormalize(-CasVel);
    #else
      #if(clock<0.15)
        #declare CasRoll=Linterp(0.111111111,90,0.15,180,clock);
        #declare CasPoint=Linterp(0.111111111,vnormalize(-CasVel),0.15,EarthPoint,clock);
      #else
        #declare CasRoll=180;
        #declare CasPoint=EarthPoint;
      #end
    #end
  #end
#end
//#declare TitanPos=PlotPos(TitanVec,Time);
//#declare CameraPos=CasPos-(vnormalize(TitanPos-CasPos)*CameraDist*CasBoost*SystemScale);

union {
  sphere {0,1000 pigment {color rgb x} finish {ambient 1}}
  LocationLookAt(CasPos*SystemScale,(CasPos+CasPoint)*SystemScale)
}

camera {
  location y*1e6*SystemScale
  look_at 0
}
#declare Time=Time+1/24;
#end