#macro Transition(Q,StartT,StartVal,EndT,EndVal,T)
  #if(T>=StartT & T<=EndT)
    #declare Q=Linterp(StartT,StartVal,EndT,EndVal,T);
  #end
#end
#macro TransitionFlat(Q,StartT,EndT,EndVal,T)
  #if(T>=StartT & T<=EndT)
    #local Q=EndVal;
  #end
#end
#macro TransitionFlatBefore(Q,EndT,EndVal,T)
  #if(T<=EndT)
    #local Q=EndVal;
  #end
#end
#macro TransitionFlatAfter(Q,StartT,EndVal,T)
  #if(T>=StartT)
    #local Q=EndVal;
  #end
#end
