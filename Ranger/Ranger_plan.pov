#include "KwanMath.inc"
#include "SpiceQuat.inc"
#declare StarRad=2000*1024/image_width; //Gives 500 radius at width 1024, proportionally less for proportionally higher resolution
#declare LimitMag=3;
#include "StarsRight.inc"
//#furnsh "generic/generic.tm"
#furnsh "Ranger7.tm"
#include "Ranger_spacecraft.inc"

//Planet model

#declare SpiceTarget=array[2] {399,301}
#declare TargetName=array[2] {"Earth","Moon"}

#declare Spacecraft="-1007";
#declare RefFrame="J2000";

#declare DefaultBrilliance=0.75;
#declare Brilliance=DefaultBrilliance;
#macro SphTex(ShapeNum,ShapeName,Color)
  #local PlA=gdpool(concat("BODY",str(ShapeNum,0,0),"_RADII"),0);
  #local PlB=gdpool(concat("BODY",str(ShapeNum,0,0),"_RADII"),2);
  texture {
    #local MapName=concat(ShapeName,"Map.jpg");
    #local MapPng=0;
    #if(!file_exists(MapName))
      #local MapName=concat(ShapeName,"Map.png");
      #local MapPng=1;
    #end
    #if(file_exists(MapName))
      #debug concat("Map ",MapName," Found, using it\n")
      pigment {
        image_map
        {
          #if(MapPng)
          png 
          #else
          jpeg
          #end
          MapName
          map_type spheroid
          flatness (PlA-PlB)/PlA
          interpolate 4
        }
        rotate x*90
        rotate z*180
        scale <1,-1,1>
      }
    #else
      #debug concat("Map ",MapName," Not Found, using base color\n")
      pigment {color Color}
    #end
    finish {ambient 0 #ifdef(Diffuse) diffuse Diffuse #end brilliance Brilliance}
    scale PlA
  }
#end
#macro SphBody(ShapeNum,ShapeName,Color)
  #local PlA=gdpool(concat("BODY",str(ShapeNum,0,0),"_RADII"),0);
  #local PlB=gdpool(concat("BODY",str(ShapeNum,0,0),"_RADII"),2);
  sphere {
    <0,0,0>,1
    scale <1,1,PlB/PlA>
    scale PlA
  }
#end
#macro Spherical(ShapeNum,ShapeName,Color,Q,R)  
  object {
    SphBody(ShapeNum,ShapeName,Color)
    SphTex(ShapeNum,ShapeName,Color)
    QuatTrans(Q,R)
  }
#end

#declare ET0=str2et("1964 JUL 28 17:20:32 TDB");
PrintNumber("ET0: ",ET0)
PrintNumber(concat("ET0:  ",etcal(ET0)," "),ET0)
#declare ET1=str2et("1964 JUL 31 13:26:24 TDB");;
PrintNumber(concat("ET1: ",etcal(ET1)," "),ET1)

#declare ET=ET0;
#declare OldET=ET;
#declare ScRad=50;
#declare DeltaET=clock_delta*(ET1-ET0);
#declare ETLim=Linterp(initial_clock,ET0,final_clock,ET1,clock)+DeltaET;

#while(ET<ETLim)
  PrintNumber(concat("ET: ",etcal(ET)," "),ET)
  //#declare SCQ=pxform("-1007",RefFrame,ET);
  //#declare EXIQ=pxform("HOPE_EXI_VIS",RefFrame,ET);
  #declare PlanetPos=<0,0,0>;
  #declare MoonPos  =spkezr(     "301",ET,RefFrame,"NONE","399");
  #declare ScPos    =spkezr(Spacecraft,ET,RefFrame,"NONE","399");
  sphere {
    ScPos,ScRad
    pigment {color rgb <0,1,0>}
  }
  sphere {
    MoonPos,ScRad    
    pigment {color rgb <0.5,0.5,0.5>}
  }

  #if(OldET!=ET)
    cylinder {
      OldScPos,ScPos,ScRad
      pigment {color rgb <0,1,0>}
    }
    cylinder {
      OldMoonPos,MoonPos,ScRad    
      pigment {color rgb <0.5,0.5,0.5>}
    }
  #end

  #declare OldMoonPos=MoonPos;
  #declare OldScPos=ScPos;
  #declare OldET=ET;
  #declare ET=ET+DeltaET;
  #if(ET>ETLim)
    #declare ET=ETLim;
  #end
#end

light_source {
  spkezr(     "SUN",ET,RefFrame,"NONE","399")
  color rgb <1,1,1>*1.5
}
Spherical(399,"Earth",<0.0,0.0,1.0>,pxform("IAU_EARTH",RefFrame,ET),PlanetPos)
Spherical(301,"Moon" ,<0.5,0.5,0.5>,pxform("IAU_MOON" ,RefFrame,ET),MoonPos  )
camera {
  up y
  right -x*image_width/image_height
  location PlanetPos+<0,0,5e5>
  look_at PlanetPos
  sky y
  angle 5
}
