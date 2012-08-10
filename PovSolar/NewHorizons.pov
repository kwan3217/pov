#declare White = pigment {
   color rgb <1, 1, 1>
}

#declare RTGMetal = pigment {
   color rgb <0.1, 0.1, 0.1>
}

#declare Aluminum = texture {
   finish {
      reflection {
         rgb <0.5, 0.5, 0.5>
         metallic 1
      }
   }
   
   pigment {
      color rgb <0.905882, 0.905882, 0.905882>
   }
}

#declare Mirror = texture {
   finish {
      reflection {
         rgb <1, 1, 1>
      }
   }
   
   pigment {
      color rgb <0.905882, 0.905882, 0.905882>
   }
}

#declare Gold = texture {
   finish {
      reflection {
         rgb <0.5, 0.5, 0.5>
         metallic 1
      }
   }
   
   pigment {
      color rgb <1, 0.866667, 0>
   }
}

#declare GoldFoil = texture {
   Gold
   
   normal {
      wrinkles
      0.5
      turbulence <5, 5, 5>
      bump_size 1
   }
}

#declare Glass = material {
   texture {
      finish {
         phong 1
         conserve_energy
         
         reflection {
            rgb <0, 0, 0>
            fresnel
         }
      }
      
      pigment {
         color rgbf <1, 1, 1, 0.95>
      }
   }
   
   interior {
      ior 1.5
   }
}

#declare StarTracker = union {
   difference {
      cone {
         <0, 0.5, 0>, 0,
         <0, -0.5, 0>, 0.25
      }
      
      difference {
         cone {
            <0, 0.45, 0>, 0,
            <0, -0.55, 0>, 0.25
         }
         
         plane {
            <0, 1, 0>, -0.35
            inverse
         }
         
         pigment {
            RTGMetal
         }
      }
      
      texture {
         Aluminum
      }
   }
   
   intersection {
      sphere {
         <0, 0, 0>, 0.5
      }
      
      plane {
         <0, 1, 0>, -0.440397
         scale 1
         rotate <0, 0, 0>
         translate <0, 0, 0>
      }
      
      material {
         Glass
      }
   }
   scale 0.3
}

#declare LouverFin = box {
   <0.002, -0.001, -0.15>, <-0.002, -0.099, 0.15>
   rotate z*20
   
   texture {
      Aluminum
   }
}

#declare LouverFins3 = union {
   object {
      LouverFin
   }
   
   object {
      LouverFin
      translate x*0.1
   }
   
   object {
      LouverFin
      translate x*0.2
   }
}

#declare LouverFins7 = union {
   object {
      LouverFin
   }
   
   object {
      LouverFins3
      translate x*0.1
   }
   
   object {
      LouverFins3
      translate x*0.4
   }
}

#declare LouverFins10 = union {
   object {
      LouverFins3
   }
   
   object {
      LouverFins7
      translate x*0.3
   }
}

#declare Louver7 = union {
   object {
      LouverFins7
      scale 1
      rotate <0, 0, 0>
      translate <0, 0, 0>
   }
   
   difference {
      box {
         <-0.01, 0, -0.16>, <0.71, -0.02, 0.16>
      }
      
      box {
         <0, 0.001, -0.15>, <0.7, -0.021, 0.15>
      }
      
      texture {
         Aluminum
      }
   }
   
   box {
      <0, -0.001, -0.15>, <0.7, -0.001, 0.15>
      
      pigment {
         White
      }
   }
   scale 0.6
}

#declare Louver10 = union {
   object {
      LouverFins10
      scale 1
      rotate <0, 0, 0>
      translate <0, 0, 0>
   }
   
   difference {
      box {
         <-0.01, 0, -0.16>, <1.01, -0.02, 0.16>
      }
      
      box {
         <0, 0.001, -0.15>, <1, -0.021, 0.15>
      }
      
      texture {
         Aluminum
      }
   }
   
   box {
      <0, -0.001, -0.15>, <1, -0.001, 0.15>
      
      pigment {
         White
      }
   }
   scale 0.6
}

#declare RTGFin = box {
   <-0.002, -0.22, -0.005>, <0.002, 0.22, -0.095>
   scale 1
   rotate <0, 0, 0>
   translate <0, 0, 0>
}

