//Random Walk

#macro RandomWalk3D(Length,WalkNodes,WalkSeed,Scale)
  #local A=array[WalkNodes]
  #local R=seed(WalkSeed);
  #local A[0]=<0,0,0>;
  #local I=1;
  #while(I<WalkNodes)
    #local A[I]=A[I-1]+<0,rand(R)*2-1,rand(R)*2-1>*Scale+x*Length/(WalkNodes-1);
    #local I=I+1;
  #end
  
  #local I=0;
  #while(I<WalkNodes)
//    PrintVector("Before: ",A[I])
    #local A[I]=A[I]-Linterp(0,0,WalkNodes-1,A[WalkNodes-1],I)+x*I*Length/(WalkNodes-1);
//    PrintVector("After:  ",A[I])
    #local I=I+1;
  #end  
  
  A
#end
    
  
