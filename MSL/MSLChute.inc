#include "metals.inc"

#declare D0=19.7;
#declare S0=pi*D0*D0/4;
#declare DDisk=0.72*D0;
#declare Dp=13.5; //Projected diameter Dp range ~12.7m to 14m, dependent on dynamic pressure
#declare Rp=Dp/2;
#declare Dv=0.5;  //Disk vent
#declare Rv=Dv/2;
#declare Hp=2.4;  //Height of parachute disk part, m
#declare Hg=0.83; //Heigth of gap, m
#declare Hb=2.38; //Height of band, m
#declare Ls=33.49; //Length of suspension lines, m
#declare Hs=sqrt(Ls*Ls-Rp*Rp); //Height of suspension lines, m
#declare Hr=10.14; //Height of riser, m
#declare Hbr=1.37;  //Height of bridle, m
#declare Dbr=0.4;   //Diameter of bridle circle, m
#declare Rbr=Dbr/2;  //Radius of bridle circle, m
#declare Rbl=0.005; //Radius of lines, m
#declare Xrl=0.01;
#declare Yrl=0.10;
#declare Rsl=Rbl;

#declare MSLChuteBridle=union {
  #local I=0;
  #while(I<3)
    union {
      cylinder {
        <0,Rbr-Rbl,0>,<0,Rbr-Rbl,Hbr*2/3>,Rbl
      }            
      sphere {
        <0,Rbr-Rbl,Hbr*2/3>,Rbl
      }
      cylinder {
        <0,Rbr-Rbl,Hbr*2/3>,<0,0,Hbr>,Rbl
      }
      rotate z*120*I
      pigment {color rgb <1,1,0.5>}
    } 
    #local I=I+1;
  #end
  difference {
    union {
      cylinder {
        <0,0,Hbr/3-0.05>,<0,0,Hbr/3>,Rbr
      }
      cylinder {
        <0,0,Hbr*2/3-0.05>,<0,0,Hbr*2/3>,Rbr
      }
    }
    cylinder {
      <0,0,0>,<0,0,Hbr>,Dbr/2-(Rbl*2)
    }
    texture {T_Chrome_3C}
  }
}  
#declare MSLChuteRiser=box {
  <-Xrl/2,-Yrl/2,0>,<Xrl/2,Yrl/2,Hr>
  pigment {color rgb <1,1,0.5>}
}

#declare MSLChuteSuspension=union {
  #local I=0;
  #while(I<40)
    cylinder {
      <0,-Yrl/2,0>,<Rp*cos(radians(I*180/40)),-Rp*sin(radians(I*180/40)),Hs>,Rsl
    }
    cylinder {
      <0,Yrl/2,0>,<Rp*cos(radians(I*180/40)),Rp*sin(radians(I*180/40)),Hs>,Rsl
    }
    #local I=I+1;
  #end
  pigment {color rgb <1,1,0.5>}
}

#declare MSLChuteBand=union {
  cylinder {
    <0,0,0>,<0,0,Hb>,Rp
    open
    pigment {color rgb <1,1,1>}
  }
}

#declare MSLChuteGap=union {
  #local I=0;
  #while(I<80)
    cylinder {
      <Rp,0,0>,<Rp,0,Hg>,Rsl
      rotate I*360/80*z
    }
    #local I=I+1;
  #end
  pigment {color rgb <1,1,0.5>}
}
                                
#declare TAcc0=264;                                
#declare Acc0=vlength(A(TAcc0*24));

#macro MSLChuteAf(TT,I) 
  #switch(TT)
    #range(-99999,Tp)
      #local Af=0.00001;
      #break
    #range(Tp,TI1)
      #local Fd=max(0,vlength(A(I))-Acc0)*3200;
      #local Q=vlength(V(I));
      #local Q=Q*Q*rho(I)/2;
      #local CdA=Fd/Q;
      #local Cd=1.222;
      #local AA=CdA/Cd;
      #local Af=AA/A0;
      #break
    #range(TI1,TI2)
      #local Fd=max(0,vlength(A(I))-Acc0)*3200;
      #local Q=vlength(V(I));
      #local Q=Q*Q*rho(I)/2;
      #local CdA=Fd/Q;
      #local Cd=1.222;
      #local AA=Linterp(TI1,CdA/Cd,TI2,A0,TT);
      #local Af=AA/A0;
      #break
    #range(TI2,99999)
      #local Af=1;
      #break
  #end  
  PrintNumber("TT: ",TT)
  PrintNumber("I:  ",I)
  #ifdef(Fd)
  PrintNumber("Fd: ",Fd)
  PrintNumber("Q:  ",Q)
  PrintNumber("CdA: ",CdA)
  PrintNumber("AA:  ",AA)
  #end
  PrintNumber("Af: ",Af)
  
  (Af)
#end

#declare MSLChuteDisk=union {
  sphere {
    <0,0,0>,1
    scale <Rp,Rp,Hp>
    clipped_by {
      union {
        plane {
          z,0
        }
        cylinder {
          <0,0,0>,<0,0,Hp+0.5>,Rv
        }
        inverse
      }
    }
  }
  pigment {color rgb <1,1,1>}
}

#macro MSLChute(TT,I)
  #local Tp=264;
  #local TI1=268;
  #local TI2=270;

  #local Lp=sqrt(Rp*Rp+Hp*Hp);
  #local Afcrit=1.05;
  #local A0=pi*Rp*Rp;
  #local Acrit=A0*Afcrit;
  #local Rcrit=sqrt(Acrit/pi);
  #local Hcrit=sqrt(Lp*Lp-Rcrit*Rcrit);
 
  union {
    #local Vst=50; //m/s, line stretch speed
    #local Hmax=(Hbr+Hr+Hs+Hb+Hg+Lp);
    #local Tmax=Hmax/Vst;
    #local Af=MSLChuteAf(TT,I);
    #local this_A=A0*Af;   
    #local this_Rp=max(0.25,sqrt(this_A/pi));
    #if(Af<Afcrit)
      #local this_Rp2=this_Rp;
    #else
      #local this_Rp2=Rcrit;
    #end
    #local this_Hp=sqrt(Lp*Lp-this_Rp2*this_Rp2);
    object {MSLChuteBridle}
    object {MSLChuteRiser translate z*(Hbr)}  
    object {MSLChuteSuspension translate z*(Hbr+Hr)}
    object {MSLChuteBand translate z*(Hbr+Hr+Hs)}
    object {MSLChuteGap translate z*(Hbr+Hr+Hs+Hb)}
    union {MSLChuteDisk scale <1,1,this_Hp/Hp> translate z*(Hbr+Hr+Hs+Hb+Hg)}
    scale <this_Rp/Rp,this_Rp/Rp,max(0.00001,min(1,(TT-Tp)/Tmax))>
  }
#end

  