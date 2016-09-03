/***************************************************************************/
//		hands.inc
/***************************************************************************/
//				The Index Finger
/***************************************************************************/
#declare Index1 =
blob{
  threshold T
  
  //parent joint
  sphere{ 0,R,S scale Size/10 }

  //main piece
  cylinder{ 0, <0,Size*1/3,0>, R*Size/8,S }
  
  //child joint
  sphere{ 0,R,S scale Size/10 translate <0,Size*1/3,0> }
}
#declare Index2 =
blob{
  threshold T
  
  //parent joint
  sphere{ 0,R,S scale Size/10 }

  //main piece
  cylinder{ 0, <0,Size*5/24,0>, R*Size/8,S }
  
  //child joint
  sphere{ 0,R,S scale Size/10 translate <0,Size*5/24,0> }
}
#declare Index3 =
blob{
  threshold T
  
  //parent joint
  sphere{ 0,R,S scale Size/10 }

  //main piece
  cylinder{ 0, <0,Size*1/6,0>, R*Size/8,S }
}

#declare Index1_2 =
union{
  object{ Index1 translate <0,0,Size/256>
    texture{ Hand_Texture }
  }
  object{ Index1 translate <0,0,-Size/256>
    texture{ Hand_Texture }
  }
}
#declare Index2_2 =
union{
  object{ Index2 translate <0,0,Size/256>
    texture{ Hand_Texture }
  }
  object{ Index2 translate <0,0,-Size/256>
    texture{ Hand_Texture }
  }
}
#declare Index3_2 =
union{
  object{ Index3 translate <0,0,Size/256>
    texture{ Hand_Texture }
  }
  object{ Index3 translate <0,0,-Size/256>
    texture{ Hand_Texture }
  }
}
/***************************************************************************/
//				The Middle Finger
/***************************************************************************/
#declare Middle1 =
blob{
  threshold T
  
  //parent joint
  sphere{ 0,R,S scale Size/10 }

  //main piece
  cylinder{ 0, <0,Size*3/8,0>, R*Size/8,S }
  
  //child joint
  sphere{ 0,R,S scale Size/10 translate <0,Size*1/3,0> }
}
#declare Middle2 =
blob{
  threshold T
  
  //parent joint
  sphere{ 0,R,S scale Size/10 }

  //main piece
  cylinder{ 0, <0,Size*5/24,0>, R*Size/8,S }
  
  //child joint
  sphere{ 0,R,S scale Size/10 translate <0,Size*5/24,0> }
}
#declare Middle3 =
blob{
  threshold T
  
  //parent joint
  sphere{ 0,R,S scale Size/10 }

  //main piece
  cylinder{ 0, <0,Size*5/24,0>, R*Size/8,S }
}

#declare Middle1_2 =
union{
  object{ Middle1 translate <0,0,Size/256>
    texture{ Hand_Texture }
  }
  object{ Middle1 translate <0,0,-Size/256>
    texture{ Hand_Texture }
  }
}
#declare Middle2_2 =
union{
  object{ Middle2 translate <0,0,Size/256>
    texture{ Hand_Texture }
  }
  object{ Middle2 translate <0,0,-Size/256>
    texture{ Hand_Texture }
  }
}
#declare Middle3_2 =
union{
  object{ Middle3 translate <0,0,Size/256>
    texture{ Hand_Texture }
  }
  object{ Middle3 translate <0,0,-Size/256>
    texture{ Hand_Texture }
  }
}
/***************************************************************************/
//				The Ring Finger
/***************************************************************************/
#declare Ring1 =
blob{
  threshold T
  
  //parent joint
  sphere{ 0,R,S scale Size/10 }

  //main piece
  cylinder{ 0, <0,Size*3/8,0>, R*Size/8,S }
  
  //child joint
  sphere{ 0,R,S scale Size/10 translate <0,Size*1/3,0> }
}
#declare Ring2 =
blob{
  threshold T
  
  //parent joint
  sphere{ 0,R,S scale Size/10 }

  //main piece
  cylinder{ 0, <0,Size*5/24,0>, R*Size/8,S }
  
  //child joint
  sphere{ 0,R,S scale Size/10 translate <0,Size*5/24,0> }
}
#declare Ring3 =
blob{
  threshold T
  
  //parent joint
  sphere{ 0,R,S scale Size/10 }

  //main piece
  cylinder{ 0, <0,Size*5/24,0>, R*Size/8,S }
}

