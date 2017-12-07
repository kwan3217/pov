//View from near the EMM spacecraft
#declare TimestampSize=0.1;
#include "Ranger_common.inc"

object {Ranger_Spacecraft QuatTrans(SCQ,<0,0,0>)}
object {SkyGrid}
object {ViewFrame}

camera {
  up y*1
  right -x*image_width/image_height
//  angle 25.39
  sky z
  location -vnormalize(PlanetPos)*20
  look_at PlanetPos
}


