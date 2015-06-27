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
#macro Jettison(Object,ObjDisp,ObjBal,ObjBodyEjectV,ObjOmega,TEject,TNow)
  #local RRR=R(min(TNow,TEject)); 
  //currently neglecting velocity from body spin 
  #local VVV=V(min(TNow,TEject))+QuatVectRotate(Q(min(TNow,TEject)),ObjBodyEjectV);
  #local Tstep=TEject+DT;
  #local Steps=0;
  #while(Tstep<=(TNow+DT/2))
    #local Alt=vlength(RRR)-3396000; 
    #local Agrav=TwoBody(RRR); //Neglect J2, since we are also neglecting much larger centrifugal term
    #local Adrag=-ObjBal*MarsAtmRho(Alt)*vdot(VVV,VVV)*vnormalize(VVV)/2;
    #local AAA=Agrav+Adrag;
    #local RRR=RRR+VVV*DT;
    #local VVV=VVV+AAA*DT;
    #local Tstep=Tstep+DT;
    #local Steps=Steps+1;
  #end
  #local Tstep=Tstep-DT; //Back the last Tstep off
  #if(defined(Agrav))
  PrintVector("Agrav: ",Agrav)
  PrintVector("Adrag: ",Adrag)
  PrintVector("AAA: ",AAA)
  PrintVector("VVV: ",VVV)
  PrintVector("VVVrel: ",VVV-V(Tstep))
  PrintVector("RRR: ",RRR)
  PrintVector("RRRrel: ",RRR-R(Tstep))
  PrintVector("ObjOmega: ",ObjOmega*(Tstep-TEject))
  #end
  PrintNumber("dt_jettison: ",Tstep-TEject)
  PrintNumber("Steps: ",Steps)
  object {
    Object
    translate -ObjDisp
    rotate ObjOmega*max(0,TNow-TEject)
    translate ObjDisp
    PrintVector("RRRrel: ",RRR-R(TNow))
    QuatTrans(Q(min(TNow,TEject)),RRR)
    CenterWorld(TNow)
  }
#end
