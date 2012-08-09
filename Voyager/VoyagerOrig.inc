/*
--------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------
VOYAGER FOR POVRAY                  Version 1.1                       Updated: 28/7/98
--------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------
-------------------------VOYAGER FOR POVRAY SOURCECODE UPDATES------------------------
--------------------------------------------------------------------------------------

26/7/98: Fixed most of the problems that plagued the original version of the Voyager
sourcecode - John Duglosz pointed out to me how to rotate the scan platform from within
the scene file instead of the #include file. Scott Manley suggested turning the dish
into a more realistic paraboloid - I found that doing this removed the scaling problem
I was having, so Voyager now fits into planetary fly-by scenes where the scale is 1 POV
unit = 1 kilometre! I have also made some modifications to the shape of the upper part
of Voyager, shortening the antenna cone, and lowering the HGA Dish and Dish Collar so
that it's nearer the Bus. Although these modifications may seem minor, they make the
model look *much* more realistic!


--------------------------------------------------------------------------------------
DISTRIBUTION/LEGAL STUFF:

This source code is Copyright 1998 by Constantine Thomas. All rights reserved. You are not
allowed to use the 'Voyager for POVray' source code for commercial gain. This file
was written by Constantine Thomas (constantine.thomas@lancaster.ac.uk) and is
available from:

        http://www.lancs.ac.uk/postgrad/thomasc1/render/voyager/voyager.htm

You should have downloaded this file from the 'official' Voyager for POVray website
at the URL above, along with a sample .pov file called voyager.pov and a flyby scene file
called vgr-gany.pov. I have asked that this file should not be placed on any other servers
because there will be useful supplementary material on my site, and should I make any
changes to the code then I can do so to the file in one central location and everyone that
uses the file will know about it - if you would like to draw attention to Voyager for
POVray then please place a link to the URL above instead. MODIFIED VERSIONS OF THIS FILE
SHOULD NOT BE DISTRIBUTED IN ANY WAY, though obviously you can change the rotational
parameters contained herein (described below) for your own usage.

Please credit me as author of this source code in project that this model is used
in - all this involves is mentioning my name somewhere prominent where the results
are displayed ;-). As usual with the POV resources on my website, I would like to be
informed of any images or animations (especially the latter!) that this is used in,
and would greatly appreciate a look at the results if they're available to see online!

Other that that, have a ball 8). Happy raytracing (and animating!)!



--------------------------------------------------------------------------------------
FILE DESCRIPTION:

   This is a hand-assembled, ultra-realistic model of the Voyager spacecraft
(both of which were identical). In fact, it's probably the most realistic model
one can get without having the actual design plans in front of you to work from!
Being created in POVray, all the components here are simple objects like spheres,
cylinders, and boxes - this means you don't have the problem of thousands of little
triangles in the model that you get when you convert from formats like DXF or 3DS.
As such, it should be quick and easy to render.
    The model was based on the photographs and schematics of Voyager and its instruments
located at the Voyager Home Page (http://vraptor.jpl.nasa.gov/voyager/voyager.html) and
a few other sites on the web. To get an idea of the scale of Voyager, the dish is 12 ft
in diameter (the model is scaled accordingly) - a picture showing Voyager next to a model
of a 6ft tall man can be found in the Voyager Gallery on my website.
      Everything in this model is reproduced by estimation from these sources and by
comparison to the classic Voyager animations by Jim Blinn at JPL/NASA where available.
No other software was used to create this model - only some graph paper and a lot of
sleepless nights!

    I began work on this code on Sunday 24th May 1998; it was completed on the 1st June
1998 and represents approximately 140 hours work (you figure out how much sleep I had
that week... ;-) ). It was created entirely by hand (no modelling software involved,
just graph paper!), and contains a grand total of 955 frame-level objects.



--------------------------------------------------------------------------------------
ORIENTATION OF SPACECRAFT:

    The Spacecraft is by default oriented as follows. However, it can be rotated
easily around any of these axes since it is centred around <0,0,0>:

                                                                  On-Ground orientation      Inflight orientation
                                                                  ~~~~~~~~~~~~~~~~~~~~~      ~~~~~~~~~~~~~~~~~~~~
High Gain Antenna Dish:         points to +y (vertical)           Top of craft               Back of craft (sun-pointing)
Base of craft:                  points to -y (vertical)           Bottom of craft            Front of craft

Gold Disc:                      faces +z                          Front of craft             (Side of craft)
Red Access Panel:               faces -z                          Rear of craft              (Side of craft)

Magnetometer/RTG Boom:          extends to +x                     Magboom/RTG side           (Side of craft)
Camera Boom/Scan Platform:      extends to -x                     Camboom/Scan side          (Side of craft)




---------------------------------------------------------------------------------------------------------
VERY IMPORTANT!!!-------------------------SCALING FLY-BY SCENES------------------------------------------
---------------------------------------------------------------------------------------------------------

I am assuming (actually, I'm *suggesting*) that your planetary fly-by scenes in which you will be using
Voyager are set to a scale of 1 POV unit = 1 kilometre. There are many practical reasons for this - first,
it makes it much easier to scale real-life distances if you have a simple scale like this. Second, you will
probably find that you'll *have* to use a scale like this because if you use 1 POV unit = 1 metre you will
hit what I call the 'translation limit'. This limit is reached when objects are translated too far
(usually over a few million units) from the camera - beyond this they seem to just 'disappear', and you can't
find them no matter how far you zoom in even if you were looking right at them before. I suspect this limit
exists because of inherent limitations to the raytracing process itself. Whatever the reason, planetary scenes
where the scale is set at 1 POV unit = 1 metre simply do not appear to work. Thus, I recommend that you use
a scale of 1 POV unit = 1 kilometre for all the objects (planets, moons and vehicles) in your fly-by scenes,
because you are much more likely to avoid this translation limit then. And also, Voyager is by default scaled
to fit into such scenes.

Two scale factors have been applied to Voyager within the Source Code (on lines 1394 and 1398). The first
- scale 0.622 - scales Voyager down so that 1 POV unit = 1 metre (1:1 scaling). The second - scale 0.001 -
scales Voyager down by a further (cumulative) factor of 1000 so that 1 POV unit = 1 kilometre. The dish,
which is actually 1.80 metres in diameter, is therefore 1.8 units (metres) in diameter after the 0.622
scaling, and 0.0018 units (kilometres) in diameter after the extra 0.001 scaling.
         If you need to use Voyager in scenes where 1 POV Unit = 1 metre (for example, I have rendered such
a scene with Voyager on the ground to scale with a 6ft tall human) then simply add 'scale 1000' to the
Voyager object to restore the dish to a diameter of 1.8 units/metres.



---------------------------------------------------------------------------------------------------------
ANIMATION AND ROTATIONAL PARAMETERS:

    This model includes full support for Scan Platform rotation around the x/y axes. These can now be set
from within the POV scene file in which the Voyager object is being used. Since you'll be having to rotate
Voyager itself around its dish-axis (which should always point towards the Sun) if you want to make realistic
animations, there is a term (ybodyrot) set aside specifically for that task.
     To use these parameters, you must #declare them BEFORE the  #include="voyager.inc" statement at the
start of the scene file. Even if you're not planning to do any rotations (which means the craft will be
oriented as described a couple of sections above this), you MUST set them to zero, otherwise they'll be
undefined in the #include and you'll get an error message.
     To make life easier, I've included the relevant code below - simply paste this into the top of your
scene file and change the values if you wish to rotate anything:


//--------CUT THIS OUT AND PASTE IT AT THE TOP OF YOUR SCENE FILE!!-----------
//---------START CODE SEGMENT----------

//DECLARE ROTATION PARAMETERS FOR VOYAGER/SCAN PLATFORM
#declare ybodyrot = 0      // rotates Voyager around dish (y) axis.
#declare xrot = 0          // rotates Scan Platform around horizontal axis.
#declare yrot = 0          // rotates Scan Platform around vertical Support Strut.

//-THEN- INCLUDE VOYAGER!
#include = "Voyager.inc"   // includes Voyager object with rotation terms defined above.

//---------END OF CODE SEGMENT---------


Change the following parameters to rotate the appropriate parts of the spacecraft. Clock values
should also be used here for animations.


ybodyrot:   This rotates the whole spacecraft around the central body/dish/antenna (y) axis.
            This is done primarily for the particles and fields experiments which require
            measurements in various orientations (these experiments cannot themselves move
            independently of the main bus of Voyager), and also to move the scan platform
            boom round to the side facing a target if the body of Voyager should obstruct
            the view during the fly-by. Note that the HGA (antenna) dish must *always* point
            towards the Sun (or Earth, if you can distinguish between the two [not likely]).
                    ybodyrot is not part of the Voyager Sourcecode - rather, it must be added
            as in a rotate statement with the Voyager object itself in the POV Scene File. i.e.

                            object {Voyager rotate <0,ybodyrot,0>}

            See the POV Scene files included with this source code file for examples.


xrot:       This rotates the Scan Platform around an axis defined by the wide horizontal
            cylinder in the Scan Platform object. This allows the whole platform to track
            targets behind or in front of the spacecraft (for inflight purposes only,
            'behind' is defined as being the Sun/Earthward direction that the dish faces).
            POSITIVE xrot rotates the scanplatform DOWNWARDS when viewed from above (the dish)

yrot:       This rotates the whole Scan Platform around the thin cylindrical strut that
            connects it to the main rectangular Camera Boom (the strut itself defines
            the rotational axis). This allows the instruments on the platform to track targets
            as Voyager passes them.
            +y rotation is CLOCKWISE when viewed from above (the dish).

xrot and yrot can and should be used together for perfect realism, but I can imagine that
Voyager camera tracking is going to be an extremely tricky business to get absolutely right!
One obvious thing to bear in mind is that the Scan Platform is not going to be used when the
whole body of the spacecraft is rotating (otherwise you'd get very blurred pictures from the
cameras! ;-)). There is also probably a limiting angle for the xrot and yrot parameters,
defined by the field of view blocked off by other parts of Voyager (ie. the body itself in
the case of yrot, or the Camera Boom in the case of xrot). Valid values of xrot are probably in
the range of +90 to -90 degrees. For now, you'll have to figure out yrot limits for yourself,
but it should be easy to determine.
     Anyway, the capability for truly realistic movement is there should you require it...

--------------------------------------------------------------------------------------
OBJECT INDEX:

Start of actual Source Code:        line 258

VGRTex TEXTURE:                     line 271

VOYAGER OBJECT DECLARATION:         line 297

BUS + BUS OBJECTS:
     Main Bus (main body):          line 303
     Fuel Tank:                     line 368
     Fuel Tank Supports:            line 375
     The Gold Disc:                 line 382
     The 'Dish Widget':             line 389
     Bus Radiators:                 line 401
     Special Bus Radiator:          line 438
     MagBoom Support Box:           line 485
     HG Magnetometers:              line 490
     Rear Bus Access Panel:         line 514
     Bus Support Struts:            line 523
     Optical Calibration Panel:     line 551
     PRA-PWS antennae:              line 567

DISH + DISH OBJECTS:
     Low Gain Antenna (LGA):        line 619
     LGA Support Struts:            line 638
     High Gain Antenna (HGA) Dish:  line 656
     HGA Dish Copper Rim:           line 666
     HGA Dish Base Antenna Horn:    line 677
     HGA Dish Collar:               line 687
     HGA Dish Support Struts:       line 697


BOOMS:
     Magnetometer boom:             line 726
     RTG boom + supports:           line 796
     Camera boom + supports:        line 901

CAMBOOM INSTRUMENTS:
     CRS:                           line 1014
     PLS:                           line 1055
     LECP:                          line 1127

SCAN PLATFORM + INSTRUMENTS:
     ScanPlatform:                  line 1180
     WACam:                         line 1199
     NACam:                         line 1230
     PPS:                           line 1261
     IRIS:                          line 1277
     UVS:                           line 1306

SCANBOOM (Camboom+Scanplatform):    line 1351
Voyager Whole Object Scaling:       line 1393
--------------------------------------------------------------------------------------
*/



