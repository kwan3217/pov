#include "frustum.inc"

#declare Plastic = finish {
   phong 0.2
}

#declare Bellows = union { 
   #local R1=0.15;
   #local R2=0.02;
   #local H=0.2;
   #local R3=0;
   #local HP=0;   
   solveFrust(R1,R2,H,R3,HP)     
   #debug concat("R3: ",str(R3,0,6),"\n")
   #debug concat("HP: ",str(HP,0,6),"\n")
   difference {
     union {
   cone {
      <0, -R1, 0>, 0.3,
      <0, -R3, 0>, 0.3+HP
   } 
   cone {
      <0, R1, 0>, 0.3,
      <0, R3, 0>, 0.3+HP
   } 
   #declare SeamR=0.001;
   #declare Seam=union {
     cylinder {
       <0,R1,0>,<0.3,R1,0>,SeamR
     }  
     sphere {
       <0.3,R1,0>,SeamR
     }
     cylinder {
       <0.3,R1,0>,<0.3+HP,R3,0>,SeamR
     }
     torus {
       R2,SeamR
       rotate x*90
       translate x*(0.3+H-R2)
     }
     cylinder {
       <0.3,-R1,0>,<0.3+HP,-R3,0>,SeamR
     }
     sphere {
       <0.3,-R1,0>,SeamR
     }
     cylinder {
       <0,-R1,0>,<0.3,-R1,0>,SeamR
     }  
   }     
   object {Seam}
   object {Seam rotate y*180}
   torus {
     0.3+H-R2,R2
   }        
   }
      cylinder {-y,y,0.02}
      cylinder {-y*(R1-0.1),y*(R1-0.01),0.2}
   }
   
}

#declare HammerHalf = union {
   object {Bellows}
   object {Bellows
      translate y*0.3
   }
   
   object {Bellows
      translate y*(-0.3)
   }
   
   texture {
      pigment {   
        cylindrical 
        color_map {
         [1-(H+0.3) color rgb <1,0.2,0.2>]
         [1-(HP+0.3) color rgb <1,0,0>]
        }
      }
      finish {
         Plastic
      }
   }
   translate y*0.45
   scale <1, 0.6, 1>
}

light_source {
   <0, 5, 3>, rgb 1.0
   area_light x*2 z*2 40 40 circular adaptive 2 jitter orient
}
#local r=0.1;
#local l=2;
#local R=H+0.3;
union {
   //*PMName Hammer
   
   union {
      //*PMName Handle
      
      cylinder {
         <0, 0.15, 0>, <0, -0.15, 0>, 0.3
      }
      
      cylinder {
         <0, 0, 0>, <l, 0, 0>, r
      }
      sphere {
        <l,0,0>,r
      }
      texture {
         pigment {
            color rgb <1, 1, 0>
         }
         
         finish {
            Plastic
         }
      }     
  
      texture {
        pigment {
        // texture pigment {} attribute
        // create a texture that lays an image's colors onto a surface
        // image maps into X-Y plane from <0,0,0> to <1,1,0>
         image_map {
           png "Kodocha.png" // the file to read (iff/tga/gif/png/jpeg/tiff/sys)
           map_type 2        // 0=planar, 1=spherical, 2=cylindrical, 5=torus
           interpolate 2     // 0=none, 1=linear, 2=bilinear, 4=normalized distance
           once           // for no repetitive tiling
         }            
         scale 0.75       
         rotate y*180
         rotate -z*90 
         rotate x*5
         translate x*0.375
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
   rotate x*90   
   #local Theta1=asin(R/sqrt(r*r+l*l));
   #local Theta2=atan(r/l);
   #local Theta=Theta1-Theta2;
   rotate -z*degrees(Theta)  
   translate y*(0.3+H)           
}

camera {
   perspective
   location <5, 9, 5>
   sky <0, 1, 0>
   direction <0, 0, 1>
   right x*image_width/image_height
   up y
   look_at <0.75, 0.35, 0>
   angle 25
}                    

#local S="????????"
      
plane {
  y,0
  pigment {color rgb 1.5}
} 
   
   // Persistence of Vision Ray Tracer Scene Description File
// File: ?.pov
// Vers: 3.6
// Desc: Radiosity Scene Template
// Date: mm/dd/yy
// Auth: ?
//

#version 3.6;

#declare Radiosity=on;

global_settings {
  assumed_gamma 1.0
  //max_trace_level 25
  #if (Radiosity)
    radiosity {
      pretrace_start 0.08           // start pretrace at this size
      pretrace_end   0.04           // end pretrace at this size
      count 35                      // higher -> higher quality (1..1600) [35]
      nearest_count 5               // higher -> higher quality (1..10) [5]
      error_bound 1.8               // higher -> smoother, less accurate [1.8]
      recursion_limit 3             // how much interreflections are calculated (1..5+) [3]
      low_error_factor .5           // reduce error_bound during last pretrace step
      gray_threshold 0.0            // increase for weakening colors (0..1) [0]
      minimum_reuse 0.015           // reuse of old radiosity samples [0.015]
      brightness 1                  // brightness of radiosity effects (0..1) [1]

      adc_bailout 0.01/2
      //normal on                   // take surface normals into account [off]
      //media on                    // take media into account [off]
      //save_file "file_name"       // save radiosity data
      //load_file "file_name"       // load saved radiosity data
      //always_sample off           // turn sampling in final trace off [on]
      //max_sample 1.0              // maximum brightness of samples
    }
  #end
}

#default {
  texture {
    pigment {rgb 1}
    #if (Radiosity)
      finish {
        ambient 0.0
        diffuse 0.6
        specular 0.3
      }
    #else
      finish {
        ambient 0.1
        diffuse 0.6
        specular 0.3
      }
    #end
  }
}
  

// create a TrueType text shape
text {
  ttf             // font type (only TrueType format for now)
  "arial.ttf",  // Microsoft Windows-format TrueType font file name
  "A)bort",      // the string to create
  0.1,              // the extrusion depth
  0               // inter-character spacing
  pigment {color rgb <1,0,0>}
  rotate x*90
  translate y*0.1
  scale 0.4
  rotate y*210
  translate <1.35,0,-1.5>
}
// create a TrueType text shape
text {
  ttf             // font type (only TrueType format for now)
  "arial.ttf",  // Microsoft Windows-format TrueType font file name
  "R)etry",      // the string to create
  0.1,              // the extrusion depth
  0               // inter-character spacing
  pigment {color rgb <1,0,0>}
  rotate x*90
  translate y*0.1
  scale 0.4
  rotate y*210
  translate <1.35,0,-1.0>
}
// create a TrueType text shape
text {
  ttf             // font type (only TrueType format for now)
  "arial.ttf",  // Microsoft Windows-format TrueType font file name
  "I)nfluence",      // the string to create
  0.1,              // the extrusion depth
  0               // inter-character spacing
  pigment {color rgb <1,1,0>}
  rotate x*90
  translate y*0.1
  scale 0.4
  rotate y*210
  translate <1.5,0,0.25>
}
// create a TrueType text shape
text {
  ttf             // font type (only TrueType format for now)
  "arial.ttf",  // Microsoft Windows-format TrueType font file name
  "with hammer",      // the string to create
  0.1,              // the extrusion depth
  0               // inter-character spacing
  pigment {color rgb <1,1,0>}
  rotate x*90
  translate y*0.1
  scale 0.4
  rotate y*210
  translate <1.95,0,0.5>
}

