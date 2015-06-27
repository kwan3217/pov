#include "KwanMath.inc"

#local FinHeight=1.542;
#local FinLength=1.608;
#local FinWidth=0.1;
#local FinAft=0.712;
#local FinOut=0.64;

#local X0=0;
#local X1=0.065*FinLength;   //Back of tall part of fin
#local X2=0.117*FinLength;  //Front of notch at bottom
#local X3=0.239*FinLength;  //Widest point of fin on top
#local X4=0.520*FinLength;   //Widest point of fin on bottom
#local X5=0.383*FinLength;   //Front of fin at top
#local X6=1.0*FinLength;   //Front of fin at bottom

#local Y0=0;
#local Y1=0.071*FinHeight;  //Top of notch at back
#local Y2=0.391*FinHeight;  //Top of back cylinder
#local Y3=1*FinHeight;    //Top of fin

#local Z0=0;
#local Z1=0.3*FinWidth;   //Widest point of fin at top
#local Z2=1*FinWidth;     //Widest point of fin at bottom

#declare Pegasus1Fin=union {
  mesh {
  	//Left Side
  	//Back part of fin
  	triangle {
	  	<X2,Y0,Z0>,<X1,Y3,Z0>,<X3,Y3,Z1>
		}
		triangle {
	  	<X2,Y0,Z0>,<X4,Y0,Z2>,<X3,Y3,Z1>
		}
		//Front part of fin
  	triangle {
	  	<X4,Y0,Z2>,<X3,Y3,Z1>,<X5,Y3,Z0>
		}
		triangle {
	  	<X4,Y0,Z2>,<X6,Y0,Z0>,<X5,Y3,Z0>
		}
  	//Right Side
  	//Back part of fin
  	triangle {
	  	<X2,Y0,-Z0>,<X1,Y3,-Z0>,<X3,Y3,-Z1>
		}
		triangle {
	  	<X2,Y0,-Z0>,<X4,Y0,-Z2>,<X3,Y3,-Z1>
		}
		//Front part of fin
  	triangle {
	  	<X4,Y0,-Z2>,<X3,Y3,-Z1>,<X5,Y3,-Z0>
		}
		triangle {
	  	<X4,Y0,-Z2>,<X6,Y0,-Z0>,<X5,Y3,-Z0>
		}
    //Top part
		triangle {
		  <X1,Y3,Z0>,<X3,Y3,Z1>,<X3,Y3,-Z1>
	  }
		triangle {
		  <X5,Y3,Z0>,<X3,Y3,Z1>,<X3,Y3,-Z1>
	  }
  }
	difference {
  	union {
	    box {
		    <X0,Y0,-Z2>,<X4,Y2-Z2,Z2>
  		}
	  	cylinder {
		    <X0,Y2-Z2,0>,<X4,Y2-Z2,0>,Linterp(Y0,Z2,Y3,Z1,Y2-Z2)
  		}
	  }
		box {
		  <X0,Y0-0.1,-Z2-0.1>,<X2,Y1,Z2+0.1>
			matrix <
			  1,0,0,
				-X2/Y1,1,0,
				0,0,1
				0,0,0
			>
		}
		box {
		  <X0,Y0-0.1,-Z2-0.1>,<X2,Y3+0.1,Z2+0.1>
			matrix <
			  1,0,0,
				-(X4-X3)/Y3,1,0,
				0,0,1
				X4,0,0
			>
		}
		box {
		  <X0-0.1,Y0,-Z2-0.1>,<X4,Y3,-Z2>
			matrix <
			  1,0,0,
				0,1,(Z2-Z1)/Y3,
				0,0,1,
				0,0,0
			>
		}
		box {
		  <X0-0.1,Y0,Z2+0.1>,<X4,Y3,Z2>
			matrix <
			  1,0,0,
				0,1,-(Z2-Z1)/Y3,
				0,0,1,
				0,0,0
			>
		}
	}
	pigment {color rgb 1.0}
	finish {ambient 0.5}
	translate <FinAft,FinOut,0>
	scale 100
}

/*
object {Fin}

camera {
  location <3,2,-5>
	look_at <X6/2,Y3/2,0>
	angle 15
}

light_source {
  <20,20,-3>
	color rgb 1
}
*/
