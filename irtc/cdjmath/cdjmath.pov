//The Mathematics of Horror
//Chris Jeppesen
//27 Oct 1999

//render at +a0.001 +am2 +r3 +w800 +h600

//Changes for POV-Ray 3.7, 10 Aug 2018
global_settings {
  assumed_gamma 2.2
}
//Copy-pasta of Kwan Logo
#local KwanN=16;
#local KwanW="/h>m8X=X7KJXFXWhjhKMa$Q$AD390$&<";
#local KwanA=0;
#macro KwanK()
  #declare KwanA=KwanA+1;
  #local result=  asc(substr(KwanW,KwanA,1))*2/KwanN-4;
  (result/2)
#end
#declare KwanCircle=difference {
  cylinder{-y/8,y/8,2}
  prism{
    -KwanN,KwanN,KwanN
    #while(KwanA<KwanN*2)
      #local A1=KwanK()-34/KwanN;
      #local A2=KwanK()-44/KwanN;
      #debug concat(str((A1+2)*250,0,6)," ",str(1000-(A2+2)*250,0,6),"\n")
      <A1,A2>
    #end
  }
  scale y*20
  rotate -x*90
  scale 0.5
} 

#include "colors.inc"
#include "textures.inc"  
#include "stones.inc"
//#include "kwanlogo.inc"
#include "metals.inc"
#include "woods.inc"    

#declare star_count = 2000;
#declare star_scale = 0.5;
#include "GALAXY.SF"

camera {
  up y
  right x*image_width/image_height
  location <-1,2,-3>
//  look_at <-1.4,1.5,1.5>
  look_at <-0.05,1.5,0>
//  angle 10
}

light_source {
  <-0,20,-20>
  color 1.5
}

union {
  text {
    ttf "timesi.ttf"
    "d"
    0.2,0
    translate <-1,0,0>
  }

  box {
    <-1.25,-0.1,0>,<-0.25,-0.125,0.2>
  }
  
  text {
    ttf "timesi.ttf"
    "d"
    0.2,0
    translate <-1.25,-0.9,0>
  }

  text {
    ttf "symbol.ttf"
    "l"
    0.2,0
    translate <-0.75,-0.9,0>
  }

  text {
    ttf "times.ttf"
    "8"
    0.2,0
  }   
  
  text {
    ttf "symbol.ttf"
    "p"
    0.2,0
    translate <0.4,0,0>
  }
  
  text {
    ttf "timesi.ttf"
    "hc"
    0.2,0
    translate <0.9,0,0>
  }                        
  
  box {
    <0,-0.1,0>,<1.8,-0.125,0.2>
  }
  
  text {
    ttf "symbol.ttf"
    "l"
    0.2,0
    translate <0.7,-0.9>
  }
  
  text {
    ttf "times.ttf"
    "5"
    0.2,0
    scale 0.3
    translate <1.1,-0.4,0>
  }
  
  text {
    ttf "times.ttf"
    "1"
    0.2,0
    translate <2.8,0,0>
  }

  box {
    <2,-0.1,0>,<3.7,-0.125,0.2>
  }
  
  text {
    ttf "timesi.ttf"
    "e"
    0.2,0
    translate <2.0,-0.9,0>
  }

  text {
    ttf "timesi.ttf"
    "hc"
    0.2,0
    scale 0.3
    translate <2.55,-0.4,0>
  }
  
  box {
    <2.4,-0.43,0>,<2.9,-0.43-0.025,0.2>
  }

  text {
    ttf "timesi.ttf"
    "kT"
    0.2,0
    scale 0.3
    translate <2.6,-0.7,0>
  }

  text {
    ttf "symbol.ttf"
    "l"
    0.2,0
    scale 0.3
    translate <2.45,-0.7>
  }

  text {
    ttf "times.ttf"
    "-1"
    0.2,0
    translate <3,-0.9,0>
  } 
  
  text {
    ttf "times.ttf"
    "=0"
    0.2,0
    translate <3.8,-0.45,0>
  }

