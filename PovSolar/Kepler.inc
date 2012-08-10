// Kepler.inc
//Copyright © 1999-2000 Kwan Systems
//You may use and modify this as you see fit for any non-commercial purpose
//otherwise contact me at chrisj@digiquill.com
//Chris Jeppesen - 19 Dec 2000

#include "KwanMath.inc"

/*Definition of Elements********\
 Ep    epoch of elements
 a     semi-major axis = q*(1+e)/(1-e*e)
 q     perihelion distance = a*(1-e*e)/(1+e)
 e     eccentricity
 i     inclination
 LAN   longitude of the ascending node
 AP    argument of perihelion = LP-LAN
 LP    longitude of perihelion = LAN+AP
 L     mean longitude=LAN+AP+M
 P     orbital period = sqrt(a*a*a)*EaP (from Keplers 3rd)
 n     Mean Daily Motion = 360/P 
 Tp    Time of perihelion passage
 M     mean anomaly = L-LP
                    = n*(T-Tp)
\*******************************/

/*Usage*************************\
#macro PosInSpace(Ep,A,E,I,LAN,AP,M,N,T)  
Parameters:
  Ep,A,E,I,LAN,AP,M,N: Orbital elements as defined above
  T: Time to calculate position for
Returns:
  Position vector of object at time T
Remarks:
  angles I, LAN, AP, M, and N are in DEGREES    

#macro TraceOrbit(A,E,I,LAN,AP,Thickness,TA1,TA2)  
Parameters:
  A,E,I,LAN,AP: Orbital elements as defined above
  Thickness: radius of cylinders used to construct the cylinder, in the same units as A
  TA1,TA2: True Anomaly to start and end orbit trace at
Usage:
  object {TraceOrbit(...) texture {SomeTex}}
\*******************************/

#macro RotX(V,Theta)
  #local Check=(vrotate(V,<Theta,0,0>));
  (Check)
#end

#macro RotY(V,Theta)
  #local Check=(vrotate(V,<0,Theta,0>));
  (Check)
#end

#macro RotZ(V,Theta)
  #local Check=(vrotate(V,<0,0,Theta>));
  (Check)
#end 

//from polar form of conic section equation, w/ focus at origin
#macro RadFromAnom(A,E,TA)
  (A * (1 - E * E)) / (1 + E * cos(TA))
#end

