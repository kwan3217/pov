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
                   
#declare Inc=60;       
#declare AP=30;
#declare LAN=clock*360;
                   
object {            
  TraceOrbit(0.25,0.5,Inc,LAN,AP,0.02)
  pigment {color Green}
}            

object {            
  TraceOrbit(0.50,0.2,Inc,LAN,AP,0.02)
  pigment {color Yellow}
}            

object {            
  TraceOrbit(1.00,0.50,Inc,LAN,AP,0.02)
  pigment {color Cyan}
}            

object {            
  TraceOrbit(1.0,1.2,Inc,LAN,AP,0.02)
  pigment {color Magenta}
}

cylinder {
  <0,0,0>,<0.75,0,0>,0.02
  pigment {color White}
  rotate -y*LAN
}            

text {
  ttf
  "verdana.ttf"
  concat(" = ",str(clock*360,0,1))
  0,0
  pigment {color Red}    
  scale 0.5
  translate <-0.65,0.03,1>
}

text {
  ttf
  "symbol.ttf"
  "W"
  0,0
  pigment {color Red}    
  scale 0.5
  translate <-0.95,0.03,1>
}

PrintNumber("LAN: ",clock*90)                        