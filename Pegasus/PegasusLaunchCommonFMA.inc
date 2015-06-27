#include "KwanMath.inc"
#include "KeplerGaussFG.inc"
#include "Events FMA.inc"
#declare Stage1On=Events[1];
#declare Stage2On=Events[4];
#declare Stage3On=Events[8];
#declare Stage1Off=Events[2];
#declare Stage2Off=Events[6];
#declare Stage3Off=Events[9];
#declare FSSep=Events[3];
#declare ISep=Stage2On+0.3;
#declare SSSep=Events[7];
#declare FSep=Events[5];
#declare SCSep=Events[10];
#declare TSSep=SCSep;
#declare AEarth=6378137;
#declare FEarth=1/298.257223563;
#declare BEarth=AEarth*(1-FEarth);
#include "LocLook.inc"
#include "BlueMarbleJava.inc"
#include "The Big FMA Table.inc"
#declare VideoLength=250.25;
#declare FrameRate=30000/1001;
#declare NumFrames=VideoLength*FrameRate;
PrintNumber("NumFrames: ",NumFrames)
#version unofficial MegaPov 1.11;

#ifndef(Linear)
#declare Linear=0;
#end

global_settings {exposure 1.6 max_trace_level 50}

#declare Timing=array[10] {
0,
10.13,	//Drop
19.43,	//First stage ignition
56.96,	//First stage burnout
66.29,	//Second stage ignition
103.64,	//Second stage burnout
169.32, //Third stage ignition
206.69,	//Third stage burnout
239.81, //Separation
VideoLength
}

#declare Events=array[10] {
-10
0,	//Drop
Stage1On,	  //First stage ignition
Stage1Off,	//First stage burnout
Stage2On, 	//Second stage ignition
Stage2Off,	//Second stage burnout
Stage3On, 	//Third stage ignition
Stage3Off,	//Third stage burnout
TSSep,	    //Separation
(Linterp(Timing[7],Stage3Off,Timing[8],TSSep,VideoLength))
}

PrintNumber("Last Event: ",Events[9])

#macro FindTPIR(A,X)
  //find the value in A closest to X without going over, return its array index
	//Assumes A is sorted ascending
  #local i=dimension_size(A,1)-1;
  #while(A[i]>X) 
    #local i=i-1;
  #end
	(i)
#end

#macro FindTPIR2(A,I,X)
  //find the value in A[:][I] closest to X without going over, return its array index
	//Assumes A is sorted ascending
  #local i=dimension_size(A,1)-1;
  #while(A[i][I]>X) 
    #local i=i-1;
  #end
	(i)
#end

#ifndef(ClockMode) #declare ClockMode=0; #end

#macro CalcMusicClock(klock)
  #local M_C=VideoLength*klock;
  PrintNumber("MusicClock: ",M_C)
  (M_C)
#end

#macro CalcPegasusClock(klock)
  #local MC=CalcMusicClock(klock);
  #local i=FindTPIR(Timing,MC);
  PrintNumber("Timing[i]: ",Timing[i])
  PrintNumber("Timing[i+1]: ",Timing[i+1])
  PrintNumber("Events[i]: ",Events[i])
  PrintNumber("Events[i+1]: ",Events[i+1])
  #local PC=Linterp(Timing[i],Events[i],Timing[i+1],Events[i+1],MC);
  PrintNumber("PegasusClock: ",PC)
  (PC)
#end

#if(ClockMode=0)
  #declare MusicClock=CalcMusicClock(clock);
  #declare PegasusClock=CalcPegasusClock(clock);
  PrintNumber("PegasusClock: ",PegasusClock)
#else
  #declare PegasusClock=clock;
  PrintNumber("PegasusClock: ",PegasusClock)
  #local i=FindTPIR(Events,PegasusClock);
  PrintNumber("Events[i]: ",Events[i])
  PrintNumber("Events[i+1]: ",Events[i+1])
#end

#declare FairingDeploy=(PegasusClock>FSep);
PrintNumber("FairingDeploy: ",FairingDeploy)	

