#include "KwanMath.inc"

//Derived orbit parameters
#declare Rsc=Re+Alt;
#declare nR=sqrt(Mu/pow(Rsc,3)); //mean motion, rad/sec
#declare nD=degrees(nR);
#declare Peak=90/nD;
#declare coeff=-3*nR*Re*Re*J2/(2*Rsc*Rsc);
PrintNumber("coeff: ",coeff)
#declare IncR=acos(EarthRate/coeff);
#declare IncD=degrees(IncR);
//PrintNumber("IncD: ",IncD)
#declare BetaR=radians(BetaD);
#declare SunDecR=radians(SunDecD);

//Derived Cips parameters
#declare CipsStart=CipsStartTheta/nD;
PrintNumber("CipsStart:  ",CipsStart)
//#declare CipsStart=CipsStartP-Peak;
#declare CipsEnd=CipsEndP-Peak;

//Globe pole location
#declare Pz=cos(IncR);
#declare Px=(-Pz*sin(BetaR)+sin(SunDecR))/cos(BetaR);
#declare Py=sqrt(1-Px*Px-Pz*Pz);
#declare PoleVec=<Px,Py,Pz>;
//PrintVector("PoleVec: ",PoleVec)
#declare AscNode=<-Py/sqrt(Px*Px+Py*Py), Px/sqrt(Px*Px + Py*Py),0>;
#declare DscNode=< Py/sqrt(Px*Px+Py*Py),-Px/sqrt(Px*Px + Py*Py),0>;
//PrintNumber("ThetaAsc:",degrees(acos(vdot(-x,AscNode))))
#declare alphapR=atan2(Pz,Px);
#declare deltapbarR=acos(Py);
#declare alphapD=degrees(alphapR);
//PrintNumber("alphapD: ",alphapD)
#declare deltapbarD=degrees(deltapbarR);
//PrintNumber("deltapbarD: ",deltapbarD)

#declare SunPoint=<cos(BetaR),0,sin(BetaR)>*149500000;

#macro Pos(T)
  (<sin(nR*T),cos(nR*T),0>*Rsc)
#end  

#declare Spd=sqrt(Mu/Rsc);
//PrintNumber("Spd: ",Spd)
#macro Vel(T)
  (<cos(nR*T),-sin(nR*T),0>*Spd)
#end

#macro SofieHtoT(H)
  #local Sqrt1=abs(-H*H-2*H*Re-Re*Re+Rsc*Rsc*pow(cos(BetaR),2)*pow(sin(BetaR),2)+Rsc*Rsc*pow(sin(BetaR),4));
  #local Sqrt2=abs(pow(cos(BetaR),2)*pow(sin(BetaR),2)+pow(sin(BetaR),4)-1);
  (-(acos(sqrt(Sqrt1)/(Rsc*sqrt(Sqrt2)))/nR))
#end

#macro SofieTtoH(T)
  #local V=<cos(BetaR),0,sin(BetaR)>;
  #local TClose=-Rsc*cos(BetaR)*sin(nR*T);
  
  #local ClosePoint=Pos(T)+V*TClose;
  (vlength(ClosePoint)-Re)
#end

//Derived Sofie parameters
#declare SofieObsStart=SofieHtoT(0);
//PrintNumber("SofieObsStart: ",SofieObsStart)
//PrintNumber("SofieObsH:     ",SofieTtoH(SofieObsStart))
#declare SofieCVStart=SofieHtoT(CVBase);
//PrintNumber("SofieCVStart:    ",SofieCVStart)
//PrintNumber("SofieObsH:     ",SofieTtoH(SofieCVStart))
#declare SofieCVEnd=SofieHtoT(CVTop);
//PrintNumber("SofieCVEnd:    ",SofieCVEnd)
//PrintNumber("SofieObsH:     ",SofieTtoH(SofieCVEnd))
#declare SofieObsEnd=SofieObsStart+SofieObsDuration;
//PrintNumber("SofieObsEnd:   ",SofieObsEnd)
//PrintNumber("SofieObsH:     ",SofieTtoH(SofieObsEnd))
#declare SofieCalEnd=SofieObsStart+SofieObsDuration+SofieCalDuration;
//PrintNumber("SofieCalEnd:   ",SofieObsEnd)
//PrintNumber("SofieCalH:     ",SofieTtoH(SofieCalEnd))
#declare InertialFreezeTime=SofieCalEnd;

#include "Roll2d.inc"

#declare RollD=Roll2d(BetaD,Alt);
PrintNumber("RollD:        ",RollD)
#declare RollR=radians(RollD);
PrintNumber("RollR:        ",RollR)

