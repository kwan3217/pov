#declare Deploy=1;

#include "LocLook.inc"
#include "Math.inc"
#include "AimAtt4South.inc"

#macro RunFile(A,B)

  #declare BetaD=B;
  #declare Alt=A;

  #include "AimAttDerived4South.inc"

  #if(B>0)
    #declare Sign="P";
  #else
    #declare Sign="M";
  #end
  #declare Suffix=concat("_",str(A,3,0),"_",Sign,str(abs(B),1,0));
  #fopen ouf concat("SunSouth.m") append
  #write(ouf,concat("Alt",Suffix,"=",str(A,3,0)),";\n")
  #write(ouf,concat("BetaD",Suffix,"=",str(B,3,0)),";\n")
  #write(ouf,concat("SofieStart",Suffix,"=",str(SofieObsStart,0,6),";\n"))
  #write(ouf,concat("CipsEnd",Suffix,"=",str(CipsEnd,0,6),";\n"))
  #write(ouf,concat("Sun",Suffix,"=[\n")
  #local S=""
  #local I=floor(StartTime);
  #while(I<EndTime)
    #local V=SunVecRH;
    PrintVector("V: ",V)
    #local V=AimAttInvRHV(I,V);
    PrintVector("V: ",V)
    #declare S=concat(str(I,10,0),",",str(V.x,10,6),",",str(V.y,10,6),",",str(V.z,10,6),"\n");
    #write(ouf,S)
    #local I=I+5;
  #end
  #write(ouf,"];\n")
  #fclose ouf

  #fopen ouf concat("NadirSouth.m") append
  #write(ouf,concat("Alt",Suffix,"=",str(A,3,0)),";\n")
  #write(ouf,concat("BetaD",Suffix,"=",str(B,3,0)),";\n")
  #write(ouf,concat("SofieStart",Suffix,"=",str(SofieObsStart,0,6),";\n"))
  #write(ouf,concat("CipsEnd",Suffix,"=",str(CipsEnd,0,6),";\n"))
  #write(ouf,concat("Nadir",Suffix,"=[\n")
  #local S=""
  #local I=floor(StartTime);
  #while(I<EndTime)
    #local V=-vnormalize(Pos(I));
    PrintVector("V: ",V)
    #local V=AimAttInvRHV(I,V);
    PrintVector("V: ",V)
    #declare S=concat(str(I,10,0),",",str(V.x,10,6),",",str(V.y,10,6),",",str(V.z,10,6),"\n");
    #write(ouf,S)
    #local I=I+5;
  #end
  #write(ouf,"];\n")
  #fclose ouf

  #fopen ouf concat("MatxSouth.m") append
  #write(ouf,concat("Alt",Suffix,"=",str(A,3,0)),";\n")
  #write(ouf,concat("BetaD",Suffix,"=",str(B,3,0)),";\n")
  #write(ouf,concat("SofieStart",Suffix,"=",str(SofieObsStart,0,6),";\n"))
  #write(ouf,concat("CipsEnd",Suffix,"=",str(CipsEnd,0,6),";\n"))
  #write(ouf,concat("Matx",Suffix,"=[\n")
  #local S=""
  #local I=floor(StartTime);
  #while(I<EndTime)
    #declare S="";
    PrintAimAtt(I,S)
    #declare S=concat(str(I,10,0),",",S,"\n");
    #write(ouf,S)
    #local I=I+5;
  #end
  #write(ouf,"];\n")
  #fclose ouf
#end

RunFile(600,0)
RunFile(600,6)
RunFile(600,9)
RunFile(615,9)
RunFile(560,9)
