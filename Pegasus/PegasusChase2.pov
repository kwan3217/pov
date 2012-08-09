#declare NaN=0;
#declare Idx=frame_number;
#declare Chunk=floor(Idx/240);
#declare Idx=mod(Idx,240);
#include concat("PegasusState",str(Chunk,0,0),".inc")

#include "Math.inc"
#include "LocLook.inc"

#declare Deploy=0;
#declare FairingDeploy=0;
//#include "Aim.inc"
#declare PegasusClock=frame_number/24.0;
#if(PegasusClock>5 & PegasusClock<73.6) #declare LitStage=1; #end
#if(PegasusClock>95.3 & PegasusClock<173.6) #declare LitStage=2; #end
#declare VFinCommand=VFinCmd[Idx];
#declare LFinCommand=LFinCmd[Idx];
#declare RFinCommand=RFinCmd[Idx];
#declare Pos=LH(Position[Idx]);
#declare CoM=LH(TotalCoM[Idx]);
#declare Quick=1;
#include "Pegasus.inc"

#macro Vector(V,R)
  #if(vlength(V)>0)
  cylinder {
	  0,V*0.75,R
	}
	cone {
	  V*0.75,R*2,V,0
	}
	#end
#end

#declare Dynamics=union {
  union {
  	union {
	    Vector(LH(LWingForce[Idx])/5000,0.1)
		  translate LH(LWingCoF)
  		pigment {color rgb <1,0,0>}
	  }
  	union {
	    Vector(LH(RWingForce[Idx])/5000,0.1)
		  translate LH(RWingCoF)
  		pigment {color rgb <1,0,0>}
	  }
  	union {
	    Vector(LH(LFinForce[Idx])/5000,0.1)
		  translate LH(LFinCoF)
  		pigment {color rgb <1,0,0>}
	  }
  	union {
	    Vector(LH(RFinForce[Idx])/5000,0.1)
		  translate LH(RFinCoF)
  		pigment {color rgb <1,0,0>}
	  }
  	union {
	    Vector(LH(VFinForce[Idx])/5000,0.1)
		  translate LH(VFinCoF)
  		pigment {color rgb <1,0,0>}
	  }
  	union {
	    Vector(LH(Stage1HAeroForce[Idx])/5000,0.1)
		  translate LH(Stage1HAeroCoF)
  		pigment {color rgb <1,0,0>}
	  }
  	union {
	    Vector(LH(Stage1RocketForce[Idx])/5000,0.1)
		  translate LH(Stage1RocketCoF)
  		pigment {color rgb <1,0.5,0>}
	  }
  	union {
	    Vector(LH(Stage2HAeroForce[Idx])/5000,0.1)
		  translate LH(Stage2HAeroCoF)
  		pigment {color rgb <1,0,0>}
	  }
  	union {
	    Vector(LH(Stage2RocketForce[Idx])/5000,0.1)
		  translate LH(Stage2RocketCoF)
  		pigment {color rgb <1,0.5,0>}
	  }
  	union {
	    Vector(LH(Stage3HAeroForce[Idx])/5000,0.1)
		  translate LH(Stage3HAeroCoF)
  		pigment {color rgb <1,0,0>}
	  }
  	union {
	    Vector(LH(Stage3RocketForce[Idx])/5000,0.1)
		  translate LH(Stage3RocketCoF)
  		pigment {color rgb <1,0.5,0>}
	  }
  	union {
	    Vector(LH(InterstageHAeroForce[Idx])/5000,0.1)
		  translate LH(InterstageHAeroCoF)
  		pigment {color rgb <1,0,0>}
	  }
  	union {
	    Vector(LH(FairingHAeroForce[Idx])/5000,0.1)
		  translate LH(FairingHAeroCoF)
  		pigment {color rgb <1,0,0>}
	  }
  	union {
	    Vector(LH(PayloadHAeroForce[Idx])/5000,0.1)
		  translate LH(PayloadHAeroCoF)
  		pigment {color rgb <1,0,0>}
	  }
		#ifdef(Stage1VAeroCoF) 
  		union {
	    	Vector(LH(Stage1VAeroForce[Idx])/5000,0.1)
		  	translate LH(Stage1VAeroCoF)
  			pigment {color rgb <1,0,0>}
	  	}
  		union {
	    	Vector(LH(Stage2VAeroForce[Idx])/5000,0.1)
		  	translate LH(Stage2VAeroCoF)
  			pigment {color rgb <1,0,0>}
	  	}
  		union {
	    	Vector(LH(Stage3VAeroForce[Idx])/5000,0.1)
		  	translate LH(Stage3VAeroCoF)
  			pigment {color rgb <1,0,0>}
	  	}
  		union {
	    	Vector(LH(InterstageVAeroForce[Idx])/5000,0.1)
		  	translate LH(InterstageVAeroCoF)
  			pigment {color rgb <1,0,0>}
	  	}
  		union {
	    	Vector(LH(FairingHAeroForce[Idx])/5000,0.1)
		  	translate LH(FairingHAeroCoF)
  			pigment {color rgb <1,0,0>}
	  	}
  		union {
	    	Vector(LH(PayloadVAeroForce[Idx])/5000,0.1)
		  	translate LH(PayloadVAeroCoF)
  			pigment {color rgb <1,0,0>}
	  	}
		#end
		cylinder {
		  CoM-z*5,CoM+z*5,0.1
			pigment {color rgb <0,1,0>}
		}
  	translate -CoM
	  LocationLookAt(
	    <0,0,0>,
  	  LH(Nose[Idx]),
	    LH(Tail[Idx]),
  	)
	}
	union {
    Vector(LH(Velocity[Idx])/15,0.1)
	  pigment {color rgb <1,1,0>}
  }
	PrintVector("CoM:  ",CoM)
	PrintVector("Nose: ",Nose[Idx])
	PrintVector("Tail: ",Tail[Idx])
}

text {
  ttf "arialn.ttf" concat("Altitude: ",str(vlength(Pos)-6378137,0,1),"m Time: ",str(PegasusClock,0,2),"s") 0 0
//  ttf "arialn.ttf" concat("Altitude: ",str(Pos.y,0,1),"m Time: ",str(PegasusClock,0,2),"s") 0 0
	pigment {color rgb <0,0,1>}
}

#declare RotPegasus=union {
  object {Pegasus}
	translate -CoM
	LocationLookAt(
	  <0,0,0>,
	  LH(Nose[Idx]),
	  LH(Tail[Idx]),
	)
}

union {
  object {RotPegasus}
	object {Dynamics}
	translate <-5,0,-5>
}
union {
	object {Dynamics}
	translate <5,0,5>
}


camera {
  location <50,50,-50>
  look_at <0,0,0>
	sky LH(Sky[Idx])
	angle 22
}

light_source {
  <20,20,0>*1000
  color rgb 1
}

background {
  color rgb <0,0.5,1>
}
