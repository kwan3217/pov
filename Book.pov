#include "Book.inc"

#macro LH(V)
  (<V.x,V.y,-V.z>)
#end

cylinder {
  0,LH(Orient[frame_number][0]),0.1
  pigment {color rgb <1,0,0>}
}

cylinder {
  0,LH(Orient[frame_number][1]),0.1
  pigment {color rgb <0,1,0>}
}

cylinder {
  0,LH(Orient[frame_number][2]),0.1
  pigment {color rgb <0,0,1>}
}
        
camera {   
  sky LH(z)
  location LH(<0,-10,0>)
  look_at <0,0,0>
}

light_source {
  LH(<20,-20,20>)
  color rgb 1.5
}