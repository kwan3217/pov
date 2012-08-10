#version 3.5;

#include "colors.inc"
#include "shapes.inc"
#include "metals.inc"
#include "Scene.inc"

#declare SceneWeight=array[7] {0.25,0.25,0.25,0.125,1,1,1}
#declare SceneNums=array[7] {1,2,3,4,10,30,40}   
SceneCalc()

global_settings {
  assumed_gamma 1.0
  max_trace_level 5
  charset utf8
}   

background {color rgb <0,0.5,1>}

#declare Zoom=exp((1-SceneClockMult(1,10))*2)/1.5;
#declare CameraLoc=<-5, 2, -15>;
#declare CameraLoc=CameraLoc*Zoom+y*52;
#declare CameraLook= <0, 30+22*SceneClockMult(1,10),  0.0>;

camera {
  location CameraLoc  
  look_at  CameraLook
}

sky_sphere {
  pigment {
    gradient y
    color_map {
      [0.0 rgb <0.6,0.7,1.0>*(1-SceneClockMult(1,10))]
      [0.7 rgb <0.0,0.1,0.8>*(1-SceneClockMult(1,10))]
    }
  }
}

light_source {
  <0, 0, 0>            // light's position (translated below)
  color rgb <1, 1, 1>  // light's color
  translate <-30, 30, -30>*1000
}


#declare Engine=object {
  Paraboloid_Y scale <1,-1,1> translate y
  clipped_by {
    plane {-y,0}
  }
}            

#declare Strapon=union {
  object {
    Engine
    scale <0.75,2.0,0.75>
    translate <0.8,0,0>
    pigment {color rgb 0.5}
  }
  cylinder {
    <0,1.5,0>,<0,2.6,0>,0.9
  pigment {color rgb 1}
  }
  box {
    <0,1.5,-0.9>,<1.2,2.6,0.9>
  pigment {color rgb 1}
  }
  cylinder {
    <0,2.6,0>,<0,3.7,0>,0.9
    pigment {color rgb 0.5}
  }
  box {
    <0,2.6,-0.9>,<1.2,3.7,0.9>
    pigment {color rgb 0.5}
  }
  cylinder {
    <0,3.7,0>,<0,17.6,0>,0.9
    pigment {color rgb 1}
  }
  cone {
    <0,0,0>,0.9,<0,4.2,0>,0
    matrix <1,0,0,
            9/42,1,0,
            0,0,1,
            0,17.6,0>
    pigment {color rgb 1}
  }       
  translate -x*3.0
}      

#declare Core=union {
  cylinder {
    <0,1.5,0>,<0,2.6,0>,2.1
    pigment {color rgb 1}
  }
  cylinder {
    <0,2.6,0>,<0,3.7,0>,2.1
    pigment {color rgb 0.5}
  }
  cylinder {
    <0,3.7,0>,<0,21.8,0>,2.1
    pigment {color rgb 1}
  }
}        

#declare FirstStage=union {
  object {Core}
  object {Strapon rotate y*030}
  object {Strapon rotate y*090}
  object {Strapon rotate y*150}
  object {Strapon rotate y*210}
  object {Strapon rotate y*270}
  object {Strapon rotate y*330}
  difference {
    sphere {
      <0,22.9-2.5,0>,2.5
    }
    plane {
      y,21.8
    }
    pigment {color rgb 0.5}
  }
  #declare I=0;
  #while(I<36)
    cylinder {
      <0,21.8,-2.05>,<2.05*sin(20*pi/180),23.1,-2.05*cos(20*pi/180)>,0.05
      rotate y*I*10
      pigment {color rgb 1}
      
    } 
    cylinder {
      <0,21.8,-2.05>,<-2.05*sin(20*pi/180),23.1,-2.05*cos(20*pi/180)>,0.05
      rotate y*I*10
      pigment {color rgb 1}
      
    } 
    #declare I=I+2;                     
  #end
  torus {
    2.05,0.05
    translate y*23.05
    pigment {color rgb 1}
  }
}      

