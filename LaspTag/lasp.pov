#include "snoe.inc"  
#include "Stars.inc"
object {Stars}
#declare sec=clock*5;
#declare LogoFadeIn=BLinterp(2,0,3,1,sec);
PrintNumber("Sec:        ",sec)
PrintNumber("LogoFadeIn: ",LogoFadeIn) 

#declare Fade=ASDR(0,0.5,4.5,5,0,1,sec);
PrintNumber("Fade:",Fade)

#if(Fade<1)
  sphere {
    <0,0,0>,0.0001 hollow
    pigment {color rgbf <1,1,1,Fade>}
    finish {ambient 0 diffuse 0 specular 0}
  }
#end

#if(LogoFadeIn>0)
#declare LogoTransmit=1-LogoFadeIn;
#include "NewLASPLogoFull.inc"
#include "LocLook.inc"

union {
  object {
    AllShapes scale 1/AllShapes_WIDTH   
    rotate -x*90
    scale 10
    translate <-8,2.5,10> 
    scale 0.01
  }                      
  no_shadow
  LocationLookAt(<0,0,0>,<-4,0,10>,vnormalize(y-x*sec*0.1+x))
}
#end

object {
  SNOE  
  rotate z*90
  rotate x*30*sec
  translate -x*4
  translate z*sec*5
  no_shadow
}
camera {
  right x*16/9
  location <0,0,0>
  look_at <-4,0,10>
  sky vnormalize(y-x*sec*0.1+x)
}  

sphere {
  <0,-6470,0>,6370
  pigment {color rgb <0.3,0.3,1>}
}

sphere {
  <0,-6470,0>,6375
  texture{ 
    pigment { 
      bozo turbulence 0.65
      octaves 6  omega 0.7 lambda 2 
      color_map { 
        [0.0  color rgb <0.95, 0.95, 0.95>*0.5 ]
        [0.2  color rgb <1, 1, 1>*2 ]
        [0.45 color rgb <0.85, 0.85, 0.85> ]
        [0.6 color rgbt <1, 1, 1, 1>*1 ]
        [1.0 color rgbt <1, 1, 1, 1>*1 ]
      } // end color_map
      scale 100
    }
  } // end texture 2
}

light_source {  
  <0,5,-10>*1e8
  color rgb 1
}

