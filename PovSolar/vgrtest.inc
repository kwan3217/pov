#include "colors.inc"
#include "textures.inc"
#include "shapes.inc"

#declare Voyager =object {Paraboloid_Y
           translate <0,0.95,0>                            // moves paraboloid up so it can be clipped
           clipped_by {plane {y , 1.86}}
           pigment {White}
           finish {Dull}
           scale <3,1.5,3>

//SCALE WHOLE VOYAGER OBJECT DOWN TO 1:1 SCALING.
scale 0.622            //This scales Voyager down so that 1 POV unit = 1 metre.
                       // Unscaled, the dish is 2.895 units in radius. The actual Voyager dish is
                       // 1.8 metres in radius (6 ft), so the scale factor to scale it to 1.8 units is 0.622.

scale 0.001            //This scales Voyager down further (cumulative) so that 1 POV unit = 1 kilometre,
                       // so that it is scaled properly in planetary fly-by scenes with the same scale.
                       // At this scale, the dish is 0.0018 units (km) across.

}// end Voyager union
