union {
   union {
      union {
         //*PMName Backshell
         
         cone {
            //*PMName Wraparound Antenna
            <0, 0, 2.875>, 0.3655,
            <0, 0, 2.356>, 0.6535
         }
         
         cone {
            //*PMName Cruise Stage Interface
            <0, 0, 2.356>, 0.6535,
            <0, 0, 2.296>, 0.7645
            
            material {
               //*PMName Gold Anodized Alumninum
               
               texture {
                  finish {
                     phong 1
                     metallic 1
                  }
                  
                  pigment {
                     color rgb <1, 0.992157, 0.411765>
                  }
               }
            }
         }
         
         cone {
            //*PMName Backshell 1
            <0, 0, 2.296>, 0.7645,
            <0, 0, 1.878>, 1.5005
         }
         
         cone {
            //*PMName Backshell 2
            <0, 0, 1.878>, 1.5005,
            <0, 0, 0.91061>, 2.22476
         }
         
         material {
            //*PMName Composite
            
            texture {
               pigment {
                  color rgb <1, 1, 1>
               }
               
               finish {
                  phong 1
                  phong_size 60
               }
            }
         }
      }
      
      union {
         //*PMName Heatshield
         
         difference {
            //*PMName Heatshield Shoulder
            
            torus {
               2.124, 0.126
               rotate x*90
               translate z*0.83496
            }
            
            cylinder {
               <0, 0, 0.91061>, <0, 0, 1>, 2.25
            }
         }
         
         cone {
            //*PMName Heatshield Cone
            <0, 0, 0.71656>, 2.1671,
            <0, 0, 0.06785>, 0.38477
         }
         
         intersection {
            cylinder {
               <0, 0, 0>, <0, 0, 0.07>, 0.38477
               scale 1
               rotate <0, 0, 0>
               translate <0, 0, 0>
            }
            
            sphere {
               <0, 0, 1.125>, 1.125
            }
         }
         
         material {
            texture {
               pigment {
                  color rgb <0.752941, 0.345098, 0>
               }
               
               finish {
                  ambient rgb <0.3, 0.25, 0.2>
               }
            }
         }
      }
      translate z*(-1)
   }
}