#include "colors.inc"

#debug "Here\n"

#ifndef(FlameClock)
  #local FlameClock=10;
#end

#local DensMap = density {
  radial  rotate y*90 translate z*-5
  translate <0,0,-15*FlameClock>
  warp {turbulence 0.8 octaves 3 lambda 2.5}
  translate <0,0,15*FlameClock>
  colour_map {
    [0.49  rgb 0]
    [0.495 rgb 1]
    [0.5   rgb 4]
    [0.505 rgb 1]
    [0.51  rgb 0]
  }
}
#local ColMap = density {
  radial rotate y*90 translate z*-5
  translate <0,0,-15*FlameClock>
  warp {turbulence 1.2 octaves 3 lambda 2.5}
  translate <0,0,15*FlameClock>
  colour_map {
    [0.495 rgb <1,1,0>]
    [0.5   rgb <1,1,1>]
    [0.505 rgb <1,1,0>]
  }
}

#local DensEnding = density {
  spherical scale 10
  colour_map {
    [0     rgb 0*<1,0,0>]
    [0.5   rgb <1,.5,0>*.5]
    [0.75  rgb <1,1,0>]
    [0.875 rgb 1]
    [1     rgb <-1,0,1>]
  }
}

#local DensMap2 = density {
  radial rotate y*90 translate z*-3
  translate <0,0,-25*FlameClock>
  warp {turbulence 1.3 octaves 3 }
  translate <0,0,25*FlameClock>
  colour_map {
    [0.45 rgb 0]
    [0.48 rgb 0.4]
    [0.5 rgb 1]
    [0.52 rgb 0.4]
    [0.55 rgb 0]
  }
}

#local ColMap2 = density {
  radial rotate y*90 translate z*-3
  translate <0,0,-25*FlameClock>
  warp {turbulence 1.3 octaves 3 }
  translate <0,0,25*FlameClock>
  colour_map {
    [0.47 Yellow]
    [0.5  White]
    [0.53 Yellow]
  }
}

#local DensEnding2 = density {
  spherical scale <5,5,10>
  translate <0,0,-15*FlameClock>
  warp {turbulence 0.5}
  translate <0,0,15*FlameClock>
  colour_map {
    [0     rgb 0]
    [0.1   rgb 1]
    [0.875 rgb 1]
    [1     rgb <1,1,-1>]
  }
}

#local numLights=5;
#local FlameLights= union {
  #local i=0;
  #while (i<10)
    #local i = i + 10/numLights;
    light_source {
      z*i
      color <1,0,0>*1.9/numLights
      media_interaction off
      fade_distance 5 fade_power 0.8
    }
    light_source {
      z*i
      color <0,1,0>*1.5/numLights
      media_interaction off
      fade_distance 5.5 fade_power 4
    }
  #end
}

#declare Flame = union {
  #debug "Here2\n"
  object {FlameLights}
  cylinder {
    0,z*3,3
    pigment {Clear}
    hollow
    interior {
      media {
        emission 1
        density {ColMap}
        density {DensMap}
        density {DensMap rotate z*90}
        density {DensEnding}
        scale .8
      }
      media {
        emission .75
        density {ColMap2}
        density {DensMap2}
        density {DensMap2 rotate z*90}
        density {DensEnding2}
        scale .8
      }
    }
    scale <1,1,1>/.8
	}
}

