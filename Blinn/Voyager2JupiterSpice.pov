#include "KwanMath.inc"
#include "LocLook.inc"
#include "hud.inc"
#include "textures.inc"
#include "SpiceQuat.inc"

//#version unofficial Megapov 1.22;

#furnsh "generic/generic.tm"
#furnsh "Voyager/vgr2.tm"

//#declare StartCal="1986-01-24 17:59:47TDB"; //Nominal closest approach
//#declare Cal0="1986-01-24 01:07:40TDB"; //Best fit to short Blinn start
//#declare Cal1="1986-01-25 17:05:03TDB"; //Best fit to short Blinn stop
#declare Cal0="1979-07-07 11:39:45 TDB";
#declare Cal1="1979-07-11 05:11:11 TDB";
#declare ET0=str2et(Cal0);
PrintNumber("ET0: ",ET0)
PrintNumber(concat("ET0: ",etcal(ET0)," "),ET0)
#declare ET1=str2et(Cal1);
PrintNumber(concat("ET1: ",etcal(ET1)," "),ET1)
PrintNumber("frame_number: ",frame_number)
#declare ET=Linterp(initial_frame,ET0,final_frame,ET1,frame_number); 
PrintNumber(concat("This ET: ",etcal(ET)," "),ET)

#declare Spacecraft="-32";

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
#declare SpiceTarget=array[6] {599,501,502,503,504,505}
#declare TargetName=array[6] {"Jupiter","Io","Europa","Ganymede","Callisto","Amalthea"}
#declare Gray=<1,1,1>;
#declare TargetColor=array[6] {<0,135,213>/255,Gray*0.39,Gray*0.21,Gray*0.27,Gray*0.23,Gray*0.32}
#declare TargetExtraRot=array[6] {100,0,0,0,0,0}
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
#macro SphTex(ShapeNum,ShapeName,Color,ExtraRot)
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
        rotate z*ExtraRot
      }
    #else
      #debug concat("Map ",MapName," Not Found, using base color\n")
      pigment {color Color}
    #end
    finish {ambient 0.15 diffuse 0.85 brilliance Brilliance}
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
#macro Spherical(ShapeNum,ShapeName,Color,ExtraRot)  
  object {
    SphBody(ShapeNum,ShapeName,Color)
    SphTex(ShapeNum,ShapeName,Color,ExtraRot)
  }
#end

//Draw Jupiter
#local I=0;
PrintNumber("Sat: ",SpiceTarget[I])
#local ObjFrame=concat("IAU_",strupr(TargetName[I]));
object {
  Spherical(SpiceTarget[I],TargetName[I],TargetColor[I],TargetExtraRot[I]) 
  QuatTrans(pxform(ObjFrame,RefFrame,ET),spkezr(str(SpiceTarget[I],0,0),ET,RefFrame,"LT+S",Spacecraft))
  scale 0.1
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
      scale <VolcanoHeight[P]*2,VolcanoWidth[P]/2,VolcanoWidth[P]/2>
      translate x*(IoRad-VolcanoHeight[P])
      rotate -y*VolcanoPos[P].lat
      rotate  z*VolcanoPos[P].lon
      PrintVector("Position (iocentric): ",VolcanoPos[P])
      pigment {color rgbt <0.8,0.8,1,0.8>}
      finish {ambient 0.5 diffuse 0}
      no_shadow
    }
    #local P=P+1;
  #end
  QuatTrans(pxform("IAU_IO",RefFrame,ET),spkezr("501",ET,RefFrame,"LT+S",Spacecraft))
  scale 0.1
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
        Spherical(SpiceTarget[I],TargetName[I],TargetColor[I],TargetExtraRot[I]) 
        QuatTrans(pxform(ObjFrame,RefFrame,ET),spkezr(str(SpiceTarget[I],0,0),ET,RefFrame,"LT+S",Spacecraft))
      }
      #local I=I+1;
    #end
    sphere {
      0,500
      pigment {color rgb <1,0,1>}
      finish {ambient 1 diffuse 0}
      QuatTrans(pxform("IAU_AMALTHEA",RefFrame,ET),spkezr("505",ET,RefFrame,"LT+S",Spacecraft))
      no_shadow
    }
  }
  scale 0.1
  global_lights on
}


