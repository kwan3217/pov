// PlanetMod.inc
//Copyright © 1999 Kwan Systems
//You may use and modify this as you see fit for any non-commercial purpose
//otherwise contact me at chrisj@digiquill.com
//Chris Jeppesen - 18 Oct 1999
//#version unofficial Megapov 1.22;

/*Usage*************************\
object {
  <Planet>Model
  scale YourKmToPovConversion
  translate <wherever>*YourKmToPovConversion
}
where <Planet> is replaced with the full name of the planet. Default dimensions are in km

The following arrays are also available.
They are 1000-element sparse arrays.
  X00 is the barycenter of planet system X (Sun=0, Mercury=1...Pluto=9)
  X01 is the first moon of a planet
  X02 is second....
  X99 is planet itself (Planet is considered 99th satelite of its system's barycenter)
  0XX are things like asteroids and comets, ie heliocentric orbiting bodies other than planets.
PlanetExists is 1 for a planet or moon that can have a position calculated for it, 0 for no position model,
  regardless of wheter there is a shape model declared for it.
PlanetIncluded is 1 for objects with a model declared or 0 for no model.
PlanetName is a string containing the name of the planet
PlanetModel is an array of objects, SunModel to PlutoModel
APlanet is the (major) equatorial radius in km for each planet
BPlanet is the polar radius in km for each planet
CPlanet (when included) is the minor equatorial radius
\*******************************/

/* Detail         What it means
    -1            Don't include planet model at all
     0            solid colored sphere/ellipsoid
     1            textured sphere, no rings,no clouds(Earth)
     2            1 and solid colored rings(gas giants)/Clouds(Earth)
     3            2 and textured rings(Saturn)/Shiny Oceans(Earth)
     4            3 and Bump Maps (Earth, Mars, Moon)/Shape Models(Small irregular bodies)
*/

#include "PlanetConstSpice.inc"
#include "KwanMath.inc"
#furnsh "generic.tm"

//#include "LocLook.inc"
#declare PlanetModel=array[1000];
#declare PlanetRot=array[1000];
#declare PlanetIncluded=array[1000];
#declare PlanetScale=array[1000];
#declare PlanetColor=array[1000];
#declare APlanet=array[1000];
#declare BPlanet=array[1000];
#declare CPlanet=array[1000];
#declare I=0;
#declare found=0;
#while(I<1000)
  #declare BodyI_radii=concat("BODY",str(I,0,0),"_RADII");
  #declare APlanet[I]=gdpool(BodyI_radii,0,found);
  #if(found)
    PrintNumber("I: ",I)
    PrintNumber("APlanet: ",APlanet[I])
    #declare BPlanet[I]=gdpool(BodyI_radii,2,found);
    #declare CPlanet[I]=gdpool(BodyI_radii,1,found);
    #declare PlanetIncluded[I]=1;
    #declare PlanetRot[I]=0;
    #declare PlanetScale[I]=1;
  #else
    #declare PlanetIncluded[I]=0;
  #end
  #declare I=I+1;
#end

#ifndef(Detail)   #declare Detail=99;        #end

#ifndef(ObjDetail) 
  #declare ObjDetail=array[1000] 
  #declare I=0;
  #while(I<1000)
    #declare ObjDetail[I]=Detail;
    #declare I=I+1;
  #end
#end

#declare PoleRad=0.02;
#declare GridRad=0.01;