//--------------------------------------------------------------------------------------
//-----------------------------SOURCE CODE BEGINS HERE----------------------------------
//--------------------------------------------------------------------------------------
//--------DEFINE INCLUDE FILES---------
#include "colors.inc"
#include "textures.inc"
#include "glass.inc"
#include "metals.inc"
#include "shapes.inc"

#ifndef (ybodyrot) #declare ybodyrot=0; #end
#ifndef (yrot)     #declare yrot=0;     #end
#ifndef (xrot)     #declare xrot=0;     #end




//--------DEFINE VGRTex TEXTURE--------
//VgrTex for most of the bodywork - a dark grey metallic texture.
#declare VgrTex =
texture  {
           pigment {color rgb <0.4,0.4,0.4>}
             finish {
                     ambient 0.05
                     brilliance 5
                     diffuse 0.8
                     metallic
                     specular 0.80
                     roughness 1/10
                    }//end finish
         } //end VgrTex definition





//-----------------------------------------------------------------------------------------------
//--------------------------------------------VOYAGER OBJECTS------------------------------------
//-----------------------------------------------------------------------------------------------
//
// This is the main Voyager object declaration - Voyager is the sum of all the (955!) objects below.
// Refer to it by this name (Voyager) when you use this as an #include in your POV files.

//DECLARE VOYAGER OBJECT (the union of everything below this line)
#declare Voyager =
union {



// MAIN BUS (DEFINITION)
// Voyager body (or 'Bus') is an decagonal prism 0.5 units high and 2 units across (ie. the 'radius' is 1 unit)
// The default centre of the body is at <0,0.25,0>
// This is scaled so that it is 0.8 units high

#declare Bus =
difference {
//Outer Body
prism {
  linear_sweep
  linear_spline
  0,          // base height
  0.5,        // top height
  11,         // number of points
  <1,0>,
  <0.8090169944, 0.5877852523>,
  <0.309016994, 0.9510565163>,
  <-0.309016994, 0.9510565163>,
  <-0.8090169944, 0.5877852523>,
  <-1,0>,
  <-0.8090169944, -0.5877852523>,
  <-0.309016994, -0.9510565163>,
  <0.309016994, -0.9510565163>,
  <0.8090169944, -0.5877852523>,
  <1,0>
  }

//Inner Body
prism {
  linear_sweep
  linear_spline
  0,         // base height
  0.5,       // top height
  11,        // number of points
  <1,0>,
  <0.8090169944, 0.5877852523>,
  <0.309016994, 0.9510565163>,
  <-0.309016994, 0.9510565163>,
  <-0.8090169944, 0.5877852523>,
  <-1,0>,
  <-0.8090169944, -0.5877852523>,
  <-0.309016994, -0.9510565163>,
  <0.309016994, -0.9510565163>,
  <0.8090169944, -0.5877852523>,
  <1,0>
  scale <0.8,1.2,0.8>
  translate <0,-0.05,0>
  }
  texture {VgrTex}
  scale <1.6,1.6,1.6>
} // end Bus Definition difference


//DRAW BODY WITH CAVITIES BEHIND RADIATORS (to get appropriate shading behind them...)
difference
     {object {Bus}
      box {<-0.40,0.35,-0.1>,  <0.40,-0.35,0.005> texture {VgrTex} translate <0,0.4,1.522> rotate <0,36,0> }
      box {<-0.40,0.35,-0.1>,  <0.40,-0.35,0.005> texture {VgrTex} translate <0,0.4,1.522> rotate <0,144,0>}
      box {<-0.40,0.35,-0.1>,  <0.40,-0.35,0.005> texture {VgrTex} translate <0,0.4,1.522> rotate <0,-36,0>}
      box {<-0.40,0.35,-0.1>,  <0.40,-0.35,0.005> texture {VgrTex} translate <0,0.4,1.522> rotate <0,-144,0>}
     }// end Bus with Radiator Cavities difference
// END MAIN BUS DEFINITION



//FUEL TANK (sphere in the middle of the Bus)
  sphere
  {<0,0,0>, 0.6
  texture {VgrTex}
  translate <0,0.7,0>
  }// end Fuel Tank Sphere

//FUEL TANK SUPPORT CROSS-STRUTS
  cylinder {<-1.4,0.7,0>, <1.4,0.7,0> 0.04 texture {VgrTex}}
  cylinder {<0,0.7,-1.4>, <0,0.7,1.4> 0.04 texture {VgrTex}}




//THE GOLD DISC
//I though Brass looked more realistic than the Gold_Texture...
cylinder {<0,0.4,1.522>, <0,0.4,1.55> 0.25 texture {Brass_Texture finish {Shiny reflection 1}}}




//THE DISH WIDGET
//This is the widget that connects from the body above the Disc to the underside of the HGA dish. You
//can see it in most of the photos and schematics, but its purpose is never explained!
union {
         cylinder {<0,0.8,1.217>, <0,1.85,1.75> 0.02     texture {VgrTex} }
         box {<-0.2,1.85,1.7>   , <0.2,2.15,1.9>         pigment {White} finish {diffuse 0.8} }
         clipped_by {object {Paraboloid_Y translate <0,0.95,0> scale <3,1.5,3> inverse}}
      }// end Dish Widget union




//RADIATORS
// Radiator Definition (Union)
#declare Radiator =
union {
//frame
difference
      {
      box {<-0.40,0.35,-0.005>,  <0.40,-0.35,0.005> texture {Silver_Texture finish {Shiny}}}  // frame
      box {<-0.35,0.0125,-0.006>, <0.35,0.325,0.006> texture {Silver_Texture}} //subtract these two
      box {<-0.35,-0.325,-0.006>, <0.35,-0.0125,0.006> texture {Silver_Texture}} //boxes to put fins in
      }// end difference

//crossbar (standalone)
      box {<-0.35,-0.0125,0.005>, <0.35,0.0125,0.03> texture {Silver_Texture}}  //crossbar

//angled fins
union {
// POVcode program to generate the angled fin arrays on top and bottom of radiator.
#declare tcount=0;
#declare numbfin=8;
#declare fin =  box {<0.041, 0.325,-0.003>, <-0.041, 0.0125, 0.003>
                     texture {Silver_Texture finish {Shiny}}
                     rotate <0,30,0>}       // individual angled fin

#while (tcount < numbfin)
       object {fin translate <0.284-(tcount*0.081),0,0>}                    // top fins    (row of 8)
       object {fin rotate <180,0,0> translate <0.284-(tcount*0.081),0,0>}   // bottom fins (row of 8 oppositely angled)
   #declare tcount=tcount + 1;
#end
       }// end angled fins sub-union

translate <0,0.4,1.522>         // moves entire radiator unit out to body exterior
} // end Radiator Definition union




