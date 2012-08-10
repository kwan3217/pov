// Gauss.inc
//Copyright © 1999 Kwan Systems
//You may use and modify this as you see fit for any non-commercial purpose
//otherwise contact me at chrisj@digiquill.com
//Chris Jeppesen - 13 May 1999

/*Usage*************************\
#macro PlotOrbit(R1,R3,A,E,I,LAN,AP,M,N,FT)
Parameters:
  R1,R3: Start and End position of the orbit
  FT: Flight Time of orbit (in days)
Returns:
  A,E,I,LAN,AP,M,N:  Pass variables to hold calculated orbital elements
Remarks:
  Epoch of orbit is time object is at R1
  orbital elements returned are in degrees
  Assumes heliocentric orbit, length units same as those of R1 and R3,
  Time unit is days.
\*******************************/

#include "kepler.inc"

//Theta is in radians
#macro GenerateOrbit(R1,R3,Theta,A,E)   
  #declare Phi=vangle(R1,R3);
  PrintNumber("Phi:   ",Phi)
  #declare E=((vlength(R1) - vlength(R3)) / (vlength(R3) * cos(Theta + Phi) - vlength(R1) * cos(Theta)));
  PrintNumber("E:     ",E)
  
  #declare A=vlength(R1) * (1 + E * cos(Theta)) / (1 - E * E);
  PrintNumber("A:     ",A)
#end

#macro FinishOrbit(R1,R3,Theta,A,E,I,LAN,AP,M,N)
  #local VX=vcross(R3,R1);             
  PrintNumber("            A: ",A)
  PrintNumber("            E: ",E)
  #declare I=degrees(vangle(VX,<0,1,0>));
  PrintNumber("            I: ",I)        
  #declare LAN=atan2(VX.z,VX.x)+pi/2; 
  #local VP=vaxis_rotate(R1,VX,degrees(Theta));
  #local VLAN=<cos(LAN),0,sin(LAN)>;
  #local VZ=vcross(VP,VLAN);
  #declare LAN=degrees(LAN);
  PrintNumber("          LAN: ",LAN)        
  #declare AP=(Sgn(VZ.y))*degrees(vangle(VP,VLAN));
  PrintNumber("           AP: ",AP) 
  PrintNumber("        Theta: ",degrees(Theta))
  #declare M=degrees(AnomToMean(Theta,E));
  PrintNumber("            M: ",M)
  #local P=AtoP(1,PlanetEle[Ea][PlaP],abs(A));         
  PrintNumber("            P: ",P)
  #declare N=360/P; 
  PrintNumber("            N: ",N)
#end   

#macro TimeOrbit(R1,R3,Theta,A,E)
  #local Phi=Acos(vdot(R1,R3)/(vlength(R1)*vlength(R3)));
  #local M1=AnomToMean(Theta,E);
  #local M3=AnomToMean(Theta+Phi,E);
  #local P=AtoP(PlanetMass[Su],abs(A));
  (P*abs(M3-M1)/(2*pi))
#end

#macro PlotOrbit(R1,R3,A,E,I,LAN,AP,M,N,FT)
  #local Tolerance=1e-10;
  #local Delta=0.001;
  #local TT2=0;
  #local TT1=0;
  #local Theta = -0.1;
  PrintNumber("Theta: ",Theta)
  #declare E = -1;
  #while (!((E > 0) & ((E < 1 & A > 0) | (E > 1 & A < 0))))
    #local Theta = Theta + 0.1;
    PrintNumber("Theta: ",Theta)
    GenerateOrbit(R1, R3, Theta + Delta, A, E)
  #end
  #local TT2 = TimeOrbit(R1, R3, Theta + Delta, A, E);
  GenerateOrbit(R1, R3, Theta, A, E)
  #local TT1 = TimeOrbit(R1, R3, Theta, A, E);
  PrintNumber("Diff:  ",TT1-FT)
  #while (abs(TT1 - FT) > Tolerance)
    #if (TT1 > 0)
      #local M = (TT2 - TT1) / Delta;
      #local Theta = Constrain(-2*pi, 2*pi, Theta - (TT1 - FT) / M);
    #else
      #local Theta = Constrain(-2*pi, 2*pi, Theta + 0.1);
    #end
    PrintNumber("Theta: ",Theta)
    #while (!((E > 0) & ((E < 1 & A > 0) | (E > 1 & A < 0))))
      #local Theta = Theta + 0.1;
      PrintNumber("Theta: ",Theta)
      GenerateOrbit(R1, R3, Theta + Delta, A, E)
    #end
    #local TT2 = TimeOrbit(R1, R3, Theta + Delta, A, E);
    #while (!((E > 0) & ((E < 1 & A > 0) | (E > 1 & A < 0))))
      #local Theta = Theta + 0.1;
      PrintNumber("Theta: ",Theta)
      GenerateOrbit(R1, R3, Theta, A, E)
    #end
    #local TT1 = TimeOrbit(R1, R3, Theta, A, E);
    PrintNumber("Diff:  ",(TT1-FT))
    PrintNumber("FT:    ",FT)
  #end
  FinishOrbit(R1, R3, Theta, A, E, I, LAN, AP, M, N)
#end
    
             
