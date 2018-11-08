//stars.inc

//fills the sky with stars, based on data from the Yale Bright Star Catalog, J2000.0 equator and epoch
//The north pole is in the direction of <0,0,1>
//The vernal equinox (0h00m RA) is in the direction <1,0,0>
//Orion is at about 6h RA and therefore in the direction of <0,1,0>

#include "KwanMath.inc"
#ifndef(CelestialSphereRad)
  #declare CelestialSphereRad=1e6;
#end

#ifndef(StarRatio)
  #declare StarRatio=720;
#end

#ifndef(StarRad)
  #declare StarRad=CelestialSphereRad/StarRatio;
#end

#ifndef(LimitMag)
  #declare LimitMag=6;
#end

#ifndef(BrightMax)
  #declare BrightMax=1;
#end

#ifndef(ColorSat)
  #declare ColorSat=0.5;
#end

#ifndef(Gamma)
  #declare Gamma=0.4;
#end

#local ParseStar=true;
#if(file_exists("StarsRightCache.inc"))
  #include "StarsRightCache.inc"
  #if(CelestialSphereRad=CacheCelestialSphereRad)
    #if(LimitMag=CacheLimitMag)
      #if(BrightMax=CacheBrightMax)
        #if(ColorSat=CacheColorSat)
          #if(Gamma=CacheGamma)
            #local ParseStar=false;
            #debug "Using Cache\n"
          #else
            #debug "Not using cache: Gamma\n"
          #end
        #else
          #debug "Not using cache: ColorSat\n"
        #end
      #else
        #debug "Not using cache: BrightMax\n"
      #end
    #else
      #debug "Not using cache: LimitMag\n"
    #end
  #else
   #debug "Not using cache: CelSphRad\n"
  #end
#else
  #debug "Not using cache: No Cache\n"
#end

#if(ParseStar)
#ifndef(BrightStarCatalog)
#include "Catalog.inc"
#end

#fopen ouf "StarsRightCache.inc" write
#write(ouf, "#declare CacheCelestialSphereRad=",CelestialSphereRad,";\n")
#write(ouf, "#declare CacheLimitMag=          ",LimitMag,";\n")
#write(ouf, "#declare CacheBrightMax=         ",BrightMax,";\n")
#write(ouf, "#declare CacheColorSat=          ",ColorSat,";\n")
#write(ouf, "#declare CacheGamma=             ",Gamma,";\n")
#declare Colors=array[8] {
  <0.5,0.5,1>,     //O,W
  <0.75,0.75,1>,   //B
  <1,1,1>,         //A
  <1,1,0.5>,       //F
  <1,1,0>,         //G
  <1,0.5,0>,       //K,R,S
  <1,0,0>          //M,N
  <0.5,0,0>        //(M10)
}

#macro GetRA(N)
  //returns RA in degrees
  #local S=BrightStarCatalog[N]
  #local Hours=val(substr(S,76,2));
  #local Minutes=val(substr(S,78,2));
  #local Seconds=val(substr(S,80,4));
  ((Hours+Minutes/60+Seconds/3600)*15)
#end

#macro GetDec(N)
  //returns Dec in degrees
  #local S=BrightStarCatalog[N]
  #local Sign   =    substr(S,84,1)
  #local Degrees=val(substr(S,85,2));
  #local Minutes=val(substr(S,87,2));
  #local Seconds=val(substr(S,89,2));
  ((Degrees+Minutes/60+Seconds/3600)*(strcmp(Sign,"-")=0?-1:1))
#end

#macro GetMag(N)
  //returns Magnitude, lower number is brighter
  #local S=BrightStarCatalog[N]
  //#warning concat("MagStr: ",substr(S,103,5))
  (val(substr(S,103,5)))
#end

#macro GetName(N)
  #local S=BrightStarCatalog[N]
  //#warning concat("MagStr: ",substr(S,103,5))
  concat(substr(S,5,10)," HR",substr(S,1,4))
#end

#local MaxMag=GetMag(0);

#macro GetSpectralLetter(N)
  #local S=BrightStarCatalog[N]
  substr(S,130,1)
#end

#macro GetSpectralSubtype(N)
  #local S=BrightStarCatalog[N]
  val(substr(S,131,1))
#end

#macro GetSpectralType(N)
  //Returns number corresponding to spectral type, O=zero, M=6
  #local SpectralLetter=asc(GetSpectralLetter(N));
  //#warning chr(SpectralLetter)
  #switch(SpectralLetter)
    #case (asc("O"))
    #case (asc("W"))
      (0)
      #break
    #case (asc("B"))
      (1)
      #break
    #case (asc("A"))
      (2)
      #break
    #case (asc("F"))
      (3)
      #break
    #case (asc("G"))
      (4)
      #break
    #case (asc("K"))
    #case (asc("R"))
    #case (asc("S"))
      (5)
      #break
    #case (asc("M"))
    #case (asc("N"))
    #case (asc("C"))
    #else
      (6)
      #break
  #end
