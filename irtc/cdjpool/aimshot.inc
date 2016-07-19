//Aimshot.inc

#declare Threshold=0.1;
        
#macro CheckTunnel(Start,Stop,Bp,Free,B1,B2)
  #local I=0;
  #local Ref=(Stop-Start);
  #local RefLen=vlength(Ref);
  #declare TunnelOK=1;
  #while(I<dimension_size(Free,1) & TunnelOK=1)
    #if(I!=B1 & I!=B2 & Free[I])    
      #local This=Bp[I]-Start;
      #local Par=((vdot(Ref,This))/pow(vlength(Ref),2))*Ref;
      #local Perp=This-Par;
      #if (vlength(Par)>0 & vlength(Par)<RefLen & vlength(Perp)<2)
        #declare TunnelOK=0;
      #end
    #end 
    #local I=I+1;
  #end
#end

#macro DispVec(Label,V)
  #warning concat(Label,": <",str(V.x,8,14),",",str(V.y,8,14),",",str(V.z,8,14),">  (Len: ",str(vlength(V),8,14),")\n")
#end
  
#macro DispReal(Label,V)
  #warning concat(Label,": ",str(V,8,14),"\n")
#end
  
#macro Aim(Time,CuePos,ObjPos,HolePos)
//  DispVec(" HolePos (H)",HolePos)
//  DispVec("  ObjPos (B)",ObjPos)
//  DispVec("  CuePos (C)",CuePos)
  #declare HoleVec=HolePos-ObjPos;
//  DispVec(" HoleVec (V)",HoleVec)
  #declare AimPoint=-2*vnormalize(HoleVec)+ObjPos;
//  DispVec("AimPoint (A)",AimPoint)
  #declare ShootVec=vnormalize(AimPoint-CuePos);  
//  DispVec("ShootVec (S)",ShootVec)
  #declare ShotStraightness=vdot(vnormalize(HoleVec),ShootVec);
//  DispReal("Straight (T)",ShotStraightness)
  #declare PathLength=vlength(AimPoint-CuePos)+(vlength(HoleVec)/ShotStraightness);
//  #warning concat("Cue->Aimpoint: ",str(vlength(AimPoint-CuePos),0,4),"\n")
//  #warning concat(" Target->Hole: ",str(vlength(HoleVec),0,4),"\n")
  #declare Speed=PathLength/Time;
//  #warning concat("  Path Length: ",str(PathLength,0,4),"\n")
//  #warning concat("        Speed: ",str(Speed,0,4),"\n")
  #declare ShootVec=ShootVec*Speed;
  #declare ShotPossible=(ShotStraightness>Threshold);
#end

#macro MakeShot(Target)
  #declare ShotPossible=0;
  #local I=0;
  #while(ShotPossible=0 & I<dimension_size(Hole,1))
    Aim(6,BallPos[0],BallPos[Target],Hole[I])
    #if(ShotPossible)     
      CheckTunnel(BallPos[0],AimPoint,BallPos,BallFree,0,Target)
      #if(TunnelOK=1)
        CheckTunnel(AimPoint,Hole[I],BallPos,BallFree,Target,-1)
        #if(TunnelOK=1)
          #ifdef(Log)
            Log(concat("Ball ",str(Target,0,0),", Hole ",str(I,0,0),": Shot Possible (straightness = ",str(ShotStraightness,0,3),")\n"))
          #else
            #warning concat("Ball ",str(Target,0,0),", Hole ",str(I,0,0),": Shot Possible (straightness = ",str(ShotStraightness,0,3),")\n")
          #end
          #declare TargetBall=Target;
          #declare BallSpd[0]=ShootVec;
        #else
          #declare ShotPossible=0;
          #declare I=I+1;
          #warning concat("Ball ",str(Target,0,0),", Hole ",str(I,0,0),": Shot not Possible (object ball blocked)\n")
        #end
      #else
        #declare ShotPossible=0;
        #warning concat("Ball ",str(Target,0,0),", Hole ",str(I,0,0),": Shot not Possible (Cue ball blocked)\n")
        #declare I=I+1;
      #end
    #else
//      #warning concat("Ball ",str(Target,0,0),", Hole ",str(I,0,0),": Shot not Possible (straightness = ",str(ShotStraightness,0,3),")\n")
      #declare I=I+1;
    #end
  #end
#end

#macro ChooseShot(Lo,Hi)
  #declare ShotPossible=0;
  #declare Threshold=0.8;
  #while(Threshold>0.1 & ShotPossible=0)
    #warning concat("Looking for shots at threshold ",str(Threshold,0,2),"\n")
    #declare I=Lo;
    #while(I<=Hi & ShotPossible=0)
//      #warning concat("Looking for shots at ball ",str(I,0,0),"\n")
      #if(BallFree[I])
        MakeShot(I)  
      #end
      #declare I=I+1;
    #end 
    #declare Threshold=Threshold-0.1;
  #end 
  #if(ShotPossible=0)
    #warning "No shots possible to 0.1 straightness\n"
  #end
#end

