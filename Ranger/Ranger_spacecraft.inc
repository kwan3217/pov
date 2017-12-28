#include "SpiceQuat.inc"

#macro Axis(L,R)
  cylinder {
    0,x*L,R
    pigment {color rgb x}
  }
  cylinder {
    0,y*L,R
    pigment {color rgb y}
  }
  cylinder {
    0,z*L,R
    pigment {color rgb z}
  }
  cylinder {
    0,-x*L,R
    pigment {color rgb <1,1,1>-x}
  }
  cylinder {
    0,-y*L,R
    pigment {color rgb <1,1,1>-y}
  }
  cylinder {
    0,-z*L,R
    pigment {color rgb <1,1,1>-z}
  }
#end

#macro FOV(centerLR,centerUD,FOVL,FOVR,FOVU,FOVD,W)
  difference {
    intersection {
      plane {
        -y,0
        rotate  x*(FOVU+W)
      }
      plane {
         y,0
        rotate -x*(FOVD+W)
      }
      plane {
         x,0
        rotate  y*(FOVL+W)
      }
      plane {
        -x,0
        rotate -y*(FOVR+W)
      }
    }
    intersection {
      plane {
        -y,0
        rotate  x*(FOVU)
      }
      plane {
         y,0
        rotate -x*(FOVD)
      }
      plane {
         x,0
        rotate  y*(FOVL)
      }
      plane {
        -x,0
        rotate -y*(FOVR)
      }
    }
    no_shadow
    rotate -x*centerUD
    rotate z*centerLR
  }
#end

#declare FOV_A=FOV(0.05,38+8.75,12.78,10.75,12.18,12.48,0.5)

#declare Ranger_Spacecraft=union {
//  Axis(1,0.025)
  //Omni antenna
  cylinder {
    <0,0,-0.6>,<0,0,-0.5>,0.05
  }
  //TV experiment case
  difference {
    cone {
      <0,0,-0.5>,0.06,<0,0,0>,0.1
    }
    //Camera reference axis
    cylinder {
      <0,0,0>,<0,0,1>,0.05
      rotate -x*38
      translate -z*0.4
    }
  }
  //Bus electronics boxes
  #local I=0;
  #while(I<6)
    box {
      <0.08,-0.08,0.0>,<0.15,0.08,0.12>
      rotate z*I*60
    }
    #local I=I+1;
  #end
  //Solar panels
  #local I=0;
  #while(I<2)
    box {
      <0.15,-0.12,0.12>,<0.6,0.12,0.121>
      pigment {color rgb <0.5,0,1>}
      rotate z*I*180
    }
    box {
      <0.15,-0.12,0.121>,<0.6,0.12,0.125>
      pigment {color rgb <1,1,1>}
      rotate z*I*180
    }
    #local I=I+1;
  #end
  //High gain antenna
  union {
    difference {
      #local R=0.3;
      sphere {
        <0,0,R>,R-0.12
      }
      sphere {
        <0,0,R>,R-0.13
      }
      plane {
        -z,-0.2
      }
    }
    cylinder {
      <0,0,0.12>,<0,0,0.2>,0.01
    }
    translate  y*sqrt(3)/2*0.15-z*0.2
    rotate x*122
    translate -y*sqrt(3)/2*0.15+z*0.2
  }
  pigment {color rgb <0.5,0.5,0.5>}
  finish {ambient 0.5}
}


