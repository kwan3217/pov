#macro Box(I,Corner)
  #declare Corner[0]=< 1, 0,-1>+y*I; //URF
  #declare Corner[1]=< 1, 0, 1>+y*I; //URA
  #declare Corner[2]=<-1, 0,-1>+y*I; //ULF
  #declare Corner[3]=<-1, 0, 1>+y*I; //ULA
#end

#macro Square(A,B,C,D)
  triangle {A,B,C}
  triangle {A,C,D}
#end

#macro Sides(CornerA,CornerB)
  Square(CornerA[0],CornerB[0],CornerB[1],CornerA[1])
  Square(CornerA[1],CornerB[1],CornerB[3],CornerA[3])
  Square(CornerA[3],CornerB[3],CornerB[2],CornerA[2])
  Square(CornerA[2],CornerB[2],CornerB[0],CornerA[0])
#end

#macro Plane(CornerA)
  Square(CornerA[0],CornerA[1],CornerA[3],CornerA[2])
#end

#macro BoxStack(IA,IB,dI)
  #local CornerA=array[4];
  #local CornerB=array[4];
  #local I=IA;
  Box(I,CornerA)
  Plane(CornerA)
  #local I=I+dI;
  #while (I<IB) 
    Box(I,CornerB)
    Sides(CornerA,CornerB)
    #local CornerA=CornerB;
    #local I=I+dI;
  #end
  #if(I!=IB)
    #local I=IB;
    Box(I,CornerB)
    Sides(CornerA,CornerB)
    #local CornerA=CornerB;
  #end
  Plane(CornerA)
#end

