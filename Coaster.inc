#include "KwanMath.inc"
#include "bezier.inc"
#include "Track.inc"  //Track definition
#include "Car.inc"    //Simulation results

#macro DrawTrack()
  #declare I=0;
  #while(I<dimension_size(CoasterPoints,1))      
    cylinder {  
      CoasterPoints[I][0],CoasterPoints[I][1],0.05
      pigment {color rgb <1,0,0> }
    }
    cylinder {  
      CoasterPoints[I][1],CoasterPoints[I][2],0.05
      pigment {color rgb <1,0,0> }
    }
    cylinder {  
      CoasterPoints[I][2],CoasterPoints[I][3],0.05
      pigment {color rgb <1,0,0> }
    } 
    #local A=x;
    #local B=x;
    #local C=x;
    #local D=x;
    GetCoeff(CoasterPoints[I][0],CoasterPoints[I][1],CoasterPoints[I][2],CoasterPoints[I][3],A,B,C,D)
    union {
      PlotBezier(A,B,C,D,0.1,100)
      pigment {color rgb <1,1,0>}
    }
    #declare I=I+1;
  #end
#end

#declare I=frame_number;
sphere {
  Position[I],0.2
	pigment {color rgb <1,1,1>}
}
cylinder {
  Position[I],Position[I]+Velocity[I]*0.75,0.05
	pigment {color rgb <1,0.5>}
}
cone {
  Position[I]+Velocity[I]*0.75,0.1,Position[I]+Velocity[I],0
	pigment {color rgb <1,0.5>}
}

camera {
  location <20,20,20>
  look_at Position[I]
  angle 30
}

DrawTrack()

/*  
plane {
  y,0
  pigment {checker color rgb 1 color rgb 0}
}

plane {
  z,1
  pigment {checker color rgb 1 color rgb 0}
} 
*/

light_source {
  <20,20,-20>*10
  color rgb 2
}
                             