#declare FlameClock=PegasusClock;
PrintNumber("FlameClock: ",FlameClock)
#local i=FindTPIR(Events,PegasusClock);
#if(i=2 | i=3) #declare LitStage=1; #declare TailOffTau=1; #end
#if(i=4 | i=5) #declare LitStage=2; #declare TailOffTau=3; #end
#if(i=6 | i=7) #declare LitStage=3; #declare TailOffTau=3; #end
#if(i=3 | i=5 | i=7) 
  #declare TailOffTime=PegasusClock-Events[i];
#else
  #declare TailOffTime=0;
#end  
PrintNumber("Here! ",0)

#macro LH(V)
  <V.x,V.z,V.y>
#end

#macro Transform(Row,Vec)
  (LH(<TheBigSITable[Row][67]*Vec.x+TheBigSITable[Row][70]*Vec.y+TheBigSITable[Row][73]*Vec.z,
       TheBigSITable[Row][68]*Vec.x+TheBigSITable[Row][71]*Vec.y+TheBigSITable[Row][74]*Vec.z,
       TheBigSITable[Row][69]*Vec.x+TheBigSITable[Row][72]*Vec.y+TheBigSITable[Row][75]*Vec.z>))
#end		

#macro GetT(Row) 
  (TheBigSITable[Row][0])
#end

#macro GetPos(Row) 
  (LH(<TheBigSITable[Row][17],TheBigSITable[Row][18],TheBigSITable[Row][19]>))
#end

#macro GetVel(Row) 
  (LH(<TheBigSITable[Row][20],TheBigSITable[Row][21],TheBigSITable[Row][22]>))
#end

#macro GetPegasusState(PegClock,Pos,Vel,Nose,Tail)
  #declare Pos0=GetPos(0);
  PrintVector("Pos0: ",Pos0)
  #declare Vel0=GetVel(0);
  PrintVector("Vel0: ",Vel0)
  #declare Nose0=Transform(0,x);
  PrintVector("Nose0: ",Nose0)
  #declare Tail0=Transform(0,-z);
  PrintVector("Tail0: ",Tail0)
  #declare PlanePos=Pos0+Vel0*PegClock;
  #declare PlaneVel=Vel0;
  #declare PlaneNose=Nose0;
  #declare PlaneTail=Tail0;
  PrintVector("PlanePos:  ",PlanePos)
  PrintVector("PlaneVel:  ",PlaneVel)
  PrintVector("PlaneNose: ",PlaneNose)
  PrintVector("PlaneTail: ",PlaneTail)
  #declare PlaneLLA=xyz2lla(PlanePos/AEarth,FEarth); 
  #declare PlaneLLA=<PlaneLLA.x,PlaneLLA.y,PlaneLLA.z*AEarth>; 
  #declare PlaneAlt=PlaneLLA.z;
  PrintVector("PlaneLLA: ",PlaneLLA)
  #if(PegClock>0)
    #local TLoI=FindTPIR2(TheBigSITable,0,PegClock);
    #local TMiI=TLoI+1;
    #local TLo=TheBigSITable[TLoI][0];
    #local TMi=TheBigSITable[TMiI][0];
    #local PosLo=GetPos(TLoI);
    PrintVector("PosLo: ",PosLo)
    #local PosMi=GetPos(TMiI);
    PrintVector("PosMi: ",PosMi)
    #local VelLo=GetVel(TLoI);
    #local VelMi=GetVel(TMiI);
    #local NoseLo=Transform(TLoI,x);
    #local NoseMi=Transform(TMiI,x);
    #local TailLo=Transform(TLoI,-z);
    #local TailMi=Transform(TMiI,-z);
    #switch(PegClock)
      #range(0,60)
        #local THiI=TMiI+1;
        #local THi=TheBigSITable[THiI][0];
        #local PosHi=GetPos(THiI);
        #local VelHi=GetVel(THiI);
        #declare Pos=Quadterp(TLo,PosLo,TMi,PosMi,THi,PosHi,PegClock);
        #declare Vel=Quadterp(TLo,VelLo,TMi,VelMi,THi,VelHi,PegClock);
        #break
      #range(60,99999)
        #declare Pos=Linterp(TLo,PosLo,TMi,PosMi,PegClock);
        #declare Vel=Linterp(TLo,VelLo,TMi,VelMi,PegClock);
        #break
    #end
    #declare Nose=vnormalize(Linterp(TLo,NoseLo,TMi,NoseMi,PegClock));
    #declare Tail=vnormalize(Linterp(TLo,TailLo,TMi,TailMi,PegClock));
  #else
    #declare Pos=PlanePos;
    #declare Vel=PlaneVel;
    #declare Nose=PlaneNose;
    #declare Tail=PlaneTail;
  #end
  #declare WindVec=<0,7.2921158553e-5,0>;
  #declare Wind=vcross(Pos,WindVec);
  PrintVector("Wind: ",Wind)
  #declare AirVel=Vel-Wind;
  PrintVector("AirVel: ",AirVel)
	#declare AoA=degrees(vangle(Nose,AirVel));
	PrintNumber("AoA: ",AoA)
  #declare LLA=xyz2lla(Pos/AEarth,FEarth);
  #declare LLA=<LLA.x,LLA.y,LLA.z*AEarth>;
  #declare Alt=LLA.z;
  PrintVector("LLA: ",LLA)
	#declare AltRel=Alt/12000;
  #declare RhoRel=Dens(Alt)/Dens(0);
	#declare FlameAtmDens=Dens(Alt)/Dens(12000);
	#declare FlameAngle=Linterp(0,0,1,AoA,FlameAtmDens);
  PrintNumber("RhoRel: ",RhoRel)
