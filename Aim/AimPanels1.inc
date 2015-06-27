#include "KwanMath.inc"
#declare AEarth=6378137;
#declare FEarth=1/298.257223563;
#declare BEarth=AEarth*(1-FEarth);
PrintNumber("BEarth: ",BEarth)
#ifndef(Lines) #declare Lines=0; #end
#include "LocLook.inc"
#declare UseStripe=Lines;
#include "BlueMarbleJava.inc"
#include "vec6.inc"
#include "quat6.inc"
#include "CommonVolumeArray.inc"
#ifndef(StartTime) #declare StartTime=-720; #end
#ifndef(EndTime)   #declare EndTime=   430; #end
#declare AimClock=Linterp(0,TermOverflight+StartTime,1,TermOverflight+EndTime,clock);
PrintNumber("AimClock: ",AimClock)
#declare MovieTime=62;
#declare Epoch=2454272.5;
#declare J2000=2451545;
#declare Epoch=Epoch-J2000;
#declare JD=Epoch+J2000+AimClock/86400;
#declare JDStart=Epoch+J2000+(TermOverflight+StartTime)/86400;
PrintNumber("JD: ",JD)
#declare VideoLength=120;
#declare FrameRate=30000/1001;
#declare NumFrames=VideoLength*FrameRate;
PrintNumber("NumFrames: ",NumFrames)
#version unofficial MegaPov 1.22;
///*
#declare CelestialSphereRad=4e6;
#declare StarRatio=image_width;
#include "Stars.inc"
//*/
#include "SunVec.inc"
#declare Hc=83000;
#declare Hoz=30000;
#declare FadeMinLat=radians(50);
#declare FadeMaxLat=radians(70);

#macro SecToJD(TSec)
  (Epoch+J2000+TSec/86400)
#end

global_settings {exposure 1.6 max_trace_level 50}

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

#macro LH(V)
  <V.x,V.z,V.y>
#end

//Quaternions are stored in the file as x,y,z,scalar body->inertial transformation
#macro QuatVecTransform(Q,V)
  #local e4=Q.t;
  #local e=<Q.x,Q.y,Q.z>;
  #local ev=vcross(e,V);	
  (V+2*(e4*vcross(e,V)+vcross(e,vcross(e,V))))
#end

#macro Transform(T,V)
	PrintNumber("T:   ",T)
  #local Row=FindTPIR2(Quat,0,T);
	PrintNumber("Row: ",Row)
  #local T0=Quat[Row  ][0];
	PrintNumber("T0:  ",T0)
  #local T1=Quat[Row+1][0];
	PrintNumber("T1:  ",T1)
  #local T2=Quat[Row+2][0];
	PrintNumber("T2:  ",T2)
  #local Q0=<Quat[Row  ][1],Quat[Row  ][2],Quat[Row  ][3],Quat[Row  ][4]>;
  PrintQuat("Q0: ",Q0)	
	#local e0=<Quat[Row  ][1],Quat[Row  ][2],Quat[Row  ][3]>;
  PrintVector("e0: ",e0)	
  #local Q1=<Quat[Row+1][1],Quat[Row+1][2],Quat[Row+1][3],Quat[Row+1][4]>;
  PrintQuat("Q1: ",Q1)	
	#local e1=<Quat[Row+1][1],Quat[Row+1][2],Quat[Row+1][3]>;
  PrintVector("e1: ",e1)	
	#if(vdot(e0,e1)<0) #local Q1=-Q1; #end
  PrintQuat("Q1: ",Q1)	
  #local Q2=<Quat[Row+2][1],Quat[Row+2][2],Quat[Row+2][3],Quat[Row+2][4]>;
  PrintQuat("Q2: ",Q2)	
	#local e2=<Quat[Row+2][1],Quat[Row+2][2],Quat[Row+2][3]>;
  PrintVector("e2: ",e2)	
	#if(vdot(e0,e2)<0) #local Q2=-Q2; #end
  PrintQuat("Q2: ",Q2)	
  #local Q=Quadterp(T0,Q0,T1,Q1,T2,Q2,T);
  PrintQuat("Q: ",Q)	
  (QuatVecTransform(Q,V))
#end		

