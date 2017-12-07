//View from the EXI instrument
#include "exi_common.inc"

//object {EMM_Spacecraft QuatTrans(SCQ,<0,0,0>)}
object {SkyGrid}
object {ViewFrame}

camera {
  #declare Up=y*1;
  #declare Right=-x*image_width/image_height;
  PrintVector("Up:    ",Up)
  PrintVector("Right: ",Right)
  PrintNumber("FoV:   ",EXI_FOV)
  PrintNumber("Dir:   ",0.5*vlength(Right)/tan(radians(EXI_FOV/2)))
  PrintNumber("FoVV:  ",EXI_FOV_vert)
  PrintNumber("FoVn:  ",EXI_FOV*3/4)
  up Up
  right Right
  angle EXI_FOV
  sky QuatTransV(EXIQ,<0,0,0>,y)
  location <0,0,0>
  look_at QuatTransV(EXIQ,<0,0,0>,z)
}