#declare Ring1_2 =
union{
  object{ Ring1 translate <0,0,Size/256>
    texture{ Hand_Texture }
  }
  object{ Ring1 translate <0,0,-Size/256>
    texture{ Hand_Texture }
  }
}
#declare Ring2_2 =
union{
  object{ Ring2 translate <0,0,Size/256>
    texture{ Hand_Texture }
  }
  object{ Ring2 translate <0,0,-Size/256>
    texture{ Hand_Texture }
  }
}
#declare Ring3_2 =
union{
  object{ Ring3 translate <0,0,Size/256>
    texture{ Hand_Texture }
  }
  object{ Ring3 translate <0,0,-Size/256>
    texture{ Hand_Texture }
  }
}
/***************************************************************************/
//				The Pinky Finger
/***************************************************************************/
#declare Pinky1 =
blob{
  threshold T
  
  //parent joint
  sphere{ 0,R,S scale Size/10 }

  //main piece
  cylinder{ 0, <0,Size*1/4,0>, R*Size/8,S }
  
  //child joint
  sphere{ 0,R,S scale Size/10 translate <0,Size*1/4,0> }
}
#declare Pinky2 =
blob{
  threshold T
  
  //parent joint
  sphere{ 0,R,S scale Size/10 }

  //main piece
  cylinder{ 0, <0,Size*1/6,0>, R*Size/8,S }
  
  //child joint
  sphere{ 0,R,S scale Size/10 translate <0,Size*1/6,0> }
}
#declare Pinky3 =
blob{
  threshold T
  
  //parent joint
  sphere{ 0,R,S scale Size/10 }

  //main piece
  cylinder{ 0, <0,Size*1/6,0>, R*Size/8,S }
}

#declare Pinky1_2 =
union{
  object{ Pinky1 translate <0,0,Size/256>
    texture{ Hand_Texture }
  }
  object{ Pinky1 translate <0,0,-Size/256>
    texture{ Hand_Texture }
  }
}
#declare Pinky2_2 =
union{
  object{ Pinky2 translate <0,0,Size/256>
    texture{ Hand_Texture }
  }
  object{ Pinky2 translate <0,0,-Size/256>
    texture{ Hand_Texture }
  }
}
#declare Pinky3_2 =
union{
  object{ Pinky3 translate <0,0,Size/256>
    texture{ Hand_Texture }
  }
  object{ Pinky3 translate <0,0,-Size/256>
    texture{ Hand_Texture }
  }
}
/***************************************************************************/
//				The Thumb
/***************************************************************************/
#declare R_Thumb1 =
blob{
  threshold T
  
  //the slanted thumb-pad-type-thing
  sphere{ 0,R,S scale <Size*9/50,Size*3/10,Size*9/60> translate <Size*1/16,Size*3/20,0> }
  
  //the joint
  sphere{ 0,R,S scale Size/10 translate <0,Size*1/3,0> }
}
#declare L_Thumb1 =
blob{
  threshold T
  
  //the slanted thumb-pad-type-thing
  sphere{ 0,R,S scale <Size*9/50,Size*3/10,Size*9/60> translate <-Size*1/16,Size*3/20,0> }
  
  //the joint
  sphere{ 0,R,S scale Size/10 translate <0,Size*1/3,0> }
}
#declare Thumb2 =
blob{
  threshold T
  
  //parent joint
  sphere{ 0,R,S scale Size/10 }

  //main piece
  cylinder{ 0, <0,Size*9/40,0>, R*Size/8,S }
  
  //child joint
  sphere{ 0,R,S scale Size/10 translate <0,Size*1/5,0> }
}
#declare Thumb3 =
blob{
  threshold T
  
  //parent joint
  sphere{ 0,R,S scale Size/10 }

  //main piece
  cylinder{ 0, <0,Size*9/40,0>, R*Size/8,S }
  
  //child joint
  sphere{ 0,R,S scale Size/10 translate <0,Size*1/5,0> }
}

