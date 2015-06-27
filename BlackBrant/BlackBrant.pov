#include "NASA36_290_30fps.inc"
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

#include "metals.inc"

#declare BlackPaint=texture {pigment {color rgb < 26, 26, 26>*0.7/255}};
#declare WhitePaint=texture {pigment {color rgb <255,255,255>*0.7/255}};    
#declare RedPaint=  texture {pigment {color rgb <255,0,0>*0.7/255}};    
#declare ShinyAluminum=  texture {T_Chrome_5E}    
#declare DullAluminum=  texture {T_Chrome_2A}    
#declare LaenPurple=texture {pigment {color rgb <160,0,255>*0.7/255}};
#declare Magnesium=  texture {T_Copper_2A}    
#declare LightYellowPaint= texture {pigment {color rgb <255,240,128>*0.7/255}};     

#declare TerrierFin=prism {
  0,0.02/0.0254 , 4
  < 0, 9>, 
  <-6.5,31>, 
  <-17,31>,
  <-23.5,9>
  rotate<-90,-90,0>
  scale 0.0254
  rotate<0,0,0> 
  translate<-0.01,0,29.27*0.0254> 
}

#declare BlackBrantFin=prism { 
  0,0.02/0.0254 , 4
  < 0, 9>, 
  <-36,29.5>, 
  <-61,29.5>,
  <-48,9>
  rotate<-90,-90,0>

  scale 0.0254
  rotate<0,0,0> 
  translate<-0.01,0,227.45*0.0254> 
}


#declare Terrier=union {
  object {TerrierFin rotate z* 45 texture {LightYellowPaint}}
  object {TerrierFin rotate z*135 texture {LightYellowPaint}}
  object {TerrierFin rotate z*225 texture {LightYellowPaint}}
  object {TerrierFin rotate z*315 texture {LightYellowPaint}}
  cylinder {
    z*0,z*147*0.0254,18.0*0.0254/2
    texture {WhitePaint}
  }
  cone {
    z*147*0.0254,18.0*0.0254/2,z*152*0.0254,12.0*0.0254/2
    texture {ShinyAluminum}
  }    
  cylinder {
    z*152*0.0254,z*155*0.0254,12.0*0.0254/2
    texture {ShinyAluminum}
  }    
  cone {
    z*155*0.0254,12.0*0.0254/2,z*169*0.0254,22.0*0.0254/2
    texture {ShinyAluminum}
  }    
}          

#declare BlackBrant=union {
  cone {
    z*169*0.0254,22.0*0.0254/2,z*183.49*0.0254,17.26*0.0254/2
    texture {ShinyAluminum}
  }    
  cylinder {
    z*183.49*0.0254,z*391.81*0.0254,17.26*0.0254/2
    texture {BlackPaint}
  }
  cylinder {
    z*391.81*0.0254,z*402.42*0.0254,17.26*0.0254/2
    texture {DullAluminum}
  }
  cone {
    z*402.42*0.0254,17.26*0.0254/2,z*419.28*0.0254,22.0*0.0254/2
    texture {DullAluminum}
  }
  object {BlackBrantFin rotate z* 45 texture {BlackPaint}}
  object {BlackBrantFin rotate z*135 texture {BlackPaint}}
  object {BlackBrantFin rotate z*225 texture {BlackPaint}}
  object {BlackBrantFin rotate z*315 texture {BlackPaint}}
}    

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
  rotate y*180
  translate z*520*0.0254
}  

#declare Payload=union {
  cylinder {
    z*419.28*0.0254,z*514.92*0.0254,22.0*0.0254/2
    texture {DullAluminum}
  }
  cone {
    z*514.92*0.0254,22.0*0.0254/2,z*534.25*0.0254,17.26*0.0254/2 
    texture {DullAluminum}
  }   
  cylinder {
    z*534.25*0.0254,z*539.16*0.0254,17.26*0.0254/2              
    texture {DullAluminum}
  }
  object {Rocketometer}
}             

#macro TangentOgive(R,L)
  #local Rho=(R*R+L*L)/(2*R);  
  #debug concat("R: ",str(R,0,6)," L: ",str(L,0,6)," Rho: ",str(Rho,0,6),"\n")
  torus { Rho-R, Rho  rotate x*90 clipped_by {cylinder {0,z*L,R}}}
#end

#declare Telemetry=union {
  cylinder {
    z*539.16*0.0254,z*570.16*0.0254,17.26*0.0254/2              
    texture {DullAluminum}
  }
  cylinder {
    z*570.16*0.0254,z*586.10*0.0254,17.26*0.0254/2              
    texture {Magnesium}
  }
  cylinder {
    z*586.10*0.0254,z*611.35*0.0254,17.26*0.0254/2              
    texture {DullAluminum}
  }
  object {
    TangentOgive(17.26/2,(670.13-611.35) )
    translate z*611.35
    scale 0.0254
    texture {DullAluminum}
  }
  
}

#declare BlackBrantIX=union {
#if(T<6.3)  object {Terrier} #end
  object {BlackBrant}
  object {Payload}
  object {Telemetry}
  rotate y*180 //Orient such that Rocketometer is parallel to world frame, not rocket
  translate z*10
}

cone {
  0,0.2,vnormalize(R),0
  texture {RedPaint}
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

PrintVector("Nose_i: ",QuatVectRotate(Q_br,-z))

object {
  BlackBrantIX
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
  sky vnormalize(R)
  up y
  right -4/3*x
  location <0,-50,0>
  look_at <0,0,0> 
  angle 18
}         

light_source {
  <20,-20,20>
  color rgb <1,1,1>*1.5 
}  