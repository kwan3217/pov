#version unofficial MegaPov 1.11;
#declare ro=389;
#declare ri=292;
#declare rm=320;
#declare o=ro-rm;

union {
  difference {
	  cylinder {
		  <0,0,0>,<0,0,1>,ro
		}
		cylinder {
		  <-o,o,-0.001>,<-o,o,1.001>,rm
		}
	}
	cylinder {
	  <0,0,0>,<0,0,1>,ri
  }
	pigment { color rgb <0,0,1> }
  finish {ambient 1 diffuse 0}

}

text {
  ttf "arialnb.ttf" "NERGAL" 1 <-0.0,0,0>
	v_align_center
	h_align_center
	scale <1.2,1.0,1.0>
	scale 160
	translate <50,0,-1>
	pigment {
	  gradient x
		color_map {
		 [0 color rgb <1,1,1>]
		 [0.2 color rgb <1,1,1>]
		 [0.2 color rgb <1,0,0>]
		 [1.0 color rgb <1,0,0>]
		}
		scale 1000000
		translate -x*170
	}
  finish {ambient 1 diffuse 0}
}

light_source {
  <0,0,-20>*1e6 color rgb 5
}

camera {
  up y right x
  location <0,0,-2>*ro
	look_at <0,0,0>
}
