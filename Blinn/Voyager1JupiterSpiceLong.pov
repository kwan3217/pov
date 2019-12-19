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

//#declare StartCal="1986-01-24 17:59:47TDB"; //Nominal closest approach
//#declare Cal0="1986-01-24 01:07:40TDB"; //Best fit to short Blinn start
//#declare Cal1="1986-01-25 17:05:03TDB"; //Best fit to short Blinn stop
#declare Cal0="1986-01-24 00:00:00TDB";
#declare Cal1="1986-01-25 01:00:00TDB";
#declare ET0=str2et(Cal0);
PrintNumber("ET0: ",ET0)
PrintNumber(concat("ET0: ",etcal(ET0)," "),ET0)
#declare ET1=str2et(Cal1);
PrintNumber(concat("ET1: ",etcal(ET1)," "),ET1)

#declare RubberClockFrame=array[24] {
120,
415,
817,
1027,
1385,
1742,
3165,
3472,
3507,
3775,
4363,
4398,
4434,
4470,
4896,
4932,
4968,
5003,
5039,
5075,
5110,
5373,
6275,
7464
}

#declare RubberClockTime=array[24] {
str2et("1986-01-24 03:27:06.676TDB"),
str2et("1986-01-24 04:45:44.891TDB"),
str2et("1986-01-24 08:14:58.672TDB"),
str2et("1986-01-24 09:07:00.407TDB"),
str2et("1986-01-24 08:49:43.846TDB"),
str2et("1986-01-24 10:06:52.211TDB"),
str2et("1986-01-24 13:25:08.554TDB"),
str2et("1986-01-24 14:17:46.448TDB"),
str2et("1986-01-24 14:19:22.873TDB"),
str2et("1986-01-24 14:38:52.017TDB"),
str2et("1986-01-24 16:09:52.040TDB"),
str2et("1986-01-24 16:11:28.465TDB"),
str2et("1986-01-24 16:13:04.889TDB"),
str2et("1986-01-24 16:14:41.313TDB"),
str2et("1986-01-24 16:40:12.048TDB"),
str2et("1986-01-24 16:42:36.685TDB"),
str2et("1986-01-24 16:45:01.321TDB"),
str2et("1986-01-24 16:47:25.958TDB"),
str2et("1986-01-24 16:49:50.594TDB"),
str2et("1986-01-24 16:52:15.230TDB"),
str2et("1986-01-24 16:54:39.867TDB"),
str2et("1986-01-24 17:18:10.072TDB"),
str2et("1986-01-24 19:52:02.694TDB"),
str2et("1986-01-25 00:16:48.591TDB")
}

#declare NWnd=ckcov("Voyager/ck/vg2_ura_version1_type1_iss_sedr.bc",-32100,"INTERVAL",0,"TDB",10000);
PrintNumber("NWnd: ",NWnd)

//Animation settings
#macro RubberClock(F) 
  (Tableterp(RubberClockFrame,RubberClockTime,F))
#end
#declare ET=RubberClock(frame_number); 
PrintNumber(concat("This ET: ",etcal(ET)," "),ET)

#declare I=0;
#while(ckgetcov(I,0)<ET) 
  #declare I=I+1;
#end
#declare ETScan=ckgetcov(I-1,0);
PrintNumber("ETScanI: ",I)
PrintNumber(etcal(ETScan),ETScan)

//Targets are 0 for the planet, 1-5 for the major satellites in Spice order, 6 for Sigma Sagitarius
#declare SpiceTarget=array[7] {799,701,702,703,704,705,-1}
#declare TargetName=array[7] {"Uranus","Ariel","Umbriel","Titania","Oberon","Miranda","SigSag"}
#declare Gray=<1,1,1>;
#declare TargetColor=array[7] {<0,135,213>/255,Gray*0.39,Gray*0.21,Gray*0.27,Gray*0.23,Gray*0.32,Gray*-1}

//Start images for VxBEST sequences
                                     // P A    U    T    O    M
#declare CloseupStartImg=array[7]    {-1,5001,4976,4982,4960,5006,-1}
#declare CloseupNumImg=array[7]      {-1,4   ,1   ,2   ,1   ,8   ,-1}
#declare CloseupTargetTable=array[7] {-1,7   ,3   ,5   ,1   ,8   ,-1}
#declare H=array[7]                  {-4,1.3 ,2.2 ,1.2 ,1.4 ,3.4 ,-1} //Absolute magnitudes of satellites