#declare R_Thumb1_2 =
union{
  object{ R_Thumb1 translate <0,0,Size/256>
    texture{ Hand_Texture }
  }
  object{ R_Thumb1 translate <0,0,-Size/256>
    texture{ Hand_Texture }
  }
}
#declare L_Thumb1_2 =
union{
  object{ L_Thumb1 translate <0,0,Size/256>
    texture{ Hand_Texture }
  }
  object{ L_Thumb1 translate <0,0,-Size/256>
    texture{ Hand_Texture }
  }
}
#declare Thumb2_2 =
union{
  object{ Thumb2 translate <0,0,Size/256>
    texture{ Hand_Texture }
  }
  object{ Thumb2 translate <0,0,-Size/256>
    texture{ Hand_Texture }
  }
}
#declare Thumb3_2 =
union{
  object{ Thumb3 translate <0,0,Size/256>
    texture{ Hand_Texture }
  }
  object{ Thumb3 translate <0,0,-Size/256>
    texture{ Hand_Texture }
  }
}
/***************************************************************************/
//			Construct The Fingers
/***************************************************************************/
#declare R_Index_Finger =
union{
  object{ Index1_2 }
  union{
    object{ Index2_2 }
    object{ Index3_2
      transform R_Index_Curve
      translate <0,Size*5/24,0>
    }
    transform R_Index_Curve
    translate <0,Size*1/3,0>
  }
  transform R_Index_Rotation
}
#declare L_Index_Finger =
union{
  object{ Index1_2 }
  union{
    object{ Index2_2 }
    object{ Index3_2
      transform L_Index_Curve
      translate <0,Size*5/24,0>
    }
    transform L_Index_Curve
    translate <0,Size*1/3,0>
  }
  transform L_Index_Rotation
}
#declare R_Middle_Finger =
union{
  object{ Middle1_2 }
  union{
    object{ Middle2_2 }
    object{ Middle3_2
      transform R_Middle_Curve
      translate <0,Size*5/24,0>
    }
    transform R_Middle_Curve
    translate <0,Size*3/8,0>
  }
  transform R_Middle_Rotation
}
#declare L_Middle_Finger =
union{
  object{ Middle1_2 }
  union{
    object{ Middle2_2 }
    object{ Middle3_2
      transform L_Middle_Curve
      translate <0,Size*5/24,0>
    }
    transform L_Middle_Curve
    translate <0,Size*3/8,0>
  }
  transform L_Middle_Rotation
}
#declare R_Ring_Finger =
union{
  object{ Ring1_2 }
  union{
    object{ Ring2_2 }
    object{ Ring3_2
      transform R_Ring_Curve
      translate <0,Size*5/24,0>
    }
    transform R_Ring_Curve
    translate <0,Size*3/8,0>
  }
  transform R_Ring_Rotation
}
#declare L_Ring_Finger =
union{
  object{ Ring1_2 }
  union{
    object{ Ring2_2 }
    object{ Ring3_2
      transform L_Ring_Curve
      translate <0,Size*5/24,0>
    }
    transform L_Ring_Curve
    translate <0,Size*3/8,0>
  }
  transform L_Ring_Rotation
}
#declare R_Pinky_Finger =
union{
  object{ Pinky1_2 }
  union{
    object{ Pinky2_2 }
    object{ Pinky3_2
      transform R_Pinky_Curve
      translate <0,Size*1/6,0>
    }
    transform R_Pinky_Curve
    translate <0,Size*1/4,0>
  }
  transform R_Pinky_Rotation
}
#declare L_Pinky_Finger =
union{
  object{ Pinky1_2 }
  union{
    object{ Pinky2_2 }
    object{ Pinky3_2
      transform L_Pinky_Curve
      translate <0,Size*1/6,0>
    }
    transform L_Pinky_Curve
    translate <0,Size*1/4,0>
  }
  transform L_Pinky_Rotation
}
#declare R_Thumb =
union{
  object{ R_Thumb1_2 }
  union{
    object{ Thumb2_2 }
    object{ Thumb3_2
      transform R_Thumb_Angle
      translate <0,Size*9/40,0>
    }
    transform R_Thumb_Angle2
    rotate <0,0,0>
    translate <0,Size*1/3,0>
  }
  transform R_Thumb_Rotation
}
#declare L_Thumb =
union{
  object{ L_Thumb1_2 }
  union{
    object{ Thumb2_2 }
    object{ Thumb3_2
      transform L_Thumb_Angle
      translate <0,Size*9/40,0>
    }
    transform L_Thumb_Angle2
    rotate <0,0,0>
    translate <0,Size*1/3,0>
  }
  transform L_Thumb_Rotation
}
/***************************************************************************/
//				The Palm
/***************************************************************************/
#declare R_Palm =
blob{
  threshold T
  
  //the knuckles
  sphere{ 0,R,S scale Size/10 translate <-Size*1/4,0,0> }
  sphere{ 0,R,S scale Size/10 translate <0,0,0> }
  sphere{ 0,R,S scale Size/10 translate <Size*1/4,0,0> }
  sphere{ 0,R,S scale Size/10 translate <Size*1/2,0,0> }
  sphere{ 0,R,S scale Size/8.0 translate <-Size*1/8,-Size*1/16,0> }
  sphere{ 0,R,S scale Size/8.0 translate <Size*1/8,-Size*1/16,0> }
  sphere{ 0,R,S scale Size/8.0 translate <Size*3/8,-Size*1/16,0> }
  
  //back of the hand near the knuckles
  sphere{ 0,R,S scale Size/8 translate <-Size/4,-Size/8,0> }
  sphere{ 0,R,S scale Size/8 translate <0,-Size/8,0> }
  sphere{ 0,R,S scale Size/8 translate <Size/4,-Size/8,0> }
  sphere{ 0,R,S scale Size/8 translate <Size/2,-Size/8,0> }
  
  //slanted thumb-pad-type-thing
  sphere{ 0,R,S scale <Size*9/50,Size*3/10,Size*9/60> translate <Size*1/16,Size*3/20,0>
    transform R_Thumb_Rotation translate <-Size*3/8,-Size/2,0>
  }
  
  //back of the hand
  sphere{ 0,R,S scale <Size*1/7,Size*1/3,Size*1/7> translate <-Size*2/8,-Size*1/4,0> }
  sphere{ 0,R,S scale <Size*1/4,Size*1/3,Size*1/8> translate <-Size*1/8,-Size*1/4,0> }
  sphere{ 0,R,S scale <Size*1/4,Size*1/3,Size*1/8> translate <Size*0/8,-Size*1/4,-Size*1/32> }
  sphere{ 0,R,S scale <Size*1/4,Size*1/3,Size*1/8> translate <Size*1/8,-Size*1/4,-Size*1/32> }
  sphere{ 0,R,S scale <Size*1/4,Size*1/3,Size*1/8> translate <Size*2/8,-Size*1/4,-Size*1/32> }
  sphere{ 0,R,S scale <Size*1/4,Size*1/3,Size*1/8> translate <Size*3/8,-Size*1/4,0> }
  sphere{ 0,R,S scale <Size*1/7,Size*1/3,Size*1/8> rotate <0,0,-15> translate <Size*7/16,-Size*1/4,0> }
  
  //section near the wrist
  sphere{ 0,R,S scale Size*1/6 translate <-Size*2/8,-Size*9/16,0> }
  sphere{ 0,R,S scale Size*1/6 translate <-Size*1/8,-Size*10/16,0> }
  sphere{ 0,R,S scale Size*1/6 translate <Size*0/8,-Size*10/16,0> }
  sphere{ 0,R,S scale Size*1/6 translate <Size*1/8,-Size*10/16,0> }
  sphere{ 0,R,S scale Size*1/6 translate <Size*2/8,-Size*10/16,0> }
//  sphere{ 0,R,S scale Size*1/7 translate <Size*3/8,-Size*10/16,0> }
//  sphere{ 0,R,S scale Size*1/7 translate <Size*4/8,-Size*9/16,0> }

  sphere{ 0,R,S scale Size*1/6 translate <-Size*1/8,-Size*8/16,0> }
  sphere{ 0,R,S scale Size*1/6 translate <Size*0/8,-Size*8/16,0> }
  sphere{ 0,R,S scale Size*1/6 translate <Size*1/8,-Size*8/16,0> }
  sphere{ 0,R,S scale Size*1/6 translate <Size*2/8,-Size*8/16,0> }
//  sphere{ 0,R,S scale Size*1/7 translate <Size*3/8,-Size*8/16,0> }
  
  //start of the fingers
  cylinder{ 0, <0,Size*1/3,0>, R*Size*1/16,S
    transform R_Index_Rotation translate <-Size*1/4,0,0>
  }
  cylinder{ 0, <0,Size*1/3,0>, R*Size*1/16,S
    transform R_Middle_Rotation translate <Size*0/4,0,0>
  }
  cylinder{ 0, <0,Size*1/3,0>, R*Size*1/16,S
    transform R_Ring_Rotation translate <Size*1/4,0,0>
  }
  cylinder{ 0, <0,Size*1/4,0>, R*Size*1/16,S
    transform R_Pinky_Rotation translate <Size*2/4,0,0>
  }
  
}
#declare L_Palm =
blob{
  threshold T
  
  //the knuckles
  sphere{ 0,R,S scale Size/10 translate <Size*1/4,0,0> }
  sphere{ 0,R,S scale Size/10 translate <0,0,0> }
  sphere{ 0,R,S scale Size/10 translate <-Size*1/4,0,0> }
  sphere{ 0,R,S scale Size/10 translate <-Size*1/2,0,0> }
  sphere{ 0,R,S scale Size/8.0 translate <Size*1/8,-Size*1/16,0> }
  sphere{ 0,R,S scale Size/8.0 translate <-Size*1/8,-Size*1/16,0> }
  sphere{ 0,R,S scale Size/8.0 translate <-Size*3/8,-Size*1/16,0> }
  
  //back of the hand near the knuckles
  sphere{ 0,R,S scale Size/8 translate <Size/4,-Size/8,0> }
  sphere{ 0,R,S scale Size/8 translate <0,-Size/8,0> }
  sphere{ 0,R,S scale Size/8 translate <-Size/4,-Size/8,0> }
  sphere{ 0,R,S scale Size/8 translate <-Size/2,-Size/8,0> }
  
  //slanted thumb-pad-type-thing
  sphere{ 0,R,S scale <Size*9/50,Size*3/10,Size*9/60> translate <-Size*1/16,Size*3/20,0>
    transform L_Thumb_Rotation translate <Size*3/8,-Size/2,0>
  }
  
  //back of the hand
  sphere{ 0,R,S scale <Size*1/7,Size*1/3,Size*1/7> translate <Size*2/8,-Size*1/4,0> }
  sphere{ 0,R,S scale <Size*1/4,Size*1/3,Size*1/8> translate <Size*1/8,-Size*1/4,0> }
  sphere{ 0,R,S scale <Size*1/4,Size*1/3,Size*1/8> translate <-Size*0/8,-Size*1/4,-Size*1/32> }
  sphere{ 0,R,S scale <Size*1/4,Size*1/3,Size*1/8> translate <-Size*1/8,-Size*1/4,-Size*1/32> }
  sphere{ 0,R,S scale <Size*1/4,Size*1/3,Size*1/8> translate <-Size*2/8,-Size*1/4,-Size*1/32> }
  sphere{ 0,R,S scale <Size*1/4,Size*1/3,Size*1/8> translate <-Size*3/8,-Size*1/4,0> }
  sphere{ 0,R,S scale <Size*1/7,Size*1/3,Size*1/8> rotate <0,0,15> translate <-Size*7/16,-Size*1/4,0> }
  
  //section near the wrist
  sphere{ 0,R,S scale Size*1/6 translate <Size*2/8,-Size*9/16,0> }
  sphere{ 0,R,S scale Size*1/6 translate <Size*1/8,-Size*10/16,0> }
  sphere{ 0,R,S scale Size*1/6 translate <-Size*0/8,-Size*10/16,0> }
  sphere{ 0,R,S scale Size*1/6 translate <-Size*1/8,-Size*10/16,0> }
  sphere{ 0,R,S scale Size*1/6 translate <-Size*2/8,-Size*10/16,0> }
//  sphere{ 0,R,S scale Size*1/7 translate <-Size*3/8,-Size*10/16,0> }
//  sphere{ 0,R,S scale Size*1/7 translate <-Size*4/8,-Size*9/16,0> }

  sphere{ 0,R,S scale Size*1/6 translate <Size*1/8,-Size*8/16,0> }
  sphere{ 0,R,S scale Size*1/6 translate <-Size*0/8,-Size*8/16,0> }
  sphere{ 0,R,S scale Size*1/6 translate <-Size*1/8,-Size*8/16,0> }
  sphere{ 0,R,S scale Size*1/6 translate <-Size*2/8,-Size*8/16,0> }
//  sphere{ 0,R,S scale Size*1/7 translate <-Size*3/8,-Size*8/16,0> }
  
  //start of the fingers
  cylinder{ 0, <0,Size*1/3,0>, R*Size*1/16,S
    transform L_Index_Rotation translate <Size*1/4,0,0>
  }
  cylinder{ 0, <0,Size*1/3,0>, R*Size*1/16,S
    transform L_Middle_Rotation translate <-Size*0/4,0,0>
  }
  cylinder{ 0, <0,Size*1/3,0>, R*Size*1/16,S
    transform L_Ring_Rotation translate <-Size*1/4,0,0>
  }
  cylinder{ 0, <0,Size*1/4,0>, R*Size*1/16,S
    transform L_Pinky_Rotation translate <-Size*2/4,0,0>
  }
  
}
#declare R_Palm2 =
union{
  object{ R_Palm translate <0,Size/256,0>
    texture{ Hand_Texture }
  }
  object{ R_Palm translate <0,0,Size/256>
    texture{ Hand_Texture }
  }
  object{ R_Palm translate <0,0,-Size/256>
    texture{ Hand_Texture }
  }
}
#declare L_Palm2 =
union{
  object{ L_Palm translate <0,Size/256,0>
    texture{ Hand_Texture }
  }
  object{ L_Palm translate <0,0,Size/256>
    texture{ Hand_Texture }
  }
  object{ L_Palm translate <0,0,-Size/256>
    texture{ Hand_Texture }
  }
}
/***************************************************************************/
#declare R_Hand =
union{
  object{ R_Thumb translate <-Size*3/8,-Size/2,0> }
  object{ R_Index_Finger translate <-Size/4,0,0> }
  object{ R_Middle_Finger translate <0,0,0> }
  object{ R_Ring_Finger translate <Size/4,0,0> }
  object{ R_Pinky_Finger translate <Size/2,0,0> }
  object{ R_Palm2 }
}
#declare L_Hand =
union{
  object{ L_Thumb translate <Size*3/8,-Size/2,0> }
  object{ L_Index_Finger translate <Size/4,0,0> }
  object{ L_Middle_Finger translate <0,0,0> }
  object{ L_Ring_Finger translate <-Size/4,0,0> }
  object{ L_Pinky_Finger translate <-Size/2,0,0> }
  object{ L_Palm2 }
}
