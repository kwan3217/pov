#declare Stage1On=  5.00;
#declare Stage2On= 95.30;
#declare Stage3On=540.73;
#declare Stage1Off= 73.60;
#declare Stage2Off=164.70;
#declare Stage3Off=609.23;
#declare FSSep=95.0;
#declare SSSep=510.0;
#declare FSep=115.0;
#include "LocLook.inc"
#declare AEarth=6378.137;
#declare BEarth=6378.137;
#include "BlueMarbleJava.inc"
#include "KwanMath.inc"
#include "PegasusState0.inc"
#declare Fps=24; //Frames per second in data file
#declare Sps=10; //Seconds per second of data file

#version unofficial MegaPov 1.11;

#ifndef(Linear)
#declare Linear=0;
#end

global_settings {exposure 1.6 max_trace_level 10}

#declare Events=array[10] {
-10
0,	//Drop
Stage1On,	  //First stage ignition
Stage1Off,	//First stage burnout
Stage2On, 	//Second stage ignition
Stage2Off,	//Second stage burnout
Stage3On, 	//Third stage ignition
Stage3Off,	//Third stage burnout
700,        //End of audio
99999
}

#declare Timing=array[10] {
0,
10.13,	//Drop
19.43,	//First stage ignition
56.96,	//First stage burnout
66.29,	//Second stage ignition
103.64,	//Second stage burnout
169.32, //Third stage ignition
206.69,	//Third stage burnout
212.85, //End of audio
99999
}

#macro FindTPIR(A,X)
  //find the value in A closest to X without going over, return its array index
	//Assumes A is sorted ascending
  #local i=dimension_size(A,1)-1;
  #while(A[i]>X) 
    #local i=i-1;
  #end
	(i)
#end

#macro Stage(Name,T,StageObj,StagePos,StageVel,StagePoint,ExtraRot,RotCenter,ExtraTrans)
  #local TStart=T[0];
	#local TEnd=T[dimension_size(T,1)-1];
  #if(PegasusClock>TStart & PegasusClock<TEnd)
    #debug concat("Detaching ",Name,"\n")
    PrintNumber("TStart:    ",TStart)
  	#local StageLoI=FindTPIR(T,PegasusClock);
  	#local StageMiI=StageLoI+1;
    #local StageLo=T[StageLoI];
    #local StageMi=T[StageMiI];
    #local Pos1=StagePos[StageLoI];
    #local Att1=StagePoint[StageLoI];
    #local Pos2=StagePos[StageMiI];
    #local Att2=StagePoint[StageMiI];
    PrintNumber("StageLoI: ",StageLoI)
    PrintNumber("StageMiI: ",StageMiI)
    PrintNumber("StageLo: ",StageLo)
    PrintNumber("StageMi: ",StageMi)
    PrintVector("Pos1: ",Pos1)
    PrintVector("Pos2: ",Pos2)
    PrintVector("Att1: ",Att1)
    PrintVector("Att2: ",Att2)
    #if(PegasusClock<10)
    	#local StageHiI=StageMiI+1;
      #local StageHi=T[StageHiI];
      #local Pos3=StagePos[StageHiI];
      #local Att3=StagePoint[StageHiI];
      PrintNumber("StageHiI: ",StageHiI)
      PrintNumber("StageHi: ",StageHi)
      PrintVector("Pos3: ",Pos3)
      PrintVector("Att3: ",Att3)
      #local SPos=LH(Quadterp(StageLo,Pos1,StageMi,Pos2,StageHi,Pos3,PegasusClock));
      #local SAtt=vnormalize(LH(Quadterp(StageLo,Att1,StageMi,Att2,StageHi,Att3,PegasusClock)));
		#else
      #local SPos=LH(Linterp(StageLo,Pos1,StageMi,Pos2,PegasusClock));
      #local SAtt=vnormalize(LH(Linterp(StageLo,Att1,StageMi,Att2,PegasusClock)));
		#end
    PrintVector("StagePos: ",SPos)
    PrintVector("Dist:     ",Pos-SPos)
    PrintVector("StageAtt: ",SAtt)
    object {
      StageObj
      translate -RotCenter
      rotate ExtraRot
      translate RotCenter+ExtraTrans
      LocationLookAt(SPos-Pos,SAtt+SPos-Pos,vnormalize(SPos))
    }
  #else
    #debug concat("Not Detaching ",Name,"\n")
  #end
