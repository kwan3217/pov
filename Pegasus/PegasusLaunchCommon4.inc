#include "KwanMath.inc"
#include "PovSolar/KeplerGaussFG.inc"
#include "Events.inc"
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
#declare AEarth=6378137;
#declare BEarth=6356752.31;
PrintNumber("BEarth: ",BEarth)
#declare FEarth=1/298.257223563;
#declare WEarth=7.2921158553e-5;
#declare WindVec=<0,WEarth,0>;
#declare BEarth=AEarth*(1-FEarth);
PrintNumber("BEarth: ",BEarth)
#include "LocLook.inc"
#include "BlueMarbleJava.inc"
#include "The Big SI Table.inc"
#include "Locations.inc"
#include "CALF Tracking.inc"

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
600,        //End of audio
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
  #declare PegasusLoI=FindTPIR2(CALFTracking,0,PegasusClock);
  #declare PegasusMiI=PegasusLoI+1;
#end

#declare PegasusLo=CALFTracking[PegasusLoI][0];
#declare PegasusMi=CALFTracking[PegasusMiI][0];
PrintNumber("PegasusLoI: ",PegasusLoI)
PrintNumber("PegasusMiI: ",PegasusMiI)
PrintNumber("PegasusLo: ",PegasusLo)
PrintNumber("PegasusMi: ",PegasusMi)

//Given station ECEF lat, lon, alt, time since drop, and
//      azimuth, elevation, and range from station,
//      calculate ECI location of rocket
#macro trackRocket(lat,lon,alt,time,az,el,range)
  #local lat=radians(lat);
	//Allow for the rotation of the Earth since drop
  #local lon=radians(lon)+time*WEarth;
	#local az=radians(az);
	#local el=radians(el);
	
	#local sta=lla2xyz(<lat,lon,alt/AEarth>,FEarth)*AEarth;
	
	//Station zenith vector
	#local sz=[cos(lat)*cos(lon),cos(lat)*sin(lon),sin(lat)]
	//Station east vector (Perpendicular to rotation axis and zenith)
	#local se=vcross([0,0,1],sz)
	#local se=se/vlength(se);
	//Station north vector (Perpendicular to zenith and east)
	#local sn=vcross(sz,se)
	#local sn=sn/vlength(sn)
	
	
  #local RocketPos=(se*sin(az)*cos(el)+sn*cos(az)*cos(el)+sz*sin(el))*range+sta;
	PrintVector("RocketPos: ",RocketPos)
	(RocketPos)
	
#end

#macro LH(V)
  <V.x,V.z,V.y>
#end

#macro Transform(Row,Vec)
  (LH(<TheBigSITable[Row][67]*Vec.x+TheBigSITable[Row][70]*Vec.y+TheBigSITable[Row][73]*Vec.z,
       TheBigSITable[Row][68]*Vec.x+TheBigSITable[Row][71]*Vec.y+TheBigSITable[Row][74]*Vec.z,
       TheBigSITable[Row][69]*Vec.x+TheBigSITable[Row][72]*Vec.y+TheBigSITable[Row][75]*Vec.z>))
#end		

