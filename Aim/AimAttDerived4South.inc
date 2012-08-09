#include "KwanMath.inc"

//Derived orbit parameters
#declare Rsc=Re+Alt;
#declare nR=sqrt(Mu/pow(Rsc,3)); //mean motion, rad/sec
#declare nD=degrees(nR);
#declare Peak=90/nD;
#declare coeff=-3*nR*Re*Re*J2/(2*Rsc*Rsc);
PrintNumber("Peak: ",Peak)
#declare IncR=acos(EarthRate/coeff);
#declare IncD=degrees(IncR);
//PrintNumber("IncD: ",IncD)
#declare BetaR=radians(BetaD);
#declare SunDecR=radians(SunDecD);

//Derived Cips parameters
#declare CipsStart=CipsStartThetaD/nD;
PrintNumber("CipsStart:  ",CipsStart)
//#declare CipsStart=CipsStartP-Peak;
#declare CipsEnd=CipsEndThetaD/nD;
PrintNumber("CipsEnd:  ",CipsEnd)
//#declare CipsEnd=CipsEndP-Peak;

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
#declare SunVecRH=<cos(BetaR),sin(BetaR),0>;

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

#declare SofieVec=<cos(aR),0,-sin(aR)>;

#declare RSofieVec=vrotate(SofieVec,x*RollD);
PrintVector("RSofieVec:   ",RSofieVec)
#declare PitchR=atan2(RSofieVec.z,RSofieVec.x);
PrintNumber("PitchR:      ",PitchR)
#declare PitchD=degrees(PitchR);
PrintNumber("PitchD:      ",PitchD)
#declare PRSofieVec=vrotate(RSofieVec,y*PitchD);
PrintVector("RSofieVec:   ",PRSofieVec)
#declare YawR=BetaR-atan2(PRSofieVec.y,PRSofieVec.x);
PrintNumber("YawR:        ",YawR)
#declare YawD=degrees(YawR);
PrintNumber("YawD:        ",YawD)
#declare YPRSofieVec=vrotate(PRSofieVec,z*YawD);
PrintVector("YPRSofieVec: ",YPRSofieVec)
PrintVector("SunVec:      ",<cos(BetaR),sin(BetaR),0>)
#declare ThetaSwitch1=PitchD;
PrintNumber("ThetaSwitch1:  ",ThetaSwitch1)
#declare TSwitch1=ThetaSwitch1/nD;
PrintNumber("TSwitch1:      ",TSwitch1)

#declare RSofieVec2=vrotate(SofieVec,x*0);
PrintVector("RSofieVec2:   ",RSofieVec2)
#declare PitchR2=atan2(RSofieVec2.z,RSofieVec2.x);
PrintNumber("PitchR2:      ",PitchR2)
#declare PitchD2=degrees(PitchR2);
PrintNumber("PitchD2:      ",PitchD2)
#declare PRSofieVec2=vrotate(RSofieVec2,y*PitchD2);
PrintVector("RSofieVec2:   ",PRSofieVec2)
#declare YawR2=BetaR-atan2(PRSofieVec2.y,PRSofieVec2.x);
PrintNumber("YawR2:        ",YawR2)
#declare YawD2=degrees(YawR2);
PrintNumber("YawD2:        ",YawD2)
#declare YPRSofieVec2=vrotate(PRSofieVec2,z*YawD2);
PrintVector("YPRSofieVec2: ",YPRSofieVec2)
PrintVector("SunVec:      ",<cos(BetaR),sin(BetaR),0>)
#declare ThetaSwitch2=PitchD2;
PrintNumber("ThetaSwitch2:  ",ThetaSwitch2)
#declare TSwitch2=ThetaSwitch2/nD;
PrintNumber("TSwitch2:      ",TSwitch2)

#macro RollPovD(a)
  rotate -x*a
#end

#macro PitchPovD(a)
  rotate -z*a
#end

#macro YawPovD(a)
  rotate -y*a
#end

#macro RollPovDV(a,V)
  (vrotate(V,-x*a))
#end

#macro PitchPovDV(a,V)
  (vrotate(V,-z*a))
#end

#macro YawPovDV(a,V)
  (vrotate(V,-y*a))
#end

#macro RollRHDV(V,a)
  (vrotate(V,x*a))
#end

#macro PitchRHDV(V,a)
  (vrotate(V,y*a))
#end

#macro YawRHDV(V,a)
  (vrotate(V,z*a))
#end

#macro RollPovR(a)
  RollPovD(degrees(a))
#end

#macro PitchPovR(a)
  PitchPovD(degrees(a))
#end

#macro YawPovR(a)
  YawPovD(degrees(a))
#end

#macro LH(V)
  (<V.x,V.z,V.y>)
#end

#declare OrbitNorm=<0,0,1>;

#declare StartTime=-Peak;
PrintNumber("StartTime: ",StartTime)
#declare EndTime=Peak*3;
PrintNumber("EndTime:   ",EndTime)

