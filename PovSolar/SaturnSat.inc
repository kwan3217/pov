//EarthSat.inc         
//Position of moons of Saturn
//in km, J2000 ecliptic    

//Orbital elements and perturbations are from Paul Schlyter's page, http://hotel04.ausys.se/pausch/comp/tutorial.html

#macro CalcRheaSatPos(TimeSMJD)
  #local D=TimeSMJD-11093;
  #local T=D/365.25;
  #local A=AUtoKm(0.00352400);  //Semimajor axis
  #local N=radians(79.6900400700);       //rad/day, Mean daily motion
  #local Pi=radians(305+10.2077*T);      //rad
  #local OmegaT=radians(276.49+0.5219*(TimeSMJD-11368.0)/365.25); //rad
  #local NT=radians(44.5-0.5219*(TimeSMJD-11368.0)/365.25);       //rad
  #local Gamma0=radians(0.3305); //deg
  #local Kappa=radians(57.29578);
  #local ESin=0.000210*sin(Pi)+0.00100*sin(OmegaT);
  #local ECos=0.000210*cos(Pi)+0.00100*cos(OmegaT);
  #local E=sqrt(ESin*ESin+ECos*ECos);
  #local OmegaBar=atan2(ESin,ECos);
  #local Lambda=radians(359.4727+N*D+Kappa*sin(Gamma0)*tan(Ie/2)*sin(radians(356.87-10.2077*T));
  
  

#ifndef(EarthSatMethod) #declare EarthSatMethod=2; #end

#macro CalcEarthSatPos(Date)
  #if(EarthSatMethod=1)
   (CalcEarthSatPos1(Date))    
  #else
   (CalcEarthSatPos2(Date))    
  #end
#end
                       
#macro CalcEarthSatPos1(T)
  #local D=T-51543.5;
  #local N=(Rev(125.1228-0.0529538083*D));   //Longitude of Asc Node
  #local I=5.1454;                           //Inclination
  #local W=(Rev(318.0634+0.1643573223*D));   //Argument of Perigee
  #local A=60.2666;                          //Semimajor Axis, Earth Radii
  #local E=0.054900;                         //Eccentricity
  #local Mm=(Rev(115.3654+13.0649929509*D)); //Mean Anomaly
  #local Ecc=degrees(MeanToEcc(radians(Mm),E));
  #local X=A*(CosD(Ecc)-E);
  #local Y=A*sqrt(1-E*E)*SinD(Ecc);
  #local R=sqrt(X*X+Y*Y);
  #local V=Rev(Atan2D(Y,X));
  #local Xe=R*(CosD(N)*CosD(V+W)-SinD(N)*SinD(V+W)*CosD(I));
  #local Ye=R*(SinD(N)*CosD(V+W)+CosD(N)*SinD(V+W)*CosD(I));
  #local Ze=R*SinD(V+W)*SinD(I);
  #local Lon=Rev(Atan2D(Ye,Xe));
  #local Lat=Atan2D(Ze,sqrt(Xe*Xe+Ye*Ye));
  #local Ls=Rev((282.9404+4.70935e-5*D)+(356.0470+0.9856002585*D));
  #local Ms=Rev(356.0470+0.9856002585*D);
  #local Lm=Rev(N+W+Mm);
  #local DD=Rev(Lm-Ls);
  #local F=Rev(Lm-N);
  #local PLon01=-1.274 * SinD(Mm - 2*DD);    //(Evection)
  #local PLon02=+0.658 * SinD(2*DD);         //(Variation)
  #local PLon03=-0.186 * SinD(Ms);           //(Yearly equation)
  #local PLon04=-0.059 * SinD(2*Mm - 2*DD);
  #local PLon05=-0.057 * SinD(Mm - 2*DD + Ms);
  #local PLon06=+0.053 * SinD(Mm + 2*DD);
  #local PLon07=+0.046 * SinD(2*DD - Ms);
  #local PLon08=+0.041 * SinD(Mm - Ms);
  #local PLon09=-0.035 * SinD(DD);           //(Parallactic equation)
  #local PLon10=-0.031 * SinD(Mm + Ms);
  #local PLon11=-0.015 * SinD(2*F - 2*DD);
  #local PLon12=+0.011 * SinD(Mm - 4*DD);
  #local PLon=PLon01+PLon02+PLon03+PLon04+PLon05+PLon06+PLon07+PLon08+PLon09+PLon10+PLon11+PLon12;
  #local PLat01=-0.173 * SinD(F - 2*DD);
  #local PLat02=-0.055 * SinD(Mm - F - 2*DD);
  #local PLat03=-0.046 * SinD(Mm + F - 2*DD);
  #local PLat04=+0.033 * SinD(F + 2*DD);
  #local PLat05=+0.017 * SinD(2*Mm + F);
  #local PLat=PLat01+PLat02+PLat03+PLat04+PLat05;
  #local PDis01=-0.58 * CosD(Mm - 2*DD);
  #local PDis02=-0.46 * CosD(2*DD);
  #local PDis=PDis01+PDis02;
  #local Lon=Lon+PLon;
  #local Lat=Lat+PLat;
  #local R=R+PDis;
  #local Pos=<R*CosD(Lon)*CosD(Lat),R*SinD(Lat),R*SinD(Lon)*CosD(Lat)>;
  (Pos*6378.135)
