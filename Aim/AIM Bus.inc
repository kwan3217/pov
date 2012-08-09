//*PMRawBegin
#ifndef(CipsDeploy)  #declare CipsDeploy=1;  #end
#ifndef(SofieDeploy) #declare SofieDeploy=1; #end
//*PMRawEnd

#declare BlackPaint = texture {
   pigment {
      color rgb <0.05, 0.05, 0.05>
   }
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

#declare WhitePlastic = texture {
   pigment {
      color rgb <1.2, 1.2, 1.2>
   }
   
   finish {
      phong 0.5
   }
}

#declare Glass = material {
   texture {
      pigment {
         color rgbf <0.9, 0.9, 1, 1>
      }
      
      finish {
         phong 0
         specular 0.5
      }
   }
   
   interior {
      ior 1.5
   }
}

#declare GoldishAluminum = texture {
   finish {
      phong 0
      phong_size 10
   }
   
   pigment {
      color rgb <0.6, 0.6, 0.5>
   }
}

#declare DullAluminum = texture {
   finish {
      phong 0
      phong_size 10
   }
   
   pigment {
      color rgb <0.6, 0.6, 0.6>
   }
}

#declare ShinyAluminum = texture {
   finish {
      phong 0
      phong_size 10
      specular 0.5
   }
   
   pigment {
      color rgb <0.8, 0.8, 0.8>
   }
}

#declare Mirror = texture {
   finish {
      phong 0
      phong_size 10
      specular 1
   }
   
   pigment {
      color rgb <1, 1, 1>
   }
}

#declare Gold = texture {
   pigment {
      color rgb <1, 1, 0.2>
   }
   
   finish {
      phong 0
      
      reflection {
         rgb <0.3, 0.3, 0.3>
      }
   }
}

#declare Honeycomb = texture {
   Gold
   
   normal {
      crackle
      3
      scale <0.03, 1000, 0.03>
      bump_size 1
   }
}

#declare Bolt = cylinder {
   <0, 0.01, 0>, <0, -0.06, 0>, 0.005
   
   texture {
      GoldishAluminum
   }
}

#declare Bolts1 = union {
   object {
      Bolt
      translate x*(-0.0314)
   }
   
   object {
      Bolt
      translate x*(-0.094)
   }
   
   object {
      Bolt
      translate x*(-0.157)
   }
   
   object {
      Bolt
      translate x*(-0.22)
   }
   
   object {
      Bolt
      translate x*(-0.188)
   }
}

#declare Bolts2 = union {
   object {
      Bolts1
   }
   
   object {
      Bolts1
      scale <-1, 1, 1>
   }
   
   texture {
      GoldishAluminum
   }
}

#declare FlangeFlat = union {
   box {
      <-0.22, 0, 0>, <0.22, 0.025, 0.003>
   }
   
   box {
      <-0.245, 0, 0>, <0.245, -0.025, 0.003>
   }
   
   cylinder {
      <-0.22, 0, 0>, <-0.22, 0, 0.003>, 0.025
   }
   
   cylinder {
      <0.22, 0, 0>, <0.22, 0, 0.003>, 0.025
   }
}

#declare FlangeCurve = intersection {
   cylinder {
      <0.245, 0, 0.01>, <-0.245, 0, 0.01>, 0.01
   }
   
   cylinder {
      <-0.25, 0, 0.01>, <0.25, 0, 0.01>, 0.007
      inverse
   }
   
   plane {
      <0, 1, 0>, 0
      inverse
   }
   
   plane {
      <0, 1, 0>, 0
      rotate x*90
      translate z*0.01
   }
}

#declare Flange = union {
   object {
      Bolts2
      rotate x*(-90)
      translate y*(-0.04)
   }
   
   object {
      Bolts2
      rotate x*180
      translate <0, 0.01, 0.05>
   }
   
   object {
      FlangeFlat
      rotate z*180
      translate y*(-0.025)
   }
   
   object {
      FlangeCurve
      scale 1
      rotate <0, 0, 0>
      translate <0, 0, 0>
   }
   
   object {
      FlangeFlat
      rotate z*180
      translate y*(-0.025)
      rotate x*(-90)
      translate <0, 0.007, 0.01>
   }
   
   texture {
      GoldishAluminum
   }
   translate z*(-0.003)
}

