#include "textures.inc"
#declare DMFWood4=texture {
  DMFWood4
	finish {ambient 0.5}
}

#include "rope.inc"
#include "manequin.inc"

global_settings {ambient_light 1}

#macro CurvedCylindricalShell(Angle,InnerRad,OuterRad,Height,CurveRad)
  #local Shell=intersection {
	  cylinder {
		  <0,0,0>,<0,Height,0>,OuterRad
		}
		cylinder {
		  <0,-0.1,0>,<0,Height+0.1,0>,InnerRad
			inverse
		}
		#if(Angle>180)
		  union {
			  plane {
				  z,0
					rotate y*(Angle/2)
				}
				plane {
				  -z,0
					rotate -y*(Angle/2)
				}
			}
		#else
		  intersection {
			  plane {
				  z,0
					rotate y*(Angle/2)
				}
				plane {
				  -z,0
					rotate -y*(Angle/2)
				}
			}
		#end
	}
	#local Block=box {
	  <0,Height+0.1,0.1>,<OuterRad+0.1,Height-CurveRad,-CurveRad>
		rotate y*(180-Angle/2)
	}
	#local CurvePart = intersection {
	  cylinder {
		  <0,Height-CurveRad,-CurveRad>,<OuterRad+0.1,Height-CurveRad,-CurveRad>,CurveRad
			rotate y*(180-Angle/2)
		}
		object {Block}
		object {Shell}
	}
	union {
  	difference {
    	object {Shell}
		  object {Block}
  		object {Block scale <1,1,-1>}
	  }
		object {CurvePart}
		object {CurvePart scale <1,1,-1>}
	}
#end

#macro Car(ShaftNum,Height,Open)
  union {
		union {
  		CurvedCylindricalShell(270,1.9,2,4,0.2)
			cylinder {
	  		<0,0,0>,<0,-0.1,0>,2
			}
			texture {DMFWood4 rotate x*87 scale 1}
		}
		object {
  		CurvedCylindricalShell(50,2,2.1,4,0.2)
			texture {DMFWood4 rotate x*87 scale 1}
			rotate y*180
			rotate y*(1+2*Open)*25
		}
		object {
  		CurvedCylindricalShell(50,2,2.1,4,0.2)
			texture {DMFWood4 rotate x*87 scale 1}
			rotate y*180
			rotate -y*(1+2*Open)*25
		}
//		object {Manequin scale 3.4}
		rotate y*90
		translate <3.5,Height,ShaftNum*7+3.5>
	}
#end

#declare FloorSpacing=10;
#declare NumFloors=20;
#declare NumLights=10;
#declare RoomWidth=30;
#declare RoomLength=100;
#declare RoomHeight=NumFloors*FloorSpacing;
#declare WallThick=0.25;
#declare FloorWidth=100;

#declare Room=union {
  //Floor
  box {
	  <0,-WallThick,0>,<RoomWidth,0,RoomLength>
	}
	//Side wall
	box {
	  <RoomWidth,0,0>,<RoomWidth+WallThick,RoomHeight,RoomLength>
	}
	//Front wall
	box {
	  <0,0,RoomLength>,<RoomWidth,RoomHeight,RoomLength+WallThick>
	}
	texture {DMFWood4 rotate x*87 scale 50}
}

#declare Floors=union {
  #declare I=0;
  #while(I<=NumFloors)
	  box {
		  <-FloorWidth,I*FloorSpacing-WallThick,0>,<0,I*FloorSpacing,RoomLength>
		}
		#if(I>0)
			#declare J=0;
			#while(J<=NumLights)
		  	light_source {
			  	<0.5,I*FloorSpacing,J*RoomLength/NumLights>
					color rgb 1.5/(NumLights*NumFloors)
				}
				#declare J=J+1;
    	#end
		#end
	  #declare I=I+1;
	#end
	pigment {color rgb <0.5,0.5,0.5>}
}
camera {
  location <3.5,(RoomHeight*clock+3),3.5>
	look_at <3.5,300,3.5>
}
object {Room}	
object {Floors}
object {Car(0,max(0,RoomHeight*clock),0)}
object {Car(1,max(0,RoomHeight*(clock-0.2)),0)}
object {Car(2,max(0,RoomHeight*(clock-0.4)),0)}
object {Car(3,max(0,RoomHeight*(clock-0.6)),0)}
object {Car(4,max(0,RoomHeight*(clock-0.8)),0)}
object {Car(5,max(0,RoomHeight*(clock-1.0)),0)}

union {Rope(<10,0,5>,<10,RoomHeight,5>,MaxSeg,clock)}
union {Rope(<10,0,15>,<10,RoomHeight,15>,MaxSeg,clock)}
union {Rope(<10,0,25>,<10,RoomHeight,25>,MaxSeg,clock)}
union {Rope(<10,0,35>,<10,RoomHeight,35>,MaxSeg,clock)}
union {Rope(<10,0,45>,<10,RoomHeight,45>,MaxSeg,clock)}

union {Rope(<22,0,5>, <22,RoomHeight,5>,MaxSeg,clock)}
union {Rope(<22,0,15>,<22,RoomHeight,15>,MaxSeg,clock)}
union {Rope(<22,0,25>,<22,RoomHeight,25>,MaxSeg,clock)}
union {Rope(<22,0,35>,<22,RoomHeight,35>,MaxSeg,clock)}
union {Rope(<22,0,45>,<22,RoomHeight,45>,MaxSeg,clock)}
