// PlanetMod.inc
//Copyright © 1999 Kwan Systems
//You may use and modify this as you see fit for any non-commercial purpose
//otherwise contact me at chrisj@digiquill.com
//Chris Jeppesen - 18 Oct 1999
#version unofficial Megapov 1.22;

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

#include "PlanetConst.inc"
//#include "LocLook.inc"

#declare ASun=696000;
#declare BSun=ASun;

#declare AMercury=2440;
#declare FMercury=0;
#declare BMercury=AMercury*(1-FMercury);

#declare AVenus=6051.84;
#declare FVenus=0;
#declare BVenus=AVenus*(1-FVenus);

#declare AEarth=6378.136;
#declare BEarth=6356.752;

#declare AMoon=1737.15;
#declare FMoon=0;
#declare BMoon=AMoon*(1-FMoon);

#ifndef(AMars) #declare AMars=3389.92; #end
#ifndef(FMars) #declare FMars=1/154.409; #end
#ifndef(BMars) #declare BMars=AMars*(1-FMars); #end
PrintNumber("AMars: ",AMars)
PrintNumber("BMars: ",BMars)

#declare APhobos=13.1;
#declare BPhobos=11.1;
#declare CPhobos=9.3;

#declare ADeimos=7.8;
#declare BDeimos=6.0;
#declare CDeimos=5.1;

#declare AEros=20.591;
#declare BEros=5.711;
#declare CEros=5.332;

#declare AIda=26.8;
#declare BIda=12.0;
#declare CIda=7.6;

#declare AGaspra=9.1;
#declare BGaspra=5.2;
#declare CGaspra=4.4;

#declare AJupiter=71492;
#declare BJupiter=66854;

#declare AIo=1821.3;
#declare FIo=0;
#declare BIo=AIo*(1-FIo);

#declare AEuropa=1565;
#declare FEuropa=0;
#declare BEuropa=AEuropa*(1-FEuropa);

#declare AGanymede=2634;
#declare FGanymede=0;
#declare BGanymede=AGanymede*(1-FGanymede);

#declare ACallisto=2403;
#declare FCallisto=0;
#declare BCallisto=ACallisto*(1-FCallisto);       

#declare AAmalthea=131;
#declare BAmalthea=67;
#declare CAmalthea=73;

#declare ASaturn=60268;
#declare BSaturn=54364;       

#declare AMimas=210.3;
#declare BMimas=192.6;
#declare CMimas=197.4;

#declare AEnceladus=249.4;
#declare BEnceladus=AEnceladus;

#declare ATethys=529.9;
#declare BTethys=ATethys;

#declare ADione=559;
#declare BDione=ADione;

#declare ARhea=764;
#declare BRhea=ARhea;

#declare ATitan=2575.5;
#declare BTitan=ATitan;

#declare AHyperion=133;
#declare BHyperion=AHyperion;

#declare AIapetus=718;
#declare BIapetus=AIapetus;

#declare APrometheus= 74;
#declare BPrometheus= 34;
#declare CPrometheus= 50;

#declare APandora= 55;
#declare BPandora= 31;
#declare CPandora= 44;

#declare AJanus= 97;
#declare BJanus= 77;
#declare CJanus= 95;

#declare AEpimetheus= 69;
#declare BEpimetheus= 55;
#declare CEpimetheus= 55;

#declare AUranus=25559;
#declare BUranus=24973;

#declare AAriel=578.9; //+-0.6
#declare BAriel=AAriel;
       
#declare AUmbriel=584.7; //+-2.8
#declare BUmbriel=AUmbriel;

#declare ATitania=788.9; //+-1.8
#declare BTitania=ATitania;

#declare AOberon=761.4; //+-2.6
#declare BOberon=AOberon;

#declare AMiranda=235.8; //+-0.7
#declare BMiranda=AMiranda;

#declare ANeptune=24624;
#declare BNeptune=24342;       

#declare ATriton=1352.6; //+-2.4
#declare BTriton=ATriton;

#declare ANeried=170;
#declare ANaiad=29;
#declare AThalassa=40;
#declare ADespina=74;
#declare AGalatea=79;
#declare ALarissa=96;

