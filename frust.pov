#macro PrintNumber(Label,X)
  #debug concat(Label,": ",str(X,6,6),"\n")     
#end
#macro PrintVector(Label,X)
  #debug concat(Label,": <",str(X.x,6,6),",",str(X.y,6,6),",",str(X.z,6,6),"> (length: ",str(vlength(X),6,6),")","\n")     
#end

#macro solveQuad(a,b,c,x1,x2)
  #declare x1=(-b+sqrt(b*b-4*a*c))/(2*a);
  #declare x2=(-b-sqrt(b*b-4*a*c))/(2*a);
#end              

#macro solveFrust(r1,r2,h,r3,hp)
  #local ap=4*r2*r2-4*r1*r1;
  #local bp=-8*r1*r2+8*h*r1;
  #local cp=-4*h*h+8*h*r2;
  #local m1=0;
  #local m2=0;
  #if(ap!=0)
    solveQuad(ap,bp,cp,m1,m2)
    #if(abs(m1)>abs(m2))
      #local m=m1;
    #else         
      #local m=m2;
    #end 
    PrintNumber("m",m)     
    #local Q=atan2(m,1);
  #else
    #local Q=pi/2;
  #end      
  #local Qp=pi/2-Q;
  #if (Qp>pi/2)
    #local Qp=Qp-pi;
  #end
  #declare r3=r2*cos(Qp);
  #declare hp=h-r2+r2*sin(Qp);
#end                         

#declare R1=13;
#declare R2=4;
#declare H=37.06;

#declare xc=R1;
#declare yc=H-R2;

torus {
  R2,0.05   
  rotate x*90
  translate <xc,yc,0> 
  pigment {color rgb <0,1,0>}
}          

plane {
  z,0
  pigment {checker color rgb 1 color rgb 0}
}

cylinder {
  -y*100,y*100,0.05
  pigment {color rgb <0,0,1>}
}

cylinder {
  -x*100,x*100,0.05
  pigment {color rgb <1,0,0>}
}

#declare R3=0;
#declare Hp=0;

camera {
  orthographic
  location <0,0,-30>
  look_at <0,0,0>
}

light_source {
  <20,20,-20>*1000
  color rgb 1
} 

solveFrust(R1,R2,H,R3,Hp)

cylinder {
  0,<R1-R3,Hp,0>,0.05
  pigment {color rgb <1,1,0>}
}  

#macro sphereFrust(P1,R1,P2,R2)
  //Create a sphere capped frustum with a bottom radius of R1, a sphere cap radius of R2.
  #local H=vlength(P2-P1);
  PrintNumber("H",H)     
  #local Axis=vnormalize(P2-P1);
  PrintVector("Axis",Axis)
  #local C=P1+(H-R2)*Axis;
  PrintVector("C",C)
  #local R3=0;
  #local Hp=0;
  solveFrust(R1,R2,H,R3,Hp);
  PrintNumber("R3: ",R3)
  PrintNumber("Hp: ",Hp)
  #local P3=P1+Hp*Axis;
  sphere {
    C,R2
  }
  cone {
    P1,R1,P3,R3
  }
#end
union {
  sphereFrust(<0,0,0>,R1,<0,H,0>,R2)
  pigment {color rgb <1,0.5,0>}
}
