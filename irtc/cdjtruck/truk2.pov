// GALAXY INCLUDE FILE: CUSTOM GALAXY SCENE
// ****************************************
// This scene shows how Galaxy.obj and Galaxy.sf can be used to build
// custom galaxy scenes, piece by piece.
//
// Recommended resolution: 640 x 480, anti-aliasing on

// STARFIELD
#version 3.7;
global_settings {assumed_gamma 2.2}
   #declare star_count = 2000;
   #declare star_scale = .5;
//   #include "GALAXY.SF"

   #declare galaxy_seed = 1;
   #declare star_count = 500;
   #declare star_type = 3;
   #declare star_colour = <1, .9, .7>;
   #declare star_scale = 1.5;
//   #include "GALAXY.SF"

// PINK NEBULA
   #declare galaxy_colour1 = <1.2, 1, 1.1>;
   #declare galaxy_colour2 = <1, .3, .6>;
   #declare galaxy_pattern_origin = x * 1;
   #declare galaxy_turb_origin = x * -4;
   #declare galaxy_object_name = "Nebula3";
   #declare galaxy_object_scale = 1.75;
   #declare galaxy_object_position = <-5, 5, 0>;
   #declare galaxy_cluster_name = "";
   #include "GALAXY.OBJ"

// BLUE NEBULA
   #declare galaxy_colour1 = <.5, .9, 1.2>;
   #declare galaxy_colour2 = <.1, .3, .5>;
   #declare galaxy_pattern_origin = x * -20;
   #declare galaxy_object_name = "Nebula2";
   #declare galaxy_object_scale = 1.2;
   #declare galaxy_object_position = <10, -12, 0>;
//   #include "GALAXY.OBJ"

// LARGE STAR
   #declare galaxy_object_name = "Star1";
   #declare galaxy_colour1 = <1.5, 1.5, 1.5>;
   #declare galaxy_object_scale = 1;
   #declare galaxy_object_position = <17, -10, 0>;
//   #include "GALAXY.OBJ"

light_source { <10, 10, -10> color rgb 1 shadowless }

#include "truck.inc"
#include "colors.inc"

//object {Truck translate z*10}

//sphere {
//  <-5,0,30>,10
//  pigment {Red}
//  finish {ambient 1}
//}

// create a regular point light source
light_source
{
  0*x // light's position (translated below)
  color red 1.0  green 1.0  blue 1.0  // light's color
  translate <-20, 40, -20>
}


camera
{
  up y
  right image_width/image_height*x
  //Use this to keep the same vertical angle
  angle 7*3/4*image_width/image_height
  location  <0.0 , 0.0 ,-5.0>
  look_at   <15.0 , -3.0 , 30.0>
}

sphere { 
  0,1 
  pigment { rgbt 1 } hollow
  interior { 
    media { 
      emission 1
      density { 
        spherical 
        density_map { 
          [0 rgb 0]
          [0.3 rgb <0.1,0,0>]
          [1 rgb <1,0,0>]
        }
      }
    }
    media { 
      absorption 0.1
      density { 
        spherical 
        density_map { 
          [0 rgb 0]
          [0.3 rgb <1,1,1>]
        }
      }
    }   
  }
  scale <14,14,14>
  translate <-8,-3,30>
}

/*sphere { 0, 1
  pigment { color rgbt <1, 1, 1, 1> }
  halo {
    emitting
    spherical_mapping
    linear
    color_map {
      [ 0 color rgbt <1, 0, 0, 1> ]
      [ 0.3 color rgbt <1, 0, 0, 0> ]
    }
    samples 10
  }
  hollow
  scale <14,14,14>
  translate <-8,-3,30>
}
*/
sphere {
  <15,-3,30>,0.2
  pigment {rgb <0,0,0>}
}

#declare I=2;
#while (I<40)
  torus {
    I*0.05,0.05
    pigment {
      wood
      color_map {
        [0 rgb <1, 2, 1> ]
        [1 rgb <0.8, 0, 0> ]
      }
      scale 4
      rotate x*90
    }
    translate x*0.1
    rotate x*3
    rotate y*(clock+0.8)*(sqrt(40)-sqrt(I))*157
    rotate x*-30
    translate <15,-3,30>
  }
  #declare I=I+1;
#end

#declare X1A=14;
#declare X2A=-10;
#declare Z1A=-1.5;
#declare Z2A=10;

#declare X1B=-8;
#declare X2B=-8;
#declare Z1B=10;
#declare Z2B=-20;

#declare X1T=3.6;
#declare Y1T=-0.8;
#declare Z1T=6;

#declare X2T=15.5;
#declare Y2T=-3;
#declare Z2T=30;

#declare I=clock*0.85;

#declare XT=(X2T-X1T)*I+X1T;
#declare YT=(Y2T-Y1T)*I+Y1T;
#declare ZT=(Z2T-Z1T)*I+Z1T;

object {
  Truck
  scale 0.1
  rotate <clock*360,clock*540,clock*720>
  translate <XT,YT,ZT>
}

#declare I=0;
#while (I<0.1)
  #declare XA=(X2A-X1A)*I+X1A;
  #declare XB=(X2B-X1B)*I+X1B;
  #declare ZA=(Z2A-Z1A)*I+Z1A;
  #declare ZB=(Z2B-Z1B)*I+Z1B;
  cone {
    <XA,0,ZA>,0.05
    <XB,0,ZB>,0.3
    rotate x*-30
    translate <0,-3,30>
    pigment {rgbt<1,0,0,0.8>}
  }
  #declare I=I+0.01;
#end


// create a TrueType text shape
text
{
  ttf "verdana.ttf",
  "Black Holes Suck!",
  0.5, 0
  scale 0.5
  pigment {rgb 1}
  translate y*-2.2
  translate x*(3.6-clock*15)
  translate z*30
  rotate x*4.0
  rotate y*26.56
}
