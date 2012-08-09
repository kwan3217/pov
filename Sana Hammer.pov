#declare Plastic = finish {
   phong 0.5
}

#declare Bellows = union {
   cone {
      <0, -0.15, 0>, 0.3,
      <0, 0, 0>, 0.5
      scale 1
      rotate <0, 0, 0>
      translate <0, 0, 0>
   }
   
   cone {
      <0, 0.15, 0>, 0.3,
      <0, 0, 0>, 0.5
      scale 1
      rotate <0, 0, 0>
      translate <0, 0, 0>
   }
}

global_settings {
   adc_bailout 0.00392157
   assumed_gamma 1.5
   noise_generator 2
}

#declare HammerHalf = union {
   object {
      Bellows
      scale 1
      rotate <0, 0, 0>
      translate <0, 0, 0>
   }
   
   object {
      Bellows
      scale 1
      rotate <0, 0, 0>
      translate y*0.3
   }
   
   object {
      Bellows
      scale 1
      rotate <0, 0, 0>
      translate y*(-0.3)
   }
   
   texture {
      pigment {
         color rgb <1, 0, 0>
      }
      
      finish {
         Plastic
      }
   }
   translate y*0.45
   scale <1, 0.6, 1>
}

light_source {
   <4, 5, -5>, rgb <1, 1, 1>
}

union {
   //*PMName Hammer
   
   union {
      //*PMName Handle
      
      cylinder {
         <0, 0.15, 0>, <0, -0.15, 0>, 0.3
         scale 1
         rotate <0, 0, 0>
         translate <0, 0, 0>
      }
      
      cylinder {
         <0, 0, 0>, <2, 0, 0>, 0.05
         scale 1
         rotate <0, 0, 0>
         translate <0, 0, 0>
      }
      
      texture {
         pigment {
            color rgb <1, 1, 0>
         }
         
         finish {
            Plastic
         }
      }
   }
   
   object {
      HammerHalf
      translate y*0.15
   }
   
   object {
      HammerHalf
      translate y*0.15
      rotate x*180
   }
   rotate x*20
}

camera {
   perspective
   location <5, 5, -5>
   sky <0, 1, 0>
   direction <0, 0, 1>
   right <1.3333, 0, 0>
   up <0, 1, 0>
   look_at <0, 0, 0>
   angle 20
}