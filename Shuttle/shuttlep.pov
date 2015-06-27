// Persistence of Vision Ray Tracer Scene Description File
// File: ?.pov
// Vers: 3
// Desc: Basic Scene Example
// Date: mm/dd/yy
// Auth: ?
//

#include "colors.inc"
#include "metals.inc"
#include "skies.inc"
#include "glass.inc"
//#include "math.inc"

#declare NaturalColor=1;


#declare BASE          = 45;
#declare LDoorOpen=0;//175; //135
#declare RDoorOpen=0;//175; //135

#include "Shuttle.inc"
global_settings
{
  ambient_light color rgb 0.3
  assumed_gamma 1.0
}

background {rgb <0.7,0.7,1>}


light_source
{
  0*x                     // light's position (translated below)
  color rgb <1,1,1>       // light's color
  translate <35000, 50000, -100000>
  shadowless
  rotate y*clock*360
//  atmosphere on
//  atmospheric_attenuation on
}


#declare Tank=union {
  sphere {
    <0,2.5,0>,2.5
  }
  cylinder {
    <0,2.5,0>,<0,12.5,0>,2.5
  }
  sphere {
    <0,12.5,0>,2.5
  }
}

#declare Tank1Tex=texture {
  T_Chrome_3A
}

#declare Tank2Tex=texture {
  T_Gold_3A
}

#declare TankAssembly=union {
  object {Tank scale <1,0.5,1> texture {Tank1Tex}}
  object {Tank scale <1,0.5,1> translate <0,7.5,0> texture {Tank2Tex}}
  object {Tank translate <5,0,0> rotate y*0 texture {Tank1Tex}}  
  object {Tank translate <5,0,0> rotate y*60 texture {Tank2Tex}}  
  object {Tank translate <5,0,0> rotate y*120 texture {Tank1Tex}}  
  object {Tank translate <5,0,0> rotate y*180 texture {Tank2Tex}}  
  object {Tank translate <5,0,0> rotate y*240 texture {Tank1Tex}}  
  object {Tank translate <5,0,0> rotate y*300 texture {Tank2Tex}}  
}  
             
#declare LegExtension=0;
#declare LanderLeg=union {
  cylinder {
    <0,16.5,-7>,<0,8,-7>,0.5
    translate <0,-16.5,7.5>
    rotate x*LegExtension
    translate <0,16.5,-7.5>
  }
  union {
    cylinder {
      <0,8,-7>,<0,0,-7>,0.5
    }
    cylinder {
      <0,0,-7>,<0,0.5,-7>,1.5
    }
    translate <0,-8.5*cos(radians(LegExtension)),-8.5*sin(radians(LegExtension))>
    translate <0,8.5,0>
  }
}
             
#declare Lander=union {
  union {
    cone {
      <0,27.5,0>,3.5,<0,25,0>,7.5
    }   
    difference {
      cylinder {
        <0,25,0>,<0,17.5,0>,7.5
      }
      box {
        <-7.5,24.5,-6>,<-2,17.49,-7.51>
      }
      box {
        <7.5,24.5,-6>,<2,17.49,-7.51>
      }
    }
    pigment {color Gray}
  }   
  intersection {
    plane {
      y,24.5
    } 
    sphere {
      0,7.49 
      scale <1,0.75,1>
      translate <0,24.5,0>
    }
    pigment {color Blue}
  }
  union { 
    difference {
      union {
        cylinder {
          <0,17.5,0>,<0,10.5,0>,7.5
        }
        cone {
          <0,10.5,0>,7.5,<0,8,0>,3.5
        }
      }
      cylinder {
        <0,16.5,-7.5>,<0,7.99,-7.5>,1
      }
      cylinder {
        <0,16.5,7.5>,<0,7.99,7.5>,1
      }
      cylinder {
        <-7.5,16.5,0>,<-7.5,7.99,0>,1
      }
      cylinder {
        <-7.5,16.5,0>,<-7.5,7.99,0>,1
      }
    }
    object {LanderLeg}
    object {LanderLeg rotate y*90}
    object {LanderLeg rotate y*180}
    object {LanderLeg rotate y*270}
    texture {
      T_Gold_3A
      normal {
        wrinkles 1
      }
    }
  }
  cone {
    <0,10,0>,0.5,<0,7,0>,1.5
    open
    pigment {color Gray25}
  }
//  cylinder {
//    <0,0,-8>,<0,6,-8>,1
//    pigment {color Red}
//  }
}
  

#declare CargoBay=union {
  cylinder {
    <576,0,429.214>,<1311.337,0,429.214>,105.711
    open
    clipped_by {
      box {
        <500,-110,-100>,<1400,110,429.214>
      }
    }
  }
  cylinder {
    <716,0,450>,<716,0,300>,40
  }
  object {
    Lander
    scale <12,12,-12>
    rotate z*90
    translate <1100,0,400>
  }
  object {
    TankAssembly
    scale <12,12,-12>
    rotate z*90
    translate <1311.337,0,400>
  }
  pigment {color White}
}

#declare OrbiterWithCargo=union {
  object {Orbiter}
  object {CargoBay transform OrbTransform}
}

#declare SizeParts=union {
  object {Orbiter}
}  

#declare O1=min_extent(SizeParts);
//PrintVector("O1: ",O1)
#declare O2=max_extent(SizeParts);
//PrintVector("O2: ",O2)

object {
  Orbiter               
//  rotate x*120
//  rotate -y*120
//  translate <-(O2.x+O1.x)/2,-(O2.y+O1.y)/2,-(O2.z+O1.z)/2>
}

#declare Y=image_height;
#declare X=Y*(O2.x-O1.x)/(O2.y-O1.y);
//PrintNumber("Proper X=",X)
camera {
  location <0,20,-50>
  look_at <0,15,0>
//  angle 10
}                    

global_settings {
//  ini_option concat("+W",str(X,0,0))
}
