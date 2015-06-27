//plantest.pov
//Copyright © 1999 Kwan Systems
//You may use and modify this as you see fit for any non-commercial purpose
//otherwise contact me at chrisj@digiquill.com
//Chris Jeppesen - 8 Nov 2000

#include "PlanetMod.inc"  
#include "Terminal.inc"          

#declare I=0;
#declare J=0;
#while(J<=999)     
  #if(PlanetIncluded[J])
    object {
      PlanetModel[J]
      scale 1/APlanet[J]    //for equal sized spheres
      //scale 1/APlanet[599]    //for proportional sizes
      rotate y*90 
      rotate y*clock*360
      rotate -x*20   
      translate <mod(I,8)-3.5,-floor((I)/8)+2.5,0>*2
    }
    #declare I=I+1;
  #end
  #declare J=J+1;
#end

light_source {
  <0,0,-20000>   
  color 1.5
}

camera {
  location <0,0,-100>
  look_at <0,0,0>  
  angle 10
}

                                  
