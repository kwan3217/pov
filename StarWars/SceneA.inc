
#if(clock>5) 
  #declare CameraProgress=1;
#else
  #declare CameraProgressA=-0.0625;
  #declare CameraProgressB=0.625;
  #declare CameraProgressC=-0.5625;
  #declare y1p=0.25;
  #if(clock<3) 
    #declare CameraProgress=clock*y1p;
  #else
    #declare CameraProgress=CameraProgressA*clock*clock+CameraProgressB*clock+CameraProgressC;
  #end
#end

#declare CamLocStart=<-1,-2.75,-8>;
#declare CamLocStop=<2.4,-2.75,-6.5>;
#declare CamLookStart=<0,-1.75,-1.75>;
#declare CamLookStop=<0,-0.8,-1.75>;
#declare CamLoc=Linterp(0,CamLocStart,1,CamLocStop,CameraProgress);
#declare CamLook=Linterp(0,CamLookStart,1,CamLookStop,CameraProgress);

camera {
   perspective
   location CamLoc
   sky <0, 1, 0>
   direction <0, 0, 1>
   right <OutAspect, 0, 0>
   up <0, 1, 0>
   look_at CamLook
}

#if(clock>5)

#declare Subtitle=text {
   //*PMName Kwan
   ttf "arial.ttf"
   "a division of Kwan Systems"
   0.0, <0, 0>
   no_shadow
   finish {
     ambient 1 diffuse 0
   }
   scale 0.1
   rotate y*90
   translate <1,-1/3,0>
   scale 0.01
   pigment {
      color rgbf <1, 1, 1,BLinterp(5,1,6,0,clock)>
   }
}
#declare SubtitleCenter=(max_extent(Subtitle)-min_extent(Subtitle))/2;
union {
  Subtitle
  translate -SubtitleCenter.x
  LocationLookAt(CamLoc,CamLook,y)
}

#end

#if(clock<1)
  sphere {
    CamLoc,0.005
    finish {
      ambient 0 diffuse 0
    } 
    pigment {
      color rgbf<1,1,1,clock>
    }
    hollow
  }
#end

#if(clock>10)
  sphere {
    CamLoc,0.005
    finish {
      ambient 0 diffuse 0
    } 
    pigment {
      color rgbf<1,1,1,BLinterp(10,1,11,0,clock)>
    }
    hollow
  }
#end

#declare Swing=sin(Linterp(0,0,4*pi,11,clock));

#declare GirderTex = texture {
   finish {
      metallic 1
      specular 0.2
   }
   
   pigment {
      color rgb <0.25, 0.25, 0.25>
   }
}

#declare LadderStep = union {
   cylinder {
      <0, 0, 0.225>, <0, 0, -0.225>, 0.01
   }
   
   cylinder {
      <0, 0, 0.225>, <0, 0, -0.225>, 0.01
      matrix < 1, 0, 0,
               0, 1, 0,
               -1, 0, 1,
               0, 0, 0 >
      translate x*0.225
   }
}

#declare GirderSide = union {
   box {
      <-1.7, -0.025, -0.025>, <1.7, 0.025, 0.025>
      translate z*(-0.225)
   }
   
   object {
      LadderStep
   }
   
   object {
      LadderStep
      translate x*(-0.45)
   }
   
   object {
      LadderStep
      translate x*(-0.9)
   }
   
   object {
      LadderStep
      translate x*(-1.35)
   }
   
   object {
      LadderStep
      translate x*0.45
   }
   
   object {
      LadderStep
      translate x*0.9
   }
   
   cylinder {
      <0, 0, 0.225>, <0, 0, -0.225>, 0.01
      translate x*1.35
   }
   translate y*(-0.225)
}

#declare Girder = union {
   object {
      GirderSide
      rotate <0, 0, 0>
   }
   
   object {
      GirderSide
      rotate x*90
   }
   
   object {
      GirderSide
      rotate x*180
   }
   
   object {
      GirderSide
      rotate x*270
   }
   
   texture {
      GirderTex
   }
}

global_settings {
   assumed_gamma 1.5
   noise_generator 2
}

