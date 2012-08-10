/*
Earth Scene File            by Constantine Thomas               24/8/98

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
Cloudmap provided by James Hastings-Trew.
----Please credit these map sources if you use them in your images!----
Cloudmap transparency coding by Kari Kivisalo.
This POV Scene file by Constantine Thomas.
*/


// ==== Standard POV-Ray Includes ====
#include "colors.inc"	// Standard Color definitions
#include "textures.inc"	// Standard Texture definitions


camera{
  location <50000,0,25000>
  direction<0,0,4>
  look_at  <0,0,0>
  rotate <0,50,0>
}


// create a regular point light source
light_source
{
  0*x // light's position (translated below)
  color red 1.0  green 1.0  blue 1.0  // light's color
  looks_like {sphere {0*x, 696265 pigment {Yellow} finish {ambient 1}}}
  translate <150000000, 0, 0>
  rotate <0,0,0>
}


#declare Indexes = 256  // number of entries in the gif color map

#declare T = 1.5        // controls how fast the clouds become
                        // opaque towards the center (white areas)
                        // T=1 -> linear
                        // T<1 -> less transparency on the edges
                        // T>1 -> more transparency on the edges (better)


#declare Earth=
union {
//Sea Map (specular)
      sphere {0, 1
        pigment {image_map {png "TexMaps\earth-seas.png" map_type 1 interpolate 2}}
        finish {ambient 0 diffuse 1 specular 0.5 roughness 0.01}}

//Land map (not specular, overlaid above Sea Map)
//-NOTE: transmit statement below must not be changed- ; this makes blue areas (ie. the oceans) transparent!
      sphere {0, 1.000001
        pigment {image_map {png "TexMaps\earth-land.png" map_type 1 interpolate 2 transmit 58, 1.0}}
        finish {ambient 0 diffuse 1}
        normal {bump_map {png "TexMaps\EarthBump.png" map_type 1 interpolate 4 bump_size 3}}
             }

//Cloud map (above Land and Sea)
      sphere{0, 1.01
        pigment{image_map {png "TexMaps\earth-clouds.png" map_type 1 interpolate 2
        #declare n=0
        #while (n<Indexes)
        transmit n,1-pow(n/(Indexes-1),T)
        #declare n=n+1;
        #end
                }}
        finish {ambient 0 diffuse 1}
            }
        scale <6378.136,6356.752,6378.136>
      }// end Earth union


object {Earth rotate <0,-clock*360,0>}
