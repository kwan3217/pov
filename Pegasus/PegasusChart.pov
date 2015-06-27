#declare Quick=1;
#include "PegasusLaunchCommon3.inc"

#declare T=0;
#macro V(VV)
  concat(str(VV.x,0,3),",",str(VV.y,0,3),",",str(VV.z,0,3))
#end

#fopen ouf "PegasusChart.csv" write
#while(T<=20.05)
  #declare Pos=<0,0,0>;
  #declare Vel=<0,0,0>;
  #declare Nose=<0,0,0>;
  #declare Tail=<0,0,0>;
  GetPegasusState(T,Pos,Vel,Nose,Tail)
  #write(ouf,T,",",V(Pos),",",V(Vel),",",str(Alt,0,3),",",V(PlanePos),",",str(PlaneAlt,0,3),"\n")
  #declare T=T+0.1;
#end
#fclose ouf
/*
#fopen ouf "PegasusTiming.csv" write
#declare Frame=0;
#while(Frame<5104)
  #declare Klock=Frame/5104;
  #write(ouf,Frame,",",Klock,",",CalcPegasusClock(Klock),",",CalcMusicClock(Klock),"\n")
  #declare Frame=Frame+1;
#end
#fclose ouf
*/