#macro GetPos(T) 
  #local Row=FindTPIR2(Vec,0,T);
  #local T0=Vec[Row  ][0];
  #local T1=Vec[Row+1][0];
  #local T2=Vec[Row+2][0];
  #local R0=<Vec[Row  ][1],Vec[Row  ][2],Vec[Row  ][3]>;
  #local R1=<Vec[Row+1][1],Vec[Row+1][2],Vec[Row+1][3]>;
  #local R2=<Vec[Row+2][1],Vec[Row+2][2],Vec[Row+2][3]>;
  (LH(Quadterp(T0,R0,T1,R1,T2,R2,T)))
#end

#macro gmst(T)
  PrintNumber("JD: ",Epoch+J2000+T/86400)
  #local TT=(T/86400+Epoch)/36525;
  PrintNumber("TT: ",TT)
  #local thetag=(((-6.2e-6)*TT+0.093104)*TT+(876600*3600+8640184.812866)*TT)+67310.54841;
  #local thetag=mod(thetag ,86400);
  #local thetag=thetag/240;
  #local thetag=mod(thetag,360);
  (thetag)
#end

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

#ifdef(Stars)
  object {
    Stars
  }
#end


#declare ThetaE=gmst(AimClock);
#declare PMC_Clouds=texture {
  pigment {
    bozo
    turbulence 0.65
    octaves 6
    omega 0.7
    lambda 2
    color_map {
        [0.3 rgbf <1,1,1,0.5>]
        [0.7 rgbf <1,1,1,1>]
    }
    scale <6, 1, 6>
  }
  finish {ambient 0 brilliance 0}
}

#declare FalseColor_Clouds=texture {
  pigment {
    bozo
    turbulence 0.65
    octaves 6
    omega 0.7
    lambda 2
    color_map {
         [ 0.0 color rgb <1, 0, 0>         ]
         [ 0.1 color rgb <1, 0.5, 0>       ]
         [ 0.2 color rgb <1, 1, 0>         ]
         [ 0.3 color rgb <0, 1, 0>         ]
         [ 0.4 color rgb <0, 1, 1>         ]
         [ 0.5 color rgb <0, 0, 1>         ]
         [ 0.6 color rgb <0.25, 0, 0.5>    ]
         [ 0.7 color rgb <0, 0, 0>         ]
    }
    scale <6, 1, 6>
  }
  finish {ambient 0 brilliance 0}
}

#declare CloudDeckTex=texture {
  gradient y
  triangle_wave
  turbulence 0.2
  scale <10,1,10>
  texture_map {
    [sin(FadeMinLat) pigment {color rgbf 1} ]
    [sin(FadeMaxLat) PMC_Clouds scale <30,100,30>/(AEarth*2)*1000]
  }
  scale AEarth
  scale <1,2*BEarth/AEarth,1>
}

#declare FalseColorDeckTex=texture {
  gradient y
  triangle_wave
  turbulence 0.2
  scale <10,1,10>
  texture_map {
    [sin(FadeMinLat) pigment {color rgb <0,0,0>} ]
    [sin(FadeMaxLat) FalseColor_Clouds scale <30,100,30>/(AEarth*2)*1000]
  }
  scale AEarth
  scale <1,2*BEarth/AEarth,1>
}

#declare CloudSphere=sphere {
        0,1
       	scale <AEarth+Hc,BEarth+Hc,AEarth+Hc>
        texture {CloudDeckTex}
        hollow
        no_shadow
        double_illuminate
      }

#macro CipsClouds()
  sphere {
    0,1
    scale <AEarth+Hc+50,BEarth+Hc+50,AEarth+Hc+50>
    texture{CloudDeckTex rotate -y*ThetaE}
    hollow
    no_shadow
    double_illuminate
  }
#end

#macro Earth(CamLoc,Look,Angle)
  #local LCamLoc=CamLoc;
  #local LCamLoc=vrotate(LCamLoc,y*ThetaE);
	#local Sky=vnormalize(Pos);
  #ifdef(Quick)
  	sphere {
    	0,1
    	scale <AEarth,BEarth,AEarth>
    	translate -Pos
			pigment {color rgb<0,0,1>}
  	}
	#else
  	union {
      union {
      	EarthMod(LCamLoc,Look,Angle)
        object {CloudSphere}
     	  rotate -y*ThetaE
      }
      CipsClouds()
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
    up y
    #if(image_width=720)
      right x*4/3
    #else
      right x*(image_width/image_height)
    #end
    location CamLoc-Pos
    look_at Look-Pos
    sky vnormalize(N*SkyN+R*SkyR+T*SkyT)
    angle degrees(Angle)
  }
