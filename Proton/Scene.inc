//Scene.inc      

//declare SceneNums and SceneWeight arrays

#macro Linterp(x1,y1,x2,y2,xx)
  (y1+(y2-y1)*(xx-x1)/(x2-x1))
#end       

#macro SceneCalc()
  #declare SceneBound=array[dimension_size(SceneNums,1)+2]
  #declare SceneNums2=array[SceneNums[dimension_size(SceneNums,1)-1]+1];
  #local SceneTotalWeight=0;
  #local I=0;               
  #while(I<dimension_size(SceneNums,1))
    #local SceneTotalWeight=SceneTotalWeight+SceneWeight[I];
    #declare SceneNums2[SceneNums[I]]=I;  
    #local I=I+1;
  #end
  #local I=0;               
  #declare SceneBound[0]=0;
  #while(I<dimension_size(SceneNums,1))
    #declare SceneBound[I+1]=SceneBound[I]+SceneWeight[I]/SceneTotalWeight;
    //#warning concat("SceneBound[",str(I+1,0,0),"]=",str(SceneBound[I+1],6,6),"\n")
    #local I=I+1;
  #end                                   
  #declare SceneBound[dimension_size(SceneNums,1)+1]=2;
#end

#macro SceneClockLin(SceneNum)  
  #local SceneNum2=SceneNums2[SceneNum];
  (Linterp(SceneBound[SceneNum2],0,SceneBound[SceneNum2+1],1,clock))
#end
  
#macro SceneClockLBound(SceneNum)  
  #local SceneNum2=SceneNums2[SceneNum];
  #if(clock<SceneBound[SceneNum2])
    ((0))
  #else
    (Linterp(SceneBound[SceneNum2],0,SceneBound[SceneNum2+1],1,clock))
  #end
#end
  
#macro SceneClockUBound(SceneNum)  
  #local SceneNum2=SceneNums2[SceneNum];
  #if(clock>SceneBound[SceneNum2+1])
    (1)
  #else
    (Linterp(SceneBound[SceneNum2],0,SceneBound[SceneNum2+1],1,clock))
  #end
#end

#macro SceneClockBound(SceneNum)  
  #local SceneNum2=SceneNums2[SceneNum];
  #if(clock<SceneBound[SceneNum2])
    (0)
  #else #if(clock>SceneBound[SceneNum2+1])
    (1)
  #else
    (Linterp(SceneBound[SceneNum2],0,SceneBound[SceneNum2+1],1,clock))
  #end #end
#end

#macro SceneClockMult(SceneNumA,SceneNumB)  
  #local SceneNum2A=SceneNums2[SceneNumA];
  #local SceneNum2B=SceneNums2[SceneNumB];
  #if(clock<SceneBound[SceneNum2A])
    (0)
  #else #if(clock>SceneBound[SceneNum2B+1])
    (1)
  #else
    (Linterp(SceneBound[SceneNum2A],0,SceneBound[SceneNum2B+1],1,clock))
  #end #end
#end