#end

#if(PegasusClock<60)
  #include "L1011.inc"
#end

#declare Pos=<0,0,0>;
#declare Vel=<0,0,0>;
#declare Nose=<0,0,0>;
#declare Tail=<0,0,0>;

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

light_source {
  <1e6,0,0>
  color rgb 1.5
  rotate -y*(53.68405-180)
}

#declare ThetaE=PegasusClock*(360/86164.09);

#macro Earth(CamLoc,Look,Angle)
  #local LCamLoc=CamLoc;
  #local LCamLoc=vrotate(LCamLoc,y*ThetaE);
	#local Sky=vnormalize(Pos);
	PrintNumber("Alt:          ",Alt)
	PrintNumber("vlength(Pos): ",vlength(Pos))
	#local RadHere=vlength(Pos)-Alt;
	PrintNumber("RadHere:      ",RadHere)
	#local HorizonDist=sqrt(pow(vlength(Pos),2)-pow(RadHere,2));
	PrintNumber("HorizonDist:  ",HorizonDist)
	#local HorizonAngle=atan2(HorizonDist,RadHere);
	PrintNumber("HorizonAngle: ",HorizonAngle)
	#local SkyColor=<0,0.5,1>;
	#declare RhoAlt=Dens(Alt)/Dens(0);
	cone {
	  -Pos,0,-Pos+Sky*(AEarth+100000)*cos(HorizonAngle),(AEarth+100000)*sin(HorizonAngle)
		open
		hollow
		no_shadow
		finish {
		  ambient 1
			diffuse 0
		}
		pigment {
		  onion
			color_map {
      #local I=0;
			[0 color rgb SkyColor]
			#while(I<200000)
			  #local RhoLevel=Dens(I)/Dens(0);
			  [(AEarth+I)/(AEarth+200000) color rgb max(RhoLevel,RhoAlt)*SkyColor]
  			#local I=I+1000;
			#end
		  }
			scale <1,1-FEarth,1>*(AEarth+200000)
			translate -Pos
		}
  }
	background {color rgb RhoAlt*SkyColor}
  #ifdef(Quick)
  	sphere {
    	0,1
    	scale <AEarth,BEarth,AEarth>
    	translate -Pos
			pigment {color rgb<0,0,1>}
  	}
	#else
  	union {
    	EarthMod(LCamLoc,Look,Angle)
    	rotate -y*ThetaE
    	translate -Pos
  	}
	#end
#end

