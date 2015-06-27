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

#macro RowF(T)
  #local NumInt=AimAttTNum-1;
	#local IntSize=AimAttTEnd-AimAttTStart;
	#local TT=T-AimAttTStart;
	(floor(TT/IntSize*NumInt))
#end

#macro RowInv(R)
  #local NumInt=AimAttTNum-1;
	#local IntSize=AimAttTEnd-AimAttTStart;
  (R*IntSize/NumInt+AimAttTStart)
#end  

#macro Interp(T,Table,Col)
//	PrintNumber("T:  ",T)
  #local RF=RowF(T);
//	PrintNumber("RF: ",RF)
	#local RC=RF+1;
//	PrintNumber("RC: ",RC)
  (Linterp(RowInv(RF),Table[RF][Col],RowInv(RC),Table[RC][Col],T))
#end

#macro Pos(T)
  (LH(Interp(T,AimAttM,3)))
#end  

#macro Vel(T)
  (LH(Interp(T,AimAttM,4)))
#end  

#declare StartTime=-720;
PrintNumber("StartTime: ",StartTime)
#declare EndTime=300;
PrintNumber("EndTime:   ",EndTime)

#declare AnimTime=EndTime-StartTime;
PrintNumber("AnimTime:  ",AnimTime)
#ifndef(TimeMod) #declare TimeMod=1; #end
PrintNumber("clock: ",clock)
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

PrintVector("ScLoc:     ",Pos(clockSec))

PrintVector("Vel: ",Vel(clockSec))

#macro AimRot(T)
  #local M1=Interp(T,AimAttM,0);
  #local M2=Interp(T,AimAttM,1);
  #local M3=Interp(T,AimAttM,2);
	rotate x*180
	//Flip model handedness to RH
	matrix <1   ,0   ,0   ,
	        0   ,0   ,1   ,
					0   ,1   ,0   ,
					0   ,0   ,0    >
  //Transform					
	matrix <M1.x,M2.x,M3.x,
	        M1.y,M2.y,M3.y,
					M1.z,M2.z,M3.z,
					0   ,0   ,0    >
  //Switch transformation back to LH				
	matrix <1   ,0   ,0   ,
	        0   ,0   ,1   ,
					0   ,1   ,0   ,
					0   ,0   ,0    >
#end

#macro AimAtt(T,P)
  AimRot(T)
  scale 0.001
  translate P
#end

#macro AimRotV(T,V)
  #local M1=Interp(T,AimAttM,0);
  #local M2=Interp(T,AimAttM,1);
  #local M3=Interp(T,AimAttM,2);
	#local V2=V;
	//rotate x*180
	#local V2=<V2.x,-V2.y,-V2.z>;
	//Flip model handedness to RH
	#local V2=LH(V2);
  //Transform					
	#local V2=
	  <M1.x*V2.x+M2.x*V2.y+M3.x*V2.z,
		 M1.y*V2.x+M2.y*V2.y+M3.y*V2.z,
		 M1.z*V2.x+M2.z*V2.y+M3.z*V2.z>;
  //Switch transformation back to LH				
	#local V2=LH(V2);
  (V2)
#end

#macro AimAttV(T,P,V)
  #local V2=AimRotV(T,V);
  #local V2=V2*0.001;
	#local V2=V2+P;
	(V2)
#end

#macro AimAtt2()
  AimAtt(clockSec,Pos(clockSec))
#end

#macro AimRot2()
  AimRot(clockSec)
#end

#macro SofieTtoH(T)
  #local V=Interp(T,AimAttM,5);
  (V.x)
#end

#declare CipsState=0;
#declare CipsStart=CipsObs[0][0]+11.34;
PrintNumber("CipsStart: ",CipsStart)
#declare CipsEnd=CipsObs[35][0];
#declare CipsCadence=43.5;
#declare CipsExp=1.2;
PrintNumber("CipsExp:   ",CipsExp)
#declare FrameTime=clock_delta*AnimTime;
PrintNumber("FrameTime: ",FrameTime)
#declare ExpTime=max(CipsExp,FrameTime);
PrintNumber("ExpTime:   ",ExpTime)
#declare CipsCadenceCycle=mod((clockSec-CipsStart)+CipsCadence*1000,CipsCadence);
PrintNumber("Cycle:     ",CipsCadenceCycle)


#if(clockSec>CipsStart & clockSec<CipsEnd)
  #declare CipsState=CipsState+1;
  #if(CipsCadenceCycle<ExpTime)
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
    #declare CipsDapatColor=Linterp(0,<0,0,1>,1,<1,1,1>,exp(-(CipsCadenceCycle-ExpTime)/(5*FrameTime)));
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

#if(clockSec>SofieCalStartS & clockSec<SofieObsEndS)
  #declare SofieState=SofieState+1;
  #if(clockSec>SofieObsStartS)
    #declare SofieState=SofieState+1;
    #if(clockSec>SofieCVStartS & clockSec<SofieCVEndS)
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
		#declare SofieDapatColor=<0,1,0,0.8>;
    #break
  #case(2)
    #declare SofieStatus="Sofie taking data"
		#declare SofieDapatColor=<1,1,0,0.8>;
    #break
  #case(3)
    #declare SofieStatus="Sofie Comm Volume"
		#declare SofieDapatColor=<1,0,0,0.8>;
    #break
#end    

#debug concat(SofieStatus,"\n")
#debug concat(CipsStatus,"\n")

#declare OrbitNorm=<0,0,1>;

#debug "Done parsing AimAttDerived5.inc"