#declare BNeried=170;
#declare BNaiad=29;
#declare BThalassa=40;
#declare BDespina=74;
#declare BGalatea=79;
#declare BLarissa=96;

#declare AProteus=218;
#declare BProteus=201;
#declare CProteus=208;

#declare APluto=1137;
#declare FPluto=1;
#declare BPluto=APluto*FPluto;       

#declare ACharon=593;
#declare FCharon=1;
#declare BCharon=ACharon*FCharon;       

#declare APlanet=array[1000]
#declare APlanet[Su]=ASun;
#declare APlanet[Me]=AMercury;
#declare APlanet[Ve]=AVenus;
#declare APlanet[Ea]=AEarth;
#declare APlanet[Ma]=AMars;
#declare APlanet[Ju]=AJupiter;
#declare APlanet[Sa]=ASaturn;
#declare APlanet[Ur]=AUranus;
#declare APlanet[Ne]=ANeptune;
#declare APlanet[Pl]=APluto;
#declare APlanet[Mo]=AMoon;
#declare APlanet[Ph]=APhobos;
#declare APlanet[De]=ADeimos;
#declare APlanet[Io]=AIo;
#declare APlanet[Eu]=AEuropa;
#declare APlanet[Ga]=AGanymede;
#declare APlanet[Ca]=ACallisto;
#declare APlanet[Am]=AAmalthea;
#declare APlanet[Er]=AEros;
#declare APlanet[Id]=AIda;
#declare APlanet[Gs]=AGaspra;
#declare APlanet[Mi]=AMimas;
#declare APlanet[En]=AEnceladus;
#declare APlanet[Te]=ATethys;
#declare APlanet[Di]=ADione;
#declare APlanet[Rh]=ARhea;
#declare APlanet[Ti]=ATitan;
#declare APlanet[Hy]=AHyperion;
#declare APlanet[Ia]=AIapetus;
#declare APlanet[Pm]=APrometheus;
#declare APlanet[Pa]=APandora;
#declare APlanet[Ja]=AJanus;
#declare APlanet[Ep]=AEpimetheus;
#declare APlanet[Ar]=AAriel;
#declare APlanet[Um]=AUmbriel;
#declare APlanet[Tt]=ATitania;
#declare APlanet[Ob]=AOberon;
#declare APlanet[Mr]=AMiranda;
#declare APlanet[Tr]=ATriton;
#declare APlanet[Nr]=ANeried;
#declare APlanet[Na]=ANaiad;
#declare APlanet[Th]=AThalassa;
#declare APlanet[Ds]=ADespina;
#declare APlanet[Gl]=AGalatea;
#declare APlanet[La]=ALarissa;
#declare APlanet[Pr]=AProteus;
#declare APlanet[Ch]=ACharon;

#declare BPlanet=array[1000]
#declare BPlanet[Su]=BSun;
#declare BPlanet[Me]=BMercury;
#declare BPlanet[Ve]=BVenus;
#declare BPlanet[Ea]=BEarth;
#declare BPlanet[Ma]=BMars;
#declare BPlanet[Ju]=BJupiter;
#declare BPlanet[Sa]=BSaturn;
#declare BPlanet[Ur]=BUranus;
#declare BPlanet[Ne]=BNeptune;
#declare BPlanet[Pl]=BPluto;
#declare BPlanet[Mo]=BMoon;
#declare BPlanet[Ph]=BPhobos;
#declare BPlanet[De]=BDeimos;
#declare BPlanet[Io]=BIo;
#declare BPlanet[Eu]=BEuropa;
#declare BPlanet[Ga]=BGanymede;
#declare BPlanet[Ca]=BCallisto;
#declare BPlanet[Am]=BAmalthea;
#declare BPlanet[Er]=BEros;    
#declare BPlanet[Gs]=BGaspra;
#declare BPlanet[Mi]=BMimas;
#declare BPlanet[En]=BEnceladus;
#declare BPlanet[Te]=BTethys;
#declare BPlanet[Di]=BDione;
#declare BPlanet[Rh]=BRhea;
#declare BPlanet[Ti]=BTitan;
#declare BPlanet[Hy]=BHyperion;
#declare BPlanet[Ia]=BIapetus;
#declare BPlanet[Pm]=BPrometheus;
#declare BPlanet[Pa]=BPandora;
#declare BPlanet[Ja]=BJanus;
#declare BPlanet[Ep]=BEpimetheus;
#declare BPlanet[Ar]=BAriel;
#declare BPlanet[Um]=BUmbriel;
#declare BPlanet[Tt]=BTitania;
#declare BPlanet[Ob]=BOberon;
#declare BPlanet[Mr]=BMiranda;
#declare BPlanet[Tr]=BTriton;
#declare BPlanet[Nr]=BNeried;
#declare BPlanet[Na]=BNaiad;
#declare BPlanet[Th]=BThalassa;
#declare BPlanet[Ds]=BDespina;
#declare BPlanet[Gl]=BGalatea;
#declare BPlanet[La]=BLarissa;
#declare BPlanet[Pr]=BProteus;
#declare BPlanet[Ch]=BCharon;

