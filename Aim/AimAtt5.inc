//Physical constants
#declare Re=6378.137;
#declare Rp=6357.751;
#declare Hc=82;
#declare J2=0.00108263;
#declare EP=365.2421897;
#declare Mu=398600.4415;
#declare EarthRate=2*pi/(EP*86400);

#macro LH(V)
  (<V.x,V.z,V.y>)
#end

//Primary Orbit parameters
#include "AimAtt09_600P9N.inc"
#include "AimAttDerived6.inc"

//CV parameters
#declare CVBase=30;
#declare CVTop=130;
#declare OzoneHeight=50;

