#version unofficial MegaPov 1.11;
#include "host.inc"
#fopen ouf concat(Host,".txt") append
#write( ouf, concat(date("%Y %b %d %H:%M:%S"),Host," Render - frame ",str(frame_number,0,0)," of ",str(final_frame,0,0),"\n"))
#fclose ouf
#debug concat("\u001b];",Host," Render - frame ",str(frame_number,0,0)," of ",str(final_frame,0,0),"\a")

//#declare Quick=1;
#declare ClockMode=0;
#include "PegasusLaunchCommonFMA.inc"

#switch(PegasusClock)
  #range(-99999,FSSep)
    #declare PegCenter=8.7;
		#break
  #range(FSSep,FSSep+5)
    #declare PegCenter=Linterp(FSSep,8.7,FSSep+5,13.75,PegasusClock); 
		#break
  #range(FSSep+5,SSSep)
    #declare PegCenter=13.75;
		#break
  #range(SSSep,SSSep+5)
    #declare PegCenter=Linterp(SSSep,13.75,SSSep+5,14.5,PegasusClock); 
		#break
  #range(SSSep+5,SCSep)
    #declare PegCenter=14.5;
		#break
  #range(SCSep,99999)
    #declare PegCenter=0;
		#break
#end 
//#declare Fade=min(1,Linterp(final_frame-30,1,final_frame,0,frame_number));

#switch(PegasusClock)
  #range(-10,-5)
//    #declare Fade=min(Linterp(0,0,1,1,MusicClock),1);
    #declare PegCenter=Linterp(-10,0,-5,17,PegasusClock);
	  #declare Lon=Linterp(-10,0,-5,0,PegasusClock);
		#declare Lat=Linterp(-10,0,-5,0,PegasusClock);
		#declare CamDist=Linterp(-10,3,-5,5,PegasusClock);
		#break
  #range(-5,0)
    #declare PegCenter=Linterp(-5,17,0,8.7,PegasusClock);
	  #declare Lon=0;
		#declare Lat=0;
		#declare CamDist=Linterp(-5,5,0,50,PegasusClock);
		#break
  #range(0,5)
	  #declare Lon=Linterp(0,0,5,15,PegasusClock);
		#declare Lat=degrees(atan2(Linterp(0,0,5,-2.5,PegasusClock),1));
		#declare CamDist=50;
		#break
  #range(5,15)
	  #declare Lon=Linterp(5,15,15,70,PegasusClock);
		#declare Lat=Linterp(5,degrees(atan2(-2.5,1)),20,-10,PegasusClock);
		#declare CamDist=Linterp(5,50,20,25,PegasusClock);
		#break
  #range(15,20)
	  #declare Lon=Linterp(15,70,20,80,PegasusClock);
    #declare Lat15=Linterp(5,degrees(atan2(-2.5,1)),20,-10,15);
		#declare Lat=Linterp(15,Lat15,20,-3,PegasusClock);
		#declare CamDist=Linterp(5,50,20,25,PegasusClock);
		#break
  #range(20,40)
	  #declare Lon=80;
		#declare Lat=Linterp(20,-3,40,10,PegasusClock);
		#declare CamDist=25;
		#break
  #range(40,60)
	  #declare Lon=Linterp(40,80,60,0,PegasusClock);
		#declare Lat=Linterp(40,10,60,0,PegasusClock);
		#declare CamDist=25;
		#break
  #range(60,112)
	  #declare Lon=0;
		#declare Lat=0;
		#declare CamDist=25;
		#break
  #range(112,123)
	  #declare Lon=Linterp(112,0,123,30,PegasusClock);
		#declare Lat=Linterp(112,0,123,30,PegasusClock);
		#declare CamDist=25;
		#break
  #range(123,152)
	  #declare Lon=30;
		#declare Lat=30;
		#declare CamDist=25;
		#break
  #range(152,162)
	  #declare Lon=Linterp(152,30,162,-30,PegasusClock);
		#declare Lat=30;
		#declare CamDist=25;
		#break
	#range(162,262)
	  #declare Lon=-30;
		#declare Lat=30;
		#declare CamDist=25;
		#break
	#range(262,322)
	  #declare Lon=Linterp(262,-30,322,330,PegasusClock);
		#declare Lat=30*cos(Linterp(262,0,322,2*pi,PegasusClock));
		#declare CamDist=(25+7.5*(-1+cos(Linterp(262,0,322,2*pi,PegasusClock))));
		#break
	#range(322,334.5)
	  #declare Lon=Linterp(322,-30,334.5,45,PegasusClock);
		#declare Lat=30;
		#declare CamDist=BLinterp(SSSep,25,SSSep+5,10,PegasusClock);
		#break
  #range(334.5,99999)
	  #declare Lon=45;
		#declare Lat=30;
		#declare CamDist=BLinterp(SSSep,25,SSSep+5,10,PegasusClock);
		#break
#end 

PrintNumber("CameraLat:  ",Lat)
PrintNumber("CameraLon:  ",Lon)
PrintNumber("CameraDist: ",CamDist)


#declare Look=Pos+Nose*PegCenter;
#declare CamLoc=Look+vnormalize(
    NA*cos(radians(Lat))*cos(radians(Lon))+
		TA*cos(radians(Lat))*sin(radians(Lon))+
		R*sin(radians(Lat))
	)*CamDist;
#declare Angle=atan(4/3);

PrintVector("Look:   ",Look)
PrintVector("CamLoc: ",CamLoc)

Earth(CamLoc,Look,Angle)

PrintVector("Look:   ",Look)
PrintVector("CamLoc: ",CamLoc)

PrintVector("NA: ",NA)
PrintVector("TA: ",TA)
PrintVector("R:  ",R)

#declare Look=Pos+Nose*PegCenter;
#declare CamLoc=Look+vnormalize(
    NA*cos(radians(Lat))*cos(radians(Lon))+
		TA*cos(radians(Lat))*sin(radians(Lon))+
		R*sin(radians(Lat))
	)*CamDist;
#declare Angle=atan(4/3);

PrintVector("Look:   ",Look)
PrintVector("CamLoc: ",CamLoc)
#declare AuxLight=min(1,Linterp(-5,1,0,0,PegasusClock));
#if(AuxLight>0)
  light_source {
    CamLoc-Pos
    color rgb <1,1,1>*AuxLight
  }
#end
#ifdef(Fade)
#if(Fade<1)
  PrintNumber("Fade: ",Fade)
  sphere {
    0,1
    pigment {color rgbf <1,1,1,Fade>}
    finish {ambient 0 diffuse 0}
    translate CamLoc-Pos
    hollow
  }
#end
#else
#debug "No Fade"
#end
Camera(CamLoc,Look,0,1,0,Angle)
PrintNumber("Frame: ",frame_number)
PrintNumber("PegasusClock: ",PegasusClock)
#ifdef(MusicClock)PrintNumber("MusicClock:   ",MusicClock)#end
