/*
--------------------------------------------------------------------------------------
VOYAGER TEST POV FILE                  By Constantine Thomas                   28/7/98

Use this file to generate any of the 'plan' views in the Voyager Gallery, or
otherwise experiment with the Voyager object.
--------------------------------------------------------------------------------------
*/

//DECLARE ROTATION PARAMETERS FOR VOYAGER/SCAN PLATFORM ROTATION
#declare ybodyrot=0
#declare yrot=0
#declare xrot=0


//-THEN- INCLUDE VOYAGER!
#include "Voyager.inc"




/*
--------------CAMERAS + BUILT-IN LIGHT SOURCES--------------
(1) (long) Backside Camera, magnetometer to right (+x right, +y up, -z towards)
(2) (long) Front view, magnetometer to left (+x left, +y up, +z towards)
(3) (long) Top View looking straight down (+x right, y towards, +z up)
(4) (close-up) Bottom View looking straight up (+x right, -y towards, +z down)
(5) Scan Platform oblique view
(6) Magboom/RTG oblique view
(7) 'Photo' view (roughly the same as in the actual Voyager photograph)
*/

// Choose your camera!
//------------------------------

#switch (7)

//------------------------------
//

//Camera choices
#case (1)
//(long) Backside Camera, magnetometer to right (+x right, +y up, -z towards)
camera {
   location  <2,1.5, -15>
   direction <0,0,1>
   look_at  <2,0.6,0>
}
//Camera 1 light source
light_source {0*x
color red 1 green 1 blue 1
translate <0, 3, -17.5>
}
#break



#case (2)
//(long) Front view, magnetometer to left (+x left, +y up, +z towards)
camera {
   location  <2, 1.5, 15>
   direction <0,0,1>
   look_at  <2,0.6,0>
}
//Camera 2 light source
light_source
{
  0*x // light's position (translated below)
  color red 1.0  green 1.0  blue 1.0  // light's color
  shadowless
  translate <5, 3, 10>
}
#break


#case (3)
//(long) Top View looking straight down (+x right, y towards, +z up)
camera {
   location  <5.5, 16.5, 0>
   direction <0,0,1>
   look_at  <5.5,0,0>
}
//Camera 3 light source
light_source
{
  0*x // light's position (translated below)
  color red 1.0  green 1.0  blue 1.0  // light's color
  translate <5.5, 16.5, 7>
}
#break


#case (4)
//(close-up) Bottom View looking straight up (+x right, -y towards, +z down)
camera {
   location  <0, -18, 0>
   direction <0,0,2.5>
   look_at  <0,0,0>
}
//Camera 4 light source
light_source
{
  0*x // light's position (translated below)
  color red 1.0  green 1.0  blue 1.0  // light's color
  translate <0, -20, 0>
}
#break


#case (5)
//Scan Platform oblique view
camera {
   location  <-6.5, 0.5, 4>
   direction <0,0,1>
   look_at  <-2.4,0.5,0>
}
//Camera 5 light source
light_source
{
  0*x // light's position (translated below)
  color red 1.0  green 1.0  blue 1.0  // light's color
  translate <-17, 5, 17>
}
#break


#case (6)
//Magnetometer boom/RTG oblique view
camera {
   location  <6.5, 0.5, 4>
   direction <0,0,1>
   look_at  <2.4,0.5,0>
}
//Camera 6 light source
light_source
{
  0*x // light's position (translated below)
  color red 1  green 1 blue 1  // light's color
  translate <17, 5, 17>
}
#break



#case (7)
//'Photo' view (roughly the same as in the actual Voyager photograph)
camera {
   location  <0, -1, 25>
   direction <0,0,2.3>
   look_at  <0,0.5,0>
   rotate <0,-40,0>
}
//Camera 7 light source
light_source {
   0*x
   color red 1 green 1 blue 1
   translate <0, 1, 40>
   rotate <0,20,0>
}
#break
#end


//------------------------------------End camera selection-----------------------------

//DRAW VOYAGER SPACECRAFT
        object {Voyager rotate <0, ybodyrot, 0> // change ybodyrot at top of file to rotate Voyager!
                scale 1000}                     // scale 1000 to scale Voyager so that 1 POV unit = 1 metre.
                                                // This is only necessary 'on the ground' - in fly-by scenes
                                                // you will have to omit this and use the default scaling
                                                // defined in the #include, which is 1 POV unit = 1 kilometre.