#declare Hexagon = prism {
   linear_spline
   linear_sweep
   0, 1,
   7,
   <0.5, 0.86603>, <1, 0>, <0.5, -0.866025>, <-0.5, -0.866025>, <-1, 0>, <-0.5, 0.86603>, <0.5, 0.86603>
}

#declare CIPSLens = union {
   box {
      <0.025, 0.095, 0.055>, <0.045, 0.105, 0.045>
      
      texture {
         Gold
      }
   }
   
   cylinder {
      <-0.025, 0.105, 0.05>, <-0.045, 0.105, 0.05>, 0.0045
   }
   
   cylinder {
      <0.055, 0.11, -0.032>, <0.045, 0.11, -0.032>, 0.0045
      
      texture {
         BlackPaint
      }
   }
   
   box {
      <-0.04, 0.105, 0.045>, <-0.045, 0.1, 0.05>
   }
   
   box {
      <0.050955, 0.11, -0.036513>, <0.045, 0.1, -0.027841>
   }
   
   box {
      <-0.03, 0.105, 0.045>, <-0.025, 0.1, 0.05>
   }
   
   union {
      //*PMName Cover
      
      cylinder {
         <-0.03, 0.105, 0.05>, <-0.04, 0.105, 0.05>, 0.005
      }
      
      cylinder {
         <0, 0.11, 0>, <0, 0.105, 0>, 0.043
      }
      
      box {
         <-0.04, 0.105, 0.008>, <-0.03, 0.11, 0.05>
      }
      
      box {
         <0.04, 0.105, -0.008>, <0.03, 0.11, -0.036>
      }
      translate <0, -0.105, -0.05>
      rotate x*200
      //*PMRawBegin
      *CipsDeploy
      //*PMRawEnd
      translate <0, 0.105, 0.05>
      
      texture {
         BlackPaint
      }
   }
   
   union {
      intersection {
         prism {
            linear_spline
            conic_sweep
            0.1, 0.15,
            10,
            <-0.45, 0.45>, <0.45, 0.45>, <0.45, -0.45>, <-0.45, -0.45>, <-0.45, 0.45>,
            <-0.44, 0.44>, <0.44, 0.44>, <0.44, -0.44>, <-0.44, -0.44>, <-0.44, 0.44>
            scale 1
            rotate <0, 0, 0>
            translate y*0.005
         }
         
         plane {
            <0, 0.95325, 0.30218>, 0.113716
         }
      }
      
      difference {
         box {
            <-0.045, 0.1, -0.045>, <0.045, 0.105, 0.045>
         }
         
         box {
            <-0.03, 0.099, -0.03>, <0.03, 0.106, 0.03>
         }
      }
   }
   
   cylinder {
      <0, 0, 0>, <0, -0.02, 0>, 0.035
      scale 1
      rotate <0, 0, 0>
      translate <0, 0, 0>
   }
   
   box {
      <0, 0, -0.035>, <0.04, -0.02, 0.035>
      scale 1
      rotate <0, 0, 0>
      translate <0, 0, 0>
   }
   
   cylinder {
      <0, 0, 0>, <0, 0.03, 0>, 0.02
      open
      scale 1
      rotate <0, 0, 0>
      translate <0, 0, 0>
   }
   
   cone {
      <0, 0.03, 0>, 0.02,
      <0, 0.07, 0>, 0.035
      scale 1
      rotate <0, 0, 0>
      translate <0, 0, 0>
   }
   
   difference {
      union {
         cylinder {
            <0, 0.07, 0>, <0, 0.1, 0>, 0.035
         }
         
         cylinder {
            <0, 0.095, 0>, <0, 0.1, 0>, 0.045
         }
      }
      
      cylinder {
         <0, 0.06, 0>, <0, 0.11, 0>, 0.033
      }
   }
   
   intersection {
      sphere {
         <0, 0.035, 0>, 0.07
         scale 1
         rotate <0, 0, 0>
         translate <0, 0, 0>
      }
      
      plane {
         <0, 1, 0>, 0.0960525
         scale 1
         rotate <0, 0, 0>
         translate <0, 0, 0>
         inverse
      }
      
      material {
         Glass
      }
   }
   
   texture {
      ShinyAluminum
   }
}