#macro Stage(Obj,PegTime,DropTime,EjectVel,ExtraRot,CoR)
  #if(PegTime>=DropTime)
	  PrintNumber("PegTime:  ",PegTime)
	  PrintNumber("DropTime: ",DropTime)
		PrintNumber("DelTime:  ",PegTime-DropTime)
    #local SPos=<0,0,0>;
    #local SVel=<0,0,0>;
    #local SNose=<0,0,0>;
    #local STail=<0,0,0>;
    GetPegasusState(DropTime,SPos,SVel,SNose,STail)
		PrintVector("SPos:  ",SPos)
		PrintVector("SVel:  ",SVel)
		PrintVector("SNose: ",SNose)
		PrintVector("STail: ",STail)
	  #local SWing=vcross(SNose,STail);
		PrintVector("SWing: ",SWing)
  	#local SVelEject=EjectVel.x*SNose+EjectVel.y*SWing+EjectVel.z*STail;
		PrintVector("SVelEject: ",SVelEject)
	  #local SVel=SVel+SVelEject;
		#local SPos2=<0,0,0>;
		#local SVel2=<0,0,0>;
		#declare DUinSU=6378137;
    KeplerFG(SPos,SVel,(PegTime-DropTime),3.986004415e14,SPos2,SVel2)
    PrintVector("SPos2: ",SPos2)
    PrintVector("SVel2: ",SVel2)
  	object {
	    Obj
		  translate -CoR
  		rotate ExtraRot*(PegTime-DropTime)
	  	translate CoR
  		LocationLookAt(SPos2-Pos,SNose+SPos2-Pos,STail)
		}
	#end
#end

#macro PowerStage(Obj,PegTime,DropTime,EjectVel,Acc,ExtraRot,CoR)
  #if(PegTime>=DropTime)
		#local T=(PegTime-DropTime);
		#local SPos2=EjectVel*T+Acc*T*T/2;
		PrintVector("SPos2: ",SPos2)
  	object {
	    Obj
		  translate -CoR
  		rotate ExtraRot*T
	  	translate CoR
			translate SPos2
  		LocationLookAt(<0,0,0>,Nose,Tail)
		}
	#end
#end

#macro PowerStage2(Obj,PegTime,DropTime,IgnTime,EjectVel,Acc,ExtraRot,CoR)
  #if(PegTime<IgnTime)
	  PowerStage(Obj,PegTime,DropTime,EjectVel,0,ExtraRot,CoR)
	#else
  	#local T1=(IgnTime-DropTime);
		#local T2=(PegTime-IgnTime);
		#local T=T1+T2;
	  #local SPos2=EjectVel*T+Acc*T2*T2/2;
  	PrintVector("SPos2: ",SPos2)
   	object {
      Obj
	    translate -CoR
   		rotate ExtraRot*T
	   	translate CoR
	  	translate SPos2
  	  LocationLookAt(<0,0,0>,Nose,Tail)
  	}
	#end
#end

#macro Camera(CamLoc,Look,SkyN,SkyR,SkyT,Angle)
  PrintVector("Pos in Camera:",Pos)
  PrintVector("CamLoc: ",CamLoc)
  PrintVector("Look: ",Look)
  PrintNumber("Angle: ",Angle)
  camera {
    up y
		#if(image_width=720)
		  right x*4/3
	  #else
      right x*(image_width/image_height)
		#end
    location CamLoc-Pos
    look_at Look-Pos
    sky vnormalize(NA*SkyN+R*SkyR+TA*SkyT)
  	angle degrees(Angle)
  }
#end

GetPegasusState(PegasusClock,Pos,Vel,Nose,Tail)

#declare WindVec=<0,7.2921158553e-5,0>;
#declare Wind=vcross(Pos,WindVec);
PrintVector("Wind: ",Wind)
#declare AirVel=Vel-Wind;
PrintVector("AirVel: ",AirVel)

#declare R=vnormalize(Pos);
#declare N=vnormalize(vcross(R,vnormalize(Vel)));
#declare NA=vnormalize(vcross(R,vnormalize(AirVel)));
//#declare NDeflect=degrees(vangle(N,NA));
#declare NP=vnormalize(vcross(R,vnormalize(Nose)));
#declare T=vnormalize(vcross(N,R));
#declare TA=vnormalize(vcross(NA,R));
#declare TP=vnormalize(vcross(NP,R));