#declare Cage=union {
  cylinder {
    <0,1,0>,<0,1.2,0>,PoleRad
    pigment {color rgb<1,0,0>}
    finish {ambient 1}
  }        
  cylinder {
    <1,0,0>,<1.2,0,0>,PoleRad
    pigment {color rgb<0,1,0>}
    finish {ambient 1}
  }        
  cylinder {
    <0,0,1>,<0,0,1.2>,PoleRad
    pigment {color rgb<0,0,1>}
    finish {ambient 1}
  }        
  difference {
    torus {
      1,GridRad
      rotate -x*90
    }      
    plane {
      x,0
    }
    pigment {color rgb<1,0,0>}
    finish {ambient 1}
  }
  difference {
    torus {
      1,GridRad
      rotate -x*90
      sturm
    }      
    plane {
      -x,0
    }
    pigment {color rgb<0.25,0.25,0.25>}
    finish {ambient 1}
  }
  #local I=15;
  #while(I<180)   
    torus {
      1,GridRad
      rotate -x*90
      rotate -y*I
      pigment {color rgb<0.25,0.25,0.25>}
      finish {ambient 1}
      sturm
    }
    torus {
      cos(radians(90-I)),GridRad
      translate y*sin(radians(90-I))
      pigment {color rgb<0.25,0.25,0.25>}
      finish {ambient 1}
      sturm
    }
    #local I=I+15;
  #end
  no_shadow
}    
      
//Sun Image derived by me from Big Bear Solar Observatory Photo, 2 Nov 2000
//Mercury Image from James Hastings-Trew's site http://apollo.spaceports.com/~jhasting/MercuryMap.jpg    
//Venus Image from Björn Jónsson's site http://www.mmedia.is/~bjj/data/venus/venus.html
//Jupiter Image from Constantine Thomas' Site http://www.lancs.ac.uk/postgrad/thomasc1/render/planets/jupiter.htm
//Io Image from Björn Jónsson's site http://www.mmedia.is/~bjj/data/Io/Io.html
//Europa Image from Björn Jónsson's site http://www.mmedia.is/~bjj/data/europa/europa.html
//Ganymede Image from Björn Jónsson's site http://www.mmedia.is/~bjj/data/ganymede/ganymede.html
//Callisto Image from Björn Jónsson's site http://www.mmedia.is/~bjj/data/callisto/index.html
//Uranus from Constantine Thomas' Site http://www.lancs.ac.uk/postgrad/thomasc1/render/planets/uranus.htm
//Uranus satellites from David Seal's site http://space.jpl.nasa.gov/
#declare DefaultBrilliance=0.75;
#declare Brilliance=DefaultBrilliance;
#macro Spheroid(ShapeNum)  
  sphere {
    <0,0,0>,1
    PrintNumber("ShapeNum: ",ShapeNum)
    scale <1, BPlanet[ShapeNum]/APlanet[ShapeNum],1>
    #local MapName=concat("Data/",PlanetName[ShapeNum],"Map.png")
    #if(/*ObjDetail[ShapeNum]>=1 & */file_exists(MapName))
      #debug concat("Map ",MapName," Found, using it\n")
      pigment {
        image_map
        {
          png MapName
          map_type spheroid
          flatness (1-BPlanet[ShapeNum]/APlanet[ShapeNum])
          interpolate 4
        }
      }
    #else
      #debug concat("Map ",MapName," Not Found, using base color\n")
      PrintVector("Color: ",PlanetColor[ShapeNum])
      pigment {color PlanetColor[ShapeNum]}
    #end
    finish {ambient 0 #ifdef(Diffuse) diffuse Diffuse #end brilliance Brilliance}
    scale <1,1,1>*APlanet[ShapeNum]
    rotate y*PlanetRot[ShapeNum]
  }
#end

//Eros model from the NEAR-Shomeaker Laser Altimeter http://sebago.mit.edu/near/Eros129GSFC2.lonlatrad2
//The best place to find shape models of irregular bodies is to start at Phil Stooke's page http://publish.uwo.ca/~pjstooke/plancart.htm
//Phobos Image from http://publish.uwo.ca/~pjstooke/phobos2.jpg, contrast reduced and brightness enhanced
//Phobos Shape model from http://publish.uwo.ca/~pjstooke/phoshape.txt
//Deimos Shape model from http://publish.uwo.ca/~pjstooke/deishape.txt, header removed and modified for processing by ShapeModel.inc
#include "ShapeModel.inc"
#macro Irregular(ShapeNum)
  #if(ObjDetail[ShapeNum]<4 | !file_exists(concat("Data/",PlanetName[ShapeNum],"Shape.txt")))
    //Plain old ellipsoid
    sphere {
      0,1
      pigment {
        #if(ObjDetail[ShapeNum]>=1 & file_exists(concat("Data/",PlanetName[ShapeNum],"Map.png")))
          image_map {
            png concat("Data/",PlanetName[ShapeNum],"Map.png")
            map_type 2
            interpolate 2
            scale 2
            translate -y*1
          }
          rotate y*PlanetRot[ShapeNum]
        #else
          color PlanetColor[ShapeNum]
        #end
      }
      scale <APlanet[ShapeNum],BPlanet[ShapeNum],CPlanet[ShapeNum]>
    }
  #else
    object {
      #if(!file_exists(concat(PlanetName[ShapeNum],"Shape.inc")))
        ShapeModel(concat("Data/",PlanetName[ShapeNum],"Shape.txt"),concat(PlanetName[ShapeNum],"Shape.inc"),1,PlanetScale[ShapeNum])
      #end
      #include concat(PlanetName[ShapeNum],"Shape.inc")
      pigment {
        #if(file_exists(concat("Data/",PlanetName[ShapeNum],"Map.png")))
          image_map {
            png concat("Data/",PlanetName[ShapeNum],"Map.png")
            map_type 2
            interpolate 2
          }
          scale 2*BPlanet[ShapeNum]
          translate -y*1
          rotate y*PlanetRot[ShapeNum]
        #else
          color PlanetColor[ShapeNum]
        #end
      }
    }
  #end
#end

#if(ObjDetail[Su]>=0)
#declare PlanetColor[Su]=<1,1,0.8>*1;
#ifndef(SunLights) #declare SunLights=1; #end
#ifndef(SunBright) #declare SunBright=1; #end
#debug "Sun\n"
#declare PlanetModel[Su]=light_source {
    #debug "Sun Light"
    <0,0,0> color SunBright
    #if(SunLights>1)
      #debug "Sun Light Area Light"
      area_light
      <APlanet[Su]*2,0,0>,<0,BPlanet[Su]*2,0>,sqrt(SunLights),sqrt(SunLights)
      adaptive 1
      circular
      orient
    #end
  looks_like {
    object {
      Spheroid(Su)
      finish {
        ambient 1 diffuse 0 specular 0 phong 0 reflection 0
      }
      no_shadow
    }
  }
}
#end

