#version unofficial Megapov 1.22;

#include "Actors.inc"

#local ShotTime=array[19] {3,5,3,5,5,5,5,5,10,5,5,2,3,4,5,5,5,5,5}

CalcShotTime(ShotTime)

#switch(Shot)
  #case(0) //Title card
    text {
      ttf "verdana.ttf" 
      "Part 1 - Slope" 0 0
      h_align_center
      rotate -y*90
      rotate -z*90
      translate <0,-0.001,1>
      Fade(<0.1,0.1,0.1,0>,ASDR(0,0.25,0.75,1,0,1,ShotClockN))
    }
    #declare Slope=0.25*sin(ShotClockN*2*pi);
    cylinder {
      <-9,0,-9*Slope>,<9,0,9*Slope>,0.05
      Fade(<0,1,0,0>,ASDR(0,0.25,0.75,1,0,1,ShotClockN))
    }
    #break
  #case(1) //"Here is a straight line in two-dimensional space. How can we tell how steep it is?"
    #declare Slope=1/4;
    cylinder {
      <-9,0,-9*Slope>,Linterp(0,<-9,0,-9*Slope>,1,<9,0,9*Slope>,ShotClockN*1.5),0.05
      pigment {color rgb <0,1,0>}
    }
    #break
  #case(2) //"One way is to measure the angle with a protractor."
    object {
      Protractor
      #declare Num=1-pow(1-ShotClockN,2);
      rotate <-1,1,1>*(1-Num)*40
      translate Linterp(0,<-5,-10,5>,1,<0,0,0>,Num)
    }
    #declare Slope=1/4;
    cylinder {
      <-9,0,-9*Slope>,<9,0,9*Slope>,0.05
      pigment {color rgb <0,1,0>}
    }
    #break
  #case(3) //"A line which is perfectly horizontal has an angle of 0&deg;"
    object {
      Protractor
    }
    #declare Slope=1/4*BLinterp(0,1,2,0,ShotClockS);
    #declare Angle=degrees(atan(Slope));
    cylinder {
      <-9,0,-9*Slope>,<9,0,9*Slope>,0.05
      pigment {color rgb <0,1,0>}
    }
    AngleDisplay(0,BLinterp(0,0,2,1,ShotClockS))
    #break
  #case(4) //"One which goes up as you go right has a positive angle..."
    object {
      Protractor
    }
    #declare Slope=BLinterp(0,0,2,1,ShotClockS);
    #declare Angle=degrees(atan(Slope));
    cylinder {
      <-9,0,-9*Slope>,<9,0,9*Slope>,0.05
      pigment {color rgb <0,1,0>}
    }
    AngleDisplay(Angle,1)
    #break
  #case(5) //"...and one which goes down as you go right has a negative angle."
    object {
      Protractor
    }
    #declare Slope=BLinterp(0,1,2,-1,ShotClockS);
    #declare Angle=degrees(atan(Slope));
    cylinder {
      <-9,0,-9*Slope>,<9,0,9*Slope>,0.05
      pigment {color rgb <0,1,0>}
    }
    AngleDisplay(Angle,1)
    #break
  #case(6) //"We can go all the way to vertical at 90&deg;..."
    object {
      Protractor
    }
    #declare Angle=BLinterp(0,-45,2,90,ShotClockS);
    cylinder {
      <-9,0,0>,<9,0,0>,0.05
      pigment {color rgb <0,1,0>}
      rotate -y*Angle
    }
    AngleDisplay(Angle,1)
    #break
  #case(7) //"...but the line is the same as the one at -90&deg;"
    object {
      Protractor
    }
    #declare Angle=BLinterp(0,90,2,-90,ShotClockS);
    cylinder {
      <-9,0,0>,<9,0,0>,0.05
      pigment {color rgb <0,1,0>}
      rotate -y*Angle
    }
    AngleDisplay(Angle,1)
    #break
  #case(8) //"Any line has an angle between -90 and +90."
    object {
      Protractor
    }
    #declare Angle=BLinterp(-1,90,1,-90,cos(ShotClockN*1.25*pi*2));
    cylinder {
      <-9,0,0>,<9,0,0>,0.05
      pigment {color rgb <0,1,0>}
      rotate -y*Angle
    }
    AngleDisplay(Angle,1)
    #break
  #case(9) //"While this will work, there is a way to measure its steepness..."
    object {
      Protractor
      #declare Num=pow(BLinterp(0.2,0,1,1ShotClockN),2);
      rotate <-1,1,1>*Num*40
      translate Linterp(1,<-5,-10,5>,0,<0,0,0>,Num)
    }
    #declare Slope=BLinterp(0.2,0,1,1/4,ShotClockN);
    #declare Angle=degrees(atan(Slope));
    cylinder {
      <-9,0,-9*Slope>,<9,0,9*Slope>,0.05
      pigment {color rgb <0,1,0>}
    }
    AngleDisplay(0,BLinterp(0,1,2,0,ShotClockS))
    #break
  #case(10) //"...with only a ruler."
    object {
      Ruler
      #declare Num=1-pow(1-BLinterp(0,0,0.6,1,ShotClockN),2);
      rotate <-1,1,1>*(1-Num)*40
      translate Linterp(0,<-5,-10,5>*1.7,1,<0,0,0>,Num)
    }
    #declare Slope=1/4;
    #declare Angle=degrees(atan(Slope));
    cylinder {
      <-9,0,-9*Slope>,<9,0,9*Slope>,0.05
      pigment {color rgb <0,1,0>}
    }
    #break
  #case(11) //"This can be a lot more convenient for some purposes."
    object {
      Ruler
    }
    object {
      Pencil
      rotate <0,-15,-30>
      #declare Num=1-pow(1-BLinterp(0,0,1,1,ShotClockN),2);
      rotate <-1,1,1>*(1-Num)*40
      translate Linterp(0,<-5,-10,5>*1.7,1,<0,0,0>,Num)
    }
    #declare Slope=1/4;
    #declare Angle=degrees(atan(Slope));
    cylinder {
      <-9,0,-9*Slope>,<9,0,9*Slope>,0.05
      pigment {color rgb <0,1,0>}
    }
    #break
  #case(12) //"We measure a certain distance from the line directly to the right. This is the ''run''."
    object {
      Ruler
    }
    #declare Run=BLinterp(0,0,2/3,4,ShotClockN);
    object {
      Pencil
      rotate <0,-15,-30>
      translate x*Run
    }
    box {
      <0,-0.001,0.025>,<Run,0,-0.025>
      pigment {color rgb <1,0,0>}
    }
    RunDisplay(Run,BLinterp(0,0,1,1,ShotClockS))
    #declare Slope=1/4;
    #declare Angle=degrees(atan(Slope));
    cylinder {
      <-9,0,-9*Slope>,<9,0,9*Slope>,0.05
      pigment {color rgb <0,1,0>}
    }
    #break
  #case(13) //"We then measure straight up or down, back to the line. This is the ''rise''."
    #declare Run=4;
    #declare Rise=1;
    object {
      Ruler
      translate -x*BLinterp(0,4,3/4,0,ShotClockN)
      rotate -y*BLinterp(0,0,3/4,90,ShotClockN)
      translate x*4
    }
    object {
      Pencil
      rotate <0,-15,-30>
      translate x*4
      translate BLinterp(3/4,<0,0,0>,1,<8,-2,5>,ShotClockN)
    }
    box {
      <0,-0.001,0.025>,<4,0,-0.025>
      pigment {color rgb <1,0,0>}
    }
    RunDisplay(Run,1)
    RiseDisplay(Rise,BLinterp(0,0,1,1,ShotClockS))
    #declare Slope=Rise/Run;
    #declare Angle=degrees(atan(Slope));
    cylinder {
      <-9,0,-9*Slope>,<9,0,9*Slope>,0.05
      pigment {color rgb <0,1,0>}
    }
    #break
  #case(14) //"Now we divide rise by run and call this the ''slope.''"
    #declare Run=4;
    #declare Rise=1;
    #declare Slope=Rise/Run;
    #declare Angle=degrees(atan(Slope));
    object {
      Ruler
      rotate -y*90
      translate x*4
    }
    box {
      <0,-0.001,0.025>,<4,0,-0.025>
      pigment {color rgb <1,0,0>}
    }
    RunDisplay(Run,1)
    RiseDisplay(Rise,1)
    SlopeDisplay(Slope,BLinterp(0,0,1,1,ShotClockS))
    cylinder {
      <-9,0,-9*Slope>,<9,0,9*Slope>,0.05
      pigment {color rgb <0,1,0>}
    }
    #break
  #case(15) //"Since the line is straight, it doesn't matter where we do this, the slope is the same everywhere."
    #declare Run=4;
    #declare Rise=1;
    #declare Slope=Rise/Run;
    #declare Origin=sin(2*pi*BLinterp(0,0,0.9,1,ShotClockN));
    #if(Origin>0) 
      #declare Origin=Origin*3;
    #else 
      #declare Origin=Origin*5;
    #end
    #declare Angle=degrees(atan(Slope));
    object {
      Ruler
      rotate -y*90
      translate x*4
      translate <1,0,Slope>*Origin
    }
    box {
      <0,-0.001,0.025>,<4,0,-0.025>
      pigment {color rgb <1,0,0>}
      translate <1,0,Slope>*Origin
    }
    RunDisplay(Run,1)
    RiseDisplay(Rise,1)
    SlopeDisplay(Slope,1)
    cylinder {
      <-9,0,-9*Slope>,<9,0,9*Slope>,0.05
      pigment {color rgb <0,1,0>}
    }
    #break
  #case(16) //"You can choose any run you want, but once you do, the steepness of the line determines the rise and the slope."
    #declare Origin=sin(2*pi*BLinterp(0,0,0.9,1,ShotClockN));
    #if(Origin>0) 
      #declare Origin=Origin*2;
    #else 
      #declare Origin=Origin*7;
    #end
    #declare Run=4+Origin;
    #declare Rise=1+Origin/4;
    #declare Slope=1/4;
    #declare Angle=degrees(atan(Slope));
    object {
      Ruler
      rotate -y*90
      translate x*Run
    }
    box {
      <0,-0.001,0.025>,<Run,0,-0.025>
      pigment {color rgb <1,0,0>}
    }
    RunDisplay(Run,1)
    RiseDisplay(Rise,1)
    SlopeDisplay(Slope,1)
    cylinder {
      <-9,0,-9*Slope>,<9,0,9*Slope>,0.05
      pigment {color rgb <0,1,0>}
    }
    #break
  #case(17) //"The problem with slope is that no matter how high the slope number is..."
    #declare Origin=BLinterp(0,0,1,100,ShotClockN*ShotClockN);
    #declare Run=4;
    #declare Rise=1+Origin;
    #declare Slope=Rise/Run;
    #declare Angle=degrees(atan(Slope));
    object {
      Ruler
      rotate -y*90
      translate x*Run
    }
    box {
      <0,-0.001,0.025>,<Run,0,-0.025>
      pigment {color rgb <1,0,0>}
    }
    RunDisplay(Run,1)
    RiseDisplay(Rise,1)
    SlopeDisplay(Slope,1)
    cylinder {
      <-9,0,-9*Slope>,<9,0,9*Slope>,0.05
      pigment {color rgb <0,1,0>}
    }
    #break
  #case(18) //"...we can't reach vertical, since there is a horizontal run." 
    #declare Origin=Linterp(0,0,1,100,pow(ShotClockN+1,2));
    #declare Run=4;
    #declare Rise=1+Origin;
    #declare Slope=Rise/Run;
    #declare Angle=degrees(atan(Slope));
    #declare FadeN=BLinterp(0,1,1,0,ShotClockN);
    object {
      Ruler
      rotate -y*90
      translate x*Run
      #declare Num=pow(BLinterp(0.4,0,1,1ShotClockN),2);
      rotate <-1,1,1>*Num*20
      translate Linterp(1,<12*Num,-5,5>,0,<0,0,0>,Num)
    }
    box {
      <0,-0.001,0.025>,<Run,0,-0.025>
      Fade(<1,0,0,0>,FadeN)
    }
    RunDisplay(Run,FadeN)
    RiseDisplay(Rise,FadeN)
    SlopeDisplay(Slope,FadeN)
    cylinder {
      <-9,0,-9*Slope>,<9,0,9*Slope>,0.05
      Fade(<0,1,0,0>,FadeN)
    }
    #break
#end

plane {
  -y,0
  pigment {checker color rgb 1 color rgb 0.75}
}


camera {
  right x*16/9
  sky z
  location <0,-9,0.5>
  look_at <0,0,0.5>
}

light_source {
  <20,-20,20>*1000
  color rgb 1
//  area_light <0,2,0>,<0,0,2> 5 5 circular orient adaptive 1
}


