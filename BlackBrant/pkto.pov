#include "RockNRoller_24fps.inc"
#include "KwanMath.inc"

#declare T= State[frame_number][0].t;
PrintNumber("T: ",T)
#declare R=<State[frame_number][0].x,State[frame_number][0].y,State[frame_number][0].z>;
PrintVector("R: ",R)
#declare Q_br=State[frame_number][1];
PrintQuat("Q_br: ",Q_br)
#declare V=<State[frame_number][2].x,State[frame_number][2].y,State[frame_number][2].z>;
PrintVector("V: ",V)
#declare A=<State[frame_number][3].x,State[frame_number][3].y,State[frame_number][3].z>;
PrintVector("A: ",A)
#declare A_ng=<State[frame_number][4].x,State[frame_number][4].y,State[frame_number][4].z>;
PrintVector("A_ng: ",A_ng)
#declare map=<State[frame_number][5].x,State[frame_number][5].y,State[frame_number][5].z>;
PrintVector("map: ",map)
#declare mgp=<State[frame_number][6].x,State[frame_number][6].y,State[frame_number][6].z>;
PrintVector("mgp: ",mgp)

#include "metals.inc"

#declare BlackPaint=texture {pigment {color rgb < 26, 26, 26>*0.7/255}};
#declare WhitePaint=texture {pigment {color rgb <255,255,255>*0.7/255}};    
#declare RedPaint=  texture {pigment {color rgb <255,0,0>*0.7/255}};    
#declare ShinyAluminum=  texture {T_Chrome_5E}    
#declare DullAluminum=  texture {T_Chrome_2A}    
#declare LaenPurple=texture {pigment {color rgb <160,0,255>*0.7/255}};
#declare Magnesium=  texture {T_Copper_2A}    
#declare LightYellowPaint= texture {pigment {color rgb <255,240,128>*0.7/255}};     

#declare Rocketometer=union {
  box {
    <0,0,-0.02>,<2,1,0.02>
    texture {LaenPurple}
  }
  cylinder {
    0,x,0.03
    pigment {color rgb x}
  }
  cylinder {
    0,y,0.03
    pigment {color rgb y}
  }
  cylinder {
    0,z,0.03
    pigment {color rgb z}
  }         
  translate <-1,-0.5,0>
}  


#macro QuatMult(Q1,Q2)
  #local v1=<Q1.x,Q1.y,Q1.z>;
  #local r1=Q1.t;
  #local v2=<Q2.x,Q2.y,Q2.z>;
  #local r2=Q2.t;
  #local r=r1*r2-vdot(v1,v2);
  #local vv=r1*v2+r2*v1+vcross(v1,v2);
  (<vv.x,vv.y,vv.z,r>)
#end

#macro QuatVectRotate(Q,V)
  #local Q1=QuatMult(Q,<V.x,V.y,V.z,0>);
  #local Q2=QuatMult(Q1,<-Q.x,-Q.y,-Q.z,Q.t>);
  (<Q2.x,Q2.y,Q2.z>)
#end

#macro QuatTrans(Q,T)
  #local q0=Q.t;
  #local q1=-Q.x;
  #local q2=-Q.y;
  #local q3=-Q.z;
  matrix <1-2*(q2*q2+q3*q3),2*(q1*q2+q0*q3)  ,2*(q1*q3-q0*q2),
          2*(q1*q2-q0*q3)  ,1-2*(q1*q1+q3*q3),2*(q2*q3+q0*q1),
          2*(q1*q3+q0*q2)  ,2*(q2*q3-q0*q1)  ,1-2*(q1*q1+q2*q2),
          T.x              ,T.y              ,T.z>
#end

union {
  object {Rocketometer}
  cone {
    0,1,map,0
    texture {RedPaint}
    scale 0.1
  }
  QuatTrans(Q_br,x*0)
}

object {
  cone {
    0,0.5,A_ng/9.80665,0
  }
  pigment {color rgb <1,0.5,0>} 
  scale 0.2
  translate x*3
}

camera {
  up y
  right -image_width/image_height*x
  location <0,-50,0>
  look_at <0,0,0> 
}         

light_source {
  <20,-20,20>
  color rgb <1,1,1>*1.5 
}  