#end

#declare MoonTerms=array[60][11]   
   //D  M  M' F   L          R     D  M  M' F    B 
   {{0, 0, 1, 0,6288774,-20905355, 0, 0, 0, 1,5128122},
    {2, 0,-1, 0,1274027, -3699111, 0, 0, 1, 1, 280602},
    {2, 0, 0, 0, 658314, -2955968, 0, 0, 1,-1, 277693},
    {0, 0, 2, 0, 213618,  -569925, 2, 0, 0,-1, 173237},
    {0, 1, 0, 0,-185116,    48888, 2, 0,-1, 1,  55413},
    {0, 0, 0, 2,-114332,    -3149, 2, 0,-1,-1,  46271},
    {2, 0,-2, 0,  58793,   246158, 2, 0, 0, 1,  32573},
    {2,-1,-1, 0,  57066,  -152138, 0, 0, 2, 1,  17198},
    {2, 0, 1, 0,  53322,  -170733, 2, 0, 1,-1,   9266},
    {2,-1, 0, 0,  45758,  -204586, 0, 0, 2,-1,   8822},
    {0, 1,-1, 0, -40923,  -129620, 2,-1, 0,-1,   8216},
    {1, 0, 0, 0, -34720,   108743, 2, 0,-2,-1,   4324},
    {0, 1, 1, 0, -30383,   104755, 2, 0, 1, 1,   4200},
    {2, 0, 0,-2,  15327,    10321, 2, 1, 0,-1,  -3359},
    {0, 0, 1, 2, -12528,        0, 2,-1,-1, 1,   2463},
    {0, 0, 1,-2,  10980,    79661, 2,-1, 0, 1,   2211},
    {4, 0,-1, 0,  10675,   -34782, 2,-1,-1,-1,   2065},
    {0, 0, 3, 0,  10034,   -23210, 0, 1,-1,-1,  -1870},
    {4, 0,-2, 0,   8548,   -21636, 4, 0,-1,-1,   1828},
    {2, 1,-1, 0,  -7888,    24208, 0, 1, 0, 1,  -1794},
    {2, 1, 0, 0,  -6766,    30824, 0, 0, 0, 3,  -1749},
    {1, 0,-1, 0,  -5163,    -8379, 0, 1,-1, 1,  -1565},
    {1, 1, 0, 0,   4987,   -16675, 1, 0, 0, 1,  -1491},
    {2,-1, 1, 0,   4036,   -12831, 0, 1, 1, 1,  -1475},
    {2, 0, 2, 0,   3994,   -10445, 0, 1, 1,-1,  -1410},
    {4, 0, 0, 0,   3861,   -11650, 0, 1, 0,-1,  -1344},
    {2, 0,-3, 0,   3665,    14403, 1, 0, 0,-1,  -1335},
    {0, 1,-2, 0,  -2689,    -7003, 0, 0, 3, 1,   1107},
    {2, 0,-1, 2,  -2602,        0, 4, 0, 0,-1,   1021},
    {2,-1,-2, 0,   2390,    10056, 4, 0,-1, 1,    833},
    {1, 0, 1, 0,  -2348,     6322, 0, 0, 1,-3,    777},
    {2,-2, 0, 0,   2236,    -9884, 4, 0,-2, 1,    671},
    {0, 1, 2, 0,  -2120,     5751, 2, 0, 0,-3,    607},
    {0, 2, 0, 0,  -2069,        0, 2, 0, 2,-1,    596},
    {2,-2,-1, 0,   2048,    -4950, 2,-1, 1,-1,    491},
    {2, 0, 1,-2,  -1773,     4130, 2, 0,-2, 1,   -451},
    {2, 0, 0, 2,  -1595,        0, 0, 0, 3,-1,    439},
    {4,-1,-1, 0,   1215,    -3958, 2, 0, 2, 1,    422},
    {0, 0, 2, 2,  -1110,        0, 2, 0,-3,-1,    421},
    {3, 0,-1, 0,   -892,     3258, 2, 1,-1, 1,   -366},
    {2, 1, 1, 0,   -810,     2616, 2, 1, 0, 1,   -351},
    {4,-1,-2, 0,    759,    -1897, 4, 0, 0, 1,    331},
    {0, 2,-1, 0,   -713,    -2117, 2,-1, 1, 1,    315},
    {2, 2,-1, 0,   -700,     2354, 2,-2, 0,-1,    302},
    {2, 1,-2, 0,    691,        0, 0, 0, 1, 3,   -283},
    {2,-1, 0,-2,    596,        0, 2, 1, 1,-1,   -229},
    {4, 0, 1, 0,    549,    -1423, 1, 1, 0,-1,    223},
    {0, 0, 4, 0,    537,    -1117, 1, 1, 0, 1,    223},
    {4,-1, 0, 0,    520,    -1571, 0, 1,-2,-1,   -220},
    {1, 0,-2, 0,   -487,    -1739, 2, 1,-1,-1,   -220},
    {2, 1, 0,-2,   -399,        0, 1, 0, 1, 1,   -185},
    {0, 0, 2,-2,   -381,    -4421, 2,-1,-2,-1,    181},
    {1, 1, 1, 0,    351,        0, 0, 1, 2, 1,   -177},
    {3, 0,-2, 0,   -340,        0, 4, 0,-2,-1,    176},
    {4, 0,-3, 0,    330,        0, 4,-1,-1,-1,    166},
    {2,-1, 2, 0,    327,        0, 1, 0, 1,-1,   -164},
    {0, 2, 1, 0,   -323,     1165, 4, 0, 1,-1,    132},
    {1, 1,-1, 0,    299,        0, 1, 0,-1,-1,   -119},
    {2, 0, 3, 0,    294,        0, 4,-1, 0,-1,    115},
    {2, 0,-1,-2,      0,     8752, 2,-2, 0, 1,    107}}

