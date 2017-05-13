/***************************************************************************/
//		person.inc
/***************************************************************************/
//		People Plugin for POV-Ray 3.x

//		Created by Hero Ngauv, 1997

//		See "readme.txt" for usage information.
/***************************************************************************/
#ifndef (Height)
  #declare Height = 32;
  #end
#declare Size = (Height/8); // (1.02109375)
/***************************************************************************/
#ifndef (Gender)
  #declare Gender = 1;		//1=male, 2=female
  #end
#ifndef (Breasts)
  #declare Breasts = 10/16;	//keep between 8/16 and 12/16
  #end
/***************************************************************************/
#include "rotation.inc"
#include "texture.inc"
/***************************************************************************/
#declare T = 0.25;	//threshold
#declare R = 1.5;	//radius
#declare S = 0.83;//1	//strength
/***************************************************************************/
#include "chest.inc"
#include "legs.inc"
#include "head.inc"
#include "arms.inc"
#include "hands.inc"
/***************************************************************************/
#declare Head2 =
union{
  object {
    Hair
    texture {Hair_Texture}
  }
  object{ Head
    texture{ Head_Texture }
    texture{
      pigment{
        #if (Gender = 1)
          image_map{ gif "headf10.gif" interpolate 2 once }
          #end
        #if (Gender = 2)
          image_map{ gif "headf7.gif" interpolate 2 once }
          #end
        translate <-0.5,-0.275,0>
        scale <Size*1.25,Size*1.15,1>
      }
      finish{ ambient 0.15 diffuse 0.85 }
    }
    translate <0,0,Size*1/256>
  }
  object{ Head
    texture{ Head_Texture }
    texture{
      pigment{
        #if (Gender = 1)
          image_map{ gif "headb10.gif" interpolate 2 once }
          #end
        #if (Gender = 2)
          Clear
          #end
        translate <-0.5,-0.275,0>
        scale <Size*1.25,Size*1.15,1>
      }
      finish{ ambient 0.15 diffuse 0.85 }
    }
    translate <0,0,-Size*1/256>
  }
}
#declare Neck2 =
union{
  object{ Neck texture{ Suit_Texture } translate <0,0,Size*1/256> }
  object{ Neck texture{ Suit_Texture } translate <0,0,-Size*1/256> }
}
#declare R_Thigh2 =
union{
  object{ Thigh texture{ Suit_Texture translate <-Size/2.5,0,0> } translate <0,0,Size*1/256> }
  object{ Thigh texture{ Suit_Texture translate <-Size/2.5,0,0> } translate <0,0,-Size*1/256> }
//  object{ Thigh texture{ Base translate <-Size/2.5,0,0> scale <1.0,1,1> } translate <0,0,Size*1/256> }
//  object{ Thigh texture{ Base2 translate <-Size/2.5,0,0> scale <1.0,1,1> } translate <0,0,-Size*1/256> }
}
#declare L_Thigh2 =
union{
  object{ Thigh texture{ Suit_Texture translate <Size/2.5,0,0> } translate <0,0,Size*1/256> }
  object{ Thigh texture{ Suit_Texture translate <Size/2.5,0,0> } translate <0,0,-Size*1/256> }
//  object{ Thigh texture{ Base translate <Size/2.5,0,0> scale <1.0,1,1> } translate <0,0,Size*1/256> }
//  object{ Thigh texture{ Base2 translate <Size/2.5,0,0> scale <1.0,1,1> } translate <0,0,-Size*1/256> }
}
#declare R_Shin2 =
union{
  object{ Shin texture{ Suit_Texture translate <-Size/2.5,0,0> } translate <0,Size*1/256,0> }
  object{ Shin texture{ Suit_Texture translate <-Size/2.5,0,0> } translate <0,0,Size*1/256> }
  object{ Shin texture{ Suit_Texture translate <-Size/2.5,0,0> } translate <0,0,-Size*1/256> }
//  object{ Shin texture{ Base translate <-Size/2.5,Size*2,0> scale <1.1,1,1> } translate <0,Size*1/256,0> }
//  object{ Shin texture{ Base translate <-Size/2.5,Size*2,0> scale <1.1,1,1> } translate <0,0,Size*1/256> }
//  object{ Shin texture{ Base2 translate <-Size/2.5,Size*2,0> scale <1.1,1,1> } translate <0,0,-Size*1/256> }
}
#declare L_Shin2 =
union{
  object{ Shin texture{ Suit_Texture translate <Size/2.5,0,0> } translate <0,Size*1/256,0> }
  object{ Shin texture{ Suit_Texture translate <Size/2.5,0,0> } translate <0,0,Size*1/256> }
  object{ Shin texture{ Suit_Texture translate <Size/2.5,0,0> } translate <0,0,-Size*1/256> }
//  object{ Shin texture{ Base translate <Size/2.5,Size*2,0> scale <1.1,1,1> } translate <0,Size*1/256,0> }
//  object{ Shin texture{ Base translate <Size/2.5,Size*2,0> scale <1.1,1,1> } translate <0,0,Size*1/256> }
//  object{ Shin texture{ Base2 translate <Size/2.5,Size*2,0> scale <1.1,1,1> } translate <0,0,-Size*1/256> }
}
#declare R_Foot2 =
union{
  object{ Foot texture{ Foot_Texture translate <-Size/2.5,0,0> } translate <0,Size*1/256,Size*1/256> }
  object{ Foot texture{ Foot_Texture translate <-Size/2.5,0,0> } translate <0,0,Size*1/256> }
  object{ Foot texture{ Foot_Texture translate <-Size/2.5,0,0> } translate <0,0,-Size*1/256> }
//  object{ Foot texture{ Base translate <-Size/2.5,Size*4,0> scale <1.2,1,1> } translate <0,Size*1/256,Size*1/256> }
//  object{ Foot texture{ Base translate <-Size/2.5,Size*4,0> scale <1.2,1,1> } translate <0,0,Size*1/256> }
//  object{ Foot texture{ Base2 translate <-Size/2.5,Size*4,0> scale <1.2,1,1> } translate <0,0,-Size*1/256> }
}
#declare L_Foot2 =
union{
  object{ Foot texture{ Foot_Texture translate <Size/2.5,0,0> } translate <0,Size*1/256,Size*1/256> }
  object{ Foot texture{ Foot_Texture translate <Size/2.5,0,0> } translate <0,0,Size*1/256> }
  object{ Foot texture{ Foot_Texture translate <Size/2.5,0,0> } translate <0,0,-Size*1/256> }
//  object{ Foot texture{ Base translate <Size/2.5,Size*4,0> scale <1.2,1,1> } translate <0,Size*1/256,Size*1/256> }
//  object{ Foot texture{ Base translate <Size/2.5,Size*4,0> scale <1.2,1,1> } translate <0,0,Size*1/256> }
//  object{ Foot texture{ Base2 translate <Size/2.5,Size*4,0> scale <1.2,1,1> } translate <0,0,-Size*1/256> }
}
#declare R_Upper_Arm2 =
union{
  object{ Upper_Arm texture{ Suit_Texture translate <-Size*1.15,0,0> } translate <0,0,Size*1/256> }
  object{ Upper_Arm texture{ Suit_Texture translate <-Size*1.15,0,0> } translate <0,0,-Size*1/256> }
}
#declare L_Upper_Arm2 =
union{
  object{ Upper_Arm texture{ Suit_Texture translate <Size*1.15,0,0> } translate <0,0,Size*1/256> }
  object{ Upper_Arm texture{ Suit_Texture translate <Size*1.15,0,0> } translate <0,0,-Size*1/256> }
}
#declare R_Forearm2 =
union{
  object{ Forearm texture{ Suit_Texture translate <-Size*1.15,0,0> } translate <-Size*1/256,0,0> }
  object{ Forearm texture{ Suit_Texture translate <-Size*1.15,0,0> } translate <Size*1/256,0,0> }
  object{ Forearm texture{ Suit_Texture translate <-Size*1.15,0,0> } translate <Size*1/256,Size*1/256,0> }
}
#declare L_Forearm2 =
union{
  object{ Forearm texture{ Suit_Texture translate <Size*1.15,0,0> } translate <-Size*1/256,0,0> }
  object{ Forearm texture{ Suit_Texture translate <Size*1.15,0,0> } translate <Size*1/256,0,0> }
  object{ Forearm texture{ Suit_Texture translate <Size*1.15,0,0> } translate <Size*1/256,Size*1/256,0> }
}
/***************************************************************************/
#declare Person =
union{
  union{
    object{ Chest
      texture{ Suit_Texture }
      translate <0,0,Size*1/256>
    }
    object{ Back
      texture{ Suit_Texture }
      translate <0,0,Size*-1/256>
    }
    union{
      object{ Neck2 }
      object{ Head2
        #if (Gender = 1)
          scale <0.925,1,1>
        #end
        #if (Gender = 2)
          scale <0.875,1,1>
        #end
        transform Head_Rotation
        #if (Gender = 1)
          translate <0,Size*0.3,Size/8>
        #end
        #if (Gender = 2)
          translate <0,Size*0.3,Size/12>
        #end
      }
      transform Neck_Rotation
//      translate <0,Size*0.25,Size/8>
      #if (Gender = 1)
        translate <0,Size*2.5,-Size/12>
      #end
      #if (Gender = 2)
        translate <0,Size*2.5,-Size/20>
      #end
    }

