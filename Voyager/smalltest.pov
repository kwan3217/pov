/*
--------------------------------------------------------------------------------------
VOYAGER TEST POV FILE                  By Constantine Thomas                   28/7/98

Use this file to generate any of the 'plan' views in the Voyager Gallery, or
otherwise experiment with the Voyager object.
--------------------------------------------------------------------------------------
*/

//DECLARE ROTATION PARAMETERS FOR VOYAGER/SCAN PLATFORM ROTATION
#declare ybodyrot=0;
#declare yrot=0;
#declare xrot=0;

#declare Scale=1/exp(clock*20);
#warning concat("Scale: ",str(Scale,14,14))

//-THEN- INCLUDE VOYAGER!
#include "Voyager111.inc"

//(long) Front view, magnetometer to left (+x left, +y up, +z towards)
camera {
   location  <2, 1.5, 15>*Scale
   look_at  <2,0.6,0>*Scale
   angle 30
}
//Camera 2 light source
light_source
{
  0*x // light's position (translated below)
  color red 1.0  green 1.0  blue 1.0  // light's color
  shadowless
  translate <5, 3, 10>*Scale
}


//------------------------------------End camera selection-----------------------------

//DRAW VOYAGER SPACECRAFT
        object {Voyager rotate <0, ybodyrot, 0> // change ybodyrot at top of file to rotate Voyager!
                scale 1000*Scale}                     // scale 1000 to scale Voyager so that 1 POV unit = 1 metre.
                                                // This is only necessary 'on the ground' - in fly-by scenes
                                                // you will have to omit this and use the default scaling
                                                // defined in the #include, which is 1 POV unit = 1 kilometre.
