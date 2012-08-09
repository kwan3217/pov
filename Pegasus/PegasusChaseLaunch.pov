#declare ClockMode=1;
#include "PegasusLaunchCommon.inc"

#declare Look=Pos+Att*8.7;
#declare CameraSpline=spline {
  quadratic_spline
  -5,<0.0,  2.0, 50>,
  -1,<0.0,  2.0, 50>,
	 2,<0.0,  2.0, 50>,
	10,<pi/2,-25.0, 50>,
	11,<1.7,-25.0, 50>,
	15,<1.7,-10.0, 40>,
}
#declare CameraVec=CameraSpline(PegasusClock);
#declare theta=CameraVec.x;
#declare alt=CameraVec.y;
#declare dist=CameraVec.z;

#declare DeltaCamLoc=vnormalize(NA*cos(theta)*dist-TA*sin(theta)*dist+R*alt)*dist;
#declare CamLoc=Look+DeltaCamLoc;
#declare Angle=atan(4/3);
Earth(CamLoc,Look,Angle)
Camera(CamLoc,Look,Angle)
PrintVector("DeltaCamLoc: ",DeltaCamLoc)
