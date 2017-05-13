#include "KwanMath.inc"
#include "LocLook.inc"

//#declare OutAspect=4/3;
#declare OutAspect=image_width/image_height;

#if(clock<11) 
  #include "SceneA.inc"
#else
  #include "SceneB.inc"
#end
