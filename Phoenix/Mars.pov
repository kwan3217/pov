#version unofficial Megapov 1.22;

#include "host.inc"
#debug concat("\u001b];Mars.pov - ",Host," Render - frame ",str(frame_number,0,0)," of ",str(final_frame,0,0),"\a")

global_settings {
  right_handed
}

#include "KwanMath.inc"
#include "PhxLoadVec.inc"

#declare AMars=AMars+MOLAFinal-0.347-0.230;
#declare BMars=BMars+MOLAFinal-0.347-0.230;
#declare FMars=1-(BMars/AMars);
#declare Detail=-1;
#declare MaDetail=1;

#include "PlanetMod.inc"

camera {
  right x*16/9
  location Loc+Look
  look_at Look
  sky Sky
}

light_source {
  Sun
  <1,1,1>
}

object {
  MarsModel
  rotate x*90
  translate -R
}