#declare Frame = union {
   object {
      //*PMName Top Girder
      Girder
      translate y*0.7
   }
   
   object {
      //*PMName Bottom Girder
      Girder
      translate y*(-1.4)
   }
   
   object {
      //*PMName Left Mast
      Girder
      rotate z*(-90)
      scale <0.5, 1, 1>
      translate <-1.6, -0.725, 0>
   }
   
   object {
      //*PMName Right Mast
      Girder
      rotate z*(-90)
      scale <0.5, 1, 1>
      translate <1.6, -0.725, 0>
   }
}

difference {
   //*PMName Kwan Logo
   
   cylinder {
      <0, 0.5, 0>, <0, -0.5, 0>, 2
   }
   
   cylinder {
      <0, 0.495, 0>, <0, -0.495, 0>, 1.995
   }
   
   prism {
      linear_spline
      linear_sweep
      -0.51, 0.51,
      17,
      <47, 104>, <62, 109>, <56, 88>, <61, 88>, <55, 75>, <74, 88>, <70, 88>, <87, 104>, <106, 104>, <75, 77>, <97, 36>, <81, 36>, <65, 68>, <51, 57>, <48, 36>, <38, 60>, <47, 104>
      scale <0.0625, 1, 0.0625>
      translate <-2, 0, -2>
      translate <-2.125, 0, -2.75>
   }
   rotate x*(-90)
   scale <1, 1, 3>
   
   texture {
      pigment {
         color rgb <1, 0.5, 0>
      }
      
      normal {
         agate
         0.1
         agate_turb 0.5
         turbulence <0, 0, 0>
      }
   }
}

object {
   //*PMName Front Frame
   Frame
   translate z*(-1)
}

object {
   //*PMName Back Frame
   Frame
   translate z*1
}

object {
   //*PMName Top Girder
   Girder
   rotate y*90
   scale <0.5, 1, 0.88>
   translate <-0.1, 0.7, 0>
}

object {
   //*PMName Bottom Girder
   Girder
   rotate y*90
   scale <0.5, 1, 0.88>
   translate <-0.1, -1.4, 0>
}

object {
   //*PMName Mast
   Girder
   rotate z*90
   scale <0.5, 1.3, 1>
   translate <-0.1, -0.25, 0>
}

#declare Stone = texture {
   normal {
      granite
      0.2
   }
   
   pigment {
      granite
      
      color_map {
         [ 0 color rgb <0.5, 0.5, 0.5>
         ]
         [ 0.5 color rgb <0.6, 0.55, 0.5>
         ]
         [ 1 color rgb <0.25, 0.25, 0.25>
         ]
      }
   }
   scale 0.1
}

union {
   //*PMName Pedastal
   
   box {
      <-2.5, -2.2, -2.5>, <2.5, -3, 2.5>
   }
   
   box {
      <-2.6, -2.3, -2.6>, <2.6, -2.31, 2.6>
   }
   
   box {
      <-2.6, -2.4, -2.6>, <2.6, -2.41, 2.6>
   }
   
   box {
      <3, -3, 3>, <-3, -4, -3>
   }
   
   difference {
      box {
         <-2.7, -2.8, -2.7>, <2.7, -3, 2.7>
      }
      
      cylinder {
         <-2.7, -2.8, -2.7>, <2.7, -2.8, -2.7>, 0.2
      }
      
      cylinder {
         <-2.7, -2.8, 2.7>, <2.7, -2.8, 2.7>, 0.2
      }
      
      cylinder {
         <-2.7, -2.8, -2.7>, <-2.7, -2.8, 2.7>, 0.2
      }
      
      cylinder {
         <2.7, -2.8, -2.7>, <2.7, -2.8, 2.7>, 0.2
      }
   }
   
   texture {
      Stone
   }
}

#declare Cornice = intersection {
   cylinder {
      <0, 0.125, 0>, <0, -0.125, 0>, 0.125
   }
   
   cylinder {
      <0.125, 0, 0>, <-0.125, 0, 0>, 0.125
   }
   
   cylinder {
      <0, 0, 0.125>, <0, 0, -0.125>, 0.125
   }
}

