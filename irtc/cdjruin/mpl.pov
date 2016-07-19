//mpl.inc

#include "colors.inc"
#include "textures.inc"
#include "shapes.inc"
#include "skies.inc"
#include "metals.inc"

global_settings {ambient_light 0.4 assumed_gamma 2.2}
#declare SolarCells=0;   
#declare SkyLight=1;
#declare SkyLights=20;
#declare ComplexGround=1;
#declare SolarCell=intersection {
  box {                   
    <-0.05,0.0,-0.1>,<0.5,0.02,0.1>
    pigment {color rgb<0.1,0.0,0.2>}
    finish {phong 1}
  }
  box {                   
    <-0.045,-0.005,-0.095>,<0.45,0.025,0.095>
    pigment {color rgb<0.6,0.3,0.0>}
    finish {phong 1}
  }
}

#declare Panel=union {
  intersection {
    prism {
      linear_sweep
      linear_spline
      0,1,11
      <1.3,0>,<1.3,0.8>,<1.0,1.8>,<0.4,1.8>,<0.4,1.9>,<-0.4,1.9>,<-0.4,1.8>,<-1.0,1.8>,<-1.3,0.8>,<-1.3,0>,<1.3,0>
      scale <1,0.04,1>
      translate -y*0.01
      texture {
        T_Gold_5A
        normal {
          wrinkles 2 scale <1,10,1>
        }
      }
    }
    box { 
      <-1.31,0,-0.01>,<1.31,0.03,1.91>
      pigment {color Gray10}
    }
    box { 
      <-1.31,-0.01,-0.01>,<1.31,0.02,1.91>
      texture {T_Chrome_3A}
    }
  }
  #if(SolarCells)  //1 to render solar cells, 0 to not
    intersection {
      prism {
        linear_sweep
        linear_spline
        0,1,11
        <1.28,0.02>,<1.28,0.8>,<0.98,1.78>,<0.38,1.78>,<0.38,1.88>,<-0.38,1.88>,<-0.38,1.78>,<-0.98,1.78>,<-1.28,0.8>,<-1.28,0.02>,<1.28,0.02>
        scale <1,0.05,1>
      } 
      #declare PanelSeed=seed(2468);
      union {
        #declare I=-1.3;
        #while (I<1.3)
          #declare J=0; 
          #while (J<1.9)
            object {
              SolarCell
              rotate x*4*rand(PanelSeed)-2
              rotate z*2*rand(PanelSeed)-1
              translate <I+0.05,0.01,J+0.1>
            }
            #declare J=J+0.2;
          #end
          #declare I=I+0.1;
        #end   
      }
    }              
  #end
  bounded_by {
    box {
      <-1.3,0,0>,<1.3,0.03,1.9>
    }
  }
//  scale <1,1,1>
  translate z*0.05
}

#declare Dish=object {
  Paraboloid_Y
  scale <1,-1,1>
  translate y*1
  clipped_by {
    plane {-y,0}
  }
}

#declare Wing=union {
  object {       
    Panel
  }
  object {       
    Panel      
    rotate y*180
    rotate x*45
  }
  cylinder {
    <-0.1,0,0>,<0.1,0,0>,0.05
    pigment {color rgb<1,1,1>}
  }
  cylinder {
    <-0.6,0,0>,<-0.8,0,0>,0.05
    pigment {color rgb<1,1,1>}
  }
  cylinder {
    <0.6,0,0>,<0.8,0,0>,0.05
    pigment {color rgb<1,1,1>}
  }
  scale 0.8
  translate z*2.0
  translate y*0.25
}                  

#macro Linear(A,B,T)
  (A+(B-A)*T)
#end

#declare LegLength=2.0;
#declare FootY=-0.6;
#declare StrutA=<0.5,0.1,-sqrt(3)/2>;
#declare StrutB=<LegLength,FootY,0>;
#declare Strut=union {
  cylinder {
    Linear(StrutA,StrutB,0.05),StrutB,0.02
  }
  cylinder {
    Linear(StrutA,StrutB,0.5),StrutB,0.04
  }
  cone {
    Linear(StrutA,StrutB,0.45),0.025,Linear(StrutA,StrutB,0.5),0.045
    pigment {color rgb<0.3,0.3,0.3>}
  }
}
#declare Leg=union {
  object {Strut}
  object {Strut scale <1,1,-1>}