#declare RTGFins = union {
   object {
      RTGFin
   }
   
   object {
      RTGFin
      translate z*(-0.1)
   }
   
   object {
      RTGFin
      translate z*(-0.2)
   }
   
   object {
      RTGFin
      translate z*(-0.3)
   }
   
   object {
      RTGFin
      translate z*(-0.4)
   }
   
   object {
      RTGFin
      translate z*(-0.5)
   }
   
   object {
      RTGFin
      translate z*(-0.6)
   }
}

#declare RTG = union {
   cylinder {
      <0, 0, -0.02>, <0, 0, -0.72>, 0.12
      scale 1
      rotate <0, 0, 0>
      translate <0, 0, 0>
   }
   
   object {
      RTGFins
   }
   
   object {
      RTGFins
      rotate z*45
   }
   
   object {
      RTGFins
      rotate z*90
   }
   
   object {
      RTGFins
      rotate z*135
   }
   
   pigment {
      RTGMetal
   }
   scale <1, 1, 0.8>
   translate <0, 0.25, -1.1>
}

global_settings {
   adc_bailout 0.00392157
   assumed_gamma 1.5
   noise_generator 2
}

#declare SDCDetector = union {
   box {
      //*PMName PVDF
      <0.22, 0, 0.47>, <-0.22, 0, -0.47>
      
      texture {
         Mirror
      }
   }
   
   difference {
      //*PMName Frame
      
      box {
         <0.24, 0.025, 0.49>, <-0.24, -0.025, -0.49>
      }
      
      box {
         <-0.22, -0.05, -0.47>, <0.22, 0.05, 0.47>
      }
      
      texture {
         Gold
      }
   }
}

#declare SDCRow = union {
   object {
      SDCDetector
      translate x*(-1.25)
   }
   
   object {
      SDCDetector
      translate x*(-0.75)
   }
   
   object {
      SDCDetector
      translate x*(-0.25)
   }
   
   object {
      SDCDetector
      translate x*0.25
   }
   
   object {
      SDCDetector
      translate x*0.75
   }
   
   object {
      SDCDetector
      translate x*1.25
   }
}

#declare SDCRows = union {
   object {
      SDCRow
      translate z*(-0.55)
   }
   
   object {
      SDCRow
      translate z*0.55
   }
}

#declare SDC = union {
   object {
      SDCRows
      scale 1
      rotate <0, 0, 0>
      translate y*(-0.025)
   }
   
   box {
      <-1.525, 0, -1.075>, <1.525, 0.1, 1.075>
      scale 1
      rotate <0, 0, 0>
      translate <0, 0, 0>
      
      texture {
         Aluminum
      }
   }
}

#declare InfiniteDish = quadric {
   <0.4, 0, 0.4>,
   <0, 0, 0>,
   <0, -1, 0>, 0
}

#declare Dish = object {
   InfiniteDish
   
   clipped_by {
      cylinder {
         <0, 0.4, 0>, <0, 0, 0>, 1
      }
   }
}

#declare LegHalf = cylinder {
   <-0.1732, 0.83, -0.1>, <0, 0.15697, -0.65404>, 0.01
   
   texture {
      GoldFoil
   }
   scale 1
   rotate <0, 0, 0>
   translate <0, 0, 0>
}

#declare Leg = union {
   object {
      LegHalf
      scale 1
      rotate <0, 0, 0>
      translate <0, 0, 0>
   }
   
   object {
      LegHalf
      scale <-1, 1, 1>
      rotate <0, 0, 0>
      translate <0, 0, 0>
   }
   
   cylinder {
      <-0.1732, 0.83, -0.1>, <0, 1, 0>, 0.01
      
      texture {
         GoldFoil
      }
      scale 1
      rotate <0, 0, 0>
      translate <0, 0, 0>
   }
}

#declare LorriMainBody = cylinder {
   <0.4, 0.3, 0.85>, <0.4, 0.3, 0.3>, 0.15
   scale 1
   rotate <0, 0, 0>
   translate <0, 0, 0>
}