union {
   //*PMName Tower
   
   object {
      Cornice
      translate <-6.625, -1.625, 1.625>
   }
   
   object {
      Cornice
      translate <-6.625, -1.625, 0.375>
   }
   
   box {
      <-6.625, -4, 0.375>, <-5.375, -1.625, 1.625>
   }
   
   cylinder {
      <-6.625, -4, 0.375>, <-6.625, -1.625, 0.375>, 0.125
   }
   
   cylinder {
      <-5.375, -4, 0.375>, <-5.375, -1.625, 0.375>, 0.125
   }
   
   cylinder {
      <-6.625, -4, 1.625>, <-6.625, -1.625, 1.625>, 0.125
   }
   
   cylinder {
      <-5.375, -4, 1.625>, <-5.375, -1.625, 1.625>, 0.125
   }
   
   cylinder {
      <-5.375, -1.625, 1.625>, <-6.625, -1.625, 1.625>, 0.125
   }
   
   cylinder {
      <-5.375, -1.625, 0.375>, <-6.625, -1.625, 0.375>, 0.125
   }
   
   cylinder {
      <-5.375, -1.625, 0.375>, <-5.375, -1.625, 1.625>, 0.125
   }
   
   cylinder {
      <-6.625, -1.625, 0.375>, <-6.625, -1.625, 1.625>, 0.125
   }
   
   object {
      Cornice
      translate <-5.375, -1.625, 1.625>
   }
   
   object {
      Cornice
      translate <-5.375, -1.625, 0.375>
   }
   
   box {
      <-6.5, -1.5, 0.5>, <-5.5, -0.5, 1.5>
   }
   
   box {
      <-6.625, -0.6, 0.375>, <-5.375, -0.62, 1.625>
   }
   
   box {
      <-6.625, -0.7, 0.375>, <-5.375, -0.72, 1.625>
   }
   
   box {
      <-6.625, -0.8, 0.375>, <-5.375, -0.82, 1.625>
   }
   
   cylinder {
      <-6, -0.5, 1>, <-6, 0.5, 1>, 0.2
      open
      scale 1
      rotate <0, 0, 0>
      translate <0, 0, 0>
      hollow
   }
   
   union {
      //*PMName Tower Spotlight
      
      difference {
         box {
            <-0.091052, -0.10947, -0.01>, <0.09342, 0.02, 0.01>
         }
         
         box {
            <-0.08, -0.1, -0.011>, <0.08, 0.021, 0.011>
         }
      }
      
      union {
         cylinder {
            <0, 0.1, 0>, <0, -0.08, 0>, 0.05
            hollow false
         }
         
         cone {
            <0, 0.1, 0>, 0.049,
            <0, 100, 0>, 4
            
            material {
               interior {
                  media {
                     method 3
                     emission rgb <1, 1, 1>
                  }
               }
               
               texture {
                  pigment {
                     color rgbf <1, 1, 1, 1>
                  }
               }
            }
            hollow
         }
         
         cylinder {
            <-0.05, 0, 0>, <-0.08, 0, 0>, 0.01
            hollow
         }
         
         cylinder {
            <0.05, 0, 0>, <0.08, 0, 0>, 0.01
            hollow
         }
         rotate <0, 0, 0>
      }
      
      cylinder {
         <0, -0.11, 0>, <0, -0.15, 0>, 0.01
      }
      translate y*0.15
      rotate y*30.6
      translate <-6, 0, 1>
      
      texture {
         GirderTex
      }
   }
   
   texture {
      Stone
   }
}

#declare Columns = union {
   cylinder {
      <-1, -1, 6.5>, <-1, -4, 6.5>, 0.3
   }
   
   cylinder {
      <-3, -1, 6.5>, <-3, -4, 6.5>, 0.3
   }
   
   cylinder {
      <-5, -1, 6.5>, <-5, -4, 6.5>, 0.3
   }
   
   cylinder {
      <-7, -1, 6.5>, <-7, -4, 6.5>, 0.3
   }
   
   cylinder {
      <-9, -1, 6.5>, <-9, -4, 6.5>, 0.3
   }
   
   cylinder {
      <-11, -1, 6.5>, <-11, -4, 6.5>, 0.3
   }
}

