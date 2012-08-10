// Vgrnew.inc
//Copyright © 1999 Kwan Systems
//You may use and modify this as you see fit for any non-commercial purpose
//otherwise contact me at chrisj@digiquill.com
//Chris Jeppesen - 13 May 1999

/*Usage*************************\
  This file extends vgrele.inc. Use this file in place of vgrele.inc
\*******************************/

#include "vgrele.inc"
#include "gauss.inc"

#declare I=0;
#while (I<(MaxVoyEl[V2]-2))
  PrintNumber("Leg: ",I)
  #declare T1=Voy[V2][I][Ast];
  #declare T3=Voy[V2][I+1][Aep];
  CalcPlanetPos(T1)               
  #if(I=0)
    #declare R1=PlanetPos[Ea];
  #else                 
    #declare R1=PlanetPos[Voy[V2][I-1][Acen]];
  #end
  CalcPlanetPos(T3)         
  #declare R3=PlanetPos[Voy[V2][I+1][Acen]];
  #declare Voy[V2][I][Aep]=T1;
  PlotOrbit(R1,R3,Voy[V2][I][Aa],Voy[V2][I][Ae],Voy[V2][I][Ai],Voy[V2][I][Alan],Voy[V2][I][Aap],Voy[V2][I][Am],Voy[V2][I][An],T3-T1)
  #declare I=I+2;
#end
