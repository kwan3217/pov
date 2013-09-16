#include "KwanMath.inc"
#include "LocLook.inc"
#include "hud.inc"
#include "textures.inc"
#include "SpiceQuat.inc"

#version unofficial Megapov 1.22;

#furnsh "generic/generic.tm"
#furnsh "Voyager/vgr2.tm"

//#declare StartCal="1986-01-24 17:59:47TDB"; //Nominal closest approach
//#declare Cal0="1986-01-24 01:07:40TDB"; //Best fit to short Blinn start
//#declare Cal1="1986-01-25 17:05:03TDB"; //Best fit to short Blinn stop
#declare Cal0="1986-01-24 16:00:00TDB";
#declare Cal1="1986-01-24 17:00:00TDB";
#declare ET0=str2et(Cal0);
PrintNumber("ET0: ",ET0)
PrintNumber(concat("ET0: ",etcal(ET0)," "),ET0)
#declare ET1=str2et(Cal1);
PrintNumber(concat("ET1: ",etcal(ET1)," "),ET1)

#declare NWnd=ckcov("Voyager/ck/vg2_ura_version1_type1_iss_sedr.bc",-32100,"INTERVAL",0,"TDB",10000);
PrintNumber("NWnd: ",NWnd)

//Animation settings
#declare ET=Linterp(0,ET0,1,ET1,clock); //Seconds from start of animation
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
#declare CloseupVertigo=array[7]     { 1,10  ,40  ,40  ,40  ,10  ,-1}
#declare H=array[7]                  {-4,1.3 ,2.2 ,1.2 ,1.4 ,3.4 ,-1} //Absolute magnitudes of satellites

#declare TargetTable=array[11][2] {{str2et("1986-01-24 01:00:00TDB"),0},
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

//Position and velocity of planet relative to spacecraft
#local V_pl=<0,0,0>;
#local R_pl=spkezr(str(SpiceTarget[0],0,0),ET,RefFrame,"LT+S",Spacecraft,V_pl);

