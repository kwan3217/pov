//Billiard Mechanics Include File

//#debug "Parsing Mechanics Engine (mechanic.inc)\n"

#ifndef(Gravity)
#declare Gravity=-0*y;
#end
#ifndef(AirResist)
#declare AirResist=0;  //between 0 and 1, higher is more resistance
#end
#ifndef(WallBallE)
#declare WallBallE=0.95;  //Wall-Ball colision elasticity. 1 is perfectly elastic, 0 is stick.
#end
#ifndef(MaxIters)
#declare MaxIters=10;   //Steps of iteration during one frame
#end
#ifndef(SpdCutoff)
#declare SpdCutoff=0.00; //Minimum ball speed
#end
#ifndef(MClock)
#declare MClock=clock;
#end
#ifndef(MDelta)
#declare MDelta=clock_delta;
#end
#ifndef(OrigVec)
#declare OrigVec="mstatevec.inc"
#end
#ifndef(StateVec)
#declare StateVec="statevec.inc"
#end
#ifndef(MechanicLog)
#declare MechanicLog="mechanic.Log"
#end

#macro Log(S)
//  #debug S
  #write (LogF,S)
#end

#macro LogTime(T)
  Log(concat("Current Time is ",str(T,0,4),"\n"))
#end

#declare MicroClockDelta=MDelta/MaxIters;

#declare GravityUse=Gravity*MicroClockDelta;
#declare AirResistUse=1-(AirResist*MicroClockDelta);

#macro DetectBallCollision(Bp,Bv,Bf,I)
  #declare J=I+1; //Only check for higher numbered balls. The lower ones already checked for you.
  #while(J<dimension_size(Bp,1))
    #if(Bf[J])
      #declare Dist=Bp[J]-Bp[I]; //Vector from center of Ball[I] to Ball[J]
      #if(vlength(Dist)<2)
        LogTime(CurrentTime)
        Log(concat("Ball[",str(I,1,0),"] Collision with Ball[",str(J,1,0),"]\n"))
        Log(concat("Dist to Ball[",str(J,1,0),"]: <",str(Dist.x,8,14),",",str(Dist.y,8,14),",",str(Dist.z,8,14),"> (Len: ",str(vlength(Dist),8,14),")\n"))
        //Ball[J] is the target ball, Ball[I] is the action ball
        #declare Spd=Bv[I]-Bv[J];  //Reduce speeds to target ball space
        Log(concat("       Spd: <",str(Spd.x,8,14),",",str(Spd.y,8,14),",",str(Spd.z,8,14),">  (Len: ",str(vlength(Spd),8,14),")\n"))
        #declare Par=((vdot(Dist,Spd))/pow(vlength(Dist),2))*Dist;
        Log(concat("       Par: <",str(Par.x,8,14),",",str(Par.y,8,14),",",str(Par.z,8,14),">  (Len: ",str(vlength(Par),8,14),")\n"))
        #declare Perp=Spd-Par;
        Log(concat("      Perp: <",str(Perp.x,8,14),",",str(Perp.y,8,14),",",str(Perp.z,8,14),">  (Len: ",str(vlength(Perp),8,14),")\n"))
        //Translate back to table space
        #declare Bv[I]=Bv[J]+Perp;  //This is correct, because Bv[J] is the reduction vector to ball space.
        #declare Bv[J]=Bv[J]+Par;
        //Move action ball so it is no longer intersecting target ball
        #declare Dist=Dist*2/vlength(Dist);
        #declare Bp[I]=Bp[J]-Dist;
      #end //#if(vlength(Dist)<2)
    #end //#if(Bf[J])
    #declare J=J+1;
  #end
#end

#macro DetectPocketed(Bp,Hole,Bf)
  #declare J=0;
  #while(J<dimension_size(Hole,1))
//    Log(concat("I=",str(I,3,0),"  J=",str(J,3,0),"  d=",str(dimension_size(Hole,1),3,0),"\n"))
    #if(vlength(Bp[I]-Hole[J])<HoleRadius-0.5)
      #declare Bf[I]=0;
      LogTime(CurrentTime)
      Log(concat("Pocketed Ball[",str(I,1,0),"]\n"))
    #end        
    #declare J=J+1;
  #end
#end

#macro DetectSpdCutoff(V,I)
  #if (vlength(V)!=0)
    #if(vlength(V)<SpdCutoff)
      #declare V=<0,0,0>;                     
      LogTime(CurrentTime)
      Log(concat("Cut speed to Ball[",str(I,1,0),"]\n"))
    #end
  #end
#end

