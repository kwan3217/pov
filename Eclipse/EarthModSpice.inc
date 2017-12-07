/*
Earth Scene File            by Constantine Thomas               24/8/98
Slightly modified by Chris Jeppesen 20 May 1999
Heavily modified by Chris Jeppesen 18 Oct 1999
Heavily modified some more by Chris Jeppesen 16 Jul 2003

This Scene file shows you how to put the three earth maps (land, sea, clouds) together
to make a very realistic-looking Earth. It works like this:
The idea is that you layer the three maps to get the right effect.
    The sea map goes at the bottom of the pile, and has a specular finish.
    The land map above this, with the (blue) ocean areas rendered completely transparent
    by a transmit statement. The land areas will therefore 'cover over' any specular highlight
    on the sea map below it, which gives the appearance that the sea only is reflecting the
    sunlight and the continents aren't (which is what we want).

    [If you're looking at the maps, you may be wondering why the land areas on the Sea Map
    (and the ocean areas on the Land map) are coloured in the same shade of blue. Originally,
    these 'blank' areas were black, but when I rendered them on top of eachother the outlines
    of the continents had a black rim around them. By colouring the 'non-active' areas of each
    map blue, this rim is made invisible and the result looks much better.]

    The cloud map then goes above both of these maps. Make sure that the central band of the
    cloudmap (ie. the bits where there are no clouds) is black, otherwise it won't work properly!

These maps are available from http://www.lancs.ac.uk/postgrad/thomasc1/render/planets/earth.htm
in PNG format and are contained in the 'earthpng.zip' file there.

Earth land map and sea map derived from original Earth map by Constantine Thomas.
Cloudmap and ocean map provided by James Hastings-Trew.
----Please credit these map sources if you use them in your images!----
Cloudmap transparency coding by Kari Kivisalo.
This POV Scene file by Constantine Thomas.
*/

/*Changes by Chris Jeppesen:
  * Got a better geographically accurate earth map.
  * Modified model to use a material map. Now instead of two full color maps, one for the ocean
    and one for land, there is one full color map for both and one black and white map showing
    what is land(black) and what is white(water).
  * Added bump map.
  * Converted all maps to PNG format.
  * Got a night bitmap. Integrating it will be the fun part. Using negative diffuse and positive ambient sounds like a plan
  * Changed over to use the BlueMarble maps
  * Uses the flattening patch
  * Almost none of Constantine's code remains (Mostly only cloud transparency code), so I will claim it as my own.
*/

//#version unofficial MegaPov 1.0;

#declare Indexes = 256;  // number of entries in the gif color map

#declare T = 1.5;        // controls how fast the clouds become
                        // opaque towards the center (white areas)
                        // T=1 -> linear
                        // T<1 -> less transparency on the edges
                        // T>1 -> more transparency on the edges (better)

/* Detail         What it means
    -1            Don't include planet model at all
     0            solid colored sphere
     1            textured sphere, no clouds
     2            1 and Clouds
     3            2 and Shiny Oceans(Earth)
     4            3 and Bump Maps
*/
#if(ObjDetail[Ea]>=1)
#declare EarthPigment=pigment{
  image_map {
    png "EarthMap/EarthMap0.png"
    map_type spheroid
    flatness (1-BEarth/AEarth)
    interpolate 2
  }
  scale AEarth
}
#end

#declare LandTex=          texture {   //Land
  pigment {EarthPigment}
  finish {ambient 0 brilliance 0.5}
  #if(ObjDetail[Ea]>=4)
    normal {
      bump_map {
        png "EarthBump/EarthBump0.png"
        map_type spheroid
        flatness 1-(BEarth/AEarth)
        interpolate 4
        bump_size 3
      }
      scale AEarth
    }
  #end
}

#declare OceanTex=texture {  //Ocean
  pigment {EarthPigment}
  finish {
    ambient 0
    diffuse 1
    specular 0.5
    roughness 0.01
  }
}

#declare EarthModel=union {
  //Surface
  sphere {
    0,1
    scale <AEarth,BEarth,AEarth>
    #if(ObjDetail[Ea]>=3)
      texture {
        material_map {
          png "EarthLand/EarthLand0.png"  
          map_type spheroid
	  flatness 1-(BEarth/AEarth)
          interpolate 0
	  texture {OceanTex} // 0     WATER
          texture {LandTex}  // 1     EVERGREEN NEEDLELEAF FOREST                
	  texture {LandTex}  // 2     EVERGREEN BROADLEAF FOREST                 
	  texture {LandTex}  // 3     DECIDUOUS NEEDLELEAF FOREST                
	  texture {LandTex}  // 4     DECIDUOUS BROADLEAF FOREST                 
	  texture {LandTex}  // 5     MIXED FOREST
	  texture {LandTex}  // 6     WOODLAND
	  texture {LandTex}  // 7     WOODED GRASSLAND                              
	  texture {LandTex}  // 8     CLOSED SHRUBLAND                          
	  texture {LandTex}  // 9     OPEN SHRUBLAND                           
	  texture {LandTex}  //10     GRASSLAND                                
	  texture {LandTex}  //11     CROPLAND                        
	  texture {LandTex}  //12     BARE GROUND
	  texture {LandTex}  //13     URBAN AND BUILT-UP                     	  
        }
      }
    #else
      #if(ObjDetail[Ea]>=1)
        pigment {EarthPigment}
      #else
        pigment {color <0,0,1>}
      #end
    #end
  }
  //Cloud map (above Surface)
  #if(ObjDetail[Ea]>=2)
    sphere{
      0, 1.005
      scale <AEarth,BEarth,AEarth>
      pigment{
        image_map {
          png "EarthCloud/EarthCloud0.png"
          map_type spheroid
          flatness (1-BEarth/AEarth)
          interpolate 2
          #declare n=0;
          #while (n<Indexes)
            transmit n,1-pow(n/(Indexes-1),T)
            #declare n=n+1;
          #end
        }
	scale AEarth
      }
      finish {ambient 0 diffuse 1 brilliance 0.5}
    }
  #end
  //Night Map (Very Slightly above Surface)
  #local T=1;
  #if(ObjDetail[Ea]>=2)
    sphere{
      0, 1.00001
      scale <AEarth,BEarth,AEarth>
      pigment{
        image_map {
          png "EarthLights/EarthLights0.png"
          map_type spheroid
          flatness (1-BEarth/AEarth)
          #declare n=0;
          /*
          #while (n<Indexes)
            transmit n,1-pow(n/(Indexes-1),T)
            #declare n=n+1;
          #end
          */
          transmit all 0.9
        }
	scale AEarth
      }
      finish {ambient 5 diffuse -5 brilliance 0.5}//Turn on the lights slightly before twilight
      no_shadow
    }
  #end
  rotate y*180
}


