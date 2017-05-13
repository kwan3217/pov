//poolcue.pov 
#include "colors.inc"
#include "woods.inc"
#include "metals.inc"

/*
#declare CueAt=<1,1,1>;
#declare CuePointAt=<0,2,0>;
#declare CuePullBack=(1-clock)*5;
*/
#declare PoolCueTex=texture {
  gradient y
  texture_map {
    [0.0 pigment {color <0,0.75,1>}]
    [1.05/15 pigment {color <0,0.75,1>}]
    [1.05/15 pigment {color White}]
    [1.3/15 pigment {color White}]
    [1.3/15 T_Wood13]
    [0.4 T_Wood11]
    [0.59 T_Wood11]
    [0.59 T_Gold_5A]
    [0.61 T_Gold_5A]
    [0.61 T_Wood14]
    [1.0 T_Wood14]
  }
}

//Scene Starter 

#declare Ny=vnormalize(CuePointAt-CueAt);
#declare Nx=vnormalize(vcross(Ny,z));
#declare Nz=vcross(Nx,Ny);
         
#declare PoolCue=object {
  cone {
    <0,-1,0>,0.06,<0,-14.99,0>,0.3
    texture {
      PoolCueTex
      scale <1,15,1>
    }
  }
  scale 2 
  translate -y*CuePullBack
  matrix <Nx.x,Nx.y,Nx.z,
          Ny.x,Ny.y,Ny.z,
          Nz.x,Nz.y,Nz.z,
          CueAt.x,CueAt.y,CueAt.z>
  bounded_by {
    box {<WallX[0],Floor[0],WallZ[0]>,<WallX[1],Floor[1],WallZ[1]>}
  }
}

