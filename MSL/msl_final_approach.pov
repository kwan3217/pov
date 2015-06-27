#include "msl_final_approach.inc"
#include "LocLook.inc"

plane {
  z,0
  pigment {checker scale 100}
}

#declare skycrane_start=831;
#declare skycrane_length=7.5; //7.5m bridle, 1m/s
#declare skycrane_speed=1; //7.5m bridle, 1m/s
#declare skycrane_time=skycrane_length/skycrane_speed*24; //Frames in skycrane maneuver
                     
#if(frame_number<skycrane_start)
  #declare skycrane=0;
#else  
#if(frame_number<(skycrane_start+skycrane_time))
  #declare skycrane=skycrane_length*(frame_number-skycrane_start)/skycrane_time;
#else
  #declare skycrane=skycrane_length;
#end
#end

#local R=msl_final_approach[frame_number][0];
#local V=msl_final_approach[frame_number][1];
#local A=msl_final_approach[frame_number][2];        
#if(R.z<skycrane_length+0.5)
  #declare R=<R.x,R.y,skycrane_length+0.5>;
#end

sphere {
  R,1
  pigment {color rgb <0,0,1>}
}

#if(vlength(A)>0)
  cone {
    R-vnormalize(A),0.2,R-vnormalize(A)-A*0.1,0
    pigment {color rgb <1,0.5,0>}
  }
#end

#local dgrid=100;

#local grid=<floor(R.x/dgrid)*dgrid,floor(R.y/dgrid)*dgrid,floor(R.z/dgrid)*dgrid>;

#local I=-5;
#while(I<=5)
  #local J=-5;
  #while(J<=5)
    #local K=-5;
    #while(K<=5) #if(I!=0 & J!=0 & K!=0)
      sphere {
        grid+<I,J,K>*dgrid,1
        pigment {color rgb <1,0,0>}  
        no_shadow
      }
      #end
      #local K=K+1;
    #end
    #local J=J+1;
  #end
  #local I=I+1;
#end

#declare CameraLoc= R+<-20,5,5>;
//#declare CameraLoc=vnormalize(vnormalize(R(frame_number))*50-W(frame_number)*40)*50;
#declare CameraLook=R;
#declare CameraSky=z;

camera {
  up y
  right -x*image_width/image_height
  sky z
  location CameraLoc
  look_at CameraLook
}

light_source {
  <-10,0,5>*1e6
  color rgb <1,1,1>
}

#if(skycrane>0)
  cylinder {
    R,R-<0,0,skycrane>,0.1
    pigment {color rgb <1,1,1>}
  }
  box {
    R-<0,0,skycrane>-<0.5,0.5,0.5>,R-<0,0,skycrane>+<0.5,0.5,0.5>
    pigment {color rgb <1,1,0>}
  }
#end

union {
  union {
    textHud("AGL: ",                     <-16,8.5>,<1,0,0>,0,-1)
    textHudNumber(R.z, "m",<-12,8.5>,<1,0,0>,  -1)

    textHud("Acc: ",                     <-16,7.5>,<1,1,0>,0,-1)
    textHudNumber(vlength(A)/9.80665, "g",<-12,7.5>,<1,1,0>,  -1)
    textHud("Vrel:",                     <11.5,8.5>,<1,1,1>,0,-1)
    textHudNumber(vlength(V), "m/s",<15,8.5>,<1,1,1>,  -1)
    textHud("Fpa: ",                     <11.5,8.0>,<0.5,0.5,0.5>,0,-1)
    #if(abs(R.z)>0)
      textHudNumber(degrees(atan2(R.z,vlength(<R.x,R.y,0>))), "deg",<15,8.0>,<0.5,0.5,0.5>,  -1)
    #end
    textHud("Skycrane: ",                     <11.5,7.5>,<0.5,0.5,0.5>,0,-1)
    textHudNumber(skycrane, "m",<15,7.5>,<0.5,0.5,0.5>,  -1)
//    textHud("AlpT:",                     <11.5,6.5>,BLinterp(1,<0,0,0>,2,<0.5,0.5,0.5>,abs(Dtot)),0,-1)
//    textHudNumber(degrees(AlpT), "deg",<15,6.5>,BLinterp(1,<0,0,0>,2,<0.5,0.5,0.5>,abs(Dtot)),  -1)
    textHud("hd:  ",                     <11.5,7.0>,<1,1,1>,0,-1)
    textHudNumber(V.z, "m/s",<15,7.0>,<1,1,1>,  -1)
    textHud("vh:",                     <11.5,6.0>,<1,1,1>,0,-1)
    textHudNumber(vlength(<V.x,V.y,0>), "m/s",<15,6.0>,<1,1,1>,  -1)
    scale <0.175,0.175,1>
    no_shadow
  }
  LocationLookAt(CameraLoc,CameraLook,CameraSky)
}



