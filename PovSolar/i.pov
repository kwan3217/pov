//i.pov

camera {
  location <clock*3-1.5,1.5,-1.5>
  look_at <0,0,0>
}

#include "kepler.inc"
#include "colors.inc"

plane {
  y,0.02
//  pigment {checker rgbf<1,1,1,1>, rgbf<1,1,1,0.5>}
  pigment {rgbf <0.3,0.3,1,0.5>}
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

cylinder {
  <0,-10,0>,<0,10,0>,0.02
  pigment {color Green}
}                    

sphere {
  0,0.1
  pigment {color Yellow}
}


light_source {
  <20,20,-20>
  color White*1.5
}
                   
#declare Inc=clock*90;
                   
object {            
  TraceOrbit(0.25,0.5,Inc,0,0,0.02,0,360)
  pigment {color Green}
}            

object {            
  TraceOrbit(0.50,0.2,Inc,135,0,0.02,0,360)
  pigment {color Yellow}
}            

object {            
  TraceOrbit(0.75,0,Inc,90,0,0.02,0,360)
  pigment {color Cyan}
}            

object {            
  TraceOrbit(-1.0,1.2,Inc,45,0,0.02,0,360)
  pigment {color Magenta}
}            

text {
  ttf
  "verdana.ttf"
  concat("i = ",str(clock*90,0,1))
  0,0
  pigment {color Red}    
  scale 0.5
  translate <-0.95,0.03,1>
}

PrintNumber("i: ",clock*90)                        