#end

#declare Pos=GetPos(AimClock)*1000;
PrintVector("Pos: ",Pos)
#declare Vel=GetPos(AimClock+1)*1000-Pos;
PrintVector("Vel: ",Vel)
#declare LLA=xyz2lla(Pos/AEarth,FEarth);
#declare LLA=<LLA.x,LLA.y,LLA.z*AEarth>;
#declare Alt=LLA.z;
PrintVector("LLA: ",LLA)
PrintNumber("Alt: ",Alt)

#declare R=vnormalize(Pos);
PrintVector("R: ",R)
#declare N=vnormalize(vcross(R,vnormalize(Vel)));
PrintVector("N: ",N)
#declare T=vnormalize(vcross(N,R));
PrintVector("T: ",T)
#declare Nose=LH(Transform(AimClock,<1,0,0>));
PrintVector("Nose: ",Nose)
#declare Wing=LH(Transform(AimClock,<0,1,0>));
PrintVector("Wing: ",Wing)
#declare Tail=LH(Transform(AimClock,<0,0,1>));
PrintVector("Tail: ",Tail)

#include "Aim.inc"

object {
  Aim
  translate y*0.4
  rotate x*180
  LocationLookAt(<0,0,0>,Nose,Tail)
}

sphere {
  0,radians(0.25)
  translate LH(SunVec(JD))*1
  scale 150e9
  pigment {color rgb <1,1,0>}
  finish {ambient 1 diffuse 0}
  no_shadow
}

#if(Lines)

#declare TransCipsHollowFOVCluster=difference {
  object {
    CipsHollowFOVCluster 
    translate y*0.4
    rotate x*180
    LocationLookAt(<0,0,0>,Nose,Tail)
  }
  plane {
    #declare b=asin((AEarth+Hc)/(AEarth+Alt));
    #declare Q=pow(AEarth+Hc,2)/(AEarth+Alt);
    Pos,Q
    translate -Pos
  }
}

#macro PastCipsFOV(T) 
  union {
    object {
      CipsSceneFOV
      translate y*0.4
      rotate x*180
    }
    #local ThisPos=Pos-GetPos(T)*1000;
    #local ThisNose=LH(Transform(T,<1e4,0,0>));
    #local ThisTail=LH(Transform(T,<0,0,1e4>));
    #fopen ouf "pastquat.txt" append
    #write( ouf, concat(date("%Y %b %d %H:%M:%S")," ",Host," Render - frame ",str(frame_number,0,0)," of ",str(final_frame,0,0),"\n",
                        "AimClock: ",str(AimClock,0,6),"\n",
                        "T:        ",str(T,0,6),"\n",
                        "ThisPos:  <",str(ThisPos.x,0,6),",", str(ThisPos.y,0,6),",", str(ThisPos.z,0,6), "> (length:",str(vlength(ThisPos),0,6),")\n",
                        "ThisNose: <",str(ThisNose.x,0,6),",",str(ThisNose.y,0,6),",",str(ThisNose.z,0,6),"> (length:",str(vlength(ThisNose),0,6),")\n",
                        "ThisTail: <",str(ThisTail.x,0,6),",",str(ThisTail.y,0,6),",",str(ThisTail.z,0,6),"> (length:",str(vlength(ThisTail),0,6),")\n"))
    #fclose ouf
    LocationLookAt(ThisPos,ThisNose+ThisPos,ThisTail+ThisPos)
  }
#end

#macro AllPastCipsFOV()
  #if(NumExp>0)
    #local I=0;
    #while(I<NumExp)
      PastCipsFOV(ExpTimes[I])
      #local I=I+1;
    #end
  #end
#end

#declare CipsState=0;
#declare CipsCadence=43;
#declare CipsStart=TermOverflight-CipsCadence*6;
#declare CipsEnd=  TermOverflight+CipsCadence*25;
#if(AimClock>CipsStart)
  #local CipsClock=AimClock-CipsStart;
  #declare NumExp=1+floor(CipsClock/CipsCadence);
  PrintNumber("NumExp: ",NumExp)
  #declare ExpTimes=array[NumExp];
  #local I=0;
  #while(I<NumExp)
    #declare ExpTimes[I]=CipsStart+CipsCadence*I;
    PrintNumber(concat("ExpTimes[",str(I,0,1),"]: "),ExpTimes[I])
    #local I=I+1;
  #end