#declare CPlanet=array[1000]
#declare CPlanet[Su]=BSun;
#declare CPlanet[Me]=BMercury;
#declare CPlanet[Ve]=BVenus;
#declare CPlanet[Ea]=BEarth;
#declare CPlanet[Ma]=BMars;
#declare CPlanet[Ju]=BJupiter;
#declare CPlanet[Sa]=BSaturn;
#declare CPlanet[Ur]=BUranus;
#declare CPlanet[Ne]=BNeptune;
#declare CPlanet[Pl]=BPluto;
#declare CPlanet[Mo]=BMoon;
#declare CPlanet[Ph]=CPhobos;
#declare CPlanet[De]=CDeimos;
#declare CPlanet[Io]=BIo;
#declare CPlanet[Eu]=BEuropa;
#declare CPlanet[Ga]=BGanymede;
#declare CPlanet[Ca]=BCallisto;
#declare CPlanet[Ar]=BAriel;
#declare CPlanet[Pm]=CPrometheus;
#declare CPlanet[Pa]=CPandora;
#declare CPlanet[Ja]=CJanus;
#declare CPlanet[Ep]=CEpimetheus;
#declare CPlanet[Um]=BUmbriel;
#declare CPlanet[Tt]=BTitania;
#declare CPlanet[Ob]=BOberon;
#declare CPlanet[Mr]=BMiranda;
#declare CPlanet[Er]=CEros;
#declare CPlanet[Id]=CIda;
#declare CPlanet[Gs]=CGaspra;
#declare CPlanet[Am]=CAmalthea;
#declare CPlanet[Pr]=CProteus;

#ifndef(Detail)   #declare Detail=99;        #end