  #if (Gender = 1)
  union{	//right arm
    object{ R_Upper_Arm2 }
    union{
      object{ R_Forearm2 }
      object{ R_Hand scale 18/32 rotate <180,90,0> translate <0,-Size*8/16,Size*1/16>
        transform R_Hand_Rotation
        translate <0,-Size*17/16,0>
      }
      transform R_Elbow_Rotation
      translate <0,-Size*1.25,0>
    }
    rotate <0,0,3>
    transform R_Arm_Rotation
    translate <Size*0.85,Size*1.9,-Size/16>
  }
  union{	//left arm
    object{ L_Upper_Arm2 }
    union{
      object{ L_Forearm2 scale <-1,1,1> }
      object{ L_Hand scale 18/32 rotate <180,-90,0> translate <0,-Size*8/16,Size*1/16>
        transform L_Hand_Rotation
        translate <0,-Size*17/16,0>
      }
      transform L_Elbow_Rotation
      translate <0,-Size*1.25,0>
    }
    rotate <0,0,-3>
    transform L_Arm_Rotation
    translate <-Size*0.85,Size*1.9,-Size/16>
  }
  #end
  #if (Gender = 2)
  union{	//right arm
    object{ R_Upper_Arm2 }
    union{
      object{ R_Forearm2 }
      object{ R_Hand scale 17/32 rotate <180,90,0> translate <0,-Size*9/16,Size*3/32>
        transform R_Hand_Rotation
        translate <0,-Size*32/32,0>
      }
      transform R_Elbow_Rotation
      translate <0,-Size*1.25,0>
    }
    rotate <0,0,3>
    transform R_Arm_Rotation
    translate <Size*0.8,Size*1.9,-Size/16>
  }
  union{	//left arm
    object{ L_Upper_Arm2 }
    union{
      object{ L_Forearm2 scale <-1,1,1> }
      object{ L_Hand scale 17/32 rotate <180,-90,0> translate <0,-Size*9/16,Size*3/32>
        transform L_Hand_Rotation
        translate <0,-Size*32/32,0>
      }
      transform L_Elbow_Rotation
      translate <0,-Size*1.25,0>
    }
    rotate <0,0,-3>
    transform L_Arm_Rotation
    translate <-Size*0.8,Size*1.9,-Size/16>
  }
  #end
    transform Torso_Rotation
  }

#if (Gender = 1)
  union{	//right leg
    object{ R_Thigh2 }
    union{
      object{ R_Shin2 }
      object{ R_Foot2
        transform R_Foot_Rotation
        translate <0,-Size*2,0>
      }
      transform R_Shin_Rotation
      translate <0,-Size*2,0>
    }
    transform R_Leg_Rotation
    translate <Size/2.5*0.85,0,0>
  }
  union{	//left leg
    object{ L_Thigh2 }
    union{
      object{ L_Shin2 }
      object{ L_Foot2
        transform L_Foot_Rotation
        translate <0,-Size*2,0>
      }
      transform L_Shin_Rotation
      translate <0,-Size*2,0>
    }
    transform L_Leg_Rotation
    translate <-Size/2.5*0.85,0,0>
  }
#end
#if (Gender = 2)
  union{	//right leg
    object{ R_Thigh2 }
    union{
      object{ R_Shin2 }
      object{ R_Foot2
        transform R_Foot_Rotation
        translate <0,-Size*2,0>
      }
      transform R_Shin_Rotation
      translate <0,-Size*2,0>
    }
    transform R_Leg_Rotation
    translate <Size/2.75*0.9,0,0>
  }
  union{	//left leg
    object{ L_Thigh2 }
    union{
      object{ L_Shin2 }
      object{ L_Foot2
        transform L_Foot_Rotation
        translate <0,-Size*2,0>
      }
      transform L_Shin_Rotation
      translate <0,-Size*2,0>
    }
    transform L_Leg_Rotation
    translate <-Size/2.75*0.9,0,0>
  }
#end
}
