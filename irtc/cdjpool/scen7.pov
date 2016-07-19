//intro.pov
//Render with
//+fn +kf11.8 +kff100 -ul +j0 +am2 +kc +ki1.8

#include "colors.inc"
#include "textures.inc"
//#declare UseTransparentWalls=0;
#include "pooltabl.inc"

//#declare UseShuttle=0;
#declare SimpleStation=1;
#declare InternalBrightness=1;
#declare AstronautRotate=<0,0,clock*2>;
#include "station.inc"
#if(clock<8)
#declare MClock=clock;
#end
#declare MaxIters=20; 
#declare ScaleFac=0.03;  
#declare TransFac=CenterPoolModule;
#declare EarthPos=<0,0,0>;

#declare OrigVec="state6.inc"
#if(clock<0)
  #include OrigVec
#else
  #include "mechanic.inc"
#end
#declare CuePointAt=AimPoint;
#declare CuePullBack=max(-clock*5,0);
#warning concat("CuePullBack: ",str(CuePullBack,0,5),"\n")
#include "poolcue.inc"

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
        interpolate 0 // 0=none, 1=linear, 2=bilinear, 4=normalized distance
        bump_size 3 // 0...3
      }
    }
  }
  rotate y*(30+clock)
  rotate -x*15
  rotate EarthPos*50
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
  rotate y*(30+clock*0.9)
  rotate -x*15
  rotate EarthPos*50
  translate EarthPos+(1.5*z)
  scale 637814
}

light_source {
  <10000000,0,-10000000>
  color <1,1,1>*InternalBrightness
}

#if(clock<15)
object {
  Station
  translate <0,0,0>
}  
#end

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

//Scene 2 Camera  
/*
camera {    
  location vrotate(<0,65,0>,-y*(clock)*30/8+15)*ScaleFac+TransFac
  look_at <0,0,0>*ScaleFac+TransFac 
  angle 42+(clock)*12/8
}
*/
                
//Zoomout Camera
/*
camera {
  location CenterPoolModule-z*2+<0,0,-exp(min(clock,17))*0.1>
  look_at CenterPoolModule
}
*/
 
                
//Floating Camera        
camera {                                                   
  //location CenterPoolModule-y*1
//  #if(clock<0)
    location CenterPoolModule+<0,1,-1.6>
    look_at (CenterPoolModule)
//  #else
//    location CenterPoolModule+<0.9,0.5,0.99>
//    look_at (BallPos[TargetBall])*ScaleFac+TransFac
//  #end
//  fisheye
//  angle 360
//  angle 60
}

#warning concat("Clock: ",str(clock,0,5),"\n")
