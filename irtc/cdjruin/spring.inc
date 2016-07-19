/*****

           Creator: Ronald L. Parker
      Date Created: April 11, 1996
   Objects defined: Spring, SpringLength
       POV Version: 3.0 beta 6


   *** ABOUT THE SPRING

   Units are whatever you want.  The spring starts at the origin and extends
   along the Y axis for approximately SpringLength units (a slight amount of
   overhang, less than or equal to WireRadius, can be expected at each end.)

   *** ABOUT THE VARIABLES

   WireRadius  - the radius of the wire the spring is made from.  Default .5.
   CoilRadius  - the radius of the spring coil (to the center of the wire.)
                 Default 3.
   CoilSpacing - the space between centers on the coils.  Increase to stretch.
                 Default 1.8
   Coils       - the number of coils on the spring.

   *** NOTES

   If you stretch the spring too far, it falls apart.  Experiment to find out
   how far "too far" is.  It varies depending on the variables you specify.


*****/

#ifndef (WireRadius)
  #declare WireRadius = .5;
  #end

#ifndef (CoilRadius)
  #declare CoilRadius = 3;
  #end

#ifndef (CoilSpacing)
  #declare CoilSpacing = 1.8;
  #end

#ifndef (Coils)
  #declare Coils=10;
  #end

#declare Spring_Segment=intersection {
    torus {
      CoilRadius, WireRadius
      }
    plane {
      -z, CoilRadius/100
      }
    plane {
      -x, CoilRadius/100
      }
    rotate < degrees( -atan2(  CoilSpacing/8, CoilRadius )), 0, degrees( -atan2(  CoilSpacing/8, CoilRadius )) >
    }

#declare Spring_Round = union {

  object {Spring_Segment}
  object {Spring_Segment translate ( .25 * CoilSpacing * y ) rotate (  -90 * y ) }
  object {Spring_Segment translate ( .50 * CoilSpacing * y ) rotate ( -180 * y ) }
  object {Spring_Segment translate ( .75 * CoilSpacing * y ) rotate ( -270 * y ) }
  }

#declare SpringLength=Coils*CoilSpacing;

#declare Spring = union {
  #declare i = 0;
  #while ( i < Coils )
    object { Spring_Round translate CoilSpacing * i * y }
    #declare i = i + 1;
    #end
  }

