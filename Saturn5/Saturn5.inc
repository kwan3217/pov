#declare Hemisphere=sphere {
  0,1
  clipped_by {cylinder {<0,0,0>,<0,1.001,0>,1.001}}
}

#macro Stringers(Ymin,Ymax,Rad,Num)
  #local I=0;
  #while(I<Num)
    box {
      <-1.5*Rad/(396.8/2),Ymin,-Rad>,<1.5*Rad/(396.8/2),Ymax,-Rad-1.5*Rad/(396.8/2)>
      rotate y*I*360/Num
    }
    #declare I=I+1;
  #end
#end

//All units in the plans this is based upon are inches.
//The Saturn V vehicle has a maximum station of 4240.79 to the top of the escape tower,
//and a minimum of -115.36 at the bottom of the engine bells,
//for a total height of 4356.15 inches, 363.0125 feet, 110.64621m
//The finished model is scaled in meters, the standard length unit of all
//spacecraft models
#include "S-IC.inc"
#include "S-II.inc"
#include "S-IVB.inc"

#declare Saturn5=union {
//  object {S1C hollow}
//  object {Interstage}
  object {S2}
  object {S4B}
  object {Spacecraft}
  object {BPC_LES}
  
  translate y*115.36 //put the bottom of the engine bells at station 0
  scale 1/12*0.3048
  rotate y*180
  hollow
}
