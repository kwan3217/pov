#declare Zlimit=145000;
#declare Gamma=1.2941;
#declare Beta=1.458e-6; //Viscosity coefficient, kg/(s m K^1/2)
#declare M0=28.9644; //Earth molecular weight at sea level, kg/kmol
#declare MMars=286.91*M0/188.92; //Mars molecular weight, kg/kmol
#declare Rs=8314.32; // Ideal gas constant, k*Na, J/(K kmol)
#declare S=110.4; //Sutherland's constant, K
#declare Na=6.022169e26; //Avogadro constant, 1/kmol
#declare Sigma=3.65e-10; //Effective colision diameter, m
#declare TAlt1=array[10] {  0,2000,4000,14000,20000,30000,40000,84000,90000,125000}
#declare TTbl1=array[10] {195, 200, 200,  180,  180,  165,  165,  120,  200,   200}
//#declare LnPAlt=array[6] {     0,     2000,     4000,    14000,   20000,30000}//,84000,125000}
//#declare LnPTbl=array[6] {ln(610),ln(499.5),ln(410.1),ln(145.1),ln(75.2),3.44}//ln(23.9)}//,-3.32,-6.82}
#declare TAlt=array[27]  {  2.17,  4.83,  7.41,  9.92, 12.37, 14.74, 17.06, 19.33, 21.54, 23.71, 25.84, 27.93, 29.99, 32.03, 34.05, 36.06, 38.06, 40.05, 42.04, 44.02, 45.99, 47.95, 49.89, 51.83, 53.72, 55.65, 57.55}
#declare TTbl=array[27]  {209.39,203.59,197.79,192.08,186.63,181.46,176.77,172.53,168.64,165.22,162.06,159.20,156.83,155.03,153.86,153.15,152.50,151.68,150.77,149.83,148.78,147.71,146.72,145.76,144.75,143.68,143.68}
#declare LnPTbl=array[27]{  6.16,  5.91,  5.66,  5.41,  5.16,  4.91,  4.66,  4.41,  4.16,  3.91,  3.66,  3.41,  3.16,  2.91,  2.66,  2.41,  2.16,  1.91,  1.66,  1.41,  1.16,  0.91,  0.66,  0.41,  0.17, -0.09, -0.34}
#declare LnDTbl=array[27]{ -4.43, -4.66, -4.88, -5.10, -5.32, -5.54, -5.76, -5.99, -6.22, -6.45, -6.68, -6.91, -7.14, -7.38, -7.62, -7.87, -8.11, -8.36, -8.60, -8.85, -9.09, -9.33, -9.57, -9.82,-10.06,-10.30,-10.54}

#macro TableTerp(TblAlt,TblVal,Alt)
  #local I=1;
  #while(I<dimension_size(TblAlt,1)-1 & TblAlt[I]<Alt)
    #local I=I+1;
  #end
  (Linterp(TblAlt[I-1],TblVal[I-1],TblAlt[I],TblVal[I],Alt))
#end

#macro Temp(Alt)
  #if(Alt<57550)
    #local result=(TableTerp(TAlt,TTbl,Alt/1000));
  #else
    #local result=(TableTerp(TAlt1,TTbl1,Alt));
  #end
  (result)
#end

#macro Pressure(Alt)
  (exp(TableTerp(TAlt,LnPTbl,Alt/1000)))
#end

#macro MolWeight(Alt)
  (Density(Alt)*Temp(Alt)/Pressure(Alt)*Rs)
#end

#macro Density(Alt)
  #if(Alt<57550)
    #local result=(exp(TableTerp(TAlt,LnDTbl,Alt/1000)));
  #else
    #local result=(Pressure(Alt)*MMars/(Rs*Temp(Alt)));
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


