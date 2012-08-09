//TestWalk.pov

#include "KwanMath.inc"
#include "RandomWalk.inc"

#declare A=RandomWalk3D(2,101,1,0.02);


union {
  PrintVector("",A[0])
  sphere {
    A[0],0.01
  }
  #local I=1;
  #while(I<dimension_size(A,1))
    PrintVector("",A[I])
    cylinder{
      A[I-1],A[I],0.01
    }
    sphere {
      A[I],0.01
    }
    #local I=I+1;
  #end
  pigment {color rgb <1,1,0>}
}

camera {
  location <0.5,2,-5>
  look_at <0.5,0,0>
  angle 20
}

light_source {
  <20,20,-20>
  color 1.5
}
