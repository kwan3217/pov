#macro TablePosVel(Table,Time,CasPos,CasVel)
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
#else
  //Use the Saturn body centered state vectors
  #local I=1;
  PrintDate("Time: ",Time)
  #while((Time>Table[I][0]))
    #local I=I+1;
  #end
  PrintDate("Before Epoch: ",Table[I-1][0])
  #local CasPos1=<0,0,0>;
	#local CasVel1=<0,0,0>;
	KeplerFG(                  //R0,V0,T,Mu,R,V */
    LH(<Table[I-1][1],           //Rx, km
        Table[I-1][2],           //Ry, km
        Table[I-1][3]>),         //Rz, km
    LH(<Table[I-1][4],           //Vx, km/s
        Table[I-1][5],           //Vy, km/s
        Table[I-1][6]>),         //Vz, km/s
     (Time-Table[I-1][0])*86400, //Time from epoch, s
		 37931284.5,                      //Saturn GM, km and s
	   CasPos1,CasVel1
	 )
  #local Time1=Table[I-1][0];
  PrintDate("After Epoch: ",Table[I][0])
  #local CasPos2=<0,0,0>;
	#local CasVel2=<0,0,0>;
	KeplerFG(                  //R0,V0,T,Mu,R,V */
    LH(<Table[I][1],           //Rx, km
        Table[I][2],           //Ry, km
        Table[I][3]>),         //Rz, km*/
    LH(<Table[I][4],           //Vx, km/s
        Table[I][5],           //Vy, km/s
        Table[I][6]>),         //Vz, km/s
     (Time-Table[I][0])*86400, //Time from epoch, s
		 37931284.5,                      //Saturn GM, km and s
	   CasPos2,CasVel2
	 )
	 #local Time2=Table[I][0];
#end	 
#declare CasPos=Linterp(Time1,CasPos1,Time2,CasPos2,Time);
#declare CasVel=Linterp(Time1,CasVel1,Time2,CasVel2,Time);

#end
