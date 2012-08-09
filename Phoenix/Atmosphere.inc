#declare Zlimit=145000;
#declare Gamma=1.2941;
#declare Beta=1.458e-6; //Viscosity coefficient, kg/(s m K^1/2)
#declare M0=28.9644; //Earth molecular weight at sea level, kg/kmol
#declare MMars=286.91*M0/188.92; //Mars molecular weight, kg/kmol
#declare Rs=8314.32; // Ideal gas constant, k*Na, J/(K kmol)
#declare S=110.4; //Sutherland's constant, K
#declare Na=6.022169e26; //Avogadro constant, 1/kmol
#declare Sigma=3.65e-10; //Effective colision diameter, m
#declare TAlt=array[10] {  0,2000,4000,14000,20000,30000,40000,84000,90000,125000}
#declare TTbl=array[10] {195, 200, 200,  180,  180,  165,  165,  120,  200,   200}
#declare LnPAlt=array[6] {     0,     2000,     4000,    14000,   20000,30000}//,84000,125000}
#declare LnPTbl=array[6] {ln(610),ln(499.5),ln(410.1),ln(145.1),ln(75.2),3.44}//ln(23.9)}//,-3.32,-6.82}

#macro TableTerp(TblAlt,TblVal,Alt)
  #local I=1;
  #while(I<dimension_size(TblAlt,1)-1 & TblAlt[I]<Alt)
    #local I=I+1;
  #end
/*
  PrintNumber("I: ",I)
  PrintNumber("TblAlt[I-1]: ",TblAlt[I-1])
  PrintNumber("TblAlt[I]:   ",TblAlt[I])
  PrintNumber("TblVal[I-1]: ",TblVal[I-1])
  PrintNumber("TblVal[I]:   ",TblVal[I])
*/
  (Linterp(TblAlt[I-1],TblVal[I-1],TblAlt[I],TblVal[I],Alt))
#end

#macro Temp(Alt)
  (TableTerp(TAlt,TTbl,Alt))
#end

#macro Pressure(Alt)
  (exp(TableTerp(LnPAlt,LnPTbl,Alt)))
#end

#macro MolWeight(Alt)
  (MMars)
#end

#macro Density(Alt)
  #local T=Temp(Alt);
  #if(T=0)
    #local result=(0);
  #else
    #local result=(MolWeight(Alt)*Pressure(Alt)/(Rs*Temp(Alt)));
  #end
  (result)
#end

#macro Vsound(Alt)
  #local M=MolWeight(Alt);

  #if(M=0)
    #local result=(0);
  #else
    #local result=(sqrt(Gamma*Rs*Temp(Alt)/M));
  #end
  (result)
#end

#macro Viscosity(Alt)
  #local T=Temp(Alt);
  ((Beta*pow(T,1.5))/(T+S))
#end


