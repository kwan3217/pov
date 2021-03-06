#include "SpiceQuat.inc"

#declare Axis=union {
  cylinder {
    0,x,0.1
    pigment {color rgb x}
  }
  cylinder {
    0,y,0.1
    pigment {color rgb y}
  }
  cylinder {
    0,z,0.1
    pigment {color rgb z}
  }
  cylinder {
    0,-x,0.1
    pigment {color rgb <1,1,1>-x}
  }
  cylinder {
    0,-y,0.1
    pigment {color rgb <1,1,1>-y}
  }
  cylinder {
    0,-z,0.1
    pigment {color rgb <1,1,1>-z}
  }
}

#declare EMM_Spacecraft=union {
  //spacecraft bus
  box {
    <-0.5,-0.5,-0.5>,<0.5,0.5,0.5>
    pigment {rgb <0.5,0.5,0.5>}
  }
  object {Axis}
  //antenna
  sphere {
    #declare R=3;
    0,R
    pigment {color rgb <0.5,0.5,0.5>}
    clipped_by {plane {z,-(R-1)}}
    translate z*R
    scale 0.25
    translate z*0.1
    rotate y*23
    translate z*0.7
  }
  //panels
  box {
    <0.55,-0.4,0.48>,<1.45,0.4,0.5>
    pigment {color rgb <0,0,1>}
  }
  box {
    <1.55,-0.4,0.48>,<2.45,0.4,0.5>
    pigment {color rgb <0,0,1>}
  }
  box {
    <-0.55,-0.4,0.48>,<-1.45,0.4,0.5>
    pigment {color rgb <0,0,1>}
  }
  box {
    <-1.55,-0.4,0.48>,<-2.45,0.4,0.5>
    pigment {color rgb <0,0,1>}
  }
  //EXI instrument 
  object {
    Axis
    scale 0.4
    QuatTrans(pxform("HOPE_EXI","HOPE_SPACECRAFT",0),<-0.4,+0.5,0>)
  }
  object {
    Axis
    scale <0.2,0.2*3/4,0.2>
    QuatTrans(pxform("HOPE_EXI_VIS","HOPE_SPACECRAFT",0),<-0.45,+0.6,-0.1>)
  }
  object {
    Axis
    scale <0.2,0.2*3/4,0.2>
    QuatTrans(pxform("HOPE_EXI_UV","HOPE_SPACECRAFT",0),<-0.45,+0.6,0.1>)
  }
}


