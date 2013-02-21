#version unofficial Megapov 1.22;

global_settings {right_handed}

#macro QuatConj(Q)
  (<-Q.x,-Q.y,-Q.z,Q.t>)
#end

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
  //Given a quaternion from a certain frame to another frame, and
  //a vector in the from frame, calculate the vector in the to frame
  #local Q1=QuatMult(Q,<V.x,V.y,V.z,0>);
  #local Q2=QuatMult(Q1,QuatConj(Q));
  (<Q2.x,Q2.y,Q2.z>)
#end

#macro qlength(Q)
  (sqrt(Q.x*Q.x+Q.y*Q.y+Q.z*Q.z+Q.t*Q.t))
#end

#macro PrintQuat(Label,Q) 
  #debug concat(Label,"<x: ",str(Q.x,0,6),
                     ", y: ",str(Q.y,0,6),
                     ", z: ",str(Q.z,0,6),
                     ", t: ",str(Q.t,0,6),
               "> (length: ",str(qlength(Q),0,6),")\n")
#end

#macro QuatTransV(Q,Trans,V)
  (QuatVectRotate(Q,V)+Trans)
#end

//Given an object in the from frame, rotate it parallel to the to frame
//and then translate it so that the point at the old origin is at T
#macro QuatTrans(Q,T)
  #local q0=Q.t;
  #local q1=Q.x;
  #local q2=Q.y;
  #local q3=Q.z; 
  matrix <1-2*(q2*q2+q3*q3),2*(q1*q2+q0*q3)  ,2*(q1*q3-q0*q2),
          2*(q1*q2-q0*q3)  ,1-2*(q1*q1+q3*q3),2*(q2*q3+q0*q1),
          2*(q1*q3+q0*q2)  ,2*(q2*q3-q0*q1)  ,1-2*(q1*q1+q2*q2),
          T.x              ,T.y              ,T.z>
//  matrix <1-2*(q2*q2+q3*q3),2*(q1*q2-q0*q3)  ,2*(q1*q3+q0*q2),
//          2*(q1*q2+q0*q3)  ,1-2*(q1*q1+q3*q3),2*(q2*q3-q0*q1),
//          2*(q1*q3-q0*q2)    ,2*(q2*q3+q0*q1),1-2*(q1*q1+q2*q2),
//          T.x              ,T.y              ,T.z>
#end
/*
//Quaternion test cases
#debug "Quaternion basis vectors: \n"
PrintQuat("i: ",<1,0,0,0>)
PrintQuat("j: ",<0,1,0,0>)
PrintQuat("k: ",<0,0,1,0>)
PrintQuat("1: ",<0,0,0,1>)
#debug "Stone Bridge Equations (all should equal <0,0,0,-1>)\n"
PrintQuat("i^2: ",QuatMult(<1,0,0,0>,<1,0,0,0>))
PrintQuat("j^2: ",QuatMult(<0,1,0,0>,<0,1,0,0>))
PrintQuat("k^2: ",QuatMult(<0,0,1,0>,<0,0,1,0>))
PrintQuat("ijk: ",QuatMult(<1,0,0,0>,QuatMult(<0,1,0,0>,<0,0,1,0>)))
#debug "Non-comutativity\n"
PrintQuat("ij (should equal  k): ",QuatMult(<1,0,0,0>,<0,1,0,0>))
PrintQuat("ji (should equal -k): ",QuatMult(<0,1,0,0>,<1,0,0,0>))
PrintQuat("ik (should equal -j): ",QuatMult(<1,0,0,0>,<0,0,1,0>))
PrintQuat("ki (should equal  j): ",QuatMult(<0,0,1,0>,<1,0,0,0>))
PrintQuat("jk (should equal  i): ",QuatMult(<0,1,0,0>,<0,0,1,0>))
PrintQuat("kj (should equal -i): ",QuatMult(<0,0,1,0>,<0,1,0,0>))
//Rotation test
#local S_MCMF=spkezr("SUN",StartET,"IAU_MARS", "NONE","MSL");
#local S_MCI =spkezr("SUN",StartET,"MARSIAU",  "NONE","MSL");
#local Q=pxform("MARSIAU","IAU_MARS",StartET);
PrintQuat  ("Q:        ",Q)
PrintVector("Sun MCI:  ",S_MCI)
PrintVector("Sun MCMF: ",S_MCMF)
PrintVector("Rotate MCI",QuatVectRotate(Q,S_MCI))
PrintNumber("Vangle (asec): ",degrees(vangle(S_MCMF,QuatVectRotate(Q,S_MCI)))*3600)
*/
