//Turn.inc

#include "KwanMath.inc"

#ifndef(Verbose) #declare Verbose=0; #end

#macro PrintNumberV(Label,N,Level)
  #if(Verbose>=Level)
    PrintNumber(Label,N)
  #end
#end

#macro PrintVectorV(Label,N,Level)
  #if(Verbose>=Level)
    PrintVector(Label,N)
  #end
#end

#macro PrintSV(Label,Level)
  #if(Verbose>=Level)
    #debug concat(Label,"\n")
  #end
#end

#macro IntegrateS(X1,X2,T)
  PrintSV("Start IntegrateS",1)
  PrintNumberV("X1:       ",X1,1)
  PrintNumberV("X2:       ",X2,1)
  PrintNumberV("T:        ",T,1)
  #local Distance=abs(X2-X1);
  PrintNumberV("Distance: ",Distance,1)
  #local ThisTurnTime=TurnTime(Distance);
  PrintNumberV("TurnTime: ",ThisTurnTime,1)
  #if(T<0)
    PrintSV("Before",1)
    #local Result1=X1;
  #else 
    #if(T<ThisTurnTime)
      PrintSV("During",1)
      #local TD=TurnDist(0,T,Distance);
      PrintNumberV("TD: ",TD,1)
      #local Result1=X1+(X2-X1)*TD/Distance;
    #else
      PrintSV("After",1)
      #local Result1=X2;
    #end 
  #end
  PrintNumberV("Result1: ",Result1,1)
  (Result1)
#end

#macro IntegrateV(X1,X2,T)
  PrintSV("Start IntegrateV",1)
  PrintVectorV("X1:       ",X1,1)
  PrintVectorV("X2:       ",X2,1)
  PrintNumberV("T:        ",T,1)
  #local Distance=vlength(X2-X1);
  PrintNumberV("Distance: ",Distance,1)
  #local ThisTurnTime=TurnTime(Distance);
  PrintNumberV("TurnTime: ",ThisTurnTime,1)
  #if(T<0)
    PrintSV("Before",1)
    #local Result1=X1;
  #else 
    #if(T<ThisTurnTime)
      PrintSV("During",1)
      #local TD=TurnDist(0,T,Distance);
      PrintNumberV("TD: ",TD,1)
      #local Result1=X1+(X2-X1)*TD/Distance;
    #else
      PrintSV("After",1)
      #local Result1=X2;
    #end 
  #end
  PrintVectorV("Result1: ",Result1,1)
  (Result1)
#end

#macro TurnS(Time,Space,T)
  PrintSV("Start TurnS",1)
  #local I=0;
  PrintNumberV("I:      ",I,1)
  #declare Done=(I>=dimension_size(Time,1));
  PrintNumberV("Done:   ",Done,1)
  #local Result2=Space[0];
  PrintNumberV("Result2: ",Result2,1)
  #while(!Done)
    PrintNumberV("T:      ",T,1)
    PrintNumberV("Time[I]:",Time[I],1)
    #if(T<Time[I])
      #declare Done=true;
      PrintNumberV("Done:   ",Done,1)
    #else
      #local Commanded=Space[I];
      #local TCommanded=Time[I];
      #local Result2=IntegrateS(Result2,Space[I],T-Time[I]);
      PrintNumberV("Result2: ",Result2,1)
    #end
    #local I=I+1;
    PrintNumberV("I:      ",I,1)
    #declare Done=(Done | (I>=dimension_size(Time,1)));
    PrintNumberV("Done:   ",Done,1)
  #end
//  PrintNumber("TCmd: ",TCommanded)
//  PrintNumber("Cmd:  ",Commanded)
  (Result2)
#end

#macro TurnV(Time,Space,T)
  PrintSV("Start TurnV",1)
  #local I=0;
  PrintNumberV("I:      ",I,1)
  #declare Done=(I>=dimension_size(Time,1));
  PrintNumberV("Done:   ",Done,1)
  #local Result2=Space[0];
  PrintVectorV("Result2: ",Result2,1)
  #while(!Done)
    PrintNumberV("T:      ",T,1)
    PrintNumberV("Time[I]:",Time[I],1)
    #if(T<Time[I])
      #declare Done=true;
      PrintNumberV("Done:   ",Done,1)
    #else
      #local Commanded=Space[I];
      #local TCommanded=Time[I];
      #local Result2=IntegrateV(Space[max(I-1,0)],Space[I],T-Time[I]);
      PrintVectorV("Result2: ",Result2,1)
    #end
    #local I=I+1;
    PrintNumberV("I:      ",I,1)
    #declare Done=(Done | (I>=dimension_size(Time,1)));
    PrintNumberV("Done:   ",Done,1)
  #end
  PrintNumber("TCmd: ",TCommanded)
  PrintVector("Cmd:  ",Commanded)
  (Result2)
#end

