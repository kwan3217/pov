/***************************************************************************/
//		rotation.inc
/***************************************************************************/
//			Listing of Rotation Names

//Note:  Refer to this list rather than going
//       through the whole file.  Saves *LOTS* of time.

/*
For these, use:
  #declare Name_Of_Rotation =
    transform{
      (These can be in any order.)
      rotate x * angle
      rotate y * angle
      rotate z * angle
      (Due to POV-Ray's order of operation, don't use: rotate <x,y,z>)
    }

  Head_Rotation
  Neck_Rotation
  Torso_Rotation

  R_Arm_Rotation
    R_Elbow_Rotation
      R_Hand_Rotation

  L_Arm_Rotation
    L_Elbow_Rotation
      L_Hand_Rotation

  R_Leg_Rotation
    R_Shin_Rotation
      R_Foot_Rotation

  R_Leg_Rotation
    R_Shin_Rotation
      R_Foot_Rotation

For these, use:
  #declare Hand_Position = "name of hand position"

  Hand_Position
    "relaxed"
    "flat"
    "fist"
    "pointing finger"
    "the finger"
    "gun"
    "peace"

Or...you can rotate each individual finger/thumb:
  (Use the same transform setup as the limbs above.)
  "Curve" means how much the fingers will curve from the knuckle.
  "Rotation" means what the rotation for the ENTIRE finger.
  
  R_Index_Curve
  R_Index_Rotation
  R_Middle_Curve
  R_Middle_Rotation
  R_Ring_Curve
  R_Ring_Rotation
  R_Pinky_Curve
  R_Pinky_Rotation
  R_Thumb_Curve
  R_Thumb_Rotation

  L_Index_Curve
  L_Index_Rotation
  L_Middle_Curve
  L_Middle_Rotation
  L_Ring_Curve
  L_Ring_Rotation
  L_Pinky_Curve
  L_Pinky_Rotation
  L_Thumb_Curve
  L_Thumb_Rotation
*/  
/***************************************************************************/
//			The Head
/***************************************************************************/
#ifndef (Head_Rotation)
  #declare Head_Rotation = transform{ rotate 0 }
  #end
#ifndef (Neck_Rotation)
  #declare Neck_Rotation = transform{ rotate 0 }
  #end
/***************************************************************************/
//			The Torso
/***************************************************************************/
#ifndef (Torso_Rotation)
  #declare Torso_Rotation = transform{ rotate 0 }
  #end
/***************************************************************************/
//			The Arms
/***************************************************************************/
#ifndef (R_Arm_Rotation)
  #declare R_Arm_Rotation =
    transform{
      rotate y*0
      rotate z*5
      rotate x*0
    }
  #end
#ifndef (L_Arm_Rotation)
  #declare L_Arm_Rotation =
    transform{
      rotate y*0
      rotate z*-5
      rotate x*0
    }
  #end
#ifndef (R_Elbow_Rotation)
  #declare R_Elbow_Rotation =
    transform{
      rotate x*0
    }
  #end
#ifndef (L_Elbow_Rotation)
  #declare L_Elbow_Rotation =
    transform{
      rotate x*0
    }
  #end

#ifndef (R_Hand_Rotation)
  #declare R_Hand_Rotation =
    transform{
      rotate z*0
      rotate x*0
    }
  #end
#ifndef (L_Hand_Rotation)
  #declare L_Hand_Rotation =
    transform{
      rotate z*0
      rotate x*0
    }
  #end
/***************************************************************************/
//				The Legs
/***************************************************************************/
#ifndef (R_Leg_Rotation)
  #declare R_Leg_Rotation =
    transform{
      rotate y*0
      rotate z*0
      rotate x*0
    }
  #end
#ifndef (L_Leg_Rotation)
  #declare L_Leg_Rotation =
    transform{
      rotate y*0
      rotate z*0
      rotate x*0
    }
  #end