#macro SunFlare(SunPos,CamPos,Angle)
  disc {
	  0,z,1
		pigment {
  		image_map {
	  	  png "flare.png"
			}
			scale 2
			translate -x-y
		}
		scale radians(Angle)*vlength(CamPos-SunPos)
//		rotate y*90
		LocationLookAt(SunPos,CamPos,y)
  }
#end

#ifndef(GRSLon) #declare GRSLon=40; #end //to properly position GRS
#declare Sphericals=array[30] {Me,Ve,Ma,Ju,Io,Eu,Ga,Ca,Mi,En,Te,Di,Rh,Ti,Hy,Ia,Ar,Um,Tt,Ob,Mr,Tr,Nr,Na,Th,Ds,Gl,La,Pl,Ch}
#declare PlanetColor[Me]=<1,1,1>*0.5;
#declare PlanetRot[Me]=180;
#declare PlanetColor[Ve]=<0,1,1>;
#declare PlanetRot[Ve]=180;
#declare PlanetColor[Ea]=<0,0,1>;
#declare PlanetRot[Ea]=180;
#declare PlanetColor[Ma]=<1,0,0>;
#declare PlanetRot[Ma]=180;
#declare PlanetColor[Ju]=<1,0.5,0>;
#declare PlanetRot[Ju]=180+GRSLon;
#declare PlanetColor[Io]=<1,0.5,0>;
#declare PlanetColor[Eu]=<1,1,0>;
#declare PlanetColor[Ga]=<0.5,0.25,0>;
#declare PlanetColor[Ca]=<1,1,1>*0.5;
#declare PlanetColor[Mi]=<1,1,1>*0.77;
#declare PlanetColor[En]=<1,1,1>*1.04;
#declare PlanetColor[Te]=<1,1,1>*0.80;
#declare PlanetColor[Di]=<1,1,1>*0.55;
#declare PlanetColor[Rh]=<1,1,1>*0.65;
#declare PlanetColor[Ti]=<1,1/3,0>;
#declare PlanetColor[Hy]=<1,1,1>*0.25;
#declare PlanetColor[Ia]=<1,1,1>*0.50;
#declare PlanetColor[Ar]=<1,1,1>*0.39;
#declare PlanetColor[Um]=<1,1,1>*0.21;
#declare PlanetColor[Tt]=<1,1,1>*0.27;
#declare PlanetColor[Ob]=<1,1,1>*0.23;
#declare PlanetColor[Mr]=<1,1,1>*0.32;
#declare PlanetColor[Tr]=<1,1,1>*1.00;
#declare PlanetColor[Nr]=<1,1,1>*0.20;
#declare PlanetColor[Na]=<1,1,1>*0.06;
#declare PlanetColor[Th]=<1,1,1>*0.06;
#declare PlanetColor[Ds]=<1,1,1>*0.06;
#declare PlanetColor[Gl]=<1,1,1>*0.06;
#declare PlanetColor[La]=<1,1,1>*0.06;
#declare PlanetColor[Pl]=<1,1,1>*1;
#declare PlanetColor[Ch]=<1,1,1>*1;

