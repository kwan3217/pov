#declare HeadSize=3/4;
#declare ArmLength=5;
#declare TorsoLength=3.5;
//Distance from centerline to hip joint
#declare HipWidth=0.75;
//Distance from centerline to shoulder joint
#declare ShoulderWidth=1.25;

//"Yes" head nod. Positive is chin up
#ifndef(NeckNod)   #declare NeckNod=0;   #end

#ifndef(NeckTilt)  #declare NeckTilt=0; #end

//
#ifndef(LHipKick)  #declare LHipKick=0;#end
#ifndef(LKnee)     #declare LKnee=0;#end
#ifndef(LToePoint) #declare LToePoint=0;#end
//
#ifndef(LArmPitch) #declare LArmPitch=0;#end
#ifndef(LArmRoll)  #declare LArmRoll=0;#end
#ifndef(LElbow)    #declare LElbow=0;#end
//
#ifndef(RHipKick)  #declare RHipKick=0;#end
#ifndef(RKnee)     #declare RKnee=0;#end
#ifndef(RToePoint) #declare RToePoint=0;#end
//
#ifndef(RArmPitch) #declare RArmPitch=0;#end
#ifndef(RArmRoll)  #declare RArmRoll=0;#end
#ifndef(RElbow)    #declare RElbow=0;#end
//"No" head shake
#ifndef(NeckTwist) #declare NeckTwist=0; #end

#declare Manequin=union {
  //Hips - The anchor to everything
  sphere {
    0,1
    scale <HipWidth+0.25,0.5,0.25>
  }

  //Torso
  sphere {
    0,1
    scale <1,TorsoLength/2,0.5>
    translate y*TorsoLength/2
  }

  //shoulders      
  
  sphere {
    0,1
    scale <ShoulderWidth+0.25,0.25,0.25>
    translate y*TorsoLength
  }        

  //head 
  sphere {
    0,1
    scale <0.75,1,0.75>*HeadSize
    translate y*0.75*HeadSize
    rotate -x*NeckNod
    rotate y*NeckTwist
    rotate z*NeckTilt
    translate y*3.75
  }
  
  //Left leg
  union {       
    union {      
      //Left foot
      intersection {
        sphere {
          0,1
        }
        cylinder {
          0,y,1
        }
        scale <0.35,0.15,0.75>
        translate z*0.75
        rotate x*LToePoint
        translate -y*3
      }
        
      //Left Shin
      sphere {
        0,1
        scale <0.35,1.5,0.35>
        translate -y*1.5
      }
      //Left kneecap
      sphere {
        0,1
        scale 0.35
      }
      rotate x*LKnee
      translate -y*1.5
    }
    //Left thigh
    sphere {
      0,1
      scale <0.35,1.5,0.35>
    }
    translate -y*1.5
    rotate -x*LHipKick
    translate -x*HipWidth
  }    
  //Left Arm
  union {       
    union {      
      //Left hand
      sphere {
        0,1
        scale 0.35
        translate -y*2.5
      }
        
      //Left forearm
      sphere {
        0,1
        scale <0.25,ArmLength/4,0.25>
        translate -y*ArmLength/4
      }
      //Left kneecap
      sphere {
        0,1
        scale 0.25
      }
      rotate x*LElbow
      translate -y*ArmLength/4
    }
    //Left thigh
    sphere {
      0,1
      scale <0.25,ArmLength/4,0.25>
    }
    translate -y*ArmLength/4
    rotate -z*LArmRoll
    rotate -x*LArmPitch
    translate <-ShoulderWidth,TorsoLength,0>
  }    
  //Right leg
  union {       
    union {      
      //Right foot
      intersection {
        sphere {
          0,1
        }
        cylinder {
          0,y,1
        }
        scale <0.35,0.15,0.75>
        translate z*0.75
        rotate x*RToePoint
        translate -y*3
      }
        
      //Right Shin
      sphere {
        0,1
        scale <0.35,1.5,0.35>
        translate -y*1.5
      }
      //Right kneecap
      sphere {
        0,1
        scale 0.35
      }
      rotate x*RKnee
      translate -y*1.5
    }
    //Right thigh
    sphere {
      0,1
      scale <0.35,1.5,0.35>
    }
    translate -y*1.5
    rotate -x*RHipKick
    translate x*HipWidth
  }    
  //Right Arm
  union {       
    union {      
      //Right hand
      sphere {
        0,1
        scale 0.35
        translate -y*2.5
      }
        
      //Right forearm
      sphere {
        0,1
        scale <0.25,1.25,0.25>
        translate -y*1.25
      }
      //Right Elbow
      sphere {
        0,1
        scale 0.25
      }                
      rotate x*LElbow
      translate -y*1.25
    }
    //Right upper arm
    sphere {
      0,1
      scale <0.25,1.25,0.25>
    }
    translate -y*1.25
    rotate z*RArmRoll
    rotate -x*RArmPitch
    translate <ShoulderWidth,TorsoLength,0>
  }    
  pigment {color rgb <0.75,0,1>  }
  finish {phong 1} 
//  rotate -y*90
  translate y*6
  scale 1.7272/11.0625 //Convert to meters, my height (5'8")
}
