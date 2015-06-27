#version unofficial MegaPov 1.0;

global_settings {exposure 1.6}

#include "Calendar.inc"

#include "PlanetConst.inc"
#include "Math.inc"
#include "Rotation.inc"
#include "Kepler.inc"
#include "KeplerGaussFG.inc"
#include "Turn.inc"
#include "../Voyager/Voyager.inc"
#include "../LocLook.inc"

//Epoch is Entry interface time. After this, there is significant drag, etc, IE its not in orbit.
#declare Epoch=53029.701354166;
#declare Tfca=clock*3600;
PrintNumber("Tfca:  ",Tfca)
#declare Time=Epoch+Tfca/86400;

#declare LightSpeed=299792.458; // km/s

#macro HandSwap(V)
  (<V.x,V.z,V.y>)
#end

//Numbers are in horizons right-handed coordinates J2000Ecl, Planet centered
#declare SCPosEpoch=HandSwap(<-1.237243944200919E+03,-3.291141306866659E+03, 2.131226194147659E+02>);
#declare SCVelEpoch=HandSwap(< 5.184069196141672E+00,-8.738754744970176E-01,-2.198705941484093E+00>);
#declare MarMu=42828.301;
#declare SCPos=<0,0,0>;
#declare SCVel=<0,0,0>;
#declare TrVel2=<0,0,0>;
#declare TrPos2=<0,0,0>;

KeplerFG(SCPosEpoch,SCVelEpoch,Tfca,MarMu,SCPos,SCVel)

PrintDate("Epoch (SMJDTDB): ",Epoch)
PrintDate("Time (SMJDTDB): ",Time)
#declare MarsPos=<0,0,0>;
#declare PlanetPos=array[1000];
#declare CmdLine=concat("java org.kwansystems.ephemeris.PlanetPosPOV ",str(Time,0,9))
#debug CmdLine
#system CmdLine
#declare I=0;
#while(I<1000) 
  #if(defined(PlanetPos[I])) PrintVector(concat("PlanetPos[",str(I,0,0),"]: "),PlanetPos[I]) #end
  #declare I=I+1;
#end

#declare SystemScale=0.01;
#declare Detail=-1;
#declare SuDetail=99;
#declare MaDetail=99;
#declare PhDetail=99;
#declare DeDetail=99;
#declare includeAsteroids=0;
#declare IncludeMoons=0;
#declare SunLights=10;
#declare SunBright=2;
//#declare SunSide=1;

#declare SunPos=-PlanetPos[Ma]+PlanetPos[Su];
#declare EarthPos=-PlanetPos[Ma]+PlanetPos[Ea];

PrintNumber("Light Time (s): ",vlength(EarthPos)/LightSpeed)



#declare MaRelVec=vnormalize(MarsPos-SCPos);

//#declare LookAtPos=MarsPos;
#declare LookAtPos=SCPos+SCVel*1000;

PrintVector("SCPos:   ",SCPos)
PrintVector("LookAt:  ",LookAtPos)
#declare SCBoost=100;
#declare LookVec=vnormalize(vnormalize(SCPos-LookAtPos)+0.03*y-0.03*z)*0.06*SCBoost;
PrintVector("LookVec: ",LookVec)
#declare CameraPos=LookVec+SCPos;
#declare LookAtPos=SCPos+SCVel*1000+LookVec;

#include "PlanetMod.inc"

#declare MERALat=radians(- 14.5718);
#declare MERALon=radians( 175.4785);
#declare MERAAlt=0;
#declare MERAVec=AMars*lla2xyz(<MERALat,MERALon,MERAAlt>,(1-BMars/AMars));
PrintVector("MerAVec: ",MERAVec)
#declare MERBLat=radians(-  1.9483);
#declare MERBLon=radians( 354.4742);
#declare MERBAlt=0;
#declare MERBVec=AMars*lla2xyz(<MERBLat,MERBLon,MERBAlt>,(1-BMars/AMars));
PrintVector("MerBVec: ",MERBVec)

object {
  MarsModel
  scale SystemScale
  Rotate(Ma)
}

#declare MERAPos=RotateV(SystemScale*MERAVec,Ma);
PrintVector("MerAPos: ",MERAPos)
#declare MERBPos=RotateV(SystemScale*MERBVec,Ma);

sphere {
  MERAPos 100*SystemScale
	pigment {color rgb <0,0,1>}
	finish {ambient 1 diffuse 0}
}