#declare I=0;
#while(I<dimension_size(Sphericals,1))
  #if(ObjDetail[Sphericals[I]]>=0)
    #debug concat(PlanetName[Sphericals[I]],"\n")
    #declare PlanetModel[Sphericals[I]]=Spheroid(Sphericals[I])
  #end
  #declare I=I+1;
#end

//#declare Irregulars=array[11] {Er,Id,Gs,Ph,De,Am,Pm,Pa,Ja,Ep,Pr}
#declare Irregulars=array[8] {Ph,De,Am,Pm,Pa,Ja,Ep,Pr}
#declare PlanetColor[Er]=<1,1,1>*0.7;
#declare PlanetScale[Er]=0.001;
#declare PlanetColor[Id]=<1,1,1>*0.7;
#declare PlanetColor[Gs]=<1,1,1>*0.7;
#declare PlanetColor[Ph]=<1,1,1>*0.7;
#declare PlanetRot[Ph]=80;
#declare PlanetColor[Ph]=<1,1,1>*0.7;
#declare PlanetRot[Ph]=90;
#declare PlanetColor[Am]=<0.8,0.7,0.6>;
#declare PlanetRot[Am]=90;
#declare PlanetColor[Pm]=<1,1,1>*0.5;
#declare PlanetColor[Pa]=<1,1,1>*0.5;
#declare PlanetColor[Ja]=<1,1,1>*0.5;
#declare PlanetColor[Ep]=<1,1,1>*0.5;
#declare PlanetColor[Pr]=<0.8,0.7,0.6>;
#declare PlanetRot[Pr]=90;

//#declare I=0;
//#while(I<dimension_size(Irregulars,1))
//  #if(ObjDetail[Irregulars[I]]>=0)
//    #debug concat(PlanetName[Irregulars[I]],"\n")
//    #declare PlanetModel[Irregulars[I]]=Irregular(Irregulars[I])
//  #end
//  #declare I=I+1;
//#end

/*
#if(ObjDetail[Ea]>=0)
  #debug "Earth\n"
  #include "EarthModSpice.inc"
#end
*/

