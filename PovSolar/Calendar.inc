//Calendar.inc
//Copyright 2000 Kwan Systems
//You may use and modify this as you see fit for any non-commercial purpose
//otherwise contact me at chrisj@digiquill.com
//Chris Jeppesen - 11 April 2000

//Works in JD (Julian Date) 

//Only good for 1900AD-2099AD!

/*Usage*************************\
#macro JulianDate(Y,M,D,H,N,S)
Parameters:
  Y,M,D: Date
  H,N,S: UT
Returns:
  JD of M/D/Y HH:NN:SS UT

#macro CalendarDate(JulD,Year,Month,Day,Hour,Minute,Second)
Parameters:
  JulD: JD
Returns:
  Year,Month,Day,Hour,Minute,Second equivalent of JD

#macro PrintDate(Tag,JulD)
Parameters:
  Tag:  Tag to print just before date
  JulD: JD to print
Result:
  Prints in the Warning Stream the following
  Tag M/D/Y HH:NN:SS (24XXXXX.XXXXXX)
\*******************************/

#declare MonthName=array[12] {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"}

#macro JulianDate(Y,M,D,H,N,S)
  ((367*Y-floor(7*(Y+floor((M+9)/12))/4)+floor(275*M/9)+D+1721013.5)+(H/24)+(N/1440)+(S/86400))
#end

//Good for any julian date
#macro CalendarDate(JulD,Year,Month,Day,Hour,Minute,Second)
  #local JD0 = JulD + 0.5;

  #local Z = floor(JD0);
  #local F = floor((JD0 - Z)*86400+0.5)/86400;

  #local A = 0.0;
  #local ALP = 0.0;
  #if ( Z < 2299161 )
    #local A = Z;
  #else
    #local ALP = floor((Z - 1867216.25)/36524.25);
    #local A = Z + 1.0 + ALP - floor(ALP/4.0);
  #end

  #local B = A + 1524;
  #local C = floor((B - 122.1)/365.25);
  #local D = floor(365.25*C);
  #local E = floor((B - D)/30.600001);

  #declare Day = B - D - floor(30.600001*E) + F;

  #declare Month = 0;
  #if (E < 13.5)
    #declare Month = E - 1;
  #else
    #declare Month = E - 13;
  #end

  #declare Year = 0;
  #if (Month > 2.5)
    #declare Year = C - 4716;
  #else
    #declare Year = C - 4715;
  #end
	
  #declare Hour = floor(24.0*(Day - floor(Day)));
  #declare Minute = floor(1440.0*(Day - floor(Day) - Hour/24.0));
  #declare Second = 86400.0*(Day - floor(Day) - Hour/24.0 - Minute/1440.0);

  #declare Day = floor(Day);
#end

#macro StringDate(JulD)
  #local Year=0;
  #local Month=0;
  #local Day=0;
  #local Hour=0;
  #local Minute=0;
  #local Second=0;
  CalendarDate(JulD,Year,Month,Day,Hour,Minute,Second)
  concat(str(Year,-4,0)," ",MonthName[Month-1]," ",str(Day,-2,0)," ",str(Hour,-2,0),":",str(Minute,-2,0),":",str(Second,-2,0))
#end

#macro StringTime(Day)
  #if(Day<0)
    #local T=-Day;
    #local Neg="-"
  #else
    #local T=Day;
    #local Neg="+"
  #end
  #local Hour=0;
  #local Minute=0;
  #local Second=0;
  #declare Hour = floor(24.0*T);
  #declare Minute = floor(1440.0*(T - Hour/24.0));
  #declare Second = 86400.0*(T - Hour/24.0 - Minute/1440.0);
  concat(Neg,str(Hour,-2,0),"h",str(Minute,-2,0),"m",str(Second,-2,0),"s")
#end

#macro PrintDate(Tag,JulD)
  #debug concat(Tag," ",StringDate(JulD)," (",str(JulD,0,6),")\n")
#end

#declare Jan =  1;
#declare Feb =  2;
#declare Mar =  3;
#declare Apr =  4;
#declare May =  5;
#declare Jun =  6;
#declare Jul =  7;
#declare Aug =  8;
#declare Sep =  9;
#declare Oct = 10;
#declare Nov = 11;
#declare Dec = 12;
