#include "KwanMath.inc"

#declare SeatWidth=1.5;
#declare SeatBackTop=3;
#declare SeatBackBottom=1.5;
#declare SeatExtent=1.5;
#declare BackAngle=10;
#declare ArmBottom=2;
#declare ArmTop=2.1;
#declare ArmWidth=0.25;
#declare ArmExtent=SeatExtent;
#declare SeatOffset=0.25;

#declare NumSeats=0;

#macro Seat(LArm,Space,Open,RArm)
  #if(LArm)
    box {
      <0+SeatOffset,-ArmWidth/2,ArmBottom>,
      <ArmExtent+SeatOffset,ArmWidth/2,ArmTop>
    }
  #end
  box {
    <0,ArmWidth/2,0>
    <0.1,Space-ArmWidth/2,SeatBackTop-SeatBackBottom>
    rotate -y*BackAngle
    translate <SeatOffset,0,SeatBackBottom>
  }
  box {
    <0,ArmWidth/2,0>
    <SeatExtent,Space-ArmWidth/2,0.1>
    rotate -y*(90-Open)
    translate <SeatOffset,0,SeatBackBottom>
  }
  #if(RArm)
    box {
      <0+SeatOffset,Space-ArmWidth/2,ArmBottom>,
      <ArmExtent+SeatOffset,Space+ArmWidth/2,ArmTop>
    }
  #end
  #declare NumSeats=NumSeats+1;
#end

#macro SeatStraightRow(LAisle,Space,RAisle) 
  #local SeatsSpace=Space-LAisle-RAisle;
  #local NumSeatsRow=floor(SeatsSpace/SeatWidth);
  #local SeatSpace=SeatsSpace/NumSeatsRow;
  #local I=0;
  #while(I<NumSeatsRow-1)
    union { Seat(1,SeatSpace,80,0) translate y*(SeatSpace*I+LAisle) }
    #local I=I+1;
  #end
  union { Seat(1,SeatSpace,80,1) translate y*(SeatSpace*I+LAisle) }
#end

#macro FloorStraightRow(Space,RowRise,RowRun)
  box {
    <0,0,0>,<RowRun,Space,0.2>
  }
  box {
    <0,0,0.2>,<0.2,Space,RowRise>
  }
#end

#macro StraightSection(LAisle,Space,RAisle,RowSpacing,Rise,Run,SeatTex,FloorTex)
  #local Rows=floor(Run/RowSpacing);
  #local RowRun=Run/Rows;
  #local RowRise=Rise/Rows;
  #local FloorRow=union {FloorStraightRow(Space,RowRise,RowRun)}
  #local I=0;
  union {
    #while(I<Rows)
      union {SeatStraightRow(LAisle,Space,RAisle) translate <-RowRun,0,RowRise>*I}
      #local I=I+1;
    #end
    texture {SeatTex}
  }
  #local I=0;
  union {
    #while(I<Rows)
      object {FloorRow translate <-RowRun,0,RowRise>*I}
      #local I=I+1;
    #end
    texture {FloorTex}
  }
#end

#macro StraightBleacher(LAisle,Space,RAisle,Sections,Aisle,RowSpacing,Rise,Run,SeatTex,FloorTex)
  #local TotalAisleSpace=(Sections-1)*Aisle+LAisle+RAisle;
  #local TotalSeatSpace=Space-TotalAisleSpace;
  #local SectionSeatSpace=TotalSeatSpace/Sections;
  #local LSectionWidth=LAisle+SectionSeatSpace+Aisle/2;
  #local MSectionWidth=SectionSeatSpace+Aisle;
  #local RSectionWidth=Aisle/2+SectionSeatSpace+RAisle;  

  union {
    //Left unique section
    union {StraightSection(LAisle,LSectionWidth,Aisle/2,RowSpacing,Rise,Run,SeatTex,FloorTex)}
    //Middle common sections
    #local I=1;
    #while(I<Sections-1)
      union {
        StraightSection(Aisle/2,MSectionWidth,Aisle/2,RowSpacing,Rise,Run,SeatTex,FloorTex)
        translate y*(LSectionWidth+(MSectionWidth)*(I-1))
      }
      #local I=I+1;
    #end
    //Right unique section
    union {
      StraightSection(Aisle/2,RSectionWidth,RAisle,RowSpacing,Rise,Run,SeatTex,FloorTex)
      translate y*(LSectionWidth+(MSectionWidth)*(I-1))
    }
  }