#declare ProtonLogo=union { 
  text {
    ttf "ariblk.ttf" "\u041F",1,0
    translate y*5
  }              
  text {
    ttf "ariblk.ttf" "P",1,0
    translate y*4
  }              
  text {
    ttf "ariblk.ttf" "O",1,0
    translate y*3
  }              
  text {
    ttf "ariblk.ttf" "T",1,0
    translate y*2
  }              
  text {
    ttf "ariblk.ttf" "O",1,0
    translate y*1
  }              
  text {
    ttf "ariblk.ttf" "H",1,0
    translate y*0
  }              
  scale 1.8 translate <-0.5,26,-2.5>
} 

#declare SecondStage=union {
  #declare I=0;
  #while(I<36)
    cylinder {
      <0,24.4,-2.05>,<2.05*sin(20*pi/180),23.1,-2.05*cos(20*pi/180)>,0.05
      rotate y*I*10
      pigment {color rgb 1}
    } 
    cylinder {
      <0,24.4,-2.05>,<-2.05*sin(20*pi/180),23.1,-2.05*cos(20*pi/180)>,0.05
      rotate y*I*10
      pigment {color rgb 1}     
    } 
    #declare I=I+2;                     
  #end
  torus {
    2.05,0.05
    translate y*23.15
    pigment {color rgb 1}
  }
  cylinder {
    <0,24.4,0>,<0,36.3,0>,2.1
    pigment {
      object {
        union {
          object {ProtonLogo}
          object {ProtonLogo rotate y*180}
        }
        color rgb 1
        color rgb <1,0,0>
      }
    }
          
  }     
  cylinder {
    <0,36.3,0>,<0,41.4,0>,2.1
    open
    pigment {color rgb 1}
  }
  object {
    Engine
    scale <0.75,1.5,0.75>
    translate <1.0,23.3,0>
    pigment {color rgb 0.5}
  }    
  object {
    Engine
    scale <0.85,2.3,0.85>
    translate <-1.0,23.3,0>
    pigment {color rgb 0.5}
  }    
  object {
    Engine
    scale <0.75,1.5,0.75>
    translate <0,23.3,-1.0>
    pigment {color rgb 0.5}
  }    
  object {
    Engine
    scale <0.75,1.5,0.75>
    translate <0,23.3,1.0>
    pigment {color rgb 0.5}
  }    
}  

#declare ThirdStage=union {
  cone {
    <0,39.7,0>,0.6,<0,41.4,0>,2.1
    pigment {color rgb 0.5}
  }    
  cylinder {
    <0,41.4,0>,<0,45.1,0>,2.1
    pigment {
      color rgb 1
    }
    texture {
      pigment {
        image_map {
          png "AvalonSmNew.png" // the file to read (iff/tga/gif/png/jpeg/tiff/sys)
          map_type 0        // 0=planar, 1=spherical, 2=cylindrical, 5=torus
          interpolate 2     // 0=none, 1=linear, 2=bilinear, 4=normalized distance
          once           // for no repetitive tiling  
        }
        //rotate -x*90
        scale <1,2451/2241,1>
        scale 2
        translate <-1,42,0>
      }
    }
  }     
  object {
    Engine
    scale <0.85,2.1,0.85>
    translate <0,38.1,0>
    pigment {color rgb 0.5}
  }    
}    

#declare Fairing= union {
    cylinder {
      <0,45.1,0>,<0,45.683,0>,2.05
      open
      pigment {color rgb 0.25}
    }
    cylinder {
      <0,45.683,0>,<0,48.754,0>,2.175
      open
      pigment {color rgb 0.25}
    }
    cylinder {
      <0,48.754,0>,<0,52.866,0>,2.175
      open
      pigment {color rgb 0.25}
    }
    cone {
      <0,52.866,0>,2.175,<0,54.978>,1.3915
      open
      pigment {color rgb 0.25}
    }
    cone {
      <0,54.978>,1.3915,<0,57.283,0>,0
      open
      pigment {color rgb 0.25}
    }
  clipped_by {plane {
    x,0
  }}
}              