//SPECIAL RADIATOR
//This is the unique radiator to the right of the disc (as you're looking at it) - it has a grey box instead
//of the usual fins on the bottom row. Otherwise it's the same as the others.

#declare Specialradiator =
union {
//frame
difference
      {
      box {<-0.40,0.35,-0.005>,  <0.40,-0.35,0.005> texture {Silver_Texture finish {Shiny}}}  // frame
      box {<-0.35,0.0125,-0.006>, <0.35,0.325,0.006> texture {Silver_Texture}} //subtract this for top row of fins
      }// end difference

//The grey lower box replacing the lower fins that makes this radiator different to all the rest
      box {<-0.35,-0.325,-0.006>, <0.35,-0.0125,0.01> pigment {Grey} finish {Shiny}}

//crossbar (standalone)
      box {<-0.35,-0.0125,0.005>, <0.35,0.0125,0.03> texture {Silver_Texture}}  //crossbar

//angled fins
union {
// POVcode program to generate the angled fin arrays on top and bottom of radiator.
#declare tcount=0;
#declare numbfin=8;
#declare fin =  box {<0.041, 0.325,-0.003>, <-0.041, 0.0125, 0.003>
                     texture {Silver_Texture finish {Shiny}}
                     rotate <0,30,0>}       // individual angled fin

#while (tcount < numbfin)
       object {fin translate <0.284-(tcount*0.081),0,0>}                    // top fins    (row of 8)
   #declare tcount=tcount + 1;
#end
       }// end angled fins sub-union

translate <0,0.4,1.522>         // moves entire radiator unit out to body exterior
} // end Specialradiator Definition union



//PLACE RADIATORS ON BUS
object {Specialradiator rotate <0,-36,0>}        // rotates special radiator to right of disc on Bus.
object {Radiator rotate <0,-144,0>}              // places and rotates normal radiator around Bus.
object {Radiator rotate <0,36,0>}                // places and rotates normal radiator around Bus.
object {Radiator rotate <0,144,0>}               // places and rotates normal radiator around Bus.



//SUPPORT BOX BASE FOR MAGNETOMETER BOOM (on Bus, not part of Magboom union)
box {<1.2,1,0.4><1.7,0.3,-0.4> texture {VgrTex}}



//HIGH FIELD MAGNETOMETERS (HFMAGS) (?)
// I think these are the HFMAGs. They're the two long white boxes round the back of the Bus, near
// the RTG boom/Body connector.
//HFMAG box 1
union {
    box {<-0.1,0,-0.15><0.05,0.8,0.15>   texture {VgrTex}}
    box {<0.05,0,-0.15><0.1,0.8,0.15> pigment {White} finish {Dull}}
    scale 0.8                                                       //scales down box.
    translate <0,0,-0.225> translate <0,0.8,0> translate <1.45,0,0> //moves box up and around to place on Bus.
    rotate <0,54,0>                                                 //rotates to correct position.
      }// end HFMAG box 1 union

//HFMAG box 2
union {
    box {<-0.1,0,-0.15><0.05,0.8,0.15>   texture {VgrTex}}
    box {<0.05,0,-0.15><0.1,0.8,0.15> pigment {White} finish {Dull}}
    scale 0.8                                                       //scales down box.
    translate <0,0,0.225> translate <0,0.8,0> translate <1.45,0,0>  //moves box up and around to place on Bus.
    rotate <0,54,0>                                                 //rotates to correct position.
      }// end HFMAG box 1 union




//REAR ACCESS PANEL (on back of bus)
box {
     <-0.40,0.35,-0.005>,  <0.40,-0.35,0.005> pigment {Brown}
     translate <0,0.4,-1.522>                                       //translates panel to rear of craft
     }//end Access Panel Box




//BUS SUPPORT STRUTS
// These are the triangular struts on which Voyager would stand if it was on the ground,
// coming out from the base of the decagonal Bus (body).
#declare brad=0.05;  // Radius of base support struts
union  {
//orientations are as viewed from below the centre of the spacecraft
//left
  cylinder {<-1.5,-2,0>, <-1.1,0,0.75>,   brad}
  cylinder {<-1.5,-2,0>, <-1.1,0,-0.75>,  brad}
  sphere   {<-1.1,0,0.75>, 0.1                } //bottom left
//right
  cylinder {<1.5,-2,0>, <1.1,0,-0.75>,    brad}
  cylinder {<1.5,-2,0>, <1.1,0,0.75>,     brad}
  sphere   {<1.1,0,0.75>, 0.1                 }  //bottom right
//top
  cylinder {<0,-2,-1.5>, <1.1,0,-0.75>,   brad}
  cylinder {<0,-2,-1.5>, <-1.1,0,-0.75>,  brad}
  sphere   {<1.1,0,-0.75>, 0.1                }  //top right
//bottom
  cylinder {<0,-2,1.5>, <1.1,0,0.75>,     brad}
  cylinder {<0,-2,1.5>, <-1.1,0,0.75>,    brad}
  sphere   {<-1.1,0,-0.75>, 0.1               }  //top left
  texture {VgrTex}
        }// end Bus support struts union