#macro GetTrackPos(Row)
  (trackRocket(Locations[2][0],Locations[2][1],Locations[2][2],CALFTracking[Row][0],CALFTracking[Row][2],CALFTrackin[Row][1],CALFTracking[Row][4]

#macro GetPos(Row) 
  (LH(<TheBigSITable[Row][17],TheBigSITable[Row][18],TheBigSITable[Row][19]>))
#end

#macro GetVel(Row) 
  (LH(<TheBigSITable[Row][20],TheBigSITable[Row][21],TheBigSITable[Row][22]>))
#end

#declare Pos0=GetPos(0);
PrintVector("Pos0: ",Pos0)
#declare Vel0=GetVel(0);
PrintVector("Vel0: ",Vel0)
#declare Nose0=Transform(0,x);
PrintVector("Nose0: ",Nose0)
#declare Tail0=Transform(0,-z);
PrintVector("Tail0: ",Tail0)
#declare PlanePos=Pos0+Vel0*PegasusClock;
#declare PlaneVel=Vel0;
#declare PlaneNose=Nose0;
#declare PlaneTail=Tail0;


#declare LFinCommand=0;
#declare RFinCommand=0;
#declare VFinCommand=0;
#include "Pegasus.inc"

PrintVector("PlanePos:  ",PlanePos)
PrintVector("PlaneVel:  ",PlaneVel)
PrintVector("PlaneNose: ",PlaneNose)
PrintVector("PlaneTail: ",PlaneTail)

#macro GetPegasusState(PegClock,Pos,Vel,Nose,Tail)
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
		#if(PegClock>10000)
    	#local THiI=TMiI+1;
  		#local THi=TheBigSITable[THiI][0];
  		#local PosHi=GetPos(THiI);
  		#local VelHi=GetVel(THiI);
    	#declare Pos=Quadterp(TLo,PosLo,TMi,PosMi,THi,PosHi,PegClock);
    	#declare Vel=Quadterp(TLo,VelLo,TMi,VelMi,THi,VelHi,PegClock);
		#else
    	#declare Pos=Linterp(TLo,PosLo,TMi,PosMi,PegClock);
    	#declare Vel=Linterp(TLo,VelLo,TMi,VelMi,PegClock);
		#end
	  #declare Nose=vnormalize(Linterp(TLo,NoseLo,TMi,NoseMi,PegClock));
   	#declare Tail=vnormalize(Linterp(TLo,TailLo,TMi,TailMi,PegClock));
	#else
  	#declare Pos=PlanePos;
  	#declare Vel=PlaneVel;
  	#declare Nose=PlaneNose;
  	#declare Tail=PlaneTail;
	#end
#end

#if(PegasusClock<20)
  #include "L1011.inc"
#end

#declare Pos=<0,0,0>;
#declare Vel=<0,0,0>;
#declare Nose=<0,0,0>;
#declare Tail=<0,0,0>;

GetPegasusState(PegasusClock,Pos,Vel,Nose,Tail)

PrintVector("Pos:  ",Pos)
PrintVector("Vel:  ",Vel)
PrintVector("Nose: ",Nose)
PrintVector("Tail: ",Tail)

#declare LLA=xyz2lla(Pos/AEarth,FEarth);
PrintVector("LLA: ",LLA)
#declare Alt=LLA.z*AEarth;
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
  rotate -y*(53.68405-180)
}

#declare R=vnormalize(Pos);
#declare N=vnormalize(vcross(R,vnormalize(Vel)));
#declare NA=vnormalize(vcross(R,vnormalize(AirVel)));
//#declare NDeflect=degrees(vangle(N,NA));
#declare NP=vnormalize(vcross(R,vnormalize(Nose)));
#declare T=vnormalize(vcross(N,R));
#declare TA=vnormalize(vcross(NA,R));
#declare TP=vnormalize(vcross(NP,R));

#declare ThetaE=PegasusClock*(360/86164.09);

#macro Earth(CamLoc,Look,Angle)
  #local LCamLoc=CamLoc;
  #local LCamLoc=vrotate(LCamLoc,y*ThetaE);
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

object {
  Pegasus
  LocationLookAt(<0,0,0>,Nose,Tail)
}

#ifdef(Pegasus1)
Stage(Pegasus1,PegasusClock,FSSep,<-4,0,0>,<0,0,-30>,<0,0,0>)
#end
PowerStage(Pegasus1Inter,PegasusClock,ISep,<0,0,0>,<-20,0,0>,<20,40,60>,<10.40,0,0>)
PowerStage(PegasusFairingRight,PegasusClock,FSep,<5,-1,0>,<-30,0,0>,<0,0,0>,<0,0,0>)
PowerStage(PegasusFairingLeft,PegasusClock,FSep,<5,1,0>,<-30,0,0>,<0,0,0>,<0,0,0>)
PowerStage(Pegasus2,PegasusClock,SSSep,<-1,0,0>,<0,0,0>,<0,0,0>,<0,0,0>)

#ifdef(L1011)
object {
  L1011
  LocationLookAt(PlanePos-Pos,PlaneNose+PlanePos-Pos,PlaneTail)
}
#end

