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
   #include "GALAXY.SF"

   #declare galaxy_seed = 1;
   #declare star_count = 500;
   #declare star_type = 3;
   #declare star_colour = <1, .9, .7>;
   #declare star_scale = 1.5;
   #include "GALAXY.SF"

light_source { <10, 10, -10> color rgb 1 shadowless }

#include "truck.inc"
#include "colors.inc"

//object {Truck translate z*10}


// create a regular point light source
light_source
{
  0*x // light's position (translated below)
  color red 1.0  green 1.0  blue 1.0  // light's color
  translate <-20, 40, -20>
}

#declare X1A=14;
#declare X2A=-10;
#declare Z1A=-1.7;
#declare Z2A=10;

#declare X1B=-8;
#declare X2B=-8;
#declare Z1B=10;
#declare Z2B=-20;

#declare X1T=-5;
#declare Y1T=3;
#declare Z1T=-5;

#declare X2T=15;
#declare Y2T=-3;
#declare Z2T=30;

#declare I=clock*0.6;

#declare XT=(X2T-X1T)*I+X1T;
#declare YT=(Y2T-Y1T)*I+Y1T;
#declare ZT=(Z2T-Z1T)*I+Z1T;

object {
  Truck
  rotate <-clock*316-210,-clock*597+90,-clock*734+150>
  translate <XT,YT,ZT>
}

camera
{
  up y
  right image_width/image_height*x
  //Use this to keep the same vertical angle
  angle 60*3/4*image_width/image_height
  location  <0.0 , 0.0 ,-5.0>
  look_at   <XT,YT,ZT>//<15.0 , -3.0 , 30.0>
}