//#declare StartTime=SofieObsStart-15;
//PrintNumber("StartTime: ",StartTime)
//#declare EndTime=-StartTime;
//PrintNumber("EndTime:   ",EndTime)

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
PrintNumber("frame:     ",frame_number)
PrintNumber("clock:     ",clock)
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

#include "Turn2.inc"

//put the beginning of the big yaws at the upcrossing and downcrossing
#declare SgnYawD=Sgn(YawD);
#if(SgnYawD=0)
  #declare SgnYawD=1;
#end
                               //Time                        YR Cmd                    P Cmd            Pitch mode (1=geocen, 0=inert)
#declare YPRTable=array[13][4] {{-99999*x,                  <180*SgnYawD,0,0>,         x*0,                        x*1},
                                {(SofieObsStart-600)*x,     <0,0,0>,                   x*0,                        x*1},
                                {(SofieObsStart-300)*x,     <0,0,0>,                   x*-aD,                      x*0},
                                {(SofieObsStart-180)*x,     <BetaD,0,0>,               x*-aD,                      x*0},
                                {ManvStart1*x,              <0,0,0>,                   x*-aD,                      x*0},
                                {TSwitch1*x,                <0,0,0>,                   x*0,                        x*1},
                                {ManvStart2*x,              <0,0,0>,                   x*0,                        x*1},
                                {Peak*x,                    <180*SgnYawD,0,0>,         x*0,                        x*1},
                                {(2*Peak-ManvStart2-60)*x,  <180*SgnYawD,-RollD,0>,x*0,                       x*1},
                                {(2*Peak+PitchD/nD-60)*x,   <180*SgnYawD+YawD,-RollD,0>,x*0,                       x*1}, //This one is there just to flip the sign of the pitch at the right time
                                {(2*Peak+PitchD/nD-60)*x,   <180*SgnYawD+YawD,-RollD,0>,x*(180+PitchD),            x*0},
                                {(2*Peak-SofieObsStart)*x,  <180*SgnYawD-YawD,-RollD,0>,x*(180+PitchD),            x*0}, //This one is there just to flip the sign of the yaw at the right time
                                {(2*Peak-SofieObsStart)*x,  <180*SgnYawD,0,0>,         x*0,                        x*1}
                               }


#declare TimeTable=array[dimension_size(YPRTable,1)] 
#declare YRSpaceTable=array[dimension_size(YPRTable,1)]
#declare PTable=array[dimension_size(YPRTable,1)]
#declare PMTable=array[dimension_size(YPRTable,1)]
#local I=0;
#while(I<dimension_size(YPRTable,1))
  #declare TimeTable[I]=YPRTable[I][0].x;
  #declare YRSpaceTable[I]=YPRTable[I][1];
  #declare PTable[I]=YPRTable[I][2].x;
  #declare PMTable[I]=YPRTable[I][3].x;
  #debug concat(str(TimeTable[I],10,2),str(YRSpaceTable[I].x,10,2),str(YRSpaceTable[I].y,10,2),str(PTable[I],10,2),str(PMTable[I],5,0),"\n")
  #local I=I+1;
#end

#macro ScRoll(T)
  #local Result=TurnV(TimeTable,YRSpaceTable,T);
  (Result.y)
#end

#macro ScYaw(T)
  #local Result=TurnV(TimeTable,YRSpaceTable,T);
  (Result.x)
#end

#macro TableRow(T)
  #local I=0;
  #while(I<dimension_size(TimeTable,1))
    #if(T>TimeTable[I])
      #local result=I;
    #end
    #local I=I+1;
  #end
  (result)
#end

#macro ScPitch(T)
  #local Theta=nD*T; //Theta=pure pitch required for geocentric pointing
  #local TRow=TableRow(T);
  #local TRowM1=max(0,TRow-1);
  #if(PMTable[TableRow(T)])
    #debug "Geocentric\n"
    #if(PMTable[TRowM1]=0)
      //We were in inertial
      #debug "Was Inertial\n"
      #if(T>Peak)
        #debug "Flipping Over\n"
        #local ThetaCmd=180-(PTable[TRowM1]-180);
      #else
        #debug "Not Flipping Over\n"
        #local ThetaCmd=PTable[TRowM1];
      #end
      #local Result=IntegrateS(ThetaCmd,Theta,T-TimeTable[TRow]);
    #else
      //We were in geocentric
      #debug "Was Geocentric\n"
      #local Result=Theta;
    #end
  #else
    #debug "Inertial\n"
    #if(PMTable[TRowM1])
      //We were in geocentric before
      #debug "Was Geocentric\n"
      #local ThetaCmd=nD*TimeTable[TableRow(T)];
      #if(T>Peak)
        #debug "Flipping Over\n"
        #local ThetaCmd=180-(ThetaCmd-180);
      #else
        #debug "Not Flipping Over\n"
      #end
    #else
      //We were already in inertial (possibly at a different pitch)
      #debug "Was Inertial\n"
      #local ThetaCmd=PTable[TRowM1];
    #end
    PrintNumber("ThetaCmd: ",ThetaCmd)
    PrintNumber("PTable: ",PTable[TRow])
    #local Result=IntegrateS(ThetaCmd,PTable[TRow],T-TimeTable[TRow]);
  #end
  (Result)
