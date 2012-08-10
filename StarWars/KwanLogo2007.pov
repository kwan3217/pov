#include "KwanMath.inc"
#include "LocLook.inc"

#version unofficial Megapov 1.22;

#declare OutAspect=4/3;

#if(clock<11) 
  #include "SceneA.inc"
#else
  #include "SceneB.inc"
#end