//OPTICAL CALIBRATION TARGET PANEL
union {
cylinder {<0,0.5,0.55>, <0,0.5,-0.55>, 0.025 texture {VgrTex}}                //lateral connector to base strut
box {<0,-0.5,-0.5>, <-0.01,0.5,0.5> texture {VgrTex}}                         //panel base
box {<-0.005,-0.45,-0.45>, <-0.015,0.45,0.45> texture {Chrome_Texture}}       //Reflective calibrator panel
box {<0,-0.5,-0.5>, <-0.1,-0.51,0.5> texture {Chrome_Texture}}                //sticky-outy bit at the bottom
rotate <0,0,-30>                                                   //tilts panel relative to vertical
translate <-1.5, -1, 0>                                            //moves panel down to position on base struts
      }// end Optical Calibration Target union







//----------------------------------------------------------------------------------
//-------------PLANETARY RADIO ASTRONOMY/PLASMA WAVE SUBSYSTEM (PRA-PWS)------------
//----------------------------------------------------------------------------------
// These are the two long thin antennae that straddle the Magboom from beneath it.

#declare PRAPWS =
union
{
//PRA-PWS main box
box {<-0.3,-0.167,-0.5>, <-0.1,0.167,0.5> texture {VgrTex}}         // 0.333 units high total
box {<-0.1,-0.167,-0.5>, <0,0.055,0.5>    texture {VgrTex}}         // up to 2/3rds of the main box height


//Antenna/aerial attachment boxes
//Box1, on the right as you look at PRA-PWS from the front
union {
box {<0.15,0.11,0.15>, <-0.15,-0.11,-0.15> texture {VgrTex}}
cylinder {<0,0,0>, <30,0,0>, 0.03 texture {VgrTex finish {ambient 1}}}      //aerial
     rotate <0,-45,0>                         //rotates box round y-axis
     rotate <0,0,-30>                        //rotates box down to below the main box level
     translate <0.1,0,0>                     //moves out from main box
     translate <0,0,0.24>                    //moves to side
     translate <0,-0.181,0>                  //moves down to correct y-level
     } //end Box1 antenna/aerial attachment box union


//Box2, on the left as you look at PRA-PWS from the front
union {
box {<0.15,0.11,0.15>, <-0.15,-0.11,-0.15> texture {VgrTex}}
cylinder {<0,0,0>, <30,0,0>, 0.03 texture {VgrTex finish {ambient 1}}}      //aerial
     rotate <0,45,0>                         //rotates box round y-axis
     rotate <0,0,-30>                        //rotates box down to below the main box level
     translate <0.1,0,0>                     //moves out from main box
     translate <0,0,-0.24>                    //moves to side
     translate <0,-0.181,0>                  //moves down to correct y-level
     } //end Box2 antenna/aerial attachment box union

} // end PRA-PWS union



//DRAW PRA-PWS (on Bus under Magboom)
object {PRAPWS scale 0.5 translate <1.84, 0.4, 0>}






//-----------------------------------------------------------------------------------
//------------------------HIGH GAIN ANTENNA AND DISH SUPPORT STRUTS------------------
//-----------------------------------------------------------------------------------
//LOW GAIN ANTENNA (LGA) on top of struts above main HGA Dish.
union { box      {<0.09,4.15,0.01> , <-0.09,4.41,-0.01>
                  pigment {White}}                                          //antenna axial fin on top
        cylinder {<0,4.275,0>      , <0,4.35,0> 0.1
                  texture {Bronze_Texture}}                                 //cylinder on axial fin
        cone     {<0,3.95,0> 0.175 , <0,4.21,0> 0.1
                  texture {Bronze_Texture}}                                 //top 'cone' part of antenna
        cylinder {<0,3.85,0>       , <0,3.95,0> 0.2
                  texture {Bronze_Texture}}                                 //cylindrical base of cone
        cylinder {<0,3.75,0>       , <0,3.849,0> 0.601
                  texture {Bronze_Texture}}                                 //bronze side surface of antenna mid-base
        cylinder {<0,3.75,0>       , <0,3.85,0> 0.60
                  pigment {White}}                                          //cylindrical mid-base of antenna
        cone     {<0,3.75,0> 0.6   , <0,3.54,0> 0.05
                  pigment {White}}                                          //wide dish-pointing base cone (underside)
     }// end antenna union



//LGA ANTENNA STRUTS
#declare arrad=0.04;   // Radius of antenna struts
// These struts are thin and triangular, with apex on dish - co-ordinate format is (<dish>, <top>)
union {
   cylinder {<0,1.8,-1.5>, <-0.4,3.75,-0.4>, arrad rotate <0,000,0> }
   cylinder {<0,1.8,-1.5>, <+0.4,3.75,-0.4>, arrad rotate <0,000,0> }

   cylinder {<0,1.8,-1.5>, <-0.4,3.75,-0.4>, arrad rotate <0,120,0> }
   cylinder {<0,1.8,-1.5>, <+0.4,3.75,-0.4>, arrad rotate <0,120,0> }

   cylinder {<0,1.8,-1.5>, <-0.4,3.75,-0.4>, arrad rotate <0,240,0> }
   cylinder {<0,1.8,-1.5>, <+0.4,3.75,-0.4>, arrad rotate <0,240,0> }

   pigment {White}
      clipped_by {object {Paraboloid_Y translate <0,0.95,0> scale <3,1.5,3>}}
      }// end antenna struts union


//HIGH GAIN ANTENNA (HGA) DISH
object {Paraboloid_Y
           translate <0,0.95,0>                            // moves paraboloid up so it can be clipped
           clipped_by {plane {y , 1.86}}
           pigment {White}
           finish {Dull}
           scale <3,1.5,3>
}


//HGA DISH COPPER RIM
object {Paraboloid_Y
           translate <0,0.95,0>                            // moves paraboloid up so it can be clipped
           clipped_by {plane {y , 1.86 inverse}}
           clipped_by {plane {y , 1.88}}
           texture {Copper_Texture}
           finish {diffuse 1}
           scale <3,1.5,3>
         }// end HGA Dish Copper Rim


//HGA DISH BASE ANTENNA HORN
//This is the cylinder/cone widget at the base of the dish, directly beneath the LGA antenna.
union {
      cone {<0,2.19,0> 0.075, <0,2.57,0>, 0.1 open texture {Bronze_Texture}}        // Bronze 'horn' cone
      cone {<0,1.42,0>,0.15, <0,2.19,0>, 0.1 pigment {White} finish {Dull}}         // white base cone
      clipped_by {object {Paraboloid_Y translate <0,0.95,0> scale <3,1.5,3>}}       // so the flat base of base cone doesn't go beneath the dishobject
      }//end HGA Dish Base Antenna Horn union



//HGA DISH COLLAR
difference {
  cylinder { <0,1.45,0> , <0,1.8,0> 1.5}
  cylinder { <0,1.45,0> , <0,1.8,0> 1.4 open}
      clipped_by {object {Paraboloid_Y translate <0,0.95,0> scale <3,1.5,3> inverse}}
      texture {VgrTex}
           }// end HGA Dish Collar difference



//HGA DISH SUPPORT STRUTS (between body and dish)
#declare dsrad=0.05;  // Radius of dish support struts
//format : (Base point, dish collar point)
union  {
  cylinder {<-0.396,0.78,1.217>, <-0.75,1.55,1.2>, dsrad}                       // above radiator
  cylinder {<-1.036,0.78,0.752>, <-0.75,1.55,1.2>, dsrad}
  cylinder {<-0.396,0.78,1.217>, <-0.75,1.55,1.2>, dsrad rotate <0,108,0>}
  cylinder {<-1.036,0.78,0.752>, <-0.75,1.55,1.2>, dsrad rotate <0,108,0>}
  cylinder {<-0.396,0.78,1.217>, <-0.75,1.55,1.2>, dsrad rotate <0,180,0>}
  cylinder {<-1.036,0.78,0.752>, <-0.75,1.55,1.2>, dsrad rotate <0,180,0>}
  cylinder {<-0.396,0.78,1.217>, <-0.75,1.55,1.2>, dsrad rotate <0,288,0>}
  cylinder {<-1.036,0.78,0.752>, <-0.75,1.55,1.2>, dsrad rotate <0,288,0>}
  texture {VgrTex}
       }// end HGA Dish Support Struts union