#macro Slice(Theta) 
  #local Theta=Constrain(0,360,Theta);
  #if(Theta>180)
    union {
  #else
    intersection {
  #end
    plane {
      -z,0
    }
    plane {
      z,0
      rotate y*-Theta
    }
  }
#end

//angles are in degrees
#macro TraceOrbit(A,E,I,LAN,AP,Thickness,TA1,TA2)  
  #local Theta=radians(TA1);
  #local Inc=pi/100;     
  #while(TA2<TA1)
    #local TA2=TA2+360;
  #end
  union {
    #if(radians(abs(TA1-TA2))<Inc) 
      #local R=RadFromAnom(A,E,radians(TA1));
      #local RR=RadFromAnom(A,E,radians(TA2)); 
      #if(R>0)
        sphere {
        <R*cos(radians(TA1)),0,R*sin(radians(TA1))>,Thickness
        }        
        #if(RR>0)
        cylinder {
        <R*cos(radians(TA1)),0,R*sin(radians(TA1))>,<RR*cos(radians(TA2)),0,RR*sin(radians(TA2))>,Thickness
        }
        #end
      #end
    #else
      #while(Theta+Inc<radians(TA2))          
        #local R=RadFromAnom(A,E,Theta);
        #local RR=RadFromAnom(A,E,Theta+Inc); 
        #if(R>0)
        sphere {
          <R*cos(Theta),0,R*sin(Theta)>,Thickness
        }        
        #if(RR>0)
          cylinder {
            <R*cos(Theta),0,R*sin(Theta)>,<RR*cos(Theta+Inc),0,RR*sin(Theta+Inc)>,Thickness
          }
        #end
        #end
        #declare Theta=Theta+Inc;
      #end
      #declare Theta=Theta-Inc;
      #local R=RadFromAnom(A,E,Theta);
      #local RR=RadFromAnom(A,E,radians(TA2)); 
      #if(R>0)
        sphere {
          <R*cos(Theta),0,R*sin(Theta)>,Thickness
        }        
        #if(RR>0)
          cylinder {
            <R*cos(Theta),0,R*sin(Theta)>,<RR*cos(radians(TA2)),0,RR*sin(radians(TA2))>,Thickness
          }
        #end
      #end
    #end
    rotate -y*AP
    rotate -x*I
    rotate -y*LAN
  }      
#end

//Eccentric Anomaly to Mean Anomaly
//Kepler's Equation M=E-e*sin(E)
#macro EccToMean(Ecc, E)
  #if(E < 1)
    (Ecc - E * sin(Ecc))
  #else
    (E * SinH(Ecc) - Ecc)
  #end
#end

#macro EccToAnom(Ecc,E)
   #if(E<1)
     (2*Atan(sqrt((1+E)/(1-E))*tan(Ecc/2)))
   #else
     (2*Atan(sqrt((E+1)/(E-1))*TanH(Ecc/2)))
   #end
#end

#macro AnomToEcc(Theta,E)
   #if(E<1)
     (2*Atan(sqrt((1-E)/(1+E))*tan(Theta/2)))
   #else
     (2*AtanH(sqrt((E-1)/(E+1))*tan(Theta/2)))
   #end
#end

//Kepler's Equation M=Ecc-E*sin(Ecc) solved for E
//Since it's trancendental, it can't be solved, and must be iterated
#macro MeanToEcc(M,E)
  #local Delta = 1e-10;
  #local Ecc2=0;
  #local Count=0;
  #local Ecc1 = M;
  #local Done=0;
  #if(M!=0) //Check for Short cut, also eliminate divide by zero errors when Ecc2 is calculated to be zero
    #while(Done=0)
      #if(E < 1)
        #local Ecc2 = M + E * sin(Ecc1);
      #else
        #local Ecc2 = AsinH((M + Ecc1) / E);
      #end
      #if(abs(1 - (Ecc1 / Ecc2)) < Delta)  
        #local Done=1;
      #end
      #local Ecc1 = Ecc2;
      #local Count = Count + 1;
    #end
  #end
  (Ecc2)  //Return value
#end
                   
#macro MeanToAnom(M,E)
  (EccToAnom(MeanToEcc(M,E),E))
#end

#macro AnomToMean(T,E)
  #local Ecc=(AnomToEcc(T,E));
  (EccToMean(Ecc,E))
#end

//Kepler's 3rd law
#macro AtoP(GM, A)
  //A^3=KP^2
  //k=A^3/P^2=GM/(4*Pi^2)
  //sqrt(A^3/K)=P
  #local K = GM / (4 * pi *pi);
  (sqrt(abs(A * A * A / K)))
#end

#macro PtoA(GM, P)
  //A^3=KP^2
  //A=(P^2*K)^(1/3)
  #local K = GM / (4 * pi *pi)
  (pow(K * P * P,1 / 3))
#end

//angles M and N are in DEGREES                   
#macro RTAInPlane(Ep,A,E,M,N,T,R,TA)
  //add mean daily motion to mean anomaly at Ep to get mean anomaly at T
  #local MM=M+N*(T-Ep);
  //convert M to radians
  #local MM=radians(MM);       
  //Get true anomaly from mean anomaly
  #declare TA=MeanToAnom(MM,E);  
  //get distance from center
  #declare R=RadFromAnom(A,E,TA); 
#end

//angles M and N are in DEGREES                   
#macro PosInPlane(Ep,A,E,M,N,T)
  #local TA=0;  
  #local R=0; 
  RTAInPlane(Ep,A,E,M,N,T,R,TA)
  (<R*cos(TA),0,R*sin(TA)>)  //return value
#end
    
//angles I, LAN, M, and N are in DEGREES    
#macro PosInSpace(Ep,A,E,I,LAN,AP,M,N,T)  
  #local P=PosInPlane(Ep,A,E,M,N,T);
  #local Q=RotY(P,-AP);
  #local R=RotX(Q,-I);
  (RotY(R,-LAN))
#end

#macro VelInPlane(Ep,A,E,M,N,T)
  //add mean daily motion to mean anomaly at Ep to get mean anomaly at T
  #local MM = M + N * (T - Ep);
  //convert M to radians
  #local MM = radians(MM);
  //Get true anomaly from mean anomaly
  #local TA = MeanToAnom(MM, E);
  #local V=<-radians(N) * A * sin(TA) / ((1 + E) *sqrt(1 - pow(E,2))),
             0,
             radians(N) * A * (cos(TA) + E) / sqrt(1 - pow(E,2))>;
  (V)
#end

#macro VelInSpace(Ep,A,E,I,LAN,AP,M,N,T)
  #local P = VelInPlane(Ep, A, E, M, N, T);
  #local Q=RotY(P, -AP);
  #local R=RotX(Q, -I);
  (RotY(R, -LAN))
#end



