// PlanetPos.inc
//Copyright © 2000 Kwan Systems
//You may use and modify this as you see fit for any non-commercial purpose
//otherwise contact me at chrisj@digiquill.com
//Chris Jeppesen - 3 Apr 2000

/*Usage*************************\
#macro CalcPlanetPos(Time)
Parameters:
  Time: SMJD Time at which to calculate planetary positions
Produces:
  PlanetPos[]: Array[0..999] of solar system barycentric position vectors un units of AU.
  PlanetVel[]: Array[0..999] of velocity vectors.
\*******************************/

#include "Kepler.inc"
#include "Calendar.inc"
#warning "In PlanetPos.inc\n\n"    

#declare EarthTilt=23.45;   

#declare PlanetMass=array[1000]          //Numbers are in units of G*M=km^3/s^2 
#declare KgtoGM1=1.26686537e8/1.8986e27; //Final array is in units of G*M=km^3/day^2, calcualted from Jupiter mass and GM as given on Horizons
#declare GM1toGM2=86400*86400;           //GM1 is in units of G*M=km^3/sec^2, GM2 is in units of G*M=km^3/day^2
#declare PlanetMass[Su]=1.3271243994e11*GM1toGM2;
#declare PlanetMass[Me]=2.203209e4*GM1toGM2;
#declare PlanetMass[Ve]=3.2485863e5*GM1toGM2;
#declare PlanetMass[Ea]=3.98600440e5*GM1toGM2;
#declare PlanetMass[Ma]=4.28283e4*GM1toGM2;
#declare PlanetMass[Ju]=1.26686537e8*GM1toGM2;
#declare PlanetMass[Sa]=3.7931187e7*GM1toGM2;
#declare PlanetMass[Ur]=5.793947e6*GM1toGM2;
#declare PlanetMass[Ne]=6.835107e6*GM1toGM2;
#declare PlanetMass[Pl]=9.47e2*GM1toGM2;
#declare PlanetMass[Mo]=4.9027990412911e3*GM1toGM2;
#declare PlanetMass[Io]=8.933e22*KgtoGM1*GM1toGM2;
#declare PlanetMass[Eu]=4.797e22*KgtoGM1*GM1toGM2;
#declare PlanetMass[Ga]=8.933e22*KgtoGM1*GM1toGM2;
#declare PlanetMass[Ca]=8.933e22*KgtoGM1*GM1toGM2;

#declare PlanetExists=array[1000]
#declare I=0;
#while(I<1000)
  #declare PlanetExists[I]=0;
  #declare I=I+1;
#end
#declare PlanetExists[Su]=1;
  #declare PlanetExists[Er]=1;
  #declare PlanetExists[Id]=1;
  #declare PlanetExists[Gs]=1;
#declare PlanetExists[Me]=1;
#declare PlanetExists[Ve]=1;
#declare PlanetExists[Ea]=1;
  #declare PlanetExists[Mo]=1;
#declare PlanetExists[Ma]=1;
  #declare PlanetExists[Ph]=1;
  #declare PlanetExists[De]=1;
#declare PlanetExists[Ju]=1;
  #declare PlanetExists[Io]=1;
  #declare PlanetExists[Eu]=1;
  #declare PlanetExists[Ga]=1;
  #declare PlanetExists[Ca]=1;
#declare PlanetExists[Sa]=1;
#declare PlanetExists[Ur]=1;
#declare PlanetExists[Ne]=1;
#declare PlanetExists[Pl]=1;

//(epoch = J2000.0 = 2000 January 1 12:00:00UT = SMJD 51545.0)
#declare PlanetEpoch  = JulianDate(2000,Jan,1,12,0,0);  //epoch of all these elements 

#declare PlanetEle=array[1000][14] 

#declare PlA=0;
#declare PlE=1;
#declare PlI=2;
#declare PlLAN=3;
#declare PlLP=4; 
#declare PlL=5;  
#declare PlP=6;
#declare PlN=7;
#declare PldA=8;
#declare PldE=9;
#declare PldI=10;
#declare PldLAN=11;
#declare PldLP=12;
#declare PldL=13;