//----------------------------------------------------
//----------------------------------------------------
//----------------       BOOMS       -----------------
//----------------------------------------------------
//----------------------------------------------------


//-------------------------------------------------------------------------
//----------------------------MAGNETOMETER BOOM----------------------------
//-------------------------------------------------------------------------
// The long arm of the magnetometer boom (magboom) above the RTG boom, in the +x direction:
// Each segment is 0.3 unit blocks long (after scaling) - these are used to define the length of the boom.

//MAGNETOMETER BOOM SEGMENTS
#declare boomrad=0.1;
#declare boombit =
union {
  cylinder {<0.7,0,0>, <0.7,0,1> , boomrad}
  cylinder {<-.7,0,0>, <-.7,0,1> , boomrad}
  cylinder {<0,1,0>,   <0,1,1>   , boomrad}

  cylinder {<0.7,0,0>, <-.7,0,0> , boomrad}
  cylinder {<0,1,0>,   <-.7,0,0> , boomrad}
  cylinder {<0,1,0>,   <0.7,0,0> , boomrad}

  cylinder {<0.7,0,0>, <-.7,0,1> , boomrad}
  cylinder {<-.7,0,0>, <0,1,1>   , boomrad}
  cylinder {<0,1,0>,   <0.7,0,1> , boomrad}
      } // end boombit union


#declare tcount=0;
#declare segs=66.7;


//magboom
#declare magboom =
union {
#while (tcount < segs)
  object {boombit translate <0,0,tcount> texture {Bronze_Texture}}     // boom segments
  #declare tcount=tcount + 1;
#end


//MAGBOOM BASE CYLINDER (Bus Attachment)
   cylinder {<0,0.5,-0.25>,    <0,0.5,4>   , 1     texture {VgrTex}}   // main base cylinder


//MAGBOOM BASE RINGS:
   cylinder {<0,0.5, 3.9> ,    <0,0.5,4>   , 1.2   texture {VgrTex}}   //  (outer)
   cylinder {<0,0.5, 2.9> ,    <0,0.5,3>   , 1.2   texture {VgrTex}}   //
   cylinder {<0,0.5, 1.9> ,    <0,0.5,2>   , 1.2   texture {VgrTex}}   //
   cylinder {<0,0.5, 0.9> ,    <0,0.5,1>   , 1.2   texture {VgrTex}}   //  (inner/body)


//MAGBOOM SPINE (central spine running up entire length of Magboom)
   cylinder {<0,0.5, 1.9> ,    <0,0.5, 67> , 0.07   texture {Bronze_Texture}}


//MAGBOOM (outer) END TERMINATOR BOX
  box {<-0.25,0.5,0.25>, <0.25,-0.5,-0.25> texture {Bronze_Texture} translate <0,0.5,67.1>}
    } //end magboom union


//DRAW MAGBOOM
object {magboom
        scale 0.3
        translate <0,-0.4,0>     // moves the base to centre height of decagonal body (y was -0.5)
        translate <0,0,1.75>      // moves the base out to edge of body          (z was 1.6)
        rotate <-35,0,0>         // angles it upwards
        rotate <0,90,0>          // rotates it round to the RTG side of Voyager
       }// end magboom object





//-----------------------------------------------------------------------------------------------
//--------------------RTG BOOM + RTG GENERATORS, AND CONNECTOR STRUTS----------------------------
//-----------------------------------------------------------------------------------------------
//NB: RTG boom is +x direction, below the long magnetometer boom.

#declare rtgrad=0.07;

//the rtgb object below describes the struts that connect the rtgblock to the body
#declare rtgb=

//RTG SUPPORT STRUTS
union {
//section 1 (nearest body)
  cylinder {<2.5,1,0.5>      <1.28,0.71,0.87>   rtgrad texture {VgrTex}}   // upper triangular body linker
  cylinder {<2.5,1,-0.5>     <1.28,0.71,-0.87>  rtgrad texture {VgrTex}}   // upper triangular body linker
  cylinder {<2.5,0.5,0.5>    <1.28,0.07,0.87>   rtgrad texture {VgrTex}}   // lower triangular body linker
  cylinder {<2.5,0.5,-0.5>   <1.28,0.07,-0.87>  rtgrad texture {VgrTex}}   // lower triangular body linker

//section 2 (middle part)
  cylinder {<2.5,1,0.5>      <3.375,0.6,0.4>    rtgrad texture {VgrTex}}   // Upper central linker
  cylinder {<2.5,1,-0.5>     <3.375,0.6,-0.4>   rtgrad texture {VgrTex}}   // Upper central linker
  cylinder {<2.5,0.5,0.5>    <3.375,0.1,0.4>    rtgrad texture {VgrTex}}   // Lower central linker
  cylinder {<2.5,0.5,-0.5>   <3.375,0.1,-0.4>   rtgrad texture {VgrTex}}   // Lower central linker

//section 3 (RTG end)
  cylinder {<3.375,0.6,0.4>  <4.2,0.05,0.3>     rtgrad texture {VgrTex}}   // Upper RTG linker
  cylinder {<3.375,0.6,-0.4> <4.2,0.05,-0.3>    rtgrad texture {VgrTex}}   // Upper RTG linker

  cylinder {<3.375,0.1,0.4>  <4.2,-0.2,0.3>     rtgrad texture {VgrTex}}   // Lower RTG linker
  cylinder {<3.375,0.1,-0.4> <4.2,-0.2,-0.3>    rtgrad texture {VgrTex}}   // Lower RTG linker


//CROSSLINKS
//crosslink A connects upper and lower section 1/2 (rectangular)
  cylinder {<2.5,1,0.5>      <2.5,0.5,0.5>      rtgrad texture {VgrTex}}   // side crosslink
  cylinder {<2.5,1,-0.5>     <2.5,0.5,-0.5>     rtgrad texture {VgrTex}}   // side crosslink
  cylinder {<2.5,1,0.5>      <2.5,1,-0.5>       rtgrad texture {VgrTex}}   // top crosslink
  cylinder {<2.5,0.5,-0.5>   <2.5,0.5,0.5>      rtgrad texture {VgrTex}}   // bottom crosslink

//crosslink B connects lower section 1/2 and upper section 2.3 (rectangular, sides only)
  cylinder {<2.5,0.5,0.5>    <3.375,0.6,0.4>    rtgrad texture {VgrTex}}
  cylinder {<2.5,0.5,-0.5>   <3.375,0.6,-0.4>   rtgrad texture {VgrTex}}

//crosslink C connects upper and lower section 2/3 (rectangular)
  cylinder {<3.375,0.1,0.4>  <3.375,0.6,0.4>    rtgrad texture {VgrTex}}   // side crosslink
  cylinder {<3.375,0.1,-0.4> <3.375,0.6,-0.4>   rtgrad texture {VgrTex}}   // side crosslink
  cylinder {<3.375,0.6,0.4>  <3.375,0.6,-0.4>   rtgrad texture {VgrTex}}   // top crosslink
  cylinder {<3.375,0.1,0.4>  <3.375,0.1,-0.4>   rtgrad texture {VgrTex}}   // bottom crosslink
      }// end RTG support struts union


//The rtgcells are the three grey 'ribbed' boxes in the RTGboom
#declare rtgcell =
union {
  box {<-1,-1,-1>,<1,1,1>  rotate <00,0,0>}
  box {<-1,-1,-1>,<1,1,1>  rotate <30,0,0>}
  box {<-1,-1,-1>,<1,1,1>  rotate <60,0,0>}
  scale     <0.45,0.3,0.3>
  pigment {Gray35}
  finish  {Shiny}
      }// end rtgcell union


