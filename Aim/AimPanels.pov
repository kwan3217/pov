#version unofficial MegaPov 1.11;
#include "host.inc"
#fopen ouf concat(Host,".txt") append
#write( ouf, concat(date("%Y %b %d %H:%M:%S"),Host," Render - frame ",str(frame_number,0,0)," of ",str(final_frame,0,0),"\n"))
#fclose ouf
#debug concat("\u001b];",Host," Render - frame ",str(frame_number,0,0)," of ",str(final_frame,0,0),"\a")

#if(clock>(26/310) & clock < (165/310)) #declare Quick=0; #end
#if(clock>(234/310) & clock < (1780/1858)) #declare Quick=0; #end
#include "KwanMath.inc"
#declare Deploy=BLinterp(0,0,0.2,1,clock);
#declare CipsDeploy=BLinterp(0.8,0,0.9,1,clock);
#declare SofieDeploy=BLinterp(0.3,0,0.4,1,clock);
#declare Lines=0;
#declare StartTime=100;
#declare EndTime=200;
#include "AimPanels1.inc"
PrintNumber("Deploy: ",Deploy)

#declare PegCenter=0;

#declare CIPSLat=-60;
#declare CIPSLon=180;
#declare CIPSDist=2.5;
#declare SOFIELat=-45;
#declare SOFIELon=60;
#declare SOFIEDist=2.5;
#declare CDELat=60;
#declare CDELon=60;
#declare CDEDist=2.5;

#switch(clock)
  #range(0,0.2)
	  #declare Lon=Linterp(0,0,0.2,100,clock);
		#declare Lat=Linterp(0,30,0.2,SOFIELat,clock);
		#declare CamDist=10;
		#break
  #range(0.2,0.3)
	  #declare Lon=Linterp(0.2,100,0.3,SOFIELon,clock);
		#declare Lat=SOFIELat;
		#declare CamDist=Linterp(0.2,10,0.3,SOFIEDist,clock);
		#break
  #range(0.3,0.5)
	  #declare Lon=SOFIELon;
		#declare Lat=SOFIELat;
		#declare CamDist=SOFIEDist;
		#break
  #range(0.5,0.6)
	  #declare Lon=Linterp(0.5,SOFIELon,0.6,CDELon,clock);
		#declare Lat=Linterp(0.5,SOFIELat,0.6,CDELat,clock);
		#declare CamDist=CDEDist;
		#break
  #range(0.6,0.7)
	  #declare Lon=CDELon;
		#declare Lat=CDELat;
		#declare CamDist=CDEDist;
		#break
  #range(0.7,0.8)
	  #declare Lon=Linterp(0.7,CDELon,0.8,CIPSLon,clock);;
		#declare Lat=Linterp(0.7,CDELat,0.8,CIPSLat,clock);
		#declare CamDist=2.5;
		#break
  #range(0.8,0.9)
	  #declare Lon=CIPSLon;
		#declare Lat=CIPSLat;
		#declare CamDist=2.5;
		#break
  #range(0.9,1.0)
	  #declare Lon=Linterp(0.9,CIPSLon,1.0,CDELat,clock);
		#declare Lat=Linterp(0.9,CIPSLat,1.0,30,clock);
		#declare CamDist=Linterp(0.9,CIPSDist,1.0,10,clock);
		#break
#end 

PrintNumber("CameraLat:  ",Lat)
PrintNumber("CameraLon:  ",Lon)
PrintNumber("CameraDist: ",CamDist)


#declare Look=Pos+Nose*PegCenter/*+vturbulence(2,0.5,6,y*clock*2)*CamDist/20*/;
#declare CamLoc=Look+vnormalize(
    N*cos(radians(Lat))*cos(radians(Lon))+
		T*cos(radians(Lat))*sin(radians(Lon))+
		R*sin(radians(Lat))
	)*CamDist/*+vturbulence(2,0.5,6,x*clock*10)*CamDist/10*/;
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
  }
#end
*/

Camera(CamLoc,Look,0.3,1,0,Angle)
light_source {
  CamLoc-Pos
  color rgb <1,1,1>*BLinterp(0.2,0,0.3,1,clock)*BLinterp(0.9,1,1.0,0,clock)
}