#macro DoStep(Q,Bp,Bv,Bf)
  Log(concat("Clock: ",str(Q,1,4),"\n"))
  Log(concat("Air Resistance Used: ",str(AirResistUse,4,14),"\n"))
  Log(concat("       Gravity Used: ",str(GravityUse.y,4,14),"\n"))
  
  #declare Iters=MaxIters;
  #while (Iters>0)
    #if(mod(Iters,20)=0)
//      #debug concat(str(Iters,0,0)," iterations left...\n")
    #end
    #declare CurrentTime=Q+(MaxIters-Iters)*MicroClockDelta;
    #declare I=0;
    #while(I<dimension_size(Bp,1))
      //Move the balls
      #if(Bf[I])  //If the ball is live...
//        Log(concat("Moving Ball[",str(I,1,0),"]\n"))
        #declare Bp[I]=Bp[I]+Bv[I]*MicroClockDelta;
        #declare Bv[I]=(Bv[I]+GravityUse)*AirResistUse;//Gravitate the velocity
        //Detect collision with WallX
        #declare J=0;
        #while(J<dimension_size(WallX,1))
          #if(abs(Bp[I].x-WallX[J])<1)
            #if(Bp[I].x>WallX[J])
              #declare Bp[I]=x*(WallX[J]+1)+y*Bp[I].y+z*Bp[I].z;
            #else
              #declare Bp[I]=x*(WallX[J]-1)+y*Bp[I].y+z*Bp[I].z;
            #end
            #declare Bv[I]=Bv[I]*<-1,1,1>*WallBallE;
            LogTime(CurrentTime)
            Log(concat("Ball[",str(I,1,0),"] Collision with WallX[",str(J,1,0),"]\n"))
          #end
          #declare J=J+1;
        #end
        //Detect collision with WallZ
        #declare J=0;
        #while(J<dimension_size(WallZ,1))
          #if(abs(Bp[I].z-WallZ[J])<1)
            #if(Bp[I].z>WallZ[J])
              #declare Bp[I]=x*Bp[I].x+y*Bp[I].y+z*(WallZ[J]+1);
            #else
              #declare Bp[I]=x*Bp[I].x+y*Bp[I].y+z*(WallZ[J]-1);
            #end
            #declare Bv[I]=Bv[I]*<1,1,-1>*WallBallE;
            LogTime(CurrentTime)
            Log(concat("Ball[",str(I,1,0),"] Collision with WallZ[",str(J,1,0),"]\n"))
          #end
          #declare J=J+1;
        #end
        //Detect collision with floor
        #declare J=0;
        #while(J<dimension_size(Floor,1))
          #if(abs(Bp[I].y-Floor[J])<1)
            #if(Bp[I].y>Floor[J])
              #declare Bp[I]=x*Bp[I].x+y*(Floor[J]+1)+z*Bp[I].z;
            #else
              #declare Bp[I]=x*Bp[I].x+y*(Floor[J]-1)+z*Bp[I].z;
            #end
            #declare Bv[I]=Bv[I]*<1,-1,1>*WallBallE;
            LogTime(CurrentTime)
            Log(concat("Ball[",str(I,1,0),"] Collision with Floor[",str(J,1,0),"]\n"))
          #end
          #declare J=J+1;
        #end
        DetectBallCollision(Bp,Bv,Bf,I)
        DetectSpdCutoff(Bv[I],I)
        DetectPocketed(Bp,Hole,Bf)
      #else
//        Log(concat("Ball[",str(I,1,0),"] is not free\n"))
      #end
      #declare I=I+1;
    #end
    #declare Iters=Iters-1;
  #end
    
  #declare I=0;
  #while(I<dimension_size(Bp,1))
    Log(concat("Ball ",str(I,1,0)))
    #if(Bf[I])
      Log("\n")
    #else
      Log(" (pocketed)\n")
    #end
    Log(concat("  Position: <",str(Bp[I].x,8,14),",",str(Bp[I].y,8,14),",",str(Bp[I].z,8,14),">\n"))
    Log(concat("  Velocity: <",str(Bv[I].x,8,14),",",str(Bv[I].y,8,14),",",str(Bv[I].z,8,14),">  (Len: ",str(vlength(Bv[I]),8,14),")\n"))
    #declare I=I+1;
  #end
#end

#macro WriteStateVectors()
#fopen Ouf StateVec write
//Write out the results for next time
#write (Ouf,"//Modified state vector for clock=",MClock+MDelta,"\n")
#write (Ouf,"\n")
#write (Ouf,concat("#declare StateVecTime=",str(MClock+MDelta,8,14),";\n"))
#write (Ouf,"#declare BallPos=array[",dimension_size(BallPos,1),"] {\n")
#declare I=0;
#while(I<dimension_size(BallPos,1)-1)
  #write (Ouf,concat("  <",str(BallPos[I].x,8,14),",",str(BallPos[I].y,8,14),",",str(BallPos[I].z,8,14),">,\n"))
  #declare I=I+1;
