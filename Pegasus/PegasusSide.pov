#include "PegasusPos.inc"
#include "LocLook.inc"
#include "EarthMod5.inc"
#include "PovSolar/Math.inc"

#version unofficial MegaPov 1.0;

global_settings {exposure 1.6 max_trace_level 10}

#declare Timing=array[10] {
0,
10.13,	//Drop
19.43,	//First stage ignition
56.96,	//First stage burnout
66.29,	//Second stage ignition
103.64,   	//Second stage burnout
169.32,	        //Third stage ignition
206.69,  	//Third stage burnout
212.85,          //End of audio
99999
}

#macro Stage(Name,TStart,TEnd,StageObj,StagePos,StageVel,StagePoint,ExtraRot,RotCenter,ExtraTrans)
  #if(PegasusClock>TStart & PegasusClock<TEnd)
    #debug concat("Detaching ",Name,"\n")
    PrintNumber("TStart:    ",TStart)
    PrintNumber("PegasusLo: ",PegasusLo)
    PrintNumber("PegasusHi: ",PegasusHi)
    PrintNumber("Comp:      ",ceil(PegasusClock))
    #if(ceil(PegasusClock)<=ceil(TStart))
      //Transition from attached
      #debug "Transition\n"
      PrintVector("FPos: ",StagePos[PegasusHi])
      #local PosA=PegasusPos[PegasusLo];
      #local PosB=StagePos[PegasusHi];
      #local Pos1=Linterp(PegasusLo,PosA,PegasusHi,PosB,TStart);
      #local AttA=PegasusPoint[PegasusLo];
      #local AttB=StagePoint[PegasusHi];
      #local Att1=Linterp(PegasusLo,AttA,PegasusHi,AttB,TStart);
      #local TransLo=TStart;
      PrintVector("PosA: ",PosA)
      PrintVector("PosB: ",PosB)
      PrintVector("AttA: ",AttA)
      PrintVector("AttB: ",AttB)
    #else
      #debug "Not Transition\n"
      #local Pos1=StagePos[PegasusLo];
      #local Att1=StagePoint[PegasusLo];
      #local TransLo=PegasusLo;
    #end
    PrintNumber("TransLo: ",TransLo)
    #local Pos2=StagePos[PegasusHi];
    PrintVector("Pos1: ",Pos1)
    PrintVector("Pos2: ",Pos2)
    #local Att2=StagePoint[PegasusHi];
    PrintVector("Att1: ",Att1)
    PrintVector("Att2: ",Att2)
    #local SPos=LH(Linterp(TransLo,Pos1,PegasusHi,Pos2,PegasusClock));
    #local SAtt=vnormalize(LH(Linterp(TransLo,Att1,PegasusHi,Att2,PegasusClock)));
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

#declare Events=array[10] {
-10
0,	//Drop
5,	//First stage ignition
73.6	//First stage burnout
95.3	//Second stage ignition
164.7	//Second stage burnout
554.99	//Third stage ignition
623.49	//Third stage burnout
700      //End of audio
99999
}

#declare MusicClock=Timing[8]*clock;
PrintNumber("MusicClock: ",MusicClock)
#local i=9;
#while(Timing[i]>MusicClock) 
  #local i=i-1;
#end
PrintNumber("Timing[i]: ",Timing[i])
PrintNumber("Timing[i+1]: ",Timing[i+1])
PrintNumber("Events[i]: ",Events[i])
PrintNumber("Events[i+1]: ",Events[i+1])
#local PegasusClock=Linterp(Timing[i],Events[i],Timing[i+1],Events[i+1],MusicClock);
PrintNumber("PegasusClock: ",PegasusClock)

#declare FlameClock=PegasusClock;

#include "Pegasus.inc"

#if(PegasusClock<0)
  #declare PegasusLo=0;
  PrintNumber("PegasusLo: ",PegasusLo)
  #declare PegasusHi=0;
  PrintNumber("PegasusHi: ",PegasusHi)
#else
  #declare PegasusLo=floor(PegasusClock);
  PrintNumber("PegasusLo: ",PegasusLo)
  #declare PegasusHi=floor(PegasusClock)+1;
  PrintNumber("PegasusHi: ",PegasusHi)
