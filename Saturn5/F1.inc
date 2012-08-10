#version unofficial MegaPov 0.71;

#include "shapes.inc"
#include "colors.inc"
#include "metals.inc"
#include "F1Flame.inc"

#declare Engine=object {
  Paraboloid_Y
  clipped_by { cylinder {
    <0,-0.00001,0>,<0,1,0>,1
  }}
  scale <1,-1,1>
}

#local BellX=76.5;
#local BellY=180;
#local BellA=BellY/(BellX*BellX);

//#declare nDeco=7;
//#declare Deco=array[nDeco]
//#include "pipedeco.inc"
#declare F1=union {
  object {Engine translate y*1 scale <BellX,BellY,BellX>}
//
// union{
//    #include "pipe_1.inc"
//    #include "pipe_2.inc"
//    #include "pipe_4.inc"
//    #include "pipe_5.inc"
//    texture{T_Chrome_3A}
//    scale 1.5
//    translate y*210
//  }

  #local MainTorusOffset=sqrt((180-85.5)/BellA)+8;
//  union {
//    #include "pipe_3.inc"
//    texture {T_Chrome_3A}
//    scale <1.5,3,1.5>
//    translate <MainTorusOffset,210,0>
//  }


  torus {
    MainTorusOffset,10
    translate y*(85.5)
  }
  union {
  #local I=0;
  #while(I<6)
    torus {
      sqrt((180-I*80/6)/BellA)+1.5,2
      translate y*(I*80/6)
      sturm
    }
    #local I=I+1;
  #end
    texture {
      T_Chrome_3A
    }
  }
  #local I=0;
  #while(I<20)
    torus {
      sqrt((I*90/20)/BellA)+0.75,1
      translate y*((180-I*90/20))
      sturm
    }
    #local I=I+1;
  #end
  //Combustion Chamber
  cylinder {
    <0,170,0>,<0,200,0>,30
    open
  }
  cone {
    <0,170,0>,30,<0,160,0>,sqrt(20/BellA)
    open
  }
  //Turbopump
  cone {
    <MainTorusOffset,85.5,0>,10<MainTorusOffset,110,0>,12
  }
  union {
    cylinder {
      <0,0,0>,<0,24,0>,12
      matrix <1,0,0,
              -1/6,1,0,
              0,0,1,
              MainTorusOffset,110,0>
    }
    cone {
      <0,0,0>,12,<0,12,0>,18
      matrix <1,0,0,
              -0.5,1,0,
              0,0,1,
              MainTorusOffset-4,134,0>
    }
    cylinder {
      <0,0,0>,<0,72,0>,18
      translate <MainTorusOffset-10,146,0>
    }
    texture {T_Chrome_3A}
  }

//  object {F1Flame scale 76.5*F1FlameScale/12*0.3048}

  texture {T_Chrome_1A}
  translate -y*115.36
  hollow
}