#declare Lorri = union {
   union {
      //*PMName Door
      
      box {
         <0.49, 0.2, 0.85>, <0.55, 0.4, 0.86>
         scale 1
         rotate <0, 0, 0>
         translate <0, 0, 0>
      }
      
      cylinder {
         <0.4, 0.3, 0.85>, <0.4, 0.3, 0.86>, 0.15
      }
      translate <-0.56, -0.3, -0.855>
      rotate y*180
      translate <0.56, 0.3, 0.855>
      
      texture {
         GoldFoil
      }
   }
   
   union {
      //*PMName Hinge
      
      box {
         <0.55, 0.4, 0.855>, <0.57, 0.42, 0.8>
         scale 1
         rotate <0, 0, 0>
         translate <0, 0, 0>
      }
      
      cylinder {
         <0.56, 0.18, 0.855>, <0.56, 0.2, 0.855>, 0.015
      }
      
      box {
         <0.55, 0.18, 0.855>, <0.57, 0.2, 0.8>
         scale 1
         rotate <0, 0, 0>
         translate <0, 0, 0>
      }
      
      cylinder {
         <0.56, 0.42, 0.855>, <0.56, 0.4, 0.855>, 0.015
      }
      
      cylinder {
         <0.56, 0.4, 0.855>, <0.56, 0.2, 0.855>, 0.01
      }
      
      texture {
         GoldFoil
      }
   }
   
   difference {
      //*PMName Tube
      
      object {
         LorriMainBody
         
         texture {
            GoldFoil
         }
      }
      
      cylinder {
         <0.4, 0.3, 0.86>, <0.4, 0.3, 0.31>, 0.14
         scale 1
         rotate <0, 0, 0>
         translate <0, 0, 0>
      }
   }
   
   difference {
      cylinder {
         //*PMName Mirror
         <0.4, 0.3, 0.32>, <0.4, 0.3, 0.31>, 0.14
      }
      
      cylinder {
         //*PMName Mirror
         <0.4, 0.3, 0.33>, <0.4, 0.3, 0.3>, 0.03
      }
      
      texture {
         Mirror
      }
   }
   
   cylinder {
      <0.4, 0.3, 0.8>, <0.4, 0.3, 0.75>, 0.03
      scale 1
      rotate <0, 0, 0>
      translate <0, 0, 0>
   }
   
   box {
      //*PMName Spider 1
      <0.399, 0.32, 0.76>, <0.401, 0.45, 0.79>
   }
   
   box {
      //*PMName Spider 2
      <0.399, 0.32, 0.76>, <0.401, 0.45, 0.79>
      translate <-0.4, -0.3, 0>
      rotate z*120
      translate <0.4, 0.3, 0>
   }
   
   box {
      //*PMName Spider 3
      <0.399, 0.32, 0.76>, <0.401, 0.45, 0.79>
      translate <-0.4, -0.3, 0>
      rotate z*(-120)
      translate <0.4, 0.3, 0>
   }
   
   pigment {
      RTGMetal
   }
}

camera {
   perspective
   location <8.94879, 2.47472, 5.17192>
   sky <0, 1, 0>
   direction <0, 0, 1>
   right <1.3333, 0, 0>
   up <0, 1, 0>
   look_at <0.0420573, 0.540193, 0.0286306>
   angle 30
}

#declare Pepssi = union {
   difference {
      //*PMName Door 1
      
      cylinder {
         <1.24, 0.5, 0.7>, <1.21, 0.5, 0.7>, 0.045
         scale 1
         rotate <0, 0, 0>
         translate <0, 0, 0>
      }
      
      cylinder {
         <1.31, 0.5, 0.7>, <1.19, 0.5, 0.7>, 0.04
         scale 1
         rotate <0, 0, 0>
         translate <0, 0, 0>
      }
      
      plane {
         <0, 0, 1>, 0.69
         scale 1
         rotate <0, 0, 0>
         translate <0, 0, 0>
         inverse
      }
      
      pigment {
         RTGMetal
      }
      translate <0, -0.461, -0.69>
      rotate x*(-130)
      translate <0, 0.461, 0.69>
   }
   
   difference {
      //*PMName Door 2
      
      cylinder {
         <1.24, 0.5, 0.7>, <1.21, 0.5, 0.7>, 0.045
         scale 1
         rotate <0, 0, 0>
         translate <0, 0, 0>
      }
      
      cylinder {
         <1.31, 0.5, 0.7>, <1.19, 0.5, 0.7>, 0.04
         scale 1
         rotate <0, 0, 0>
         translate <0, 0, 0>
      }
      
      plane {
         <0, 0, 1>, 0.71
         scale 1
         rotate <0, 0, 0>
         translate <0, 0, 0>
      }
      
      pigment {
         RTGMetal
      }
      translate <0, -0.461, -0.71>
      rotate x*130
      translate <0, 0.461, 0.71>
   }
   
   cylinder {
      <1, 0.5, 0.7>, <1.2, 0.5, 0.7>, 0.05
      scale 1
      rotate <0, 0, 0>
      translate <0, 0, 0>
   }
   
   cylinder {
      <1.25, 0.5, 0.7>, <1.2, 0.5, 0.7>, 0.04
      scale 1
      rotate <0, 0, 0>
      translate <0, 0, 0>
   }
   
   texture {
      GoldFoil
   }
}

