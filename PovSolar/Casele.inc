// CasEle.inc
//Copyright © 1999 Kwan Systems
//You may use and modify this as you see fit for any non-commercial purpose
//otherwise contact me at chrisj@digiquill.com
//Chris Jeppesen - 25 Oct 1999

/*Usage*************************\
#macro CasPos(Time)
Parameters:
  Time: SMJD Time for wihch to calculate spacecraft position
Returns:
  Position vector of Casileo spacecraft at given time

#macro CasTraceOrbit(SC,Time,Thickness)
Parameters:
  Time: SMJD Time to trace orbit to
  Thickness: radius of cylinders used to construct the cylinder, in the same units as A
Usage:
  object {VoyTraceOrbit(...) texture {SomeTex}}
\*******************************/

#include "PlanetMod.inc"
#include "PlanetPos.inc"

#macro JD(Y,M,D,H,N,S)
  (JulianDate(Y,M,D,H,N,S))
#end

#declare CasLaunch=(JD(1997,10,15,9,10,0))

#declare Cas=array[7][10] {
       /* Center         Start                   Epoch                  A                    E          I                  LAN             AP        M         N  */
/*EV*/ {Su,(JD(1997,10,15,9,10,0)),(JD(1997,10,15,9,10,0)),0.842447662875739,0.199880919156033,1.22841469965581,22.056766993784,199.130680108248,152.14818790055,  -1},
/*VM*/ {Su,(JD(1998,4,26,13,4,0)),(JD(1998,4,26,13,4,0)),1.15329496485402,0.369315728096541,3.80237728531054,78.9599350139529,198.213111499071,-4.83003044469183E-03,  -1},
/*MV*/ {Su,(JD(1998,12,4,7,12,0)),(JD(1998,12,4,7,12,0)),1.12809211291209,0.399835397352446,3.37538029213663,76.7965148612566,200.096937243992,176.967243888429,  -1},
/*VE*/ {Su,(JD(1999,6,24,20,6,0)),(JD(1999,6,24,20,6,0)),1.66225838319625,0.566130036944276,1.12956792213237,144.76242117527,101.798199228198,-2.12481432293088,  -1},
/*EJ*/ {Su,(JD(1999,8,18,3,8,0)),(JD(1999,8,18,3,8,0)),4.19968019066454,0.791895866294413,0.70422685095294,144.761798670016,133.690238209006,3.63403555335038,  -1},
/*JS*/ {Su,(JD(2000,12,30,0,12,0)),(JD(2000,12,30,0,12,0)),5.31730231465299,0.740811900213695,0.777718202880026,130.383073272059,163.547339308926,43.7410809336615,  -1},
/*JS*/ {Sa,(JD(2004,7,1,0,12,0)),(JD(2004,7,1,0,12,0)),5.31730231465299,0.740811900213695,0.777718202880026,130.383073272059,163.547339308926,43.7410809336615,  -1},
       }

/*
Afterwards, use Saturn Orbit
*/


#declare Acen=0;
#declare Ast=1;
#declare Aep=2;
#declare Aa=3;
#declare Ae=4;
#declare Ai=5;
#declare Alan=6;
#declare Aap=7;
#declare Am=8;
#declare An=9;

#declare MaxCasEl=7;

#declare ElSet=0;
#while(ElSet<MaxCasEl)
  #declare Cas[ElSet][An]=360/AtoP(PlanetMass[Cas[ElSet][Acen]],Cas[ElSet][Aa]/KmtoAU(1));
  #declare ElSet=ElSet+1;
#end


#macro CasPos(Time)
  #local ElSet=MaxCasEl-1;
  #while(ElSet>0 & Time<Cas[ElSet][Ast])
    #local ElSet=ElSet-1;
  #end
  #if(Time>=Cas[0][Ast]) 
    PrintNumber("On ElSet ",ElSet)
    #if(Cas[ElSet][Acen]=Su)  
      (PosInSpace(Cas[ElSet][Aep],
                  Cas[ElSet][Aa],
                  Cas[ElSet][Ae],
                  Cas[ElSet][Ai],
                  Cas[ElSet][Alan],
                  Cas[ElSet][Aap],
                  Cas[ElSet][Am],
                  Cas[ElSet][An],
                  Time))  
    #else
      CalcPlanetPos(Time)
      (PlanetPos[Cas[ElSet][Acen]])
      #warning "At planet encounter\n"
    #end
  #else
    #warning "Not yet launched\n"
    CalcPlanetPos(Time)
    (PlanetPos[Ea])
  #end
#end

#macro CasTraceOrbit(Time,Thickness)
  #local ElSet=0;
  #local RR1=0;
  #local TA1=0;
  #local RR2=0;
  #local TA2=0;
  #while(ElSet<(MaxCasEl-1))
    #if((ElSet=MaxCasEl-1))
      #if(Time>Cas[ElSet][Ast])
        RTAInPlane(Cas[ElSet][Aep],
                   Cas[ElSet][Aa],
                   Cas[ElSet][Ae],
                   Cas[ElSet][Am],
                   Cas[ElSet][An],
                   Cas[ElSet][Ast],
                   RR1,TA1)  
        RTAInPlane(Cas[ElSet][Aep],
                   Cas[ElSet][Aa],
                   Cas[ElSet][Ae],
                   Cas[ElSet][Am],
                   Cas[ElSet][An],
                   Time,
                   RR2,TA2)  
        TraceOrbit(Cas[ElSet][Aa],
                   Cas[ElSet][Ae],
                   Cas[ElSet][Ai],
                   Cas[ElSet][Alan],
                   Cas[ElSet][Aap],       
                   Thickness,degrees(TA1),degrees(TA2))  
      #end
    #else
      #if(Time>Cas[ElSet+1][Aep])
        RTAInPlane(Cas[ElSet][Aep],
                   Cas[ElSet][Aa],
                   Cas[ElSet][Ae],
                   Cas[ElSet][Am],
                   Cas[ElSet][An],
                   Cas[ElSet][Ast],
                   RR1,TA1)  
        RTAInPlane(Cas[ElSet][Aep],
                   Cas[ElSet][Aa],
                   Cas[ElSet][Ae],
                   Cas[ElSet][Am],
                   Cas[ElSet][An],
                   Cas[ElSet+1][Aep],
                   RR2,TA2)  
        TraceOrbit(Cas[ElSet][Aa],
                   Cas[ElSet][Ae],
                   Cas[ElSet][Ai],
                   Cas[ElSet][Alan],
                   Cas[ElSet][Aap],       
                   Thickness,degrees(TA1),degrees(TA2))  
      #else 
        #if (Time>Cas[ElSet][Ast])
          RTAInPlane(Cas[ElSet][Aep],
                     Cas[ElSet][Aa],
                     Cas[ElSet][Ae],
                     Cas[ElSet][Am],
                     Cas[ElSet][An],
                     Cas[ElSet][Ast],
                     RR1,TA1)  
          RTAInPlane(Cas[ElSet][Aep],
                     Cas[ElSet][Aa],
                     Cas[ElSet][Ae],
                     Cas[ElSet][Am],
                     Cas[ElSet][An],
                     Time,
                     RR2,TA2)  
          TraceOrbit(Cas[ElSet][Aa],
                     Cas[ElSet][Ae],
                     Cas[ElSet][Ai],
                     Cas[ElSet][Alan],
                     Cas[ElSet][Aap],
                     Thickness,degrees(TA1),degrees(TA2))  
        #end
      #end
    #end
    #local ElSet=ElSet+1;
  #end
#end

