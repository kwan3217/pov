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
#declare Cal0="1979-07-09 22:00:00 UTC";
#declare Cal1="1979-07-10 09:00:00 UTC";
#declare VolWatch0="1979-07-09 22:39:57.520 UTC";
#declare VolWatch1="1979-07-10 08:23:10.000 UTC";
#declare TCMbegin="1979-07-10 00:39:37 TDB";
#declare TCMend="1979-07-10 01:56:09 TDB";
#declare CalDiscovery="1979-03-08 13:28:00 UTC"; //Time that volcano discovery image was taken
#declare ET0=str2et(Cal0);
#declare ETVolWatch0=str2et(VolWatch0);
#declare ETVolWatch1=str2et(VolWatch1);
PrintNumber("ET0: ",ET0)
PrintNumber(concat("ET0: ",etcal(ET0)," "),ET0)
#declare ET1=str2et(Cal1);
PrintNumber(concat("ET1: ",etcal(ET1)," "),ET1)
PrintNumber("frame_number: ",frame_number)
#declare ET=Linterp(initial_frame,ET0,final_frame,ET1,frame_number); 
PrintNumber(concat("This ET: ",etcal(ET)," "),ET)
#declare ETTCMbegin=str2et(TCMbegin);
#declare ETTCMend  =str2et(TCMend  );

#declare Spacecraft="-32";

#if(Spacecraft="-32")
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
#else
#declare NWnd=0;
#declare ETScan=0;
#end

//Targets are 0 for the planet, 1-5 for the major satellites in Spice order, 6 for Sigma Sagitarius
#declare SpiceTarget=array[7] {599,501,502,503,504,505,-1}
#declare TargetName=array[7] {"Jupiter","Io","Europa","Ganymede","Callisto","Amalthea","SigSag"}
#declare Gray=<1,1,1>;
#declare TargetColor=array[7] {<0,135,213>/255,Gray*0.39,Gray*0.21,Gray*0.27,Gray*0.23,Gray*0.32,Gray*-1}

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

//Draw Jupiter
#local I=0;
PrintNumber("Sat: ",SpiceTarget[I])
#local ObjFrame=concat("IAU_",strupr(TargetName[I]));
object {
  Spherical(SpiceTarget[I],TargetName[I],TargetColor[I]) 
  QuatTrans(pxform(ObjFrame,RefFrame,ET),spkezr(str(SpiceTarget[I],0,0),ET,RefFrame,"LT+S",Spacecraft))
}


//Draw volcanic plumes
#macro LLR2XYZ(V)
  PrintVector("Input: ",V)
  #local CLat=cos(radians(V.lat));
  #local CLon=cos(radians(V.lon));
  #local SLat=sin(radians(V.lat));
  #local SLon=sin(radians(V.lon));
  #local Result=(<CLat*CLon,CLat*SLon,SLat>*V.alt);
  PrintVector("Result: ",Result)
  (Result)