#else
  #declare NumExp=0;
#end
#declare AnimTime=EndTime-StartTime;
PrintNumber("CipsStart: ",CipsStart)
#declare CipsExp=1.2;
PrintNumber("CipsExp:   ",CipsExp)
#declare FrameTime=clock_delta*AnimTime;
PrintNumber("FrameTime: ",FrameTime)
#declare ExpTime=max(CipsExp,FrameTime);
PrintNumber("ExpTime:   ",ExpTime)
#declare CipsCadenceCycle=mod((AimClock-CipsStart)+CipsCadence*1000,CipsCadence);
PrintNumber("Cycle:     ",CipsCadenceCycle)
  
union {
  AllPastCipsFOV()
  pigment {color rgb <1,0,0>}
  no_shadow
}
  
#if(AimClock>CipsStart & AimClock<CipsEnd)
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
#if(AimClock>SofieT000 & AimClock<SofieTCal)
  #declare SofieState=SofieState+1;
  #if(AimClock<SofieT150)
    #declare SofieState=SofieState+1;
    #if(AimClock>SofieT030 & AimClock<SofieT130)
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

#if(SofieState>0)
  object {
    SofieFOV
    translate y*0.4
    rotate x*180
//    LocationLookAt(<0,0,0>,LH(SunVec(JD)),Tail)
    LocationLookAt(<0,0,0>,Nose,Tail)
    
    pigment {color SofieDapatColor}
  }
#end


//object {CVBound pigment {color rgb <1,0,1>}}
#macro CVPoint(TNow,TThen,Dist,RotLeft,RotUp)
  #local Tail=Transform(TThen,<0,1,0>);
  #local JDThen=SecToJD(TThen);
  PrintNumber("JDThen: ",JDThen)
  #local Sun=LH(SunVec(SecToJD(TThen)));
  #local Wing=vnormalize(vcross(Tail,Sun));
  #local Tail=vnormalize(vcross(Sun,Wing));
  #local R0=GetPos(TThen);
  #local V=vaxis_rotate(vaxis_rotate(Sun,Tail,RotLeft/60),Wing,RotUp/60);
  //Plane - r.Sun=Dist
  //Ray   - r=r0+v*t
  //        (r0+v*t).Sun=Dist
  //        r0.Sun+v.Sun*t=Dist
  //        v.Sun*t=Dist-r0.Sun
  //        t=(Dist-r0.Sun)/(v.Sun)
  #local T=(Dist-vdot(R0,Sun))/vdot(V,Sun);
  #local R=R0+V*T;
  (vrotate(R,-y*(TNow-TThen)*360/86164.09))
#end

#declare CVDist=array[4]{-125,125,-125,125}
#declare CVRot=array[4]{3,3,-3,-3}

#macro CVPoints(TNow,TThen)
  #local ArraySize=ceil((min(TNowSofieT130)-TThen)/CommonVolumeDelta);
  PrintNumber("ArraySize: ",ArraySize)
  
#end

/*
#declare I=0;
#while(I<4)
  sphere {
    #local SphPos=CVPoint(AimClock,AimClock,CVDist[I],CVRot[I],0);
    PrintVector("SphPos: ",SphPos)
    SphPos,400000
    translate -Pos
    pigment {color rgb <1,0,1>}
    finish {ambient 1 diffuse 0}
  }
  #declare I=I+1;
#end
*/

#debug concat(SofieStatus,"\n")
#debug concat(CipsStatus,"\n")

sphere {
  0,1
 	scale <AEarth+Hc+100,BEarth+Hc+100,AEarth+Hc+100>
  translate -Pos
  texture {
    object {
      TransCipsHollowFOVCluster
      texture {pigment {color rgbf <1,1,1,1>} finish {ambient 0 diffuse 0}}
      texture {pigment {color rgb CipsDapatColor} finish {ambient 1 diffuse 0}}
    }
  }
  hollow
  no_shadow
  double_illuminate
}
#end
light_source {
  LH(SunVec(JD))*1e9
  color rgb 1.5
}