#ifndef(ObjDetail) 
  #declare ObjDetail=array[1000] 
  #declare I=0;
  #while(I<1000)
    #declare ObjDetail[I]=Detail;
    #declare I=I+1;
  #end
  #ifdef(SuDetail) #declare ObjDetail[Su]=SuDetail;  #end
  #ifdef(MeDetail) #declare ObjDetail[Me]=MeDetail;  #end
  #ifdef(VeDetail) #declare ObjDetail[Ve]=VeDetail;  #end
  #ifdef(EaDetail) #declare ObjDetail[Ea]=EaDetail;  #end
  #ifdef(MaDetail) #declare ObjDetail[Ma]=MaDetail;  #end
  #ifdef(JuDetail) #declare ObjDetail[Ju]=JuDetail;  #end
  #ifdef(SaDetail) #declare ObjDetail[Sa]=SaDetail;  #end
  #ifdef(UrDetail) #declare ObjDetail[Ur]=UrDetail;  #end
  #ifdef(NeDetail) #declare ObjDetail[Ne]=NeDetail;  #end
  #ifdef(PlDetail) #declare ObjDetail[Pl]=PlDetail;  #end
  #ifdef(MoDetail) #declare ObjDetail[Mo]=MoDetail;  #end
  #ifdef(PhDetail) #declare ObjDetail[Ph]=PhDetail;  #end
  #ifdef(DeDetail) #declare ObjDetail[De]=DeDetail;  #end
  #ifdef(IoDetail) #declare ObjDetail[Io]=IoDetail;  #end
  #ifdef(EuDetail) #declare ObjDetail[Eu]=EuDetail;  #end
  #ifdef(GaDetail) #declare ObjDetail[Ga]=GaDetail;  #end
  #ifdef(CaDetail) #declare ObjDetail[Ca]=CaDetail;  #end
  #ifdef(AmDetail) #declare ObjDetail[Am]=AmDetail;  #end
  #ifdef(ErDetail) #declare ObjDetail[Er]=ErDetail;  #end
  #ifdef(IdDetail) #declare ObjDetail[Id]=IdDetail;  #end
  #ifdef(GsDetail) #declare ObjDetail[Gs]=GsDetail;  #end
  #ifdef(MiDetail) #declare ObjDetail[Mi]=MiDetail;  #end
  #ifdef(EnDetail) #declare ObjDetail[En]=EnDetail;  #end
  #ifdef(TeDetail) #declare ObjDetail[Te]=TeDetail;  #end
  #ifdef(DiDetail) #declare ObjDetail[Di]=DiDetail;  #end
  #ifdef(RhDetail) #declare ObjDetail[Rh]=RhDetail;  #end
  #ifdef(TiDetail) #declare ObjDetail[Ti]=TiDetail;  #end
  #ifdef(HyDetail) #declare ObjDetail[Hy]=HyDetail;  #end
  #ifdef(IaDetail) #declare ObjDetail[Ia]=IaDetail;  #end
  #ifdef(PmDetail) #declare ObjDetail[Pm]=PmDetail;  #end
  #ifdef(PaDetail) #declare ObjDetail[Pa]=PaDetail;  #end
  #ifdef(JaDetail) #declare ObjDetail[Ja]=JaDetail;  #end
  #ifdef(EpDetail) #declare ObjDetail[Ep]=EpDetail;  #end
  #ifdef(ArDetail) #declare ObjDetail[Ar]=ArDetail;  #end
  #ifdef(UmDetail) #declare ObjDetail[Um]=UmDetail;  #end
  #ifdef(TtDetail) #declare ObjDetail[Tt]=TtDetail;  #end
  #ifdef(ObDetail) #declare ObjDetail[Ob]=ObDetail;  #end
  #ifdef(MrDetail) #declare ObjDetail[Mr]=MrDetail;  #end
  #ifdef(TrDetail) #declare ObjDetail[Tr]=TrDetail;  #end
  #ifdef(NrDetail) #declare ObjDetail[Nr]=NrDetail;  #end
  #ifdef(NaDetail) #declare ObjDetail[Na]=NaDetail;  #end
  #ifdef(ThDetail) #declare ObjDetail[Th]=ThDetail;  #end
  #ifdef(DsDetail) #declare ObjDetail[Ds]=DsDetail;  #end
  #ifdef(GlDetail) #declare ObjDetail[Gl]=GlDetail;  #end
  #ifdef(LaDetail) #declare ObjDetail[La]=LaDetail;  #end
  #ifdef(PrDetail) #declare ObjDetail[Pr]=PrDetail;  #end
  #ifdef(ChDetail) #declare ObjDetail[Ch]=ChDetail;  #end
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
#macro Spherical(ShapeNum,Rot,Color)  
  sphere {
    PrintNumber("Spherical model: ",
    <0,0,0>,APlanet[ShapeNum]
    #local MapName="concat("Data/",PlanetName[ShapeNum],"Map.png")
    #if(/*ObjDetail[ShapeNum]>=1 & */file_exists(MapName))
      #debug concat("Map ",MapName," Found, using it\n")
      pigment {
        image_map
        {
          png MapName
          map_type spherical
          interpolate 4
        }
      }
    #else
      #debug concat("Map ",MapName," Not Found, using base color\n")
      pigment {color Color}
    #end
    finish {ambient 0 #ifdef(Diffuse) diffuse Diffuse #end brilliance Brilliance}
    scale <1, BPlanet[ShapeNum]/APlanet[ShapeNum],1>
    rotate y*Rot
  }
#end

//Eros model from the NEAR-Shomeaker Laser Altimeter http://sebago.mit.edu/near/Eros129GSFC2.lonlatrad2
//The best place to find shape models of irregular bodies is to start at Phil Stooke's page http://publish.uwo.ca/~pjstooke/plancart.htm
//Phobos Image from http://publish.uwo.ca/~pjstooke/phobos2.jpg, contrast reduced and brightness enhanced
//Phobos Shape model from http://publish.uwo.ca/~pjstooke/phoshape.txt
//Deimos Shape model from http://publish.uwo.ca/~pjstooke/deishape.txt, header removed and modified for processing by ShapeModel.inc
#include "ShapeModel.inc"
#macro Irregular(ShapeNum,RotateMap,Scale,BaseColor)
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
          rotate y*RotateMap
        #else
          color rgb BaseColor
        #end
      }
      scale <APlanet[ShapeNum],BPlanet[ShapeNum],CPlanet[ShapeNum]>
    }
  #else
    object {
      #if(!file_exists(concat(PlanetName[ShapeNum],"Shape.inc")))
        ShapeModel(concat("Data/",PlanetName[ShapeNum],"Shape.txt"),concat(PlanetName[ShapeNum],"Shape.inc"),1,Scale)
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
          rotate y*RotateMap
        #else
          color rgb BaseColor
        #end
      }
    }
  #end
