//These determine the coefficients of the roll poly
//They are functions of altitude, with zero at 450km and 1 unit=1km
#declare PolyQ=array[3] {-7.62361804160367e-007, 0.000482814379121888, -0.191804263774172};
#declare PolyL=array[3] { 1.09969888145440e-005,-0.008454324809293420,  6.465382467633230};
#declare PolyC=array[3] {-2.81292050737441e-008, 0.000274570926913346,-15.260657565575000};

//This determines the maximum required roll
//as a function of beta, in degrees

#macro Roll2d(BetaD,Alt)
  #declare Q=Polyval(PolyQ,Alt-450);
  #declare L=Polyval(PolyL,Alt-450);
  #declare C=Polyval(PolyC,Alt-450);
  #declare Poly=array[3] {Q,L,C};
  (max(Polyval(Poly,BetaD),0)*(Sgn(BetaD)))
#end