#declare CamT=array[16] {ET0,
                        str2et("1979-03-05 11:00:00 UTC"), str2et("1979-03-05 11:30:00 UTC"), //Swing to Io
                        str2et("1979-03-05 16:00:00 UTC"), str2et("1979-03-05 16:30:00 UTC"), //Back to Jupiter
                        str2et("1979-03-05 17:30:00 UTC"), str2et("1979-03-05 18:00:00 UTC"), //Swing to Callisto
                        str2et("1979-03-05 21:00:00 UTC"), str2et("1979-03-05 21:30:00 UTC"), //Swing to Ganymede
                        str2et("1979-03-06 03:00:00 UTC"), str2et("1979-03-06 03:30:00 UTC"), //Back to Jupiter
                        str2et("1979-03-05 10:00:00 UTC"), str2et("1979-03-05 10:30:00 UTC"), //Swing to Callisto
                        str2et("1979-03-06 12:00:00 UTC"), str2et("1979-03-06 12:30:00 UTC"), //Back to Jupiter
                        ET1};
                     

#declare J=spkezr("599",ET,RefFrame,"LT+S",Spacecraft);
#declare I=spkezr("501",ET,RefFrame,"LT+S",Spacecraft);
#declare E=spkezr("502",ET,RefFrame,"LT+S",Spacecraft);
#declare G=spkezr("503",ET,RefFrame,"LT+S",Spacecraft);
#declare C=spkezr("504",ET,RefFrame,"LT+S",Spacecraft);
#declare CamL=array[16] {J,
                         J,I,
                         I,J,
                         J,C,
                         C,G,
                         G,J,
                         J,C,
                         C,J,
                         J}

#declare CamA=array[16] {45,
                         45,45,
                         45,45,
                         45,15,
                         15,15,
                         15,45,
                         45,45,
                         45,45,
                         45}

#declare CamSky=<0,0,1>;
#declare CamAngle=Tableterp(CamT,CamA,ET);
#declare CamTan=tan(radians(CamAngle)/2);
#declare CamUp=1;
#declare CamRight=image_width/image_height;
#declare CameraLoc=<0,0,0>;
#declare CameraLook=Tableterp(CamT,CamL,ET);
#declare StageOut=vnormalize(CameraLook-CameraLoc);
#declare StageRight=vnormalize(vcross(StageOut,CamSky));
#declare StageUp=vnormalize(vcross(StageRight,StageOut));
#declare SCPos=50*StageOut-5*StageUp+13*StageRight;

#include "Hud2018.inc"
#declare HudObject=union {
  #declare I=0;
  #while(I<NWnd)
    #local ThisETScan=ckgetcov(I,0);
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
    #declare I=I+1;
  #end  
  #local X=Linterp(ET0,-CamRight/2,ET1,CamRight/2,ET);
  cylinder {
    <X,CamUp/2,0>,<X,CamUp/2-0.01,0>,0.001
    pigment {color rgb <1,1,1>}
    finish {ambient 1 diffuse 0}
  }
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
//#declare CelestialSphereRad=2e6;
#declare LimitMag=3.5;
#include "StarsRight.inc"
object {
  Stars
  QuatTrans(pxform("J2000",RefFrame,ET),<0,0,0>)
}

PrintNumber("ET0: ",ET0)
PrintNumber(concat("ET0: ",etcal(ET0)," "),ET0)
#declare ET1=str2et(Cal1);
PrintNumber(concat("ET1: ",etcal(ET1)," "),ET1)
PrintNumber("frame_number: ",frame_number)
#declare ET=Linterp(initial_frame,ET0,final_frame,ET1,frame_number); 
PrintNumber(concat("This ET: ",etcal(ET)," "),ET)

