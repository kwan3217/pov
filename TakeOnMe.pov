#include "metals.inc"

#macro Solid(T)
  box {
    <-1, -1, -1>, <1, 1, 1>
    texture {T}
		scale 0.75
  }
#end

#macro Wireframe(T1,T2)
  union {
    union {
      sphere {<1, -1, 1>, 0.1}
			sphere {<1, -1, -1>, 0.1}
      sphere {<-1, -1, 1>, 0.1}
      sphere {<-1, -1, -1>, 0.1}
      sphere {<1, 1, 1>, 0.1}
      sphere {<1, 1, -1>, 0.1}
      sphere {<-1, 1, 1>, 0.1}
      sphere {<-1, 1, -1>, 0.1}
			texture {T1}
    }
    union {
      cylinder {<1, -1, 1>, <-1, -1, 1>, 0.075}
      cylinder {<1, -1, -1>, <1, -1, 1>, 0.075}
      cylinder {<-1, -1, -1>, <1, -1, -1>, 0.075}
      cylinder {<-1, -1, -1>, <-1, -1, 1>, 0.075}
      cylinder {<1, 1, 1>, <-1, 1, 1>, 0.075}
      cylinder {<1, 1, -1>, <1, 1, 1>, 0.075}
      cylinder {<-1, 1, -1>, <1, 1, -1>, 0.075}
      cylinder {<-1, 1, -1>, <-1, 1, 1>, 0.075}
      cylinder {<1, 1, 1>, <1, -1, 1>, 0.075}
      cylinder {<1, 1, -1>, <1, -1, -1>, 0.075}
      cylinder {<-1, 1, 1>, <-1, -1, 1>, 0.075}
      cylinder {<-1, 1, -1>, <-1, -1, -1>, 0.075}
			texture {T2}
    }
		scale 0.75
  }
#end

#macro MagicCube(TS,R,T) 
	object {
  	Solid(texture{pigment{color rgb TS}})
		rotate R*360
		translate T
		scale <1,1,-1>
		no_image
		no_shadow
	}
	object {
  	Wireframe(texture{pigment{ color rgb 0.1}},texture{pigment{ color rgb 0.7}})
		rotate R*360
		translate T
		no_reflection
		no_shadow
	}
#end

light_source {
   <4, 3, -5>, rgb <1, 1, 1>
}

camera {
   location <0, 2, -5>
   look_at <0, 0, 0>
	 rotate y*(45*cos(2*pi*clock)-90)
}

#declare MagicMirror=box {
  <-2,-1.5,-0.0001>,<2,1.5,0.0001>
}

MagicCube(<1,0,0>,<clock*3,clock*2,clock>,<sin(2*pi*clock)*2,0,2>)
MagicCube(<0,0,1>,<clock,clock*2,clock*3>,<sin(4*pi*clock)*1,0,-2>)

object {
  MagicMirror
	pigment {color rgb <0,0,0>}
	finish {reflection 1}
	no_shadow
}

union {
  sphere {<-2,-1.5,0>,0.1}
  sphere {<-2,1.5,0>,0.1}	
  sphere {<2,-1.5,0>,0.1}	
  sphere {<2,1.5,0>,0.1}
	cylinder {<-2,-1.5,0>,<2,-1.5,0>,0.1}
	cylinder {<2,-1.5,0>,<2,1.5,0>,0.1}
	cylinder {<2,1.5,0>,<-2,1.5,0>,0.1}
	cylinder {<-2,1.5,0>,<-2,-1.5,0>,0.1}
	pigment {color rgb <1,1,1>}
	no_shadow
}

#declare Room=box {
  <-10,-2,-10>,<10,4,10>
}

object {
  Room
	pigment {bozo 
	  color_map {
		  [0 color rgb 1]
			[0.5 color rgb 1]
			[0.5 color rgb 0]
			[1 color rgb 0]
		}
	}
	no_reflection 
}

object {
  Room
	pigment {bozo 
	  color_map {
		  [0 color rgb 1]
			[0.25 color rgb <1,1,0>]
			[0.5 color rgb <0,1,1>]
			[0.75 color rgb <0,0,1>]
			[1 color rgb 0]
		}
	}
	scale <1,1,-1>
	no_image
}