#end

#macro LH(V)
  <V.x,V.z,V.y>
#end

#declare PlanePos=LH(PegasusPos[0]+PegasusVel[0]*PegasusClock);
#declare PlaneVel=LH(PegasusVel[0]);
#declare PlanePoint=LH(PegasusPoint[0]);
PrintVector("PlanePos: ",PlanePos)
PrintVector("PlaneVel: ",PlaneVel)
PrintVector("PlaneAtt: ",PlanePoint)

#if(PegasusClock>0)
  #declare Pos1=PegasusPos[PegasusLo];
  #declare Pos2=PegasusPos[PegasusHi];
  #declare Pos=LH(Linterp(PegasusLo,Pos1,PegasusHi,Pos2,PegasusClock));
  #declare Vel1=PegasusVel[PegasusLo];
  #declare Vel2=PegasusVel[PegasusHi];
  #declare Vel=LH(Linterp(PegasusLo,Vel1,PegasusHi,Vel2,PegasusClock));
  #declare Att1=PegasusPoint[PegasusLo];
  #declare Att2=PegasusPoint[PegasusHi];
  #declare Att=vnormalize(LH(Linterp(PegasusLo,Att1,PegasusHi,Att2,PegasusClock)));
#else
  #declare Pos=PlanePos;
  #declare Vel=PlaneVel;
  #declare Att=PlanePoint;
#end

#if(PegasusClock<12)
  #include "L1011.inc"
#end

PrintVector("Pos: ",Pos)
PrintVector("Vel: ",Vel)
PrintVector("Att: ",Att)

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

#declare RhoRel=Dens(Alt)/Dens(0);
PrintNumber("RhoRel: ",RhoRel)

background {color rgb <0,0.5,1>*RhoRel}

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
#declare N=vcross(R,vnormalize(Vel));
#declare NA=vcross(R,vnormalize(AirVel));
#declare NP=vcross(R,vnormalize(Att));
#declare T=vcross(R,N);
#declare TA=vcross(R,NA);
#declare TP=vcross(R,NP);

#declare AEarth=6378.137;
#declare BEarth=6356.75231;
#declare Look=Pos+Att*8.7;
#declare CamLoc=Look+NA*50+R*2;
#declare Angle=atan(4/3);
#declare ThetaE=PegasusClock*(360/86164.09);
#declare CamLoc=CamLoc/1000;
#declare CamLoc=vrotate(CamLoc,y*ThetaE);
union {
  EarthMod()
  scale 1000
  rotate -y*ThetaE
  translate -Pos
}
#declare CamLoc=vrotate(CamLoc,-y*ThetaE);
#declare CamLoc=CamLoc*1000;

object {
  Pegasus
  LocationLookAt(<0,0,0>,Att,vnormalize(Pos))
}
#ifdef(Pegasus1) Stage("Stage 1",       80,  100,Pegasus1,FSPos,FSVel,FSPoint,<0,0,0>,<0,0,0>,<0,0,0>) #end
Stage("Interstage 1",  96,  110,Pegasus1Inter,IPos,IVel,IPoint,<0,0,0>,<0,0,0>,<0,0,0>)
Stage("Left Fairing", 110.6,130,PegasusFairingLeft,FPos,FVel,FPoint,<0,0,0>,<0,0,0>,<1,0,-1>*10*(1-exp((PegasusClock-110.6)/2)))
Stage("Right Fairing",110.6,130,PegasusFairingRight,FPos,FVel,FPoint,<0,0,0>,<0,0,0>,<1,0,1>*10*(1-exp((PegasusClock-110.6)/2)))
Stage("Stage 2",      170,  200,Pegasus2,SSPos,SSVel,SSPoint,<0,0,0>,<0,0,0>,<0,0,0>)

#ifdef(L1011)
object {
  L1011
  translate x*5
  LocationLookAt(PlanePos-Pos,PlanePoint+PlanePos-Pos,vnormalize(PlanePos))
}
#end

camera {
  location CamLoc-Pos
  look_at Look-Pos
  sky Pos
  angle 45
}