#end

#ifndef(ClockMode) #declare ClockMode=0; #end
#if(ClockMode=0)
  #declare MusicClock=Timing[8]*clock;
  PrintNumber("MusicClock: ",MusicClock)
  #local i=FindTPIR(Timing,MusicClock);
  PrintNumber("Timing[i]: ",Timing[i])
  PrintNumber("Timing[i+1]: ",Timing[i+1])
  PrintNumber("Events[i]: ",Events[i])
  PrintNumber("Events[i+1]: ",Events[i+1])
  #declare PegasusClock=Linterp(Timing[i],Events[i],Timing[i+1],Events[i+1],MusicClock);
  PrintNumber("PegasusClock: ",PegasusClock)
#else
  #declare PegasusClock=clock;
  PrintNumber("PegasusClock: ",PegasusClock)
  #local i=FindTPIR(Events,PegasusClock);
  PrintNumber("Events[i]: ",Events[i])
  PrintNumber("Events[i+1]: ",Events[i+1])
#end

#if(PegasusClock<(FSep-2))
  #declare FairingDeploy=0;
#else
  #declare FairingDeploy=Linterp(FSep-2,0,FSep,1,PegasusClock);
#end
PrintNumber("FairingDeploy: ",FairingDeploy)	

#declare FlameClock=PegasusClock;
#if(i=2) #declare LitStage=1; #end
#if(i=4) #declare LitStage=2; #end
#if(i=6) #declare LitStage=3; #end

#if(PegasusClock<0)
  #declare PegasusLoI=0;
  #declare PegasusMiI=0;
  #declare PegasusHiI=0;
#else
  #declare PegasusLoI=floor(PegasusClock*Fps);
  #declare PegasusMiI=PegasusLoI+1;
#end

#declare PegasusLo=PegasusLoI/Fps;
#declare PegasusMi=PegasusMiI/Fps;
PrintNumber("PegasusLoI: ",PegasusLoI)
PrintNumber("PegasusMiI: ",PegasusMiI)
PrintNumber("PegasusLo: ",PegasusLo)
PrintNumber("PegasusMi: ",PegasusMi)

#macro LH(V)
  <V.x,V.z,V.y>
#end

#declare PlanePos=LH(Position[0]+Velocity[0]*PegasusClock);
#declare PlaneVel=LH(Velocity[0]);
#declare PlaneNose=LH(Nose[0]);
#declare PlaneTail=LH(Tail[0]);

#declare FileIdx=floor(PegasusLoI/(Fps*Sps));
#declare FileI=PegasusLoI-FileIdx*Fps*Sps;
PrintNumber("FileIdx: ",FileIdx)
PrintNumber("FileI:   ",FileI)
#if(FileIdx>0)
  #include concat("PegasusState",str(FileIdx,0,0),".inc")
#end

#declare LFinCommand=LFinCmd[FileI];
#declare RFinCommand=RFinCmd[FileI];
#declare VFinCommand=VFinCmd[FileI];
#include "Pegasus.inc"

PrintVector("PlanePos:  ",PlanePos)
PrintVector("PlaneVel:  ",PlaneVel)
PrintVector("PlaneNose: ",PlaneNose)
PrintVector("PlaneTail: ",PlaneTail)

#if(PegasusClock>0)
  #declare Pos=LH(Position[FileI]);
  #declare Vel=LH(Velocity[FileI]);
  #declare Nose=LH(Nose[FileI]);
  #declare Tail=LH(Tail[FileI]);
