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
#furnsh "Voyager/vgr2.tm"

//#declare StartCal="1986-01-24 17:59:47TDB"; //Nominal closest approach
//#declare Cal0="1986-01-24 01:07:40TDB"; //Best fit to short Blinn start
//#declare Cal1="1986-01-25 17:05:03TDB"; //Best fit to short Blinn stop
#declare Cal0="1979-07-09 14:14:21 UTC";
#declare Cal1="1979-07-09 14:14:21 UTC";
#declare ET0=str2et(Cal0);
PrintNumber("ET0: ",ET0)
PrintNumber(concat("ET0: ",etcal(ET0)," "),ET0)
#declare ET1=str2et(Cal1);
PrintNumber(concat("ET1: ",etcal(ET1)," "),ET1)
PrintNumber("frame_number: ",frame_number)
#declare ET=Linterp(initial_frame,ET0,final_frame,ET1,frame_number); 
PrintNumber(concat("This ET: ",etcal(ET)," "),ET)

#declare ScanPlatformCK="Voyager/ck/vg2_jup_version1_type1_iss_sedr.bc";
#furnsh ScanPlatformCK
#declare NWnd=ckcov(ScanPlatformCK,-32100,"INTERVAL",0,"TDB",100000);
PrintNumber("NWnd: ",NWnd)

#declare I=0;
#while(ckgetcov(I,0)<ET) 
  #declare I=I+1;
#end
#declare ETScan=ckgetcov(I-1,0);
PrintNumber("ETScanI: ",I)
PrintNumber(etcal(ETScan),ETScan)



//Targets are 0 for the planet, 1-5 for the major satellites in Spice order, 6 for Sigma Sagitarius
#declare SpiceTarget=array[7] {599,501,502,503,504,505,-1}
#declare TargetName=array[7] {"Jupiter","Io","Europa","Ganymede","Callisto","Amalthea","SigSag"}
#declare Gray=<1,1,1>;
#declare TargetColor=array[7] {<0,135,213>/255,Gray*0.39,Gray*0.21,Gray*0.27,Gray*0.23,Gray*0.32,Gray*-1}

#declare Spacecraft="-32";
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

#declare RingTex=texture {
  pigment {color rgbf<0.15,0.15,0.15,0.6>}
  finish {ambient 1.0}
}
#declare DefaultBrilliance=0.75;
#declare Brilliance=DefaultBrilliance;
#macro SphTex(ShapeNum,ShapeName,Color)
  #local PlA=gdpool(concat("BODY",str(ShapeNum,0,0),"_RADII"),0);
  #local PlB=gdpool(concat("BODY",str(ShapeNum,0,0),"_RADII"),2);
  texture {
    #local MapName=concat(ShapeName,"Map.png")
    #if(/*ObjDetail[ShapeNum]>=1 & */file_exists(MapName))
      #debug concat("Map ",MapName," Found, using it\n")
      pigment {
        image_map
        {
          png MapName
          map_type spheroid
          flatness (PlA-PlB)/PlA
          interpolate 4
        }
        scale <-1,1,1>
        rotate x*90
        rotate z*180 //180 is valid for all Galileans

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
PrintNumber("Sat: ",SpiceTarget[I])
#local ObjFrame=concat("IAU_",strupr(TargetName[I]));
//We are doing a closeup of this moon right now, get the full model
object {
  Spherical(SpiceTarget[I],TargetName[I],TargetColor[I]) 
  QuatTrans(pxform(ObjFrame,RefFrame,ET),spkezr(str(SpiceTarget[I],0,0),ET,RefFrame,"LT+S",Spacecraft))
}

#local I=I+1;
light_group {
  light_source {
    spkezr("599",ET,RefFrame,"LT+S",Spacecraft)
    color rgb <0.2,0.15,0.1>
    shadowless
  }
  union {
    #while(I<=5)
      PrintNumber("Sat: ",SpiceTarget[I])
      #local ObjFrame=concat("IAU_",strupr(TargetName[I]));
      //We are doing a closeup of this moon right now, get the full model
      object {
        Spherical(SpiceTarget[I],TargetName[I],TargetColor[I]) 
        QuatTrans(pxform(ObjFrame,RefFrame,ET),spkezr(str(SpiceTarget[I],0,0),ET,RefFrame,"LT+S",Spacecraft))
      }
      #local I=I+1;
    #end
  }
  global_lights on
}

#declare CamSky=<0,0,1>;
#declare CamAngle=2;
#declare CamTan=tan(radians(CamAngle)/2);
#declare CamUp=1;
#declare CamRight=image_width/image_height;
#declare CameraLoc=<0,0,0>;
#declare CameraLook=spkezr("502",ET,RefFrame,"LT+S",Spacecraft);

camera {
  up y*CamUp
  right -x*CamRight
  sky CamSky
  angle CamAngle
  location CameraLoc 
  look_at CameraLook
}

#declare StarRatio=1440*45/CamAngle;
#include "StarsRight.inc"
object {
  Stars
  QuatTrans(pxform("J2000",RefFrame,ET),<0,0,0>)
}


