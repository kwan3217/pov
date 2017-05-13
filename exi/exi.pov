#include "KwanMath.inc"
#include "SpiceQuat.inc"

#furnsh "generic/generic.tm"
#furnsh "emm/emm_LD0711_v160816.tm"

//Planet model

#declare SpiceTarget=array[1] {499}
#declare TargetName=array[1] {"Mars"}

#declare Spacecraft="-62";
#declare RefFrame="ECLIPJ2000";
#declare ET=486388767.185;
PrintNumber(concat("ET: ",etcal(ET)," "),ET)
PrintNumber("sclk ticks: ",sce2c(-62,ET))


#declare DefaultBrilliance=0.75;
#declare Brilliance=DefaultBrilliance;
#macro SphTex(ShapeNum,ShapeName,Color)
  #local PlA=gdpool(concat("BODY",str(ShapeNum,0,0),"_RADII"),0);
  #local PlB=gdpool(concat("BODY",str(ShapeNum,0,0),"_RADII"),2);
  texture {
    #local MapName=concat(ShapeName,"Map.png")
    #if(file_exists(MapName))
      #debug concat("Map ",MapName," Found, using it\n")
      pigment {
        image_map
        {
          png MapName
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
#macro Spherical(ShapeNum,ShapeName,Color,ET)  
  object {
    SphBody(ShapeNum,ShapeName,Color)
    SphTex(ShapeNum,ShapeName,Color)
    QuatTrans(pxform("IAU_MARS",RefFrame,ET),<0,0,0>)
  }
#end

//plan view
#declare Cal0="2021-Apr-17 16:32:22.347UTC";
#declare Cal1="2021-Apr-18 16:32:22.347UTC";
#declare ET0=str2et(Cal0);
PrintNumber("ET0: ",ET0)
PrintNumber(concat("ET0: ",etcal(ET0)," "),ET0)
#declare ET1=str2et(Cal1);
PrintNumber(concat("ET1: ",etcal(ET1)," "),ET1)

#declare N_Steps=1440;
#declare I=0;
#declare F=Linterp(initial_clock,0,final_clock,N_Steps,clock);
#while(I<F)
  #declare ET=Linterp(0,ET0,N_Steps,ET1,I);
  PrintNumber(concat("ET: ",etcal(ET)," "),ET)
  sphere {
    spkezr(Spacecraft,ET,RefFrame,"NONE","Mars"), 200
    pigment {color rgb <0,0,1>}
    no_shadow
  }
  #declare I=I+1;
#end

#declare ET=Linterp(initial_clock,ET0,final_clock,ET1,clock);


light_source {
  spkezr("SUN",ET,RefFrame,"LT+S","Mars")
  color rgb <1,1,1>*1.5
}

Spherical(499,"Mars",<1,0,0>,ET)



camera {
  up y*1
  right -x*image_width/image_height
  sky z
  location vnormalize(spkezr("SUN",ET,RefFrame,"LT+S","Mars"))*100000
  look_at <0,0,0>
}


