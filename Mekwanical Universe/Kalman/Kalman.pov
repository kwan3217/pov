#version unofficial Megapov 1.22;

#include "KwanMath.inc"

global_settings {
  right_handed
  charset utf8
}

#declare fps=24;
PrintNumber("Frames/sec: ",fps)

//Each slot is the number of seconds in one shot, or a marker
//-1 divides scenes
//use 0 to comment out a shot without disturbing the order
//Don't end the last scene with -1
#declare ShotTime=array[8] {
  4,-1,
  0,-1,
  4,18,4,18}

//===De-raggedize the ShotTime array===
//Count up the elements to put into a rectangular array
#declare NumScenes=1;
#declare MaxSceneShots=0;
#declare NumSceneShots=0;
#declare I=0;
#while(I<dimension_size(ShotTime,1))
  #if(ShotTime[I]>=0)
    #declare NumSceneShots=NumSceneShots+1;
  #else
    #declare NumScenes=NumScenes+1;
    #if(NumSceneShots>MaxSceneShots)
      #declare MaxSceneShots=NumSceneShots;
    #end
    #declare NumSceneShots=0;
  #end
  #declare I=I+1;
#end
#if(NumSceneShots>MaxSceneShots)
  #declare MaxSceneShots=NumSceneShots;
#end
PrintInt("NumScenes: ",NumScenes)
PrintInt("MaxSceneShots: ",MaxSceneShots)

//Build the (rectangular) arrays
#declare ShotTime2=array[NumScenes][MaxSceneShots]
#declare SceneTime=array[NumScenes];
#declare NumSceneShots=array[NumScenes];
#declare Scene=0;
#declare Shot=0;
#declare TotalTime=0;
#declare I=0;
#while(I<dimension_size(ShotTime,1))
  #if(ShotTime[I]>=0)
    #ifndef(SceneTime[Scene])
      #declare SceneTime[Scene]=ShotTime[I];
      #declare NumSceneShots[Scene]=1;
    #else
      #declare SceneTime[Scene]=ShotTime[I]+SceneTime[Scene];
      #declare NumSceneShots[Scene]=NumSceneShots[Scene]+1;
    #end
    #declare TotalTime=TotalTime+ShotTime[I];
    #declare ShotTime2[Scene][Shot]=ShotTime[I];
    #declare Shot=Shot+1;
  #else
    #declare Scene=Scene+1;
    #declare Shot=0;
  #end
  #declare I=I+1;
#end

#declare ShotTime=ShotTime2;
PrintNumber("TotalTime: ",TotalTime)
#declare NumFrames=floor(fps*TotalTime);
PrintInt("NumFrames: ",NumFrames)

//Calculate video clocks
#declare VideoClockF=frame_number;
#declare VideoClockS=VideoClockF/fps;
#declare VideoClockN=VideoClockF/NumFrames;
PrintInt("VideoClockF: ",VideoClockF)
PrintNumber("VideoClockS: ",VideoClockS)
PrintNumber("VideoClockN: ",VideoClockN)

//Find current scene number
#declare SceneEpochS0=0;
#declare SceneEpochS1=SceneTime[0];
#declare Scene=0;
#while((Scene<NumScenes) & (VideoClockS>SceneEpochS1))
  #declare Scene=Scene+1;
  #declare SceneEpochS0=SceneEpochS1;
  #if(Scene<NumScenes) 
    #declare SceneEpochS1=SceneEpochS1+SceneTime[Scene];
  #end
#end
#declare SceneLengthS=SceneEpochS1-SceneEpochS0;

PrintInt("Scene: "+Scene)

//Calculate scene clocks
#declare SceneClockS=VideoClockS-SceneEpochS0;
#declare SceneClockF=SceneClockS*fps;
#declare SceneClockN=Linterp(SceneEpochS0,0,SceneEpochS1,1,VideoClockS);
PrintInt("SceneClockF: ",SceneClockF)
PrintNumber("SceneClockS: ",SceneClockS)
PrintNumber("SceneClockN: ",SceneClockN)

//Calculate shot clocks and current shot
#local I=0;
#local NumShots=NumSceneShots[Scene];
#if (NumShots=1)
  #declare ShotClockS=SceneClockS;
  #declare ShotClockF=SceneClockF;
  #declare ShotClockN=SceneClockN;
  #declare Shot=0;
#else
  //Now the time of all the shots is the same as the scene time
  //Find current shot number
  #local ShotEpochS0=0;
  #local ShotEpochS1=ShotTime[Scene][0];
  #declare Shot=0;
  #while((Shot<NumShots) & (SceneClockS>ShotEpochS1))
    #declare Shot=Shot+1;
    #declare ShotEpochS0=ShotEpochS1;
    #if(Shot<NumShots) 
      #declare ShotEpochS1=ShotEpochS1+ShotTime[Scene][Shot];
    #end
  #end

  #declare ShotClockS=SceneClockS-ShotEpochS0;
  #declare ShotClockF=ShotClockS*fps;
  #declare ShotClockN=Linterp(ShotEpochS0,0,ShotEpochS1,1,SceneClockS);

#end
PrintInt("Shot: "+Shot)
PrintInt("ShotClockF: ",ShotClockF)
PrintNumber("ShotClockS: ",ShotClockS)
PrintNumber("ShotClockN: ",ShotClockN)

#macro FadeIn2(Color,FadeClock)
  (Color+Linterp(0,<1,1,1,1>-Color,1,<0,0,0,0>,FadeClock))
#end

#macro Fade(Color,FadeClock)
  pigment {color rgbf FadeIn2(Color,FadeClock)}
#end

#declare ShotInc=concat("Scene",str(Scene,-3,0),"_Shot",str(Shot,-3,0),".inc");
#debug concat("Including: ",ShotInc,"\n")

#include ShotInc


