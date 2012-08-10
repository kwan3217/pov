//KeplerGaussFG.inc
//Solve the kepler problem using state vectors and universal variable formulation
#include "KwanMath.inc"

/*
#macro KeplerFG(R0,V0,T,Mu,R,V)
  Algorithm for solving the Kepler problem: Given Mu, and state at some time
  calculate state at some other time
	R0,V0  State at T0=0
	T      Time from T0, in time units of GM
	Mu     GM of central body
	R,V    State at T
*/

//Auxiliary function C(Z)
#macro CFunc(Z)
  #if(Z > 0)
    #local result=((1 - cos(sqrt(Z))) / Z);
  #else
    #if(Z < 0)
      #local result=((1 - CosH(sqrt(-Z))) / Z);
    #else
      #local result=(1 / 2);
    #end
  #end
	(result)
#end

//Derivative of C with respect to Z dC/dz
#macro CPrime(Z)
  #if(Z!=0)
    #local result=((1 - Z * SFunc(Z) - 2 * CFunc(Z)) / (2 * Z));
  #else
    #local result=(1 / 20);
  #end
	(result)
#end

//Auxiliary function S(Z)
#macro SFunc(Z)
  #if(Z > 0)
    #local result=((sqrt(Z) - sin(sqrt(Z))) / pow(Z,3/2));
  #else
    #if(Z < 0)
      #local result=((SinH(sqrt(-Z)) - sqrt(-Z)) / pow(-Z,3/2));
    #else
      #local result=(1 / 6);
    #end
  #end
	(result)
#end

//Derivative of C with respect to Z dS/dz
#macro SPrime(Z)
  #if(Z!=0)
    #local result=((CFunc(Z) - 3 * SFunc(Z)) / (2 * Z));
  #else
    #local result=(1 / 120);
  #end
	(result)
#end

//Auxiliary variable f
//R=f*R0+G*V0
#macro FFunc(X,Alpha,r0l)
  #local Z = pow(X,2)*Alpha;
  (1 - pow(X,2) * CFunc(Z) / r0l)
#end

//Auxiliary variable g
//R=f*R0+G*V0
#macro GFunc(X, Alpha, T)
  #local Z = pow(X,2) *Alpha;
  (T - pow(X,3) * SFunc(Z) / sqrt(Mu))
#end

//derivative of f with respect to time df/dt
//V=fdot*R0+gdot*V0
#macro FDot(X,Alpha,R,R0)
  #local Z = pow(X, 2) * Alpha;
  (sqrt(Mu) * X * (Z * (SFunc(Z)) - 1) / (R0 * R))
#end

//derivative of g with respect to time dg/dt
//V=fdot*R0+gdot*V0
#macro GDot(X,Alpha,R)
  #local Z = pow(X,2) * Alpha;
  (1 - pow(X,2) * (CFunc(Z)) / R)
#end

#declare DUinSU=60268; //Saturn radius, km

#macro KeplerFG(R0,V0,T,Mu,R,V)
  PrintNumber("T:  ",T)
  PrintNumber("Mu: ",Mu)
  #if(T=0)
    #declare R=R0;
    #declare V=V0;
	#else
    #local DistY=DUinSU;
    #local TimeX=sqrt(pow(DistY,3)/Mu);
		PrintNumber("TimeX: ",TimeX)
    #local TCU=T/TimeX;
  	PrintNumber("TCU: ",TCU)
    #local R0CU=R0/DistY;
	  PrintVector("R0CU: ",R0CU)
    #local V0CU=V0*TimeX/DistY;
  	PrintVector("V0CU: ",V0CU)
	  #local RCU=<0,0,0>;
  	#local VCU=<0,0,0>;
    KeplerCU(R0CU,V0CU,TCU,RCU,VCU)
    #declare R=RCU*DistY;
    #declare V=VCU*DistY/TimeX;
	#end
#end

#macro KeplerCU(R0,V0,T,R,V)
  //Algorithm for solving the Kepler problem: Given state at some time
  //calculate state at some other time
