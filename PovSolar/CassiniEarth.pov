#version unofficial MegaPov 0.71;

#ifndef(Time)
#include "Calendar.inc"

#declare Detail=-1;
#declare SuDetail=99;
#declare EaDetail=99;
#declare MoDetail=99;
#declare includeAsteroids=0;
#declare IncludeMoons=0;
#declare SystemScale=1;
#declare CasBoost=1;
#declare CameraDist=0.05; //km
#declare CameraHeight=0.01; //km
#declare SunLights=1;

#include "PlanetMod.inc"
#include "PlanetPos.inc"
#include "EarthSat.inc"
#include "Rotation.inc"
#include "KeplerGaussFG.inc"

#include "CassiniEarthVec.inc"

#include "Cassini.inc"

#end
#declare TCA=JulianDate(1999,Aug,18,3,29,29);
#declare TCAMoon=JulianDate(1999,Aug,18,1,14,12);
#declare Time=TCA-12/24+clock;
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
  MoonModel
  scale SystemScale
  Rotate(Mo,Time)
  translate CalcEarthSatPos(Time)*SystemScale
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

#declare SunPoint=vnormalize(-AUtoKm(PlanetPos[Ea]));
PrintDate("Time: ",Time)
#declare Time1=JulianDate(1999,Aug,17,22,02,00);
#declare Time2=JulianDate(1999,Aug,17,22,22,00);
#declare Time3= JulianDate(1999,Aug,18,01,15,00);
#declare Time3b=JulianDate(1999,Aug,18,01,30,00);
#declare Time4= JulianDate(1999,Aug,18,01,45,00);
#declare Time4b=JulianDate(1999,Aug,18,02,00,00);
#declare Time5= JulianDate(1999,Aug,18,02,20,00);
#declare Time6b=JulianDate(1999,Aug,18,02,35,00);
#declare Time6= JulianDate(1999,Aug,18,02,50,00);

#include "Transition.inc"

#declare CasRoll=0;
#declare CasPoint=SunPoint*5000;
#declare CamPoint=<0,0,0>;
#declare CamDir=1;
#declare CamDirExp=0;
#declare CamMax=50;
#declare ShowSRULabel=0;
#declare ShowMoonLabel=0;
#declare MoonPos=(CalcEarthSatPos(Time))*SystemScale;
#declare MoonStatFade=0;
TransitionFlatBefore(CasRoll,Time1,90,Time)
Transition(CasRoll,Time1,90,Time2,180,Time)
TransitionFlatAfter(CasRoll,Time2,180,Time)

TransitionFlatBefore(ShowSRULabel,Time1,0,Time)
TransitionFlat(ShowSRULabel,Time1,Time2,1,Time)
TransitionFlatAfter(ShowSRULabel,Time2,0,Time)

TransitionFlatBefore(ShowMoonLabel,Time4,0,Time)
TransitionFlat(ShowMoonLabel,Time4,Time5,1,Time)
TransitionFlatAfter(ShowMoonLabel,Time5,0,Time)

TransitionFlatBefore(CamPoint,Time3,<0,0,0>,Time)
Transition(CamPoint,Time3,<0,0,0>,Time4,MoonPos,Time)
TransitionFlat(CamPoint,Time4,Time5,MoonPos,Time)
Transition(CamPoint,Time5,MoonPos,Time6,<0,0,0>,Time)
TransitionFlatAfter(CamPoint,Time6,<0,0,0>,Time)

TransitionFlatBefore(MoonStatFade,Time3,0,Time)
Transition(MoonStatFade,Time3,0,Time4,1,Time)
TransitionFlat(MoonStatFade,Time4,Time5,1,Time)
Transition(MoonStatFade,Time5,1,Time6,0,Time)
TransitionFlatAfter(MoonStatFade,Time6,0,Time)

TransitionFlatBefore(CamDir,Time3b,0,Time)
Transition(CamDirExp,Time3b,0,Time4b,log(CamMax),Time)
TransitionFlat(CamDirExp,Time4b,Time5,log(CamMax),Time)
Transition(CamDirExp,Time5,log(CamMax),Time6b,0,Time)
TransitionFlatAfter(CamDirExp,Time6b,0,Time)

#declare CamDir=exp(CamDirExp);

