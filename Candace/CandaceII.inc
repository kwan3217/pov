//CandaceII.inc

#declare NC_L=9+1/16;
#declare NC_rn=0.15;
#declare NC_R=1.5;
#declare NC_rho=(NC_R*NC_R+NC_L*NC_L)/(2*NC_R);
#declare NC_xo=L-sqrt(pow(NC_rho-NC_rn,2)-pow(NC_rho-NC_R,2);
#declare NC_yt=NC_rn*(NC_rho-NC_R)/(NC_rho-NC_rn);
#declare NC_xt=NC_xo-sqrt(NC_rn*NC_rn-NC_yt*NC_yt);
#declare NC_xa=NC_xo-NC_rn;

#declare NoseCone=union {
  intersection {
    torus {
      NC_rho-NC_R,NC_rho
    }
    cylinder {
      <0,0,0>,<0,NC_L-NC_xt,0>,NC_r
    }
  }
  sphere {
    <0,NC_L-NC_xo,0>,NC_rn
  }
  pigment {color rgb <1,0,0>}
}

camera {
  location <0,2,-5>*3
  look_at <0,4.5,0>
}

light_source {
  <20,20,-20>*1000
  color rgb <1,1,1>
}
