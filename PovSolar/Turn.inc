//Turn.inc

#include "KwanMath.inc"

//Man, this promises *so* much more than it delivers...
#macro IntegrateS(X1,X2,Rate,T)
  #debug "Start IntegrateS\n"
  PrintNumber("X1:       ",X1)
  PrintNumber("X2:       ",X2)
  PrintNumber("T:        ",T)
  #declare Distance=X2-X1;
  PrintNumber("Distance: ",Distance)
  #declare TurnTime=abs(Distance/Rate);
  PrintNumber("TurnTime: ",TurnTime)
  #if(T<0)
    #debug "Before\n"
    #local Result1=(X1);
  #else 
    #if(T<TurnTime)
      #debug "During\n"
      #local Result1=(Linterp(0,X1,TurnTime,X2,T));
    #else
      #debug "After\n"
      #local Result1=(X2);
    #end 
  #end
  PrintNumber("Result1: ",Result1)
  (Result1)
#end

#macro TurnS(Time,Space,Rate,T)
  #debug "Start TurnS\n"
  #declare I=0;
  PrintNumber("I:      ",I)
  #declare Done=(I>=dimension_size(Time,1));
  PrintNumber("Done:   ",Done)
  #local Result2=Space[0];
  PrintNumber("Result2: ",Result2)
  #while(!Done)
    PrintNumber("T:      ",T)
    PrintNumber("Time[I]:",Time[I])
    #if(T<Time[I])
      #declare Done=true;
      PrintNumber("Done:   ",Done)
    #else
      #local Result2=IntegrateS(Result2,Space[I],Rate,T-Time[I]);
      PrintNumber("Result2: ",Result2)
    #end
    #declare I=I+1;
    PrintNumber("I:      ",I)
    #declare Done=(Done + (I>=dimension_size(Time,1)));
    PrintNumber("Done:   ",Done)
  #end
  (Result2)
#end