#declare TargetTable=array[10][2] {{str2et("1986-01-24 01:00:00TDB"),0},
                                   {str2et("1986-01-24 08:30:00TDB"),4}, //VOBEST
                                   {str2et("1986-01-24 09:00:00TDB"),0},
                                   {str2et("1986-01-24 11:30:00TDB"),2}, //VUBEST
                                   {str2et("1986-01-24 12:00:00TDB"),0},
                                   {str2et("1986-01-24 14:00:00TDB"),3}, //VTBEST
                                   {str2et("1986-01-24 14:30:00TDB"),0},
                                   {str2et("1986-01-24 16:00:00TDB"),1}, //VABEST
                                   {str2et("1986-01-24 16:30:00TDB"),5}, //VMBEST
                                   {str2et("1986-01-24 17:00:00TDB"),0}}

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
          map_type spherical //spheroid
//          flatness (PlA-PlB)/PlA
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

//Ring data from Constantine Thomas' Site http://www.lancs.ac.uk/postgrad/thomasc1/render/planets/uranus.htm
//Translated to POV by me
//All rings are rendered 100km wider than reality - inner radius is decreased by this amount

                          // 6     5     4     alpha beta  eta   gamma delta epsilon
#declare RingOuter=array[9] {41910,42305,42610,44807,45708,47260,47710,48310,51300}
#declare RingInner=array[9] {41900,42300,42600,44800,45700,47200,47700,48300,51200}

#declare UranusModel=union {
  Spherical(799,"Uranus",<0,1,0>)
  union {
  #local I=0;
  #while(I<9)
    disc {0,z,RingOuter[I],RingInner[I]-100}
    #local I=I+1;
  #end
    texture {RingTex}
  }
}

#declare OrbitTrans=BLinterp(95,0,139,1,frame_number);

#declare UranusOrbit=union {
  union {
  #local I=1;
  #while(I<=5)
    #local r_i=spkezr(str(SpiceTarget[I],0,0),ET,RefFrame,"NONE",str(SpiceTarget[0],0,0));
    disc {0,z,vlength(r_i)+750,vlength(r_i)-750}
    #local I=I+1;
  #end
    texture {
      pigment {color rgbf <1,1,1,OrbitTrans>}
      finish {ambient 1 diffuse 0}
    }
  }
}

#local R_Pl=spkezr(str(SpiceTarget[0],0,0),ET,RefFrame,"LT+S",Spacecraft);
PrintVector("R_Pl: ",R_Pl)

#declare InPlaceUranus=union {
  object {UranusModel}
  #if(OrbitTrans<1) object {UranusOrbit} #end
  QuatTrans(pxform("IAU_URANUS",RefFrame,ET),R_Pl)
}

object{InPlaceUranus}

#include "LocLook.inc"

#macro SunFlare(SunPos,CamPos,Angle)
  disc {
    0,z,1
    pigment {
      image_map {
        png "flare.png"
      }
      scale 2
      translate -x-y
    }
    finish {ambient 1 diffuse 0}
    no_shadow
    scale radians(Angle)*vlength(CamPos-SunPos)
    LocationLookAt(SunPos,CamPos,y)
  }
#end  

#declare NAFoV=0.424; //degrees, full width of square field of view along sides
#declare NAFoVOuter=NAFoV;
#declare NAFoVInner=NAFoV*0.98;

#macro viewpoint(ETShot,Center,Frame)
  difference {
    intersection {
      plane { x,0 rotate  y*NAFoVOuter/2}
      plane {-x,0 rotate -y*NAFoVOuter/2}
      plane {-y,0 rotate  x*NAFoVOuter/2}
      plane { y,0 rotate -x*NAFoVOuter/2}
    }
    intersection {
      plane { x,0 rotate  y*NAFoVInner/2}
      plane {-x,0 rotate -y*NAFoVInner/2}
      plane {-y,0 rotate  x*NAFoVInner/2}
      plane { y,0 rotate -x*NAFoVInner/2}
    }

    QuatTrans(pxform("VG2_SCAN_PLATFORM",Frame,ETShot),spkezr(Spacecraft,ETShot,Frame,"LT+S",Center))

  no_shadow
  }
