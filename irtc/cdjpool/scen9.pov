//Render using
//+fn +kf21 +kff200 -ul
#include "colors.inc"
#include "textures.inc" 

#if(clock<8.75)
#declare UseShuttle=1
#end

#include "station.inc"

#include "pooltabl.inc"

//Floors and ceilings
#declare Floor=array[2] {-1800,1800}

//Walls
#declare WallX=array[2] {-3600,3600}
#declare WallZ=array[2] {-1800,1800}
                      
#declare AirResist=0;
#declare OrigVec="earthvec.inc"
#include "mechanic.inc"

#declare star_count = 2000;
#declare star_scale = .5;
//#include "GALAXY.SF"

#declare galaxy_seed = 1;
#declare star_count = 500;
#declare star_type = 3;
#declare star_colour = <1, .9, .7>;
#declare star_scale = 1.5;
//#include "GALAXY.SF"

sphere {
  <0,0,0>,1
  texture {
    pigment {
      image_map {
        tga "earthimg.tga"
        map_type 1
        interpolate 4
      }
    }
    normal {
      bump_map {
        gif "earthbump.gif" // the file to read (iff/gif/tga/png/sys)
        map_type 1 // 0=planar, 1=spherical, 2=cylindrical, 5=torus
        interpolate 0 // 0=none, 1=linear, 2=bilinear, 4=normalized distance
        bump_size 3 // 0...3
      }
    }
  }
  rotate y*(30+clock)
  rotate -x*15
  rotate BallPos[1]*50
  translate BallPos[1]+(1.5*z)
  scale 637814
}

sphere {
  <0,0,0>,1.01
  texture {
    pigment {
      image_map {
        png "cloudmap.png"
        map_type 1
        interpolate 4
      }
    }
  }
  rotate y*(30+clock*0.9)
  rotate -x*15
  rotate BallPos[1]*50
  translate BallPos[1]+(1.5*z)
  scale 637814
}

#if(clock>15)
#declare BallNumber=9;
#include "poolball.inc"
object {
  Ball
  rotate BallPos[1]*10
  translate BallPos[0]+(1.5*z)
  scale 637814
}
#end

light_source {
  <10000000,0,-10000000>
  color <1,1,1>
}

camera {
  location <0,0,-exp(min(clock,17))*0.1>
  look_at <0,0,0>
}                                

#declare CreditClock=clock*2.2; 
#declare CreditScale=exp(clock/5);
    
object {
  #include "credits.inc"
  #translate <0,0,-exp(min(clock,17))*0.1>
}

#if(clock<15)
object {
  Station
  rotate -x*15
  rotate -y*30
  scale 0.1
  translate <0,0,0>
}  
#end