#end

#macro SeatCurvedRow(LAisle,Angle,RAisle,Radius) 
  #local Space=Radius*radians(Angle);
  #local LAngle=degrees(LAisle/Radius);
  #local RAngle=degrees(RAisle/Radius);
  #local SeatsSpace=Space-LAisle-RAisle;
  #local SeatsAngle=degrees(SeatsSpace/Radius);
  #local NumSeatsRow=floor(SeatsSpace/SeatWidth);
  #local SeatSpace=SeatsSpace/NumSeatsRow;
  #local SeatAngle=SeatsAngle/NumSeatsRow;
  #local I=0;
  #while(I<NumSeatsRow-1)
    union { Seat(1,SeatSpace,80,0) translate -x*(Radius) rotate -z*(LAngle+I*SeatAngle)}
    #local I=I+1;
  #end
  union { Seat(1,SeatSpace,80,1) translate -x*(Radius) rotate -z*(LAngle+I*SeatAngle)}
#end

#macro CurvedPlank(R0,R1,H0,H1)
  difference {
    cylinder {
      <0,0,H0>,<0,0,H1>,max(R0,R1)
    }
    cylinder {
      <0,0,H0-0.1>,<0,0,H1+1>,min(R0,R1)
    }
  }
#end

#macro FloorCurvedRow(Angle,Radius,RowRise,RowRun)
  intersection {
    union {
      CurvedPlank(Radius,Radius-RowRun,0,0.2) 
      CurvedPlank(Radius,Radius-0.2,0,RowRise)
    }
  }
#end

#macro CurvedSeatSection(LAisle,Angle,RAisle,InnerRadius,RowSpacing,Rise,Run,SeatTex)
  #local Rows=floor(Run/RowSpacing);
  #local RowRun=Run/Rows;
  #local RowRise=Rise/Rows;
  #local I=0;
  union {
    #while(I<Rows)
      union {SeatCurvedRow(LAisle,Angle,RAisle,InnerRadius+RowRun*I) translate <0,0,RowRise>*I}
      #local I=I+1;
    #end
    texture {SeatTex}
  }
#end

#macro CurvedFloorSection(Angle,InnerRadius,RowSpacing,Rise,Run,FloorTex)
  #local Rows=floor(Run/RowSpacing);
  #local RowRun=Run/Rows;
  #local RowRise=Rise/Rows;
  intersection {
    #local I=0;
    union {
      #while(I<Rows)
        object {FloorCurvedRow(Angle,InnerRadius+RowRun*I,RowRise,RowRun) translate <0,0,RowRise>*I}
        #local I=I+1;
      #end
      texture {FloorTex}
    }
    plane {
      -y,0
    }
    plane {
      y,0
      rotate -z*Angle
    }
  }
#end

#macro CurvedBleacher(Angle,Sections,Aisle,InnerRadius,RowSpacing,Rise,Run,SeatTex,FloorTex) 
  CurvedFloorSection(Angle,InnerRadius,RowSpacing,Rise,Run,FloorTex)
  #local SectionAngle=Angle/Sections;
  #local I=0;
  #while(I<Sections)
    union {
                      /* LAisle,Angle,RAisle,InnerRadius,RowSpacing,Rise,Run,SeatTex,FloorTex */
      CurvedSeatSection(  Aisle/2,SectionAngle,Aisle/2,InnerRadius,RowSpacing,Rise,Run,SeatTex)
      rotate -z*SectionAngle*I
    }
    #local I=I+1;
  #end
#end

