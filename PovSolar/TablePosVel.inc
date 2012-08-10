#macro TablePosVel(Table,Time,Pos,Vel)
  #local I=1;
  PrintDate("Time: ",Time)
  #while((Time>Table[I][0]))
    #local I=I+1;
  #end
  PrintDate("Before Epoch: ",Table[I-1][0])
  #local Pos1=<0,0,0>;
	#local Vel1=<0,0,0>;
	KeplerFG(                  //R0,V0,T,Mu,R,V */
    LH(<Table[I-1][1],           //Rx, km
        Table[I-1][2],           //Ry, km
        Table[I-1][3]>),         //Rz, km
    LH(<Table[I-1][4],           //Vx, km/s
        Table[I-1][5],           //Vy, km/s
        Table[I-1][6]>),         //Vz, km/s
     (Time-Table[I-1][0])*86400, //Time from epoch, s
		 37931284.5,                      //Saturn GM, km and s
	   Pos1,Vel1
	 )
  #local Time1=Table[I-1][0];
  PrintDate("After Epoch: ",Table[I][0])
  #local Pos2=<0,0,0>;
	#local Vel2=<0,0,0>;
	KeplerFG(                  //R0,V0,T,Mu,R,V */
    LH(<Table[I][1],           //Rx, km
        Table[I][2],           //Ry, km
        Table[I][3]>),         //Rz, km*/
    LH(<Table[I][4],           //Vx, km/s
        Table[I][5],           //Vy, km/s
        Table[I][6]>),         //Vz, km/s
     (Time-Table[I][0])*86400, //Time from epoch, s
		 37931284.5,                      //Saturn GM, km and s
	   Pos2,Vel2
	 )
	 #local Time2=Table[I][0];
   #declare Pos=Linterp(Time1,Pos1,Time2,Pos2,Time);
   #declare Vel=Linterp(Time1,Vel1,Time2,Vel2,Time);

#end