union {
   //*PMName Colonnade
   
   box {
      <-12, -4, 6>, <12, -3.9, 7>
   }
   
   box {
      <-12, -1, 6.9>, <12, -3.9, 7>
   }
   
   box {
      <-12, -1, 6.9>, <-12.724, -4, -13.429>
   }
   
   box {
      <12, -1, 6.9>, <12.724, -4, -13.429>
   }
   
   box {
      <-12, -1, 6>, <12, -1.1, 7>
   }
   
   object {
      Columns
   }
   
   object {
      Columns
      scale <-1, 1, 1>
   }
   
   texture {
      Stone
   }
}

union {
   //*PMName Foot plates
   
   box {
      <-1.8, -2.15, -1.3>, <-1.4, -2.2, -0.7>
      
      texture {
         GirderTex
      }
   }
   
   box {
      <-1.8, -2.15, -1.3>, <-1.4, -2.2, -0.7>
      
      texture {
         GirderTex
      }
      translate x*3.2
   }
   
   box {
      <-1.8, -2.15, -1.3>, <-1.4, -2.2, -0.7>
      
      texture {
         GirderTex
      }
      translate <3.2, 0, 2>
   }
   
   box {
      <-1.8, -2.15, -1.3>, <-1.4, -2.2, -0.7>
      
      texture {
         GirderTex
      }
      translate z*2
   }
   
   box {
      <-1.8, -2.15, -1.3>, <-1.4, -2.2, -0.7>
      
      texture {
         GirderTex
      }
      translate <1.5, 0, 1>
   }
}

sky_sphere {
   pigment {
      gradient <0, 1, 0>
      
      color_map {
         [ 0 color rgb <0.8, 0.6, 0.1>
         ]
         [ 0.3 color rgb <0.3, 0.2, 0.5>
         ]
         [ 0.4 color rgb <0, 0, 0.5>
         ]
      }
   }
}

object {
   Girder
   scale <1, 0.5, 0.5>
   translate <0, -1.8, -1.8>
}

text {
   //*PMName Kwan
   ttf "arialbi.ttf"
   "Kwan"
   0.02, <0, 0>
   scale <1.4, 1.4, 1>
   translate <-1.6263, -1.6816, -1.7>
   
   pigment {
      color rgb <0.75, 0.75, 0.75>
   }
}

text {
   //*PMName Heavy Industries
   ttf "arialbi.ttf"
   "Heavy Industries"
   0.02, <0, 0>
   scale <0.5, 0.5, 1>
   translate <-1.6263, -1.9176, -1.95>
   
   pigment {
      color rgb <1, 1, 1>
   }
}

plane {
   <0, 1, 0>, -4
   
   texture {
      Stone
   }
}

union {
   //*PMName Right spotlight
   
   difference {
      box {
         <-0.091052, -0.10947, -0.01>, <0.09342, 0.02, 0.01>
      }
      
      box {
         <-0.08, -0.1, -0.011>, <0.08, 0.021, 0.011>
      }
   }
   
   union {
      light_source {
         <0, 0, 0>, rgb <1, 1, 1>
         spotlight
         radius 2
         falloff 2.5
         point_at <0, 1, 0>
         
         looks_like {
            cylinder {
               <0, 0.05, 0>, <0, -0.05, 0>, 0.05
            }
         }
      }
      
      cylinder {
         <-0.05, 0, 0>, <-0.08, 0, 0>, 0.01
      }
      
      cylinder {
         <0.05, 0, 0>, <0.08, 0, 0>, 0.01
      }
      rotate <54.3, 1.7, 12.4>
   }
   
   cylinder {
      <0, -0.11, 0>, <0, -0.15, 0>, 0.01
   }
   translate y*0.15
   rotate y*(-12.2)
   translate <3, -4, -7>
}

union {
   //*PMName Left Spotlight
   
