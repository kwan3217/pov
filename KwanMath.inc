// KwanMath.inc
//Copyright © 1999-2006 Kwan Systems
//You may use and modify this as you see fit for any non-commercial purpose
//otherwise contact me at chrisj@digiquill.com
//Chris Jeppesen - 3 April 2000

#macro StrVector(V)
  concat(str(V.x,6,6),",",str(V.y,6,6),",",str(V.z,6,6))
#end

#macro PrintVector(Label,V)
  #debug concat(Label,"<",StrVector(V),"> (length: ",str(vlength(V),6,6),")\n")
#end

#macro StrQuat(V)
  concat(str(V.x,6,6),",",str(V.y,6,6),",",str(V.z,6,6),",",str(V.t,6,6))
#end

#macro PrintQuat(Label,V)
  #debug concat(Label,"<",StrQuat(V),"> (length: ",str(sqrt(pow(vlength(<V.x,V.y,V.z>),2)+V.t*V.t),6,6),")\n")
#end

#macro PrintNumber(Label,V)
  #debug concat(Label,str(V,6,6),"\n")
#end        

#macro PrintInt(Label,V)
  #debug concat(Label,str(V,0,0),"\n")
#end        

#macro VecEqual(V1,V2)
  #if((V1.x=V2.x) & (V1.y=V2.y) & (V1.z=V2.z)) 
    (1)
  #else
    (0)
  #end
#end        

#macro LH(V)
  (<V.x,V.z,V.y>)
#end

#macro Sgn(X)
  #if(X>0)
    #local Result=(1);
  #else #if(X<0)
      #local Result=(-1);
    #else
      #local Result=(0);
    #end
  #end
	(Result)
#end

#macro Constrain(LBound,UBound,X)
  #local Y=X;
  #while(Y<LBound) #local Y=Y+(UBound-LBound); #end
  #while(Y>UBound) #local Y=Y-(UBound-LBound); #end
  (Y)
#end

#macro Rev(X)  
  #local Y=X-floor(X/360.0)*360.0 ;
  #if(Y<0)
    #local Y=Y+360;
  #end
  (Y)
#end

#macro CosD(X)
  (cos(radians(X)))
#end

#macro SinD(X)
  (sin(radians(X)))
#end

#macro Sec(X)
  (1/cos(X))
#end

#macro Csc(X)
  (1/sin(X))
#end

#macro Cot(X)
  (1/tan(X))
#end

#macro Atan(X)
  (atan2(X,1))
#end

#macro Atan2D(Y,X)
  (degrees(atan2(Y,X)))
#end

#macro Asin(X)
  (Atan(X / sqrt(-X * X + 1)))
#end

#macro Acos(X)
  #if(X=1)
    (0)
  #else
    (Atan(-X / sqrt(-X * X + 1)) + 2 * Atan(1))
  #end
#end

#macro Asec(X)
  (Atan(X / sqrt(X * X - 1)) + Sgn((X) - 1) * (2 * Atan(1)))
#end

#macro Acsc(X)
  (Atan(X / sqrt(X * X - 1)) + (Sgn(X) - 1) * (2 * Atan(1)))
#end

#macro Acot(X)
  (Atan(X) + 2 * Atan(1))
#end

#macro SinH(X)
  ((exp(X) - exp(-X)) / 2)
#end

#macro CosH(X)
  ((exp(X) + exp(-X)) / 2)
#end

#macro TanH(X)
  ((exp(X) - exp(-X)) / (exp(X) + exp(-X)))
#end

#macro SecH(X)
  (2 / (exp(X) + exp(-X)))
#end

#macro CscH(X)
  (2 / (exp(X) - exp(-X)))
#end

#macro CotH(X)
  ((exp(X) + exp(-X)) / (exp(X) - exp(-X)))
#end

#macro AsinH(X)
  (log(X + sqrt(X * X + 1)))
#end

#macro AcosH(X) 
  (log(X + sqrt(X * X - 1)))
#end

#macro AtanH(X) 
  (log((1 + X) / (1 - X)) / 2)
#end

#macro AsecH(X) 
  (log((sqrt(-X * X + 1) + 1) / X))