#declare aD=14;
#declare aR=radians(aD);

#declare SofieVec=<cos(aR),0,sin(aR)>;

#declare RSofieVec=vrotate(SofieVec,x*RollD);
PrintVector("RSofieVec:   ",RSofieVec)
#declare PitchR=atan2(RSofieVec.z,RSofieVec.x);
PrintNumber("PitchR:      ",PitchR)
#declare PitchD=degrees(PitchR);
PrintNumber("PitchD:      ",PitchD)
#declare PRSofieVec=vrotate(RSofieVec,-y*PitchD);
PrintVector("RSofieVec:   ",PRSofieVec)
#declare YawR=-BetaR-atan2(PRSofieVec.y,PRSofieVec.x);
PrintNumber("YawR:        ",YawR)
#declare YawD=degrees(YawR);
PrintNumber("YawD:        ",YawD)
#declare YPRSofieVec=vrotate(PRSofieVec,-z*YawD);
PrintVector("YPRSofieVec: ",YPRSofieVec)
#declare DeckVec=z;
#declare RDeckVec=vrotate(DeckVec,x*RollD);
#declare PRDeckVec=vrotate(RDeckVec,-y*PitchD);
#declare YPRDeckVec=vrotate(PRDeckVec,-z*YawD);
#declare Pitch2R=atan2(PRDeckVec.x,PRDeckVec.z);
PrintNumber("Pitch2R:      ",Pitch2R)
#declare Pitch2D=degrees(Pitch2R);
PrintNumber("Pitch2D:      ",Pitch2D)
#declare ThetaSwitch1=Pitch2D;
PrintNumber("ThetaSwitch1:  ",ThetaSwitch1)
#declare TSwitch1=ThetaSwitch1/nD;
PrintNumber("TSwitch1:      ",TSwitch1)

#declare OrbitNorm=<0,0,1>;

#declare StartTime=SofieObsStart-15;
PrintNumber("StartTime: ",StartTime)
#declare EndTime=-StartTime;
PrintNumber("EndTime:   ",EndTime)
#declare AnimTime=EndTime-StartTime;
PrintNumber("AnimTime:  ",AnimTime)
#ifndef(TimeMod) #declare TimeMod=1; #end
#if(TimeMod)
  #declare clockSec=mod(clock,1)*AnimTime+StartTime;
#else
  #declare clockSec=clock*AnimTime+StartTime;
#end
#declare Theta=nD*clockSec;
#declare CipsView=floor(clock);
PrintNumber("clockSec:  ",clockSec)
PrintNumber("clockH:    ",SofieTtoH(clockSec))

PrintVector("OrbitNorm: ",OrbitNorm)
PrintVector("ScLoc:     ",Pos(clockSec))

PrintVector("Vel: ",Vel(clockSec))

#include "AttitudeControl.inc"

#declare ManvStart1=SofieCalEnd;
#declare ManvEnd1=ManvStart1+TurnTime(YawD)+TurnRatetsettle;

#declare ManvStart2=ManvStart2P-Peak;
#declare ManvEnd2=ManvStart2+TurnTime(RollD)+TurnRatetsettle;

#if(clockSec<ManvStart1)
  #declare AttitudeMode="Inertial Hold";
#else
  #if(clockSec<ManvEnd1)
    #declare AttitudeMode="Cancelling Yaw";
  #else
    #if(clockSec<ManvStart2)
      #declare AttitudeMode="Holding Roll";
    #else
      #if(clockSec<ManvEnd2)
	#declare AttitudeMode="Cancelling Roll";
      #else
	#declare AttitudeMode="Geocentric";
      #end
    #end
  #end
#end

#macro ScRoll(T)
  #if(T<ManvStart2)
    #local Result=RollD;
  #else
    #if(T<ManvEnd2)
      #local Result=RollD-TurnDist(ManvStart2,T,RollD);
    #else
      #local Result=0;
    #end
  #end
  (Result)
#end

#macro ScYaw(T)
  #if(T<ManvStart1)
    #local Result=YawD;
  #else
    #if(T<ManvEnd1)
      #local Result=YawD-TurnDist(ManvStart1,T,YawD);
    #else
      #local Result=0;
    #end
  #end
  (Result)
#end

#macro ScPitch2(T)
  #if(T<TSwitch1)
    #local Result=0;
  #else
    #local Result=Theta-ThetaSwitch1;
  #end
  (Result)
#end