#declare PlanetEle[Su][PlA]= 0.0       ;
#declare PlanetEle[Su][PlE]=0.0       ;
#declare PlanetEle[Su][PlI]= 0.0    ;
#declare PlanetEle[Su][PlLAN]=  0.0    ;
#declare PlanetEle[Su][PlLP]=  0.0    ;
#declare PlanetEle[Su][PlL]=  0.0    ;
#declare PlanetEle[Me][PlA]= 0.38709893;
#declare PlanetEle[Me][PlE]=0.20563069;
#declare PlanetEle[Me][PlI]= 7.00487;
#declare PlanetEle[Me][PlLAN]= 48.33167;
#declare PlanetEle[Me][PlLP]= 77.45645;
#declare PlanetEle[Me][PlL]=252.25084;
#declare PlanetEle[Ve][PlA]= 0.72333199;
#declare PlanetEle[Ve][PlE]=0.00677323;
#declare PlanetEle[Ve][PlI]= 3.39471;
#declare PlanetEle[Ve][PlLAN]= 76.68069;
#declare PlanetEle[Ve][PlLP]=131.53298;
#declare PlanetEle[Ve][PlL]=181.97973;
#declare PlanetEle[Ea][PlA]= 1.00000011;
#declare PlanetEle[Ea][PlE]=0.01671022;
#declare PlanetEle[Ea][PlI]= 0.00005;
#declare PlanetEle[Ea][PlLAN]=-11.26064;
#declare PlanetEle[Ea][PlLP]=102.94719;
#declare PlanetEle[Ea][PlL]=100.46435;
#declare PlanetEle[Ma][PlA]= 1.52366231;
#declare PlanetEle[Ma][PlE]=0.09341233;
#declare PlanetEle[Ma][PlI]= 1.85061;
#declare PlanetEle[Ma][PlLAN]= 49.57854;
#declare PlanetEle[Ma][PlLP]=336.04084;
#declare PlanetEle[Ma][PlL]=355.45332;
#declare PlanetEle[Ju][PlA]= 5.20336301;
#declare PlanetEle[Ju][PlE]=0.04839266;
#declare PlanetEle[Ju][PlI]= 1.30530;
#declare PlanetEle[Ju][PlLAN]=100.55615;
#declare PlanetEle[Ju][PlLP]= 14.75385;
#declare PlanetEle[Ju][PlL]= 34.40438;
#declare PlanetEle[Sa][PlA]= 9.53707032;
#declare PlanetEle[Sa][PlE]=0.05415060;
#declare PlanetEle[Sa][PlI]= 2.48446;
#declare PlanetEle[Sa][PlLAN]=113.71504;
#declare PlanetEle[Sa][PlLP]= 92.43194;
#declare PlanetEle[Sa][PlL]= 49.94432;
#declare PlanetEle[Ur][PlA]=19.19126393;
#declare PlanetEle[Ur][PlE]=0.04716771;
#declare PlanetEle[Ur][PlI]= 0.76986;
#declare PlanetEle[Ur][PlLAN]= 74.22988;
#declare PlanetEle[Ur][PlLP]=170.96424;
#declare PlanetEle[Ur][PlL]=313.23218;
#declare PlanetEle[Ne][PlA]=30.06896348;
#declare PlanetEle[Ne][PlE]=0.00858587;
#declare PlanetEle[Ne][PlI]= 1.76917;
#declare PlanetEle[Ne][PlLAN]=131.72169;
#declare PlanetEle[Ne][PlLP]= 44.97135;
#declare PlanetEle[Ne][PlL]=304.88003;
#declare PlanetEle[Pl][PlA]=39.48168677;
#declare PlanetEle[Pl][PlE]=0.24880766;
#declare PlanetEle[Pl][PlI]=17.14175;
#declare PlanetEle[Pl][PlLAN]=110.30347;
#declare PlanetEle[Pl][PlLP]=224.06676;
#declare PlanetEle[Pl][PlL]=238.92881;