#ifndef (R_Shin_Rotation)
  #declare R_Shin_Rotation =
    transform{
      rotate x*0
    }
  #end
#ifndef (L_Shin_Rotation)
  #declare L_Shin_Rotation =
    transform{
      rotate x*0
    }
  #end

#ifndef (R_Foot_Rotation)
  #declare R_Foot_Rotation =
    transform{
      rotate y*0
      rotate z*0
      rotate x*0
    }
  #end
#ifndef (L_Foot_Rotation)
  #declare L_Foot_Rotation =
    transform{
      rotate y*0
      rotate z*0
      rotate x*0
    }
  #end
/***************************************************************************/
//				The Hands
//			(with preset hand positions)
/***************************************************************************/
#ifndef (R_Hand_Position) #declare R_Hand_Position = "relaxed" #end
#ifndef (L_Hand_Position) #declare L_Hand_Position = "relaxed" #end

#if (strcmp(R_Hand_Position, "relaxed" ) = 0)
  #declare R_Index_Curve = transform{ rotate x*10 }
  #declare R_Index_Rotation = transform{ rotate x*10 }
  #declare R_Middle_Curve = transform{ rotate x*10 }
  #declare R_Middle_Rotation = transform{ rotate x*10 }
  #declare R_Ring_Curve = transform{ rotate x*10 }
  #declare R_Ring_Rotation = transform{ rotate x*10 }
  #declare R_Pinky_Curve = transform{ rotate x*10 }
  #declare R_Pinky_Rotation = transform{ rotate x*10 }
  #declare R_Thumb_Curve = 10;
  #declare R_Thumb_Rotation = transform{ rotate z*35 rotate y*60 }
#end
#if (strcmp(L_Hand_Position, "relaxed" ) = 0)
  #declare L_Index_Curve = transform{ rotate x*10 }
  #declare L_Index_Rotation = transform{ rotate x*10 }
  #declare L_Middle_Curve = transform{ rotate x*10 }
  #declare L_Middle_Rotation = transform{ rotate x*10 }
  #declare L_Ring_Curve = transform{ rotate x*10 }
  #declare L_Ring_Rotation = transform{ rotate x*10 }
  #declare L_Pinky_Curve = transform{ rotate x*10 }
  #declare L_Pinky_Rotation = transform{ rotate x*10 }
  #declare L_Thumb_Curve = 10;
  #declare L_Thumb_Rotation = transform{ rotate -z*35 rotate -y*60 }
#end

#if (strcmp(R_Hand_Position, "flat" ) = 0)
  #declare R_Index_Curve = transform{ rotate x*0 }
  #declare R_Index_Rotation = transform{ rotate x*0 }
  #declare R_Middle_Curve = transform{ rotate x*0 }
  #declare R_Middle_Rotation = transform{ rotate x*0 }
  #declare R_Ring_Curve = transform{ rotate x*0 }
  #declare R_Ring_Rotation = transform{ rotate x*0 }
  #declare R_Pinky_Curve = transform{ rotate x*0 }
  #declare R_Pinky_Rotation = transform{ rotate x*0 }
  #declare R_Thumb_Curve = 0;
  #declare R_Thumb_Rotation = transform{ rotate z*10 rotate y*0 }
#end
#if (strcmp(L_Hand_Position, "flat" ) = 0)
  #declare L_Index_Curve = transform{ rotate x*0 }
  #declare L_Index_Rotation = transform{ rotate x*0 }
  #declare L_Middle_Curve = transform{ rotate x*0 }
  #declare L_Middle_Rotation = transform{ rotate x*0 }
  #declare L_Ring_Curve = transform{ rotate x*0 }
  #declare L_Ring_Rotation = transform{ rotate x*0 }
  #declare L_Pinky_Curve = transform{ rotate x*0 }
  #declare L_Pinky_Rotation = transform{ rotate x*0 }
  #declare L_Thumb_Curve = 0;
  #declare L_Thumb_Rotation = transform{ rotate z*-10 rotate -y*0 }