//  PrintVector("R0: ",R0)
//  PrintVector("V0: ",V0)
//  PrintNumber("T: ",T)
  #if(T = 0)
    #local R = R0;
    #local V = V0;
  #else
    #local r0l= vlength(R0);
    #local v0l = vlength(V0);
    #local R0dotV0 = vdot(R0, V0);
    #local Energy = pow(v0l,2) / 2 - 1 / r0l;
    PrintNumber("Energy: ",Energy)
    #local Alpha = -(2 * Energy);
//    PrintNumber("Alpha: ",Alpha)
//    PrintNumber("A: ",1/Alpha)
		#if(Energy<0)
      #local Xp1 = T * Alpha;
		#else
		  #local Xp1=Sgn(T)*sqrt(-1/Alpha)*log(-2*T/((R0dotV0+Sgn(T)*sqrt(-1/Alpha)*(1-r0l*Alpha))/Alpha));
		#end
		PrintNumber("Xp1: ",Xp1)
		
    #local X = 0;
    #while(abs(X / Xp1 - 1) > 1e-15)
      #local X = Xp1;
      #local Z = pow(X,2) * Alpha;
      #local TT = R0dotV0 * pow(X,2) * CFunc(Z) + (1 - r0l * Alpha) * pow(X,3) * SFunc(Z) + r0l * X;
      #local DtDx = pow(X, 2) * (CFunc(Z)) + R0dotV0 * X * (1 - Z * (SFunc(Z))) + r0l * (1 - Z * (CFunc(Z)));
      PrintNumber("DtDx: ",DtDx)
      #local Xp1 = X + (T - TT) / (DtDx);
      PrintNumber("X: ",X)
    #end
    #declare R = R0*FFunc(X, Alpha, r0l)+V0*GFunc(X, Alpha, T);
    #local rl = vlength(R);
    #declare V = R0*FDot(X, Alpha, rl, r0l)+V0*GDot(X, Alpha, rl);
  #end
#end

#macro Newton(Xthis,Ygoal,Ythis,DyDx)
  (Z+(T-TTrial)/DyDx)
#end

#macro GaussFG(R1,R2,T,Mu,Type,V1,V2)
  //Algorithm for solving the Gauss problem: Given Mu, two points on orbit R0 and R1, time between points T, and trajectory Type
  //find velocities at the two points V0 and V1
  #local r1l=vlength(R1);
  PrintNumber("T:   ",T)
  PrintVector("R1: ",R1)
  #local r2l=vlength(R2);
  PrintVector("R2: ",R2)
  PrintNumber("Mu: ",Mu)
  #local DeltaNu=vangle(R1,R2);
  #if(mod(Type,2)=1)
    #local DM=1;
  #else
    PrintNumber("Here",0)
    #local DM=-1;
    #local DeltaNu=2*pi-DeltaNu;
  #end
  PrintNumber("DM:      ",DM)
  PrintNumber("DeltaNu: ",DeltaNu)
  #local A=DM*sqrt(r1l*r2l*(1+cos(DeltaNu)));
  PrintNumber("A: ",A)
  #local Z=0; //First trial gives parabolic orbit
  #local TTrial=0;
  #local Iters=0;
  #while(abs(TTrial-T)>0.0001)
    #local Y=-1;
    #local Z=Z*2;
    #while(Y<0)
      #local Z=Z/2;
      PrintNumber("Z: ",Z)
      #local S=(SFunc(Z));
      PrintNumber("S: ",S)
      #local C=(CFunc(Z));
      PrintNumber("C: ",C)
      #local Y=r1l+r2l-A*(1-Z*S)/sqrt(C);
      PrintNumber("Y: ",Y)
    #end
    #local X=sqrt(Y/C);
    PrintNumber("X: ",X)
    #local TTrial=(pow(X,3)*S+A*sqrt(Y))/sqrt(Mu);
    PrintNumber("TTrial: ",TTrial)
    //Now the fun part... New Z part
    //Newton's Method  Zn+1=Zn+(T-TTrial)/(dt/dZ)
    #local DtDz=(pow(X,3)*(SPrime(Z)-3*S*CPrime(Z)/(2*C))+A/8*(3*S*sqrt(Y)/C+A/X))/sqrt(Mu);
    PrintNumber("DtDz: ",DtDz)
    #local Z=Newton(Z,T,TTrial,DtDz);
    #local Iters=Iters+1;
  #end
  #local F=1-Y/r1l;
  PrintNumber("F: ",F)
  #local G=A*sqrt(Y/Mu);
  PrintNumber("G: ",G)
  #local GPrime=1-Y/r2l;
  PrintNumber("GPrime: ",GPrime)
  #local V1=(R2-F*R1)/G;
  PrintVector("V1: ",V1)
  #local V2=(GPrime*R2-R1)/G;
  PrintVector("V2: ",V2)
