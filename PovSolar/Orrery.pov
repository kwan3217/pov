//Orrery.pov

#declare Detail=-1;
#declare JuDetail=99;
#declare IoDetail=99;
#declare EuDetail=99;
#declare GaDetail=99;
#declare CaDetail=99;
#include "planetmod.inc"
#include "planetpos.inc"
#include "Rotation.inc" 
#include "vgrele.inc"
#include "colors.inc"
                         
#declare SolarScale=1000;

#declare DeltaT=-2+clock*4
#declare Now=(Voy[V1][1][Aep])+DeltaT;                         
                         
CalcPlanetPos(Now)    

light_source {
  -PlanetPos[Ju]*SolarScale
  color 1.5
}

object {    
  PlanetModel[Ju]
  scale KmtoAU(1)*SolarScale
  Rotate(Ju,Now)
}

#declare Now=(Voy[V1][1][Aep])+DeltaT;                         
PrintDate("Now: ",Now)
                       
CalcPlanetPos(Now)    

#declare I=500;
#while(I<Ju)
  #if(PlanetIncluded[I])
    object {    
      PlanetModel[I]
      scale KmtoAU(1)*SolarScale
      Rotate(I,Now)
      translate ((PlanetPos[I]-PlanetPos[Ju])*SolarScale)
    }
  #end
  #declare I=I+1;
#end


#declare Here=((VoyPos(V1,Now))-PlanetPos[Ju])*SolarScale;
PrintVector("Here: ",Here)

camera {              
  location Here
  look_at (PlanetPos[Io]-PlanetPos[Ju])*SolarScale
}