#else
  #declare Pos=PlanePos;
  #declare Vel=PlaneVel;
  #declare Nose=PlaneNose;
  #declare Tail=PlaneTail;
#end

#if(PegasusClock<20)
  #include "L1011.inc"
#end

PrintVector("Pos:  ",Pos)
PrintVector("Vel:  ",Vel)
PrintVector("Nose: ",Nose)
PrintVector("Tail: ",Tail)

#declare LLA=xyz2lla(Pos/6378137,1/298.257223563);
PrintVector("LLA: ",LLA)
#declare Alt=LLA.z*6378137;
PrintNumber("Alt: ",Alt)

#macro Dens(h)
  #if(h<11000) 
    #local T = 15.04 - 0.00649 * h+273.1;
    #local p= 101.29 * pow((T / 288.08),5.256);
  #else
    #if(h<25000)
      #local T = -56.46+273.1;
      #local p = 22.65 * exp (1.73 - 0.000157 * h);
    #else
      #if(h<100000)
        #local T = -131.21 + 0.00299 * h+273.1;
        #local p = 2.488 * pow(T / 216.6,-11.388);
      #else
        #local T=0;
        #local p=0;
      #end
    #end
  #end
  
  #if(T>0)
    #local rho = p / (0.2869 * T);
  #else
    #local rho=0;
  #end
  (rho)
#end

#declare WindVec=<0,7.2921158553e-5,0>;
#declare Wind=vcross(Pos,WindVec);
PrintVector("Wind: ",Wind)
#declare AirVel=Vel-Wind;
PrintVector("AirVel: ",AirVel)

light_source {
  <1e6,0,0>
  color rgb 1.5
  rotate y*122.5
}

#declare R=vnormalize(Pos);
#declare N=vnormalize(vcross(R,vnormalize(Vel)));
#declare NA=vnormalize(vcross(R,vnormalize(AirVel)));
#declare NDeflect=degrees(vangle(N,NA));
#declare NP=vnormalize(vcross(R,vnormalize(Nose)));
#declare T=vnormalize(vcross(N,R));
#declare TA=vnormalize(vcross(NA,R));
#declare TP=vnormalize(vcross(NP,R));

#declare AEarth=6378.137;
#declare BEarth=6356.75231;
#declare ThetaE=PegasusClock*(360/86164.09);

#macro Earth(CamLoc,Look,Angle)
  #local LCamLoc=CamLoc/1000;
  #local LCamLoc=vrotate(LCamLoc,y*ThetaE);
  #ifdef(Quick)
  	sphere {
    	0,1
    	scale 1000*<AEarth,BEarth,AEarth>
    	translate -Pos
			pigment {color rgb<0,0,1>}
  	}
	#else
  	union {
    	EarthMod(LCamLoc,Look,Angle)
    	scale 1000
    	rotate -y*ThetaE
    	translate -Pos
  	}
	#end
#end

#macro Camera(CamLoc,Look,SkyN,SkyR,SkyT,Angle)
  PrintVector("Pos in Camera:",Pos)
  PrintVector("CamLoc: ",CamLoc)
  PrintVector("Look: ",Look)
  PrintNumber("Angle: ",Angle)
  camera {
    location CamLoc-Pos
    look_at Look-Pos
    sky vnormalize(NA*SkyN+R*SkyR+TA*SkyT)
  	angle degrees(Angle)
  }
  #declare RhoRel=Dens(Alt)/Dens(0);
  PrintNumber("RhoRel: ",RhoRel)

  background {color rgb <0,0.5,1>*RhoRel}
#end

object {
  Pegasus
  LocationLookAt(<0,0,0>,Nose,Tail)
}

#ifdef(L1011)
object {
  L1011
  LocationLookAt(PlanePos-Pos,PlaneNose+PlanePos-Pos,PlaneTail)
}
#end

