/*
Time from start of SPICE kernel, Event
  0, SPICE kernel starts, 2008 May 25 23:30:57.920 UTC SCET
 15.202, Entry interface, 125km above ellipsoid (23:31:13.122 UTC SCET) (Interpolated)
122.955, Peak deceleration, 84.2403m/s^2
227.825, parachute firing
228.935, first peak parachute deceleration, 82.962m/s^2
242.825, heat shield jettison
252.985, leg deploy
253.485, leg deploy
253.980, leg deploy
404.940, lander separation
405.516, First thruster pulse, low thrust
408.005, First thruster pulse, high thrust
429, transition to constant velocity
431, constant velocity achieved, ~2.65m/s down
446.005, peak of touchdown transient, 52.666m/s^2, 23:38:23.925 UTC SCET, 430.804s after entry interface
452.860, SPICE kernel ends, 2008 May 25 23:38:30.780 UTC SCET
*/
#version unofficial Megapov 1.22;

#include "phx_30_IAU_MARS.inc"
#include "phx_30_blend.inc"

PrintNumber("I:       ",frame_number)
#declare T=frame_number/30;
#declare I_last=dimension_size(phx_IAU_MARS,1)-1;
#declare phx_frame_number=min(frame_number,I_last);
PrintNumber("T:       ",T)
#declare N=dimension_size(phx_IAU_MARS,1)-1;
#declare I_drop=9719;
#declare I=phx_frame_number;
PrintNumber("T:       ",phx_IAU_MARS_blend[I][0])
#declare Ip1=min(I+1,I_last);
#declare Im1=max(I-1,0);
#declare Dtm1=phx_IAU_MARS[I  ][1]-phx_IAU_MARS[Im1][1];
#declare Dtp1=phx_IAU_MARS[Ip1][1]-phx_IAU_MARS[I  ][1];
#declare Tpara0=227.825;
#declare TLeg1=252.985;
#declare TLeg2=253.485;
#declare TLeg3=253.985;
#declare Tpara1=228.935;
#declare Tdrop= 404.940;
#declare Ths=   242.825;
#declare Tland=446.005;
#declare Teng=405.515;
#declare I_drop=floor(Tdrop*30);
#declare R  =<phx_IAU_MARS_blend[I     ][ 1],phx_IAU_MARS_blend[I     ][ 2],phx_IAU_MARS_blend[I     ][ 3]>;
#declare Rm1=<phx_IAU_MARS_blend[Im1   ][ 1],phx_IAU_MARS_blend[Im1   ][ 2],phx_IAU_MARS_blend[Im1   ][ 3]>;
#declare Rp1=<phx_IAU_MARS_blend[Ip1   ][ 1],phx_IAU_MARS_blend[Ip1   ][ 2],phx_IAU_MARS_blend[Ip1   ][ 3]>;
#declare DrDt=(Rp1-R)/(Dtp1);
#declare Rf= <phx_IAU_MARS_blend[I_last][ 1],phx_IAU_MARS_blend[I_last][ 2],phx_IAU_MARS_blend[I_last][ 3]>;
#declare Rd= <phx_IAU_MARS_blend[I_drop][ 1],phx_IAU_MARS_blend[I_drop][ 2],phx_IAU_MARS_blend[I_drop][ 3]>;
PrintVector("Rd: ",Rd)
#declare V  =<phx_IAU_MARS[I     ][ 5],phx_IAU_MARS[I     ][ 6],phx_IAU_MARS[I     ][ 7]>;
PrintVector("DrDt: ",DrDt)
PrintVector("V:    ",V)
#declare Vm1=<phx_IAU_MARS[Im1   ][ 5],phx_IAU_MARS[Im1   ][ 6],phx_IAU_MARS[Im1   ][ 7]>;
#declare Vp1=<phx_IAU_MARS[Ip1   ][ 5],phx_IAU_MARS[Ip1   ][ 6],phx_IAU_MARS[Ip1   ][ 7]>;
#declare Vd =<phx_IAU_MARS[I_drop][ 5],phx_IAU_MARS[I_drop][ 6],phx_IAU_MARS[I_drop][ 7]>;
#declare M1 =<phx_IAU_MARS[phx_frame_number][ 8],phx_IAU_MARS[phx_frame_number][ 9],phx_IAU_MARS[phx_frame_number][10]>;
#declare M2 =<phx_IAU_MARS[phx_frame_number][11],phx_IAU_MARS[phx_frame_number][12],phx_IAU_MARS[phx_frame_number][13]>;
#declare M3 =<phx_IAU_MARS[phx_frame_number][14],phx_IAU_MARS[phx_frame_number][15],phx_IAU_MARS[phx_frame_number][16]>;
#declare Sun=<phx_IAU_MARS[phx_frame_number][17],phx_IAU_MARS[phx_frame_number][18],phx_IAU_MARS[phx_frame_number][19]>;
#declare BackshellTravel=886.6*0.25; //Pixels from HiRise, backshell crater to lander. Final number in meters
PrintNumber("Backshell distance from landing: ",BackshellTravel)

