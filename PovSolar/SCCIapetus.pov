#version unofficial MegaPov 1.11;
#include "Terminal.inc"

#include "PlanetConst.inc"
#include "Calendar.inc"

#declare Target=Ia;
#declare Time=JulianDate(2005,1,01,02,47,64.184)+clock/4;
#declare ChaseDistance=40;
#declare ChaseOffset=-y*10;
#declare ChaseScale=0.1;

#declare CameraAngle=3.5;

#include "SaturnChaseCommon.inc"