//  cylinder {
//    <0.5,
  cylinder {
    <1.1,0.85,0>,<LegLength,FootY,0>,0.05
    texture {
      T_Chrome_5C
      pigment {color White}
    }
  }
  #declare WireRadius=0.01;
  #declare CoilRadius=0.075;
  #declare CoilSpacing=0.075;
  #declare Coils=20;
  #include "spring.inc"
  object {
    Spring 
    translate y*0.1 
    rotate z*degrees(atan2(LegLength-1.1,0.85-FootY)) 
    translate <LegLength,FootY,0>
  }
  box {
    <-0.1,0,-0.1>,<0.1,0.35,0.1>
    translate y*(SpringLength-0.2)
    rotate z*degrees(atan2(LegLength-1.1,0.85-FootY)) 
    translate <LegLength,FootY,0>
  }
  difference {
    sphere {
      0,0.60
      translate y*0.45
    }
    sphere {
      0,0.58
      translate y*0.45
    }
    plane {
      -y,0.07
    }
    translate x*LegLength
    translate y*(FootY+0.05)
  }  
  texture {T_Chrome_5C}
}            

#declare Arm=union {  
  union {
    cylinder {
      <0,0,0>,<0,2.5,0>,0.05
      rotate z*180
      translate <0,1.6,0.1>
    }        
    cylinder {
      <0,0,-0.05>,<0,0,0.15>,0.1
      translate <0,1.6,0>
    }
    cylinder {
      <0,0,0>,<0,1.6,0>,0.05
    }                 
  }
  pigment {color <0,1,1>}
  rotate -z*90
  rotate -y*10
  translate <-1,0.90,-0.05>
} 

#declare MET=union {
  cylinder {
    <0,0,0>,<0,3,0>,0.015
  }  
  cylinder {
    <0,0.08,0>,<2,-1,0>,0.015
  }
  translate <1.25,0.8,0.3>
  texture {T_Brass_5C}
}   

#declare UHFBranch=difference {
  box {
    <-1,-1,-1>,<1,1,1>
    scale <0.01,0.15,0.1>
    translate y*0.15
  }
  box {
    <-1,-1,-1>,<1,1,1>
    scale <0.02,0.13,0.08>
    translate y*0.15
  }
}

#declare UHF=union {
  cylinder {
    <0,0,0>,<0,0.1,0>,0.1
  }                      
  object {UHFBranch}
  object {UHFBranch rotate y*90}
  pigment {color rgb<1,0.8,0.6>}
}

//DTE Antenna
#declare DTE=union {
  union {
    union {
      object {
        Dish               
        translate -y*1
        scale <0.4,0.1,0.4>
        rotate z*180
        pigment {color rgb<0.1,0.1,0.1>}
        finish {phong 1}
      }
      cylinder {
        <0,0,0>,<0,0.01,0>,0.06
        pigment {color rgb<0.8,0.0,0.0>}
        finish {phong 1}
      }       
      //Feed support
      cylinder {
        <0.2,0.25,0>,<0,0.5,0>,0.01
      }
      cylinder {
        <0.05,0.0,0>,<0.2,0.25,0>,0.01
      }
      sphere {
        <0.2,0.25,0>,0.01
      }             
      //Feed
      cylinder {
        <0.0,0.35,0>,<0,0.55,0>,0.02
      }
      cylinder {
        <0.0,0.5,0.0>,<-0.05,0.5,0.0>,0.01
      }
      cylinder {
        <0.0,0.32,0>,<0,0.35,0>,0.05
      }
      cylinder {
        <0,-0.05,-0.05>,<0,-0.05,0.05>,0.05
      }        
      translate <0,0.05,0>
      //Vertical dish mounting angle
      rotate -z*70
      //Azimuth
      rotate y*0
      translate <0.0,0.8,0.3>
    }
    cylinder {
      <0.0,0.0,0.3>,<0,0.8,0.3>,0.04
      pigment {color rgb<1,1,1>}
    }
    cylinder {
      <0.0,0.0,0.0>,<0,0.0,0.3>,0.04
      pigment {color rgb<1,1,1>}
    }
    sphere {
      <0,0,0.3>,0.04
      pigment {color rgb<1,1,1>}
    }      
    cylinder {
      <0.0,0.0,-0.15>,<0,0.0,0.15>,0.08
      pigment {color rgb<1,1,1>}
    }      
    cylinder {
      <0.0,0.0,-0.04>,<0,0.0,0.04>,0.09
      pigment {color rgb<1,1,1>}
    }      
    cylinder {
      <0.0,0.0,-0.06>,<0,0.0,-0.14>,0.09
      pigment {color rgb<1,1,1>}
    }      
    cylinder {
      <0.0,0.0,0.06>,<0,0.0,0.14>,0.09
      pigment {color rgb<1,1,1>}
    }      
    //Elevation
    rotate z*0
    rotate y*30  
    translate <0,0.15,0>
  }
  cylinder {
    <0,0.05,0>,<0,0.07,0>,0.21
    pigment {color rgb<1,1,1>}
  }
  cylinder {
    <0,0.0,0>,<0,0.07,0>,0.20
    pigment {color rgb<1,1,1>}
  }
  translate <0.6,0.8,-0.7>
  pigment {color rgb<0.5,0.5,0.5>}
}   