#end

#if(ObjDetail[Su]>=0)
#ifndef(SunLights) #declare SunLights=1; #end
#ifndef(SunBright) #declare SunBright=1; #end
#debug "Sun\n"
#declare SunModel=light_source {
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
      Spherical(Su,0,<1,1,0.8>)
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

#if(ObjDetail[Me]>=0)
  #debug "Mercury\n"
  #declare MercuryModel=Spherical(Me,180,0.5)
#end

#if(ObjDetail[Ve]>=0)
  #debug "Venus\n"
  #declare VenusModel=Spherical(Ve,180,<0,1,1>)
#end

#if(ObjDetail[Ea]>=0)
  #debug "Earth\n"
  #include "EarthMod.inc"
#end

#if(ObjDetail[Ma]>=0)
#debug "Mars\n"
#declare MarsModel=sphere {
  <0,0,0>,AMars
  scale <1, BMars/AMars,1>
  texture {
  #if(ObjDetail[Ma]>=1)
    pigment {
      image_map {    
        //Image from Constantine Thomas' Site http://www.lancs.ac.uk/postgrad/thomasc1/render/planets/mars.htm
        png "Data/MarsMap.png"
        map_type spheroid
        flatness FMars
        interpolate 4
      }
    }
    #if(ObjDetail[Ma]>=4)
      normal {
        bump_map {
          png "Data/MarsBump.png"
          map_type spheroid
          flatness FMars
          interpolate 4
          bump_size 3
        }
      }
    #end
  #else
    pigment {color Red}
  #end
  }
  rotate y*180
}
#end

#if(ObjDetail[Er]>=0)
  #debug "Eros\n"
  #declare ErosModel=Irregular(Er,0,0.001,0.7)
#end

#if(ObjDetail[Id]>=0)
  #debug "Ida\n"
  #declare IdaModel=Irregular(Id,0,1,0.7)
#end

#if(ObjDetail[Gs]>=0)
  #debug "Gaspra\n"
  #declare GaspraModel=Irregular(Gs,0,1,0.7)
#end

#if(ObjDetail[Ph]>=0)
  #debug "Phobos\n"
  #declare PhobosModel=Irregular(Ph,80,1,0.7)
#end

#if(ObjDetail[De]>=0)
  #debug "Deimos\n"
  #declare DeimosModel=Irregular(De,90,1,0.7)
#end

#declare Brilliance=1;
//#declare Diffuse=1.0;
#if(ObjDetail[Ju]>=0)
  #debug "Jupiter\n"
  #ifndef(GRSLon) #declare GRSLon=40; #end //to properly position GRS
  #declare JupiterModel=Spherical(Ju,180+GRSLon,<1,0.5,0>)
#end
#declare Brilliance=DefaultBrilliance;
#undef Diffuse

#if(ObjDetail[Io]>=0)
  #debug "Io\n"
  #declare IoModel=Spherical(Io,0,<1,0.5,0>)
#end