#end

#if (strcmp(R_Hand_Position, "fist" ) = 0)
  #declare R_Index_Curve = transform{ rotate x*80 }
  #declare R_Index_Rotation = transform{ rotate x*80 }
  #declare R_Middle_Curve = transform{ rotate x*80 }
  #declare R_Middle_Rotation = transform{ rotate x*80 }
  #declare R_Ring_Curve = transform{ rotate x*80 }
  #declare R_Ring_Rotation = transform{ rotate x*80 }
  #declare R_Pinky_Curve = transform{ rotate x*80 }
  #declare R_Pinky_Rotation = transform{ rotate x*80 }
  #declare R_Thumb_Curve = 70;
  #declare R_Thumb_Rotation = transform{ rotate z*60 rotate y*80 }
#end
#if (strcmp(L_Hand_Position, "fist" ) = 0)
  #declare L_Index_Curve = transform{ rotate x*80 }
  #declare L_Index_Rotation = transform{ rotate x*80 }
  #declare L_Middle_Curve = transform{ rotate x*80 }
  #declare L_Middle_Rotation = transform{ rotate x*80 }
  #declare L_Ring_Curve = transform{ rotate x*80 }
  #declare L_Ring_Rotation = transform{ rotate x*80 }
  #declare L_Pinky_Curve = transform{ rotate x*80 }
  #declare L_Pinky_Rotation = transform{ rotate x*80 }
  #declare L_Thumb_Curve = 70;
  #declare L_Thumb_Rotation = transform{ rotate -z*60 rotate -y*80 }
#end

#if (strcmp(R_Hand_Position, "pointing finger" ) = 0)
  #declare R_Index_Curve = transform{ rotate x*10 }
  #declare R_Index_Rotation = transform{ rotate x*-10 }
  #declare R_Middle_Curve = transform{ rotate x*80 }
  #declare R_Middle_Rotation = transform{ rotate x*80 }
  #declare R_Ring_Curve = transform{ rotate x*70 }
  #declare R_Ring_Rotation = transform{ rotate x*80 }
  #declare R_Pinky_Curve = transform{ rotate x*60 }
  #declare R_Pinky_Rotation = transform{ rotate x*80 }
  #declare R_Thumb_Curve = 40
  #declare R_Thumb_Rotation = transform{ rotate z*60 rotate y*100 }
#end
#if (strcmp(L_Hand_Position, "pointing finger" ) = 0)
  #declare L_Index_Curve = transform{ rotate x*10 }
  #declare L_Index_Rotation = transform{ rotate x*-10 }
  #declare L_Middle_Curve = transform{ rotate x*80 }
  #declare L_Middle_Rotation = transform{ rotate x*80 }
  #declare L_Ring_Curve = transform{ rotate x*70 }
  #declare L_Ring_Rotation = transform{ rotate x*80 }
  #declare L_Pinky_Curve = transform{ rotate x*60 }
  #declare L_Pinky_Rotation = transform{ rotate x*80 }
  #declare L_Thumb_Curve = 40
  #declare L_Thumb_Rotation = transform{ rotate -z*60 rotate -y*100 }
#end

#if (strcmp(R_Hand_Position, "the finger" ) = 0)
  #declare R_Index_Curve = transform{ rotate x*80 }
  #declare R_Index_Rotation = transform{ rotate y*15 rotate x*80 }
  #declare R_Middle_Curve = transform{ rotate x*10 }
  #declare R_Middle_Rotation = transform{ rotate x*10 }
  #declare R_Ring_Curve = transform{ rotate x*70 }
  #declare R_Ring_Rotation = transform{ rotate y*-20 rotate x*80 }
  #declare R_Pinky_Curve = transform{ rotate x*70 }
  #declare R_Pinky_Rotation = transform{ rotate y*-20 rotate x*80 }
  #declare R_Thumb_Curve = 70
  #declare R_Thumb_Rotation = transform{ rotate z*60 rotate y*80 }
