#version unofficial MegaPov 1.11;
#include "/home/chrisj/host.inc"
#debug concat("\u001b];",Host," Render - frame ",str(frame_number,0,0)," of ",str(final_frame,0,0),"\a")

#include "PlanetConst.inc"
#include "Calendar.inc"

#declare Target=Di;
#declare Time=JulianDate(2004,12,14,16,00,64.184)+(clock*2-1)*1/24;
#declare ChaseDistance=40;
#declare ChaseOffset=-y*10;
#declare ChaseScale=0.1;

#declare CameraAngle=3.5;

#include "SaturnChaseCommon.inc"