#end
#write (Ouf,concat("  <",str(BallPos[I].x,8,14),",",str(BallPos[I].y,8,14),",",str(BallPos[I].z,8,14),">\n"))
#write(Ouf,"}\n")
#write(Ouf,"\n")
#ifdef(AimPoint)
#write (Ouf,concat("#declare AimPoint=<",str(AimPoint.x,8,14),",",str(AimPoint.y,8,14),",",str(AimPoint.z,8,14),">;\n\n"))
#end
#ifdef(CueAt)
#write (Ouf,concat("#declare CueAt=<",str(CueAt.x,8,14),",",str(CueAt.y,8,14),",",str(CueAt.z,8,14),">;\n\n"))
#end
#ifdef(TargetBall)
#write (Ouf,concat("#declare TargetBall=",str(TargetBall,8,0),";\n\n"))
#end
#write (Ouf,"#declare BallSpd=array[",dimension_size(BallSpd,1),"] {\n")
#declare I=0;
#while(I<dimension_size(BallSpd,1)-1)
  #write (Ouf,concat("  <",str(BallSpd[I].x,8,14),",",str(BallSpd[I].y,8,14),",",str(BallSpd[I].z,8,14),">,\n"))
  #declare I=I+1;
#end
  #write (Ouf,concat("  <",str(BallSpd[I].x,8,14),",",str(BallSpd[I].y,8,14),",",str(BallSpd[I].z,8,14),">\n"))
#write(Ouf,"}\n")
#write (Ouf,"#declare BallFree=array[",dimension_size(BallFree,1),"] {\n")
#declare I=0;
#while(I<dimension_size(BallFree,1)-1)
  #write (Ouf,concat("  ",str(BallFree[I],1,0),",\n"))
  #declare I=I+1;
#end
  #write (Ouf,concat("  ",str(BallFree[I],1,0),"\n"))
#write(Ouf,"}\n")
Log("\n\n")
#fclose Ouf
#end

#macro MakeBallFree()
  #ifndef(BallFree)
    #declare BallFree=array[dimension_size(BallPos,1)]
    #declare I=0;
    #while(I<dimension_size(BallFree,1))
      #declare BallFree[I]=1;
      #declare I=I+1;
    #end
  #end
#end 

//Do this step. No actions are before this point, only macros

//If starting fresh, zero out StateVec
#if(MClock=0)      
  //zero out Mechanic Log
  #fopen Ouf MechanicLog write
  #fclose Ouf
  #fopen LogF MechanicLog append  
  Log(concat("Zeroing State Vector File ",StateVec,"\n"))
  #fopen SV StateVec write
  #fclose SV
  #fclose LogF
#end

#fopen LogF MechanicLog append  

//Read in previous state vector
Log(concat("Including State Vector File ",StateVec,"\n"))
#declare StateVecTime=-1;
#include StateVec
               
//Necessary to declare macro

//If necessary, run up to current time
#ifndef(StateVecTime)
  Log("No StateVecTime in State Vector File\n")
  Log(concat("Including Original State Vector File ",OrigVec,"\n"))
  #include OrigVec
  MakeBallFree()
  #if(MClock!=0)
    Log(concat("Running up to Start Point ",str(MClock,0,4),"\n"))
    #declare Q=0;
    #while(Q<(MClock-MDelta/2))
      DoStep(Q,BallPos,BallSpd,BallFree)
      #declare Q=Q+MDelta;
    #end
    Log(concat("At Start Point ",str(MClock,0,4),"\n"))
  #end
#else
  #if(abs(StateVecTime-MClock)>1e-6)
    Log(concat("Incorrect StateVecTime in State Vector File (",str(StateVecTime,8,14),")\n"))
    Log(concat("                                 Difference: ",str(StateVecTime-MClock,8,14),"\n"))
    #include OrigVec
    MakeBallFree()
    #if(MClock!=0)
    Log(concat("Running up to Start Point ",str(MClock,0,4),"\n"))
      #declare Q=0;
      #while(Q<(MClock-MDelta/2))
        DoStep(Q,BallPos,BallSpd,BallFree)
        #declare Q=Q+MDelta;
      #end
    #end
    Log(concat("At Start Point ",str(MClock,0,4),"\n"))
  #end
#end               
//
//Do this step
DoStep(MClock,BallPos,BallSpd,BallFree)

//Write out results
WriteStateVectors()

//When you are all done,
//state vectors BallPos and BallSpd are valid for this frame.

//#debug "Done with Mechanics Engine (mechanic.inc)\n"