#end

#macro PosVelToEle(R,V,T,Mu,A,E,I,LAN,AP,Tp)
  //Given Position R and Velocity V at Time T in gravity field Mu,
  //Find Semimajor axis A, Eccentricity E, Inclination I,
  //     Longitude of Ascending Node LAN, Argument of Pericenter AP,
  //     and Time of Pericenter Passage Tp
  #local H=vcross(V,R);
  #local N=vcross(H,y);
  #local MuEvec=(pow(vlength(V),2)-Mu/vlength(R))*R-vdot(R,V)*V;
  #local Evec=MuEvec/Mu;
//  PrintVector("EVec: ",Evec)
  #declare E=vlength(Evec);
  #declare P=pow(vlength(H),2)/Mu;
  #declare A=P/(1-pow(E,2));
  #declare I=vangle(H,y);
  #declare LAN=atan2(N.z,N.x);
  #declare AP=acos(vdot(N,Evec)/(vlength(N)*E));
  #if(Evec.y<0)
    #declare AP=AP+pi;
  #end
  #local TA=acos(vdot(Evec,R)/(vlength(R)*E));
  #if(vdot(R,V)<0)
    #local TA=TA+pi;
  #end
  #if(E<1)
    #local EA=acos((E+cos(TA))/(1+E*cos(TA)));
    PrintNumber("EA: ",EA)
    #if(TA>pi|TA<0)
      #local EA=2*pi-EA;
    #end
    PrintNumber("EA: ",EA)
    #local M=EA-E*sin(EA);
    PrintNumber("M: ",M)
    #local NN=sqrt(Mu/pow(A,3));
    PrintNumber("NN: ",NN)
    //M=N(T-Tp)
    //M/N=T-Tp
    //M/N-T=-TP
    PrintNumber("Tp: ",-M/NN)
    #declare Tp=T-M/NN;
    PrintDate("Tp: ",Tp)
  #else
    #local FA=AcosH((E+cos(TA))/(1+E*cos(TA)));
    #if(TA>pi|TA<0)
      #local FA=-abs(FA);
    #end
    #local NN=sqrt(Mu/pow(-A,3));
    #local M=E*SinH(FA)-FA;
    #declare Tp=T-M*NN;
  #end
#end

#macro PosVelToElePrint(R,V,T,Mu)
  #local A=0;
  #local E=0;
  #local I=0;
  #local LAN=0;
  #local AP=0;
  #local Tp=0;
  PosVelToEle(R,V,T,Mu,A,E,I,LAN,AP,Tp)
  PrintNumber("A: ",A)
  PrintNumber("E: ",E)
  PrintNumber("I: ",degrees(I))
  PrintNumber("LAN: ",degrees(LAN))
  PrintNumber("AP: ",degrees(AP))
  PrintDate("Tp: ",Tp)
  PrintNumber("Peri: ",A*(1-E))
  #if(E<1)
    PrintNumber("Apoa: ",A*(1+E))
  #end
#end

//Test
/*
#declare TestR1=<0.5,0.6,0.7>;
#declare TestR2=<0,1,0>;
#declare TestT=0.9667663;

#declare TestV1=<0,0,0>;
#declare TestV2=<0,0,0>;

GaussFG(TestR1,TestR2,TestT,1,2,TestV1,TestV2)
*/


//Test

#declare TestMu=37931284.50;
#declare TestR0=<DUinSU,0,0>;
#declare TestV0=<0,0,sqrt(TestMu/DUinSU)>;
#declare TestT=2*pi;

#declare TestR=<0,0,0>;
#declare TestV=<0,0,0>;
KeplerFG(TestR0,TestV0,TestT,TestMu,TestR,TestV)

PrintVector("TestR: ",TestR)
PrintVector("TestV: ",TestV)
