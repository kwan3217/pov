// solarsys.pov
//Copyright � 1999 Kwan Systems
//You may use and modify this as you see fit for any non-commercial purpose
//otherwise contact me at chrisj@digiquill.com
//Chris Jeppesen - 13 May 1999

//To duplicate Solarsys.flc, use the following parameters
//+A0.3 +KFF500 +KF14 +W640 +H480

#include "colors.inc"   
#declare Detail=-1;
#include "PlanetMod.inc"
#include "PlanetPos.inc"
#include "casele.inc"

#declare star_count = 2000;
#declare star_scale = 0.5;
#include "GALAXY.SF"

#declare Time=JulianDate(1997,Oct,15,0,0,1)+clock*PlanetEle[Ea][PlP];
#declare OrbThickness=0.005;
#declare SolarScale=1;
#declare PlanetScale=SolarScale;
#declare GG1=(CasPos(Time));
#declare Time=JulianDate(1997,Oct,15,0,0,1)+clock*PlanetEle[Ea][PlP];
CalcPlanetPos(Time)             
PrintVector("Cassini:",GG1)

#if(Time<JulianDate(1997,Oct,15,0,0,0))
  #declare GG1=(CasPos(JulianDate(1997,Oct,15,0,0,0)));
#end

#include "KwanMacs.inc"
Hud(
  text {
    ttf "verdana.ttf",
    StringDate(Time),0,0
    scale 0.02
    translate <-2/3,0.48,1>
    scale 0.01
    pigment{color White}
    finish {ambient 1}
    no_shadow
  },GG1+<5,2,0>,GG1,<0,1,0>
)

//Sun
sphere {
  PlanetPos[Su],0.1
  pigment {color <1,1,0.5>}
  finish {ambient 1}
  no_shadow
}   
light_source {
  PlanetPos[Su] color White*1.5
}

#declare PlanetMod=array[10] {
sphere {
  0,0.1
  pigment {color <1,1,0.5>}
  finish {ambient 1}
  no_shadow
}   
sphere {
  0,0.03
  pigment {color Brown}
},
sphere {
  0,0.05
  pigment {color Cyan}
},
sphere {
  0,0.05
  pigment {color Blue}
},
sphere {
  0,0.03
  pigment {color Red }
},               
sphere {
  0,0.08
  pigment {color Orange}
},               
union {
  sphere {
    0,0.07
  }
  disc {               
    0,y,0.14,0.08
    rotate -z*23
  }      
  pigment {color Yellow}
},
sphere {
  0,0.06
  pigment {color Green}
},               
sphere {
  0,0.06
  pigment {color Blue }
},               
sphere {
  0,0.02
  pigment {color Gray50 }
}               
}

#declare I=0;
#while(I<=9)
  PrintVector(concat(PlanetName[I*100+99],": "),PlanetPos[I*100+99])
  object {PlanetMod[I] translate PlanetPos[I*100+99]*SolarScale}
  #if(I!=0)
    object {
      TraceOrbit(PlanetEle[I*100+99][PlA],PlanetEle[I*100+99][PlE],PlanetEle[I*100+99][PlI],PlanetEle[I*100+99][PlLAN],PlanetEle[I*100+99][PlLP]-PlanetEle[I*100+99][PlLAN],OrbThickness,0,360)  
      texture {
        pigment {color White}
        finish {ambient 1 diffuse 0 specular 0}
      }
      no_shadow
    }        
  #end
  #declare I=I+1;
#end


#if(Time>JulianDate(1997,Oct,15,0,0,0))
  //Galileo
  sphere {
    GG1*SolarScale,0.02
    pigment {color Yellow}
    finish {ambient 1 diffuse 0 specular 0}
    no_shadow
  }               
  union {
    CasTraceOrbit(Time,OrbThickness)  
    texture {
      pigment {color Yellow}
      finish {ambient 1 diffuse 0 specular 0}
    }
    no_shadow
  } 
#end

PrintDate("Time: ",Time)