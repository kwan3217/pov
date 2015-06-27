#declare TurnRatea=0.899449713012442;
#declare TurnRatetcrit=37.2928029821767;
#declare TurnRatetsettle=38;

#macro TurnTime(Dist)
  #local Acrit=TurnRatea*TurnRatetcrit/2;
  
  #if(abs(Dist)<Acrit)
    #local T=TurnRatetcrit*sqrt(abs(Dist)/Acrit);
  #else
    #local T=(abs(Dist)+Acrit)/TurnRatea;
  #end
  (T)
#end

#macro TurnDist(Tstart,Tnow,Dist)
  #local b=2*TurnRatea/TurnRatetcrit;
  #local Total=TurnTime(Dist);
  #local T=Tnow-Tstart;
  #if(T<=0 | T>=Total)
    #if(T<=0)
      #local d=0;
    #end
    #if(T>=Total)
      #local d=Dist;
    #end
  #else
    #local StartTime=TurnRatetcrit/2;
    #local StopTime=Total-StartTime;

    #local Acrit=TurnRatea*TurnRatetcrit/2;
    #if(Total>TurnRatetcrit)
      #if(T>0 & T<StartTime)           #local state=0; #end
      #if(T>=StartTime & T<=StopTime)  #local state=1; #end
      #if(T>StopTime & T<Total)        #local state=2; #end
    #else
      #local tmid=Total/2;
      #if(T>0 & T<=tmid)               #local state=0; #end
      #if(T>tmid & T<Total)            #local state=2; #end
    #end

    #switch(state)
      #case(0) //Start up
	#local d=b*T*T/2*Sgn(Dist);
	#break
      #case(1) //Coast
	#local d=Acrit/2+TurnRatea*(T-StartTime)*Sgn(Dist);
	#break;
      #case(2) //Slow down
	#local Tc=Total-T;
	#local d=(abs(Dist)-b*Tc*Tc/2)*Sgn(Dist);
    #end
  #end
  (d)
#end


