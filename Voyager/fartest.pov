/*
--------------------------------------------------------------------------------------
VOYAGER TEST POV FILE                  By Constantine Thomas                   28/7/98

Use this file to generate any of the 'plan' views in the Voyager Gallery, or
otherwise experiment with the Voyager object.
--------------------------------------------------------------------------------------
*/
#include "stars.inc"
object {Stars}
//DECLARE ROTATION PARAMETERS FOR VOYAGER/SCAN PLATFORM ROTATION
#declare ybodyrot=0;
#declare yrot=0;
#declare xrot=0;

#declare Scale=exp(clock*20);
#warning concat("Scale: ",str(Scale,14,14))

//-THEN- INCLUDE VOYAGER!
#include "Voyager111.inc"

//(long) Front view, magnetometer to left (+x left, +y up, +z towards)
camera {
   direction <0,0,1000*Scale>
   location  <0, 0, 0>
   look_at  <0,0,1>
}
//Camera 2 light source
light_source
{
  0*x // light's position (translated below)
  color rgb 1  // light's color
  shadowless
}


//------------------------------------End camera selection-----------------------------

//DRAW VOYAGER SPACECRAFT
        object {Voyager rotate <0, ybodyrot, 0> // change ybodyrot at top of file to rotate Voyager!
//                scale 1000
                translate z*5*Scale}                     // scale 1000 to scale Voyager so that 1 POV unit = 1 metre.
                                                // This is only necessary 'on the ground' - in fly-by scenes
                                                // you will have to omit this and use the default scaling
                                                // defined in the #include, which is 1 POV unit = 1 kilometre.