PrintVector("CasPoint: ",CasPoint)
PrintNumber("CasRoll: ",CasRoll)
PrintNumber("FlightAngle: ",90-degrees(vangle(CasPos,CasVel)))

#declare StarRad=1e6/1200/CamDir;

#include "Stars.inc"

#declare StarField=object {
  Stars
  rotate x*23.45  //Convert from equatorial to eccliptic coordinate
}

#declare CameraPos=CasPos-(vnormalize(-CasPos)*CameraDist*CasBoost*SystemScale)+CameraHeight*CasBoost*SystemScale*y;

PrintVector("min: ",min_extent(Cassini))
PrintVector("max: ",max_extent(Cassini))

union {
  object {Cassini scale <-1,1,1> scale 1/1000*CasBoost*SystemScale rotate -x*90 rotate y*CasRoll}
  LocationLookAt(CasPos*SystemScale,(CasPos+CasPoint)*SystemScale)
}

object {StarField translate CameraPos*SystemScale}

#macro Hud(Object,Location,Look_At,Sky)
  #ifdef(HudLight)
    light_source {
      Location
      color HudLight
    }
  #end
  object {
    Object
    #local NZ=vnormalize(Look_At-Location);
    #local NX=-vnormalize(vcross(NZ,Sky));
    #local NY=-vcross(NX,NZ);
    matrix < NX.x,NX.y,NX.z, NY.x,NY.y,NY.z, NZ.x,NZ.y,NZ.z, Location.x,Location.y,Location.z >
  }
#end

camera {
  location CameraPos*SystemScale
  direction z*CamDir
  look_at CamPoint*SystemScale
}

#if(ShowSRULabel | ShowMoonLabel)
Hud(
  object {
    text {
      ttf "lucon"
      #if(ShowSRULabel)
      "SRU Protection Roll"
      #else
      "Imaging the Moon"
      #end
      0,0
      align_center
      pigment {color rgb 1}
      finish {ambient 1 diffuse 0}
      scale 0.025
      no_shadow
      translate <0,0.475,CamDir>
    }
  },
  CameraPos*SystemScale,CamPoint*SystemScale,<0,1,0>
)
#end
/*
#if(MoonStatFade>0)
Hud(
  object {
    text {
      ttf "lucon"
      concat("MoonDist: ",str(vlength(CasPos-MoonPos),8,0),"km")
      0,0
      pigment {color rgb 1}
      finish {ambient MoonStatFade diffuse 0}
      scale 0.025
      no_shadow
      translate <-2/3,0.475,CamDir>
    }
  },
  CameraPos*SystemScale,CamPoint*SystemScale,<0,1,0>
)
#end
*/
Hud(
  object {
    text {
      ttf "lucon" concat("Spd: ",str(vlength(CasVel)/86400,8,3),"km/s")
      0,0
      pigment {color rgb 1}
      finish {ambient 1 diffuse 0}
      scale 0.025
      no_shadow
      translate <-2/3,-0.5,CamDir>
    }
  },
  CameraPos*SystemScale,CamPoint*SystemScale,<0,1,0>
)

Hud(
  object {
    text {
      ttf "lucon" concat("Alt: ",str(vlength(CasPos)-6378.140,8,0),"km")
      0,0
      pigment {color rgb 1}
      finish {ambient 1 diffuse 0}
      scale 0.025
      no_shadow
      translate <-2/3,-0.475,CamDir>
    }
  },
  CameraPos*SystemScale,CamPoint*SystemScale,<0,1,0>
)

Hud(
  object {
    text {
      ttf "lucon" concat("UTC: ",StringDate(Time))
      0,0
      align_right
      pigment {color rgb 1}
      finish {ambient 1 diffuse 0}
      scale 0.025
      no_shadow
      translate <2/3,-0.5,CamDir>
    }
  },
  CameraPos*SystemScale,CamPoint*SystemScale,<0,1,0>
)

Hud(
  object {
    text {
      ttf "lucon" concat("TCA: ",StringTime(Time-TCA))
      0,0
      align_right
      pigment {color rgb 1}
      finish {ambient 1 diffuse 0}
      scale 0.025
      no_shadow
      translate <2/3,-0.475,CamDir>
    }
  },
  CameraPos*SystemScale,CamPoint*SystemScale,<0,1,0>
)

