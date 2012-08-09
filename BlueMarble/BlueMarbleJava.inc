/*******************************************************************************\
BlueMarbleJava.inc -- Use the Blue Marble dataset to create a model of the earth

#macro CalcEarthMod(LCamLoc,Look,Angle)
Calculate which tiles are needed to properly portray the Earth given these
camera parameters. Output is an object variable called HardSurface (This may 
be extended someday to the cloud deck, ice deck, etc) which is a perfect spheroid
with the correct texture.

#macro UseEarthMod()
Put the calculated earth model into the scene, unrotated and at the origin
with the prime meridian towards +x, the north pole towards +y, and 90degE towards
+z.

#macro EarthMod(LCamLoc,Look,Angle) 
Calls CalcEarthMod and UseEarthMod sequentially

Hidden parameters: Change these before calling the CalcEarthMod macro.
AEarth, BEarth: Size of the spheroid used. Default values are for WGS-84 
ellipsoid in km.
UseShell[n], n=0-5: Consider using shell n. #undef these to not consider the 
given shell.

\*******************************************************************************/

#version unofficial MegaPov 1.11;

#ifndef(AEarth)
  #declare AEarth=6378.137;
#end
#ifndef(BEarth)
	#declare BEarth=6356.752;
#end
#ifndef(UseStripe)
  #declare UseStripe=0;
#end
#ifndef(StripeWidth)
  #declare StripeWidth=0.001;
#end
#ifndef(BlueMarbleDate)
  #declare BlueMarbleDate="200404"
#end

#declare Stripe=texture {
  pigment {
	  planar
		color_map {
		  [0.5 color rgbf <1,1,1,1>]
			[0.5 color rgb  <1,1,1>  ]
		}
	}
	finish {ambient 0.5 diffuse 0.5 brilliance 0}
	scale StripeWidth
}



#declare UseShell0=1;
#declare UseShell1=1;
#declare UseShell2=1;
#declare UseShell3=1;
#declare UseShell4=1;
#declare UseShell5=1;
#declare UseShell6=1;

#ifndef(UseTest)
  #declare UseTest=0;
#end

#macro EarthTex()
  #ifdef(Shell0) texture {Shell0}  #end
  #ifdef(Shell1) texture {Shell1}  #end
  #ifdef(Shell2) texture {Shell2}  #end
  #ifdef(Shell3) texture {Shell3}  #end
  #ifdef(Shell4) texture {Shell4}  #end
  #ifdef(Shell5) texture {Shell5}  #end
  #ifdef(Shell6) texture {Shell6}  #end
 	#if(UseStripe)
 		#declare Lon=0;
	  #while(Lon<180)
  		texture {Stripe rotate x*90 rotate y*Lon}
    	#declare Lon=Lon+15;
   	#end
 		#declare Lat=0;
  	#while(Lat<90)
	  	texture {Stripe scale cos(radians(Lat)) translate sin(radians(Lat))*y }
      #if(Lat>0) texture {Stripe scale cos(radians(Lat)) translate -sin(radians(Lat))*y } #end
    	#declare Lat=Lat+15;
   	#end
  #end
#end

#macro CalcEarthMod(LCamLoc,Look,Angle)
  #declare CmdString=concat(str(LCamLoc.x,0,12)," ");
  #declare CmdString=concat(CmdString,str(LCamLoc.y,0,12)," ");
  #declare CmdString=concat(CmdString,str(LCamLoc.z,0,12)," ");
  #declare CmdString=concat(CmdString,str(Look.x,0,12)," ");
  #declare CmdString=concat(CmdString,str(Look.y,0,12)," ");
  #declare CmdString=concat(CmdString,str(Look.z,0,12)," ");
  #declare CmdString=concat(CmdString,str(Angle,0,12)," ");
  #declare CmdString=concat(CmdString,str(image_width,0,1)," ");
  #declare CmdString=concat(CmdString,str(UseTest,0,0)," ");
  #declare CmdString=concat(CmdString,str(UseShell0,0,0)," ");
  #declare CmdString=concat(CmdString,str(UseShell1,0,0)," ");
  #declare CmdString=concat(CmdString,str(UseShell2,0,0)," ");
  #declare CmdString=concat(CmdString,str(UseShell3,0,0)," ");
  #declare CmdString=concat(CmdString,str(UseShell4,0,0)," ");
  #declare CmdString=concat(CmdString,str(UseShell5,0,0)," ");
  #declare CmdString=concat(CmdString,str(UseShell6,0,0)," ");
  #declare CmdString=concat(CmdString,str(AEarth,0,12)," ");
  #declare CmdString=concat(CmdString,str(BEarth,0,12)," ");
  #declare CmdString=concat(CmdString,BlueMarbleDate," ");
	#debug CmdString
	#declare CmdString=concat("java -cp /home/chrisj/workspace/Java/build/classes/ org.kwansystems.pov.BlueMarble ",CmdString);
	#debug CmdString
  #system CmdString

  #declare HardSurface=union {
	  sphere {
      0,1
      scale <1,BEarth/AEarth,1>
		}
    EarthTex()
    scale AEarth
  }

#end

#macro UseEarthMod()
  union {
    object {HardSurface}
  }
#end

#macro EarthMod(CamLoc,Look,Angle)
  CalcEarthMod(CamLoc,Look,Angle)
  UseEarthMod()
#end