#end

PrintVector("YRVector: ",TurnV(TimeTable,YRSpaceTable,clockSec))
PrintNumber("ScRoll:   ",ScRoll(clockSec))
PrintNumber("ScYaw:    ",ScYaw(clockSec))
PrintNumber("ScPitch:  ",ScPitch(clockSec))

#macro AimAtt(T,P)
  RollPovD(ScRoll(T))
  #if(PMTable[TableRow(T)])
    //Geocentric
    YawPovD(ScYaw(T))
    PitchPovD(ScPitch(T))
  #else
    //Inertial
    PitchPovD(ScPitch(T))
    YawPovD(ScYaw(T))
  #end
  scale 0.001
  translate P
#end

#macro PrintAimAtt(T,S)
  #declare S=str(T,6,2);
  #declare S=concat(S,",1,",str(ScRoll(T),10,2))
  #if(PMTable[TableRow(T)])
    //Geocentric
    #declare S=concat(S,",3,",str(ScYaw(T),6,2))
    #declare S=concat(S,",2,",str(ScPitch(T),6,2))
  #else
    //Inertial
    #declare S=concat(S,",2,",str(ScPitch(T),6,2))
    #declare S=concat(S,",3,",str(ScYaw(T),6,2))
  #end
  #warning concat(S,"\n")
#end

#macro AimAttInv(T)
  #if(PMTable[TableRow(T)])
    //Geocentric
    PitchPovD(-ScPitch(T))
    YawPovD(-ScYaw(T))
  #else
    //Inertial
    YawPovD(-ScYaw(T))
    PitchPovD(-ScPitch(T))
  #end
  RollPovD(-ScRoll(T))
#end

#macro AimAttV(T,P,V)
  #local result=V;
  #local result=RollPovDV(result,ScRoll(T));
  #if(PMTable[TableRow(T)])
    //Geocentric
    #local result=YawPovDV(result,ScYaw(T));
    #local result=PitchPovDV(result,ScPitch(T));
  #else
    //Inertial
    #local result=PitchPovDV(result,ScPitch(T));
    #local result=YawPovDV(result,ScYaw(T));
  #end
  #local result=result*0.001;
  #local result=result+P;
  (result)
#end

#macro AimAttRHV(T,V)
  #local result=V;
  #local result=RollRHDV(result,ScRoll(T));
  #if(PMTable[TableRow(T)])
    //Geocentric
    #local result=YawRHDV(result,ScYaw(T));
    #local result=PitchRHDV(result,ScPitch(T));
  #else
    //Inertial
    #local result=PitchRHDV(result,ScPitch(T));
    #local result=YawRHDV(result,ScYaw(T));
  #end
  (result)
#end

#macro AimAttInvRHV(T,V)
  #local result=V;
  #if(PMTable[TableRow(T)])
    //Geocentric
    #local result=PitchRHDV(result,-ScPitch(T));
    #local result=YawRHDV(result,-ScYaw(T));
  #else
    //Inertial
    #local result=YawRHDV(result,-ScYaw(T));
    #local result=PitchRHDV(result,-ScPitch(T));
  #end
  #local result=RollRHDV(result,-ScRoll(T));
  (result)
#end

#macro AimAttInvPovV(T,V)
  #local result=V;
  #if(PMTable[TableRow(T)])
    //Geocentric
    #local result=PitchPovDV(result,-ScPitch(T));
    #local result=YawPovDV(result,-ScYaw(T));
  #else
    //Inertial
    #local result=YawPovDV(result,-ScYaw(T));
    #local result=PitchPovDV(result,-ScPitch(T));
  #end
  #local result=RollPovDV(result,-ScRoll(T));
  (result)
#end

#local SV=<cos(BetaR),sin(BetaR),0>;
PrintVector("SV:       ",SV)
#local TSV=AimAttInvRHV(clockSec,AimAttRHV(clockSec,SV));
PrintVector("TSV:      ",TSV)
#if(vlength(SV-TSV)>0.001)
  #debug "Keikoku! Double transform broken"
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
  AimAtt(clockSec,Pos(clockSec))
#end

#macro AimAttV2(V)
  #local Result=AimAttV(clockSec,Pos(clockSec),V);
  (Result)
#end

#macro SofiePoint2()
  #local result=SofiePoint(clockSec,Pos(clockSec));
  (result)
#end

#macro DeckNormPoint2()
  #local result=DeckNormPoint(clockSec,Pos(clockSec));
  (result)
#end

#macro DeckNorm2()
  #local result=DeckNorm(clockSec,Pos(clockSec));
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
