#version unofficial Megapov 1.22;

#include "KwanMath.inc"

global_settings {
  right_handed
  charset utf8
}

#declare MoveTime=array[4] {5,5,8,2}

#local I=0;
#declare TotalTime=0;
#while(I<dimension_size(MoveTime,1))
  #declare TotalTime=TotalTime+MoveTime[I];
  #local I=I+1;
#end
PrintNumber("TotalTime: ",TotalTime)

#declare Time=Linterp(0,0,1,TotalTime,clock);
#declare Scene=0;
#declare SceneStart=0;
#declare SceneEnd=MoveTime[0];
#while(Time>=MoveTime[Scene]+SceneStart)
  #declare SceneStart=SceneStart+MoveTime[Scene];
  #declare Scene=Scene+1;
  #declare SceneEnd=SceneStart+MoveTime[Scene];
#end
#declare SceneClock=Linterp(SceneStart,0,SceneEnd,1,Time);
#declare SceneTime=Time-SceneStart;
#declare squared=chr(178);

#macro FadeIn2(Color,FadeClock)
  (Color+Linterp(0,<1,1,1,1>-Color,1,<0,0,0,0>,FadeClock))
#end

#macro FadeOut2(Color,FadeClock)
  (Color+Linterp(1,<1,1,1,1>-Color,0,<0,0,0,0>,FadeClock))
#end

#macro FadeIn(Color,FadeClock)
  pigment {color rgbf FadeIn2(Color,FadeClock)}
#end

#macro FadeOut(Color,FadeClock)
  pigment {color rgbf FadeOut2(Color,FadeClock)}
#end

#declare Background=plane {
  z,0
  pigment {checker color rgb 1 color rgb 0.75}
}

#macro Trapterp(X0,X1,X2,X3,Y0,Y1,X) 
  #if(X<X2)
    #local result=BLinterp(X0,Y0,X1,Y1,X);
  #else 
    #local result=BLinterp(X2,Y1,X3,Y0,X);
  #end
  (result)
#end

#declare Loc0=<0,0,0>/2;
#declare Scale0=7;
#declare Loc1=Loc0;
#declare Scale1=Scale0;
#declare Loc2=Loc1;
#declare Scale2=Scale1;
#declare Thick=0.025;

#switch(Scene)
  #case(0)
    #declare Loc=Loc0;
    #declare Scale=Scale0;
    #declare Background=plane {
      z,0
      FadeIn(<1,1,1,0>,BLinterp(0,0,1,1,SceneTime))
    }
    text {
      ttf "verdana.ttf" 
      "Kwanometry" 1 0
      h_align_center
      rotate y*180
      rotate -z*90
      translate <0,0,0.001>
      FadeIn(<0.1,0.1,0.1,0>,Trapterp(0.5,1.5,4,5,0,1,SceneTime))
    }
    text {
      ttf "verdana.ttf" 
      concat(chr(169)," 2008 Kwan Heavy Industries") 1 0
      h_align_center
      scale 0.5
      rotate y*180
      rotate -z*90
      translate <0,-2,0.001>
      FadeIn(<0.1,0.1,0.1,0>,Trapterp(1,2,4,5,0,1,SceneTime))
    }
    #break
  #case(1)
    #declare Loc=Loc1;
    #declare Scale=Scale1;
    #declare Background=plane {
      z,0
      pigment {rgb 1}
    }
    text {
      ttf "verdana.ttf" 
      "Coordinates" 1 0
      h_align_center
      rotate y*180
      rotate -z*90
      translate <0,0,0.001>
      FadeIn(<0.1,0.1,0.1,0>,Trapterp(0,1,4,5,0,1,SceneTime))
    }
  #case(2)
    #declare Loc=Loc2;
    #declare Scale=Scale2;
    #declare Background=plane {
      z,0
      pigment {rgb 1}
    }
    cylinder {
      <-8,0,0>,<Linterp(0,-6.5,1,6.5,SceneClock),0,0>,Thick
      pigment {color rgb <0.1,0.1,0.1>}
    }
    #break
  #case(3)
    #declare Loc=Loc2;
    #declare Scale=Scale2;
    #declare Background=plane {
      z,0
      pigment {rgb 1}
    }
    #local I=-6;
    cylinder {
      <-7,0,0>,<7,0,0>,Thick
      pigment {color rgb <0.1,0.1,0.1>}
    }
    #while(I<Linterp(0,-7,1,7,SceneClock))
      cylinder {
        <I,-0.1-0.1*(I=0),0>,<I,0.1+0.1*(I=0),0>,0.05
        pigment {color rgb <0.1,0.1,0.1>}
      }
      #local I=I+1;
    #end
    #break
#end

object {Background}

camera {
  orthographic
  up z*Scale
  right x*16/9*Scale
  location Loc+z*10
  look_at Loc
  sky y
}

light_source {
  <20,20,20>*1000
  color rgb 1.5
  shadowless
}