#end
#if (strcmp(L_Hand_Position, "the finger" ) = 0)
  #declare L_Index_Curve = transform{ rotate x*80 }
  #declare L_Index_Rotation = transform{ rotate -y*15 rotate x*80 }
  #declare L_Middle_Curve = transform{ rotate x*10 }
  #declare L_Middle_Rotation = transform{ rotate x*10 }
  #declare L_Ring_Curve = transform{ rotate x*70 }
  #declare L_Ring_Rotation = transform{ rotate y*20 rotate x*80 }
  #declare L_Pinky_Curve = transform{ rotate x*70 }
  #declare L_Pinky_Rotation = transform{ rotate y*20 rotate x*80 }
  #declare L_Thumb_Curve = 70
  #declare L_Thumb_Rotation = transform{ rotate -z*60 rotate -y*80 }
#end

#if (strcmp(R_Hand_Position, "gun" ) = 0)
  #declare R_Index_Curve = transform{ rotate x*10 }
  #declare R_Index_Rotation = transform{ rotate x*-20 }
  #declare R_Middle_Curve = transform{ rotate x*10 }
  #declare R_Middle_Rotation = transform{ rotate x*-20 }
  #declare R_Ring_Curve = transform{ rotate x*80 }
  #declare R_Ring_Rotation = transform{ rotate x*80 }
  #declare R_Pinky_Curve = transform{ rotate x*80 }
  #declare R_Pinky_Rotation = transform{ rotate x*80 }
  #declare R_Thumb_Curve = 5
  #declare R_Thumb_Rotation = transform{ rotate z*10 rotate y*0 }
#end
#if (strcmp(L_Hand_Position, "gun" ) = 0)
  #declare L_Index_Curve = transform{ rotate x*10 }
  #declare L_Index_Rotation = transform{ rotate x*-20 }
  #declare L_Middle_Curve = transform{ rotate x*10 }
  #declare L_Middle_Rotation = transform{ rotate x*-20 }
  #declare L_Ring_Curve = transform{ rotate x*80 }
  #declare L_Ring_Rotation = transform{ rotate x*80 }
  #declare L_Pinky_Curve = transform{ rotate x*80 }
  #declare L_Pinky_Rotation = transform{ rotate x*80 }
  #declare L_Thumb_Curve = 5
  #declare L_Thumb_Rotation = transform{ rotate -z*10 rotate -y*0 }
#end

#if (strcmp(R_Hand_Position, "peace" ) = 0)
  #declare R_Index_Curve = transform{ rotate x*0 }
  #declare R_Index_Rotation = transform{ rotate z*20 rotate x*0 }
  #declare R_Middle_Curve = transform{ rotate x*0 }
  #declare R_Middle_Rotation = transform{ rotate -z*20 rotate x*0 }
  #declare R_Ring_Curve = transform{ rotate x*80 }
  #declare R_Ring_Rotation = transform{ rotate y*-20 rotate x*80 }
  #declare R_Pinky_Curve = transform{ rotate x*70 }
  #declare R_Pinky_Rotation = transform{ rotate y*-20 rotate x*80 }
  #declare R_Thumb_Curve = 30
  #declare R_Thumb_Rotation = transform{ rotate z*60 rotate y*110 }
#end
#if (strcmp(L_Hand_Position, "peace" ) = 0)
  #declare L_Index_Curve = transform{ rotate x*0 }
  #declare L_Index_Rotation = transform{ rotate -z*20 rotate x*0 }
  #declare L_Middle_Curve = transform{ rotate x*0 }
  #declare L_Middle_Rotation = transform{ rotate z*20 rotate x*0 }
  #declare L_Ring_Curve = transform{ rotate x*80 }
  #declare L_Ring_Rotation = transform{ rotate y*20 rotate x*80 }
  #declare L_Pinky_Curve = transform{ rotate x*70 }
  #declare L_Pinky_Rotation = transform{ rotate y*20 rotate x*80 }
  #declare L_Thumb_Curve = 30
  #declare L_Thumb_Rotation = transform{ rotate -z*60 rotate -y*110 }
