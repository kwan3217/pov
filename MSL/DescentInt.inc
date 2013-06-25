#declare MDescentFuel=390; //kg
#declare MDescentDry=829;  //kg
#declare VeMLE=2200;       //m/s
#declare MRover=899;       //kg
#declare Tstep=Tsep+1;
#declare FMLE=3000;        //N at 100% thrust, each MLE
#declare Throttle=0;
#declare Mdot=0;
#declare MM=MDescentFuel+MDescentDry;
#if(TTT<Tland) #declare MM=MM+MRover; #end
#declare NMLE=8;
#declare FMax=FMLE*NMLE;

#while(Tstep<=min(TTT,Tflyaway))
  #declare AA=vlength(A(Tstep));
  #local Vv=vdot(L(Tstep),V(Tstep)); //Vertical component of velocity at step time
  #if(Vv<-0.78)
    #declare NMLE=8; //vv faster than 0.78m/s
  #else
    #declare NMLE=4; //vv slower (in constant vel phase)
  #end
  #declare MM=MDescentFuel+MDescentDry;
  #if(Tstep<Tland) #declare MM=MM+MRover; #end
  #declare FF=MM*AA;
  #declare FMax=FMLE*NMLE;
  #declare Throttle=FF/FMax;
  #declare Mdot=FF/VeMLE;
  #declare MDescentFuel=MDescentFuel-DT*Mdot;
  #declare Tstep=Tstep+DT;
#end

PrintNumber("Mdot:         ",Mdot)
PrintNumber("FuelExhaust:  ",MDescentFuel/Mdot)
PrintNumber("Throttle:     ",Throttle)
PrintNumber("FullThrottle: ",FMax/MM/9.80665)
PrintNumber("MDescentFuel: ",MDescentFuel)
PrintNumber("MDescentFrac: ",MDescentFuel/390)