#declare rtgblock =
union {
       cylinder {<4.8,0 ,0>, <5, 0 , 0>, 0.5    texture {VgrTex}}    // Attachment Plate
       object {rtgcell translate <5.5, 0, 0>}                        // inner rtg
       object {rtgcell translate <6.5, 0, 0>}                        // middle rtg
       object {rtgcell translate <7.5, 0, 0>}                        // outer rtg
       cylinder {<4.8,0,0>, <7.8, 0, 0>, 0.3    texture {VgrTex}}    // Central support cylinder
       cylinder {<7.8,0,0>, <7.9, 0, 0>, 0.6    texture {VgrTex}}    // Wide End cap
       cylinder {<7.8,0,0>, <8, 0, 0>,   0.5    texture {VgrTex}}    // Terminating End cap

//Axial Brace cylinders
       cylinder {<4.85,0.45,0>, <7.85,0.45, 0>, 0.05  texture {VgrTex}}                     // Top brace cylinder
       cylinder {<4.85,0.45,0>, <7.85,0.45, 0>, 0.05  texture {VgrTex} rotate <120,0,0>}    // side brace cylinder
       cylinder {<4.85,0.45,0>, <7.85,0.45, 0>, 0.05  texture {VgrTex} rotate <240,0,0>}    // side brace cylinder

//triangular support struts
       cylinder {<6,-0.23,0.4>, <6.5,-1.23,0.45>,   0.05   texture {VgrTex}}  // DiscSide
       cylinder {<7,-0.23,0.4>, <6.5,-1.23,0.45>,   0.05   texture {VgrTex}}  // DiscSide
       cylinder {<6,-0.23,-0.4>, <6.5,-1.23,-0.45>, 0.05   texture {VgrTex}}  // OtherSide
       cylinder {<7,-0.23,-0.4>, <6.5,-1.23,-0.45>, 0.05   texture {VgrTex}}  // OtherSide

//straight support struts (going vertically down)
       cylinder {<7,-0.23,0.4>, <7,-1.23,0.45>, 0.05       texture {VgrTex}}
       cylinder {<7,-0.23,-0.4>, <7,-1.23,-0.45>, 0.05     texture {VgrTex}}
       scale 0.8 translate <0, -0.4,0>                                        //scales whole RTGBlock and moves it down
      }// end rtgblock union


#declare rtgboom=
 union {
        object {rtgb}
        object {rtgblock translate <0.25,0.25,0>}
       }// end rtgboom union


//DRAW RTG-BOOM
object {rtgboom}





//----------------------------------------------------------------------------------------------------
//----------------------CAMERA BOOM, BODY/CAMBOOM SUPPORTS, AND CAMBOOM EXPERIMENTS------------------
//----------------------------------------------------------------------------------------------------
// The rectangular boom on the opposite side of the craft to the mag/RTG booms.

// Scanboom support (connects Camera boom to main body)
// struts from radiator side to lateral top of boom
  cylinder {<-1.036,0.78,0.752>, <-2.2,2,0.2>,   0.04   texture {VgrTex}}     //corner above radiator
  cylinder {<-1.036,0.78,0.752>, <-2.2,2,-0.2>,  0.04   texture {VgrTex}}     //corner above radiator

//struts from 'anti-radiator' side to lateral top of boom
  cylinder {<-1.036,0.78,-0.752>, <-2.2,2,-0.2>, 0.04   texture {VgrTex}}
  cylinder {<-1.036,0.78,-0.752>, <-2.2,2,0.2>,  0.04   texture {VgrTex}}

//central long strut to underside of boom
  cylinder {<-1.6,0.78,0>, <-4.0,1.7,0>, 0.04           texture {VgrTex}}     // central strut



//-----------------------------------------------------------------------------------
//--------------CAMERA BOOM, goes towards -x after rotation (see later)--------------
//-----------------------------------------------------------------------------------
#declare camboomrad=0.1;
#declare camboombit =
union {
//top rectangle
  cylinder {<0.7,0,-1> , <0.7,0,1>  , camboomrad}
  cylinder {<0.7,0,1>  , <-0.7,0,1> , camboomrad}
  cylinder {<-0.7,0,1> , <-0.7,0,-1>, camboomrad}
  cylinder {<-0.7,0,-1>, <0.7,0,-1> , camboomrad}

//bottom rectangle
  cylinder {<0.7,1,-1> , <0.7,1,1>  , camboomrad}
  cylinder {<0.7,1,1>  , <-0.7,1,1> , camboomrad}
  cylinder {<-0.7,1,1> , <-0.7,1,-1>, camboomrad}
  cylinder {<-0.7,1,-1>, <0.7,1,-1> , camboomrad}

//vertical support struts
  cylinder {<0.7,0,-1> , <0.7,1,-1> , camboomrad}
  cylinder {<-0.7,0,1> , <-0.7,1,1> , camboomrad}
  cylinder {<-0.7,0,-1>, <-0.7,1,-1>, camboomrad}
  cylinder {<0.7,0,1>  , <0.7,1,1>  , camboomrad}

//diagonal support struts
  cylinder {<-0.7,0,1> , <-0.7,1,-1>, camboomrad}      //near diagonal
  cylinder {<0.7,0,-1> , <0.7,1,1>  , camboomrad}      //far diagonal
  cylinder {<-0.7,0,-1>, <0.7,0,1>  , camboomrad}      //top diagonal
  cylinder {<0.7,1,-1> , <-0.7,1,1> , camboomrad}      //bottom diagonal
 } //end camboombit union


#declare tcount=0;
#declare segs=7;

#declare camboom=

union {
#while (tcount < segs)
  object {camboombit translate <0,0,tcount*2>}
  #declare tcount=tcount + 1;
#end
      } //end camboom union


//-------------------------------------------------------------------------------------
//CAMBOOM SUPPORT STRUT (links Camboom to Scan Platform)
//Camboom/Strut Connectors
union {
      union {
     cylinder { <0.1, 1.52, 0>,  <0.1, 1.48, 0>,    0.2  texture {VgrTex} scale <2,1,1.2>}  //Top Camboom Connector
     cylinder { <0.1, 1.22, 0>,  <0.1, 1.18, 0>,    0.2  texture {VgrTex} scale <2,1,1.2>}  //Bottom Camboom Connector
     clipped_by {plane {x, 0.11}}
            }// end Camboom Connector union


//actual support strut
     cylinder { <0, 1.65, 0>,  <0, 0, 0>,           0.07 texture {VgrTex}}

translate <-6.5,0.5,0>
}//end Camboom Support Strut union



//----------------------------------------------------------------------
//----------------------------------------------------------------------
//----------------------------------------------------------------------
//SUPPORT STRUTS FOR CRS, PLS, LECP (separate from camboom union and individual camboom experiments)
//CRS Support Struts (above CamBoom)
cylinder {<-4, 2, 0.2>, <-4.31, 2.35, 0.2>, 0.03     texture {VgrTex}}      // seg 3/4 to CRS (front)
cylinder {<-4.6, 2, 0.2>, <-4.29, 2.35, 0.2>, 0.03   texture {VgrTex}}      // CRS to seg 4/5 (front)

cylinder {<-4, 2, -0.2>, <-4.31, 2.35, -0.2>, 0.03   texture {VgrTex}}      // seg 3/4 to CRS (back)
cylinder {<-4.6, 2, -0.2>, <-4.29, 2.35, -0.2>, 0.03 texture {VgrTex}}      // CRS to seg 4/5 (back)


//PLS Support Box
box {<-5.2,1.85,0.2>, <-5.8,2.25,-0.2>               texture {VgrTex}}      // goes through CamBoom


//LEP Support Struts (under middle of CamBoom)
cylinder {<-4.0,1.7,0>, <-4.19, 1.35, 0>, 0.03       texture {VgrTex}}      //Bodyside
cylinder {<-4.6,1.7,0>, <-4.41, 1.35, 0>, 0.03       texture {VgrTex}}      //Scanside







//----------------------------------------------------------------------
//--------------------------CAMBOOM EXPERIMENTS-------------------------
//----------------------------------------------------------------------

//----------CRS (Cosmic Ray) EXPERIMENT------------------------------------
//This is the cube on the top of the camboom nearest the body of the craft

