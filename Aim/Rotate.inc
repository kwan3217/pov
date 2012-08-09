#include "KwanMath.inc"
#include "Aim.inc"
#include "Roll2d.inc"

#declare a=radians(14);
#declare b=radians(9);
#declare roll=radians(Roll2d(degrees(b),600));
PrintNumber("Roll:        ",roll)

#declare SofieVec=<cos(a),0,sin(a)>;

#declare RSofieVec=vrotate(SofieVec,-x*degrees(roll));
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
  (<V.x,-V.z,-V.y>)
#end

union {
  Vector(LH(<cos(b),-sin(b),0>))
  pigment {color rgb <1,1,0>}
}

//These are in POV coordinates!
#macro Pitch(a)
  rotate z*degrees(a)
#end

#macro Roll(a)
  rotate -x*degrees(a)
#end

#macro Yaw(a)
  rotate y*degrees(a)
#end

union {
  Vector(LH(SofieVec)*2)
  Roll(roll)
  Pitch(pitch)
  Yaw(yaw)
  pigment {color rgb <0,1,0>}
}

union {
  object {
    Aim
    rotate z*180
  }
  union {
    Vector(LH(z)*3)
    pigment {color rgb <0,1,1>}
  }
  union {
    Vector(LH(SofieVec)*2)
    rotate z*180
    translate SofiePoint0
    rotate z*180
    pigment {color rgb <1,1,1>}
  }
  Roll(roll)
  Pitch(pitch)
  Yaw(yaw)
}  

camera {
  location vnormalize(<0,2,-5>)*4
  look_at <0,0,0>
}

light_source {
  <20,20,-20>*1000
  color rgb 1
}