#declare SolarPanelBracket = intersection {
   //*PMName Solar Panel Bracket
   
   box {
      <-0.045, 0.0068034, 0.0062827>, <-0.02, 0.11166, 0.07708>
      inverse
   }
   
   box {
      <0.045, 0.0068034, 0.0062827>, <0.02, 0.11166, 0.07708>
      inverse
   }
   
   box {
      <-0.015, 0.0068034, 0.0062827>, <0.015, 0.11166, 0.07708>
      inverse
   }
   
   union {
      box {
         <-0.05, 0, 0>, <0.05, 0.1, 0.071639>
      }
      
      cylinder {
         <0, 0.06, -0.01>, <0, 0.06, 0>, 0.015
         
         texture {
            ShinyAluminum
         }
      }
   }
   
   plane {
      <0, 1, 0>, 0
      rotate x*55.2
      translate <0, 0.064146, 0.0311011>
   }
   translate <0, 0.628, -0.45>
   
   texture {
      GoldishAluminum
   }
}

#declare CDEDetector = union {
   box {
      //*PMName PVDF
      <0.22, 0, 0.47>, <-0.22, 0.001, -0.47>
      
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

#declare CDERow = union {
   object {
      CDEDetector
      translate x*(-1.25)
   }
   
   object {
      CDEDetector
      translate x*(-0.75)
   }
   
   object {
      CDEDetector
      translate x*(-0.25)
   }
   
   object {
      CDEDetector
      translate x*0.25
   }
   
   object {
      CDEDetector
      translate x*0.75
   }
   
   object {
      CDEDetector
      translate x*1.25
   }
}

#declare CDERows = union {
   object {
      CDERow
      translate z*(-0.55)
   }
   
   object {
      CDERow
      translate z*0.55
   }
}