#macro CalcEarthSatPos2(Date)
  #local D=Date-51545;
  #local T=D/36525;   
  #local LPrime=radians(mod(218.3164591+481267.88134236*T-0.0013268*pow(T,2)+pow(T,3)/538841-pow(T,4)/65194000,360));
  #local D=radians(mod(297.8502042+445267.1115168*T-0.00163*pow(T,2)+pow(T,3)/545868-pow(T,4)/113065000,360));       
  #local M=radians(mod(357.5291092+35999.0502909*T-0.0001536*pow(T,2)+pow(T,3)/24490000,360));                       
  #local MPrime=radians(mod(134.9634114+477198.8676313*T+0.008997*pow(T,2)+pow(T,3)/69699-pow(T,4)/14712000,360));   
  #local F=radians(mod(93.2720993+483202.0175273*T-0.0034029*pow(T,2)+pow(T,3)/3526000-pow(T,4)/863310000,360));     
  #local A1=radians(mod(119.75+131.849*T,360));
  #local A2=radians(mod(53.09+479264.29*T,360));
  #local A3=radians(mod(313.45+481266.484*T,360));
  #local E=1-0.002516*T-0.0000074*pow(T,2);
  #local I=1;
  #local LTermTotal=3958*sin(A1)+1962*sin(LPrime-F)+318*sin(A2);
  #local RTermTotal=0;
  #local BTermTotal=-2235*sin(LPrime)+382*sin(A3)+175*sin(A1-F)+175*sin(A1+F)+127*sin(LPrime-MPrime)+115*sin(LPrime+MPrime);
  #while(I<=60)
    #local LTermTotal=LTermTotal+MoonTerms[I-1][4] *pow(E,abs(MoonTerms[I-1][1]))*sin(MoonTerms[I-1][0]*D+MoonTerms[I-1][1]*M+MoonTerms[I-1][2]*MPrime+MoonTerms[I-1][3]*F);
    #local RTermTotal=RTermTotal+MoonTerms[I-1][5] *pow(E,abs(MoonTerms[I-1][1]))*cos(MoonTerms[I-1][0]*D+MoonTerms[I-1][1]*M+MoonTerms[I-1][2]*MPrime+MoonTerms[I-1][3]*F);
    #local BTermTotal=BTermTotal+MoonTerms[I-1][10]*pow(E,abs(MoonTerms[I-1][7]))*sin(MoonTerms[I-1][6]*D+MoonTerms[I-1][7]*M+MoonTerms[I-1][8]*MPrime+MoonTerms[I-1][9]*F);
    #local I=I+1;
  #end
  #local Lon=LPrime+radians(LTermTotal/1000000);
  #local Lat=radians(BTermTotal/1000000);
  #local Dist=385000.56+ RTermTotal/1000;
  (<cos(Lon)*cos(Lat),sin(Lat),sin(Lon)*cos(Lat)>*Dist)
#end
                       
