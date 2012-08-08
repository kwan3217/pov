//CandaceII.inc

#include "q.inc"

#declare T=q[0][4]+clock;
#declare TLiftoff=1636;
#declare TCutoff=1638.4;
#declare Tdet=1642.65;
#declare I=0;
#while(q[I][4]<T)
  #declare I=I+1;
#end

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

union {
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
  translate -y*10
  rotate z*90
  quat(<q[I][1],q[I][0],q[I][2],q[I][3]>)
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
