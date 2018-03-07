//#version unofficial Megapov 1.22;

#include "KwanMath.inc"

global_settings {
//  right_handed
  charset utf8
}

#declare fps=24;
PrintNumber("Frames/sec: ",fps)

#declare NumScenes=1;
#declare SceneTime=array[NumScenes] {33}

#declare I=0;
#declare TotalTime=0;
#while(I<NumScenes)
  #declare TotalTime=TotalTime+SceneTime[I];
  #declare I=I+1;
#end
PrintNumber("TotalTime: ",TotalTime)

#declare NumFrames=fps*TotalTime;
PrintNumber("NumFrames: ",NumFrames)

//Calculate video clocks
#declare VideoClockF=frame_number;  //Frame number in the whole video
#declare VideoClockS=VideoClockF/fps;  //Time from beginning of video in seconds
#declare VideoClockN=VideoClockF/NumFrames; //Fraction of the whole video, [0,1)
PrintNumber("VideoClockF: ",VideoClockF)
PrintNumber("VideoClockS: ",VideoClockS)
PrintNumber("VideoClockN: ",VideoClockN)

//Find current scene number
#declare SceneEpochS0=0;            //Starting time of the current scene in seconds
#declare SceneEpochS1=SceneTime[0]; //Ending time of current scene in seconds
#declare Scene=0;                   //Current scene number
#while((Scene<NumScenes) & (VideoClockS>SceneEpochS1))
  #declare Scene=Scene+1;
  #declare SceneEpochS0=SceneEpochS1;
  #if(Scene<NumScenes) 
    #declare SceneEpochS1=SceneEpochS1+SceneTime[Scene];
  #end
#end
#declare SceneLengthS=SceneEpochS1-SceneEpochS0; //Length of current scene in seconds

PrintNumber("Scene: "+Scene)

//Calculate scene clocks
#declare SceneClockS=VideoClockS-SceneEpochS0; //Time from beginning of scene in seconds
#declare SceneClockF=SceneClockS*fps;          //Frames from beginning of scene
#declare SceneClockN=Linterp(SceneEpochS0,0,SceneEpochS1,1,VideoClockS); //Fraction of the current scene, [0,1)
PrintNumber("SceneClockF: ",SceneClockF)
PrintNumber("SceneClockS: ",SceneClockS)
PrintNumber("SceneClockN: ",SceneClockN)

#macro CalcShotTime(ShotTime)
  #local NumShots=dimension_size(ShotTime,1);
  #if (NumShots=1)
    #declare ShotClockS=SceneClockS; //Time from beginning of shot in seconds
    #declare ShotClockF=SceneClockF; //Frames from beginning of shot
    #declare ShotClockN=SceneClockN; //Normalized shot time, [0,1)
    #declare Shot=0;
  #else
    //Calculate the nominal sum of the shot lengths, according to the ShotTime array.
    #local I=0;
    #local TotalShotTime=0;
    #while(I<NumShots)
      #local TotalShotTime=TotalShotTime+ShotTime[I];
      #local I=I+1;
    #end
    PrintNumber("TotalShotTime: ",TotalShotTime)

    //Fix the ShotTime array, so it fits within the scene perfectly.
    #local ShotFactor=SceneLengthS/TotalShotTime;
    PrintNumber("ShotFactor: ",ShotFactor)
    #local I=0;
    #while(I<NumShots)
      #declare ShotTime[I]=ShotFactor*ShotTime[I];
      #local I=I+1;
    #end

    //Now the time of all the shots is the same as the scene time

    //Find current shot number
    #local ShotEpochS0=0;
    #local ShotEpochS1=ShotTime[0];
    #declare Shot=0;
    #while((Shot<NumShots) & (SceneClockS>ShotEpochS1))
      #declare Shot=Shot+1;
      #declare ShotEpochS0=ShotEpochS1;
      #if(Shot<NumShots) 
        #declare ShotEpochS1=ShotEpochS1+ShotTime[Shot];
      #end
    #end

    //Calculate scene clocks
    #declare ShotClockS=SceneClockS-ShotEpochS0;
    #declare ShotClockF=ShotClockS*fps;
    #declare ShotClockN=Linterp(ShotEpochS0,0,ShotEpochS1,1,SceneClockS);

  #end
  PrintNumber("Shot: "+Shot)
  PrintNumber("ShotClockF: ",ShotClockF)
  PrintNumber("ShotClockS: ",ShotClockS)
  PrintNumber("ShotClockN: ",ShotClockN)
#end

#macro FadeIn2(Color,FadeClock)
  (Color+Linterp(0,<1,1,1,1>-Color,1,<0,0,0,0>,FadeClock))
#end

#macro Fade(Color,FadeClock)
  pigment {color rgbf FadeIn2(Color,FadeClock)}
#end

#switch(Scene)
  #case(0)
    #include "Scene00.inc"
    #break
#end
