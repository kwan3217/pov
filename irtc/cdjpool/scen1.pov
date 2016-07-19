//intro.pov
//Render with
//+fn +kf1 +kff200 -ul

global_settings {max_trace_level 10}

#include "colors.inc"
#include "textures.inc"
//#include "mstatevec.inc"
//#declare UseTransparentWalls=0;
#include "pooltabl.inc"

#declare UseShuttle=1;
//#declare ShuttleOfs=z*(exp((1-clock))-1)*4;
#declare InternalBrightness=min(8-clock,1);
#include "station.inc"
#include "state1.inc"

#declare ScaleFac=0.03;  
#declare TransFac=CenterPoolModule;
#declare EarthPos=<0,0,0>;


/*
text {
  ttf "arial.ttf"
  concat("Clock=",str(clock,1,3))
  0.1,0
  scale 2
  translate <WallX[0],Floor[1]-1.5,WallZ[0]>
  pigment {color Red}
  no_shadow
} 
*/

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
  rotate y*120
  rotate y*(30+clock*8)
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
    #declare I=I+1;
  #end
  
  box {
    <-2,0,-1>,<2,-0.1,1>
    pigment {
      image_map {
        gif "3dpool.gif" // the file to read (iff/gif/tga/png/sys)
        map_type 0 // 0=planar, 1=spherical, 2=cylindrical, 5=torus
 //       interpolate 0 // 0=none, 1=linear, 2=bilinear, 4=normalized distance
      }
      rotate x*90
      translate <-1/2,0,-1/2>
      scale <4,1,2>
    }
    scale 25
    translate -y*60
  }
  
  object {PoolTable}
  #declare CuePointAt=AimPoint;
  #declare CuePullBack=5;
  #include "poolcue.inc"
  object {PoolCue}

  scale ScaleFac
  translate TransFac
}  

//Intro Camera  
/*
camera {    
#if(clock<3)
  location <0,65,0>*ScaleFac+TransFac
#else
  location vrotate(<0,65,0>,-x*(clock-3)*90/5+y*(clock-3)*15/5)*ScaleFac+TransFac
#end
  look_at <0,0,0>*ScaleFac+TransFac 
#if(clock<3) 
  angle 42
#else   
  angle 42+(clock-3)*12/5
#end
} 
*/
                
//Scene 1 Camera  
#declare A=3.6888794541139;
#declare B=2.995732273554;
camera {   
  #declare KlockA=1-clock;
  #declare KlockB=(0.75-clock)*4/3;
  #if(clock<0.75)
    #declare L=vrotate(<0,2.5*exp(KlockB*B)-2.5,-2.5*exp(KlockA*A)>,<0,-360*KlockB,0>);
    location L+CenterPoolModule
    look_at CenterPoolModule+z*20*sin(clock*pi)
  #else
    #declare L=<0,0,-2.5*exp(KlockA*A)>;
    location L+CenterPoolModule
    look_at CenterPoolModule
  #end               
  DispReal("KlockA",KlockA)
  DispReal("KlockB",KlockB)
  DispVec("Camera Location",L) 
//  angle 45
}                

               
//Zoomout Camera
/*
camera {
  location CenterPoolModule-z*2+<0,0,-exp(min(clock,17))*0.1>
  look_at CenterPoolModule
}
*/

/*                
//Floating Camera        
camera {
  location CenterPoolModule-z*3
  look_at CenterPoolModule
}
*/