#declare LIDAR=union {
  box {
    <0,0,0>,<0.2,0.4,0.25>
    pigment {color <1,1,1>}
  }
  box {
    <0.01,0.39,-0.01>,<0.19,0.41,0.26>
    pigment {color <1,0,0>}
  }
  box {
    <0.20,0.1,0.05>,<0.21,0.2,0.20>
    texture {T_Gold_5C}
  }
}

#declare MVACS=object { 
//  box {
//    <-1,-1,-1>,<1,1,1>
  superellipsoid {
    <0.2,0.2>
    scale 0.5
    translate 0.5
    scale <1,0.5,1.5>
    texture {
      T_Brass_3C
      normal {wrinkles 1 scale 0.2}
    } 
    texture {
      pigment {
        image_map {
          png "mpllogo.png"
          once     
        }
        rotate x*90
        scale <1,1,408/295>
        scale 0.7
        translate <0.1,0,0.55>
      }
      normal {wrinkles 1 scale 0.2}
    }
  }
}

#declare MPL=union {
  //bus
  prism {
    linear_sweep
    linear_spline
    0,1,7
    <1,0>,<0.5,sqrt(3)/2>,<-0.5,sqrt(3)/2>,<-1,0>,<-0.5,-sqrt(3)/2>,<0.5,-sqrt(3)/2>,<1,0>
    scale <1,0.75,1>
    pigment {color rgb<0.75,0.75,0.75>}
  }
  //deck
  prism {
    linear_sweep
    linear_spline 
    0,1,11
    <1.3,0>,<1.1,0.6>,<0.8,1.1>,<-0.8,1.1>,<-1.1,0.6>,<-1.3,0>,<-1.1,-0.6>,<-0.8,-1.1>,<0.8,-1.1>,<1.1,-0.6>,<1.3,0>
    scale <1,0.05,1>
    translate y*0.75
    pigment {color rgb<0.75,0.75,0.75>}
  }
  object {MET}
  object {
    Leg
  }
  object {
    Leg
    rotate -y*120
  }
  object {
    Leg
    rotate y*120
  }             
  object {Arm}
  object {Wing} 
  object {Wing rotate y*180}   
  //Fuel tanks
  sphere {
    0,0.4
    translate <1.0,0.525,0.75>   
    texture {
      T_Brass_3C
      normal {wrinkles 1 scale 0.2}
    }
  }
  sphere {
    0,0.4
    translate <-1.0,0.525,-0.75>   
    texture {
      T_Brass_3C
      normal {wrinkles 1 scale 0.2}
    }
  }           
  object {DTE}
  object {
    MVACS 
    scale 0.6
    rotate y*90
    translate <-0.5,0.7,-0.1>
  }
  object {
    LIDAR
    scale 0.8
    rotate y*-80
    translate <0.5,0.8,0.5>
  }
  object {
    UHF
    translate <-0.5,0.8,0.5>
  }
} 

object {MPL translate <0,-FootY+0.05,10>}

camera {
  location <10,3,10>*3
  look_at <0,1,0>
  angle 35
}

//MPL1.jpg angle
/*
camera {
  location <10,10,-5>
  look_at <0,1,0>
  angle 20
} 
*/
//MPL9.jpg angle
/*
camera {
  location <10,5,2.5>
  look_at <0,1,0>
  angle 20
} 
*/