  translate <-1.0,1.5,1.5>
  pigment {color rgb<1,0,0>}
} 
union {
  #declare I=450;
  #while(I<550)
    cylinder {
      <-500,0,500-I>,<500,0,500-I>,0.01
    }
    cylinder {
      <500-I,0,-500>,<500-I,0,500>,0.01
    }
    #declare I=I+1;
  #end
  pigment {
    wood 
    color_map {
      [0 color rgb<0,0.5,0>]
      [0.05 color rgb<0,0,0>]
      [1 color rgb<0,0,0>]
    }         
    rotate 90*x
    scale 1000
  }
//  finish {ambient 1 diffuse 0 specular 0}
}
  

union {
  difference {
    union {
      cylinder {
        <0,0,0>,<0,0,0.2>,0.5
      }
      box {
        <-0.5,0,0>,<0.5,-1,0.2>
      }              
    }
    union {
      text {
        ttf "timesi.ttf"
        "S=k    W"
        0.2,0           
      }
      text {
        ttf "times.ttf"
        "       ln  "
        0.2,0           
      }
      scale <0.25,0.25,1>
      translate <-0.45,-0.1,-0.1>
    }
    texture {T_Stone13}  
    translate <0,1,0>
    scale 0.5
    rotate x*5
  }             
  difference {
    superellipsoid {
      <1,0.4>
      scale <0.5,0.1,0.81>
      translate <0,0,-0.7>
    }
    plane {
      y,0
    }
    pigment {color rgb<0.5,0.25,0>}
    normal {
      bumps 2 scale 0.01
    }
  }            
       
  julia_fractal {
    <-0.083,0.0,-0.83,-0.025>
    quaternion
    sqr
    max_iteration 8
    precision 15
    clipped_by {plane {x,0}}
    scale 0.1
    rotate z*90     
    rotate y*180 
    scale <0.7,1,0.7>
    translate <0,0.3,-0.75>
    pigment {color White}
  }                      
  cylinder {
    <0,0,0>,<0,0.25,0>,0.01
    translate <0,0,-0.7>   
    pigment {color rgb<0,0.8,0>}
  }                 
  scale 1.2
  rotate -y*15
  translate <-0.75,0,1.50>
}


union {
  light_source {
    <0,0.5,-0.5>
    color White*0.5
  }
  difference {
    union {
      #declare I=0;
      #while(I<18)
        torus {
          1,0.3
          translate <-0.4,0,0>
          rotate x*90
          rotate y*20*I
        }
        #declare I=I+1;
      #end
    }
    sphere {
      <0,0,0>,1.2
      pigment {color rgb<1,0.8,0>}
    }          
    object {
      KwanCircle
      scale <0.8,0.8,1>
      translate <0,0.2,-1>
      pigment {color rgb<1,0.8,0>}
    }   
  }        
  cone {
    <0,1.2,0>,0.2,<0,1.6,0>,0.1
    pigment {color rgb<0.4,0.2,0>}
  }
  rotate y*30
  scale 0.2
  translate <2,0.3,0>
  pigment {color Orange}
}


union {
  #declare P=0;   
  #declare C=3e8;
  #declare H=6.6e-34;
  #declare K=1.38e-23;
  #declare T=1700;
  #declare I=1;
  #declare TopScale=680;
  #declare LeftPoint=3;
  #while(I<2000)   
    #declare PLast=P;           
    #declare L=I*10e-9;
    #declare P=8*pi*H*C/(pow(L,5)*(exp(H*C/(L*K*T))-1));
    cylinder {
      <(I-1)/100-LeftPoint,PLast/TopScale,3>,<(I)/100-LeftPoint,P/TopScale,3>,0.05
    }   
    sphere {
      <I/100-LeftPoint,P/TopScale,3>,0.05
    }
    #declare I=I+1;
  #end
  pigment {color White}
}     