#declare PlanetEle[Su][PldA]=0.0;       
#declare PlanetEle[Su][PldE]=0.0;       
#declare PlanetEle[Su][PldI]=0.0;
#declare PlanetEle[Su][PldLAN]=0.0; 
#declare PlanetEle[Su][PldLP]=0.0;
#declare PlanetEle[Su][PldL]=0.0; 
#declare PlanetEle[Me][PldA]=0.00000066;       
#declare PlanetEle[Me][PldE]=0.00002527;       
#declare PlanetEle[Me][PldI]=-23.51;
#declare PlanetEle[Me][PldLAN]=-446.30; 
#declare PlanetEle[Me][PldLP]=573.57;
#declare PlanetEle[Me][PldL]=538101628.29;
#declare PlanetEle[Ve][PldA]= 0.00000092;
#declare PlanetEle[Ve][PldE]=-0.00004938;
#declare PlanetEle[Ve][PldI]=  -2.86;
#declare PlanetEle[Ve][PldLAN]=   -996.89;
#declare PlanetEle[Ve][PldLP]=   -108.80;
#declare PlanetEle[Ve][PldL]=   210664136.06 ;
#declare PlanetEle[Ea][PldA]=-0.00000005;
#declare PlanetEle[Ea][PldE]=-0.00003804;
#declare PlanetEle[Ea][PldI]= -46.94;
#declare PlanetEle[Ea][PldLAN]= -18228.25;
#declare PlanetEle[Ea][PldLP]=   1198.28;
#declare PlanetEle[Ea][PldL]=   129597740.63 ;
#declare PlanetEle[Ma][PldA]=-0.00007221;
#declare PlanetEle[Ma][PldE]= 0.00011902;
#declare PlanetEle[Ma][PldI]= -25.47;
#declare PlanetEle[Ma][PldLAN]=  -1020.19;
#declare PlanetEle[Ma][PldLP]=   1560.78;
#declare PlanetEle[Ma][PldL]=    68905103.78 ;
#declare PlanetEle[Ju][PldA]= 0.00060737;
#declare PlanetEle[Ju][PldE]=-0.00012880;
#declare PlanetEle[Ju][PldI]=  -4.15;
#declare PlanetEle[Ju][PldLAN]=   1217.17;
#declare PlanetEle[Ju][PldLP]=    839.93;
#declare PlanetEle[Ju][PldL]=    10925078.35 ;
#declare PlanetEle[Sa][PldA]=-0.00301530;
#declare PlanetEle[Sa][PldE]=-0.00036762;
#declare PlanetEle[Sa][PldI]=   6.11;
#declare PlanetEle[Sa][PldLAN]=  -1591.05;
#declare PlanetEle[Sa][PldLP]=  -1948.89;
#declare PlanetEle[Sa][PldL]=     4401052.95 ;
#declare PlanetEle[Ur][PldA]= 0.00152025;
#declare PlanetEle[Ur][PldE]=-0.00019150;
#declare PlanetEle[Ur][PldI]=  -2.09;
#declare PlanetEle[Ur][PldLAN]=  -1681.40;
#declare PlanetEle[Ur][PldLP]=   1312.56;
#declare PlanetEle[Ur][PldL]=     1542547.79 ;
#declare PlanetEle[Ne][PldA]=-0.00125196;
#declare PlanetEle[Ne][PldE]= 0.0000251 ;
#declare PlanetEle[Ne][PldI]=  -3.64;
#declare PlanetEle[Ne][PldLAN]=   -151.25;
#declare PlanetEle[Ne][PldLP]=   -844.43;
#declare PlanetEle[Ne][PldL]=      786449.21 ;
#declare PlanetEle[Pl][PldA]= 0.00076912;
#declare PlanetEle[Pl][PldE]= 0.00006465;
#declare PlanetEle[Pl][PldI]=  11.07;
#declare PlanetEle[Pl][PldLAN]=    -37.33;
#declare PlanetEle[Pl][PldLP]=   -132.25;
#declare PlanetEle[Pl][PldL]=      522747.90 ;

#local I=1;
#while (I<=9)
  #declare PlanetEle[I*100+99][PlN]=PlanetEle[I*100+99][PldL]/3600/36525;
  #declare PlanetEle[I*100+99][PlP]=360/PlanetEle[I*100+99][PlN];
  #local I=I+1;
#end        

