#include "Stadium.inc"

#version unofficial Megapov 1.22

global_settings {
  right_handed
}

#declare Level1SeatTex=texture {
  pigment {color rgb <1,1,0>}
}

#declare Level2SeatTex=texture {
  pigment {color rgb <1,0.5,0>}
}

#declare LevelCSeatTex=texture {
  pigment {color rgb <0.5,0,1>}
}

#declare Level3SeatTex=texture {
  pigment {color rgb <0.5,0.75,1.0>}
}

#declare Level4SeatTex=texture {
  pigment {color rgb <1,0,0>}
}

#declare Concrete=texture {
  pigment {color rgb 0.5}
}

#declare RS=54/16;

#declare Level1InnerRadius=87;
#declare WingAngle=52;
#declare BowlAngle=120;
#declare StraightRun=275;

#declare LevelBack=array[6] {0,50,76,76,154,120}
#declare LevelRise=array[6] {20,20,6,42,RS*9*(42/72),38}
#declare LevelRun=array[6] {80,50,RS*3,72,RS*9,54}
#declare LevelUp=array[6] {0,28,53,67,112.5,103}
#declare LevelStraightSections=array[6] {12,15,15,7,4,0}
#declare LevelBowlSections=array[6] {12,24,24,11,0,13}
#declare LevelWingSections=array[6] {4,4,4,4,4,0}
#declare SeatTex=array[6] {Level1SeatTex,Level2SeatTex,LevelCSeatTex,Level3SeatTex,Level3SeatTex,Level4SeatTex}


#declare Level=0;
#while(Level<6)
  #if(LevelStraightSections[Level]>0)
    union {
      StraightBleacher(     2,  StraightRun,     2,  LevelStraightSections[Level],    4,        RS,  LevelRise[Level], LevelRun[Level],SeatTex[Level],Concrete)
      translate <-LevelBack[Level],0,LevelUp[Level]>
    }
    union {
      StraightBleacher(     2,  StraightRun,     2,  LevelStraightSections[Level],    4,        RS,  LevelRise[Level], LevelRun[Level],SeatTex[Level],Concrete)
      translate <-Level1InnerRadius-LevelBack[Level],0,LevelUp[Level]>
      rotate -z*BowlAngle
      translate <Level1InnerRadius,StraightRun,0>
    }
  #end
  #if(LevelWingSections[Level]>0)
    union {        /*Angle,    Sections,                Aisle,InnerRadius,                       RowSpacing,Rise,            Run,            SeatTex,       FloorTex) */
      CurvedBleacher(WingAngle,LevelWingSections[Level],4,    Level1InnerRadius+LevelBack[Level],RS,        LevelRise[Level],LevelRun[Level],SeatTex[Level],Concrete)
      rotate z*WingAngle
      translate <Level1InnerRadius,0,LevelUp[Level]>
    }
    union {        /*Angle,    Sections,                Aisle,InnerRadius,                       RowSpacing,Rise,            Run,            SeatTex,       FloorTex) */
      CurvedBleacher(WingAngle,LevelWingSections[Level],4,    Level1InnerRadius+LevelBack[Level],RS,        LevelRise[Level],LevelRun[Level],SeatTex[Level],Concrete)
      translate <0,StraightRun,LevelUp[Level]>
      rotate -z*BowlAngle
      translate <Level1InnerRadius,StraightRun,0>
    }
  #end
  #if(LevelBowlSections[Level]>0)
    union {        /*Angle,Sections,Aisle,InnerRadius,RowSpacing,Rise,Run,SeatTex,FloorTex) */
      CurvedBleacher(BowlAngle,LevelBowlSections[Level],4,    Level1InnerRadius+LevelBack[Level],RS,LevelRise[Level],LevelRun[Level],SeatTex[Level],Concrete)
      translate <Level1InnerRadius,StraightRun,LevelUp[Level]>
    }
  #end
  #declare Level=Level+1;
#end



#if(1)

camera {
  location <250,-250,200>*2
  look_at <50,275,0>
//  angle 5
}
#else
camera {
  location <90,-200,200>
  look_at <90,100,0>
}
#end

light_source {
  <20,-20,15>*1000
  color rgb 1.5
}

plane {
  z,0
  pigment {checker color rgbf <1,1,1,1> color rgbf <1,1,1,0.5>}
  scale 100
}

plane {
  z,-0.00001
  pigment {checker}
  scale 10
}

PrintNumber("Number of seats: ",NumSeats)
