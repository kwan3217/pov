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

#declare Cal0="1979-03-04 00:00:00TDB";
#declare Cal1="1979-03-07 00:00:00TDB";
#declare ET0=str2et(Cal0);
PrintNumber("ET0: ",ET0)
PrintNumber(concat("ET0: ",etcal(ET0)," "),ET0)
#declare ET1=str2et(Cal1);
PrintNumber(concat("ET1: ",etcal(ET1)," "),ET1)

//Animation settings
PrintNumber("frame_number: ",frame_number)
#declare ET=Linterp(initial_frame,ET0,final_frame,ET1,frame_number); 
PrintNumber(concat("This ET: ",etcal(ET)," "),ET)

//Targets are 0 for the planet, 1-5 for the major satellites in Spice order, 6 for Sigma Sagitarius
#declare SpiceTarget=array[6] {599,501,502,503,504,505}
#declare TargetScale=array[6] {1,10,10,10,10,100}
#declare TargetName=array[6] {"Jupiter","Io","Europa","Ganymede","Callisto","Amalthea"}
#declare Gray=<1,1,1>;
#declare TargetColor=array[6] {<0,135,213>/255,Gray*0.39,Gray*0.21,Gray*0.27,Gray*0.23,<1,0.5,0.5>*0.32}

#declare Spacecraft="-31";
#declare RefFrame="ECLIPJ2000";

//Spacecraft is at origin of coordinate system, scaled by a factor of 1000
//so as to avoid numerical issues

//Position of Sun relative to spacecraft
light_source {
  spkezr("SUN",ET,RefFrame,"LT+S","599")
  color rgb <1,1,1>*1.5
}

global_settings{max_trace_level 10}

//Planet model

#declare DefaultBrilliance=0.75;
#declare Brilliance=DefaultBrilliance;
#macro SphTex(ShapeNum,ShapeName,Color,ExtraScale)
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
    scale PlA*ExtraScale
  }
#end
#macro SphBody(ShapeNum,ShapeName,Color,ExtraScale)
  #local PlA=gdpool(concat("BODY",str(ShapeNum,0,0),"_RADII"),0);
  #local PlB=gdpool(concat("BODY",str(ShapeNum,0,0),"_RADII"),2);
  sphere {
    <0,0,0>,1
    scale <1,1,PlB/PlA>
    scale PlA*ExtraScale
  }
#end
#macro Spherical(ShapeNum,ShapeName,Color,ExtraScale)  
  object {
    SphBody(ShapeNum,ShapeName,Color,ExtraScale)
    SphTex(ShapeNum,ShapeName,Color,ExtraScale)
  }
#end

#declare CamAngle=45;
#declare CamLoc=z*5e6;
#declare pixsize=radians(CamAngle/image_width);

#macro DrawTrajectory(body,et0,et1,dt,r,track_color,mark_r,mark_color)
  #if(et1>et0)
    #local et=et0;
    #local x0=spkezr(body,et,RefFrame,"NONE","599");
    #local et=et+dt;
    union {
      #while(et<et1)
        #local x1=spkezr(body,et,RefFrame,"NONE","599");
        sphere {
          x0,r*pixsize*vlength(x0-CamLoc)
        }
        cylinder {
          x0,x1,r*pixsize*vlength(x0-CamLoc)
        }
        #local x0=x1;
        #local et=et+dt;
      #end
      #local x1=spkezr(body,et1,RefFrame,"NONE","599");
      #if(vlength(x1-x0)>0)
        cylinder {
          x0,x1,r*pixsize*vlength(x0-CamLoc)
        }
      #end
      #if(mark_r>0)
        #local minr=3*r*pixsize*vlength(x0-CamLoc);
        sphere {
          x1,max(mark_r,minr)
          texture {
            pigment {color rgb mark_texture}
            finish {ambient 1 diffuse 0 specular 0}
          }
        }
      #end
      finish {ambient 1 diffuse 0 specular 0}
      pigment {color rgb <1,1,1>}
    }
  #end
#end

#local I=0;
#while(I<=5)
  PrintNumber("Object: ",SpiceTarget[I])
  #local ObjFrame=concat("IAU_",strupr(TargetName[I]));
  union {
    Spherical(SpiceTarget[I],TargetName[I],TargetColor[I],TargetScale[I])
    QuatTrans(pxform(ObjFrame,RefFrame,ET),spkezr(str(SpiceTarget[I],0,0),ET,RefFrame,"NONE","599"))
  }
  #local I=I+1;
#end

sphere {
  0,10000
  translate spkezr(Spacecraft,ET,RefFrame,"NONE","599")
  pigment {color rgb <1,0,0>}
  no_shadow
  finish {ambient 1 diffuse 0 specular 0}
}

DrawTrajectory("-31",ET0,ET1,5000,0.5,<1,0,0>,0,0)
DrawTrajectory("501",ET0,ET1,2000,0.5,<1,0,0>,0,0)
DrawTrajectory("502",ET0,ET1,5000,0.5,<1,0,0>,0,0)
DrawTrajectory("503",ET0,ET1,5000,0.5,<1,0,0>,0,0)
DrawTrajectory("504",ET0,ET1,5000,0.5,<1,0,0>,0,0)
DrawTrajectory("505",ET0,ET1,1000,0.5,<1,0,0>,0,0)


camera {
  up y
  right -x*image_width/image_height
  sky y
  angle CamAngle
  location CamLoc
  look_at 0
}


