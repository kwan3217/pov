// Vgrele.inc
//Copyright © 1999 Kwan Systems
//You may use and modify this as you see fit for any non-commercial purpose
//otherwise contact me at chrisj@digiquill.com
//Chris Jeppesen - 13 May 1999

/*Usage*************************\
#macro VoyPos(SC,Time)
Parameters:
  SC: V1 or V2 for Voyager 1 or 2
  Time: SMJD Time for wihch to calculate spacecraft position
Returns:
  Position vector of given spacecraft at given time

#macro VoyTraceOrbit(SC,Time,Thickness)
Parameters:
  SC: V1 or V2 for Voyager 1 or 2
  Time: SMJD Time to trace orbit to
  Thickness: radius of cylinders used to construct the cylinder, in the same units as A
Usage:
  object {VoyTraceOrbit(...) texture {SomeTex}}
\*******************************/

#include "PlanetPos.inc"

#macro JD(D,M,Y,H,N,S)
  (JulianDate(Y,M,D,H,N,S))
#end
    
//All times in ET :( 
//and useful angles in degrees :) :) 
//B1950 ecliptic :( :( :(

#declare Voy=array[2][9][10] {{
       /* VOYAGER 1 */
       /* Launch :  5 Sep 1977 */
       /* Center   Start                    Epoch                                A           E           I           LAN          AP           M            N(calculated) */
/*E-J */ {Su, (JD( 5,Sep,1977,00,00,00)), (JD( 8,Sep,1977,09,08,17)),(KmtoAU(  745761000)),  0.797783,   1.032182,  -17.565509,  -0.767558,    0.304932,         -1},
/*JEnc*/ {Ju, (JD(23,Feb,1979,12,05,26)), (JD( 5,Mar,1979,12,05,26)),(KmtoAU(   -1092356)),  1.318976,   3.979134,  119.454908, -62.062795,    0.0     ,         -1},
/*J-S */ {Su, (JD(15,Mar,1979,12,05,26)), (JD(24,Apr,1979,07,33,03)),(KmtoAU( -593237000)),  2.302740,   2.481580,  112.975465,  -1.527299,   19.156329,         -1},
/*SEnc*/ {Sa, (JD( 2,Nov,1980,23,46,30)), (JD(12,Nov,1980,23,46,30)),(KmtoAU(    -166152)),  2.107561,  65.893904, -167.106611, -58.836017,    0.0     ,         -1},
/*S-  */ {Su, (JD(22,Nov,1980,23,46,30)), (JD( 1,Jan,1991,00,00,00)),(KmtoAU( -480926000)),  3.724716,  35.762854,  178.197845, -21.671355,  688.967795,         -1},
/*FLUF*/ {0,0,0,0,0,0,0,0,0,0},
/*FLUF*/ {0,0,0,0,0,0,0,0,0,0},
/*FLUF*/ {0,0,0,0,0,0,0,0,0,0},
/*FLUF*/ {0,0,0,0,0,0,0,0,0,0},
},{
       /* VOYAGER 2 */
       /* Launch : 20 Aug 1977 */
       /* Center   Start                    Epoch                                A           E           I           LAN          AP           M*/
/*E-J */ {Su, (JD(20,Aug,1977,00,00,00)), (JD(23,Aug,1977,11,29,11)),(KmtoAU(  544470000)),  0.724429,   4.825717,  -32.940520,  11.702680,   -0.888403,         -1},
/*JEnc*/ {Ju, (JD(30,Jun,1979,22,29,51)), (JD( 9,Jul,1979,22,29,51)),(KmtoAU(   -2184140)),  1.330279,   6.913454,  147.253921, -95.715216,    0.0     ,         -1},
/*J-S */ {Su, (JD(19,Jul,1979,22,29,51)), (JD(15,Sep,1979,11,07,25)),(KmtoAU(-2220315000)),  1.338264,   2.582320,  119.196938,  -9.170896,    4.798319,         -1},
/*SEnc*/ {Sa, (JD(16,Aug,1981,03,24,57)), (JD(26,Aug,1981,03,24,57)),(KmtoAU(    -332965)),  1.482601,   3.900931,   60.314852,  88.222252,    0.0     ,         -1},
/*S-U */ {Su, (JD( 5,Sep,1981,03,24,57)), (JD(17,Oct,1981,18,43,56)),(KmtoAU( -579048000)),  3.480231,   2.665128,   76.860491, 112.289600,   10.350850,         -1},
/*UEnc*/ {Ur, (JD(14,Jan,1986,17,59,47)), (JD(24,Jan,1986,17,59,47)),(KmtoAU(     -26694)),  5.014153,  11.263200,  -80.927265, -86.390059,    0.0     ,         -1},
/*U-N */ {Su, (JD( 3,Feb,1986,17,59,47)), (JD( 9,Jun,1987,00,00,00)),(KmtoAU( -448160000)),  5.806828,   2.496223, -100.376161, -46.104011,  315.018680,         -1},
/*NEnc*/ {Ne, (JD(15,Aug,1989,03,56,36)), (JD(25,Aug,1989,03,56,36)),(KmtoAU(     -24480)),  2.194523, 115.956093,  114.507068, 113.992391,    0.0     ,         -1},
/*N-  */ {Su, (JD( 4,Sep,1989,03,56,36)), (JD( 1,Jan,1991,00,00,00)),(KmtoAU( -601124000)),  6.284578,  78.810177,  101.632663, 130.043962,  342.970736,         -1},
}}  

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

