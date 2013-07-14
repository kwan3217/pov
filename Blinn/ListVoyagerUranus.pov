#include "KwanMath.inc"
#include "SpiceQuat.inc"

#version unofficial Megapov 1.22;

#furnsh "generic/generic.tm"
#furnsh "Voyager/vgr2.tm"

#declare NWnd=ckcov("Voyager/ck/vg2_ura_version1_type1_iss_sedr.bc",-32100,"INTERVAL",0,"TDB",10000);
PrintNumber("NWnd: ",NWnd)

#fopen ouf "list.txt" write
#declare I=0;
#while(I<NWnd) 
  #declare ET=ckgetcov(I,0);
  #declare Q=pxform("VG2_SCAN_PLATFORM","VG2_AZ_EL",ET);
  #declare X=QuatVectRotate(Q,x);
  #declare Y=QuatVectRotate(Q,y);
  #declare Z=QuatVectRotate(Q,z);
  #write(ouf,concat(str(ET,0,6),",",etcal(ET),",",timout(ET,"YYYY-MON-DD HR:MN:SC.### ::UTC"),",",StrQuat(Q),",",StrVector(X),",",StrVector(Y),",",StrVector(Z),"\n"))
  #declare I=I+1;
#end