#end

#macro GetColor(N)
  //returns a 3vector for color
  #local S=BrightStarCatalog[N]
  #local Mag=GetMag(N);
  //PrintNumber("Mag: ",Mag)
  #if(Mag>LimitMag)
    #local result=<0,0,0>;
  #else
    #local Bright=Linterp(MaxMag,BrightMax,LimitMag,0,Mag);
    #local Type=(GetSpectralType(N));
    #local Subtype=GetSpectralSubtype(N);
    //PrintNumber("Subtype: ",Subtype)
    //PrintVector("0 color: ",Colors[Type])
    //PrintVector("10 color: ",Colors[Type+1])
    #local Color=Linterp(0,Colors[Type],10,Colors[Type+1],Subtype)*ColorSat;
    #local Color=((<1,1,1>*(1-ColorSat)+Color)*Bright);
    #local result=<pow(Color.x,Gamma),pow(Color.y,Gamma),pow(Color.z,Gamma)>;
  #end
  (result)
#end

#macro Star(N)
  #local Dec=radians(GetDec(N));
  #local RA=radians(GetRA(N));
  #local V=CelestialSphereRad*<cos(Dec)*cos(RA),cos(Dec)*sin(RA),sin(Dec)>;
  #write(ouf,"  sphere{<",str(V.x,0,16),",",str(V.y,0,16),",",str(V.z,0,16),">,",StarRad," no_shadow finish {StarFin} pigment {color rgb ",(GetColor(N)),"}}")
  #write(ouf," //",GetName(N),", VMag=",GetMag(N)," Type=",GetSpectralLetter(N),GetSpectralSubtype(N),"\n")
  sphere {
    V,StarRad
    no_shadow
    texture {
      finish {ambient 1 diffuse 0 specular 0}
      pigment {color rgb (GetColor(N))}
    }
  }
#end

#write(ouf "#local StarFin=finish{ambient 1 diffuse 0 specular 0}\n")
#local nStars=0;
#while((nStars<dimension_size(BrightStarCatalog,1))&((GetMag(nStars))<=LimitMag))
  #local nStars=nStars+1;
#end

#write(ouf "#declare StarPos=array[",nStars,"]\n")
#write(ouf "#declare StarColor=array[",nStars,"]\n")
#write(ouf "#declare StarName=array[",nStars,"]\n")
#local I=0;
#while(I<nStars)
  #local Dec=radians(GetDec(I));
  #local RA=radians(GetRA(I));
  #local V=CelestialSphereRad*<cos(Dec)*cos(RA),cos(Dec)*sin(RA),sin(Dec)>;
  #local C=GetColor(I);
  #write(ouf,"#declare StarPos[",I,"]=<",str(V.x,0,16),",",str(V.y,0,16),",",str(V.z,0,16),">;\n")
  #write(ouf,"#declare StarColor[",I,"]=",C,";\n")
  #write(ouf,"#declare StarName[",I,"]=\"",GetName(I),"\";// VMag=",GetMag(I)," Type=",GetSpectralLetter(I),GetSpectralSubtype(I),"\n")
  #local I=I+1;
#end
#fclose ouf

#end

#include "StarsRightCache.inc"
#declare Stars=union {
#local I=0;
#while(I<dimension_size(StarPos,1))
  sphere {
    StarPos[I],StarRad
    no_shadow
    texture {
      finish {ambient 1 diffuse 0 specular 0}
      pigment {color rgb StarColor[I]}
    }
  }
/*
  text {
     ttf "arial.ttf"
     StarName[I] 0 0
     rotate x*90
     rotate -z*90
     scale 200
     translate StarPos[I]/100
     no_shadow
     texture {
       finish {ambient 1 diffuse 0 specular 0}
       pigment {color rgb (StarColor[I])}
     }
  }
*/
  #local I=I+1;
#end
}

