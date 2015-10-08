#include "shapes.inc"
#include "colors.inc"
#include "metals.inc"

#declare Engine=object {
  Paraboloid_Y
  clipped_by { cylinder {
    <0,-0.00001,0>,<0,1,0>,1
  }}
  scale <1,-1,1>
}

#local BellX=40.25;
#local BellY=94.14;
#local BellA=BellY/(BellX*BellX);

#ifndef(SmallPipes) #declare SmallPipes=true; #end

#if(SmallPipes)
#declare nDeco=7;
#declare Deco=array[nDeco]
#include "pipedeco.inc"
#end
#local MainTorusOffset=sqrt((BellY-55.96)/BellA)+4;
#declare Turbopump=union {
  cylinder {
    <0,55.96,0>,<0,200,0>,5
  }
  cylinder {
    <0,90,0>,<0,120,0>,8
  }
  torus {
    5,3
    translate y*90
  }
  torus {
    5,3
    translate y*120
  }
  translate z*MainTorusOffset
}

#declare nTex=4;
#declare Tex=array[nTex]
{texture {T_Chrome_4A},texture {pigment {color Red}},texture {T_Chrome_1A},texture {pigment {color White}}}

#declare J2=union {
  object {Engine translate y*1 scale <BellX,BellY,BellX>}
#if(SmallPipes)
  union{
    #include "pipe_1.inc"
    #include "pipe_2.inc"
    #include "pipe_4.inc"
    #include "pipe_5.inc"
    texture{T_Chrome_3A}
    scale 1
    translate y*90
  }
#end

  torus {
    MainTorusOffset,5
    translate y*(55.96)
  }
  torus {
    MainTorusOffset,5
    translate y*(49.62)
  }
  union {
  #local I=0;
  #while(I<9)
    torus {
      sqrt((BellY-I*48/9)/BellA)+0.5,0.75
      translate y*(I*48/9)
      sturm
    }
    #local I=I+1;
  #end
    texture {
      pigment {color White}
    }
  }
  //Combustion Chamber
  cone {
    <0,116.47,0>,11.03,<0,90.84,0>,sqrt((BellY-90.84)/BellA)
    open
  }
  //Start Tank
  sphere {
    <30,106.82,-4.69>,12.82
    pigment {color White}
  }
  //Turbopumps
  object {Turbopump}
  object {Turbopump rotate y*180}
  texture {T_Chrome_1A}
  translate -y*118.54
}


