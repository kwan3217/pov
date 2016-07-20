/***************************************************************************/
//		mantest.pov
/***************************************************************************/
global_settings{ max_trace_level 15 }

/*
#include "colors.inc"
  

#declare Vector = <0,0,5>
#declare Look_At = <0,0,0>
camera{
  location Vector
  look_at Look_At
} 

light_source{ (Vector + <0,0,0>) rgb 1 }


//light_source{ <0,0,0> rgb 1 }

plane{ y,32//.675
  pigment{ White }
}
*/
/***************************************************************************/

#declare R_Arm_Rotation = transform{ rotate -y*37 rotate z*30 rotate x*0 }
#declare R_Elbow_Rotation = transform{ rotate y*0 rotate x*-105 }
#declare R_Hand_Rotation = transform{ rotate z*30 rotate y*30 }
#declare R_Hand_Position = "relaxed"


#declare L_Arm_Rotation = transform{ rotate y*37 rotate -z*30 rotate x*0 }
#declare L_Elbow_Rotation = transform{ rotate y*0 rotate x*-105 }
#declare L_Hand_Rotation = transform{ rotate -z*30 rotate -y*30 }
#declare L_Hand_Position = "relaxed"

#declare R_Leg_Rotation = transform{ rotate z*2 rotate x*-32 }
#declare L_Leg_Rotation = transform{ rotate -z*2 rotate x*-28 }

#declare R_Shin_Rotation = transform{ rotate x*60 }
#declare L_Shin_Rotation = transform{ rotate x*61 }

#declare R_Foot_Rotation = transform{ rotate x*30 }
#declare L_Foot_Rotation = transform{ rotate x*28 }

#declare Height = 32;
#declare Breasts = 10/16;
#declare Gender = 1;
#declare Suit_Color = 5;
/***************************************************************************/
#include "person.inc"
/***************************************************************************/
#declare Astronaut=union{
  object{ Person   scale 1/11 }   
  box {
    <-0.8,-0.3,-0.1>,<0.8,0.3,0.1>
    pigment {Gray50}
    scale 1/3
    rotate x*30
    translate <0,0.27,0.35>
  }
}
/***************************************************************************/