#declare CRS =
union
{
difference {
//CRS box
         box {<-0.5,0,-0.5>, <0.5,1,0.5>            texture {VgrTex}}          // main CRS body

//corner box cutouts
         box {<0.6,1.1,-0.6>, <0.25,0.75,-0.25>     texture {VgrTex}}          // front left
         box {<-0.6,1.1,-0.6>, <-0.25,0.75,-0.25>   texture {VgrTex}}          // back left
         box {<-0.6,1.1,0.375>, <-0.25,0.75,0.125>  texture {VgrTex}}          // back middle-right
         box {<-0.125,1.1,0.6>, <0.125,0.75,0.25>   texture {VgrTex}}          // right middle

//front panels
         box {<0.45, 0.4, -0.4>, <0.55,0.6,0.4>     texture {VgrTex}}          // front middle
         box {<0.45, 0.1, -0.4>, <0.55,0.3,0.4>     texture {VgrTex}}          // front bottom
            }// end CRS box difference

//cylinders from cutouts
cylinder {<0.25,0.75,-0.25>, <0.5,1,-0.5>, 0.125     texture {VgrTex}}         // front left
cylinder {<-0.5,1,-0.5>, <-0.25,0.75,-0.25>,0.125    texture {VgrTex}}         // back left
cylinder {<-1,0.875,0.25>, <-0.25,0.875,0.25>, 0.125 texture {VgrTex}}         // back middle-right
cylinder {<0,0.875,0.25>, <0,0.875,0.75>, 0.125      texture {VgrTex}}         // right middle

//cross-cylinders
cylinder {<0.3,1,-0.7>, <0.7,1,-0.3>, 0.125            texture {VgrTex}}       // front left crossbar
cylinder {<-0.3,1,-0.7>, <-0.7,1,-0.3>,0.125           texture {VgrTex}}       // back left crossbar
cylinder {<-0.75,0.875,0.6>, <-0.75,0.875,-0.1>, 0.125 texture {VgrTex}}       // back middle-right crossbar
cylinder {<0,0.875,0.5>, <0.125,1.25,0.5>, 0.125       texture {VgrTex}}       // right middle angled cylinder
} // end CRS union


//DRAW CRS EXPERIMENT
object {CRS scale 0.4 rotate <0,180,0> translate <-4.3,2.15, 0>}




//-------------PLS EXPERIMENT (Plasma)----------
//This is the hexagonal-ish object on the box two boom segments out from the CRS cube,
//on the top of the camboom.

#declare PLS =
union
{
//PLS Base (hexagonal prism)
prism {
  linear_sweep
  linear_spline
  0,        // height 1
  0.21,        // height 2
  7, // number of points
  <1,0>,
  <0.5, 0.8660254038>,
  <-0.5, 0.8660254038>,
  <-1,0>,
  <-0.5, -0.8660254038>,
  <0.5, -0.8660254038>,
  <1,0>
  texture {VgrTex}
  clipped_by {plane {x,0.866}}
       } // end hexagonal prism

//PLS Top
//cone clipped by rotated hexagonal base, to simulate bits on top (see VGR homepage)
difference {
           cone {<0,0,0>, 2.1, <0,0.4,0>, 0.1 texture {VgrTex}}
           prism
                {linear_sweep
                linear_spline
                0,        // height 1
                0.5,        // height 2
                7, // number of points
                <1,0>,
                <0.5, 0.8660254038>,
                <-0.5, 0.8660254038>,
                <-1,0>,
                <-0.5, -0.8660254038>,
                <0.5, -0.8660254038>,
                <1,0>
                inverse
                texture {VgrTex}
                rotate <0,30,0>
                } //end prism
          } // end PLS Top difference


//PLS Sensor
difference {
cylinder {<1,0,0>, <1.2,0,0>,   0.25   texture {VgrTex} translate <0,0.2,0>}      //actual sensor
cylinder {<0.9,0,0>, <1.3,0,0>, 0.035  texture {VgrTex} translate <0,0.2,0>}      //hole in middle of cylinder
           }//end PLS Sensor difference

//(bottom) connector to PLS Body
box {<1,0,-0.15>, <0.7,0.25,0.15> texture {VgrTex}}


//120 degree crossbars over top of PLS
box {<1,-0.015,-0.075>, <0.1,0.015,0.075>    texture {VgrTex} rotate <0,0,0>   translate <0,0.42,0>} //top cylinder linker
box {<0.66,-0.015,-0.075>, <0.1,0.015,0.075> texture {VgrTex} rotate <0,0,-10> rotate <0,240,0> translate <0,0.42,0>}
box {<0.66,-0.015,-0.075>, <0.1,0.015,0.075> texture {VgrTex} rotate <0,0,-10> rotate <0,120,0> translate <0,0.42,0>}
} // end PLS union


//DRAW PLS OBJECT
object {PLS rotate <0,-90,0> scale 0.4 translate <-5.5,2.25,0>}




//---------------------LECP EXPERIMENT (under CamBoom)---------------------
//This is the angled cube with widgets attached, suspended from the underside of the
//camera boom beneath the CRS box.

#declare LECP =
union
{
//LECP main box
box {<-0.7,-0.5,-0.5>, <0,0.5,0.5> texture {VgrTex}}

//connecting cylinder
cylinder {<0,0,0>, <0.2,0,0>, 0.5  texture {VgrTex}}

//LECP Sensors
union {
//LECP sensor box
      box {<0.2,0.353,-0.353>, <0.9,0.-0.353,0.353> texture {VgrTex}}

//LECP sensors (cylinders)
      cylinder {<0.375,0,0>, <0.375,0.5,0>, 0.15 texture {VgrTex}}
      cylinder {<0.7,0,0>, <0.7,0.5,0>, 0.15 texture {VgrTex}}

//LECP Terminator (sphere)
      sphere {<0.9, 0,0>, 0.3 texture {VgrTex}}
      cylinder {<0.9, 0, 0>, <1.25,0,0>, 0.035 texture {VgrTex}}

//rotate <x,0,0>              // You can theoretically rotate the sensor box round the x-axis with this!
       } //end LECP Sensor Union

rotate <-45,0,0>              // This rotates the whole LECP for placement under the CamBoom
rotate <0,180,0>              // this rotates LECP so that the sphere end points to the Scan Platform end.
} //end LECP union


//DRAW LECP OBJECT
object {LECP scale 0.4 translate <-4.44,1.1,0>}








//----------------------------------------------------------------------
//------------------------------SCAN PLATFORM---------------------------
//----------------------------------------------------------------------
//The Scan Platform is the large object suspended from the end of the
//camera boom, containing most of the the cameras and sensors (the ones that have to track
//targets. The orientation of the Scan Platform can be changed using the yrot and xrot
//parameters described earlier. The front of the Scan Platform is here defined as the
//direction that the reflective Copper part of IRIS faces.