//Asteroid elements are osculating elemets as of 22 Nov 2000
//from Minor Planet Center http://cfa-www.harvard.edu/iau/MPEph/MPEph.html
/*
(433) Eros 

Epoch 2000 Sept. 13.0 TT = JDT 2451800.5 (M-N)          Williams
M 200.69764              (2000.0)            P               Q
n   0.55971459     Peri.  178.63933     -0.54572974     -0.82350018
a   1.4582264      Node   304.41137     +0.76702883     -0.41643089
e   0.2228633      Incl.   10.82934     +0.33741047     -0.38526974
P   1.76           H   11.16          G   0.46

(243) Ida 

Epoch 2000 Sept. 13.0 TT = JDT 2451800.5 (M-c)          Goffin
M 296.64850              (2000.0)            P               Q
n   0.20375060     Peri.  112.06514     +0.23438618     -0.97207487
a   2.8602464      Node   324.37315     +0.88445083     +0.21816244
e   0.0459523      Incl.    1.13683     +0.40349703     +0.08646152
P   4.84           H    9.94          G   0.15
From 428 observations at 42 oppositions, 1885-2000, mean residual 0".68.

(951) Gaspra 

Epoch 2000 Sept. 13.0 TT = JDT 2451800.5 (M-c)          Williams
M 173.12558              (2000.0)            P               Q
n   0.30002473     Peri.  129.35803     +0.92081789     -0.38392395
a   2.2098596      Node   253.31555     +0.33218900     +0.86419497
e   0.1733777      Incl.    4.10275     +0.20431565     +0.32522217
P   3.29           H   11.46          G   0.15
From 352 observations at 24 oppositions, 1913-2000, mean residual 0".60.

*/

#declare AstEpoch  = JulianDate(2000,Sep,13,0,0,0);  
//Eros
#declare PlanetEle[Er][PlA]= 1.4582264;
#declare PlanetEle[Er][PlE]=0.2228633;
#declare PlanetEle[Er][PlI]= 10.82934;
#declare PlanetEle[Er][PlLAN]= 304.41137;
#declare PlanetEle[Er][PlLP]=PlanetEle[Er][PlLAN]+178.63933;  //LP calculated from LAN and AP
#declare PlanetEle[Er][PldL]=0.55971459;  //dL calculated from N. Enter N in deg/day.
#declare PlanetEle[Er][PlL]=PlanetEle[Er][PlLP]+200.69764-PlanetEle[Er][PldL]*(AstEpoch-PlanetEpoch);  //L calculated from LP and M
#declare PlanetEle[Er][PldA]=0;
#declare PlanetEle[Er][PldE]=0;
#declare PlanetEle[Er][PldI]=0;
#declare PlanetEle[Er][PldLAN]=0;
#declare PlanetEle[Er][PldLP]=0;
#declare PlanetEle[Er][PldL]=PlanetEle[Er][PldL]*3600*36525;  //Convert n to dL, deg/day to arcsec/cen

//Ida
#declare PlanetEle[Id][PlA]= 2.8602464;
#declare PlanetEle[Id][PlE]=0.0459523;
#declare PlanetEle[Id][PlI]= 1.13683;
#declare PlanetEle[Id][PlLAN]= 324.37315;
#declare PlanetEle[Id][PlLP]=PlanetEle[Id][PlLAN]+112.06514;  //LP calculated from LAN and AP
#declare PlanetEle[Id][PldL]=0.20375060;  //dL calculated from N. Enter N in deg/day.
#declare PlanetEle[Id][PlL]=PlanetEle[Id][PlLP]+296.64850-PlanetEle[Id][PldL]*(AstEpoch-PlanetEpoch);  //L calculated from LP and M
#declare PlanetEle[Id][PldA]=0;
#declare PlanetEle[Id][PldE]=0;
#declare PlanetEle[Id][PldI]=0;
#declare PlanetEle[Id][PldLAN]=0;
#declare PlanetEle[Id][PldLP]=0;
#declare PlanetEle[Id][PldL]=PlanetEle[Id][PldL]*3600*36525;  //Convert n to dL, deg/day to arcsec/cen

//Gaspra
#declare PlanetEle[Gs][PlA]= 2.2098596;
#declare PlanetEle[Gs][PlE]=0.1733777;
#declare PlanetEle[Gs][PlI]= 10.82934;
#declare PlanetEle[Gs][PlLAN]= 4.10275;
#declare PlanetEle[Gs][PlLP]=PlanetEle[Gs][PlLAN]+129.35803;  //LP calculated from LAN and AP
#declare PlanetEle[Gs][PldL]=0.30002473;  //dL calculated from N. Enter N in deg/day.
#declare PlanetEle[Gs][PlL]=PlanetEle[Gs][PlLP]+173.12558-PlanetEle[Gs][PldL]*(AstEpoch-PlanetEpoch);  //L calculated from LP and M
#declare PlanetEle[Gs][PldA]=0;
#declare PlanetEle[Gs][PldE]=0;
#declare PlanetEle[Gs][PldI]=0;
#declare PlanetEle[Gs][PldLAN]=0;
#declare PlanetEle[Gs][PldLP]=0;
#declare PlanetEle[Gs][PldL]=PlanetEle[Gs][PldL]*3600*36525;  //Convert n to dL, deg/day to arcsec/cen

