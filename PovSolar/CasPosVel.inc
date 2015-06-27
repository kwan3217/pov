#include "CassiniSatCentVec.inc"
#include "TablePosVel.inc"

#macro CasPosVel(Time,CasPos,CasVel)
#if(Time<=2453170.5)
  //Use the sun-centered osculating elements
  #local I=1;
  PrintDate("Time: ",Time)
  PrintDate("Epoch:",CassiniEle[I][0])
  #while((Time>CassiniEle[I][0]))
    #local I=I+1;
  #end
  PrintDate("Before Epoch: ",CassiniEle[I-1][0])
  #local CasPos1=PosInSpace(
     CassiniEle[I-1][ 0],    //Epoch, JDCT
     CassiniEle[I-1][10],    //Semimajor Axis, km
     CassiniEle[I-1][ 1],    //Eccentricity
     CassiniEle[I-1][ 3],    //Inclination, deg
     CassiniEle[I-1][ 4],    //Longitude of Ascending Node, deg
     CassiniEle[I-1][ 5],    //Argument of Periapse, deg
     CassiniEle[I-1][ 8],    //Mean Anomaly, deg
     CassiniEle[I-1][ 7],    //Mean motion, deg/day
	 Time)-PlanetPos[Sa];
	#local Time1=CassiniEle[I-1][0];
  PrintDate("After Epoch: ",CassiniEle[I][0])
  #local CasPos2=PosInSpace(
     CassiniEle[I][ 0],    //Epoch, JDCT
     CassiniEle[I][10],    //Semimajor Axis, km
     CassiniEle[I][ 1],    //Eccentricity
     CassiniEle[I][ 3],    //Inclination, deg
     CassiniEle[I][ 4],    //Longitude of Ascending Node, deg
     CassiniEle[I][ 5],    //Argument of Periapse, deg
     CassiniEle[I][ 8],       //Mean Anomaly, deg
     CassiniEle[I][ 7],   //Mean motion, deg/day
	 Time)-PlanetPos[Sa];
	 #local Time2=CassiniEle[I][0];
  #declare CasPos=Linterp(Time1,CasPos1,Time2,CasPos2,Time);
  #declare CasVel=Linterp(Time1,CasVel1,Time2,CasVel2,Time);
#else
  TablePosVel(CassiniSatCentVec,Time,CasPos,CasVel)
#end	 

#end
