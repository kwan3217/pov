#version unofficial Megapov 1.22;
global_settings {right_handed}
#include "SpiceQuat.inc"
#include "Voyager.inc"

#declare MarkerTex=texture {
  pigment {color rgb <1,0,1>}
}

#declare VoyagerFull=union {
  union {
  #local I=0;
  #while(I<dimension_size(partArray,1))
    #local DoIt=1;
    #local J=0;
    #while(J<dimension_size(RBF,1))
      #if(I=RBF[J])
        #local DoIt=0;
      #end
      #local J=J+1;
    #end
    #local J=0;
    #while(J<dimension_size(Az,1))
      #if(I=Az[J])
        #local DoIt=0;
      #end
      #local J=J+1;
    #end
    #local J=0;
    #while(J<dimension_size(ScanPlatform,1))
      #if(I=ScanPlatform[J])
        #local DoIt=0;
      #end
      #local J=J+1;
    #end
#if(DoIt)
    object{partArray[I] 
#if(I=clock)
  texture {MarkerTex}
#else
  texture {materialArray[I]}
#end
  }
#end
    #local I=I+1;
  #end
  transform MeshToStd
  }
  union {
    cylinder {0, x  ,0.02 pigment {color rgb x}} 
    cylinder {0,-x  ,0.02 pigment {color rgb <1,1,1>-x}} 
    cylinder {0, y  ,0.02 pigment {color rgb y}} 
    cylinder {0,-y  ,0.02 pigment {color rgb <1,1,1>-y}} 
    cylinder {0, z*5,0.02 pigment {color rgb z}}
    cylinder {0,-z  ,0.02 pigment {color rgb <1,1,1>-z}}
    translate SPCenter
  } 


}

#declare VoyagerOnly=object {
  partArray[clock] texture {materialArray[clock]}
  transform MeshToStd
}

object {
  VoyagerFull
  rotate z*90
  rotate y*180
  translate <-4.0,0,0>
}               

object {
  VoyagerOnly
  rotate z*90
  rotate y*180
  translate <-3.0,0,0>
}               

object {
  VoyagerFull
  rotate z*90
  rotate y*180
  rotate x*90
  translate <-5,0,-3>
}               

object {
  VoyagerOnly
  rotate z*90
  rotate y*180
  rotate x*90
  translate <5,0,-3>
}               

camera {
  orthographic
  up y*1.5
  right x*16/9*1.5
  location <0,-8,0>*10
  look_at <0,0,0>
  sky z
}     

background {color rgb <0,0.5,1>}

light_source {
  <0,-5,0>*1000
  color rgb 1
}
