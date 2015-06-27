#declare CamAz=radians(225);
#declare HComp=3.5*sqrt(2);
#declare SComp=2;
#declare CamAngle=degrees(atan(8/9))*2;

#if(T>150 & T<220)
  #if(T<155)
    #debug "Camera Swing1A\n"
    #declare CamAz=radians(Linterp(150,225,155,288,T));
    #declare SComp=Linterp(150,2,155,4,T);
  #else
    #if(T<215)
      #debug "Camera Swing1B\n"
      #declare CamAz=radians(Linterp(155,288,218,290,T));
      #declare SComp=4;
    #else
      #debug "Camera Swing1C\n"
      #declare CamAz=radians(Linterp(215,290,220,225,T));
      #declare SComp=Linterp(215,4,220,2,T);
    #end
  #end    
#end
PrintNumber("CamAz: ",degrees(CamAz))

#if(T>Tpara0+12 & T<Tpara0+30)
  #debug "Camera Swing2\n"
  #declare SComp=BLinterp(Tpara0+12,2,Tpara0+15,-2,T);
  #declare CamAz=radians(BLinterp(Tpara0+12,225,Tpara0+15,135,T));
#end
#declare Ofs=-(R-RAverageA);
#declare Loc=Ln*cos(CamAz)*HComp+Le*sin(CamAz)*HComp+Sky*SComp;
PrintNumber("CamAz: ",degrees(CamAz))
#declare Look=<0,0,0>;
#if(T>Tpara0-5 & T<Tpara0+20)
  #declare Loc=BLinterp(Tpara0-5,1,Tpara0-1,30/vlength(Loc),T)*Loc;
//  #declare Look=-M1*BLinterp(Tpara0-5,0,Tpara0-1,12,T);
#end
#declare UseMRO=0;
#if(UseMRO)
  #include "mro30.inc"
  #declare LocLen=vlength(Loc);
  #declare MroLoc=<mro_IAU_MARS[frame_number][2],mro_IAU_MARS[frame_number][3],mro_IAU_MARS[frame_number][4]>;
  #declare Loc=MroLoc-R;
  #declare CamAngle=0.5;
#end
#if(T>Tland+10)
  #include "ody30.inc"
  #declare LocLen=vlength(Loc);
  #declare OdyLoc=<ody_IAU_MARS[frame_number][2],ody_IAU_MARS[frame_number][3],ody_IAU_MARS[frame_number][4]>;
  #declare OdyLoc=OdyLoc-R;
  #declare D2=vlength(OdyLoc);
  #declare OdyLoc=OdyLoc*LocLen/vlength(OdyLoc);
  #declare Loc=BLinterp(Tland+10,Loc,Tland+20,OdyLoc,T);
  #declare D1=LocLen;
  #declare LocLen=exp(BLinterp(Tland+18,ln(D1),Tland+30,ln(D2),T));
  #declare Loc=Loc*LocLen/vlength(Loc);
#end

PrintNumber("CamAngle: ",CamAngle)
