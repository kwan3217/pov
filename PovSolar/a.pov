//A.pov

camera {
  location <0,3,0>
  look_at <0,0,0>
}

#include "kepler.inc"
#include "colors.inc"

plane {
  y,0
  pigment {checker White, Black}
  scale 1/4
}

cylinder {
  <0,0,-10>,<0,0,10>,0.02
  pigment {color Red}
}

cylinder {
  <-10,0,0>,<10,0,0>,0.02
  pigment {color Blue}
}                    

light_source {
  <20,20,20>
  color White*1.5
}
            
object {            
  TraceOrbit(clock+0.5,0.00,0,0,0,0.02,0,360)
  pigment {color Green}
}            

object {            
  TraceOrbit(clock+0.5,0.25,0,0,0,0.02,0,360)
  pigment {color Yellow}
}            

object {            
  TraceOrbit(clock+0.5,0.50,0,0,0,0.02,0,360)
  pigment {color Cyan}
}            

object {            
  TraceOrbit(clock+0.5,0.75,0,0,0,0.02,0,360)
  pigment {color Magenta}
}            

sphere {
  0,0.1
  pigment {color Yellow}
}

text {
  ttf
  "verdana.ttf"
  concat("a = ",str((clock+0.5)*4,0,3))
  0,0
  pigment {color Red}    
  scale 0.3
  rotate x*90
  translate <-1.9,0.03,-1.4>
}