#include "KwanMath.inc"
#include "LocLook.inc"
#include "hud.inc"
#include "textures.inc"
#include "SpiceQuat.inc"

//#version unofficial Megapov 1.22;

//Actual animation loop will use whatever +kfi and +kff say, but
//we set up a fake "frame_number" in case we want to render at a different fps.
//FrameNumber may not be an integer but will run from FirstFrame to LastFrame
//inclusive as clock runs from 0 to 1 inclusive
//#declare FirstFrame=0;
//#declare LastFrame=7466;
//#declare FrameNumber=linterp(

#furnsh "generic/generic.tm"
#furnsh "Voyager/vgr1.tm"

#declare Cal0="1979-03-01 00:00:00TDB";
#declare Cal1="1979-03-10 01:00:00TDB";
#declare ET0=str2et(Cal0);
PrintNumber("ET0: ",ET0)
PrintNumber(concat("ET0: ",etcal(ET0)," "),ET0)
#declare ET1=str2et(Cal1);
PrintNumber(concat("ET1: ",etcal(ET1)," "),ET1)

//Animation settings
#declare ET=Linterp(ET0,initial_frame,ET1,final_frame,frame_number); 
PrintNumber(concat("This ET: ",etcal(ET)," "),ET)

#declare I=0;
#while(ckgetcov(I,0)<ET) 
  #declare I=I+1;
#end
#declare ETScan=ckgetcov(I-1,0);
PrintNumber("ETScanI: ",I)
PrintNumber(etcal(ETScan),ETScan)

//Targets are 0 for the planet, 1-5 for the major satellites in Spice order, 6 for Sigma Sagitarius
#declare SpiceTarget=array[6] {599,501,502,503,504,505}
#declare TargetName=array[6] {"Jupiter","Io","Europa","Ganymede","Callisto","Amalthea"}
#declare Gray=<1,1,1>;
#declare TargetColor=array[6] {<0,135,213>/255,Gray*0.39,Gray*0.21,Gray*0.27,Gray*0.23,Gray*0.32}

#declare Spacecraft="-31";
#declare RefFrame="ECLIPJ2000";

//Spacecraft is at origin of coordinate system, scaled by a factor of 1000
//so as to avoid numerical issues

//Position of Sun relative to spacecraft
light_source {
  spkezr("SUN",ET,RefFrame,"LT+S",Spacecraft)
  color rgb <1,1,1>*1.5
}

global_settings{max_trace_level 10}

//Planet model

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
#macro Spherical(ShapeNum,ShapeName,Color)  
  object {
    SphBody(ShapeNum,ShapeName,Color)
    SphTex(ShapeNum,ShapeName,Color)
  }
#end

#local I=0;
#while(I<=5)
  PrintNumber("Object: ",SpiceTarget[I])
  #local ObjFrame=concat("IAU_",strupr(TargetName[I]));
  union {
    Spherical(SpiceTarget[I],TargetName[I],TargetColor[I])
    QuatTrans(pxform(ObjFrame,RefFrame,ET),spkezr(str(SpiceTarget[I],0,0),ET,RefFrame,"NONE","599"))
  }
  #end
  #local I=I+1;
#end

sphere {
  0,1000
  translate spkezr(Spacecraft,ET,RefFrame,"NONE","599")
}


camera {
  up y
  right -x*image_width/image_height
  sky y
  location z*5e6
  look_at 0
}


