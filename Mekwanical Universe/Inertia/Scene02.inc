//#version unofficial Megapov 1.22;

#include "Actors.inc"

#local ShotTime=array[3] {5,5,5}

CalcShotTime(ShotTime)

#switch(Shot)
  #case(0) //Title card
    union {
      Text("verdana.ttf","Part 2",0,Center)
      translate <0,-0.001,3>
      Fade(<0.1,0.1,0.1,0>,ASDR(0,0.25,0.75,1,0,1,ShotClockN))
    }
    union {
      Text("verdana.ttf","Applications of Slope",0,Center)
      translate <0,-0.001,2>
      Fade(<0.1,0.1,0.1,0>,ASDR(0,0.25,0.75,1,0,1,ShotClockN))
    }
    #declare Run=4;
    #declare Slope=-0.1;
    #declare Rise=Slope*Run;
    #declare Angle=degrees(atan(Slope));
    cylinder {
      <-9,0,-9*Slope>,<9,0,9*Slope>,0.05
      Fade(<0,1,0,0>,ASDR(0,0.25,0.75,1,0,1,ShotClockN))
    }
    object {
      Truck
      translate z*0.05
      rotate -y*Angle
      translate Linterp(0.25,<-12,0,-12*Slope>,0.75,<9,0,9*Slope>,ShotClockN)
    }
    #break
  #case(1) 
    #declare Slope=BLinterp(0,0.25,0.5,-0.10,ShotClockN);
    #declare Run=4;
    #declare Rise=Run*Slope;
    #declare Angle=degrees(atan(Slope));
    #declare FadeN=BLinterp(0,0,0.5,1,ShotClockN);
    object {
      Ruler
      rotate -y*90
      #declare Num=pow(BLinterp(0,1,0.5,0,ShotClockN),2);
      PrintNumber("Num: ",Num)
      PrintNumber("AngleNum: ",Linterp(1,20,0,0,Num))
      PrintVector("TransNum: ",Linterp(1,<12*Num,-5,5>,0,<0,0,0>,Num))
      rotate <-0.5,1,1>*Linterp(1,20,0,0,Num)
      translate Linterp(1,<12*Num,-5,5>,0,<0,0,0>,Num)
      translate x*Run
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
    object {
      SteepGradeSign
      translate <Run,0,Rise>*6.5/Run
      translate z*BLinterp(0.5,6,1,0,ShotClockN)
    }
    #break
  #case(2) //Title card
    #declare Run=4;
    #declare Slope=-0.1;
    #declare Rise=Slope*Run;
    #declare Angle=degrees(atan(Slope));
    RunDisplay(Run,1)
    RiseDisplay(Rise,1)
    SlopeDisplay(Slope,1)
    cylinder {
      <-9,0,-9*Slope>,<9,0,9*Slope>,0.05
      Fade(<0,1,0,0>,1)
    }
    box {
      <0,-0.001,0.025>,<Run,0,-0.025>
      Fade(<1,0,0,0>,1)
    }
    union {
      object {Truck}
      TireSmoke(mod(ShotClockN*5     ,1))
      TireSmoke(mod(ShotClockN*5+0.25,1))
      TireSmoke(mod(ShotClockN*5+0.50,1))
      TireSmoke(mod(ShotClockN*5+0.75,1))
      translate z*0.05
      rotate -y*Angle
      translate Linterp(0,<-12,0,-12*Slope>,1,<9,0,9*Slope>,ShotClockN)
    }
    #declare I=0;
    #while(I<4)
      #declare I=I+1;
    #end
    object {
      Ruler
      rotate -y*90
      translate x*Run
    }
    object {
      SteepGradeSign
      translate <Run,0,Rise>*6.5/Run
    }
    #break
#end

plane {
  -y,0
  pigment {checker color rgb 1 color rgb 0.75}
}


camera {
  up y
  right -x*16/9
  sky z
  location <0,-9,0.5>
  look_at <0,0,0.5>
}

light_source {
  <20,-20,20>*1000
  color rgb 1
//  area_light <0,2,0>,<0,0,2> 5 5 circular orient adaptive 1
}