#end

#macro viewpoints(FirstShot,NShots,ET,Center,Frame)
  #local I=0;
  union {
  #while(I<NShots & ckgetcov(I+FirstShot,0)<ET)
    viewpoint(ckgetcov(I+FirstShot,0),Center,Frame)
    #local I=I+1;
  #end
  }
#end

#declare SigSgr=QuatVectRotate(pxform("J2000",RefFrame,ET),<214095.0732442103326321,-870573.0495412370655686,-443019.0346080258022994>);

#declare DoZoomIn=1;

#local I=1;
#declare AU=149597871;
#while(I<=5)
  PrintNumber("Sat: ",SpiceTarget[I])
  #local ObjFrame=concat("IAU_",strupr(TargetName[I]));
  #if((TargetTable[CloseupTargetTable[I]][0]<=ET) & (TargetTable[CloseupTargetTable[I]+1][0]>ET) & DoZoomIn)
    //We are doing a closeup of this moon right now, get the full model
    PrintNumber(concat("Closeup of ",TargetName[I],": "),1)
    #declare VxBEST=viewpoints(CloseupStartImg[I],CloseupNumImg[I],ET,str(SpiceTarget[I],0,0),ObjFrame)
    object {
      SphBody(SpiceTarget[I],TargetName[I],TargetColor[I]) 
      texture {
        object {
          VxBEST
          SphTex(SpiceTarget[I],TargetName[I],TargetColor[I])
          texture {pigment {color rgb 1} finish {ambient 1 diffuse 0}}
        }
      }
      QuatTrans(pxform(ObjFrame,RefFrame,ET),spkezr(str(SpiceTarget[I],0,0),ET,RefFrame,"LT+S",Spacecraft))
    }
    plane {
      QuatVectRotate(pxform("VG2_SCAN_PLATFORM",ObjFrame,ckgetcov(CloseupStartImg[I],0)),z),0
      texture {
        object {VxBEST
          texture {pigment {color rgbf <1,1,1,1>}}
          texture {pigment {color rgb 1} finish {ambient 1 diffuse 0}}
        }
      }
      QuatTrans(pxform(ObjFrame,RefFrame,ET),spkezr(str(SpiceTarget[I],0,0),ET,RefFrame,"LT+S",Spacecraft))
    }  
  #else
    //Simplified model
    #local Sp=spkezr(Spacecraft,ET,RefFrame,"LT+S",str(SpiceTarget[I],0,0))/AU;
    PrintVector("Sp: ",Sp)
    #local Ss=spkezr("SUN"     ,ET,RefFrame,"LT+S",str(SpiceTarget[I],0,0))/AU;
    PrintVector("Ss: ",Ss)
    #local theta=vangle(Sp,Ss);
    PrintNumber("theta: ",degrees(theta))
    #local p=2/3*((1-theta/pi)*cos(theta)+1/pi*sin(theta));
    PrintNumber("p: ",p)
    #local m=H[I]+2.5*log(pow(vlength(Ss),2)*pow(vlength(Sp),2)/(p*pow(1,4)));
    PrintNumber("m: ",m)
    union {
      Spherical(SpiceTarget[I],TargetName[I],TargetColor[I])
      QuatTrans(pxform(concat("IAU_",strupr(TargetName[I])),RefFrame,ET),spkezr(str(SpiceTarget[I],0,0),ET,RefFrame,"LT+S",Spacecraft))
    }
  #end
  #local I=I+1;
#end

#declare CamAngleFrame=array[8] {
  0,69,158,315,415,744,843,8000
}

#declare CamAngleTable=array[8] {
  ln(78),
  ln(78),
  ln(44),
  ln(44),
  ln(5),
  ln(5),
  ln(44),
  ln(44)
}

#declare TargetFrame=array[7] {
  0,315,315,415,744,843,8000
}

#declare TargetTable=array[7] {
  0,0,6,6,6,0,0
}

#declare ObjPosFrame=array[7] {
  0,158,315,315,346,415,8000
}

//Target position on screen in SD 720x540 coordinates
#declare ObjPosTable=array[7] {
  <327,224>,
  <336,228>,
  <350,232>, //Step change from Uranus...
  <335,291>, //...to SigSgr
  <303,335>,
  <320,438>,
  <350,232> 
}

