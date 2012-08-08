#include "KwanMath.inc"
#include "LocLook.inc"
#declare Aeroshell=#include "MSLAeroshell2.inc"
#declare State=#include "msl_edl2.inc"

#macro Vec(I,J)
  (<State[I][J+0],State[I][J+1],State[I][J+2]>)
#end

#macro R(I)  (Vec(I, 2)) #end
#macro V(I)  (Vec(I, 5)) #end
#macro A(I)  (Vec(I, 8)) #end
#macro S(I)  (Vec(I,11)) #end
#macro E(I)  (Vec(I,14)) #end
#macro rho(I)(State[I][17]) #end
#macro agl(I)(State[I][18]) #end
#macro alt(I)(State[I][19]) #end
#macro csound(I)(State[I][20]) #end
#macro Alpha(I) 
  PrintNumber("Alpha(I) I:",I)
  #if(I<50*24)
    #local result=(State[50*24][21]);
  #else
    #local result=(State[I][21]);
  #end
(result)
#end
#macro bank(I) 
  #if(I<50*24)      
//    (0)
    #local result=(State[50*24][22]);
  #else
    #local result=(State[I][22]);
  #end
(result)
#end

#macro meanBank(I)
  #local J=max(0,I-24);
  #local acc=0;
  #local n=0;
  #while(J<min(I+24,9999))
    #local acc=acc+bank(I)*ASDR(I-24,I,I,I+24,0,1,J);
    #local n=n+ASDR(I-24,I,I,I+24,0,1,J);
    #local J=J+1;
  #end
  (acc/n)
#end

//Local vertical vector. In this model, we use a spherical reference surface 3396km in radius, so
//local vertical is parallel to planetocentric position
#macro L(I)
  (vnormalize(R(I)))
#end
           
#macro Ea(I)
  (vnormalize(vcross(z,R(I))))
#end
           
#macro No(I)
  (vnormalize(vcross(Ea(I),R(I))))
#end
           
//Tangential vector, parallel to Vrel           
#macro T(I)
  (vnormalize(V(I)))
#end

//Side vector, perpendicular to both L and T, so in local horizon plane
#macro W(I)
  (vnormalize(vcross(L(I),T(I))))
#end

//Normal vector, perpendicular to both T and W, towards local vertical
#macro N(I)
  (vnormalize(vcross(W(I),T(I))))
#end

//Non-gravitational acceleration in drag frame. Components are parallel to T,W,N in that order
#macro AD(I)
  (<vdot(T(I),A(I)),vdot(W(I),A(I)),vdot(N(I),A(I))>)
#end

#declare TT=frame_number/24; 
#declare TT0=264;

#include "MSLChute.inc"

object{Aeroshell}
object {MSLChute(TT+TT0,frame_number+TT0*24) translate z*1.9}

camera {
  up y
  right x*image_width/image_height
  location <-5,2,0>*50+z*(20)
  look_at <0,0,20>
  angle 20
  
}

light_source {
  <-20,20,20>*1000
  color rgb <1,1,1>
}