   difference {
      box {
         <-0.091052, -0.10947, -0.01>, <0.09342, 0.02, 0.01>
      }
      
      box {
         <-0.08, -0.1, -0.011>, <0.08, 0.021, 0.011>
      }
   }
   
   union {
      light_source {
         <0, 0, 0>, rgb <1, 1, 1>
         spotlight
         radius 2
         falloff 2.5
         point_at <0, 1, 0>
         
         looks_like {
            cylinder {
               <0, 0.05, 0>, <0, -0.05, 0>, 0.05
            }
         }
      }
      
      cylinder {
         <-0.05, 0, 0>, <-0.08, 0, 0>, 0.01
      }
      
      cylinder {
         <0.05, 0, 0>, <0.08, 0, 0>, 0.01
      }
      rotate x*70
   }
   
   cylinder {
      <0, -0.11, 0>, <0, -0.15, 0>, 0.01
   }
   translate y*0.15
   rotate y*(30.6+Swing*15)
   translate <-3, -4, -7>
}

union {
   //*PMName Left Upper Spotlight
   
   difference {
      box {
         <-0.091052, -0.10947, -0.01>, <0.09342, 0.02, 0.01>
      }
      
      box {
         <-0.08, -0.1, -0.011>, <0.08, 0.021, 0.011>
      }
   }
   
   union {
      cylinder {
         <0, 0.1, 0>, <0, -0.08, 0>, 0.05
         hollow false
      }
      
      cone {
         <0, 0.1, 0>, 0.049,
         <0, 100, 0>, 4
         
         material {
            interior {
               media {
                  method 3
                  emission rgb <1, 1, 1>
               }
            }
            
            texture {
               pigment {
                  color rgbf <1, 1, 1, 1>
               }
            }
         }
         hollow
      }
      
      cylinder {
         <-0.05, 0, 0>, <-0.08, 0, 0>, 0.01
         hollow
      }
      
      cylinder {
         <0.05, 0, 0>, <0.08, 0, 0>, 0.01
         hollow
      }
      rotate x*10
   }
   
   cylinder {
      <0, -0.11, 0>, <0, -0.15, 0>, 0.01
   }
   translate y*0.15
   rotate y*30.6
   translate <-2.4, -2.2, -2.4>
   
   texture {
      GirderTex
   }
}

union {
   //*PMName Right Upper Spotlight
   
   difference {
      box {
         <-0.091052, -0.10947, -0.01>, <0.09342, 0.02, 0.01>
      }
      
      box {
         <-0.08, -0.1, -0.011>, <0.08, 0.021, 0.011>
      }
   }
   
   union {
      cylinder {
         <0, 0.1, 0>, <0, -0.08, 0>, 0.05
         hollow false
      }
      
      cone {
         <0, 0.1, 0>, 0.049,
         <0, 100, 0>, 4
         
         material {
            interior {
               media {
                  method 3
                  emission rgb <1, 1, 1>
               }
            }
            
            texture {
               pigment {
                  color rgbf <1, 1, 1, 1>
               }
            }
         }
         hollow
      }
      
      cylinder {
         <-0.05, 0, 0>, <-0.08, 0, 0>, 0.01
         hollow
      }
      
      cylinder {
         <0.05, 0, 0>, <0.08, 0, 0>, 0.01
         hollow
      }
      rotate x*(10-10*Swing)
   }
   
   cylinder {
      <0, -0.11, 0>, <0, -0.15, 0>, 0.01
   }
   translate y*0.15
   rotate y*(-30.6)
   translate <2.4, -2.2, -2.4>
   
   texture {
      GirderTex
   }
}

light_source {
   <0, 4.7381, -6.2273>, rgb <1, 1, 1>
   media_interaction off
   media_attenuation off
}

sphere {
   <0, 0, 0>, 100
   
   material {
      interior {
         media {
            method 3
            
            scattering {
               1, rgb <0.2, 0.2, 0.2>
               extinction 0
            }
         }
      }
      
      texture {
         pigment {
            color rgbf <1, 1, 1, 1>
         }
      }
   }
   no_shadow
   no_reflection
   hollow
}
