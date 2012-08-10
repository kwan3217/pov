//webpage1.pov

camera {
  location <0,3,0>
  look_at <0,0,0>
}

#include "kepler.inc"
#include "colors.inc"

plane {
  y,0
  pigment {checker rgbf<1,1,1,0>, rgbf<0,0,0,0>}
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
            
#declare Ec=clock*2;
                   
sphere {
  0,0.1
  pigment {color Yellow}
}

object {            
  TraceOrbit(0.25,Ec,0,0,0,0.02)
  pigment {color Green}
}            

object {            
  TraceOrbit(0.50,Ec,0,0,0,0.02)
  pigment {color Yellow}
}            

object {            
  TraceOrbit(0.75,Ec,0,0,0,0.02)
  pigment {color Cyan}
}            

object {            
  TraceOrbit(1.0,Ec,0,0,0,0.02)
  pigment {color Magenta}
}            

text {
  ttf
  "verdana.ttf"
  concat("e = ",str(clock*2,0,3))
  0,0
  pigment {color Red}    
  scale 0.3
  rotate x*90
  translate <-1.9,0.03,-1.4>
}

PrintNumber("e: ",clock*2)                        