#if(ObjDetail[Eu]>=0)
  #debug "Europa\n"
  #declare EuropaModel=Spherical(Eu,0,<1,1,0>)
#end

#if(ObjDetail[Ga]>=0)
  #debug "Ganymede\n"
  #declare GanymedeModel=Spherical(Ga,0,<0.5,0.25,0>)
#end

#if(ObjDetail[Ca]>=0)
  #debug "Callisto\n"
  #declare CallistoModel=Spherical(Ca,0,0.5)
#end

#if(ObjDetail[Am]>=0)
  #debug "Amalthea\n"
  #declare AmaltheaModel=Irregular(Am,90,1,<0.8,0.7,0.6>)
#end

#if(ObjDetail[Sa]>=0)
  #debug "Saturn\n"
  #include "SaturnModRight.inc"
#end

//Boring gray spheres for the seven smaller satellites of Saturn, boring orange one for Titan
#declare Gray=<1,1,1>;
#if(ObjDetail[Mi]>=0) #debug "Mimas"      #declare MimasModel=      Spherical(Mi,0,Gray*0.77) #end
#if(ObjDetail[En]>=0) #debug "Enceladus"  #declare EnceladusModel=  Spherical(En,0,Gray*1.04) #end
#if(ObjDetail[Te]>=0) #debug "Tethys"     #declare TethysModel=     Spherical(Te,0,Gray*0.80) #end
#if(ObjDetail[Di]>=0) #debug "Dione"      #declare DioneModel=      Spherical(Di,0,Gray*0.55) #end
#if(ObjDetail[Rh]>=0) #debug "Rhea"       #declare RheaModel=       Spherical(Rh,0,Gray*0.65) #end
#if(ObjDetail[Ti]>=0) 
  #debug "Titan"      
  #declare TitanModel=union {	
	  Spherical(Ti,0,<1,1/3,0>) 
    #if(ObjDetail[Ti]>=2)	
//	    sphere {
//		    0,APlanet[Ti]
//			  pigment {color rgbt <1,1/3,0,0.9>}
//				no_shadow
//  		}
		#end
  }
#end
#if(ObjDetail[Hy]>=0) #debug "Hyperion"   #declare HyperionModel=   Spherical(Hy,0,Gray*0.25) #end
#if(ObjDetail[Ia]>=0) #debug "Iapetus"    #declare IapetusModel=    Spherical(Ia,0,Gray*0.50) #end
#if(ObjDetail[Pm]>=0) #debug "Prometheus" #declare PrometheusModel= Irregular(Pm,0,1,Gray*0.50) #end
#if(ObjDetail[Pa]>=0) #debug "Pandora"    #declare PandoraModel=    Irregular(Pa,0,1,Gray*0.50) #end
#if(ObjDetail[Ja]>=0) #debug "Janus"      #declare JanusModel=      Irregular(Ja,0,1,Gray*0.50) #end
#if(ObjDetail[Ep]>=0) #debug "Epimetheus" #declare EpimetheusModel= Irregular(Ep,0,1,Gray*0.50) #end



#if(ObjDetail[Ur]>=0)
  #debug "Uranus Blah Blah Blah\n"
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

#if(ObjDetail[Ar]>=0) #debug "Ariel"     #declare ArielModel=    Spherical(Ar,0,Gray*0.39) #end
#if(ObjDetail[Um]>=0) #debug "Umbriel"   #declare UmbrielModel=  Spherical(Um,0,Gray*0.21) #end
#if(ObjDetail[Tt]>=0) #debug "Titania"   #declare TitaniaModel=  Spherical(Tt,0,Gray*0.27) #end
#if(ObjDetail[Ob]>=0) #debug "Oberon"    #declare OberonModel=   Spherical(Ob,0,Gray*0.23) #end
#if(ObjDetail[Mr]>=0) #debug "Miranda"   #declare MirandaModel=  Spherical(Mr,0,Gray*0.32) #end


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

#if (ObjDetail[Tr]>=0)
  #debug "Triton\n"
  #declare TritonModel=Spherical(Tr,180,1)
#end

