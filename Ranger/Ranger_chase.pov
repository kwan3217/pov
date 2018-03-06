#include "KwanMath.inc"
#include "SpiceQuat.inc"
//#declare StarRad=2000*1024/image_width; //Gives 500 radius at width 1024, proportionally less for proportionally higher resolution
//#declare LimitMag=3;
//#include "StarsRight.inc"

#furnsh "Ranger7.tm"
#include "Ranger_spacecraft.inc"

//Planet model

#declare SpiceTarget=array[2] {399,301}
#declare TargetName=array[2] {"Earth","Moon"}

#declare Spacecraft="-1007";
#declare RefFrame="J2000";

#declare DefaultBrilliance=0.75;
#declare Brilliance=DefaultBrilliance;
#declare Diffuse=1;
#macro SphTex(ShapeNum,ShapeName,Color,RotateZ)
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
        rotate z*RotateZ
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
#macro Spherical(ShapeNum,ShapeName,Color,Q,R,RotateZ)  
  object {
    SphBody(ShapeNum,ShapeName,Color)
    SphTex(ShapeNum,ShapeName,Color,RotateZ)
    QuatTrans(Q,R)
  }
#end

#declare ET0=str2et("1964 JUL 31 13:09:28 TDB");
PrintNumber("ET0: ",ET0)
PrintNumber(concat("ET0:  ",etcal(ET0)," "),ET0)
#declare ET1=str2et("1964 JUL 31 13:26:24.123 TDB");
PrintNumber(concat("ET1: ",etcal(ET1)," "),ET1)

#declare ET=Linterp(initial_clock,ET0,final_clock,ET1,clock);
PrintNumber(concat("ET:  ",etcal(ET )," "),ET)
#declare PlanetPos=spkezr(     "399",ET,RefFrame,"LT+S",Spacecraft);
PrintVector("PlanetPos: ",PlanetPos)
#declare MoonVel=<0,0,0>;
#declare MoonPos  =spkezr(     "301",ET,RefFrame,"LT+S",Spacecraft,MoonVel);
PrintVector("MoonPos: ",MoonPos)
#declare SunPos   =spkezr(     "SUN",ET,RefFrame,"LT+S",Spacecraft);
PrintVector("SunPos: ",SunPos)
#declare ScPos    =spkezr(Spacecraft,ET,RefFrame,"LT+S",Spacecraft);
#declare ScVel=-MoonVel;
PrintVector("ScPos: ",ScPos)
PrintVector("ScVel: ",ScVel)

union {
  light_source {
    SunPos
    color rgb <1,1,1>*1.5
  }

//  Spherical(399,"Earth",<0.0,0.0,1.0>,pxform("IAU_EARTH",RefFrame,ET),PlanetPos,0)
  difference {
    Spherical(301,"Moon" ,<0.5,0.5,0.5>,pxform("IAU_MOON" ,RefFrame,ET),MoonPos,180  )
    object {
      FOV_A
      #local Q=pxform("RANGER7_SPACECRAFT",RefFrame,ET);
      PrintQuat("Q: ",Q)
      QuatTrans(Q,ScPos)
    }
  }
//  scale 0.001
/*  sphere {
    ScPos,50
    pigment {color rgb <0,1,0>}
  }
*/
  object {
    Ranger_Spacecraft
    #local Q=pxform("RANGER7_SPACECRAFT",RefFrame,ET);
    PrintQuat("Q: ",Q)
    QuatTrans(Q,ScPos)
  }
/*
  cylinder {
    ScPos,ScPos+2*vnormalize(PlanetPos-ScPos),0.02
    pigment {color rgb <0.5,0.75,1>}
  }
*/
}
camera {
  up y
  right -x*image_width/image_height
  sky z
  location ScPos-ScVel*2-z
  look_at ScPos
//  angle 
}
