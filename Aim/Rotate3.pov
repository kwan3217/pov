#include "Math.inc"
#include "Aim.inc"

#declare R1=max(min(Linterp(0/3,0,1/3,1,clock),1),0);
#declare P1=max(min(Linterp(1/3,0,2/3,1,clock),1),0);
#declare Y1=max(min(Linterp(2/3,0,3/3,1,clock),1),0);

#declare a=radians(14);
#declare b=radians(9);
#declare roll=radians(Roll2d(degrees(b),600));
PrintNumber("Roll:        ",degrees(roll))

#declare SofieVec=<cos(a),0,-sin(a)>;

#declare RSofieVec=vrotate(SofieVec,x*degrees(roll));
PrintVector("RSofieVec:   ",RSofieVec)
#declare pitch=atan2(RSofieVec.z,RSofieVec.x);
PrintNumber("pitch:       ",degrees(pitch))
#declare PRSofieVec=vrotate(RSofieVec,y*degrees(pitch));
PrintVector("PRSofieVec:   ",PRSofieVec)
#declare yaw=b-atan2(PRSofieVec.y,PRSofieVec.x);
PrintNumber("yaw:         ",degrees(yaw))
#declare YPRSofieVec=vrotate(PRSofieVec,z*degrees(yaw));
PrintVector("YPRSofieVec: ",YPRSofieVec)
PrintVector("SunVec:      ",<cos(b),sin(b),0>)

#declare DeckVec=z;
#declare RDeckVec=vrotate(DeckVec,-x*degrees(roll));
#declare PRDeckVec=vrotate(RDeckVec,y*degrees(pitch));
#declare YPRDeckVec=vrotate(PRDeckVec,z*degrees(yaw));
#declare pitch2=atan2(YPRDeckVec.x,YPRDeckVec.z);
PrintNumber("Pitch2:      ",pitch2)
PrintNumber("Pitch2(deg): ",degrees(pitch2))

#macro Vector(V)
  union {
    cylinder {
      0,V*0.75,0.05
    }
    cone {
      V*0.75,0.1,V,0
    }
  }
#end

#macro LH(V)
  (<V.x,V.z,V.y>)
#end

union {
  Vector(LH(<cos(b),sin(b),0>))
  pigment {color rgb <1,1,0>}
}

#macro RollPov(a)
  rotate -x*degrees(a)
#end

#macro PitchPov(a)
  rotate -z*degrees(a)
#end

#macro YawPov(a)
  rotate -y*degrees(a)
#end

#macro RollOrb(a)
  rotate x*degrees(a)
#end

#macro PitchOrb(a)
  rotate y*degrees(a)
#end

#macro YawOrb(a)
  rotate z*degrees(a)
#end

union {
  Vector(LH(SofieVec)*2)
  RollPov(roll*R1)
  PitchPov(pitch*P1)
  YawPov(yaw*Y1)
  pigment {color rgb <0,1,0>}
}

union {
  object {Aim rotate z*180}
  RollPov(roll*R1)
  PitchPov(pitch*P1)
  YawPov(yaw*Y1)
  pigment {color rgb <0,1,0>}
}

camera {
  location vnormalize(<0,2,0>)*4
  look_at <0,0,0>
}

light_source {
  <20,20,-20>*1000
  color rgb 1
}