light_source {
  <2000,1000,1000>
  color 1.0+(1-SkyLight)       
  #if(SkyLight)
    area_light <0,0,50>,<50,0,0>,6,6
    adaptive 1
  #end
}

         
#if(SkyLight)
  #declare I=0;
  #declare SkySeed=seed(1357);
  #while(I<SkyLights)
    light_source {
      2000*vnormalize(<rand(SkySeed)*2-1,rand(SkySeed),rand(SkySeed)*2-1>)
      color 2*<0.5,0.3,0.25>/SkyLights
    }
    #declare I=I+1;
  #end
#end

sky_sphere {
  S_Cloud1
}

#if (ComplexGround)
  #declare GroundTile=height_field{
    png "ground.png"
    smooth
    translate <-0.5,0,-0.5>
  }
  #declare I=-18;
    #while(I<3)
    #declare J=-18;
    #while(J<3)
      object {
        GroundTile
        pigment {color <0.8,0.5,0>}
        translate <I,-0.25,J>
        scale <20,1,20>   
        rotate y*18
      }
      #declare J=J+1;
    #end
    #declare I=I+1;
  #end
  #declare I=0;
  #declare Rock=array[20] 
  #while(I<20)
    #declare Rock[I]=height_field {
      png concat("rock01.png")
    }
    #declare I=I+1;
  #end
  #declare I=0; 
  #declare RockSeed=seed(3579);
  #while (I<10000)
    object {
      Rock[floor(rand(RockSeed)*20)]
      rotate y*360*rand(RockSeed)
      scale <rand(RockSeed)+0.5,rand(RockSeed)*0.3+0.3,rand(RockSeed)+0.5>
      rotate y*360*rand(RockSeed)
      scale rand(RockSeed)+0.5
      translate <-exp(rand(RockSeed)*4)*30+50,-0.25,-exp(rand(RockSeed)*4)*30+50>
      pigment {color <0.3,0.1,0.0>}
    }
    #declare I=I+1;
  #end
#end

plane {
  y,-0.25
  pigment {color <0.8,0.5,0>}
  #if(ComplexGround)
    normal {
      bump_map { 
        png "ground.png"
        map_type 0 // 0=planar, 1=spherical, 2=cylindrical, 5=torus
        interpolate 2 // 0=none, 1=linear, 2=bilinear, 4=normalized distance
        bump_size 40 // 0...3     
      }
      rotate x*90
      translate <-0.5,0,-0.5>
      scale <20,1,20> 
      rotate y*18 
    }
  #end
}         

//The Ruin
#declare I=0;
#while (I<10)
  union {
    #if(I=4)
    cone {
      <0,-1,0>,0.5,<0,1+(10-I),0>,0.0
      rotate z*92 rotate y*247        
      translate <-I*2,0,-5>
    }
    #else
    cone {
      <-I*2,-1,-5>,0.5,<-I*2,1+(10-I),-5>,0.0
    }
    #end
    #if(I=2)
    cone {
      <I*2,-1,0>,0.5<I*2,1+(10-I),0>,0.0
      rotate z*92 rotate y*147
      translate <I*2,0,-5>
    }
    #else
    cone {
      <I*2,-1,-5>,0.5<I*2,1+(10-I),-5>,0.0
    }
    #end
    pigment {color <0.3,0.1,0.0>}
    normal {granite 3 scale 2}
    scale 3
  }        
  #declare I=I+1;
#end

difference {
  box {
    <0,0,0>,<10,2,2>
  }
  text {
    ttf "aurabesh.ttf" "This is a Star Wars Font"
    0.5,0
    translate <0.5,0.5,-0.25>
  }       
  translate <1,0,-1>
  rotate z*degrees(atan2(-3,4))
  rotate -y*120 
  translate <-12,6,-15>
  pigment {color <0.3,0.1,0.0>}
  normal {granite 1 scale 2}
}  

/*#include "Kwanlogo.inc"
union {
  box {
    <0,0,0.2>,<1,1,1>
  }
  object {
    KwanCircle scale 0.4 translate <0.5,0.5,0> 
  }
  pigment {color <0.3,0.1,0.0>}
  normal {granite 1 scale 2}
  scale 2
  rotate x*30
  rotate -y*140
  translate <10,-0.5,-4>
}
*/