#end
#declare IoRad=gdpool("BODY501_RADII",0);
PrintNumber("IoRad: ",IoRad)
#declare VolcanoPos=array[9] {
<0,0,0>,          //P0 (Not a plume)
<-18.71,-255.28,IoRad>, //P1 (Pele)
< 18.22,-302.56,IoRad>, //P2 (Loki)
<- 1.52,-255.28,IoRad>, //P3 (Prometheus)
< 18.43,-172.59,IoRad>, //P4 (Zamama)
< 24.46,-114.68,IoRad>, //P5 (Amirani)
< 19.53,-122.31,IoRad>, //P6 (Maui)
<-29.29,-209.74,IoRad>, //P7 (Marduk)
<-49.6 ,- 56.18,IoRad>, //P8 (Masubi)
}
#declare VolcanoWidth=array[9] {
     0, //P0
  1000, //P1
   210, //P2
   250, //P3
    75, //P4
   200, //P5
   250, //P6
   180, //P7
   150, //P8
}
#declare VolcanoHeight=array[9] {
     0, //P0
   280, //P1
   100, //P2
    70, //P3
    95, //P4
    80, //P5
    80, //P6
   120, //P7
    70, //P8
}
#local P=1;
union {
  #while(P<=8)
    PrintNumber("Drawing plume ",P)
    sphere {
      <0,0,0>,1
      scale <VolcanoHeight[P],VolcanoWidth[P]/2,VolcanoWidth[P]/2>
      translate x*IoRad
      rotate -y*VolcanoPos[P].lat
      rotate  z*VolcanoPos[P].lon
      PrintVector("Position (iocentric): ",VolcanoPos[P])
      pigment {color rgb <1,0.5,0>}
      finish {ambient 1 diffuse 0}
      no_shadow
    }
    #local P=P+1;
  #end
  QuatTrans(pxform("IAU_IO",RefFrame,ET),spkezr("501",ET,RefFrame,"LT+S",Spacecraft))
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
#declare CamAngle=0.424;
#declare CamTan=tan(radians(CamAngle)/2);
#declare CamUp=1;
#declare CamRight=image_width/image_height;
#declare CameraLoc=<0,0,0>;
#declare CameraLook=spkezr("501",ET,RefFrame,"LT+S",Spacecraft);
#declare StageOut=vnormalize(CameraLook-CameraLoc);
#declare StageRight=vnormalize(vcross(StageOut,CamSky));
#declare StageUp=vnormalize(vcross(StageRight,StageOut));
#declare SCPos=2000*StageOut-5*StageUp+13*StageRight;

#include "Hud2018.inc"
#declare HudObject=union {
  #if(ET>ETVolWatch0)
    cylinder {
      #local Left =Linterp(ET0,-CamRight/2,ET1,CamRight/2,ETVolWatch0);
      PrintNumber("Left:  ",Left)
      #local Right=Linterp(ET0,-CamRight/2,ET1,CamRight/2,min(ETVolWatch1,ET));
      PrintNumber("Right: ",Right)
      <Left,CamUp/2,0>,<Right,CamUp/2,0>,0.005
      pigment {color rgb <0,0,1>}
      finish {ambient 1 diffuse 0}
      no_shadow
    }
  #end
  #if(ET<ETVolWatch1)
    cylinder {
      <Linterp(ET0,-CamRight/2,ET1,CamRight/2,max(ET,ETVolWatch0)),CamUp/2,0>,<Linterp(ET0,-CamRight/2,ET1,CamRight/2,ETVolWatch1),CamUp/2,0>,0.005
      pigment {color rgb <0,0,0.5>}
      finish {ambient 1 diffuse 0}
    }
  #end
  cylinder {
    <Linterp(ET0,-CamRight/2,ET1,CamRight/2,ETTCMbegin),CamUp/2,0.005>,
    <Linterp(ET0,-CamRight/2,ET1,CamRight/2,ETTCMend  ),CamUp/2,0.005>,
    0.0025
    pigment {color rgb <1,0,0>}
    finish {ambient 1 diffuse 0}
  }
  #declare I=0;
  #while(I<NWnd)
    #local ThisETScan=ckgetcov(I,0);
    #if((ThisETScan>ETVolWatch0)*(ThisETScan<ETVolWatch1))
      #local X=Linterp(ET0,-CamRight/2,ET1,CamRight/2,ThisETScan);
      cylinder {
        <X,CamUp/2,0>,<X,CamUp/2-0.01,0>,0.001
        #if(ET>ThisETScan)
          pigment {color rgb <0,0,1>}
        #else
          pigment {color rgb <0,0,0.5>}
        #end
        finish {ambient 1 diffuse 0}
      }
    #end
    #declare I=I+1;
  #end  
  text {
    ttf "OfficeCodePro-Regular.ttf"
    etcal(ET) 0 0
    scale 0.02
    translate <-CamRight/2+0.02,-CamUp/2+0.02,0>
    pigment {color rgb <1,1,1>}
    finish {ambient 1 diffuse 0}
  }
}

Hud(HudObject,CamUp,CamRight,CamAngle,CamSky,CameraLoc,CameraLook,1)

camera {
  up y*CamUp
  right -x*CamRight
  sky CamSky
  angle CamAngle
  location CameraLoc 
  look_at CameraLook
}

#include "Voyager.inc"
union {
  object{VoyagerQSpice(pxform("VG2_SCAN_PLATFORM","VG2_SC_BUS",ETScan)) finish {ambient 0.5}}
  PrintQuat("VG2_SC_BUS: ",pxform("VG2_SC_BUS",RefFrame,ET))
  QuatTrans(pxform("VG2_SC_BUS",RefFrame,ET),SCPos)
}

#declare StarRatio=1440*45/CamAngle;
#include "StarsRight.inc"
object {
  Stars
  QuatTrans(pxform("J2000",RefFrame,ET),<0,0,0>)
}


