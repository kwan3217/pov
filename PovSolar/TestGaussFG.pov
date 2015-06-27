
#declare V1=<0,0,0>
#declare V2=<0,0,0>

#declare Detail=-1;
#declare SuDetail=99;
#declare SunLights=1;
#declare EaDetail=1;
#include "PlanetMod.inc"

#include "KeplerGaussFG.inc"
#include "PlanetPos.inc"
#include "Rotation.inc"

#declare PlanetMass[Su]= 2.9591388145744872E-04 ; //AU^3/Day^2
#declare PlanetMass[Ea]=PlanetMass[Ea]/pow(AUtoKm(1),3);

#declare T1=JulianDate(1997,Oct,15,9,45,00);
PrintDate("T1: ",T1)
#declare T2=JulianDate(1998,Apr,26,0,0,0);
PrintDate("T2: ",T2)
CalcPlanetPos(T1)
#declare VEarth=PlanetVel[Ea];
#declare R1=PlanetPos[Ea];
PrintVector("R1: ",R1)
CalcPlanetPos(T2)
#declare R2=PlanetPos[Ve];
#declare VMars=PlanetVel[Ve];
PrintVector("R2: ",R2)

GaussFG(R1,R2,T2-T1,PlanetMass[Su],2,V1,V2)
PrintVector("V1 (Au/day): ",V1)
PrintVector("VEarth:      ",VEarth)
PosVelToElePrint(R1,V1,T1,PlanetMass[Su])

#declare V1Inf=V1-VEarth;
PrintVector("V1Inf:       ",V1Inf)
#declare R0=(6378.140+195)/AUtoKm(1);
#declare V0=sqrt(pow(vlength(V1Inf),2)+2*PlanetMass[Ea]/(R0))
#declare H0=R0*V0;
#declare Energy=pow(V0,2)/2-PlanetMass[Ea]/R0;
#declare E=sqrt(1+2*Energy*pow(H0,2)/pow(PlanetMass[Ea],2));
#declare Eta=Acos(-1/E);
PrintNumber("V0:          ",V0)
PrintNumber("Departure E: ",E)
PrintNumber("Eta: ",degrees(Eta))
PrintNumber("Celestial latitude of injection vector: ",degrees(Asin(vnormalize(V1Inf).y)))
PrintNumber("Celestial longitude of injection vector: ",degrees(atan2(V1Inf.z,V1Inf.x)))
#declare V1InfRot=vrotate(V1Inf,-x*EarthTilt);
PrintNumber("Declination of injection vector: ",degrees(Asin(vnormalize(-V1InfRot).y)))
PrintNumber("Right Ascension of injection vector: ",degrees(atan2(-V1InfRot.z,-V1InfRot.x)))
PrintVector("V2 (km/sec): ",V2)
PrintVector("VMars:      ",VMars)
PrintVector("V2Inf:       ",(V2-VMars))

object {
  PlanetModel[Ea]
  scale KmtoAU(1)
  Rotate(Ea,T1)
}

object {
  PlanetModel[Su]
  scale KmtoAU(1)
  Rotate(Su,T1)
  translate -R1
}

/*
sphere {
  0,0.1
  pigment {color rgb <1,1,0> }
}

sphere {
  R2,0.02
  pigment {color rgb <0,1,1> }
}

sphere {
  R1,0.03
  pigment {color rgb <0,0,1> }
}
#declare I=T1;
#while(I<T2)
  #declare R=<0,0,0>;
  #declare V=<0,0,0>;
  KeplerFG(R1,V1,I-T1,PlanetMass[Su],R,V)
  sphere {
    R,0.01
    pigment {color rgb 1}
  }
  KeplerFG(R1,VEarth,I-T1,PlanetMass[Su],R,V)
  sphere {
    R,0.01
    pigment {color rgb <0,0,1>}
  }
  KeplerFG(R2,VMars,T2-T1+I,PlanetMass[Su],R,V)
  sphere {
    R,0.01
    pigment {color rgb <0,1,1>}
  }
  #declare I=I+1;
#end

*/


PrintVector("V1Inf:       ",V1Inf)
camera {
  location -V1Inf*2
  look_at 0
  angle 5
}

/*
camera {
  location y*2
  look_at 0
}
*/

light_source {
  <0,2,0> color rgb 1
}