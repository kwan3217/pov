#declare Stripe = texture {
   pigment {
      planar
      
      color_map {
         [ 0.5 color rgbf <1, 1, 1, 1>
         ]
         [ 0.5 color rgb <1, 1, 1>
         ]
      }
   }
   scale 0.01
   rotate x*90
}

global_settings {
   assumed_gamma 1.5
   noise_generator 2
}

light_source {
   <4, 5, -5>, rgb <1, 1, 1>
}

sphere {
   <0, 0, 0>, 0.5
   
   texture {
      Stripe
      rotate y*30
   }
   
   texture {
      Stripe
      rotate y*60
   }
   
   texture {
      Stripe
      rotate y*90
   }
   
   texture {
      Stripe
      rotate y*120
   }
   
   texture {
      Stripe
      rotate y*150
   }
   
   texture {
      Stripe
      rotate y*180
   }
}

camera {
   perspective
   location <2, 2, -2>
   sky <0, 1, 0>
   direction <0, 0, 1>
   right <1.3333, 0, 0>
   up <0, 1, 0>
   look_at <0, 0, 0>
}