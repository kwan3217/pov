#include "Pegasus.inc"
#undef FlameClock
#include "KwanMath.inc"
#ifndef(FlameClock) #declare FlameClock=clock*5; #end
#ifndef(FlameAngle) #declare FlameAngle=clock*15; #end
#ifndef(FlameStretch) #declare FlameStretch=5; #end
#ifndef(FlameScale) #declare FlameScale=3; #end
PrintNumber("FlameClock: ",FlameClock)

#declare S=seed(FlameClock*47);

union {
  union {
    #declare Inner=0.8;
    #declare Outer=1.0;
    #declare Steps=10;
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
        pigment {
   			  gradient x
					scale 20
					translate -x*10
				  pigment_map {
  					[0.52 bozo
    				  turbulence 0.1
    	  			color_map {
	    	  		  [Linterp(0,0.0,Steps,0.5,I) color rgbf <1,1,1,1>]
		    	  	  [Linterp(0,0.0,Steps,0.5,I)+0.1 color rgbf <0.8,0.8,0.75,0.8>]
			    	  }
  				  	scale 0.1
  			  	  translate -x*FlameClock*100
  						scale 1/20
    	  		]
		  			[0.53 color rgbf <1,1,1,1>]
          }
				}
	  	  no_shadow
    	}
      #declare I=I+1;
    #end
    rotate -z*degrees(atan(tan(radians(FlameAngle))*FlameStretch))
    translate -x*1
  }

  sphere {
    <0, 0, 0>, 0.999
//		clipped_by {plane {y,0}}
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
            [ 0 color rgb <0, 0, 0>      ]
            [ 0.1 color rgb <1, 1, 0.5>  ]
            [ 0.875 color rgb <1, 1, 1>  ]
            [ 1 color rgb <1, 1, -1>     ]
          }
        }
        emission rgb <1, 1, 1>
				translate x*0.5
      }
    }
    no_shadow
    hollow
  	translate -x
  }
	#declare R=1+(rand(S)-0.5)*0.1;
  scale <FlameStretch/R,1,1>*FlameScale*R
	translate x*1.0
	rotate z*FlameAngle
}
camera {
  location <0,0,-50>
	look_at <0,0,0>
}

light_source {
  <20,20,-20>
	color rgb 1
}

global_settings {max_trace_level 50}

//plane {  -z,0	pigment {checker color rgb 1 color rgb 0}}

#declare Pegasus=union {
object {
  Pegasus1
}
object {
  Pegasus1Inter
}
object {
  Pegasus2
}
object {
  Pegasus3
}

object {
  Avionics
}
object {
  PegasusFairingLeft
}

object {
  PegasusFairingRight
}
#ifdef(Aim) 
  object {
    Aim 
    rotate z*90 
    translate 14.755*x
  } 
#end
}

object {
  Pegasus
	rotate z*FlameAngle
}