//DECLARE SCANPLATFORM UNION
#declare scanplatform =
union {



//----------THE ACTUAL SCAN PLATFORM------------
//SUPPORT BOXES (from nearest body to furthest)
      box {<0.3,-0.25,-0.3>, <0.5, 0.3, 0.3>            texture {VgrTex}}       //Camera support box
      cylinder { <0.3, 0, 0>, <-0.3, 0, 0>,  0.25       texture {VgrTex}}       //SCANPLAT ROTATIONAL AXIS (x)
      box {<0.2,-1,-0.3>, <0.3, 0.3, 0.6>               texture {VgrTex}        //angled long box (top bit)
      clipped_by {plane {y , 0.3}  rotate <135,0,0>     translate <0,0,0.5>}}   //angled long box (sloped bit)
      box {<-0.4, 0.3, 0.3>, <-0.07,-0.55,-0.3>         texture {VgrTex}}       // big box above IRIS
      box {<-0.4,-0.2,-0.3>, <-0.6, 0.4, 0.5>           texture {VgrTex}}       //UVS Support box




//-----------------------------------------------
//WIDE ANGLE IMAGING CAMERA
//Shiny object on top left of the Scan Platform as you're looking at it from the front.

union {
//WA Cam support box (on top of main Camera Support Box)
      box {<0.35,0.3,0.3>, <0.45, 0.6, 0>          texture {Chrome_Texture}}

//WA Cam struts from WA Cam support box.
      box {<0.4,0.475,0.3>, <0.55, 0.45, 0>        texture {Chrome_Texture}}
      box {<0.4,0.35,0.3>, <0.55, 0.325, 0>        texture {Chrome_Texture}}

//WA Cam electronics box (rear of camera)
      box {<0.4,0.475,0.15>, <0.55, 0.325, 0>        texture {Chrome_Texture}
      clipped_by {cylinder {<0.55, 0.4, 0>, <0.55, 0.4, 0.3>,  0.05 inverse}}}   // so you don't see it inside WA Cam.

//WA Cam cylindrical body
difference
         {
    cylinder { <0.55, 0.4, 0>, <0.55, 0.4, 0.3>,  0.05}
    cylinder { <0.55, 0.4, 0.15>, <0.55, 0.4, 0.31>,  0.04}
    texture {VgrTex}
         }// end WA Cam body difference

//WA Camera Lens
    cylinder {<0.55, 0.4, 0.16>, <0.55, 0.4, 0.2>,  0.04  texture {T_Glass1}}
      }// end WA Cam union




//-----------------------------------------------
//NARROW ANGLE IMAGING CAMERA
//Long tube on the left/top side of the Scan Platform, below the Wide Angle Camera.

union {
//Camera electronics box (at rear of camera)
      box {<0.5,0.03,-0.3>, <0.72, 0.27, -0.1>          texture {VgrTex}}

//Camera Lens
    cylinder {<0.6, 0.15, -0.1>, <0.6, 0.15, -0.05>,  0.09  texture {T_Glass1}}

//Narrow Angle Camera Body
difference
    {
    cylinder {<0.6, 0.15, -0.3>, <0.6, 0.15, 0.4>,   0.1}
    cylinder {<0.6, 0.15, -0.3>, <0.6, 0.15, 0.42>,  0.09}
    texture {VgrTex}
    }// end NA Cam body difference

//Sunshield
difference
   {
    cylinder {<0.6, 0.15, 0.4>, <0.6, 0.15, 0.6>,    0.13}
    cylinder {<0.6, 0.15, 0.39>, <0.6, 0.15, 0.62>,  0.09}    // completely hollows out sunshield
    texture {VgrTex}
   }//end NA Cam Sunshield difference
      }//end NA Cam Union




//-----------------------------------------------
//PHOTOPOLARIMETER (PPS)
//Short tube beneath the Narrow Angle camera on the left side of the Scan Platform.
//(PPS body is hollow cylinder)

difference
    {
    cylinder {<0.575, -0.1, -0.3>, <0.575, -0.1, 0.05>,  0.075}
    cylinder {<0.575, -0.1, -0.3>, <0.575, -0.1, 0.07>,  0.065}
    texture {VgrTex}
    }// end PPS difference





//-----------------------------------------------
//IRIS
//Big hollow cylindrical object on the lower right of the Scan Platform, with the shiny Copper disc face.

union {
// hollow black cylinder (IRIS body)
difference
    {
    cylinder {<-0.3, -0.75, 0.3>, <-0.3, -0.75, 0.80>,  0.45}
    cylinder {<-0.3, -0.75, 0.3>, <-0.3, -0.75, 0.85>,  0.4 }
    texture {VgrTex}
    }//end IRIS Body difference

// shiny reflective surface inside
    cylinder {<-0.3, -0.75, 0.31>, <-0.3, -0.75, 0.35>,  0.4  texture {Copper_Texture finish {reflection 1}}}

// central IRIS antenna
    cylinder {<-0.3, -0.75, 0.3>, <-0.3, -0.75, 1>,      0.1  texture {VgrTex}}       //antenna
    cylinder { <-0.3, -0.75, 0.75>, <-0.3, -0.75, 0.85>, 0.12 texture {VgrTex}}       //antenna ring

// IRIS Electronics (at back of IRIS)
    box {<-0.6, -0.65, 0.3>, <-0.1,-0.55,-0.15>               texture {VgrTex}}       //on camboom support above IRIS
    cylinder {<-0.3, -0.75, 0.3>, <-0.3, -0.75, -0.3>,  0.1   texture {VgrTex}}
} // End IRIS union





//-----------------------------------------------
//UV SPECTROMETER (UVS)
//Long box widget on the upper right side of the Scan Platform, with the protruding hollow front.

union
     {
      box {<0.075,0.05, 0>, <-0.075, 0, 0.7>        texture {VgrTex}}                //thin base
      box {<0.075,0.05, 0>, <-0.075, 0.2, 0.01>     texture {VgrTex}}                //back panel

//front panel with hole in it
difference {
            box {<0.075,0.05, 0.69>, <-0.075, 0.2, 0.7>   texture {VgrTex}}          //front panel
            box {<0.05,0.055, 0.6>, <-0.05, 0.12, 0.9>    texture {VgrTex}}          //hole
           }//end front panel difference

//UVS chassis
difference {
//outer box
           box {<0.075,0.05, 0>, <-0.075, 0.15, 0.7> inverse texture {VgrTex}}       //end outer box

//inner hollow box
           box {<0.05,0.055, 0>, <-0.05, 0.12, 0.8> clipped_by {plane {y, 0.125 rotate <30,0,0> translate <0,0,0.66>}}
           texture {VgrTex}} //end inner hollow box
           }//end UVS chassis difference

//(stopgap to cover up slope on front of outer box)
box {<0.075,0.12, 0.6>, <-0.075, 0.15, 0.7> texture {VgrTex}}

//UVS detector array cylinder
cylinder
        {<0,0,0> <0,0,0.4> 0.05 texture {VgrTex} rotate <-17,0,0> translate <0,0.1,0.015>
          clipped_by {plane {y,0.12 inverse}}          // so you can't see it if you look inside the hollow box
        }//end UVS detector array cylinder

      translate <-0.675,0.175,-0.2>                   // moves whole UVS to outer edge of scan platform
}//end UVS union



}// END SCANPLATFORM UNION






//DECLARE WHOLE SCANPLATFORM + CAMBOON OBJECT (SCANBOOM)
#declare scanboom =
union
{
    object {camboom
               rotate <0,0,180>        // flips round z-axis (LEAVE THIS AS IT IS!!!!)
               scale 0.3               // scales it down to appropriate size
               translate <0,1.5,0>     // moves it up towards dish/body
               translate <0,0,3>       // moves it out from dish/body towards scan platform
               rotate <0,-90,0>        // rotates the whole boom around to proper orientation.
               texture {VgrTex}
            }//end camboom object

    object {scanplatform


//--------------SCAN PLATFORM X-AXIS ROTATION SETTER (FOR ANIMATIONS ETC)----------------------------------------
        rotate <xrot,0,0>           // declare xrot in  POV scene file to rotate scanplatform only around x-axis!
//--------------SCAN PLATFORM X-AXIS ROTATION SETTER (FOR ANIMATIONS ETC)----------------------------------------


//--------------SCAN PLATFORM Y-AXIS ROTATION SETTER (FOR ANIMATIONS ETC)----------------------------------------
        rotate <0,yrot,0>           // declare yrot in POV scene file to rotate scanplatform around camboom strut
//--------------SCAN PLATFORM Y-AXIS ROTATION SETTER (FOR ANIMATIONS ETC)----------------------------------------

            translate <-7, 0, 0>}

}//end scanboom (whole scan platform + camboom) union



//DRAW CAMERA BOOM AND SCAN PLATFORM (SCANBOOM) OBJECT
object {scanboom
       translate <0,0.5,0>     // moves the whole thing up
       translate <0.5,0,0>     // moves the whole thing nearer body
       }// end scanboom object






//SCALE WHOLE VOYAGER OBJECT DOWN TO 1:1 SCALING.
scale 0.622            //This scales Voyager down so that 1 POV unit = 1 metre.
                       // Unscaled, the dish is 2.895 units in radius. The actual Voyager dish is
                       // 1.8 metres in radius (6 ft), so the scale factor to scale it to 1.8 units is 0.622.

scale 0.001            //This scales Voyager down further (cumulative) so that 1 POV unit = 1 kilometre,
                       // so that it is scaled properly in planetary fly-by scenes with the same scale.
                       // At this scale, the dish is 0.0018 units (km) across.

}// end Voyager union
