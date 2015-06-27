#version unofficial MegaPov 1.11;
#include "host.inc"
#fopen ouf concat(Host,".txt") append
#write( ouf, concat(date("%Y %b %d %H:%M:%S"),Host," Render - frame ",str(frame_number,0,0)," of ",str(final_frame,0,0),"\n"))
#fclose ouf
#debug concat("\u001b];",Host," Render - frame ",str(frame_number,0,0)," of ",str(final_frame,0,0),"\a")

//#declare Quick=0;
#declare Deploy=1;
#declare CipsDeploy=1;
#declare SofieDeploy=1;
#ifndef(Lines) #declare Lines=0; #end
#include "AimPanels1.inc"
PrintNumber("Deploy: ",Deploy)

#declare PegCenter=0;

#switch(AimClock)
  #range(-99999,TermOverflight-90)
	  #declare Lon=90;
		#declare Lat=30;
		#declare CamDist=10e5;
		#break
  #range(TermOverflight-90,TermOverflight+90)
	  #declare Lon=Linterp(TermOverflight-90,270,TermOverflight+90,450,AimClock);
		#declare Lat=30+30*sin(Linterp(TermOverflight-90,0,TermOverflight+90,pi,AimClock));
		#declare CamDist=10e6;
		#break
  #range(TermOverflight+90,99999)
	  #declare Lon=270;
		#declare Lat=80;
		#declare CamDist=10e6;
		#break
#end 

#declare Deploy=clock*1.5;

PrintNumber("CameraLat:  ",Lat)
PrintNumber("CameraLon:  ",Lon)
PrintNumber("CameraDist: ",CamDist)


#declare Look=Pos+Nose*PegCenter;
#declare CamLoc=Look+vnormalize(
    N*cos(radians(Lat))*cos(radians(Lon))+
		T*cos(radians(Lat))*sin(radians(Lon))+
		R*sin(radians(Lat))
	)*CamDist;
#declare Angle=atan(4/3);

PrintVector("Look:   ",Look)
PrintVector("CamLoc: ",CamLoc)

Earth(CamLoc,Look,Angle)
/*
#declare Fade=min(BLinterp(0,0,30,1,frame_number),BLinterp(final_frame-29,1,final_frame,0,frame_number));
#if(Fade<1)
  sphere {	
    0,1
    pigment {color rgbf <1,1,1,Fade>}
    finish {ambient 0 diffuse 0}
    translate CamLoc-Pos
    hollow
    no_shadow
  }
#end
*/
Camera(CamLoc,Look,0,1,0,Angle)
