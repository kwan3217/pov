#include "KwanMath.inc"
#include "SpiceQuat.inc"
#declare StarRad=2000*1024/image_width; //Gives 500 radius at width 1024, proportionally less for proportionally higher resolution
#declare LimitMag=3;
#include "StarsRight.inc"
//#furnsh "generic/generic.tm"
#furnsh "emm_20161205_nominal.tm"
#include "emm_spacecraft.inc"

#declare EXI_FOV=25.39;
#declare EXI_FOV_vert=2*degrees(atan(image_height/image_width*tan(radians(EXI_FOV/2))));
//Planet model

#declare SpiceTarget=array[1] {499}
#declare TargetName=array[1] {"Mars"}

#declare Spacecraft="-62";
//#declare RefFrame="ECLIPJ2000";
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

#declare ET0=str2et("2021-05-02 17:00:00.000 UTC");
PrintNumber("ET0: ",ET0)
PrintNumber(concat("ET0: ",etcal(ET0)," "),ET0)
#declare ET1=ET0+3600*4;
PrintNumber(concat("ET1: ",etcal(ET1)," "),ET1)

#declare ET=Linterp(initial_clock,ET0,final_clock,ET1,clock);
PrintNumber(concat("ET: ",etcal(ET)," "),ET)
#declare SCQ=pxform("HOPE_SPACECRAFT",RefFrame,ET);
#declare EXIQ=pxform("HOPE_EXI_VIS",RefFrame,ET);
#declare PlanetPos=spkezr("MARS",ET,RefFrame,"LT+S",Spacecraft);
#declare SunPos=spkezr("SUN",ET,RefFrame,"LT+S",Spacecraft);

object {
  Stars 
  scale 1/1000000 
  scale vlength(PlanetPos)
  QuatTrans(pxform("J2000",RefFrame,ET),<0,0,0>)
}

#macro Ring(major,minor)
  cylinder {
    -y*minor,y*minor,major
    open
  }
#end

#declare SkyGrid=union {
  #local I=0;
  #local LineWeight=0.0001*(4096/image_width);
  #while(I<24)
    object {
      Ring(1,LineWeight)
      rotate 15*I*z
    }
    #local J=1;
    #while(J<12)
      text {
        ttf "courbd.ttf"
        concat(str(I*15,0,0),",",str(15*J-90,0,0)) 0 0
        rotate x*90
        scale 0.002*(4096/image_width)
        translate y
        rotate (15*J-90)*x
        rotate (15*I-90)*z
      }
      #local J=J+1;
    #end
    #local I=I+1;
  #end
  #local J=1;
  #while(J<12)
    object {
      Ring(cos(radians(15*J-90)),LineWeight)
      rotate x*90
      translate z*sin(radians(15*J-90))
    }
    #local J=J+1;
  #end
  scale vlength(PlanetPos)
  QuatTrans(pxform("J2000",RefFrame,ET),<0,0,0>)
  pigment {color rgb <1,1,1>}
  finish {ambient 1 diffuse 0}
  no_shadow
}

#declare ViewFrame=union {
  union {
    object {
      //Left edge, red
      Ring(1,LineWeight*2)
      rotate z*90
      rotate y*EXI_FOV/2
      finish {ambient 1 diffuse 0}
      pigment {color rgb <1,0,0>}
    }
    object {
      //Right edge, antired (cyan)
      Ring(1,LineWeight*2)
      rotate z*90
      rotate -y*EXI_FOV/2
      finish {ambient 1 diffuse 0}
      pigment {color rgb <0,1,1>}
    }
    clipped_by {
      intersection {
        plane {
          -y,0
          rotate x*EXI_FOV_vert/2
        }
        plane {
          y,0
          rotate -x*EXI_FOV_vert/2
        }
      }
    }
  }
  union {
    object {
      //Top edge, green
      Ring(1,LineWeight*2)
      rotate x*EXI_FOV_vert/2
      finish {ambient 1 diffuse 0}
      pigment {color rgb <1,0,1>}
    }
    object {
      //Bottom edge, antigreen (magenta)
      Ring(1,LineWeight*2)
      rotate -x*EXI_FOV_vert/2
      finish {ambient 1 diffuse 0}
      pigment {color rgb <0,1,0>}
    }
    clipped_by {
      intersection {
        plane {
          x,0
          rotate y*EXI_FOV/2
        }
        plane {
          -x,0
          rotate -y*EXI_FOV/2
        }
      }
    }
  }
  text {
    ttf "courbd.ttf"
    timout(ET,"YYYY-MM-DDTHR:MN:SC UTC ::UTC") 0 0
    //In this scale, 1 unit is half the screen width
    #ifndef(TimestampSize)
      #declare TimestampSize=0.005*(4096/image_width);
    #end
    scale TimestampSize
    //In this, X is from -1 (left edge) to 1 (right edge)
    //         Y is from -h/w (bottom edge) to h/w (top edge)
    translate <-0.99,-0.74,1>
    //Now scale to fit inside of actual field of view
    scale <-tan(radians(EXI_FOV/2)),tan(radians(EXI_FOV/2)),1>
    finish {ambient 1 diffuse 0}
    pigment {color rgb <1,1,1>}
  }
  scale vlength(PlanetPos)/2
  QuatTrans(EXIQ,<0,0,0>)
//  no_shadow
}

light_source {
  spkezr("SUN",ET,RefFrame,"LT+S",Spacecraft)
  color rgb <1,1,1>*1.5
}

PrintVector("PlanetPos: ",PlanetPos)
sphere {
  #declare SunSize=gdpool("BODY10_RADII",0)/vlength(SunPos)*vlength(PlanetPos); 
  PrintNumber("SunSize: ",SunSize)
  vnormalize(SunPos)*vlength(PlanetPos),SunSize
  PrintVector("SunPos: ",SunPos)
  //Apparent sun angular size is asin(r/R)
  no_shadow
  pigment {color rgb <1,0.5,0>}
  finish {ambient 1 diffuse 0}
}

Spherical(499,"Mars",<1,0,0>,pxform("IAU_MARS",RefFrame,ET),spkezr("MARS",ET,RefFrame,"LT+S",Spacecraft))