/*
#if(ObjDetail[Sa]>=0)
  #debug "Saturn\n"
  #include "SaturnModRight.inc"
#end

#if(ObjDetail[Ur]>=0)
  #debug "Uranus\n"
  #declare RingTex=texture {
    pigment {color rgbf<0.15,0.15,0.15,0.6>}
    finish {ambient 1.0}
  }
  #declare UranusModel=
  #if(ObjDetail[Ur]>=2)
  union {
  #end
    Spherical(Ur,0,<0,1,0>)
    #if(ObjDetail[Ur]>=2)
    union {
      //Ring data from Constantine Thomas' Site http://www.lancs.ac.uk/postgrad/thomasc1/render/planets/uranus.htm
      //Translated to POV by me
      //All rings are 100km wider than reality.
      //6 ring (innermost)
      disc {
        0,z,41910,41800
      }
      //5 ring: Inner radius 42,300 km; Outer radius 42,305 km.
      disc {
        0,z,42305,42200
      }
      //4 ring: Inner radius 42,600 km; Outer radius 42,610 km.
      disc {
        0,z,42610,42500
      }
      //a ring: Inner radius 44,800 km; Outer radius 44,807 km.
      disc {
        0,z,44807,44700
      }
      //b ring: Inner radius 45,700 km; Outer radius 45,708 km.
      disc {
        0,z,45708,45600
      }
      //eta ring: Inner radius 47,200 km; Outer radius 47,260 km.
      disc {
        0,z,47260,47100
      }
    //gamma ring: Inner radius 47,700 km; Outer radius 47,710 km.
      disc {
        0,z,47710,47600
      }
    //delta ring: Inner radius 48,300 km; Outer radius 48,310 km.
      disc {
        0,z,48310,48200
      }
    //epsilon ring (outermost): Inner radius 51,200 km; Outer radius 51,300 km
      disc {
        0,z,51300,51100
      }
      texture {RingTex}
    }
  }
  #end
#end

#if (ObjDetail[Ne]>=0)
  #debug "Neptune\n"
  #declare NeptuneModel=
  #if(ObjDetail[Ne]>=2)
  union {
  #end
    Spherical(Ne,0,<0,0,1>)
    #if(ObjDetail[Ne]>=2)
      //Ring data from Constantine Thomas' Site http://www.lancs.ac.uk/postgrad/thomasc1/render/planets/neptune.htm
      //Translated to POV by me
      //N3R ring (innermost) True size: Inner radius 41,900 km; Outer radius 41,915 km.
      //200km wider than reality
      disc {
        0,y,41915,41700
        pigment {color rgbt<0.15,0.15,0.15,0.6>}
        no_shadow
      }
      //N2R ring True Size: Inner radius 53,200 km; Outer radius 53,215 km.
      //200km wider than reality
      disc {
        0,y,53215,53000
        pigment {color rgbt<0.9,0.9,0.9,0.6>}
        no_shadow
      }
      //N4R ring True Size: Inner radius 53,215 km; Outer radius 59,000 km.
      disc {
        0,y,59000,53215
        pigment {color rgbt<0.9,0.9,0.9,0.9>}
        no_shadow
      }
      //N1R (Clumpy) ring (outermost): Inner radius 62,930 km; Outer radius 62,980 km.
      //200km wider than reality
      disc {
        0,y,62980,62730
        pigment {
          bozo color_map {
            [0 color rgbt<0.15,0.15,0.15,0.60>]
            [0.6 color rgbt<1,1,1,1>]
          }
          scale 20000
        }
        finish {ambient 0.5}
        no_shadow
      }
  }
  #end
#end

#if(ObjDetail[Mo]>=0)
  #debug "Moon\n"
  #declare MoonModel=sphere {
    <0,0,0>,AMoon
    #if(ObjDetail[Mo]>=1)
      pigment {
        image_map {
          //Image from David Seal's Site http://maps.jpl.nasa.gov/textures/ear1ccc2.jpg
          png "Data/MoonMap.png"
          map_type 1
          interpolate 4
        }
      }
      #if(ObjDetail[Mo]>=4)
        normal {
          bump_map {
            png "Data/MoonBump.png"
            map_type 1
            interpolate 4
            bump_size 3
          }
        }
      #end
    #else
      pigment {color rgb<1,1,1>}
    #end
    finish {ambient 0.01 brilliance 0.5}
    scale <1, BMoon/AMoon,1>
    rotate y*180
  }
#end
*/


#debug "Done with PlanetModSpice.inc\n"
#debug "\n"