sphere {
  MERBVec 100
	scale SystemScale
	Rotate(Ma)
	pigment {color rgb <1,0,0>}
	finish {ambient 1 diffuse 0}
}

object {
  SunModel
  translate SunPos
  scale SystemScale
}

SunFlare(SunPos,CameraPos*SystemScale,10)

#declare MoonBoost=1;
object {PlanetModel[Ph] scale MoonBoost Rotate(Ph) translate (PlanetPos[Ph]-PlanetPos[Ma]) scale SystemScale}
object {PlanetModel[De] scale MoonBoost Rotate(De) translate (PlanetPos[De]-PlanetPos[Ma]) scale SystemScale}

#declare Axes=union {
  cylinder {
    0,x,0.05
    pigment {color rgb <1,0,0>}
    finish {ambient 0.5}
  }
  cylinder {
    0,y,0.05
    pigment {color rgb <0,1,0>}
    finish {ambient 0.5}
  }
  cylinder {
    0,z,0.05
    pigment {color rgb <0,0,1>}
    finish {ambient 0.5}
  }
  scale 0.05
  scale 0.001
  scale SCBoost
}
/*
#declare VoyTransform=transform {scale SCBoost LocationLookAt(SCPos,EarthPos,y) scale SystemScale}

object {
  Voyager 
  rotate -z*90 //Point HGA at +x
  transform {VoyTransform}
}

cylinder {
  SCPos,SCPos+SCVel*1,0.02
	scale SystemScale
	pigment {color rgb <1,1,0>}
}
*/

camera {
  up y
  right x*4/3
//  sky vnormalize(SunPos-CameraPos)
  location CameraPos*SystemScale
  look_at LookAtPos*SystemScale
//  angle 0.35	
  angle 30
//  angle 3.169
}

#declare CelestialSphereRad=1e6*0.99;
#declare StarRad=CelestialSphereRad*sqrt(2)*radians(30)/1024;
#declare LimitMag=5;
#declare BrightMax=1;
#declare ColorSat=0.3;
#declare Gamma=0.4;
#declare J2000Ecl=1;

#include "Stars.inc"

object {Stars translate CameraPos*SystemScale}

/*
http://spaceflightnow.com/mars/mera/status2.html
[Ed Note: All these times are Earth Received time. Light time is about 11m03.5s (663.5s) EST is UTC-5h]

The in-coming Opportunity rover is getting ever closer to Mars. Time to 
touchdown is now just four-and-a-half hours away.

Before the fiery entry into the Martian atmosphere can occur, the ring-shaped
cruise stage must be jettisoned from the descent module containing the 
Opportunity rover. This is scheduled for 11:44:46 p.m. EST.

Entry interface occurs at 11:59:46 p.m. EST as the spacecraft punches into the 
upper fringes of the atmosphere about 128 kilometers above the planet's surface
while traveling 5.4 kilometers per second (12,000 miles per hour). The 
protective heat shield is designed to withstand the 2,600-degree F temperature
expected from the friction of falling through the atmosphere. Peak heating will
happen around 12:01:28 a.m. at an altitude of 42.6 kilometers.

With about two minutes left in the descent, at 12:03:49 a.m. and 8.9 kilometers
above the ground, the craft's parachute will be deployed.

Based upon the reconstruction of data gathered during Spirit's descent and 
weather reports about the atmosphere above Meridiani Planum, engineers have
decided to have Opportunity open its parachute slightly earlier than Spirit did.

At 12:04:19 a.m. and an altitude of 5.8 kilometers, the bottom half of the 
aeroshell descent module is jettisoned, exposing the lander. The top half of the
shell, still riding the parachute, will lower the lander on a small tether.

Activation of the radar altimeter occurs at 5.4 kilometers above the surface at
12:04:24 a.m. The descent imaging camera system initiates at 12:05:07 a.m. at an
altitude of two kilometers.

The impact-cushioning airbags surrounding the lander will inflate at 12:05:31 
a.m., followed a half-second later by ignition of retro rockets on the upper 
shell to bring the descent speed to zero. The tether will be cut about 12 meters
above the surface at 12:05:34 a.m.

The first moment of touchdown -- starting a series of bounces -- is targeted for 
12:05:37 a.m. EST (0505:37 GMT).

The spacecraft is expected to bounce and roll for several minutes before coming 
to rest.

Mission Control hopes to receive communication "tones" from the rover throughout
the entry, descent and landing.

We will be posting updates on this page all evening!

*/
