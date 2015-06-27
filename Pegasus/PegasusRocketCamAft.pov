#include "/home/chrisj/host.inc"
#debug concat("\u001b];",Host," Render - frame ",str(frame_number,0,0)," of ",str(final_frame,0,0),"\a")

//#declare Quick=1;
#include "PegasusLaunchCommon3.inc"

#declare Wing=vcross(Nose,Tail);

#declare Look=PlanePos;
#declare CamLoc=Pos-Wing*1.4/2+Nose*13;
#declare Angle=atan(4/3);

Earth(CamLoc,Look,Angle)
Camera(CamLoc,Look,0,1,0,Angle)