#declare ScPosFrame=array[7] {
  0,105,315,415,744,843,8000
}

//S/C position on screen in SD 720x540 coordinates
#declare ScPosTable=array[7] {
  <-1000,800,1>,
  <146,720,1>,
  <406,403,1>,
  <406,803,0>,
  <406,803,0>,
  <563,113,1>,
  <563,113,1>,
}

#declare ScDistFrame=array[4] {
  0,105,315,8000
}

#declare ScDistTable=array[4] {
  ln(40),
  ln(10),
  ln(21.5),
  ln(40)
}

#macro spkezrTarget(Target,ET) 
  #if(Target=6) 
    #local result=SigSgr;
  #else
    #local result=spkezr(str(SpiceTarget[Target],0,0),ET,RefFrame,"LT+S",Spacecraft);
  #end
  (result)
#end

#declare CamSky=<0,0,1>;
#declare CamAngle=exp(Tableterp(CamAngleFrame,CamAngleTable,frame_number));
#declare CamTan=tan(radians(CamAngle)/2);
#declare CamUp=1;
#declare CamRight=image_width/image_height;
#declare ObjPos=Tableterp(ObjPosFrame,ObjPosTable,frame_number);
#declare ObjPos=<(ObjPos.x/720)*2-1,1-(ObjPos.y/540)*2,1>;
#declare TargetI=TPIR(TargetFrame,frame_number);
PrintNumber("TargetI: ",TargetI)
#declare Target0=TargetTable[TargetI+0];
#declare Target1=TargetTable[TargetI+1];
#declare ObjAxis0=vnormalize(spkezrTarget(Target0,ET));
#declare ObjAxis1=vnormalize(spkezrTarget(Target1,ET));
#declare ObjAxis=Linterp(TargetFrame[TargetI+0],ObjAxis0,TargetFrame[TargetI+1],ObjAxis1,frame_number);
#declare ObjHoriz=vnormalize(vcross(ObjAxis,CamSky))*CamTan;
#declare ObjVert=vnormalize(vcross(ObjHoriz,ObjAxis))*CamTan*CamUp/CamRight;
#declare CamAxis=ObjAxis-ObjHoriz*ObjPos.x-ObjVert*ObjPos.y;
#declare CamHoriz=vnormalize(vcross(CamAxis,CamSky))*CamTan;
#declare CamVert=vnormalize(vcross(CamHoriz,CamAxis))*CamTan*CamUp/CamRight;
#declare ScPos=Tableterp(ScPosFrame,ScPosTable,frame_number);
#declare ScPos=<(ScPos.x/720)*2-1,1-(ScPos.y/540)*2,ScPos.z>;
#declare ScDist=exp(Tableterp(ScDistFrame,ScDistTable,frame_number));
#declare CameraLoc=-ScDist*(ScPos.x*CamHoriz*CamRight+ScPos.y*CamVert*CamUp+ScPos.z*CamAxis);
#declare CameraLook=CameraLoc+CamAxis;

#local norm=<0,0,0>;
#local junk=trace(InPlaceUranus,CameraLoc,vnormalize(spkezr("SUN",ET,RefFrame,"LT+S",Spacecraft)),norm);
#if(vlength(norm) = 0) 
SunFlare(spkezr("SUN",ET,RefFrame,"LT+S",Spacecraft),CameraLoc,2)
#end

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

#include "Voyager.inc"
union {
  object{VoyagerQSpice(pxform("VG2_SCAN_PLATFORM","VG2_SC_BUS",ETScan))}
  PrintQuat("VG2_SC_BUS: ",pxform("VG2_SC_BUS",RefFrame,ET))
  QuatTrans(pxform("VG2_SC_BUS",RefFrame,ET),<0,0,0>)
}

/*
union {
  textHud(etcal(ETScan),<3.6,-4.65>,<1,1,1>,1,-1)
  textHud(etcal(ET),<3.6,-4.45>,<1,1,1>,1,-1)
  textHud(concat("Distance to ",TargetName[Target],": "),<-5.9,-4.45>,<1,1,1>,0,-1)
  textHudNumber(vlength(M)*1000,"m",<-2.9,-4.45>,<1,1,1>,-1)
  scale <0.175,0.175,1>/CamTan
  no_shadow
  LocationLookAt(CameraLoc,CameraLook,CamSky)
}
*/

