//Input:
//  Object - Jettisoned object in main body frame, centered on main body center of mass. Povray object.
//  ObjDisp - initial position of center of mass of jettisoned object in main body frame. 3D vector in meters
//  ObjBal - Ballistic coefficient of object = Cd*S/m. Cd is conventional drag coefficient, S is 
//           reference area, m is mass, all of jettisoned object. Scalar in units of m^2/kg. 
//  ObjBodyEjectV - Initial velocity of object in main body frame. 3D vector in meters
//  ObjOmega - Rotation rate in main body frame. 3D Vector in units of rad/s
//  TEject - Time of jettison from animation T0. Scalar in units of s
//  TNow - Time at which to draw the object from animation T0. Scalar in units of s
//Return:
//  none
//Side effects:
//  Instantiates the given object at the correct place in the universe.
//Notes:
//  If Tnow is before Teject, object will be instantiated at its correct non-jettisoned place (as if Tnow==Teject)
#macro Flyaway(Tnow)
  #local QQQ=Q(Tflyaway);
  #local ZZZ=L(Tflyaway);
  #local YYY=vcross(ZZZ,QuatVectRotate(QQQ,y));
  #local XXX=vcross(YYY,ZZZ);
  PrintVector("XXX: ",XXX)
  PrintVector("YYY: ",YYY)
  PrintVector("ZZZ: ",ZZZ)
  #local RRR=R(Tflyaway); 

  #local VVV=V(Tflyaway);
  #local Tstep=Tflyaway+DT;
  #local oldThrottle=Throttle;
  #local Tstep=Tflyaway;
  #local Pitch=0;
  #while(Tstep<Tnow)
    #declare MM=MDescentFuel+MDescentDry;
    #local ObjBal=1*4/MM; //Cd of 1, area of 4m^2
    #local Alt=vlength(RRR)-3396000; 
    #local Agrav=TwoBody(RRR); //Neglect J2, since we are also neglecting much larger centrifugal term
    #local Adrag=-ObjBal*MarsAtmRho(Alt)*vdot(VVV,VVV)*vnormalize(VVV)/2;
    #local Pitch=BLinterp(Tflyaway+2,radians(0),Tflyaway+4,radians(45),Tstep); //Switch sign of 45deg angle to control flyaway direction
    #local Vthrust=cos(Pitch)*ZZZ+sin(Pitch)*XXX;
    #if(MDescentFuel>0)
      #declare Throttle=BLinterp(Tflyaway,oldThrottle,Tflyaway+0.5,1,Tstep);
    #else
      #declare Throttle=0;
    #end
    #declare FMax=FMLE*NMLE;
    #declare AA=FMax*Throttle/MM;
    #declare Mdot=FMax*Throttle/VeMLE;
    #declare MDescentFuel=MDescentFuel-DT*Mdot;
    #local Athrust=Vthrust*AA;
    #local AAA=Agrav+Adrag+Athrust;
    #local RRR=RRR+VVV*DT;
    #local VVV=VVV+AAA*DT;
    #local Tstep=Tstep+DT;
  #end
  #if(defined(Agrav))
  PrintVector("Agrav:   ",Agrav)
  PrintVector("Adrag:   ",Adrag)
  PrintVector("Athrust: ",Athrust)
  PrintVector("AAA: ",AAA)
  PrintVector("VVV: ",VVV)
  PrintVector("VVVrel: ",VVV-V(Tflyaway))
  PrintVector("RRR: ",RRR)
  PrintVector("RRRrel: ",RRR-R(Tflyaway))
  PrintNumber("dt_flyaway: ",Tstep-Tflyaway)
  PrintNumber("Pitch:      ",degrees(Pitch))
  PrintNumber("Mdot:         ",Mdot)
  PrintNumber("FuelExhaust:  ",MDescentFuel/Mdot)
  PrintNumber("Throttle:     ",Throttle)
  PrintNumber("MDescentFuel: ",MDescentFuel)
  PrintNumber("MDescentFrac: ",MDescentFuel/390)
  #end
  object {
    MSLDescentStage(0,Throttle)
    scale <1,1,-1>
    translate -z*0.5
    rotate y*degrees(Pitch)
    translate -z*0.5
    QuatTrans(Q(Tflyaway),RRR)
    CenterWorld(Tnow)
  }
#end
