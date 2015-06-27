//The spacecraft are my playthings, the worlds my playground
//for I am an aerospace engineer
#version unofficial MegaPov 1.0;

#include "colors.inc"
#include "woods.inc"
#include "textures.inc"
#include "metals.inc"
#include "glass.inc"
#include "KwanMath.inc"
#include "NewHorizons.inc"
#include "Pegasus.inc"
#include "L1011.inc"
#include "Voyager.inc"
#declare Deploy=1;
#include "Aim.inc"
#declare SmallPipes=false;
#include "Saturn5.inc"
#include "ShuttleDiscovery.mesh2"
#include "Cassini.inc"

#declare Quality=2;
#declare Detail=-1;
#declare SaDetail=3;
#declare EaDetail=1;
#declare MoDetail=99;
#declare VeDetail=99;
#declare MaDetail=3;
#declare JuDetail=99;
#declare UrDetail=99;
#declare NeDetail=99;
#declare PlDetail=99;
#include "PlanetMod.inc"

#ifdef(SaturnModel)
object {
  PlanetModel[Sa]
  scale 1/ASaturn
  rotate z*22
  rotate y*10
  translate <-1.25,BSaturn/ASaturn,1.25>
}
#end

#ifdef(UranusModel)
object {
  PlanetModel[Ur]
  scale 0.5/AUranus
  rotate z*105
  rotate y*45
  translate <0.46,BUranus/AUranus,-0.26>
}
#end

#ifdef(NeptuneModel)
object {
  PlanetModel[Ne]
  scale 0.45/ANeptune
  rotate z*22
  rotate y*225
  translate <2.75,0.45*BNeptune/ANeptune,0.25>
}
#end

#ifdef(JupiterModel)
object {
  PlanetModel[Ju]
  scale 1.1/AJupiter
  rotate y*30
  rotate z*5
  translate <1.75,1.1*BJupiter/AJupiter,2.25>
}
#end

#ifdef(EarthModel)
object {
  PlanetModel[Ea]
  scale 1/AEarth/5
  rotate -y*150
  rotate -z*15
  rotate -y*12
  translate <-2,1/5,-3>
}
#end

#ifdef(MoonModel)
object {
  PlanetModel[Mo]
  scale 0.25/AMoon/5
  rotate -y*150
  rotate -z*15
  rotate -y*12
  translate <-1.75,0.25/5,-3.5>
}
#end

#ifdef(MarsModel)
object {
  PlanetModel[Ma]
  scale 1/AMars/8
  translate <-0.25,1/8,-3.0>
}
#end

#ifdef(VenusModel)
object {
  PlanetModel[Ve]
  scale 1/AVenus/5
  translate <-0.5,1/5,-1>
}
#end

camera {
  right x*1.6
  direction z*2
  location <0,2,-5>*2
  look_at <0,0,0>
//  look_at <3,0,0>
//  angle 10
}

light_source {
  <20,20,-20>
  color White*0.75
#if(Quality>0)  area_light z*10,x*10,5,5 adaptive 1 jitter orient circular #end
}

light_source {
  <-10,20,-20>
  color White*0.75
#if(Quality>0)  area_light z*10,x*10,5,5 adaptive 1 jitter #end
}

plane {
  y,0
  texture {T_Wood10 rotate -x*3 rotate y*37}
//  pigment {checker}
}
#macro Stand(Rad,Height)
  union {
    cylinder {
      <0,0,0>,<0,Height,0>,0.01
      texture {T_Gold_5A}
    }
    union {
      cylinder {
	<0,0,0>,<0,0.1,0>,Rad
      }
      cylinder {
	<0,0,0>,<0,0.15,0>,Rad-0.05
      }
      torus {
	Rad-0.05,0.05
	translate <0,0.1,0>
      }
      texture {DMFWood1 rotate y*3 translate x*1}
    }
  }
#end

#ifdef(Saturn5)
object {
  Saturn5
  scale 1/100*2.75
  translate <1.85,0,-4.0>
}
#end

