#version 3.7;
#include "PlanetNames.inc"
#include "KwanMath.inc"
#include "SpiceQuat.inc"
#furnsh "generic.tm"

#macro Spheroid(ShapeNum)  
  sphere {
    <0,0,0>,1
    PrintNumber("ShapeNum: ",ShapeNum)
    #local BodyI_radii=concat("BODY",str(ShapeNum,0,0),"_RADII");
    #debug concat(BodyI_radii,"\n")
    #local found=0;
    #local Re=gdpool(BodyI_radii,0,found); //First equatorial radius
    #local R2=gdpool(BodyI_radii,1,found); //Second equatorial radius
    #local Rp=gdpool(BodyI_radii,2,found); //Polar radius
    scale <1,1,Rp/Re>
    #local PngName=concat(PlanetName[ShapeNum],"Map.png")
    #local JpgName=concat(PlanetName[ShapeNum],"Map.jpg")
    pigment {
      image_map {
        #if(file_exists(PngName))
          #debug concat("Map ",PngName," Found, using it\n")
          png PngName
        #else
          #if(file_exists(JpgName))
            #debug concat("Map ",JpgName," Found, using it\n")
            jpeg JpgName
          #else
            #error "No map found"
          #end
        #end
        map_type spheroid
        flatness (1-Rp/Re)
        interpolate 4
      }
      scale <-1,1,1>
      rotate x*90
    }
    finish {ambient 0 diffuse 1 brilliance 0.5}
    scale <1,1,1>*Re
  }
#end

#declare ET=str2et("2017-Aug-21 15:00:00UTC")+clock*7*3600;
#declare EarthQ=pxform("IAU_EARTH","J2000",ET);
#declare SunR=spkezr("10",ET,"J2000","LT+S","399");
#declare MoonQ=pxform("IAU_MOON","J2000",ET);
#declare MoonR=spkezr("301",ET,"J2000","LT+S","399");
#declare MSO_x=vnormalize(SunR);
#declare MSO_z=<0,0,1>;
#declare MSO_y=vnormalize(vcross(MSO_x,MSO_z));
PrintVector("SunR: ",SunR)
PrintVector("vnormalize(SunR): ",vnormalize(SunR))
PrintVector("MoonR: ",MoonR)
PrintVector("vnormalize(MoonR): ",vnormalize(MoonR))
object {
  Spheroid(Ea)
  QuatTrans(EarthQ,<0,0,0>)
}

object {
  Spheroid(Mo)
  QuatTrans(MoonQ,MoonR)
}

camera {
  up y
  right -x*image_width/image_height
  sky z
  angle 0.5
  location MSO_x*2000000+MSO_y*20000
  look_at <0,0,0>
}

#declare SunLights=65*65;
#declare SunBright=1;
#declare found=0;
#debug "Sun\n"
light_source {
    #debug "Sun Light"
    SunR color SunBright
    #if(SunLights>1)
      #debug "Sun Light Area Light"
      area_light
      #local Re=gdpool("BODY10_RADII",0,found); //First equatorial radius
      <Re*2,0,0>,<0,Re*2,0>,sqrt(SunLights),sqrt(SunLights)
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