//Average A
#declare GWindow=60; //Frames, 5 seconds
#local II=I-GWindow/2;
#local AverageA=<0,0,0>;
#local NN=0;
#local R0=<phx_IAU_MARS_blend[II+0][ 1],phx_IAU_MARS_blend[II+0][ 2],phx_IAU_MARS_blend[II+0][ 3]>;
PrintVector("R0: ",R0)
#local V0=<phx_IAU_MARS[II+0][ 5],phx_IAU_MARS[II+0][ 6],phx_IAU_MARS[II+0][ 7]>;
PrintVector("V0: ",V0)
#local T0 =phx_IAU_MARS[II+0][ 1];
PrintNumber("T0: ",T0)
#while(II<I+GWindow/2)
  #local V2=<phx_IAU_MARS[II+1][ 5],phx_IAU_MARS[II+1][ 6],phx_IAU_MARS[II+1][ 7]>;
  #local V1=<phx_IAU_MARS[II+0][ 5],phx_IAU_MARS[II+0][ 6],phx_IAU_MARS[II+0][ 7]>;
  #local T2= phx_IAU_MARS[II+1][ 1];
  #local T1= phx_IAU_MARS[II+0][ 1];
  #local dV=V2-V1;
  #local dT=T2-T1;
  #local dVdT=dV/dT;
  #local II=II+1;
  #local NN=NN+1;
  #local AverageA=AverageA+dVdT;
#end
#local AverageA=AverageA/NN;
PrintVector("AverageA: ",AverageA)
#local dT=T-T0;
#declare RAverageA=R0+V0*dT+AverageA*dT*dT/2;
PrintVector("RAverageA: ",RAverageA)
PrintVector("Ofs: ",R-RAverageA)

#declare A  =<0,0,0>;
#declare NN=0;
PrintVector("A:    ",A)
PrintNumber("Dtm1: ",Dtm1)
PrintNumber("Dtp1: ",Dtp1)
PrintVector("V-Vm1: ",V-Vm1)
PrintVector("(V-Vm1)/Dtm1: ",(V-Vm1)/Dtm1)
#if(Dtm1>0)
  PrintVector("A:    ",A)
  #declare A=A+(V-Vm1)/Dtm1;
  PrintVector("A:    ",A)
  #declare NN=NN+1;
#end
#if(Dtp1>0)
  #declare A=A+(Vp1-V)/Dtp1;
  #declare NN=NN+1;
#end
#if(NN>0)
  #declare A=A/NN;
#end

#declare MuMars=42828.314e9;
#declare Ag=-MuMars*R/pow(vlength(R),3);
#declare Ang=A-Ag;
PrintVector("Ag: ",Ag)
PrintVector("Ang: ",Ang)

#declare AMars=3396190;
#declare BMars=3376200;
#declare FMars=1-(BMars/AMars);

#macro xyz2llr(r)
  #local R=vlength(r);
  #local Lat=asin(r.z/R);
  #local Lon=atan2(r.y,r.x);
  (<Lat,Lon,R>)
#end

