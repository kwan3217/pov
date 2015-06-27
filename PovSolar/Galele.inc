// Vgrele.inc
//Copyright © 1999 Kwan Systems
//You may use and modify this as you see fit for any non-commercial purpose
//otherwise contact me at chrisj@digiquill.com
//Chris Jeppesen - 13 May 1999

/*Usage*************************\
#macro GalPos(Time)
Parameters:
  Time: SMJD Time for wihch to calculate spacecraft position
Returns:
  Position vector of Galileo spacecraft at given time

#macro GalTraceOrbit(SC,Time,Thickness)
Parameters:
  Time: SMJD Time to trace orbit to
  Thickness: radius of cylinders used to construct the cylinder, in the same units as A
Usage:
  object {VoyTraceOrbit(...) texture {SomeTex}}
\*******************************/

#include "PlanetPos.inc"

#macro JD(Y,M,D,H,N,S)
  (JulianDate(Y,M,D,H,N,S))
#end

#declare Gal=array[7][10] {
       /* Galileo */
       /* Launch :  5 Sep 1977 */
       /* Center         Start                   Epoch                  A                      E          I        LAN      AP        M         N  */
/*EV*/ {Su, (JD(1989,10,19,01,28,37)), (JD(1989,10,19,01,28,37)), (KmtoAU(124490130.4)),  0.197725,     4.283,    25.655, -175.431,   173.504,      -1},
/*VE*/ {Su, (JD(1990,02,10,05,58,48)), (JD(1990,02,10,05,58,48)), (KmtoAU(147910815.0)),  0.292120,     3.385,    76.569,  106.326,   -14.890,      -1},
/*EG*/ {Su, (JD(1990,12,08,20,34,35)), (JD(1990,12,08,20,34,35)), (KmtoAU(237519961.4)),  0.430058,     4.547,  -103.340, -136.898,   -16.448,      -1},
/*GE*/ {Su, (JD(1991,10,29,22,36,46)), (JD(1991,10,29,22,36,46)), (KmtoAU(237560486.9)),  0.429471,     4.584,  -103.103, -137.181,   143.846,      -1},
/*EI*/ {Su, (JD(1992,12,08,15,09,25)), (JD(1992,12,08,15,09,25)), (KmtoAU(468321255.9)),  0.686152,     1.517,  -103.096, -173.802,    -0.842,      -1},
/*IJ*/ {Su, (JD(1993,08,28,16,52,05)), (JD(1993,08,28,16,52,05)), (KmtoAU(469066413.2)),  0.689222,     1.552,  -104.331, -172.744,    45.697,      -1}
/*JA*/ {Ju, (JD(1995,12,07,16,52,05)), (JD(9999,12,31,16,52,05)), (KmtoAU(469066413.2)),  0.689222,     1.552,  -104.331, -172.744,    45.697,      -1}
       }

/*
Afterwards, use Jupiter Orbit
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

#declare MaxGalEl=7;

#declare ElSet=0;
#while(ElSet<MaxGalEl)
  #declare Gal[ElSet][An]=360/AtoP(PlanetMass[Gal[ElSet][Acen]],Gal[ElSet][Aa]/KmtoAU(1));
  #declare ElSet=ElSet+1;
#end

#macro GalPos(Time)
  #local ElSet=MaxGalEl-1;
  #while(ElSet>0 & Time<Gal[ElSet][Ast])
    #local ElSet=ElSet-1;
  #end
  #if(Time>=Gal[0][Ast]) 
    PrintNumber("On ElSet ",ElSet)
    #if(Gal[ElSet][Acen]=Su)  
      (PosInSpace(Gal[ElSet][Aep],
                  Gal[ElSet][Aa],
                  Gal[ElSet][Ae],
                  Gal[ElSet][Ai],
                  Gal[ElSet][Alan],
                  Gal[ElSet][Aap],
                  Gal[ElSet][Am],
                  Gal[ElSet][An],
                  Time))  
    #else
      CalcPlanetPos(Time)
      (PlanetPos[Gal[ElSet][Acen]])
      #warning "At planet encounter\n"
    #end
  #else
    #warning "Not yet launched\n"
    CalcPlanetPos(Time)
    (PlanetPos[Ea])
  #end
#end

#macro GalTraceOrbit(Time,Thickness)
  #local ElSet=0;
  #local RR1=0;
  #local TA1=0;
  #local RR2=0;
  #local TA2=0;
  #while(ElSet<(MaxGalEl-1))
    #if((ElSet=MaxGalEl-1))
      #if(Time>Gal[ElSet][Ast])
        RTAInPlane(Gal[ElSet][Aep],
                   Gal[ElSet][Aa],
                   Gal[ElSet][Ae],
                   Gal[ElSet][Am],
                   Gal[ElSet][An],
                   Gal[ElSet][Ast],
                   RR1,TA1)  
        RTAInPlane(Gal[ElSet][Aep],
                   Gal[ElSet][Aa],
                   Gal[ElSet][Ae],
                   Gal[ElSet][Am],
                   Gal[ElSet][An],
                   Time,
                   RR2,TA2)  
        TraceOrbit(Gal[ElSet][Aa],
                   Gal[ElSet][Ae],
                   Gal[ElSet][Ai],
                   Gal[ElSet][Alan],
                   Gal[ElSet][Aap],       
                   Thickness,degrees(TA1),degrees(TA2))  
      #end
    #else
      #if(Time>Gal[ElSet+1][Aep])
        RTAInPlane(Gal[ElSet][Aep],
                   Gal[ElSet][Aa],
                   Gal[ElSet][Ae],
                   Gal[ElSet][Am],
                   Gal[ElSet][An],
                   Gal[ElSet][Ast],
                   RR1,TA1)  
        RTAInPlane(Gal[ElSet][Aep],
                   Gal[ElSet][Aa],
                   Gal[ElSet][Ae],
                   Gal[ElSet][Am],
                   Gal[ElSet][An],
                   Gal[ElSet+1][Aep],
                   RR2,TA2)  
        TraceOrbit(Gal[ElSet][Aa],
                   Gal[ElSet][Ae],
                   Gal[ElSet][Ai],
                   Gal[ElSet][Alan],
                   Gal[ElSet][Aap],       
                   Thickness,degrees(TA1),degrees(TA2))  
      #else 
        #if (Time>Gal[ElSet][Ast])
          RTAInPlane(Gal[ElSet][Aep],
                     Gal[ElSet][Aa],
                     Gal[ElSet][Ae],
                     Gal[ElSet][Am],
                     Gal[ElSet][An],
                     Gal[ElSet][Ast],
                     RR1,TA1)  
          RTAInPlane(Gal[ElSet][Aep],
                     Gal[ElSet][Aa],
                     Gal[ElSet][Ae],
                     Gal[ElSet][Am],
                     Gal[ElSet][An],
                     Time,
                     RR2,TA2)  
          TraceOrbit(Gal[ElSet][Aa],
                     Gal[ElSet][Ae],
                     Gal[ElSet][Ai],
                     Gal[ElSet][Alan],
                     Gal[ElSet][Aap],
                     Thickness,degrees(TA1),degrees(TA2))  
        #end
      #end
    #end
    #local ElSet=ElSet+1;
  #end
#end