/*	
Byte-by-byte Description of file: catalog.dat
Stars are fields we care about
--------------------------------------------------------------------------------
   Bytes Format  Units     Label      Explanations
--------------------------------------------------------------------------------
   1-  4  I4     ---       HR         [1/9110]+ Harvard Revised Number
                                      = Bright Star Number
   5- 14  A10    ---       Name       Name, generally Bayer and/or Flamsteed name
  15- 25  A11    ---       DM         Durchmusterung Identification (zone in
                                      bytes 17-19)
  26- 31  I6     ---       HD         [1/225300]? Henry Draper Catalog Number
  32- 37  I6     ---       SAO        [1/258997]? SAO Catalog Number
  38- 41  I4     ---       FK5        ? FK5 star Number
      42  A1     ---       IRflag     [I] I if infrared source
      43  A1     ---       r_IRflag  *[ ':] Coded reference for infrared source
      44  A1     ---       Multiple  *[AWDIRS] Double or multiple-star code
  45- 49  A5     ---       ADS        Aitken's Double Star Catalog (ADS) designation
  50- 51  A2     ---       ADScomp    ADS number components
  52- 60  A9     ---       VarID      Variable star identification
  61- 62  I2     h         RAh1900    ?Hours RA, equinox B1900, epoch 1900.0 (1)
  63- 64  I2     min       RAm1900    ?Minutes RA, equinox B1900, epoch 1900.0 (1)
  65- 68  F4.1   s         RAs1900    ?Seconds RA, equinox B1900, epoch 1900.0 (1)
      69  A1     ---       DE-1900    ?Sign Dec, equinox B1900, epoch 1900.0 (1)
  70- 71  I2     deg       DEd1900    ?Degrees Dec, equinox B1900, epoch 1900.0 (1)
  72- 73  I2     arcmin    DEm1900    ?Minutes Dec, equinox B1900, epoch 1900.0 (1)
  74- 75  I2     arcsec    DEs1900    ?Seconds Dec, equinox B1900, epoch 1900.0 (1)
* 76- 77  I2     h         RAh        ?Hours RA, equinox J2000, epoch 2000.0 (1)
* 78- 79  I2     min       RAm        ?Minutes RA, equinox J2000, epoch 2000.0 (1)
* 80- 83  F4.1   s         RAs        ?Seconds RA, equinox J2000, epoch 2000.0 (1)
*     84  A1     ---       DE-        ?Sign Dec, equinox J2000, epoch 2000.0 (1)
* 85- 86  I2     deg       DEd        ?Degrees Dec, equinox J2000, epoch 2000.0 (1)
* 87- 88  I2     arcmin    DEm        ?Minutes Dec, equinox J2000, epoch 2000.0 (1)
* 89- 90  I2     arcsec    DEs        ?Seconds Dec, equinox J2000, epoch 2000.0 (1)
  91- 96  F6.2   deg       GLON       ?Galactic longitude (1)
  97-102  F6.2   deg       GLAT       ?Galactic latitude (1)
*103-107  F5.2   mag       Vmag       ?Visual magnitude (1)
     108  A1     ---       n_Vmag    *[ HR] Visual magnitude code
     109  A1     ---       u_Vmag     [ :?] Uncertainty flag on V
 110-114  F5.2   mag       B-V        ? B-V color in the UBV system
     115  A1     ---       u_B-V      [ :?] Uncertainty flag on B-V
 116-120  F5.2   mag       U-B        ? U-B color in the UBV system
     121  A1     ---       u_U-B      [ :?] Uncertainty flag on U-B
 122-126  F5.2   mag       R-I        ? R-I   in system specified by n_R-I
     127  A1     ---       n_R-I      [CE:?D] Code for R-I system (Cousin, Eggen)
*128-147  A20    ---       SpType     Spectral type
     148  A1     ---       n_SpType   [evt] Spectral type code
 149-154  F6.3   arcsec/yr pmRA       ?Annual proper motion in RA J2000, FK5 system
 155-160  F6.3   arcsec/yr pmDE       ?Annual proper motion in Dec J2000, FK5 system
     161  A1     ---       n_Parallax [D] D indicates a dynamical parallax,
                                      otherwise a trigonometric parallax
 162-166  F5.3   arcsec    Parallax   ? Trigonometric parallax (unless n_Parallax)
 167-170  I4     km/s      RadVel     ? Heliocentric Radial Velocity
 171-174  A4     ---       n_RadVel  *[V?SB123O ] Radial velocity comments
 175-176  A2     ---       l_RotVel   [<=> ] Rotational velocity limit characters
 177-179  I3     km/s      RotVel     ? Rotational velocity, v sin i
     180  A1     ---       u_RotVel   [ :v] uncertainty and variability flag on
                                      RotVel
 181-184  F4.1   mag       Dmag       ? Magnitude difference of double,
                                        or brightest multiple
 185-190  F6.1   arcsec    Sep        ? Separation of components in Dmag
                                        if occultation binary.
 191-194  A4     ---       MultID     Identifications of components in Dmag
 195-196  I2     ---       MultCnt    ? Number of components assigned to a multiple
     197  A1     ---       NoteFlag   [*] a star indicates that there is a note
                                        (file notes.dat)
--------------------------------------------------------------------------------
*/