#declare BreezeM=union {
  cylinder {
    <0,0,0>,<0,1.6,0>,2.05
    texture {T_Chrome_5C}
  }
  cone {
    <0,1.6,0>,2.05,<0,2.0,0>,1.7
    texture {T_Chrome_5C}
  }
  cylinder {
    <0,2.0,0>,<0,2.071,0>,1.2
    texture {T_Chrome_5C}
  }
  cone {
    <0,2.071,0>,1.263,<0,3.071,0>,0.6075
    texture {T_Chrome_5C}
  }    
  object {
    Engine
    scale <0.5,1,0.5>
    translate <0,-0.5,0>
    texture {T_Chrome_1A}
  }
  translate y*45.683
}

#declare AluminizedTeflon=texture {
  pigment {color rgb <0.95, 0.95, 0.95>}
  finish {
    ambient 0.35
    brilliance 2
    diffuse 0.3
    metallic
    specular 0.80
    roughness 1/20
    reflection 0.1
  }               
  normal {wrinkles 0.5 scale 0.5}
}           

#declare PanelX=0.72*1.2;
#declare PanelY=1.9/1.2;  
#declare RadiatorArea=0.6;
#declare RadiatorX=RadiatorArea/PanelY;

#declare Panel=union {
  #declare I=0;
  #while(I<20)  
    cylinder {
      <0,I*0.05*PanelY,0>,<0,I*0.05*PanelY,1*PanelX>,0.005
      texture {T_Gold_5C}
    }
    #declare J=0;
    #while(J<20)
      box {
        <0,I*0.05*PanelY,J*0.05*PanelX>,<0.001,(I+1)*0.05*PanelY,(J+1)*0.05*PanelX>
        pigment {
          color rgb <0.125,0,0.5>+vturbulence(2,0.5,6,<0,I,J>)*0.05
        }
        finish {
          phong 1
        }
      }
      #declare J=J+1;
    #end
    #declare I=I+1;
  #end            
  box {
    <0,0,-RadiatorX>,<-0.005,PanelY,PanelX+RadiatorX>
    pigment {color rgb 0.9}
  }
  translate <0,0,-PanelX/2>
  rotate y*90
}         
     

#declare AlphaSize=2.033;
#declare BetaSize=1.847; 
#declare AlphaBoomLength=0.1;
#declare BetaBoomLength=0.1+(AlphaSize-BetaSize)/2;

#macro PanelAsm(Parity,BoomLength,Deploy,SunAngle) 
  //#warning "In PanelAsm\n"
  //Deploy: 0 for full stow, 1 for full deploy
  //PanelSunAngle: 0 for stow
  //Parity:      1 for left, -1 for right
  union {
    cylinder {
      <0,0,0>,<-BoomLength,0,0>,0.025
      texture {AluminizedTeflon}
    }
    object {
      Panel
      rotate z*90*Parity
      rotate x*(SunAngle+270)
      translate -x*BoomLength*Parity
    }       
    translate -y*0.025*Parity
    rotate -z*(1-Deploy)*90*Parity
  } 
  //#warning "Out of PanelAsm\n"
#end

