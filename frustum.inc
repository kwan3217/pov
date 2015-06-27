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

#macro sphereFrust(P1,R1,P2,R2)
  //Create a sphere capped frustum with a bottom radius of R1, a sphere cap radius of R2.
  #local H=vlength(P2-P1);
  #local Axis=vnormalize(P2-P1);
  #local C=P1+(H-R2)*Axis;
  #local R3=0;
  #local Hp=0;
  solveFrust(R1,R2,H,R3,Hp);
  #local P3=P1+Hp*Axis;
  sphere {
    C,R2
  }
  cone {
    P1,R1,P3,R3
  }
#end

