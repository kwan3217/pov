#macro NoseCalc(C1,R1,C2,R2,C,R)
  //Given cone with bases at <C1,0,0> and <C2,0,0> and radii R1>R2,
  //return the center <C,0,0> and radius R of a conforming spherical cap on base 2
  
  #local Angle=atan2((C2-C1),(R1-R2));
  #debug str(Angle,0,6)
  //R2=R*sin(Angle)
  #declare R=(R2/sin(Angle));
  //C2=C+R*cos(Angle)
  #declare C=(C2-R*cos(Angle));
#end

#macro NoseSphere(C1,R1,C2,R2)
  //Draw the cap calculated by NoseCalc
  #local C=0;
  #local R=0; 
  NoseCalc(C1,R1,C2,R2,C,R)
  difference {
    sphere {
      <C,0,0>,R
    }
    plane {
      x,C2
    }
  }
#end   

  

//Heat Shield
difference {
  union {
    cone {
      <0,0,0>,20,<10,0,0>,5
    }
    NoseSphere(0,20,10,5)
  }
  union {
   cone {
     <0.0001,0,0>,19.5,<10.0001,0,0>,4.5
   }
   NoseSphere(0.0001,19.5,<
  pigment {color rgb <1,1,0>}
  rotate -z*8
}

//plasma sheath


camera {
  location <2,0,-5>*10
  look_at 0
}

light_source {
  <20,20,-20>*100
  color rgb 1.5
}
