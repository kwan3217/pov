#version unofficial Megapov 1.22;

#include "KwanMath.inc"

global_settings {
  right_handed
  charset utf8
}

#declare A=4;
#declare B=3;
#declare C=sqrt(A*A+B*B);
#declare Thick=1;

#declare MoveTime=array[21] {1,3,1,3,2,2,2,5,2,5,2,5,2,2,2,2,2,0,5,10,3}

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
#while(Time>MoveTime[Scene]+SceneStart)
  #declare SceneStart=SceneStart+MoveTime[Scene];
  #declare Scene=Scene+1;
  #declare SceneEnd=SceneStart+MoveTime[Scene];
#end
#declare SceneClock=Linterp(SceneStart,0,SceneEnd,1,Time);
#declare squared=chr(178);

#if(Scene=19)
  #declare A=4+3*sin(2*pi*SceneClock);
  #declare B=7-A;
#else
  #declare A=4;
  #declare B=3;
#end
#declare C=sqrt(A*A+B*B);
#declare Thick=1;



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

#macro Tri2(EdgeColor)
union {
  intersection {
    plane {
      -z,0
    }
    plane {
      z,1
    }
    plane {
      -x,0
    }
    plane {
      -y,0
    }
    plane {
      <B,A,0>,0
      translate x*A
    }
    bounded_by {
      box {
        <0,0,0>,<A,B,1>
      }
    }
  }
  merge {
    #if(A>0)
      cylinder {
        <0,0,1>,<A,0,1>,0.025
      }
    #end
    #if(B>0)
      cylinder {
        <0,0,1>,<0,B,1>,0.025
      }
    #end
    cylinder {
      <A,0,1>,<0,B,1>,0.025
    }
    sphere {
      <0,0,1>,0.025
    }
    sphere {
      <0,B,1>,0.025
    }
    sphere {
      <A,0,1>,0.025
    }
    pigment {color rgbf EdgeColor}
  }
}
#end

#declare Tri=Tri2(<0.1,0.1,0.1>)

#macro QuadTri2(EdgeColor)
union {
  #local I=0;
  #while(I<4)
    object {
      Tri2(EdgeColor)
      translate <-(A+B)/2,-(A+B)/2,0>
      rotate z*I*90
      translate <(A+B)/2,(A+B)/2,0>
    }
    #local I=I+1;
  #end
}
#end

#declare QuadTri=union {
  #local I=0;
  #while(I<4)
    object {
      Tri
      translate <-(A+B)/2,-(A+B)/2,0>
      rotate z*I*90
      translate <(A+B)/2,(A+B)/2,0>
    }
    #local I=I+1;
  #end
}

plane {
  z,0
  pigment {checker color rgb 1 color rgb 0.75}
}

#declare Loc0Init=<A,B,0>/2;
#declare Scale0Init=(A+B);
#declare Loc0Final=<A+B,A+B,0>/2;
#declare Scale0Final=ceil(2*sqrt(2*pow((A+B)/2,2)));

#declare Loc1=Loc0Final;
#declare Scale1=Scale0Final;

#declare Loc2Init=Loc1;
#declare Scale2Init=Scale1;
#declare Loc2Final=Loc2Init;
#declare Scale2Final=Scale2Init;

#declare Loc3=Loc2Final;
#declare Scale3=Scale2Final;

#declare Loc4=Loc3;
#declare Scale4=Scale3;

#declare Loc5=Loc4;
#declare Scale5=Scale4;

#declare Loc6Init=Loc5;
#declare Scale6Init=Scale5;
#declare Loc6Final=Loc6Init*<2,1,1>+<0.5,0,0>;
#declare Scale6Final=Scale6Init;

#declare Loc7=Loc6Final;
#declare Scale7=Scale6Final;

#declare Loc8=Loc7;
#declare Scale8=Scale7;

#declare Loc9=Loc8;
#declare Scale9=Scale8;

#declare Loc10=Loc9;
#declare Scale10=Scale9;

#declare Loc11=Loc10;
#declare Scale11=Scale10;

#declare Loc12=Loc11;
#declare Scale12=Scale11;

#declare Loc13=Loc12;
#declare Scale13=Scale12;

