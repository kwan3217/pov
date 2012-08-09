//Physical constants
#declare Re=6378.137;
#declare Hc=82;
#declare J2=0.00108263;
#declare EP=365.2421897;
#declare Mu=398600.4415;
#declare EarthRate=2*pi/(EP*86400);

//Primary Orbit parameters
#declare Alt=600;
#declare BetaD=0;
#declare SunDecD=23.5;

//CV parameters
#declare CVBase=30;
#declare CVTop=130;
#declare OzoneHeight=50;

//Cips observation parameters
#declare CipsStartTheta=-14;
#declare CipsEndP=2378.24;
#declare CipsCadence=43.5;


//Sofie observation parameters
#declare SofieObsDuration=113;
#declare SofieCalDuration=32;

//Maneuver parameters
#declare ManvStart2P=1587.43;

#include "AimAttDerived3.inc"
