#include "colors.inc"

camera {
  location <6,5,10>*4
  look_at <0,-20,0>
}
light_source {
  <1,2,1>*100000000
  color White*0.3
}

#declare Turb=0;

#declare DensMap = density {
  radial  
  rotate y*90 
  translate z*-5
  translate <0,0,-15*clock>
  #if(Turb)
  warp {
    turbulence 0.8
    octaves 3 
    lambda 2.5
  }
  #end
  translate <0,0,15*clock>
  scale <1,1,1>
  colour_map {
    [0.49 rgb 0]
    [0.495 rgb 1]
    [0.5 rgb 4]
    [0.505 rgb 1]
    [0.51 rgb 0]
  }
}

#declare ColMap = density {
  radial 
  rotate y*90 
//  translate z*-5
  translate <0,0,-15*clock>
  #if(Turb)
  warp {
    turbulence 1.2 
    octaves 3 
    lambda 2.5
  }
  #end	  
  translate <0,0,15*clock>
  scale <1,1,1>
  color_map {
    [0.495 Yellow]
    [0.5 White]
    [0.505 Yellow]
  }
}
#declare DensEnding = density {
  spherical 
  scale 10
  color_map {
    [0 rgb 0*<1,0,0>]
    [0.5 rgb <1,.5,0>*.5]
    [.75 rgb <1,1,0>]
    [.875 rgb 1]
    [1 rgb <-1,0,1>]
  }
}

#declare DensMap2 = density {
  radial 
  rotate y*90 
  translate z*-3
  translate <0,0,-25*clock>
  #if(Turb)
  warp {
    turbulence 1.3 
    octaves 3 
  }
  #end	  
  translate <0,0,25*clock>
  scale <1,1,1>
  color_map {
    [0.45 rgb 0]
    [0.48 rgb 0.4]
    [0.5 rgb 1]
    [0.52 rgb 0.4]
    [0.55 rgb 0]
  }
}
#declare ColMap2 = density {
  radial 
  rotate y*90 
  translate z*-3
  translate <0,0,-25*clock>
  #if(Turb)
  warp {
    turbulence 1.3 
    octaves 3 
  }
  #end	  
  translate <0,0,25*clock>
  scale <1,1,1>
  color_map {
    [0.47 Blue]
    [0.5 Cyan]
    [0.53 Blue]
  }
}

#declare DensEnding2 = density {
  spherical scale <5,5,10>
  translate <0,0,-15*clock>
  #if(Turb)
  warp {
    turbulence 0.5
  }
  #end	  
  translate <0,0,15*clock>
  color_map {
    [0 rgb 0]
    [0.1 rgb 1]
    [.875 rgb 1]
    [1 rgb <-1,-1,1>]
  }
}

#declare Flame=union {
  //Flame
  intersection {
    sphere {
      0,1
      scale <1,1,10>
    }
    cylinder {
      0,z*10,1
    }
    pigment {color rgbf <1,1,1,0.8> /*Clear*/}
    hollow
    interior {
      media {
        emission 1
        intervals 5
        samples 2, 30
        confidence 0.99
        variance 1/10
        density {ColMap}
        density {DensMap}
        density {DensMap rotate z*90}
        density {DensEnding}
        scale .8
      }
      media {
        emission .75
        intervals 5
        samples 2, 30 
        confidence 0.99
        variance 1/10
        density {ColMap2}
        density {DensMap2}
        density {DensMap2 rotate z*90}
        density {DensEnding2}
        scale .8
      }
    }
    scale <1,1,3>/.8
  }

  //Smoke
  cylinder {
    0,z*10,3

    pigment {color rgbf <1,1,1,0.8> /*Clear*/}
    hollow
    interior {
      media {
        absorption rgb .675
        //scattering { 2, rgb .5 extinction 1 }
        density {
	  bozo
          translate <0,0,-5*clock>
  #if(Turb)
          warp {
	    turbulence 0.2 
	    octaves 1 
	    lambda .5
	  }
  #end	  
          translate <0,0,5*clock>
          scale <1,1,1/3>*.75
          color_map {
            [0 rgb 0]
            [1 rgb 1]
          }
        }
        density {
          spherical 
	  scale <5,5,10>
          translate <0,0,-5*clock>
  #if(Turb)
          warp {
	    turbulence 0.5
	  }
  #end	  
          translate <0,0,5*clock>
          color_map {
            [0 rgb 0]
            [1 rgb 1]
          }
        }
        scale .8
      }
    }
    scale <.675,.675,2>/.8
    translate <0,0,20>
  }
  rotate x*90
}

object{Flame}

#declare numLights=10;
union {
  #declare i=0;
  #while (i<10)
    #declare i = i + 10/numLights;
    light_source {
      z*i
      color Red*1.9/numLights
      media_interaction off
      fade_distance 5 
      fade_power 0.8
    }
    light_source {
      z*i
      color Green*1.5/numLights
      media_interaction off
      fade_distance 5.5 
      fade_power 4
    }
  #end
  rotate -x*30
  rotate x*90
}

background {
  rgb 0.5
}