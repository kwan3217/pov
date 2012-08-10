#version unofficial MegaPov 1.0;

#include "Calendar.inc"

#include "PlanetConst.inc"
#include "Math.inc"
#include "Rotation.inc"
#include "Kepler.inc"

#declare Y=val(date("%Y"));
#declare M=val(date("%m"));
#declare D=val(date("%d"));
#declare H=val(date("%H"))-val(date("%z"))/100;
#declare N=val(date("%M"));
#declare S=val(date("%S"))+64.184;
#declare Time=JulianDate(Y,M,D,H,N,S)+clock;
#declare PlanetPos=array[1000];
PrintDate("Time (SMJDCD): ",Time)
#debug concat(StringDate(Time),"\n")

#declare CmdLine=concat("java org.kwansystems.ephemeris.PlanetPosPOV ",str(Time,0,6))
#debug concat("\n",CmdLine,"\n")
#system CmdLine

PrintVector("Earth: ",PlanetPos[399])
PrintVector("Mars:  ",PlanetPos[499])

PrintVector("Dist:  ",PlanetPos[499]-PlanetPos[399])
PrintNumber("Light: ",vlength(PlanetPos[499]-PlanetPos[399])/299792.458)