#ifdef(Orbiter)
union {
  object {
    Orbiter
    scale 1/100*2.75
    rotate x*75
    translate -z*0.4
    rotate -y*120
    translate <0,0.1,0>
  }
  Stand(0.3,0.5)
  translate <-1.0,0,-3.5>
}
#end

#ifdef(L1011)
union {
  object {
    L1011
    scale 1/100*2.75
    rotate y*35
    translate <0,0.5,0>
  }
  Stand(0.3,0.5)
  translate <-1.0,0,-2>
}
#end

#ifdef(Pegasus)
union {
  object {
    Pegasus
    scale 1/100*2.75
		translate -x*0.25
    rotate y*35
		scale 1.5
    translate <0,0.3,0>
  }
  Stand(0.05,0.3)
  translate <-1.15,0,-2.15>
}
#end

#macro Book(W,H,Pages,Color,Cover)
union {
  box {
    //312x475
    <0,0,0>,<1,1,1>
    pigment {
      image_map {
        png Cover
      }
      rotate x*90
    }
    scale <W/100,0.001,H/100>
    translate y*0.0038*Pages
  }
  #declare I=0;
  union {
    #while(I<Pages)
      box {
        <0,0,0>,<W/100,0.003,H/100>
        translate y*I*0.0038
      }
      #declare I=I+1;
    #end
    pigment {color rgb Color}
  }
}
#end

object {
  Book(312,475,200,<0.9,0.9,0.9>,"ValladoBook.png")
  scale 1/2
  rotate y*30
  translate <0,0,-3>
}  

object {
  Book(296,475,100,<0.9,0.9,0.8>,"BMWBook.png")
  scale 1/2
  rotate y*15
  translate <0.05,0.38,-3.1>
}  

#ifdef(Cassini)
union {
  object {
    Cassini
    rotate -z*90
    rotate y*35
    scale 0.15
    translate <0,3/4,0>
  }
  cylinder {
    <0,0,0>,<0,3/4,0>,0.01
    texture {T_Gold_5A}
  }
  Stand(0.3,0.75)
  translate <0.8,(0.76+0.38)/2,-2.6>
}
#end

#ifdef(Aim)
union {
  object {
    Aim
		rotate z*180
    rotate y*215
    scale 1/4
    translate <0,3/4,0>
  }
  Stand(0.3,0.75)
  translate <-2,0,-1.5>
}
#end

#ifdef(NewHorizons)
union {
  object {
    NewHorizons
    scale 1/4
		rotate y*30
		rotate -z*90
		rotate y*135
    translate <0,3/4,0>
  }
  Stand(0.3,0.75)
  translate <-2.8,0,-2.0>
}
#end
#ifdef(PlutoModel)
object {
  PlanetModel[Pl]
  scale 1/APluto/20
  translate <-2.9,1/20+0.15,-2.2>
}
#end


#ifdef(Voyager)
union {
  object {
    Voyager
    scale 1000
    scale 1/10
    rotate -z*90
    rotate y*135
    translate <0,1.5,0>
  }
  Stand(0.3,1.5)
  translate <-3,0,4.0>
}
#end

global_settings {
#if(Quality>1)
  radiosity{
    pretrace_start 0.08
    pretrace_end   0.02
    count 80             // CHANGE range from 20 to 150
    nearest_count 5      // CHANGE range from 3 to 10
    error_bound 1        // CHANGE - range from 1 to 3 - should correspond with pretrace_end
                         //   1 : pretrace_end = 0.02
                         //   3 : pretrace_end = 0.08
                         //   use pretrace_start = 0.08
                         // you can go lower than 1, but then you probably will want to set
                         // pretrace_end to 0.01, which is really slow
    recursion_limit 4    // CHANGE

    low_error_factor .5  // leave this
    gray_threshold 0.0   // leave this
    minimum_reuse 0.015  // leave this
    brightness 1         // leave this

    adc_bailout 0.01/2   // CHANGE - use adc_bailout = 0.01 / brightest_ambient_object
  }
#end
}