#end

#macro AcscH(X)
  (log((Sgn(X) * sqrt(X * X + 1) + 1) / X))
#end

#macro AcotH(X)
  (log((X + 1) / (X - 1)) / 2)
#end

#macro LogN(X,N)
  (log(X) / log(N))
#end

#macro vangle(R1, R2)
  (Acos(vdot(R1, R2) / (vlength(R1) * vlength(R2))))
#end

#macro Linterp(X1,Y1,X2,Y2,X)
  (Y1+(Y2-Y1)*(X-X1)/(X2-X1))
#end

#macro BLinterp(X1,Y1,X2,Y2,X)
  #if(X<X1)
    #local Result=(Y1);
  #else
    #if(X>X2)
      #local Result=(Y2);
    #else
      #local Result=(Linterp(X1,Y1,X2,Y2,X));
    #end
  #end
  (Result)
#end

#macro ASDR(A,S,D,R,Y0,Y1,X)
  #if(X<D)
    #local Result=(BLinterp(A,Y0,S,Y1,X));
  #else
    #local Result=(BLinterp(D,Y1,R,Y0,X));
  #end
  (Result)
#end

#macro Quadterp(X0,Y0,X1,Y1,X2,Y2,X)
  #local P0=(X-X1)*(X-X2)/((X0-X1)*(X0-X2))*Y0;
  #local P1=(X-X0)*(X-X2)/((X1-X0)*(X1-X2))*Y1;
  #local P2=(X-X0)*(X-X1)/((X2-X0)*(X2-X1))*Y2;
  (P0+P1+P2)
#end

#macro Polyval(Poly,X)
  //poly  is an array of polynomial coefficients, highest order first.
  //x     is the point at which to evaluate the poly
  #local Accumulator=0;
  #local Coeff=0;
  #while(Coeff<dimension_size(Poly,1))
    #local Accumulator=Accumulator*X+Poly[Coeff];
    #local Coeff=Coeff+1;
  #end
  (Accumulator)
#end

#macro LLA2XYZ(Lat,Lon,R)
  #local CLat=cos(Lat);
  #local CLon=cos(Lon);
  #local SLat=sin(Lat);
  #local SLon=sin(Lon);
  (<CLat*CLon,SLat,CLat*SLon>*R)
#end

#macro XYZ2Lat(XYZ) 
  (pi/2-vangle(y,XYZ))
#end

#macro XYZ2Lon(XYZ) 
//  PrintVector("XYZ: ",XYZ)
//  PrintNumber("Lon: ",(degrees(atan2(XYZ.z,XYZ.x))))
  (atan2(XYZ.z,XYZ.x))
#end

#macro TPIR(Table,X)
  #local I=0;
//  PrintNumber("X: ",X)
//  PrintNumber("dimension_size(Table,1): ",dimension_size(Table,1))
  #while((I<dimension_size(Table,1)-1) & (X>Table[I+1]))
//    PrintNumber("I: ",I)
//    PrintNumber("Table[I+1]: ",Table[I+1])
    #local I=I+1;
  #end
  (I)
#end


#macro Tableterp(TableX,TableY,X)
  #local I=TPIR(TableX,X);
  #local X0=TableX[I];
  #local Y0=TableY[I];
  #local X1=TableX[I+1];
  #local Y1=TableY[I+1];
//  PrintNumber("X0: ",X0)
//  PrintNumber("Y0: ",Y0)
//  PrintNumber("X1: ",X1)
//  PrintNumber("Y1: ",Y1)
  (Linterp(X0,Y0,X1,Y1,X))
#end

#macro MatxVec(c11,c12,c13,c21,c22,c23,c31,c32,c33,V)
  (<c11*V.x+c12*V.y+c13*V.z,
    c21*V.x+c22*V.y+c23*V.z,
    c31*V.x+c32*V.y+c33*V.z>)
#end

#macro MatxTVec(c11,c12,c13,c21,c22,c23,c31,c32,c33,V)
  (<c11*V.x+c21*V.y+c31*V.z,
    c12*V.x+c22*V.y+c32*V.z,
    c13*V.x+c23*V.y+c33*V.z>)
#end



