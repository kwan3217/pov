//Physical constants
#declare Re=6378.137;
#declare Hc=82;
#declare J2=0.00108263;
#declare EP=365.2421897;
#declare Mu=398600.4415;
#declare EarthRate=2*pi/(EP*86400);

//Primary Orbit parameters
#declare Alt=560;
#declare BetaD=9;
#declare SunDecD=23.5;

//CV parameters
#declare CVBase=30;
#declare CVTop=130;

//Cips observation parameters
#declare CipsStartP=1235.45;
#declare CipsEndP=2378.24;
#declare CipsCadence=34;

//Sofie observation parameters
#declare SofieObsDuration=113;
#declare SofieCalDuration=32;

//Maneuver parameters
#declare ManvStart2P=1587.43;

#include "AimAttDerived.inc"
