#include "/home/chrisj/host.inc"
#debug concat("\u001b];",Host," Render - frame ",str(frame_number,0,0)," of ",str(final_frame,0,0),"\a")

#include "LocLook.inc"
#include "KwanMath.inc"

#declare Deploy=Linterp(initial_clock,0,final_clock,1.5,clock);
PrintNumber("Deploy: ",Deploy)
#declare TimeMod=0;

#include "Aim.inc"

object {
  Aim
//	rotate z*(180-34)
		rotate -y*360*Linterp(initial_clock,0,final_clock,1,clock)
  rotate x*180
}

camera {
  location <0,2,-5>
  look_at <0,0.6,0>
	angle 30
}

global_settings {max_trace_level 20}


light_source {
  <0,2,-5>
  color rgb 1
}

background {color rgb <0,0.5,1>}
