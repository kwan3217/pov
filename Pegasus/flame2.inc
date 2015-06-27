#include "KwanMath.inc"
#ifndef(TailOffTau) #declare TailOffTau=0.2; #end
#ifndef(TailOffTime) #declare TailOffTime=0; #end
#ifndef(TailOff) #declare TailOff=1-exp(-TailOffTime/TailOffTau); #end
#if(TailOff>0.999) #declare TailOff=1; #end
#ifndef(FlameAtmDens) #declare FlameAtmDens=0.2; #end
#if(FlameAtmDens>0.001) #declare Smoke=1; #end
#ifndef(FlameClock) #declare FlameClock=0; #end
#ifndef(FlameAngle) #declare FlameAngle=0; #end
#ifndef(FlameStretch) #declare FlameStretch=5*(1+(1-FlameAtmDens)*0.5); #end
#ifndef(FlameScale) #declare FlameScale=3*(1+(1-FlameAtmDens)*3); #end
#ifndef(FlameDens) #declare FlameDens=(0.1+0.9*FlameAtmDens)*(1-TailOff); #end
PrintNumber("FlameClock:   ",FlameClock)
PrintNumber("FlameAngle:   ",FlameAngle)
PrintNumber("FlameStretch: ",FlameStretch)
PrintNumber("FlameScale:   ",FlameScale)
PrintNumber("FlameDens:    ",FlameDens)

#declare S=seed(FlameClock*47);

#declare Flame=
union {
  #ifdef(Smoke) 
  union {
    #declare Outer=1.0;
    #ifdef(Quick)
      #declare Inner=Outer;
      #declare Steps=1;
    #else
      #declare Inner=0.8;
      #declare Steps=10;
    #end
    #declare I=0;
    #while(I<=Steps) 
      union {
        cylinder {
  	      <0,0,0>,<-10,0,0>,Linterp(0,Inner,Steps,Outer,I)
  	  	  open
	  	  	hollow
  	  	}
	  	  sphere {
		      <0,0,0>,Linterp(0,Inner,Steps,Outer,I)
					clipped_by {
					  plane {-x,0}
					}
    			hollow
	    	}
        #ifdef(Quick)
          pigment {color rgb <1,1,1>}
        #else
        pigment {
   			  gradient x
					scale 20
					translate -x*10
				  pigment_map {
  					[0.52 bozo
    				  turbulence 0.1
    	  			color_map {
	    	  		  [Linterp(0,0.0,Steps,0.5,I) color rgbf <1,1,1,1>]
		    	  	  [Linterp(0,0.0,Steps,0.5,I)+0.1 color rgbf <1,1,1,1>-<0.2,0.2,0.25,0.2>*FlameAtmDens]
			    	  }
  				  	scale 0.1
  			  	  translate -x*FlameClock*100
  						scale 1/20
    	  		]
		  			[0.53 color rgbf <1,1,1,1>]
          }
				}
        #end
  			finish {ambient 0.5}
	  	  no_shadow
    	}
      #declare I=I+1;
    #end
    rotate -z*degrees(atan(tan(radians(FlameAngle))*FlameStretch))
    translate -x*1
  }
  #end
  #if(TailOff<0.999)
  sphere {
    <0, 0, 0>, 0.999
//		clipped_by {plane {y,0}}
    #ifdef(Quick)
    pigment {color rgb <1,1,0>}
    #else
    pigment {
      color rgbf <1, 1, 1, 1>		
    }
    interior {
      media {
        density {
          spherical
          translate -x*FlameClock*200
          warp { turbulence 0.25 }
          translate x*FlameClock*200
          color_map {
            [ 0 color rgb <0, 0, 0>*FlameDens      ]
            [ 0.1 color rgb <1, 1, 0.5+min(TailOff*1,0.5)>*FlameDens  ]
            [ 0.875 color rgb <1, 1, 1> *FlameDens ]
            [ 1 color rgb <1, 1, -1+min(2,TailOff*4)>*FlameDens     ]
          }
        }
        emission rgb <1, 1, 1>
				translate x*(0.5+(1-FlameDens)*0.7)
      }
    }
    #end
    no_shadow
    hollow
  	translate -x
  }
  #end
	#declare R=1+(rand(S)-0.5)*0.1;
//  #declare R=1;
  scale <FlameStretch/R,1,1>*FlameScale*R
}