#declare FinalLLA=xyz2lla(<Rf.x,Rf.z,Rf.y>/AMars,FMars);
#declare FinalLLR=xyz2llr(Rf);
#debug concat("FinalLLA:   Lat:",str(degrees(FinalLLA.x),6,6)," Lon:",str(degrees(FinalLLA.y),6,6)," Alt:",str(FinalLLA.z*AMars,6,6),"\n")
#debug concat("FinalLLR:   Lat:",str(degrees(FinalLLR.x),6,6)," Lon:",str(degrees(FinalLLR.y),6,6)," Rad:",str(FinalLLR.z,6,6),"\n")
#declare DropLLA=xyz2lla(<Rd.x,Rd.z,Rd.y>/AMars,FMars);
#debug concat("DropLLA:    Lat:",str(degrees(DropLLA.x),6,6)," Lon:",str(degrees(DropLLA.y),6,6)," Alt:",str(DropLLA.z*AMars,6,6),"\n")
#declare CurrentLLA=xyz2lla(<R.x,R.z,R.y>/AMars,FMars);
#debug concat("CurrentLLA: Lat:",str(degrees(CurrentLLA.x),6,6)," Lon:",str(degrees(CurrentLLA.y),6,6)," Alt:",str(CurrentLLA.z*AMars,6,6),"\n")
#declare DropLL=<DropLLA.x,DropLLA.y,FinalLLA.z>;
PrintVector("DropLL: ",DropLL)
#declare DropAGL=(DropLLA.z-FinalLLA.z)*AMars;
PrintNumber("DropAGL: ",DropAGL)
#declare CurrentLL=<CurrentLLA.x,CurrentLLA.y,FinalLLA.z>;
PrintVector("CurrentLL: ",DropLL)
#declare DropGXYZ=lla2xyz(DropLL,FMars)*AMars;
#declare DropGXYZ=<DropGXYZ.x,DropGXYZ.z,DropGXYZ.y>;
PrintVector("DropGXYZ: ",DropGXYZ)
#declare CurrentGXYZ=lla2xyz(CurrentLL,FMars)*AMars;
#declare CurrentGXYZ=<CurrentGXYZ.x,CurrentGXYZ.z,CurrentGXYZ.y>;
PrintVector("CurrentGXYZ: ",CurrentGXYZ)
PrintVector("Rf:          ",Rf)
#declare DropHToGo=vlength(Rf-DropGXYZ);
PrintNumber("DropHToGo: ",DropHToGo)

//Drag frame
#declare Lx=V/vlength(V); //Direction of motion, drag axis
#declare Ly=vcross(R,V);  //Horizontal lift axis
#declare Ly=Ly/vlength(Ly); 
#declare Lz=vcross(Lx,Ly); //Vertical lift axis
//LVLH frame
#declare Sky=R/vlength(R);
#declare Le=vcross(<0,0,1>,Sky);
#declare Le=Le/vlength(Le);
#declare Ln=vcross(R,Le);
#declare Ln=Ln/vlength(Ln);
#include "PhxCamera.inc"
PrintNumber("Total AoA: ",degrees(vangle(Lx,M1)))
PrintVector("Rel velocity: ",V)
#declare V_LVLH=<vdot(V,Sky),vdot(V,Ln),vdot(V,Le)>;
PrintVector("Rel vel LVLH: ",V_LVLH)
#declare V_Ground=<0,V_LVLH.y,V_LVLH.z>;
PrintNumber("Groundspd: ",vlength(V_Ground))

#declare Vd_LVLH=<vdot(Vd,Sky),vdot(Vd,Ln),vdot(Vd,Le)>;
PrintVector("Rel vel LVLH at drop: ",Vd_LVLH)
#declare Vd_Ground=<0,Vd_LVLH.y,Vd_LVLH.z>;
PrintNumber("Groundspd at drop: ",vlength(Vd_Ground))
#declare DropTime=(DropHToGo+BackshellTravel)/vlength(Vd_Ground);
PrintNumber("DropTime: ",DropTime)
#declare VDropSpd=DropAGL/DropTime;
PrintNumber("VDropSpd: ",VDropSpd)

#declare Aeroid=1500;
#declare EllCurrent=CurrentLLA.z*AMars;
#declare EllFinal=FinalLLA.z*AMars;
#declare MOLACurrent=EllCurrent-Aeroid;
#declare MOLAFinal=EllFinal-Aeroid;
PrintNumber("EllCurrent:  ",EllCurrent)
PrintNumber("EllFinal:    ",EllFinal)
PrintNumber("MOLACurrent: ",MOLACurrent)
PrintNumber("MOLAFinal:   ",MOLAFinal)
PrintNumber("AGL: ",MOLACurrent-MOLAFinal)

#include "Atmosphere2.inc"
#declare TT=Temp(MOLACurrent);
PrintNumber("Temp:   ",TT)
#declare Dens=Density(MOLACurrent);
PrintNumber("Pres:   ",Pressure(MOLACurrent))
PrintNumber("Dens:   ",Dens)
PrintNumber("Vsound: ",Vsound(MOLACurrent))
#declare DynPres=pow(vlength(V),2)*Dens/2;
PrintNumber("DynPres:",DynPres)
#declare DynHeat=pow(vlength(V),3)*sqrt(Dens)/2;
PrintNumber("DynHeat:",DynHeat)
#declare Mach=vlength(V)/Vsound(MOLACurrent);
PrintNumber("Mach:   ",Mach)