#declare CDE = union {
   object {
      CDERows
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

#declare AIMBusPlusInstruments = union {
   //*PMName AIMBusPlusInstruments
   
   cylinder {
      //*PMName LaunchVehicleAdapter
      <0, 0, 0>, <0, 0.05, 0>, 0.485
      open
      
      texture {
         ShinyAluminum
      }
      hollow false
   }
   
   intersection {
      //*PMName Base plate
      
      object {
         Hexagon
      }
      
      object {
         Hexagon
         translate y*(-0.25)
         scale <1.1, 2, 1.1>
         rotate y*30
      }
      
      texture {
         GoldishAluminum
      }
      scale <0.56, 0.005, 0.56>
      translate y*0.05
   }
   
   intersection {
      //*PMName Bus Walls
      
      plane {
         <0, -1, 0>, 0
         
         texture {
            Honeycomb
            rotate z*90
         }
      }
      
      plane {
         <0, -1, 0>, -1
         
         texture {
            Honeycomb
            rotate z*90
         }
         inverse
      }
      
      object {
         Hexagon
         scale <1, 2, 1>
         translate y*(-0.5)
         
         texture {
            DullAluminum
         }
      }
      
      object {
         Hexagon
         scale <0.92, 2, 0.92>
         translate y*(-0.5)
         
         texture {
            BlackPaint
         }
         inverse
      }
      scale <0.53, 0.499, 0.53>
      translate y*0.058
   }
   
   intersection {
      //*PMName Nadir Deck
      
      plane {
         <0, -1, 0>, 0
         
         texture {
            GoldishAluminum
         }
      }
      
      plane {
         <0, 1, 0>, 1
         
         texture {
            GoldishAluminum
         }
      }
      
      object {
         Hexagon
         
         texture {
            Honeycomb
         }
         translate y*(-0.25)
         scale <1, 2, 1>
      }
      scale <0.53, 0.05, 0.53>
      translate y*0.578
   }
   
   union {
      //*PMName Flanges
      
      object {
         Flange
         translate <0, 0.56, -0.46>
         rotate y*120
      }
      
      object {
         Flange
         translate <0, 0.56, -0.46>
         rotate y*60
      }
      
      object {
         Flange
         translate <0, 0.56, -0.46>
         rotate y*300
      }
      
      object {
         Flange
         translate <0, 0.56, -0.46>
         rotate y*240
      }
      
      object {
         Flange
         translate <0, 0.56, -0.46>
         rotate y*180
      }
      
      object {
         Flange
         translate <0, 0.56, -0.46>
         rotate <0, 0, 0>
      }
   }
   
   union {
      //*PMName CIPS Instrument
      
      union {
         //*PMName PX Camera
         
         union {
            union {
               box {
                  <-0.06, 0, -0.01>, <0.06, 0.4, 0>
                  
                  texture {
                     ShinyAluminum
                  }
               }
               
               box {
                  <-0.06, 0, 0>, <0.06, 0.4, 0.01>
                  
                  texture {
                     BlackPaint
                  }
               }
               rotate x*(-22)
               translate <0, 0.0964858, -0.0443453>
            }
            
            object {
               CIPSLens
            }
            rotate y*(-180)
            rotate x*39
            translate y*0.095
         }
         
         intersection {
            box {
               <-0.05, 0.18, -0.05>, <0.05, 0, 0.05>
            }
            
            plane {
               <0, 1, 0>, 0
               rotate x*39
               translate y*0.075
            }
            
            texture {
               ShinyAluminum
            }
         }
         rotate y*180
         translate <-0.25, 1.06, 0.026>
      }
      
      union {
         //*PMName MX Camera
         
         object {
            CIPSLens
            rotate <0, 0, 0>
            rotate x*39
            translate y*0.095
         }
         
         intersection {
            box {
               <-0.05, 0.18, -0.05>, <0.05, 0, 0.05>
            }
            
            plane {
               <0, 1, 0>, 0
               rotate x*39
               translate y*0.075
            }
            
            texture {
               ShinyAluminum
            }
         }
         rotate <0, 0, 0>
         translate <-0.13, 1.06, 0.151333>
      }
      
      union {
         //*PMName MY Camera
         
         object {
            CIPSLens
            rotate y*(-90)
            rotate x*19
            translate y*0.095
         }
         
         intersection {
            box {
               <-0.05, 0.18, -0.05>, <0.05, 0, 0.05>
            }
            
            plane {
               <0, 1, 0>, 0
               rotate x*19
               translate y*0.075
            }
            
            texture {
               ShinyAluminum
            }
         }
         rotate y*90
         translate <-0.13, 1.06, 0.043>
      }
      
      union {
         //*PMName PY Camera
         
         object {
            CIPSLens
            rotate y*90
            rotate x*19
            translate y*0.095
         }
         
         intersection {
            box {
               <-0.05, 0.18, -0.05>, <0.05, 0, 0.05>
            }
            
            plane {
               <0, 1, 0>, 0
               rotate x*19
               translate y*0.075
            }
            
            texture {
               ShinyAluminum
            }
         }
         rotate y*(-90)
         translate <-0.25, 1.06, 0.16>
      }
      
      union {
         //*PMName CIPS Platform
         
         box {
            //*PMName Platform Center
            <-0.195, 0.65, -0.08>, <-0.185, 1.05, 0.28>
         }
         
         cylinder {
            <-0.18, 0.628, 0.1>, <-0.2, 0.628, 0.1>, 0.04
         }
         
         cylinder {
            <-0.1, 0.628, -0.095>, <-0.1, 0.628, -0.075>, 0.04
         }
         
         cylinder {
            <-0.28, 0.628, -0.095>, <-0.28, 0.628, -0.075>, 0.04
         }
         
         box {
            //*PMName HVPS1
            <-0.195, 1, -0.026>, <-0.295, 1.05, 0.2>
         }
         
         cylinder {
            <-0.1, 0.628, 0.275>, <-0.1, 0.628, 0.295>, 0.04
         }
         
         cylinder {
            <-0.28, 0.628, 0.275>, <-0.28, 0.628, 0.295>, 0.04
         }
         
         box {
            //*PMName HVPS2
            <-0.185, 1, -0.026>, <-0.085, 1.05, 0.2>
         }
         
         box {
            //*PMName Platform Top
            <-0.07, 1.05, -0.09>, <-0.31, 1.06, 0.29>
         }
         
         box {
            //*PMName CPA
            <-0.195, 0.68, 0.02>, <-0.285, 0.98, 0.25>
         }
         
         box {
            //*PMName CPA Cover
            <-0.285, 0.68, 0.02>, <-0.295, 0.98, 0.25>
            
            texture {
               Mirror
            }
         }
         
         box {
            //*PMName CIPS Radiator
            <-0.31, 0.921149, -0.0804788>, <-0.311, 1.19659, 0.28126>
            
            texture {
               Mirror
            }
         }
         
         prism {
            //*PMName Platform Front
            linear_spline
            linear_sweep
            0, 0.01,
            5,
            <-0.07, 0.4>, <-0.05, 0>, <-0.33, 0>, <-0.31, 0.4>, <-0.07, 0.4>
            rotate x*(-90)
            translate <0, 0.65, -0.08>
         }
         
         prism {
            //*PMName Platform Back
            linear_spline
            linear_sweep
            0, 0.01,
            5,
            <-0.07, 0.4>, <-0.05, 0>, <-0.33, 0>, <-0.31, 0.4>, <-0.07, 0.4>
            rotate x*(-90)
            translate <0, 0.65, 0.29>
            
            texture {
               Mirror
            }
         }
         
         texture {
            ShinyAluminum
         }
      }
   }
   
   union {
      //*PMName Solar Panel Brackets
      
      object {
         SolarPanelBracket
         rotate <0, 0, 0>
      }
      
      object {
         SolarPanelBracket
         rotate y*60
      }
      
      object {
         SolarPanelBracket
         rotate y*120
      }
      
      object {
         SolarPanelBracket
         rotate y*180
      }
      
      object {
         SolarPanelBracket
         rotate y*240
      }
      
      object {
         SolarPanelBracket
         rotate y*300
      }
   }
   
   union {
      //*PMName SOFIE
      
      prism {
         //*PMName Wedge
         linear_spline
         linear_sweep
         0, 0.15,
         4,
         <0.11, -0.09>, <-0.11, -0.09>, <0, 0.13>, <0.11, -0.09>
      }
      
      union {
         //*PMName SOFIE Instrument
         
         prism {
            //*PMName SOFIE Radiator Silver
            linear_spline
            linear_sweep
            -0.17, -0.165,
            8,
            <0.39617, 0.047707>, <0.50292, -0.14414>, <-0.01569, -0.15437>, <0.0038267, -0.069433>, <-0.031155, 0.011986>, <-0.069207, 0.024163>, <-0.029533, 0.16637>, <0.39617, 0.047707>
            rotate z*90
            
            texture {
               Mirror
            }
         }
         
         prism {
            //*PMName SOFIE Radiator
            linear_spline
            linear_sweep
            -0.165, -0.16,
            8,
            <0.39617, 0.047707>, <0.50292, -0.14414>, <-0.01569, -0.15437>, <0.0038267, -0.069433>, <-0.031155, 0.011986>, <-0.069207, 0.024163>, <-0.029533, 0.16637>, <0.39617, 0.047707>
            rotate z*90
         }
         
         cylinder {
            //*PMName SOFIE Steering Mirror
            <0, 0, 0.01>, <0, 0, 0>, 0.04
            scale <1, 1.414, 1>
            rotate x*(-45)
            translate <0.00274897, 0.425148, -0.0379045>
            
            texture {
               Mirror
            }
         }
         
         difference {
            //*PMName SOFIE Steering Mirror Housing
            
            prism {
               linear_spline
               linear_sweep
               0.06, -0.06,
               6,
               <0.48, -0.06>, <0.48, -0.137>, <0.3, -0.137>, <0.3, 0.053>, <0.366667, 0.053>, <0.48, -0.06>
               rotate z*90
            }
            
            prism {
               linear_spline
               linear_sweep
               0.05, -0.05,
               6,
               <0.472066, -0.0621075>, <0.472066, -0.129412>, <0.29263, -0.12962>, <0.29263, 0.044078>, <0.366897, 0.043708>, <0.472066, -0.0621075>
               
               texture {
                  BlackPaint
               }
               rotate z*90
            }
            
            cylinder {
               <0, 0.425, -0.12>, <0, 0.425, -0.15>, 0.04
            }
         }
         
         cylinder {
            //*PMName SOFIE Body
            <0, 0.3, 0>, <0, 0, 0>, 0.15
         }
         
         union {
            //*PMName SOFIE Dust Cover
            
            cylinder {
               <0, 0.425, -0.137>, <0, 0.425, -0.14>, 0.042
            }
            
            cylinder {
               <-0.02, 0.35, -0.14>, <0.02, 0.35, -0.14>, 0.003
            }
            
            box {
               <-0.01, 0.425, -0.14>, <0.01, 0.35, -0.137>
            }
            translate <0, -0.35, 0.14>
            rotate x*(-150)
            //*PMRawBegin
            *SofieDeploy
            //*PMRawEnd
            translate <0, 0.35, -0.14>
         }
         
         cylinder {
            //*PMName SOFIE Top Rib
            <0, 0.3, 0>, <0, 0.29, 0>, 0.155
         }
         
         cylinder {
            //*PMName SOFIE Bottom Rib
            <0, 0, 0>, <0, 0.01, 0>, 0.155
         }
         
         cylinder {
            //*PMName SOFIE Middle Rib
            <0, 0.145, 0>, <0, 0.155, 0>, 0.155
         }
         rotate x*14
         translate y*0.1
      }
      translate <0.17345, 0.623, -0.17029>
      
      texture {
         ShinyAluminum
      }
   }
   
   union {
      //*PMName Star Tracker
      
      intersection {
         box {
            <-0.08, 0.3, -0.08>, <0.08, 0, 0.07>
         }
         
         plane {
            <0, 1, 0>, 0
            rotate x*17
            translate <0, 0.15, 0.03>
            hollow false
         }
      }
      
      union {
         //*PMName Star Tracker Housing
         
         prism {
            quadratic_spline
            linear_sweep
            0.14, 0,
            8,
            <0.0534, -0.0337>, <-0.0534, -0.0337>, <-0.0732, 0>, <-0.0232, 0.1>, <0.0232, 0.1>, <0.0732, 0>, <0.0534, -0.0337>, <-0.0534, -0.0337>
         }
         
         difference {
            cone {
               <0, 0.07, 0.1>, 0,
               <0, 0.07, -0.2>, 0.1
               
               texture {
                  Gold
               }
            }
            
            cone {
               <0, 0.07, 0.1>, 0,
               <0, 0.07, -0.2>, 0.1
               
               texture {
                  BlackPaint
               }
               translate z*(-0.05)
            }
         }
         rotate y*180
         rotate x*17
         translate <0, 0.15, 0.03>
      }
      translate <0.154453, 0.623, 0.139237>
      
      texture {
         ShinyAluminum
      }
   }
   
   union {
      //*PMName Antenna Mast
      
      cylinder {
         <0, 0, 0>, <0, 0.6, 0>, 0.0125
      }
      
      cylinder {
         <0, 0.62, 0>, <0, 0.6, 0>, 0.02
         
         texture {
            WhitePlastic
         }
      }
      
      cylinder {
         <0, 0.7, 0>, <0, 0.62, 0>, 0.01
         
         texture {
            WhitePlastic
         }
      }
      
      cylinder {
         <0, 0.375, 0>, <0, 0.325, 0>, 0.015
         scale 1
         rotate <0, 0, 0>
         translate <0, 0, 0>
      }
      translate <0.48, 0.623, 0>
      
      texture {
         ShinyAluminum
      }
   }
   
   object {
      //*PMName CDE
      CDE
      scale 0.15
      translate <0, 0, 0>
   }
   
   intersection {
      //*PMName Base plate
      
      object {
         Hexagon
      }
      
      object {
         Hexagon
         translate y*(-0.25)
         scale <1.05, 2, 1.05>
         rotate y*30
      }
      
      texture {
         Mirror
      }
      scale <0.5, 0.005, 0.5>
      translate y*0.04
   }
}