PrintNumber("ScRoll:   ",ScRoll(clockSec))
PrintNumber("ScYaw:    ",ScYaw(clockSec))
PrintNumber("ScPitch2: ",ScPitch2(clockSec))

#macro AimAtt(T,P)
  rotate z*180
  rotate -x*ScRoll(T)
  rotate z*PitchD
  rotate y*ScYaw(T)
  rotate -z*ScPitch2(T)
  scale 0.001
  translate P
#end

#macro AimAttV(T,P,V)
  #debug "In AimAttV\n"
  #local result=V;
  #local result=vrotate(result,z*180);
  #local result=vrotate(result,-x*ScRoll(T));
  #local result=vrotate(result,z*PitchD);
  #local result=vrotate(result,y*ScYaw(T));
  #local result=vrotate(result,-z*ScPitch2(T));
  #local result=result*0.001;
  #local result=result+P;
  #debug "Out of AimAttV\n"
  (result)
#end

#macro SofiePoint(T,P)
  #debug "In SofiePoint\n"
  #local result=AimAttV(T,P,SofiePoint0);
  #debug "Out of SofiePoint\n"
  (result)
#end

#macro DeckNormPoint(T,P)
  (AimAttV(T,P,DeckNorm0))
#end

#macro DeckNorm(T,P)
  (DeckNormPoint(T,P)-Pos(T))
#end

#macro AimAtt2()
  #if(clockSec<InertialFreezeTime)
    AimAtt(InertialFreezeTime,Pos(clockSec))
  #else
    AimAtt(clockSec,Pos(clockSec))
  #end
#end

#macro AimAttV2(V)
  #if(clockSec<InertialFreezeTime)
    #local Result=AimAttV(InertialFreezeTime,Pos(clockSec),V);
  #else
    #local Result=AimAttV(clockSec,Pos(clockSec),V);
  #end
  (Result)
#end

#macro SofiePoint2()
  #debug "In SofiePoint2"
  #if(clockSec<InertialFreezeTime)
    #local result=SofiePoint(InertialFreezeTime,Pos(clockSec));
  #else
    #local result=SofiePoint(clockSec,Pos(clockSec));
  #end
  (result)
#end

#macro DeckNormPoint2()
  #if(clockSec<InertialFreezeTime)
    #local result=DeckNormPoint(InertialFreezeTime,Pos(clockSec));
  #else
    #local result=DeckNormPoint(clockSec,Pos(clockSec));
  #end
  (result)
#end

#macro DeckNorm2()
  #if(clockSec<InertialFreezeTime)
    #local result=DeckNorm(InertialFreezeTime,Pos(clockSec));
  #else
    #local result=DeckNorm(clockSec,Pos(clockSec));
  #end
  (result)
#end

#declare CipsState=0;
#if(clockSec>CipsStart & clockSec<CipsEnd)
  #declare CipsState=CipsState+1;
  #if(mod((clockSec-CipsStart)+CipsCadence*1000,CipsCadence)<clock_delta*AnimTime)
    #declare CipsState=CipsState+1;
  #end  
#end

#switch(CipsState)
  #case(0)
    #declare CipsStatus="Cips off";
    #declare CipsDapatColor=<0,0,1>;
    #break
  #case(1)
    #declare CipsStatus="Cips on";
    #declare CipsDapatColor=<1,1,0>;
    #break
  #case(2)
    #declare CipsStatus="Cips on - Exposure";
    #declare CipsDapatColor=<1,1,1>;
    #break
#end
  
#declare SofieState=0;
#if(clockSec>SofieObsStart & clockSec<SofieCalEnd)
  #declare SofieState=SofieState+1;
  #if(clockSec<SofieObsEnd)
    #declare SofieState=SofieState+1;
    #if(clockSec>SofieCVStart & clockSec<SofieCVEnd)
      #declare SofieState=SofieState+1;
    #end
  #end
#end

#switch(SofieState)
  #case(0)
    #declare SofieStatus="Sofie off"
    #break
  #case(1)
    #declare SofieStatus="Sofie calibration"
    #break
  #case(2)
    #declare SofieStatus="Sofie taking data"
    #break
  #case(3)
    #declare SofieStatus="Sofie Comm Volume"
    #break
#end    

#if(clockSec<0)
  #declare SofieAlt=concat("Sofie Alt: ",str(SofieTtoH(clockSec),0,1),"km");
#else
  #declare SofieAlt="";
#end

#debug concat(SofieStatus,"\n")
#debug concat(CipsStatus,"\n")
#debug concat(AttitudeMode,"\n")
