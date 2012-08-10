#declare Detail=-1;
#declare SuDetail=99;
#declare EaDetail=99;
#declare MoDetail=99;
#declare SunLights=100;
//#ifndef(T)
#include "PlanetMod.inc"
#include "PlanetPos.inc"
#include "Rotation.inc"
//#end
#declare SystemScale=1000;
#declare ObjectScale=SystemScale*1;

//background {color rgb<0,0.5,1>}

#declare T=JulianDate(2002,Jun,10,21,0,0)+clock*6/24;

CalcPlanetPos(T)

#ifndef(LookAt) 
  #declare LookAt=(PlanetPos[Mo]-PlanetPos[Ea])*0.475;
#end

#macro Planet(Num) 
  object {
    PlanetModel[Num]
    scale KmtoAU(1)*SystemScale
    Rotate(Num,T)
    translate PlanetPos[Num]*ObjectScale
  }
#end

Planet(Su)
Planet(Mo)
Planet(Ea)

camera {
  location PlanetPos[Ea]*SystemScale*0.99+z*5
  look_at (PlanetPos[Ea]+LookAt)*SystemScale
//  look_at PlanetPos[Mo]
  angle 1.2
}