#end
/***************************************************************************/
#ifndef (R_Index_Rotation)
  #declare R_Index_Rotation =
    transform{
      rotate x*0
      rotate z*0
    }
  #end
#ifndef (R_Index_Curve)
  #declare R_Index_Curve =
    transform{ rotate x*0 }
  #end
#ifndef (L_Index_Rotation)
  #declare L_Index_Rotation =
    transform{
      rotate x*0
      rotate z*0
    }
  #end
#ifndef (L_Index_Curve)
  #declare L_Index_Curve =
    transform{ rotate x*0 }
  #end

#ifndef (R_Middle_Rotation)
  #declare R_Middle_Rotation =
    transform{
      rotate x*0
      rotate z*0
    }
  #end
#ifndef (R_Middle_Curve)
  #declare R_Middle_Curve =
    transform{ rotate x*0 }
  #end
#ifndef (L_Middle_Rotation)
  #declare L_Middle_Rotation =
    transform{
      rotate x*0
      rotate z*0
    }
  #end
#ifndef (L_Middle_Curve)
  #declare L_Middle_Curve =
    transform{ rotate x*0 }
  #end

#ifndef (R_Ring_Rotation)
  #declare R_Ring_Rotation =
    transform{
      rotate x*0
      rotate z*0
    }
  #end
#ifndef (R_Ring_Curve)
  #declare R_Ring_Curve =
    transform{ rotate x*0 }
  #end
#ifndef (L_Ring_Rotation)
  #declare L_Ring_Rotation =
    transform{
      rotate x*0
      rotate z*0
    }
  #end
#ifndef (L_Ring_Curve)
  #declare L_Ring_Curve =
    transform{ rotate x*0 }
  #end

#ifndef (R_Pinky_Rotation)
  #declare R_Pinky_Rotation =
    transform{
      rotate x*0
      rotate z*0
    }
  #end
#ifndef (R_Pinky_Curve)
  #declare R_Pinky_Curve =
    transform{ rotate x*0 }
  #end
#ifndef (L_Pinky_Rotation)
  #declare L_Pinky_Rotation =
    transform{
      rotate x*0
      rotate z*0
    }
  #end
#ifndef (L_Pinky_Curve)
  #declare L_Pinky_Curve =
    transform{ rotate x*0 }
  #end

#ifndef (R_Thumb_Rotation)
  #declare R_Thumb_Rotation =
    transform{
      rotate z*10
      rotate y*0
    }
  #end
#ifndef (R_Thumb_Curve)
  #declare R_Thumb_Curve = 0
  #end
#declare R_Thumb_Angle = transform{ rotate x*R_Thumb_Curve }
#declare R_Thumb_Curve2 = R_Thumb_Curve;
#if (R_Thumb_Curve2 > 25)
  #declare R_Thumb_Curve2 = 10;
  #end
#ifndef (R_Thumb_Angle2)
  #declare R_Thumb_Angle2 =
    transform{ rotate x*R_Thumb_Curve2 }
  #end
#ifndef (L_Thumb_Rotation)
  #declare L_Thumb_Rotation =
    transform{
      rotate z*10
      rotate y*0
    }
  #end
#ifndef (L_Thumb_Curve)
  #declare L_Thumb_Curve = 0;
  #end
#declare L_Thumb_Angle = transform{ rotate x*L_Thumb_Curve }
#declare L_Thumb_Curve2 = L_Thumb_Curve;
#if (L_Thumb_Curve2 > 25)
  #declare L_Thumb_Curve2 = 10;
  #end
#ifndef (L_Thumb_Angle2)
  #declare L_Thumb_Angle2 =
    transform{ rotate x*L_Thumb_Curve2 }
  #end
