#include "Stars.inc"


#declare Earth=union {
  sphere {
    0,1
    pigment {
      image_map {
        png "EarthMap.png"
        map_type spherical
      }
      scale <-1,1,1>
      rotate x*90
    }
    finish {ambient 1 diffuse 0}
  }

  cylinder {
    0,x*2,0.1
    pigment {color rgb x}
  }

  cylinder {
    0,y*2,0.1
    pigment {color rgb y}
  }

  cylinder {
    0,z*2,0.1
    pigment {color rgb z}
  }
}

object {Earth}


//From WCS Paper I:
//
//Note that integer pixel numbers refer to the center of the pixel
//in each axis, so that, for example, the first pixel runs from pixel
//number 0.5 to pixel number 1.5 on every axis.
//
//From WCS Paper II section 7.4.1, example 1 (figure 36)
//
//A satellite 2230 km immediately above Cairo aims its dig-
//ital camera directly towards Athens and adjusts the orientation
//and focal length to include Cairo in the field near the bottom
//edge  of  the  frame.  The  2048 x 2048  pixel  CCD  detector
//array employed by the camera is centered on its optical axis
//so Athens is at pixel coordinate (1024.5,1024.5). Cairo – at the
//satellite's nadir – is later found to be at (681.67,60.12). The
//task is to overlay a terrestrial coordinate grid on this image.
#declare AthensFITSx=1024.5; //On the border between pixel 1024 and 1025
#declare AthensFITSy=1024.5; 
#declare CairoFITSx=681.67;
#declare CairoFITSy=60.12;
PrintNumber("CairoGimpx: ",CairoFITSx-0.5)
PrintNumber("CairoGimpy: ",2048.5-CairoFITSy)

//...
//The satellite altitude of 2230 km is 0.350 Earth radii...
#declare r=1.350;
//...
//Determination of \gamma requires knowledge of the coordinates
//of  Cairo  (31.15 E,30.03 N)  and  Athens  (23.44 E,38.00 N).
#declare CairoLat=radians(30.03);
#declare CairoLon=radians(31.15);
#declare CairoPos=<cos(CairoLat)*cos(CairoLon),cos(CairoLat)*sin(CairoLon),sin(CairoLat)>;
#declare AthensLat=radians(38.00);
#declare AthensLon=radians(23.44);
#declare AthensPos=<cos(AthensLat)*cos(AthensLon),cos(AthensLat)*sin(AthensLon),sin(AthensLat)>;

#declare AngularDist=vangle(CairoPos,AthensPos);
PrintNumber("AngularDist: ",degrees(AngularDist))
//The Kwan Hypertext Library says that the following is a tool of Satan. We are
//going to use it anyway. Point 1 is Cairo, point 2 is Athens
#declare Bearing=atan2(sin(AthensLon-CairoLon),cos(CairoLat)*tan(AthensLat)-sin(CairoLat)*cos(AthensLon-CairoLon));
PrintNumber("Bearing: ",degrees(Bearing))

sphere {
  CairoPos,0.0002
  pigment {color rgb <1,1,0>}
  finish {ambient 1 diffuse 0}
}

sphere {
  AthensPos,0.0002
  pigment {color rgb <0,1,1>}
  finish {ambient 1 diffuse 0}
}

camera {
  up y
  right -x
  direction z/0.969377182
  sky <1.44,0,1>
  location r*CairoPos
  look_at AthensPos
  
}

  


