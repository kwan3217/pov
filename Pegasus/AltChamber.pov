#include "KwanMath.inc"
#declare FlameClock=clock;
#declare Alt=clock*90000+11000;
PrintNumber("Alt: ",Alt)
#macro Temp(h)
  #if(h<11000) 
    #local T = 15.04 - 0.00649 * h+273.1;
  #else
    #if(h<25000)
      #local T = -56.46+273.1;
    #else
      #if(h<100000)
        #local T = -131.21 + 0.00299 * h+273.1;
      #else
        #local T=0;
      #end
    #end
  #end
  (T)
#end
#macro Pres(h)
  #local T=Temp(h);
  #if(h<11000) 
    #local p= 101.29 * pow((T / 288.08),5.256);
  #else
    #if(h<25000)
      #local p = 22.65 * exp (1.73 - 0.000157 * h);
    #else
      #if(h<100000)
        #local p = 2.488 * pow(T / 216.6,-11.388);
      #else
        #local p=0;
      #end
    #end
  #end
  (p)
#end

#macro Dens(h)
  #local T=Temp(h);
  #local p=Pres(h);
  #if(T>0)
    #local rho = p / (0.2869 * T);
  #else
    #local rho=0;
  #end
  (rho)
#end

background {color rgb <0,0.5,1>*Dens(Alt)/Dens(0)}
#declare FlameAtmDens=0.01;
#declare TailOffTime=clock;
PrintNumber("FlameAtmDens: ",FlameAtmDens)
#declare LitStage=1;

#include "Pegasus.inc"

global_settings {max_trace_level 50}

//plane {  -z,0	pigment {checker color rgb 1 color rgb 0}}

object {
  Pegasus
  rotate z*30
  translate <50,35,0>
}

text {
  ttf "timrom.ttf"
  concat("Alt: ",str(Alt/1000,0,3),"km") 0 0
  pigment {color rgb <1,0,0>}
  scale 10
  translate -y*10
}

text {
  ttf "timrom.ttf"
  concat("RelDens: ",str(FlameAtmDens,0,6)) 0 0
  pigment {color rgb <1,0,0>}
  scale 10
  translate -y*20
}

camera {
  location <0,0,-100>
  look_at <0,0,0>
}

light_source {
  <20,20,-20>*1000
  color rgb 1
}

plane {z,10 hollow pigment {checker color rgbf <1,1,1,1> color rgb <1,1,1> scale 5}}
