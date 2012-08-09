#include "Math.inc"
#include "Aim.inc"
#include "AimAttCommon.inc"

#declare Arc=difference {
  cylinder {
    -z,z,1
  }
  cylinder {
    -z*1.01,z*1.01,0.98
  }
  plane {
    y,0
  }
  pigment {color rgb <1,1,1>}
  finish {ambient 1 diffuse 0}
  no_shadow
}

#declare Vector=union {
  cylinder {
    0,y*0.75,0.04
  }
  cone {
    y*0.75,0.12,y,0
  }
}

#declare RollModel=union {
  //Roll model
  union {
    object {
      Aim
      scale 0.45
    }
    object {
      Vector
      pigment {color rgb <1,0,0>}
    }
    AimRot2()
    rotate y*90
    no_shadow
  }
  object {Arc}
}

#declare PitchModel=union {
  union {
    object {
      Aim
      scale 0.45
    }
    object {
      Vector
      rotate -z*90
      pigment {color rgb <1,1,0>}
    }
    AimRot2()
    no_shadow
  }
  object {Arc rotate -z*90}
}

//Yaw model
#declare YawModel=union {
  union {
    object {
      Aim
      scale 0.45
    }
    object {
      Vector
      rotate -z*90
      pigment {color rgb <0,1,0>}
    }
    AimRot2()
    rotate -x*90
    no_shadow
  }

  object {
    Arc
    rotate -z*90
  }
}

union {
  object {YawModel translate <1/3,1/2,0>*5}
  object {PitchModel translate <1/3,0,0>*5}
  object {RollModel translate <1/3,-1/2,0>*5}
  scale 0.5*2/3
  translate <1/3,1/4,0>*5
}
union {
  text {
    ttf "verdana.ttf"
    CipsStatus
    0,0
    scale 0.05
    translate <-4/3,-1,0>*0.48+y*0.0
    pigment {color rgb <1,1,0>}
    finish {ambient 1}
  }
  text {
    ttf "verdana.ttf"
    SofieStatus
    0,0
    scale 0.05
    translate <-4/3,-1,0>*0.48+y*0.05
    pigment {color rgb <0,0.5,1>}
    finish {ambient 1}
  }
  #declare SofieAlt=concat("Sofie Alt: ",str(SofieTtoH(clockSec),0,1),"km");
  text {
    ttf "verdana.ttf"
    SofieAlt
    0,0
    scale 0.05
    translate <-4/3,-1,0>*0.48+y*0.10
    pigment {color rgb <0,1,0>}
    finish {ambient 1}
  }
  scale 5
}
camera {
  orthographic
  location <0,0,-5>
  look_at <0,0,0>
}


union {
  box {
    <-1,-1,0>,<1,1,0>
    scale 1/6*1.05
    translate <0,1/6,0>
    pigment {color rgb CipsDapatColor}
    finish {ambient 1}
  }
  box {
    <-1,-1,0>,<1,1,0>
    scale 1/6*1.05
    translate <-2/3,1/6,0>
    pigment {color rgb CipsDapatColor}
    finish {ambient 1}
  }
  box {
    <-1,-1,0>,<1,1,0>
    scale 1/6*1.05
    translate <-1/3,1/3,0>
    pigment {color rgb CipsDapatColor}
    finish {ambient 1}
  }
  box {
    <-1,-1,0>,<1,1,0>
    scale 1/6*1.05
    translate <-1/3,0,0>
    pigment {color rgb CipsDapatColor}
    finish {ambient 1}
  }
  translate <1/6,0,1>
  scale 5
}

light_source {
  <0,0,-5>*1000000
  color rgb 1
}
