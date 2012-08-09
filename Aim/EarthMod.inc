#include "BlueMarbleJava.inc"
#include "textures.inc"

#declare FadeMinLat=radians(50);
#declare FadeMaxLat=radians(70);
#ifndef(UseStripe) #declare UseStripe=true; #end
#declare PMC_Clouds=texture {
  pigment {
    bozo
    turbulence 0.65
    octaves 6
    omega 0.7
    lambda 2
    color_map {
        [0.3 rgbf <1,1,1,0.5>]
        [0.7 rgbf <1,1,1,1>]
    }
    scale <6, 1, 6>
  }
  finish {ambient 0 brilliance 0}
}

#declare Stripe=texture {
  pigment {
	  planar
		color_map {
		  [0.5 color rgbf <1,1,1,1>]
			[0.5 color rgb  <1,1,1>  ]
		}
	}
	finish {ambient 0.5 diffuse 0.5 brilliance 0}
	scale 5
}

#macro EarthTex()
  #ifdef(Shell0) texture {Shell0}  #end
//  #ifdef(Shell1) texture {Shell1}  #end
//  #ifdef(Shell2) texture {Shell2}  #end
//  #ifdef(Shell3) texture {Shell3}  #end
  #ifdef(Shell4) texture {Shell4}  #end
  #ifdef(Shell5) texture {Shell5}  #end
	#if(UseStripe)
		#declare Lon=0;
		#while(Lon<180)
			texture {Stripe rotate x*90 rotate y*Lon}
	  	#declare Lon=Lon+15;
  	#end
		#declare Lat=0;
		#while(Lat<90)
			texture {Stripe scale cos(radians(Lat)) translate sin(radians(Lat))*Re*y }
			#if(Lat>0) texture {Stripe scale cos(radians(Lat)) translate -sin(radians(Lat))*Re*y } #end
	  	#declare Lat=Lat+15;
  	#end
	#end
#end

#declare CloudDeckTex=texture {
  gradient y
  triangle_wave
  turbulence 0.2
  scale <10,1,10>
  texture_map {
    [sin(FadeMinLat) pigment {color rgbf 1} ]
    [sin(FadeMaxLat) PMC_Clouds scale <30,100,30>/(Re*2)]
  }
  scale Re
  scale <1,2,1>
}

#macro CloudDeck()
  sphere {
    0,Re+Hc
    texture {CloudDeckTex}
		scale <1,(Rp+Hc)/(Re+Hc),1>
    hollow
    no_shadow
    double_illuminate
    rotate -z*deltapbarD
    rotate -y*alphapD
  }
#end

#ifndef(EarthFinish)
  #declare EarthFinish=finish { brilliance 0 ambient 0.5}
#end

#macro CalcEarthMod()
  #local LCamLoc=vrotate(CamLoc,y*alphapD);
  #local LCamLoc=vrotate(LCamLoc,z*deltapbarD);
  #local UseTest=0;

  #local Tiles0=0;
  #local Tiles1=0;
  #local Tiles2=0;
  #local Tiles3=0;
  #local Tiles4=0;
  #local Tiles5=0;
  #local Table0=array[pow(NumLatRows(0),2)*2][2];
  #local Table1=array[pow(NumLatRows(1),2)*2][2];
  #local Table2=array[pow(NumLatRows(2),2)*2][2];
  #local Table3=array[pow(NumLatRows(3),2)*2][2];
  #local Table4=array[pow(NumLatRows(4),2)*2][2];
  #local Table5=array[pow(NumLatRows(5),2)*2][2];

  MakeShellTable(0,Re,LCamLoc,Look,Angle,image_width,Table0,Tiles0)
//  MakeShellTable(1,Re,LCamLoc,Look,Angle,image_width,Table1,Tiles1)
//  MakeShellTable(2,Re,LCamLoc,Look,Angle,image_width,Table2,Tiles2)
//  MakeShellTable(3,Re,LCamLoc,Look,Angle,image_width,Table3,Tiles3)
  MakeShellTable(4,Re,LCamLoc,Look,Angle,image_width,Table4,Tiles4)
//  MakeShellTable(5,Re,LCamLoc,Look,Angle,image_width,Table5,Tiles5)

  #declare Shell0=texture {UseShellTable(0,"Map",Table0,Tiles0,0) finish { EarthFinish }}
//  #declare Shell1=texture {UseShellTable(1,"Map",Table1,Tiles1,0) finish { EarthFinish }}
//  #declare Shell2=texture {UseShellTable(2,"Map",Table2,Tiles2,0) finish { EarthFinish }}
//  #declare Shell3=texture {UseShellTable(3,"Map",Table3,Tiles3,0) finish { EarthFinish }}
  #declare Shell4=texture {UseShellTable(4,"Map",Table4,Tiles4,0)  finish { EarthFinish }}
//  #declare Shell5=texture {UseShellTable(5,"Map",Table5,Tiles5,0) finish {  EarthFinish }}

 
  #declare HardSurface=sphere {
    0,Re
		scale <1,Rp/Re,1>
    EarthTex()
    rotate -z*deltapbarD
    rotate -y*alphapD
  }

#end

#macro UseEarthMod()
  union {
    object {HardSurface}
    object {CloudDeck()}
  }
#end

#macro EarthMod()
  CalcEarthMod()
  UseEarthMod()
#end