union {
  torus {
    #declare L=2.898e-3/T;
    #declare P=8*pi*H*C/(pow(L,5)*(exp(H*C/(L*K*T))-1));
    0.075,0.025
    rotate z*90
    translate <L*1e6-LeftPoint,P/TopScale,3>
  }
  cylinder {
    <L*1e6-LeftPoint,P/TopScale-0.075,3>,<L*1e6-LeftPoint,P/TopScale-1,3>,0.025
  }
  torus {
    0.075,0.025
    translate -z*0.075
    rotate -x*30              
    rotate -y*45
    translate <L*1e6-LeftPoint,P/TopScale-1,3>
  }
  pigment {color rgb<1,1,0.7>}
}

union {
  //feet
  sphere {
    0,1
    scale <0.1,0.05,0.2>
    translate <-0.1,0,0.1>
    rotate x*45
  }                
  sphere {
    0,1
    scale <0.1,0.05,0.2>
    translate <0.1,0,0.1>
    rotate x*45
  }     
  //shins
  sphere {
    0,1
    scale <0.075,0.25,0.075>
    translate <-0.1,0.25,0>               
  }
  sphere {
    0,1
    scale <0.075,0.25,0.075>
    translate <0.1,0.25,0>               
  }      
  //knees
  sphere {
    0,1 
    scale 0.075
    translate <-0.1,0.5,0>
  }
  sphere {
    0,1 
    scale 0.075
    translate <0.1,0.5,0>
  }      
  //thighs
  sphere {
    0,1
    scale <0.075,0.25,0.075>
    translate <-0.1,0.75,0>               
  }
  sphere {
    0,1
    scale <0.075,0.25,0.075>
    translate <0.1,0.75,0>               
  }      
  //hips
  sphere {
    0,1
    scale <0.2,0.075,0.075>
    translate <0,1,0>
  }     
  //torso
  sphere {
    0,1
    scale <0.2,0.25,0.075>
    translate <0,1.25,0>
  }      
  //shoulders
  sphere {
    0,1
    scale <0.3,0.075,0.075>
    translate <0,1.5,0>
  }          
  //head
  sphere {
    0,1
    scale <0.15,0.2,0.15>
    translate <0,0.2,0>
    //neck rotation
    rotate x*30
    //neck in place
    translate <0,1.5,0>
  }     
  union {
    //left upper arm
    sphere {
      0,1
      scale <0.05,0.2,0.05>
      translate <0,-0.2,0>
    }
    //left elbow
    sphere {
      0,1
      scale 0.05
      translate <0,-0.4,0>
    }
    //left lower arm
    union {
      sphere {
        0,1
        scale <0.05,0.2,0.05>
        translate <0,-0.2,0>
      }
      //left hand
      sphere {
        0,1
        scale 0.05
        translate <0,-0.4,0>
      }                   
      //elbow rotation
      rotate -z*0  //hinge
      rotate y*0    //lower arm rotation
      //elbow in place
      translate <0,-0.4,0>
    }
    //shoulder rotation
    rotate x*0   //arm forward lift
    rotate y*0     //arm swing
    //shoulder in place
    translate <-0.3,1.5,0>
  }
  union {
    //right upper arm
    sphere {
      0,1
      scale <0.05,0.2,0.05>
      translate <0,-0.2,0>
    }
    //right elbow
    sphere {
      0,1
      scale 0.05
      translate <0,-0.4,0>
    }
    //right lower arm
    union {
      sphere {
        0,1
        scale <0.05,0.2,0.05>
        translate <0,-0.2,0>
      }
      //right hand
      sphere {
        0,1
        scale 0.05
        translate <0,-0.4,0>
      }                   
      //elbow rotation
      rotate -z*0  //hinge
      rotate y*0    //lower arm rotation
      //elbow in place
      translate <0,-0.4,0>
    }
    //shoulder rotation
    rotate -x*0   //arm forward lift
    rotate y*0     //arm swing
    //shoulder in place
    translate <0.3,1.5,0>
  }
  pigment {color <0.8,0,1>}  
  finish {phong 1}
  translate -y*1.6 
  rotate y*180
  translate -z*0.075
  rotate -y*45
  scale 1.5/2.5
  translate <L*1e6-LeftPoint,P/TopScale-1,3>
}

