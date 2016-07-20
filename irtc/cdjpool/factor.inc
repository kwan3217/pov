//Common code factored out of all scenes
global_settings {assumed_gamma 2.2 max_trace_level 10}

#include "colors.inc"
#include "textures.inc"
#include "pooltabl.inc"

#macro Mechanic(OrigVec)
#if(clock<0)
  #include OrigVec
#else
  #include "mechanic.inc"
#end
#end

#macro Earth(yrot)
sphere {
  <0,0,0>,1
  texture {
    pigment {
      image_map {
        jpeg "earthimg.jpg"
        map_type 1
        interpolate 4
      }
    }
    normal {
      bump_map {
        gif "earthbump.gif" // the file to read (iff/gif/tga/png/sys)
        map_type 1 // 0=planar, 1=spherical, 2=cylindrical, 5=torus
//        interpolate 0 // 0=none, 1=linear, 2=bilinear, 4=normalized distance
        bump_size 3 // 0...3
      }
    }
  }
  rotate y*yrot
  rotate -x*15
  rotate EarthPos*50 //This is for when Earth is knocked away in the last scene
  translate EarthPos+(1.5*z)
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
  rotate y*yrot
  rotate -x*15
  rotate EarthPos*50
  translate EarthPos+(1.5*z)
  scale 637814
}
#end

#macro UseStation(Credits)

#if(clock<15)
object {
  Station
  rotate -x*15*Credits
  rotate -y*30*Credits
  scale 1-Credits*0.9 // we want Credits?0.1:1, but no ?: operator in POV-Ray
}  
#end

#end

#macro PoolGame()
#declare ScaleFac=0.03;  
#declare TransFac=CenterPoolModule;
#declare EarthPos=<0,0,0>;
Earth(30+clock)

UseStation(0)

light_source {
  <10000000,0,-10000000>
  color <1,1,1>*InternalBrightness
}

union {
  #declare I=0;
  #declare Vectors=0;
  #while(I<dimension_size(BallPos,1))
    #if(BallFree[I])
      #declare BallNumber=I;
      #include "poolball.inc"
      object {
        Ball
        rotate <BallPos[I].y,BallPos[1].z,BallPos[1].x>*57
        translate BallPos[I]
      }
      #if(Vectors=1)
        #if(vlength(BallSpd[I])>0)
          cylinder {
            BallPos[I]+vnormalize(BallSpd[I]),BallPos[I]+BallSpd[I],0.1
            pigment {color BallColor}
          }
          cone {
            BallPos[I]+BallSpd[I]+vnormalize(BallSpd[I]),0.0, BallPos[I]+BallSpd[I],0.2
            pigment {color BallColor}
          }
        #end
      #end
    #end
    #declare I=I+1;
  #end
  
  box {
    <-2,0,-1>,<2,-0.1,1>
    pigment {
      image_map {
        gif "3dpool.gif" // the file to read (iff/gif/tga/png/sys)
        map_type 0 // 0=planar, 1=spherical, 2=cylindrical, 5=torus
//        interpolate 0 // 0=none, 1=linear, 2=bilinear, 4=normalized distance
      }
      rotate x*90
      translate <-1/2,0,-1/2>
      scale <4,1,2>
    }
    scale 25
    translate -y*60
  }
  
  object {PoolTable}
  object {PoolCue}

  scale ScaleFac
  translate TransFac
}  
#end