#switch(Scene)
  #case(0)
    #declare Loc=Loc0Init;
    #declare Scale=Scale0Init;
    text {
      ttf "verdana.ttf" 
      "Dissection Proof" 1 0
      h_align_center
      rotate y*180
      rotate -z*90
      translate <2,2,0.001>
      FadeIn(<0.1,0.1,0.1,0>,SceneClock)
    }
    text {
      ttf "verdana.ttf" 
      "of the Pythagorean Theorem" 1 0
      h_align_center
      scale 0.75
      rotate y*180
      rotate -z*90
      translate <2,1,0.001>
      FadeIn(<0.1,0.1,0.1,0>,SceneClock)
    }
    text {
      ttf "verdana.ttf" 
      concat(chr(169)," 2008 Kwan Heavy Industries") 1 0
      h_align_center
      scale 0.5
      rotate y*180
      rotate -z*90
      translate <2,0,0.001>
      FadeIn(<0.1,0.1,0.1,0>,SceneClock)
    }
    #break
  #case(1)
    #declare Loc=Loc0Init;
    #declare Scale=Scale0Init;
    text {
      ttf "verdana.ttf" 
      "Dissection Proof" 1 0
      h_align_center
      rotate y*180
      rotate -z*90
      translate <2,2,0.001>
      FadeIn(<0.1,0.1,0.1,0>,1)
    }
    text {
      ttf "verdana.ttf" 
      "of the Pythagorean Theorem" 1 0
      h_align_center
      scale 0.75
      rotate y*180
      rotate -z*90
      translate <2,1,0.001>
      FadeIn(<0.1,0.1,0.1,0>,1)
    }
    text {
      ttf "verdana.ttf" 
      concat(chr(169)," 2008 Kwan Heavy Industries") 1 0
      h_align_center
      scale 0.5
      rotate y*180
      rotate -z*90
      translate <2,0,0.001>
      FadeIn(<0.1,0.1,0.1,0>,1)
    }
    #break
  #case(2)
    #declare Loc=Loc0Init;
    #declare Scale=Scale0Init;
    text {
      ttf "verdana.ttf" 
      "Dissection Proof" 1 0
      h_align_center
      rotate y*180
      rotate -z*90
      translate <2,2,0.001>
      FadeOut(<0.1,0.1,0.1,0>,SceneClock)
    }
    text {
      ttf "verdana.ttf" 
      "of the Pythagorean Theorem" 1 0
      h_align_center
      scale 0.75
      rotate y*180
      rotate -z*90
      translate <2,1,0.001>
      FadeOut(<0.1,0.1,0.1,0>,SceneClock)
    }
    text {
      ttf "verdana.ttf" 
      concat(chr(169)," 2008 Kwan Heavy Industries") 1 0
      h_align_center
      scale 0.5
      rotate y*180
      rotate -z*90
      translate <2,0,0.001>
      FadeOut(<0.1,0.1,0.1,0>,SceneClock)
    }
    union {
      Tri2(FadeIn2(<0.1,0.1,0.1>,SceneClock))
      FadeIn(<1,1,0,0>,SceneClock)
    }
    text {
      ttf "verdana.ttf" 
      "1 triangle" 1 0
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <0,-1,1>
      FadeIn(<0.1,0.1,0.1,0>,SceneClock)
    }
    #break
  #case(3)
    #declare Loc=Linterp(0,Loc0Init,1,Loc0Final,SceneClock);
    #declare Scale=Linterp(0,Scale0Init,1,Scale0Final,SceneClock);
    object {
      Tri
      pigment {color rgb <1,1,0>}
    }
    text {
      ttf "verdana.ttf" 
      "1 triangle" 1 0
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <0,-1,1>
      pigment {color rgb <0.1,0.1,0.1>}
    }
    #break
  #case(4)
    #declare Loc=Loc1;
    #declare Scale=Scale1;
    object {
      Tri
      pigment {color rgb <1,1,0>}
    }
    text {
      ttf "verdana.ttf" 
      "1 triangle" 1 0
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <0,-1,1>
      pigment {color rgb <0.1,0.1,0.1>}
    }
    #break
  #case(5)
    #declare Loc=Linterp(0,Loc2Init,1,Loc2Final,SceneClock);
    #declare Scale=Linterp(0,Scale2Init,1,Scale2Final,SceneClock);
    object {
      Tri
      pigment {color rgb <1,1,0>}
    }
    text {
      ttf "verdana.ttf" 
      "1 triangle" 1 0
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <0,-1,1.001>
      FadeOut(<0.1,0.1,0.1,0>,SceneClock)
    }
    text {
      ttf "verdana.ttf" 
      "4 triangles" 1 0
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <0,-1,2.002>
      FadeIn(<0.1,0.1,0.1,0>,SceneClock)
    }
    #if(SceneClock>0) 
      object {
        Tri
        FadeIn(<1,1,0,0>,BLinterp(0/3,0,1/3,1,SceneClock))
        translate <-(A+B)/2,-(A+B)/2,1.001>
        rotate z*Linterp(0,0,1,270,SceneClock)
        translate <(A+B)/2,(A+B)/2,0>
      }
    #end
    #if(SceneClock>1/3) 
      object {
        Tri
        FadeIn(<1,1,0,0>,BLinterp(1/3,0,2/3,1,SceneClock))
        translate <-(A+B)/2,-(A+B)/2,1.001>
        rotate z*Linterp(0,-90,1,180,SceneClock)
        translate <(A+B)/2,(A+B)/2,0>
      }
    #end
    #if(SceneClock>2/3) 
      object {
        Tri
        FadeIn(<1,1,0,0>,BLinterp(2/3,0,3/3,1,SceneClock))
        translate <-(A+B)/2,-(A+B)/2,1.001>
        rotate z*Linterp(0,-180,1,90,SceneClock)
        translate <(A+B)/2,(A+B)/2,0>
      }
    #end
    #break  
  #case(6)
    #declare Loc=Loc3;
    #declare Scale=Scale3;
    object {
      QuadTri
      pigment {color rgb <1,1,0>}
    }
    text {
      ttf "verdana.ttf" 
      "4 triangles" 1 0
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <0,-1,1>
      FadeIn(<0.1,0.1,0.1,0>,1)
    }
    #break
  #case(7)
    #declare Loc=Loc4;
    #declare Scale=Scale4;
    object {
      QuadTri
      pigment {color rgb <1,1,0>}
    }
    box {
      <0,0,0.001>,<A+B,A+B,0.1>
      FadeIn(<0.25,0.25,1,0>,SceneClock)
    }
    text {
      ttf "verdana.ttf" 
      "4 triangles" 1 0
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <0,-1,1.002>
      FadeOut(<0.1,0.1,0.1,0>,SceneClock)
    }
    text {
      ttf "verdana.ttf" 
      concat("4 triangles+c",squared) 1 0
      h_align_right
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B,-1,0.001>
      FadeIn(<0.1,0.1,0.1,0>,SceneClock)
    }
    #break  
  #case(8)
    #declare Loc=Loc5;
    #declare Scale=Scale5;
    object {
      QuadTri
      pigment {color rgb <1,1,0>}
    }
    box {
      <0,0,0>,<A+B,A+B,0.1>
      pigment {color rgb <0.25,0.25,1>}
    }
    text {
      ttf "verdana.ttf" 
      concat("4 triangles+c",squared) 1 0
      h_align_right
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B,-1,0.001>
      FadeIn(<0.1,0.1,0.1,0>,1)
    }
    #break
  #case(9)
    #declare Loc=Linterp(0,Loc6Init,1,Loc6Final,SceneClock);
    #declare Scale=Linterp(0,Scale6Init,1,Scale6Final,SceneClock);
    object {
      QuadTri
      pigment {color rgb <1,1,0>}
    }
    box {
      <0,0,0>,<A+B,A+B,0.1>
      pigment {color rgb <0.25,0.25,1>}
    }
    text {
      ttf "verdana.ttf" 
      concat("4 triangles+c",squared) 1 0
      h_align_right
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B,-1,0.001>
      FadeIn(<0.1,0.1,0.1,0>,1)
    }
    union {
      text {
        ttf "verdana.ttf" 
        concat("4 triangles+c",squared) 1 0
        scale 7/8
        rotate y*180
        rotate -z*90
        translate <0,-1,1.001>
        FadeIn(<0.1,0.1,0.1,0>,SceneClock)
      }
      object {
        QuadTri
        FadeIn(<1,1,0,0>,SceneClock)
      }
      box {
        <0,0,0>,<A+B,A+B,0.1>
        FadeIn(<0.25,0.25,1,0>,SceneClock)
      }
      translate <Linterp(0,0,1,A+B+1,SceneClock),0,1.001>
    }
    #break
  #case(10)
    #declare Loc=Loc7;
    #declare Scale=Scale7;
    object {
      QuadTri
      pigment {color rgb <1,1,0>}
    }
    box {
      <0,0,0>,<A+B,A+B,0.1>
      pigment {color rgb <0.25,0.25,1>}
    }
    text {
      ttf "verdana.ttf" 
      concat("4 triangles+c",squared) 1 0
      h_align_right
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B,-1,0.001>
      FadeIn(<0.1,0.1,0.1,0>,1)
    }
    text {
      ttf "verdana.ttf" 
      "=" 1 0
      h_align_center
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B+0.5,-1,0.001>
      FadeIn(<0.1,0.1,0.1,0>,SceneClock)
    }
    union {
      text {
        ttf "verdana.ttf" 
        concat("4 triangles+c",squared) 1 0
        scale 7/8
        rotate y*180
        rotate -z*90
        translate <0,-1,1.001>
        FadeIn(<0.1,0.1,0.1,0>,1)
      }
      object {
        QuadTri
        FadeIn(<1,1,0,0>,1)
      }
      box {
        <0,0,0>,<A+B,A+B,0.1>
        FadeIn(<0.25,0.25,1,0>,1)
      }
      translate <A+B+1,0,0>
    }
    #break
  #case(11)
    #declare Loc=Loc8;
    #declare Scale=Scale8;
    object {
      QuadTri
      pigment {color rgb <1,1,0>}
    }
    box {
      <0,0,0>,<A+B,A+B,0.1>
      pigment {color rgb <0.25,0.25,1>}
    }
    text {
      ttf "verdana.ttf" 
      "=" 1 0
      h_align_center
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B+0.5,-1,0>
      FadeOut(<0.1,0.1,0.1,0>,0)
    }
    text {
      ttf "verdana.ttf" 
      concat("4 triangles+c",squared) 1 0
      h_align_right
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B,-1,0.001>
      FadeIn(<0.1,0.1,0.1,0>,1)
    }
    union {
      text {
        ttf "verdana.ttf" 
        concat("4 triangles+c",squared) 1 0
        scale 7/8
        rotate y*180
        rotate -z*90
        translate <0,-1,1.001>
        FadeOut(<0.1,0.1,0.1,0>,BLinterp(0,0,0.4,1,SceneClock))
      }
      box {
        <0,0,0>,<A+B,A+B,0.1>
        pigment {color rgb <0.25,0.25,1>}
      }
      object {
        Tri
        pigment {color rgb <1,1,0>}
      }
      object {
        Tri
        pigment {color rgb <1,1,0>}
        translate -<(A+B)/2,(A+B)/2,0>
        rotate z*180
        translate <(A+B)/2,(A+B)/2,0>
        translate BLinterp(0,<0,0,0>,0.4,<-B,-A,0>,SceneClock)
      }
      object {
        Tri
        pigment {color rgb <1,1,0>}
        translate -<(A+B)/2,(A+B)/2,0>
        rotate z*270
        translate <(A+B)/2,(A+B)/2,0>
        translate BLinterp(0.6,<0,0,0>,1.0,<A,0,0>,SceneClock)
      }
      object {
        Tri
        pigment {color rgb <1,1,0>}
        translate -<(A+B)/2,(A+B)/2,0>
        rotate z*90
        translate <(A+B)/2,(A+B)/2,0>
        translate BLinterp(0.6,<0,0,0>,1.0,<0,B,0>,SceneClock)
      }
      translate <A+B+1,0,0>
    }
    #break
  #case(12)
    #declare Loc=Loc8;
    #declare Scale=Scale8;
    object {
      QuadTri
      pigment {color rgb <1,1,0>}
    }
    box {
      <0,0,0>,<A+B,A+B,0.1>
      pigment {color rgb <0.25,0.25,1>}
    }
    text {
      ttf "verdana.ttf" 
      concat("4 triangles+c",squared) 1 0
      h_align_right
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B,-1,0.001>
      FadeIn(<0.1,0.1,0.1,0>,1)
    }
    text {
      ttf "verdana.ttf" 
      "=" 1 0
      h_align_center
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B+0.5,-1,0.001>
      FadeIn(<0.1,0.1,0.1,0>,1)
    }
    text {
      ttf "verdana.ttf" 
      concat("4 triangles+c",squared) 1 0
      h_align_right
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B,-1,0.001>
      FadeIn(<0.1,0.1,0.1,0>,1)
    }
    union {
      box {
        <0,0,0>,<A+B,A+B,0.1>
        pigment {color rgb <0.25,0.25,1>}
      }
      object {
        Tri
        pigment {color rgb <1,1,0>}
      }
      object {
        Tri
        pigment {color rgb <1,1,0>}
        translate -<(A+B)/2,(A+B)/2,0>
        rotate z*180
        translate <(A+B)/2,(A+B)/2,0>
        translate BLinterp(0,<0,0,0>,0.4,<-B,-A,0>,1)
      }
      object {
        Tri
        pigment {color rgb <1,1,0>}
        translate -<(A+B)/2,(A+B)/2,0>
        rotate z*270
        translate <(A+B)/2,(A+B)/2,0>
        translate BLinterp(0.6,<0,0,0>,1.0,<A,0,0>,1)
      }
      object {
        Tri
        pigment {color rgb <1,1,0>}
        translate -<(A+B)/2,(A+B)/2,0>
        rotate z*90
        translate <(A+B)/2,(A+B)/2,0>
        translate BLinterp(0.6,<0,0,0>,1.0,<0,B,0>,1)
      }
      translate <A+B+1,0,0>
    }
    #break
  #case(13)
    #declare Loc=Loc10;
    #declare Scale=Scale10;
    object {
      QuadTri
      pigment {color rgb <1,1,0>}
    }
    box {
      <0,0,0>,<A+B,A+B,0.1>
      pigment {color rgb <0.25,0.25,1>}
    }
    object {
      Tri
      pigment {color rgb <1,1,0>}
      translate <A+B+1,0,0>
    }
    object {
      Tri
      pigment {color rgb <1,1,0>}
      translate -<(A+B)/2,(A+B)/2,0>
      rotate z*180
      translate <(A+B)/2,(A+B)/2,0>
      translate <-B,-A,0>
      translate <A+B+1,0,0>
    }
    object {
      Tri
      pigment {color rgb <1,1,0>}
      translate -<(A+B)/2,(A+B)/2,0>
      rotate z*270
      translate <(A+B)/2,(A+B)/2,0>
      translate <A,0,0>
      translate <A+B+1,0,0>
    }
    object {
      Tri
      pigment {color rgb <1,1,0>}
      translate -<(A+B)/2,(A+B)/2,0>
      rotate z*90
      translate <(A+B)/2,(A+B)/2,0>
      translate <0,B,0>
      translate <A+B+1,0,0>
    }
    box {
      <0,0,0>,<A+B,A+B,0.1>
      translate <A+B+1,0,0>
      pigment {color rgb <0.25,0.25,1>}
    }
    box {
      <0,0,0>,<A,A,0.2>
      FadeIn(<1,0,0,0>,SceneClock)
      translate <0,B,0>
      translate <A+B+1,0,0>
    }
    box {
      <0,0,0>,<B,B,0.2>
      FadeIn(<0,1,0,0>,SceneClock)
      translate <A,0,0>
      translate <A+B+1,0,0>
    }
    text {
      ttf "verdana.ttf" 
      concat("4 triangles+c",squared) 1 0
      h_align_right
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B,-1,0.001>
      FadeIn(<0.1,0.1,0.1,0>,1)
    }
    text {
      ttf "verdana.ttf" 
      "=" 1 0
      h_align_center
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B+0.5,-1,0.001>
      FadeIn(<0.1,0.1,0.1,0>,1)
    }
    text {
      ttf "verdana.ttf" 
      concat("a",squared,"+b",squared,"+4 triangles") 1 0
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B+1,-1,0.001>
      FadeIn(<0.1,0.1,0.1,0>,SceneClock)
    }
    #break
  #case(14)
    #declare Loc=Loc11;
    #declare Scale=Scale11;
    object {
      QuadTri
      pigment {color rgb <1,1,0>}
    }
    box {
      <0,0,0>,<A+B,A+B,0.1>
      pigment {color rgb <0.25,0.25,1>}
    }
    object {
      Tri
      pigment {color rgb <1,1,0>}
      translate <A+B+1,0,0>
    }
    object {
      Tri
      pigment {color rgb <1,1,0>}
      translate -<(A+B)/2,(A+B)/2,0>
      rotate z*180
      translate <(A+B)/2,(A+B)/2,0>
      translate <-B,-A,0>
      translate <A+B+1,0,0>
    }
    object {
      Tri
      pigment {color rgb <1,1,0>}
      translate -<(A+B)/2,(A+B)/2,0>
      rotate z*270
      translate <(A+B)/2,(A+B)/2,0>
      translate <A,0,0>
      translate <A+B+1,0,0>
    }
    object {
      Tri
      pigment {color rgb <1,1,0>}
      translate -<(A+B)/2,(A+B)/2,0>
      rotate z*90
      translate <(A+B)/2,(A+B)/2,0>
      translate <0,B,0>
      translate <A+B+1,0,0>
    }
    box {
      <0,0,0>,<A+B,A+B,0.1>
      translate <A+B+1,0,0>
      pigment {color rgb <0.25,0.25,1>}
    }
    box {
      <0,0,0>,<A,A,0.2>
      FadeIn(<1,0,0,0>,1)
      translate <0,B,0>
      translate <A+B+1,0,0>
    }
    box {
      <0,0,0>,<B,B,0.2>
      FadeIn(<0,1,0,0>,1)
      translate <A,0,0>
      translate <A+B+1,0,0>
    }
    text {
      ttf "verdana.ttf" 
      concat("4 triangles+c",squared) 1 0
      h_align_right
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B,-1,0.001>
      FadeIn(<0.1,0.1,0.1,0>,1)
    }
    text {
      ttf "verdana.ttf" 
      "=" 1 0
      h_align_center
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B+0.5,-1,0.001>
      FadeIn(<0.1,0.1,0.1,0>,1)
    }
    text {
      ttf "verdana.ttf" 
      concat("a",squared,"+b",squared,"+4 triangles") 1 0
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B+1,-1,0.001>
      FadeIn(<0.1,0.1,0.1,0>,1)
    }
    #break
  #case(15)
    #declare Loc=Loc12;
    #declare Scale=Scale12;
    union {
      QuadTri2(FadeOut2(<0.1,0.1,0.1>,SceneClock))
      FadeOut(<1,1,0,0>,SceneClock)
    }
    prism {
      -0.3,0,4
      <A,0>,<A+B,A>,<B,A+B>,<0,B>
      pigment {color rgb <0.25,0.25,1>}
      rotate -x*90
    }
    union {
      Tri2(FadeOut2(<0.1,0.1,0.1>,SceneClock))
      FadeOut(<1,1,0,0>,SceneClock)
      translate <A+B+1,0,0>
    }
    union {
      Tri2(FadeOut2(<0.1,0.1,0.1>,SceneClock))
      FadeOut(<1,1,0,0>,SceneClock)
      translate -<(A+B)/2,(A+B)/2,0>
      rotate z*180
      translate <(A+B)/2,(A+B)/2,0>
      translate <-B,-A,0>
      translate <A+B+1,0,0>
    }
    union {
      Tri2(FadeOut2(<0.1,0.1,0.1>,SceneClock))
      FadeOut(<1,1,0,0>,SceneClock)
      translate -<(A+B)/2,(A+B)/2,0>
      rotate z*270
      translate <(A+B)/2,(A+B)/2,0>
      translate <A,0,0>
      translate <A+B+1,0,0>
    }
    union {
      Tri2(FadeOut2(<0.1,0.1,0.1>,SceneClock))
      FadeOut(<1,1,0,0>,SceneClock)
      translate -<(A+B)/2,(A+B)/2,0>
      rotate z*90
      translate <(A+B)/2,(A+B)/2,0>
      translate <0,B,0>
      translate <A+B+1,0,0>
    }
    box {
      <0,0,0>,<A,A,0.2>
      FadeIn(<1,0,0,0>,1)
      translate <0,B,0>
      translate <A+B+1,0,0>
    }
    box {
      <0,0,0>,<B,B,0.2>
      FadeIn(<0,1,0,0>,1)
      translate <A,0,0>
      translate <A+B+1,0,0>
    }
    text {
      ttf "verdana.ttf" 
      concat("c",squared) 1 0
      h_align_right
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B,-1,1.002>
      FadeIn(<0.1,0.1,0.1,0>,1)
    }
    text {
      ttf "verdana.ttf" 
      concat("4 triangles+c",squared) 1 0
      h_align_right
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B,-1,0.001>
      FadeOut(<0.1,0.1,0.1,0>,SceneClock)
    }
    text {
      ttf "verdana.ttf" 
      "=" 1 0
      h_align_center
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B+0.5,-1,0>
      FadeIn(<0.1,0.1,0.1,0>,1)
    }
    text {
      ttf "verdana.ttf" 
      concat("a",squared,"+b",squared,"+4 triangles") 1 0
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B+1,-1,0.001>
      FadeOut(<0.1,0.1,0.1,0>,SceneClock)
    }
    text {
      ttf "verdana.ttf" 
      concat("a",squared,"+b",squared) 1 0
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B+1,-1,1.002>
      FadeIn(<0.1,0.1,0.1,0>,1)
    }
    #break
  #case(16)
    #declare Loc=Loc13;
    #declare Scale=Scale13;
    prism {
      -0.3,0,4
      <A,0>,<A+B,A>,<B,A+B>,<0,B>
      pigment {color rgb <0.25,0.25,1>}
      rotate -x*90
    }
    box {
      <0,0,0>,<A,A,0.2>
      FadeIn(<1,0,0,0>,1)
      translate <0,B,0>
      translate <A+B+1,0,0>
    }
    box {
      <0,0,0>,<B,B,0.2>
      FadeIn(<0,1,0,0>,1)
      translate <A,0,0>
      translate <A+B+1,0,0>
    }
    text {
      ttf "verdana.ttf" 
      concat("c",squared) 1 0
      h_align_right
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B,-1,0>
      FadeIn(<0.1,0.1,0.1,0>,1)
    }
    text {
      ttf "verdana.ttf" 
      "=" 1 0
      h_align_center
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B+0.5,-1,0.001>
      FadeIn(<0.1,0.1,0.1,0>,1)
    }
    text {
      ttf "verdana.ttf" 
      concat("a",squared,"+b",squared) 1 0
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B+1,-1,0.001>
      FadeIn(<0.1,0.1,0.1,0>,1)
    }
    #break
  #case(17)
    #declare Loc=Loc12;
    #declare Scale=Scale12;
    prism {
      -0.3,0,4
      <A,0>,<A+B,A>,<B,A+B>,<0,B>
      pigment {color rgb <0.25,0.25,1>}
      rotate -x*90
    }
    union {
      QuadTri2(FadeOut2(<0.1,0.1,0.1>,SceneClock))
      Tri2(FadeOut2(<0.1,0.1,0.1>,SceneClock))
      union {
        Tri2(FadeOut2(<0.1,0.1,0.1>,SceneClock))
        translate -<(A+B)/2,(A+B)/2,0>
        rotate z*180
        translate <(A+B)/2,(A+B)/2,0>
        translate <-B,-A,0>
      }
      union {
        Tri2(FadeOut2(<0.1,0.1,0.1>,SceneClock))
        translate -<(A+B)/2,(A+B)/2,0>
        rotate z*270
        translate <(A+B)/2,(A+B)/2,0>
        translate <A,0,0>
      }
      union {
        Tri2(FadeOut2(<0.1,0.1,0.1>,SceneClock))
        translate -<(A+B)/2,(A+B)/2,0>
        rotate z*90
        translate <(A+B)/2,(A+B)/2,0>
        translate <0,B,0>
      }
      FadeOut(<1,1,0,0>,SceneClock)
      translate <A+B+1,0,0>
    }
    box {
      <0,0,0>,<A,A,0.2>
      FadeIn(<1,0,0,0>,1)
      translate <0,B,0>
      translate <A+B+1,0,0>
    }
    box {
      <0,0,0>,<B,B,0.2>
      FadeIn(<0,1,0,0>,1)
      translate <A,0,0>
      translate <A+B+1,0,0>
    }
    text {
      ttf "verdana.ttf" 
      concat("c",squared) 1 0
      h_align_right
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B,-1,1.002>
      FadeIn(<0.1,0.1,0.1,0>,1)
    }
    text {
      ttf "verdana.ttf" 
      concat("4 triangles+c",squared) 1 0
      h_align_right
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B,-1,0.001>
      FadeOut(<0.1,0.1,0.1,0>,SceneClock)
    }
    text {
      ttf "verdana.ttf" 
      "=" 1 0
      h_align_center
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B+0.5,-1,0>
      FadeIn(<0.1,0.1,0.1,0>,1)
    }
    text {
      ttf "verdana.ttf" 
      concat("a",squared,"+b",squared,"+4 triangles") 1 0
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B+1,-1,0.001>
      FadeOut(<0.1,0.1,0.1,0>,SceneClock)
    }
    text {
      ttf "verdana.ttf" 
      concat("a",squared,"+b",squared) 1 0
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B+1,-1,1.002>
      FadeIn(<0.1,0.1,0.1,0>,1)
    }
    #break
  #case(18)
    #declare Loc=Loc13;
    #declare Scale=Scale13;
    prism {
      -0.3,0,4
      <A,0>,<A+B,A>,<B,A+B>,<0,B>
      pigment {color rgb <0.25,0.25,1>}
      rotate -x*90
    }
    #if(SceneClock>0.4)
      union {
        QuadTri2(FadeIn2(<0.1,0.1,0.1>,BLinterp(0.4,0,1,1,SceneClock)))
        FadeIn(<1,1,0,0>,BLinterp(0.4,0,1,1,SceneClock))
      }
      union {
        Tri2(FadeIn2(<0.1,0.1,0.1>,BLinterp(0.4,0,1,1,SceneClock)))
        union {
          Tri2(FadeIn2(<0.1,0.1,0.1>,BLinterp(0.4,0,1,1,SceneClock)))
          translate -<(A+B)/2,(A+B)/2,0>
          rotate z*180
          translate <(A+B)/2,(A+B)/2,0>
          translate <-B,-A,0>
        }
        union {
          Tri2(FadeIn2(<0.1,0.1,0.1>,BLinterp(0.4,0,1,1,SceneClock)))
          translate -<(A+B)/2,(A+B)/2,0>
          rotate z*270
          translate <(A+B)/2,(A+B)/2,0>
          translate <A,0,0>
        }
        union {
          Tri2(FadeIn2(<0.1,0.1,0.1>,BLinterp(0.4,0,1,1,SceneClock)))
          translate -<(A+B)/2,(A+B)/2,0>
          rotate z*90
          translate <(A+B)/2,(A+B)/2,0>
          translate <0,B,0>
        }
        translate <A+B+1,0,0>
        FadeIn(<1,1,0,0>,BLinterp(0.4,0,1,1,SceneClock))
      }
    #end
    box {
      <0,0,0>,<A,A,0.2>
      FadeIn(<1,0,0,0>,1)
      translate <0,B,0>
      translate <A+B+1,0,0>
    }
    box {
      <0,0,0>,<B,B,0.2>
      FadeIn(<0,1,0,0>,1)
      translate <A,0,0>
      translate <A+B+1,0,0>
    }
    text {
      ttf "verdana.ttf" 
      concat("c",squared) 1 0
      h_align_right
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B,-1,0>
      FadeIn(<0.1,0.1,0.1,0>,1)
    }
    text {
      ttf "verdana.ttf" 
      "=" 1 0
      h_align_center
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B+0.5,-1,0.001>
      FadeIn(<0.1,0.1,0.1,0>,1)
    }
    text {
      ttf "verdana.ttf" 
      concat("a",squared,"+b",squared) 1 0
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B+1,-1,0.001>
      FadeIn(<0.1,0.1,0.1,0>,1)
    }
    #break
  #case(19)
    #declare Loc=Loc12;
    #declare Scale=Scale12;
    union {
      QuadTri2(FadeOut2(<0.1,0.1,0.1>,0))
      FadeOut(<1,1,0,0>,0)
    }
    prism {
      -0.3,0,4
      <A,0>,<A+B,A>,<B,A+B>,<0,B>
      pigment {color rgb <0.25,0.25,1>}
      rotate -x*90
    }
    union {
      object {
        Tri
      }
      object {
        Tri
        translate -<(A+B)/2,(A+B)/2,0>
        rotate z*180
        translate <(A+B)/2,(A+B)/2,0>
        translate <-B,-A,0>
      }
      object {
        Tri
        translate -<(A+B)/2,(A+B)/2,0>
        rotate z*270
        translate <(A+B)/2,(A+B)/2,0>
        translate <A,0,0>
      }
      object {
        Tri
        translate -<(A+B)/2,(A+B)/2,0>
        rotate z*90
        translate <(A+B)/2,(A+B)/2,0>
        translate <0,B,0>
      }
      FadeOut(<1,1,0,0>,0)
      translate <A+B+1,0,0>
    }
    box {
      <0,0,0>,<A,A,0.2>
      FadeIn(<1,0,0,0>,1)
      translate <0,B,0>
      translate <A+B+1,0,0>
    }
    box {
      <0,0,0>,<B,B,0.2>
      FadeIn(<0,1,0,0>,1)
      translate <A,0,0>
      translate <A+B+1,0,0>
    }
    text {
      ttf "verdana.ttf" 
      concat("c",squared) 1 0
      h_align_right
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B,-1,1.002>
      FadeIn(<0.1,0.1,0.1,0>,1)
    }
    text {
      ttf "verdana.ttf" 
      "=" 1 0
      h_align_center
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B+0.5,-1,0>
      FadeIn(<0.1,0.1,0.1,0>,1)
    }
    text {
      ttf "verdana.ttf" 
      concat("a",squared,"+b",squared) 1 0
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B+1,-1,1.002>
      FadeIn(<0.1,0.1,0.1,0>,1)
    }
    #break
  #case(20)
    #declare Loc=Loc12;
    #declare Scale=Scale12;
    union {
      QuadTri2(FadeOut2(<0.1,0.1,0.1>,0))
      FadeOut(<1,1,0,0>,0)
    }
    prism {
      -0.3,0,4
      <A,0>,<A+B,A>,<B,A+B>,<0,B>
      pigment {color rgb <0.25,0.25,1>}
      rotate -x*90
    }
    union {
      object {
        Tri
      }
      object {
        Tri
        translate -<(A+B)/2,(A+B)/2,0>
        rotate z*180
        translate <(A+B)/2,(A+B)/2,0>
        translate <-B,-A,0>
      }
      object {
        Tri
        translate -<(A+B)/2,(A+B)/2,0>
        rotate z*270
        translate <(A+B)/2,(A+B)/2,0>
        translate <A,0,0>
      }
      object {
        Tri
        translate -<(A+B)/2,(A+B)/2,0>
        rotate z*90
        translate <(A+B)/2,(A+B)/2,0>
        translate <0,B,0>
      }
      FadeOut(<1,1,0,0>,0)
      translate <A+B+1,0,0>
    }
    box {
      <0,0,0>,<A,A,0.2>
      FadeIn(<1,0,0,0>,1)
      translate <0,B,0>
      translate <A+B+1,0,0>
    }
    box {
      <0,0,0>,<B,B,0.2>
      FadeIn(<0,1,0,0>,1)
      translate <A,0,0>
      translate <A+B+1,0,0>
    }
    text {
      ttf "verdana.ttf" 
      concat("c",squared) 1 0
      h_align_right
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B,-1,1.002>
      FadeOut(<0.1,0.1,0.1,0>,SceneClock)
    }
    text {
      ttf "verdana.ttf" 
      "=" 1 0
      h_align_center
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B+0.5,-1,0>
      FadeOut(<0.1,0.1,0.1,0>,SceneClock)
    }
    text {
      ttf "verdana.ttf" 
      concat("a",squared,"+b",squared) 1 0
      scale 7/8
      rotate y*180
      rotate -z*90
      translate <A+B+1,-1,1.002>
      FadeOut(<0.1,0.1,0.1,0>,SceneClock)
    }
    #break
#end

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