#declare Link=union{
  torus {
    1,0.5
    clipped_by {plane {x,0}}
  }
  cylinder {
    <0,0,-1>,<2,0,-1>,0.5
  }
  cylinder {
    <0,0,1>,<2,0,1>,0.5
  }
  torus {
    1,0.5
    clipped_by {plane {x,0}} 
 
    rotate z*180
    translate <2,0,0>
  }
}

#declare Chain= union {
  union {
    #declare I=0;
    #while(I<10)
      object {
        Link
        rotate x*90*I
        translate x*2.5*I
      }
      #declare I=I+1;
    #end       
    rotate x*45
    scale 0.04
    rotate -y*90
  }  
  union {
    #declare I=0;
    #while(I<10)
      object {
        Link
        rotate x*90*I
        translate x*2.5*I
      }
      #declare I=I+1;
    #end       
    scale 0.04
    rotate x*90
    rotate -z*90
    translate <-0.04*0.707,-0.04*0.707,0>
  }  
  union {
    #declare I=0;
    #while(I<10)
      object {
        Link
        rotate x*90*I
        translate x*2.5*I
      }
      #declare I=I+1;
    #end       
    scale 0.04
    rotate x*90
    rotate -z*90
    translate <0.04*0.707,-0.04*0.707,0.707*0.04*25>
  }  
  texture {T_Chrome_5A}
}

object {Chain   translate <-1.40,1.40+0.04*0.707,1.5>}
object {Chain   translate <-2.10,1.40+0.04*0.707,1.5>}
//object {Chain   translate <-1.80,1.60+0.04*0.707,1.5>}
object {Chain   translate <-1.65,1.95+0.04*0.707,1.5>}

union {
  intersection {
    union {   
      cone {
        <0,30,0>,30,<0,30,0.025>,29.7
      }
      cone {
        <0,30,0>,30,<0,30,-0.025>,29.7
      }
    }
    plane {
      -x,0
      translate <0,30,0>
    }
    plane {
      -x,0       
      rotate z*5
      translate <0,30,0>
      inverse
    } 
    cylinder {
      <0,30,-0.1>,<0,30,0.1>,28.7
      inverse
    }
    texture {T_Chrome_5A}
  }              
  difference {         
    superellipsoid {
      <0.1,0.4>
      translate <-1,-1,0>
      scale 0.5
      scale <2,0.4,0.2>
      translate <0,30-28.7,0>  
    }
    cylinder {
      <-1,1.1,-0.2>,<-1,1.1,0.2>,0.05
    }
    cylinder {
      <-1.75,1.1,-0.2>,<-1.75,1.1,0.2>,0.05
    }
    cylinder {
      <-0.25,1.1,-0.2>,<-0.25,1.1,0.2>,0.05
    }            
    box {
      <-2.5,1.5,-0.025>,<0,0.5,0.025>
    }
    texture {
      T_Wood14
      finish { specular 0.35 roughness 0.05 ambient 0.3 }
      translate x*1
      rotate <15, 10, 0>
      translate y*2
    }
  }
  intersection {
    superellipsoid {
      <0.1,0.4>
      translate <-1,-1,0>
      scale 0.5
      scale <2,0.4,0.2>
      translate <0,30-28.7,0>  
    }              
    union {
      cylinder {
        <-1,1.1,-0.2>,<-1,1.1,0.2>,0.05
      }
      cylinder {
        <-1.75,1.1,-0.2>,<-1.75,1.1,0.2>,0.05
      }
      cylinder {
        <-0.25,1.1,-0.2>,<-0.25,1.1,0.2>,0.05
      }            
      box {
        <-2.5,1.5,-0.025>,<0,0.5,0.025>
      }      
    }
    texture {T_Chrome_5A}
  }
  scale 0.3
  rotate y*180
  rotate -z*30
  translate <4,1.3,1.6>
}  
