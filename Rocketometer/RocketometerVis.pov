//CandaceII.inc
#version unofficial Megapov 1.22;
global_settings{right_handed}

#include "SimFilterRocketometer.csv"

#declare I=frame_number;
#declare T=q[frame_number][0];
#declare TLiftoff=0;
#declare TCutoff=50.22;
#declare Tdet=95;

#declare p_r=< -0.219619,-0.782875,0.582129>;

//this converts a quaternion to a matrix using the r_to=q'*r_from*q convention,
//then does a transpose because that's the way that POV wants to see it.

#macro quat(e)
  matrix <e.t*e.t+e.x*e.x-e.y*e.y-e.z*e.z,2*(e.x*e.y-e.t*e.z),2*(e.x*e.z+e.t*e.y),
          2*(e.x*e.y+e.t*e.z),e.t*e.t-e.x*e.x+e.y*e.y-e.z*e.z,2*(e.y*e.z-e.t*e.x),
          2*(e.x*e.z-e.t*e.y),2*(e.y*e.z+e.t*e.x),e.t*e.t-e.x*e.x-e.y*e.y+e.z*e.z,
          0,0,0>
#end

#declare NC_L=9+1/16;
#declare NC_rn=0.15;
#declare NC_R=1.5;
#declare NC_rho=(NC_R*NC_R+NC_L*NC_L)/(2*NC_R);
#declare NC_xo=NC_L-sqrt(pow(NC_rho-NC_rn,2)-pow(NC_rho-NC_R,2));
#declare NC_yt=NC_rn*(NC_rho-NC_R)/(NC_rho-NC_rn);
#declare NC_xt=NC_xo-sqrt(NC_rn*NC_rn-NC_yt*NC_yt);
#declare NC_xa=NC_xo-NC_rn;

#declare NoseCone=union {
  torus {
    NC_rho-NC_R,NC_rho
    clipped_by {cylinder {
      <0,0,0>,<0,NC_L-NC_xt,0>,NC_R+0.1
    }}
    hollow
  }
  sphere {
    <0,NC_L-NC_xo,0>,NC_rn
  }
  intersection {
    cylinder {
      <0,0,0>,<0,-2.875,0>,NC_R-1/32
    }
  }
  pigment {
    image_map {
      png "NoseCone.png"
      map_type cylindrical
    }
    scale <1,9,1>
    rotate y*180
  }
  finish {
    phong 1
  }
  translate <0,10,0>
}

#declare Fin=intersection {
  prism {
    -0.0625,0.0625,4
    <0,0>,<0,5>,<2.8125,5-4.125>,<2.8125,-1.125>
  }
  plane {
    y+0.15*z,0
    matrix <2.8125,0,-4.125,
            0,1,0,
            0,0,1,
            0,0,0>
    translate z*5
  }
  plane {
    y-0.15*z,0
    matrix <2.8125,0,-1.125,
            0,1,0,
            0,0,1,
            0,0,0>
  }
  plane {
    y+0.25*x,0
    translate x*2.8125
  }
  plane {
    -y+0.15*z,0
    matrix <2.8125,0,-4.125,
            0,1,0,
            0,0,1,
            0,0,0>
    translate z*5
  }
  plane {
    -y-0.15*z,0
    matrix <2.8125,0,-1.125,
            0,1,0,
            0,0,1,
            0,0,0>
  }
  plane {
    -y+0.25*x,0
    translate x*2.8125
  }
  pigment {
    gradient y
    color_map {
     [0 color rgb <1,1,1>]
     [0.5 color rgb <1,1,1>]
     [0.5 color rgb <1,1,1>*0.1]
     [1 color rgb <1,1,1>*0.1]
    }
  }
  finish {
    phong 1
  }
  rotate -x*90
  translate x*1.5
}
  
#declare Body=union {
  cylinder {
    <0,0,0>,<0,5,0>,1.5
    pigment {
      radial
      frequency 4
      color_map {
     [0 color rgb <1,1,1>]
     [0.5 color rgb <1,1,1>]
     [0.5 color rgb <1,1,1>*0.1]
     [1 color rgb <1,1,1>*0.1]
    }
  }
  }
  cylinder {
    <0,5,0>,<0,10,0>,1.5
    pigment {
      image_map {
        png "UpperBody.png"
        map_type cylindrical
      }
      scale <1,5,1>
      translate y*5
    }
  }
  finish {
    phong 1
  }
}

#declare Rocket=union {
#if(T<Tdet)
  object {Fin}
  object {Fin rotate y*180}
  object {Fin rotate y*90}
  object {Fin rotate y*270}
  object {Body}
#end
  object {NoseCone}
#if(T>TLiftoff & T<TCutoff)
  cone {
    <0,0,0>,0.5,<0,-10,0>,0
    pigment {color rgb <1,0.5,0>}
  }
#end
  translate -y*8
  rotate x*90
}

object {Rocket
  quat(<-q[I][10],-q[I][11],-q[I][12],q[I][13]>)
}

object {Rocket
  quat(<-q[I][10+33],-q[I][11+33],-q[I][12+33],q[I][13+33]>)
}
cylinder {
  0,x*100,0.1
  pigment {color rgb <1,0,0>}
}

cylinder {
  0,y*100,0.1
  pigment {color rgb <0,1,0>}
}

cylinder {
  0,z*100,0.1
  pigment {color rgb <0,0,1>}
}

cylinder {
  0,p_r*100,0.1
  pigment {color rgb <0.5,0,1>}
}

camera {
  right x*16/9
  sky z
  location <0,-30,0>
  look_at <0,0,0>
//  angle 25
}

light_source {
  <-2,-20,20>*1000
  color rgb <1,1,1>
}