#declare Alpha=union {
  difference {
    box {
      <0,0,0>,<AlphaSize,AlphaSize,AlphaSize>
      translate <-AlphaSize/2,0,-AlphaSize/2>
      texture {AluminizedTeflon}
      //pigment {color rgbf <1,1,1,0.5>}
    }
    object {
      Engine
      scale <0.75,0.2,0.75>
      rotate x*90
      translate <0,AlphaSize/2,-AlphaSize/2-0.0001>
      pigment {color rgb 1}
    }         
  }
  union {         
    cylinder {
      <0,0.4,0>,<0,0,-0.75>,0.005
      texture {T_Gold_5C}
    }
    cylinder {
      <0,0.4,0>,<0,0,-0.75>,0.005
      rotate z*120
      texture {T_Gold_5C}
    }
    cylinder {
      <0,0.4,0>,<0,0,-0.75>,0.005
      rotate -z*120
      texture {T_Gold_5C}
    }
    translate <0,AlphaSize/2,-AlphaSize/2+0.2>
  }
  object {
    PanelAsm(1,AlphaBoomLength,(SceneClockBound(30)),(SceneClockBound(40))*90)
    translate <-AlphaSize/2,0,0>
  }
  object {
    PanelAsm(-1,AlphaBoomLength,(SceneClockBound(30)),(SceneClockBound(40))*90)
    translate <AlphaSize/2,0,0>
  }
}

#declare Alpha1=object {
  Alpha
  translate y*48.754
}

#declare Beta=union {
  difference {
    box {
      <0,0,0>,<BetaSize,BetaSize,BetaSize>
      texture {AluminizedTeflon}
      translate <-BetaSize/2,0,-BetaSize/2>
    }
    object {
      Engine
      scale <0.75,0.2,0.75>
      rotate x*90
      translate <0,BetaSize/2,-BetaSize/2-0.0001>
      pigment {color rgb 1}
    }         
  }
  union {         
    cylinder {
      <0,0.4,0>,<0,0,-0.75>,0.005
      texture {T_Gold_5C}
    }
    cylinder {
      <0,0.4,0>,<0,0,-0.75>,0.005
      rotate z*120
      texture {T_Gold_5C}
    }
    cylinder {
      <0,0.4,0>,<0,0,-0.75>,0.005
      rotate -z*120
      texture {T_Gold_5C}
    }
    translate <0,BetaSize/2,-BetaSize/2+0.2>
  }
  object {
    PanelAsm(1,BetaBoomLength,(SceneClockBound(30)),(SceneClockBound(40))*90)
    translate <-BetaSize/2,0,0>
  }
  object {
    PanelAsm(-1,BetaBoomLength,(SceneClockBound(30)),(SceneClockBound(40))*90)
    translate <BetaSize/2,0,0>
  }
}   

#declare Beta1=object {
  Beta
  translate y*(48.754+AlphaSize+0.1)
}  

#declare Beta2=object {
  Beta
  translate y*(48.754+AlphaSize+BetaSize+0.2)
}  

object {
  FirstStage
  translate -y*pow((SceneClockLBound(2)),2)*50
}

object {
  SecondStage
  translate -y*pow((SceneClockLBound(3)),2)*40
} 
object {
  ThirdStage
  translate -y*pow((SceneClockLBound(4)),2)*30
}   
  
object {
  Fairing           
//  rotate 45*z*Scene1Clock
  translate <-(SceneClockLBound(2))*10,-5*pow((SceneClockLBound(2)),2)+1*(SceneClockLBound(2)),0>
} 

object {
  Fairing rotate y*180
  translate <(SceneClockLBound(2))*10,-5*pow((SceneClockLBound(2)),2)+1*(SceneClockLBound(2)),0>
} 

object {
  BreezeM
  translate -y*pow((SceneClockLBound(10)),2)*20
}

object {
  Alpha1
}
object {
  Beta1
}
object {
  Beta2
}        
/*
#declare Flame=union {
  #declare I=0;
  #while (I<12)
  sphere {
    <0,0,0>,1
    scale <1,4,1>
    translate <0,-3-I*3.6,0>
    pigment {color rgbt <1,0.7,0,I/48+0.75,I/48+0.75>}
    finish {ambient 0.5} 
    no_shadow
  }   
  #declare I=I+1;
  #end
}

#declare I=0;
#while(I<6)
object {
  Flame
  translate -z*2.2
  rotate y*I*60
}
#declare I=I+1;
#end
*/
    