#declare MaxVoyEl=array[2] {5,9}
#declare V1=0;
#declare V2=1;       


#declare SC=0;
#while(SC<2)
  #declare ElSet=0;
  #while(ElSet<MaxVoyEl[SC])
    #declare Voy[SC][ElSet][An]=360/AtoP(PlanetMass[Voy[SC][ElSet][Acen]],Voy[SC][ElSet][Aa]/KmtoAU(1));
    #declare ElSet=ElSet+1;
  #end
  #declare SC=SC+1;
#end

#macro VoyPos(SC,Time)
  #local ElSet=MaxVoyEl[SC]-1;
  #while(ElSet>0 & Time<Voy[SC][ElSet][Ast])
    #local ElSet=ElSet-1;
  #end
  #if(Time>=Voy[SC][0][Ast]) 
    PrintNumber("On ElSet ",ElSet)
    #if(Voy[SC][ElSet][Acen]=Su)  
      (PosInSpace(Voy[SC][ElSet][Aep],
                  Voy[SC][ElSet][Aa],
                  Voy[SC][ElSet][Ae],
                  Voy[SC][ElSet][Ai],
                  Voy[SC][ElSet][Alan],
                  Voy[SC][ElSet][Aap],
                  Voy[SC][ElSet][Am],
                  Voy[SC][ElSet][An],
                  Time))  
    #else
      CalcPlanetPos(Time)
      (PlanetPos[Voy[SC][ElSet][Acen]]+
       PosInSpace(Voy[SC][ElSet][Aep],
                  Voy[SC][ElSet][Aa],
                  Voy[SC][ElSet][Ae],
                  Voy[SC][ElSet][Ai],
                  Voy[SC][ElSet][Alan],
                  Voy[SC][ElSet][Aap],
                  Voy[SC][ElSet][Am],
                  Voy[SC][ElSet][An],
                  Time))  

      #warning "At planet encounter\n"
    #end
  #else
    #warning "Not yet launched\n"
    CalcPlanetPos(Time)
    (PlanetPos[Ea])
  #end
#end

#macro VoyTraceOrbit(SC,Time,Thickness)
  #local ElSet=0;
  #local RR1=0;
  #local TA1=0;
  #local RR2=0;
  #local TA2=0;
  #while(ElSet<(MaxVoyEl[SC]))
    #if((ElSet=MaxVoyEl[SC]-1))
      #if(Time>Voy[SC][ElSet][Ast])
        RTAInPlane(Voy[SC][ElSet][Aep],
                   Voy[SC][ElSet][Aa],
                   Voy[SC][ElSet][Ae],
                   Voy[SC][ElSet][Am],
                   Voy[SC][ElSet][An],
                   Voy[SC][ElSet][Ast],
                   RR1,TA1)  
        RTAInPlane(Voy[SC][ElSet][Aep],
                   Voy[SC][ElSet][Aa],
                   Voy[SC][ElSet][Ae],
                   Voy[SC][ElSet][Am],
                   Voy[SC][ElSet][An],
                   Time,
                   RR2,TA2)  
        TraceOrbit(Voy[SC][ElSet][Aa],
                   Voy[SC][ElSet][Ae],
                   Voy[SC][ElSet][Ai],
                   Voy[SC][ElSet][Alan],
                   Voy[SC][ElSet][Aap],       
                   Thickness,degrees(TA1),degrees(TA2))  
      #end
    #else
      #if(Time>Voy[SC][ElSet+1][Aep])
        RTAInPlane(Voy[SC][ElSet][Aep],
                   Voy[SC][ElSet][Aa],
                   Voy[SC][ElSet][Ae],
                   Voy[SC][ElSet][Am],
                   Voy[SC][ElSet][An],
                   Voy[SC][ElSet][Ast],
                   RR1,TA1)  
        RTAInPlane(Voy[SC][ElSet][Aep],
                   Voy[SC][ElSet][Aa],
                   Voy[SC][ElSet][Ae],
                   Voy[SC][ElSet][Am],
                   Voy[SC][ElSet][An],
                   Voy[SC][ElSet+1][Aep],
                   RR2,TA2)  
        TraceOrbit(Voy[SC][ElSet][Aa],
                   Voy[SC][ElSet][Ae],
                   Voy[SC][ElSet][Ai],
                   Voy[SC][ElSet][Alan],
                   Voy[SC][ElSet][Aap],       
                   Thickness,degrees(TA1),degrees(TA2))  
      #else 
        #if (Time>Voy[SC][ElSet][Ast])
          RTAInPlane(Voy[SC][ElSet][Aep],
                     Voy[SC][ElSet][Aa],
                     Voy[SC][ElSet][Ae],
                     Voy[SC][ElSet][Am],
                     Voy[SC][ElSet][An],
                     Voy[SC][ElSet][Ast],
                     RR1,TA1)  
          RTAInPlane(Voy[SC][ElSet][Aep],
                     Voy[SC][ElSet][Aa],
                     Voy[SC][ElSet][Ae],
                     Voy[SC][ElSet][Am],
                     Voy[SC][ElSet][An],
                     Time,
                     RR2,TA2)  
          TraceOrbit(Voy[SC][ElSet][Aa],
                     Voy[SC][ElSet][Ae],
                     Voy[SC][ElSet][Ai],
                     Voy[SC][ElSet][Alan],
                     Voy[SC][ElSet][Aap],
                     Thickness,degrees(TA1),degrees(TA2))  
        #end
      #end
    #end
    #local ElSet=ElSet+2;
  #end
#end