//Boring gray spheres for the six smaller satellites of Neptune
#if(ObjDetail[Nr]>=0) #debug PlanetName[Nr] #declare NeriedModel=  Spherical(Nr,0,Gray*0.20)#end
#if(ObjDetail[Na]>=0) #debug PlanetName[Na] #declare NaiadModel=   Spherical(Na,0,Gray*0.06)#end
#if(ObjDetail[Th]>=0) #debug PlanetName[Th] #declare ThalassaModel=Spherical(Th,0,Gray*0.06)#end
#if(ObjDetail[Ds]>=0) #debug PlanetName[Ds] #declare DespinaModel= Spherical(Ds,0,Gray*0.06)#end
#if(ObjDetail[Gl]>=0) #debug PlanetName[Gl] #declare GalateaModel= Spherical(Gl,0,Gray*0.06)#end
#if(ObjDetail[La]>=0) #debug PlanetName[La] #declare LarissaModel= Spherical(La,0,Gray*0.06)#end

#if(ObjDetail[Pr]>=0)
  #debug "Proteus\n"
  #declare ProteusModel=Irregular(Pr,90,1,<0.8,0.7,0.6>)
#end

#if (ObjDetail[Pl]>=0)
  #debug "Pluto\n"
  #declare PlutoModel=Spherical(Pl,180,1)
#end

#if (ObjDetail[Ch]>=0)
  #debug "Charon\n"
  #declare CharonModel=Spherical(Ch,180,1)
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

#declare PlanetModel=array[1000]
#declare PlanetIncluded=array[1000]
#declare I=0;
#while(I<1000)
  #declare PlanetIncluded[I]=0;
  #declare I=I+1;