#local I=FirstAst;
#while (I<=LastAst)
  #declare PlanetEle[I][PlN]=PlanetEle[I][PldL]/3600/36525;
  #declare PlanetEle[I][PlP]=360/PlanetEle[I][PlN];
  #local I=I+1;
#end        

/*******************************\
              q AU      e                             AP        Tp
Hale-Bopp 0.913457   0.994972   89.4232  282.4209  130.5551  1997 Apr 1 02:38:15             
--------------------------------------------------------------------------------
\*******************************/

#macro CalcPlanetPos(Time)
  #declare PlanetPos=array[1000]
  #declare PlanetPos[0]=<0,0,0>;
  #declare PlanetPos[Su]=PlanetPos[0];
  #declare PlanetVel=array[1000]
  #declare PlanetVel[Su]=<0,0,0>;
  #local DeltaT=(Time-PlanetEpoch)/36525; //DeltaT in Julian Centuries=36525 days
  #local I=1;
  #while (I<=9)
    #local LP= PlanetEle[I*100+99][PlLP] +DeltaT*PlanetEle[I*100+99][PldLP]/3600;
    #local L=  PlanetEle[I*100+99][PlL]  +DeltaT*PlanetEle[I*100+99][PldL]/3600;
    #local LAN=PlanetEle[I*100+99][PlLAN]+DeltaT*PlanetEle[I*100+99][PldLAN]/3600;
    #local AP= LP-LAN;
    #local M=  L-LP;     
    //Record some M's for perturbations later
    #if(I=5)
      #local Mj=radians(M);
    #end
    #if(I=6)
      #local Ms=radians(M);
    #end
    #if(I=7)
      #local Mu=radians(M);
    #end
    #declare PlanetPos[I*100+99]=PosInSpace(
      Time,
      PlanetEle[I*100+99][PlA]+DeltaT*PlanetEle[I*100+99][PldA],
      PlanetEle[I*100+99][PlE]+DeltaT*PlanetEle[I*100+99][PldE],
      PlanetEle[I*100+99][PlI]+DeltaT*PlanetEle[I*100+99][PldI]/3600,
      LAN,
      AP,
      M,
      PlanetEle[I*100+99][PlN],
      Time);
    #declare PlanetVel[I*100+99]=VelInSpace(
      Time,
      PlanetEle[I*100+99][PlA]+DeltaT*PlanetEle[I*100+99][PldA],
      PlanetEle[I*100+99][PlE]+DeltaT*PlanetEle[I*100+99][PldE],
      PlanetEle[I*100+99][PlI]+DeltaT*PlanetEle[I*100+99][PldI]/3600,
      LAN,
      AP,
      M,
      PlanetEle[I*100+99][PlN],
      Time);
    #declare PlanetPos[I*100]=PlanetPos[I*100+99]; //Default barycenter is at center of planet
    #declare PlanetMass[I*100]=PlanetMass[I*100+99];
    #declare PlanetPos[Su]=PlanetPos[Su]-PlanetPos[I*100]*PlanetMass[I*100]/PlanetMass[Su]; //Shift solarcenter from system barycenter
    #local I=I+1;
  #end 
  //Jupiter Perturbations
  #local R=vlength(PlanetPos[Ju]);
  #local B=asin((PlanetPos[Ju]/R).y);
  #local L=atan2(PlanetPos[Ju].z,PlanetPos[Ju].x)+radians(
      -0.332 * sin(2*Mj - 5*Ms - radians(67.6))
      -0.056 * sin(2*Mj - 2*Ms + radians(21))
      +0.042 * sin(3*Mj - 5*Ms + radians(21))
      -0.036 * sin(Mj - 2*Ms)
      +0.022 * cos(Mj - Ms)
      +0.023 * sin(2*Mj - 3*Ms + radians(52))
      -0.016 * sin(Mj - 5*Ms - radians(69)));
  #declare PlanetPos[Ju]=<cos(L)*cos(B),sin(B),sin(L)*cos(B)>*R;
  //Saturn Perturbations
  #local R=vlength(PlanetPos[Sa]);
  #local B=asin((PlanetPos[Sa]/R).y)+radians(
      -0.020 * cos(2*Mj - 4*Ms - radians(2))
      +0.018 * sin(2*Mj - 6*Ms - radians(49)));
  #local L=atan2(PlanetPos[Sa].z,PlanetPos[Sa].x)+radians(
      +0.812 * sin(2*Mj - 5*Ms - radians(67.6))
      -0.229 * cos(2*Mj - 4*Ms - radians(2))
      +0.119 * sin(Mj - 2*Ms - radians(3))
      +0.046 * sin(2*Mj - 6*Ms - radians(69))
      +0.014 * sin(Mj - 3*Ms + radians(32)));
  #declare PlanetPos[Sa]=<cos(L)*cos(B),sin(B),sin(L)*cos(B)>*R;
  //Uranus Perturbations
  #local R=vlength(PlanetPos[Ur]);
  #local B=asin((PlanetPos[Ur]/R).y);
  #local L=atan2(PlanetPos[Ur].z,PlanetPos[Ur].x)+radians(
      +0.040 * sin(Ms - 2*Mu + radians(6))
      +0.035 * sin(Ms - 3*Mu + radians(33))
      -0.015 * sin(Mj - Mu + radians(20)));
  #declare PlanetPos[Ur]=<cos(L)*cos(B),sin(B),sin(L)*cos(B)>*R;
  #undef R
  #undef B
  #undef L
  
  #ifndef(IncludeAsteroids) #declare IncludeAsteroids=1; #end
  #if(IncludeAsteroids)
    #local I=FirstAst;
    #while (I<=LastAst)
      #local LP= PlanetEle[I][PlLP] +DeltaT*PlanetEle[I][PldLP]/3600;
      #local L=  PlanetEle[I][PlL]  +DeltaT*PlanetEle[I][PldL]/3600;
      #local LAN=PlanetEle[I][PlLAN]+DeltaT*PlanetEle[I][PldLAN]/3600;
      #local AP= LP-LAN;
      #local M=  L-LP;
      #declare PlanetPos[I]=PosInSpace(
        Time,
        PlanetEle[I][PlA]+DeltaT*PlanetEle[I][PldA],
        PlanetEle[I][PlE]+DeltaT*PlanetEle[I][PldE],
        PlanetEle[I][PlI]+DeltaT*PlanetEle[I][PldI]/3600,
        LAN,
        AP,
        M,
        PlanetEle[I][PlN],
        Time);
      #declare PlanetVel[I]=VelInSpace(
        Time,
        PlanetEle[I][PlA]+DeltaT*PlanetEle[I][PldA],
        PlanetEle[I][PlE]+DeltaT*PlanetEle[I][PldE],
        PlanetEle[I][PlI]+DeltaT*PlanetEle[I][PldI]/3600,
        LAN,
        AP,
        M,
        PlanetEle[I][PlN],
        Time);
      #local I=I+1;
    #end                 
  #end
  #ifndef(IncludeMoons) #declare IncludeMoons=1; #end
  #if(IncludeMoons) 
    #include "EarthSat.inc"
    #declare MP=(CalcEarthSatPos(Time))*KmtoAU(1);
    #declare MR=PlanetMass[Ea]/PlanetMass[Mo];
    #declare PlanetPos[300]=PlanetPos[Ea];
    #declare PlanetPos[Mo]=PlanetPos[Ea]+(MP*MR/(MR+1));
    #declare PlanetPos[Ea]=PlanetPos[Ea]-(MP*1/(MR+1));
    #include "MarsSat.inc"
    #declare PlanetPos[401]=PlanetPos[Ma]+CalcMarsSatPos(1,Time)*KmtoAU(1);
    #declare PlanetPos[402]=PlanetPos[Ma]+CalcMarsSatPos(2,Time)*KmtoAU(1);
    #include "JupiterSat.inc"
    #declare PlanetPos[501]=PlanetPos[Ju]+CalcJupiterSatPos(1,Time)*KmtoAU(1);
    #declare PlanetPos[502]=PlanetPos[Ju]+CalcJupiterSatPos(2,Time)*KmtoAU(1);
    #declare PlanetPos[503]=PlanetPos[Ju]+CalcJupiterSatPos(3,Time)*KmtoAU(1);
    #declare PlanetPos[504]=PlanetPos[Ju]+CalcJupiterSatPos(4,Time)*KmtoAU(1);
  #end
#end

#warning "Out of PlanetPos.inc\n\n"