#declare LFinCommand=0;
#declare RFinCommand=0;
#declare VFinCommand=0;
#declare AtmDens=RhoRel;
#include "Pegasus.inc"

#if(PegasusClock<TSSep)

#ifdef(Pegasus1)
PowerStage2(Pegasus1,           PegasusClock,FSSep,Stage2On,<-4,0,0>,<-30,0,0>,<0,0,10>,<0,0,0>)
#end
PowerStage2(Pegasus1Inter,      PegasusClock,ISep, ISep,    <0,0,0>, <-20,0,0>,<2,4,6>,<10.40,0,0>)
PowerStage2(PegasusFairingRight,PegasusClock,FSep, FSep,    <3,0,-3>,<-30,0,0>,<0, 30,0>,   <0,0,0>)
PowerStage2(PegasusFairingLeft, PegasusClock,FSep, FSep,    <3,0, 3>, <-30,0,0>,<0,-30,0>,   <0,0,0>)
PowerStage2(Pegasus2,           PegasusClock,SSSep,Stage3On,<-1,0,0>,<-25,0,0>,<0,0,0>,   <0,0,0>)
PowerStage2(Pegasus3,           PegasusClock,TSSep,99999,<-1,0,0>,<-25,0,0>,<0,0,0>,   <0,0,0>)

GetPegasusState(PegasusClock,Pos,Vel,Nose,Tail)

#declare WindVec=<0,7.2921158553e-5,0>;
#declare Wind=vcross(Pos,WindVec);
PrintVector("Wind: ",Wind)
#declare AirVel=Vel-Wind;
PrintVector("AirVel: ",AirVel)

#declare R=vnormalize(Pos);
#declare N=vnormalize(vcross(R,vnormalize(Vel)));
#declare NA=vnormalize(vcross(R,vnormalize(AirVel)));
//#declare NDeflect=degrees(vangle(N,NA));
#declare NP=vnormalize(vcross(R,vnormalize(Nose)));
#declare T=vnormalize(vcross(N,R));
#declare TA=vnormalize(vcross(NA,R));
#declare TP=vnormalize(vcross(NP,R));

PrintVector("Pos:  ",Pos)
PrintVector("Vel:  ",Vel)
PrintVector("Nose: ",Nose)
PrintVector("Tail: ",Tail)



object {
  Pegasus
  LocationLookAt(<0,0,0>,Nose,Tail)
}

#else
  #declare NoseAim=<0,0,0>;
  #declare TailAim=<0,0,0>;
  GetPegasusState(TSSep,Pos,Vel,NoseAim,TailAim)
  GetPegasusState(PegasusClock,Pos,Vel,Nose,Tail)

  #declare WindVec=<0,7.2921158553e-5,0>;
  #declare Wind=vcross(Pos,WindVec);
  PrintVector("Wind: ",Wind)
  #declare AirVel=Vel-Wind;
  PrintVector("AirVel: ",AirVel)

  #declare R=vnormalize(Pos);
  #declare N=vnormalize(vcross(R,vnormalize(Vel)));
  #declare NA=vnormalize(vcross(R,vnormalize(AirVel)));
  //#declare NDeflect=degrees(vangle(N,NA));
  #declare NP=vnormalize(vcross(R,vnormalize(Nose)));
  #declare T=vnormalize(vcross(N,R));
  #declare TA=vnormalize(vcross(NA,R));
  #declare TP=vnormalize(vcross(NP,R));

  PrintVector("Pos:  ",Pos)
  PrintVector("Vel:  ",Vel)
  PrintVector("Nose: ",Nose)
  PrintVector("Tail: ",Tail)



  object {
    Pegasus3
    translate x*(-14.5)
    LocationLookAt(<0,0,0>,Nose,Tail)
    translate NoseAim*(SCSep-PegasusClock)
  }
  object {
    Aim
    rotate z*90 translate 14.975*x
    translate x*(-14.5)
    LocationLookAt(<0,0,0>,NoseAim,TailAim)
  }

#end


#ifdef(L1011)
object {
  L1011
  LocationLookAt(PlanePos-Pos,PlaneNose+PlanePos-Pos,PlaneTail)
}
#end