//Position of Sun relative to spacecraft
light_source {
  spkezr("SUN",ET,RefFrame,"LT+S",Spacecraft)
  color rgb <1,1,1>
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
    #local MapName=concat("Data/",ShapeName,"Map.png")
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
  #local PlA=gdpool(concat("BODY",str(ShapeNum,0,0),"_RADII"),0);
  #local PlB=gdpool(concat("BODY",str(ShapeNum,0,0),"_RADII"),2);
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

#declare InPlaceUranus=object {
  UranusModel
  QuatTrans(pxform("IAU_URANUS",RefFrame,ET),R_pl)
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

#local I=1;
#declare AU=149597871;
#declare Target=0;
#while(I<=5)
  PrintNumber("Sat: ",SpiceTarget[I])
  #if((TargetTable[CloseupTargetTable[I]][0]>=ET) & TargetTable[CloseupTargetTable[I]+1][0]<ET)
    Target=I;
    //We are doing a closeup of this moon right now, get the full model
    PrintNumber(concat("Closeup of ",TargetName[I],
    #declare VxBEST=viewpoints(CloseupStartImg[I],CloseupNumImg[I],ET,str(TargetNumber[I],0,0),concat("IAU_",upcase(TargetName[I])))
    object {
      SphBody(TargetNumber[I],TargetName[I],TargetColor[I]) 
      texture {
        object {
          VxBEST
          SphTex(TargetNumber[I],TargetName[I],TargetColor[I])
          texture {pigment {color rgb 1} finish {ambient 1 diffuse 0}}
        }
      }
      QuatTrans(pxform(concat("IAU_",upcase(TargetName[I])),RefFrame,ET),spkezr(str(TargetNumber[I],0,0),ET,RefFrame,"LT+S",Spacecraft))
    }
    plane {
      QuatVectRotate(pxform("VG2_SCAN_PLATFORM",concat("IAU_",upcase(TargetName[I]),ckgetcov(CloseupStartImg[I],0)),z),0
      texture {
        object {VxBEST
          texture {pigment {color rgbf <1,1,1,1>}}
          texture {pigment {color rgb 1} finish {ambient 1 diffuse 0}}
        }
      }
      QuatTrans(pxform(concat("IAU_",upcase(TargetName[I])),RefFrame,ET),spkezr(str(TargetNumber[I],0,0),ET,RefFrame,"LT+S",Spacecraft))
    }  
  #else
    //Simplified model
  #local Sp=spkezr(Spacecraft,ET,RefFrame,"LT+S",str(TargetNumber[I],0,0))/AU;
  PrintVector("Sp: ",Sp)
  #local Ss=spkezr("SUN"     ,ET,RefFrame,"LT+S",str(TargetNumber[I],0,0))/AU;
  PrintVector("Ss: ",Ss)
  #local theta=vangle(Sp,Ss);
  PrintNumber("theta: ",degrees(theta))
  #local p=2/3*((1-theta/pi)*cos(theta)+1/pi*sin(theta));
  PrintNumber("p: ",p)
  #local m=H[I]+2.5*log(pow(vlength(Ss),2)*pow(vlength(Sp),2)/(p*pow(1,4)));
  PrintNumber("m: ",m)
  #local I=I+1;
#end

#local M=spkezr(str(TargetNumber[Target],0,0),ET,RefFrame,"LT+S",Spacecraft);

#declare CamSky=<0,0,1>;
#declare Vertigo=CloseupVertigo[Target];
#declare CamAngle=39/Vertigo;
#declare CamTan=tan(radians(CamAngle)/2);
#declare CamUp=1;
#declare CamRight=image_width/image_height;
#declare ObjPos=<-0.15,0,1>;
#declare ObjAxis=vnormalize(spkezr(str(TargetNumber[Target],0,0),ET,RefFrame,"LT+S",Spacecraft));
#declare ObjHoriz=vnormalize(vcross(ObjAxis,CamSky))*CamTan;
#declare ObjVert=vnormalize(vcross(ObjHoriz,ObjAxis))*CamTan*CamUp/CamRight;
#declare CamAxis=ObjAxis-ObjHoriz*ObjPos.x-ObjVert*ObjPos.y;
#declare CamHoriz=vnormalize(vcross(CamAxis,CamSky))*CamTan;
#declare CamVert=vnormalize(vcross(CamHoriz,CamAxis))*CamTan*CamUp/CamRight;
#declare ScPos=<0.55,0.8,1>;
#declare ScDist=45*Vertigo;
#declare CameraLoc=-ScDist*(ScPos.x*CamHoriz*CamRight*0.56+ScPos.y*CamVert*CamUp*0.725+ScPos.z*CamAxis);
#declare CameraLook=CameraLoc+CamAxis;

#local norm=<0,0,0>;
#local junk=trace(InPlaceUranus,CameraLoc,vnormalize(spkezr("SUN",ET,RefFrame,"LT+S",Spacecraft)),norm);
#if(vlength(norm) = 0) 
SunFlare(spkezr("SUN",ET,RefFrame,"LT+S",Spacecraft),CameraLoc,2)
#end

camera {
  up y*CamUp
  right x*CamRight
  sky CamSky
  angle CamAngle
  location CameraLoc 
  look_at CameraLook
}

#declare StarRatio=1440;
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

union {
  textHud(etcal(ETScan),<3.6,-4.65>,<1,1,1>,1,-1)
  textHud(etcal(ET),<3.6,-4.45>,<1,1,1>,1,-1)
  textHud(concat("Distance to ",TargetName[Target],": "),<-5.9,-4.45>,<1,1,1>,0,-1)
  textHudNumber(vlength(M)*1000,"m",<-2.9,-4.45>,<1,1,1>,-1)
  scale <0.175,0.175,Vertigo>/Vertigo
  no_shadow
  LocationLookAt(CameraLoc,CameraLook,CamSky)
}


