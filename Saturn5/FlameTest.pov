#include "../math.inc"
#version unofficial MegaPov 0.71;

#ifndef(ArrayLen)
#include "LUT.inc"
#declare NaN=0;
#include "SIVBPos.data"
#include "SIVBGroundVel.data"
#include "SIVBAccel.data"
#end

#declare Time=clock*600;
#declare ArrayPos=int(Time*2);

#macro LocationLookAt(Location,LookAt)
  #local NY=vnormalize(LookAt-Location);
  #local NX=vnormalize(vcross(NY,-y)); // z is down in this example
  #local NZ=vcross(NX,NY);
  matrix < NX.x,NX.y,NX.z, NY.x,NY.y,NY.z, NZ.x,NZ.y,NZ.z, Location.x,Location.y,Location.z >
#end

#declare Scale=1000;

#declare Pad39ALat=28.60832;
#declare Pad39ALon=-80.60414;

#macro LLAtoXYZ(Lat,Lon,Alt)
  (Alt*<cos(radians(Lat))*cos(radians(Lon)),sin(radians(Lat)),cos(radians(Lat))*sin(radians(Lon))>)
#end

#declare LaunchSite=LLAtoXYZ(Pad39ALat,Pad39ALon,6378.150);
#declare P0=SIVBPos[ArrayPos+0];
#declare T0=int((Time+0.0)*2)/2;
#declare P1=SIVBPos[ArrayPos+1];
#declare T1=int((Time+0.5)*2)/2;
#declare P2=SIVBPos[ArrayPos+2];
#declare T2=int((Time+1.0)*2)/2;
PrintVector("P0: ",P0)
PrintVector("P1: ",P1)
PrintVector("P2: ",P2)
PrintNumber("T0: ",T0)
PrintNumber("T1: ",T1)
PrintNumber("T2: ",T2)
PrintNumber("T:  ",Time)
#declare RocketPos=Quadterp(T0,P0,T1,P1,T2,P2,Time);
#declare Alt=vlength(RocketPos)-6378.140;
PrintNumber("Alt: ",Alt)
#declare F1FlameScale=exp(Alt/7.69);
#declare F1FlameSpeed=50;
background {color rgb<0.5,0.5,1>*exp(-Alt/7.69)}


PrintVector("RocketPos: ",RocketPos)
#declare P0=SIVBGroundVel[ArrayPos+0];
#declare P1=SIVBGroundVel[ArrayPos+1];
#declare P2=SIVBGroundVel[ArrayPos+2];
#declare RocketVel=Quadterp(T0,P0,T1,P1,T2,P2,Time);
#if(vlength(SIVBAccel[ArrayPos])!=0)
#declare P0=SIVBAccel[ArrayPos+0];
#declare P1=SIVBAccel[ArrayPos+1];
#declare P2=SIVBAccel[ArrayPos+2];
#end
#declare RocketPoint=Quadterp(T0,P0,T1,P1,T2,P2,Time);
#declare LaunchSiteN=LLAtoXYZ(Pad39ALat-2/Scale,Pad39ALon+1/Scale,6378.150);
#declare CameraPos=LaunchSiteN+vnormalize(LaunchSite)/Scale*100;

#include "s5mk3.inc"

//#declare Saturn5=union {
//  if(T<154

/*
union {
  object {
    Saturn5
    scale 0.3048/Scale
    rotate y*90
//    translate -z*180*0.3048
  }
  LocationLookAt(RocketPos,RocketPos+RocketPoint)
}
*/



union {
  object {F1Flame scale 76.5 scale F1FlameScale/12*0.3048/Scale}
  object {F1Flame scale 76.5 translate x*182/F1FlameScale rotate y*45 scale F1FlameScale/12*0.3048/Scale}
  object {F1Flame scale 76.5 translate x*182/F1FlameScale rotate y*135 scale F1FlameScale/12*0.3048/Scale}
  object {F1Flame scale 76.5 translate x*182/F1FlameScale rotate y*225 scale F1FlameScale/12*0.3048/Scale}
  object {F1Flame scale 76.5 translate x*182/F1FlameScale rotate y*315 scale F1FlameScale/12*0.3048/Scale}
  //LocationLookAt(RocketPos,RocketPos+RocketPoint)
}


union {
  cylinder {
    <0,0,0>,<0,0.1,0>,0.001
  }
  cone {
    <0,0.1,0>,0.002,<0,0.12,0>,0
  }
  pigment {color rgb <0,1,0>}
  LocationLookAt(RocketPos,RocketPos+RocketVel)
}


#include "EarthShell.inc"

#declare World=union {
  union {
    object {
      LUT
      scale 0.3048/Scale
    }
    LocationLookAt (LaunchSite,LaunchSite*2)
  }
  sphere {
    0,6378.140
    texture {
      pigment {
        image_map {
          png "../EarthMap2.png"
          map_type 1
          interpolate 2
          frequency 1,1
          phase 0,0
        }
      }
      rotate -y*180.03
      //rotate y*90
    }
    EarthMapShell(0,CameraPos)
    texture {
      pigment {
        image_map {
          png "Pad39.png"
          map_type 0
          interpolate 2
          once
        }
        scale <4,3,1>
        scale 900/Scale
        rotate x*90
        rotate -y*60
        translate <-580,0,-3245>/Scale
        rotate z*(-90+Pad39ALat)
        rotate -y*(Pad39ALon)
      }
    }
  }
  rotate y*(-Time*360/86164)
}

//object {World}

camera {
  sky vnormalize(RocketPos)
  location <0,2,-5>*10/Scale //RocketPos+<0,-1,-1>*0.2
  look_at 0//RocketPos+vnormalize(RocketPoint)*0.050
  angle 35

}


light_source {
  <RocketPos.x,0,RocketPos.z>*1000000
  color rgb 1
  //rotate y*45
}