light_source {
   <4.07956, 3.5317, 0.74666>, rgb <1, 1, 1>
}

#declare LargeThr = difference {
   cylinder {
      <0, 0, 0>, <0, -0.5, 0>, 0.5
      
      texture {
         Aluminum
      }
   }
   
   cone {
      <0, -0.01, 0>, 0,
      <0, -0.51, 0>, 0.3
      
      pigment {
         RTGMetal
      }
   }
   scale 0.05
   translate z*(-0.025)
}

#declare NewHorizons = union {
   //*PMName New Horizons Spacecraft
   
   union {
      //*PMName Bus
      
      difference {
         prism {
            //*PMName Main Bus
            linear_spline
            linear_sweep
            0, 0.6,
            7,
            <1, 0.8>, <1, 0.1>, <0.4, -0.7>, <-0.4, -0.7>, <-1, 0.1>, <-1, 0.8>, <1, 0.8>
         }
         
         object {
            LorriMainBody
            scale 1
            rotate <0, 0, 0>
            translate <0, 0, 0>
         }
      }
      
      object {
         //*PMName Star Tracker 1
         StarTracker
         rotate <-90, -22.5, 0>
         translate <-0.56, 0.2, 0.77>
      }
      
      object {
         //*PMName Star Tracker 2
         StarTracker
         rotate <-90, 22.5, 0>
         translate <-0.24, 0.2, 0.77>
      }
      
      union {
         //*PMName Instruments
         
         object {
            //*PMName SDC
            SDC
            scale 0.15
            rotate <0, 0, 0>
            translate <-0.4, -0.015, 0.6>
         }
         
         union {
            //*PMName Ralph
            
            intersection {
               box {
                  <-1.2, 0.03, 0.54>, <-1.25, 0.37, 0.88>
                  
                  pigment {
                     White
                  }
               }
               
               cylinder {
                  <-1.5, 0.2, 0.71>, <-1, 0.2, 0.71>, 0.13
                  
                  texture {
                     GoldFoil
                  }
               }
            }
            
            intersection {
               box {
                  <-1.2, 0.03, 0.54>, <-1.15, 0.37, 0.88>
                  
                  pigment {
                     White
                  }
               }
               
               cylinder {
                  <-1.5, 0.2, 0.71>, <-1, 0.2, 0.71>, 0.17
                  
                  texture {
                     GoldFoil
                  }
               }
            }
            
            difference {
               //*PMName Ralph Box
               
               box {
                  <-1.15, 0.04, 0.5>, <-1, 0.36, 0.98>
                  
                  texture {
                     GoldFoil
                  }
               }
               
               cylinder {
                  <-1.07, 0.17, 0.6>, <-1.07, 0.17, 1>, 0.035573
                  
                  pigment {
                     RTGMetal
                  }
               }
            }
            translate z*(-0.2)
         }
         
         difference {
            //*PMName Alice
            
            box {
               <-1.08, 0.38, 0.5>, <-1, 0.58, 0.98>
               
               texture {
                  GoldFoil
               }
            }
            
            box {
               <-1.07, 0.54, 0.6>, <-1.01, 0.57, 1>
               
               pigment {
                  RTGMetal
               }
            }
            translate z*(-0.2)
         }
         
         object {
            //*PMName Lorri
            Lorri
         }
         
         object {
            Pepssi
         }
      }
      
      prism {
         //*PMName Star Tracker Box
         linear_spline
         linear_sweep
         0, 0.3,
         5,
         <-0.3, 0.9>, <-0.1, 0.8>, <-0.7, 0.8>, <-0.5, 0.9>, <-0.3, 0.9>
      }
      
      prism {
         //*PMName RTGShield
         linear_spline
         linear_sweep
         0, 0.01,
         9,
         <0, 1>, <0.707, 0.707>, <1, 0>, <0.707, -0.707>, <0, -1>, <-0.707, -0.707>, <-1, 0>, <-0.707, 0.707>, <0, 1>
         scale 0.38
         rotate y*22.5
         rotate x*90
         translate <0, 0.25, -1.125>
         
         texture {
            GoldFoil
         }
      }
      
      object {
         //*PMName Louver 1
         Louver7
         translate x*0.5
         rotate y*(-25)
         translate z*(-0.2)
      }
      
      object {
         //*PMName Louver 2
         Louver10
         rotate y*90
         translate <-0.769752, 0, 0.629797>
      }
      
      object {
         //*PMName Louver 3
         Louver10
         rotate <0, 0, 0>
         translate <0.365438, 0, 0.42764>
      }
      
      object {
         //*PMName Louver 4
         Louver7
         translate x*0.5
         rotate y*(-90)
         translate z*(-0.2)
      }
      
      object {
         //*PMName RTG Inboard
         RTG
         translate z*(-0.05)
      }
      
      object {
         //*PMName RTG Outboard
         RTG
         translate z*(-0.65)
      }
      
      box {
         //*PMName RTGSupport
         <-0.08, 0.17, -2.2>, <0.08, 0.33, -1>
         
         texture {
            Aluminum
         }
      }
      
      difference {
         //*PMName RTG Box
         
         prism {
            linear_spline
            linear_sweep
            0, 0.96667,
            5,
            <0.4, -0.7>, <0.25, -1.1>, <-0.25, -1.1>, <-0.4, -0.7>, <0.4, -0.7>
         }
         
         plane {
            <0, 0.92818, -0.37214>, 0.82039
            inverse
         }
      }
      
      texture {
         GoldFoil
      }
      translate z*0.2
   }
   
   union {
      //*PMName Antenna
      
      cylinder {
         //*PMName Support
         <0, -0.05, 0>, <0, 0.2, 0>, 0.6
         open
         
         clipped_by {
            object {
               //*PMName Backreflector
               InfiniteDish
               scale <1.05, 1, 1.05>
               translate y*(-0.001)
               inverse
            }
         }
         
         texture {
            GoldFoil
         }
      }
      
      object {
         //*PMName Backreflector
         Dish
         
         texture {
            GoldFoil
         }
         scale <1.05, 1, 1.05>
         translate y*(-0.001)
      }
      
      object {
         Leg
         rotate <0, 0, 0>
      }
      
      object {
         Leg
         rotate y*120
      }
      
      object {
         Leg
         rotate y*240
      }
      
      object {
         //*PMName Subreflector
         Dish
         scale 0.2
         translate y*0.75
         
         pigment {
            White
         }
      }
      
      object {
         //*PMName Mainreflector
         Dish
         scale <1.05, 1, 1.05>
         
         pigment {
            White
         }
      }
      translate y*0.65
      rotate y*180
   }
   
   union {
      //*PMName LVA
      
      cylinder {
         <0, 0, 0>, <0, -0.2, 0>, 0.02
      }
      
      cylinder {
         <0, -0.2, 0>, <0, -0.22, 0>, 0.04
         
         texture {
            Aluminum
         }
      }
      
      object {
         LargeThr
         translate <0, -0.1, 0.44>
         rotate y*225
      }
      
      object {
         LargeThr
         translate <0, -0.1, 0.44>
         rotate y*315
      }
      
      object {
         LargeThr
         translate <0, -0.1, 0.44>
         rotate y*45
      }
      
      object {
         LargeThr
         translate <0, -0.1, 0.44>
         rotate y*135
      }
      
      difference {
         cylinder {
            //*PMName LVA
            <0, -0.1, 0>, <0, -0.12, 0>, 0.45
         }
         
         cylinder {
            //*PMName LVA
            <0, 0.01, 0>, <0, -0.121, 0>, 0.44
         }
         
         texture {
            Aluminum
         }
      }
      
      cylinder {
         <0, 0, 0>, <0, -0.1, 0>, 0.45
         scale 1
         rotate <0, 0, 0>
         translate <0, 0, 0>
      }
      
      texture {
         GoldFoil
      }
   }
}

object {
   NewHorizons
   scale 1
   rotate <0, 0, 0>
   translate <0, 0, 0>
}