#end
#ifdef(SunModel)      #declare PlanetModel[Su]=SunModel      #declare PlanetIncluded[Su]=1; #end
#ifdef(MercuryModel)  #declare PlanetModel[Me]=MercuryModel  #declare PlanetIncluded[Me]=1; #end
#ifdef(VenusModel)    #declare PlanetModel[Ve]=VenusModel    #declare PlanetIncluded[Ve]=1; #end
#ifdef(EarthModel)    #declare PlanetModel[Ea]=EarthModel    #declare PlanetIncluded[Ea]=1; #end
#ifdef(MoonModel)     #declare PlanetModel[Mo]=MoonModel     #declare PlanetIncluded[Mo]=1; #end
#ifdef(MarsModel)     #declare PlanetModel[Ma]=MarsModel     #declare PlanetIncluded[Ma]=1; #end
#ifdef(PhobosModel)   #declare PlanetModel[Ph]=PhobosModel   #declare PlanetIncluded[Ph]=1; #end
#ifdef(DeimosModel)   #declare PlanetModel[De]=DeimosModel   #declare PlanetIncluded[De]=1; #end
#ifdef(JupiterModel)  #declare PlanetModel[Ju]=JupiterModel  #declare PlanetIncluded[Ju]=1; #end
#ifdef(IoModel)       #declare PlanetModel[Io]=IoModel       #declare PlanetIncluded[Io]=1; #end
#ifdef(EuropaModel)   #declare PlanetModel[Eu]=EuropaModel   #declare PlanetIncluded[Eu]=1; #end
#ifdef(GanymedeModel) #declare PlanetModel[Ga]=GanymedeModel #declare PlanetIncluded[Ga]=1; #end
#ifdef(CallistoModel) #declare PlanetModel[Ca]=CallistoModel #declare PlanetIncluded[Ca]=1; #end
#ifdef(AmaltheaModel) #declare PlanetModel[Am]=AmaltheaModel #declare PlanetIncluded[Am]=1; #end
#ifdef(SaturnModel)   #declare PlanetModel[Sa]=SaturnModel   #declare PlanetIncluded[Sa]=1; #end
#ifdef(MimasModel)    #declare PlanetModel[Mi]=MimasModel    #declare PlanetIncluded[Mi]=1; #end
#ifdef(EnceladusModel)#declare PlanetModel[En]=EnceladusModel#declare PlanetIncluded[En]=1; #end
#ifdef(TethysModel)   #declare PlanetModel[Te]=TethysModel   #declare PlanetIncluded[Te]=1; #end
#ifdef(DioneModel)    #declare PlanetModel[Di]=DioneModel    #declare PlanetIncluded[Di]=1; #end
#ifdef(RheaModel)     #declare PlanetModel[Rh]=RheaModel     #declare PlanetIncluded[Rh]=1; #end
#ifdef(TitanModel)    #declare PlanetModel[Ti]=TitanModel    #declare PlanetIncluded[Ti]=1; #end
#ifdef(HyperionModel) #declare PlanetModel[Hy]=HyperionModel #declare PlanetIncluded[Hy]=1; #end
#ifdef(IapetusModel)  #declare PlanetModel[Ia]=IapetusModel  #declare PlanetIncluded[Ia]=1; #end
#ifdef(JanusModel)      #declare PlanetModel[Ja]=JanusModel       #declare PlanetIncluded[Ja]=1; #end
#ifdef(EpimetheusModel) #declare PlanetModel[Ep]=EpimetheusModel  #declare PlanetIncluded[Ep]=1; #end
#ifdef(PrometheusModel) #declare PlanetModel[Pm]=PrometheusModel  #declare PlanetIncluded[Pm]=1; #end
#ifdef(PandoraModel)    #declare PlanetModel[Pa]=PandoraModel     #declare PlanetIncluded[Pa]=1; #end
#ifdef(UranusModel)   #declare PlanetModel[Ur]=UranusModel   #declare PlanetIncluded[Ur]=1; #end
#ifdef(ArielModel)    #declare PlanetModel[Ar]=ArielModel    #declare PlanetIncluded[Ar]=1; #end
#ifdef(UmbrielModel)  #declare PlanetModel[Um]=UmbrielModel  #declare PlanetIncluded[Um]=1; #end
#ifdef(TitaniaModel)  #declare PlanetModel[Tt]=TitaniaModel  #declare PlanetIncluded[Tt]=1; #end
#ifdef(OberonModel)   #declare PlanetModel[Ob]=OberonModel   #declare PlanetIncluded[Ob]=1; #end
#ifdef(MirandaModel)  #declare PlanetModel[Mr]=MirandaModel  #declare PlanetIncluded[Mr]=1; #end
#ifdef(NeptuneModel)  #declare PlanetModel[Ne]=NeptuneModel  #declare PlanetIncluded[Ne]=1; #end
#ifdef(TritonModel)   #declare PlanetModel[Tr]=TritonModel   #declare PlanetIncluded[Tr]=1; #end
#ifdef(NeriedModel)   #declare PlanetModel[Nr]=NeriedModel   #declare PlanetIncluded[Nr]=1; #end
#ifdef(NaiadModel)    #declare PlanetModel[Na]=NaiadModel    #declare PlanetIncluded[Na]=1; #end
#ifdef(ThalassaModel) #declare PlanetModel[Th]=ThalassaModel #declare PlanetIncluded[Th]=1; #end
#ifdef(DespinaModel)  #declare PlanetModel[Ds]=DespinaModel  #declare PlanetIncluded[Ds]=1; #end
#ifdef(GalateaModel)  #declare PlanetModel[Gl]=GalateaModel  #declare PlanetIncluded[Gl]=1; #end
#ifdef(LarissaModel)  #declare PlanetModel[La]=LarissaModel  #declare PlanetIncluded[La]=1; #end
#ifdef(ProteusModel)  #declare PlanetModel[Pr]=ProteusModel  #declare PlanetIncluded[Pr]=1; #end
#ifdef(PlutoModel)    #declare PlanetModel[Pl]=PlutoModel    #declare PlanetIncluded[Pl]=1; #end
#ifdef(CharonModel)   #declare PlanetModel[Ch]=CharonModel   #declare PlanetIncluded[Ch]=1; #end
#ifdef(ErosModel)     #declare PlanetModel[Er]=ErosModel     #declare PlanetIncluded[Er]=1; #end
#ifdef(IdaModel)      #declare PlanetModel[Id]=IdaModel      #declare PlanetIncluded[Id]=1; #end
#ifdef(GaspraModel)   #declare PlanetModel[Gs]=GaspraModel   #declare PlanetIncluded[Gs]=1; #end

#debug "Done with PlanetMod.inc\n"
#debug "\n"







