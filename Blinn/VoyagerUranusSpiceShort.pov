#include "KwanMath.inc"
#include "LocLook.inc"
#include "hud.inc"
#include "textures.inc"

#version unofficial Megapov 1.22;

#furnsh "generic/generic.tm"
#furnsh "Voyager/vgr2.tm"

//#declare StartCal="1986-01-24 17:59:47TDB"; //Nominal closest approach
//#declare Cal0="1986-01-24 01:07:40TDB"; //Best fit to short Blinn start
//#declare Cal1="1986-01-25 17:05:03TDB"; //Best fit to short Blinn stop
#declare Cal0="1986-01-24 16:35:00TDB";
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
#declare SCQ=pxform("VG2_SCAN_PLATFORM","VG2_SC_BUS",ETScan);
PrintQuat("Scan Platform to Spacecraft: ",SCQ)

#declare Planet="799";
#declare Spacecraft="-32";

#include "SpiceQuat.inc"

//Spacecraft is at origin of coordinate system, scaled by a factor of 1000
//so as to avoid numerical issues

//Position and velocity of planet relative to spacecraft
#local V=<0,0,0>;
#local R_pl=spkezr(Planet,ET,"ECLIPJ2000","LT+S",Spacecraft,V);
#local V_pl=V;

//Position of Sun relative to spacecraft
light_source {
  spkezr("SUN",ET,"ECLIPJ2000","LT+S",Spacecraft)
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

#declare UranusModel=union {
  Spherical(799,"Uranus",<0,1,0>)
    union {
      //Ring data from Constantine Thomas' Site http://www.lancs.ac.uk/postgrad/thomasc1/render/planets/uranus.htm
      //Translated to POV by me
      //All rings are 100km wider than reality.
      //6 ring (innermost)
      disc {
        0,z,41910,41800
      }
      //5 ring: Inner radius 42,300 km; Outer radius 42,305 km.
      disc {
        0,z,42305,42200
      }
      //4 ring: Inner radius 42,600 km; Outer radius 42,610 km.
      disc {
        0,z,42610,42500
      }
      //a ring: Inner radius 44,800 km; Outer radius 44,807 km.
      disc {
        0,z,44807,44700
      }
      //b ring: Inner radius 45,700 km; Outer radius 45,708 km.
      disc {
        0,z,45708,45600
      }
      //eta ring: Inner radius 47,200 km; Outer radius 47,260 km.
      disc {
        0,z,47260,47100
      }
    //gamma ring: Inner radius 47,700 km; Outer radius 47,710 km.
      disc {
        0,z,47710,47600
      }
    //delta ring: Inner radius 48,300 km; Outer radius 48,310 km.
      disc {
        0,z,48310,48200
      }
    //epsilon ring (outermost): Inner radius 51,200 km; Outer radius 51,300 km
      disc {
        0,z,51300,51100
      }
      texture {RingTex}
    }
  }

#declare InPlaceUranus=object {
  UranusModel
  QuatTrans(pxform("IAU_URANUS","ECLIPJ2000",ET),R_pl)
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
//		rotate y*90
    LocationLookAt(SunPos,CamPos,y)
  }
#end  

#local Gray=<1,1,1>;
/*
object {Spherical(701,"Ariel",  Gray*0.39) QuatTrans(pxform("IAU_ARIEL",  "ECLIPJ2000",ET),spkezr("701",ET,"ECLIPJ2000","LT+S",Spacecraft))}
object {Spherical(702,"Umbriel",Gray*0.21) QuatTrans(pxform("IAU_UMBRIEL","ECLIPJ2000",ET),spkezr("702",ET,"ECLIPJ2000","LT+S",Spacecraft))}
object {Spherical(703,"Titania",Gray*0.27) QuatTrans(pxform("IAU_TITANIA","ECLIPJ2000",ET),spkezr("703",ET,"ECLIPJ2000","LT+S",Spacecraft))}
object {Spherical(704,"Oberon", Gray*0.23) QuatTrans(pxform("IAU_OBERON", "ECLIPJ2000",ET),spkezr("704",ET,"ECLIPJ2000","LT+S",Spacecraft))}
*/

sphere{0,800 pigment {color rgb <1,1,1>*0.39} finish {ambient 1 diffuse 0} QuatTrans(pxform("IAU_ARIEL",  "ECLIPJ2000",ET),spkezr("701",ET,"ECLIPJ2000","LT+S",Spacecraft))}
sphere{0,800 pigment {color rgb <1,1,1>*0.21} finish {ambient 1 diffuse 0} QuatTrans(pxform("IAU_UMBRIEL","ECLIPJ2000",ET),spkezr("702",ET,"ECLIPJ2000","LT+S",Spacecraft))}
sphere{0,800 pigment {color rgb <1,1,1>*0.27} finish {ambient 1 diffuse 0} QuatTrans(pxform("IAU_TITANIA","ECLIPJ2000",ET),spkezr("703",ET,"ECLIPJ2000","LT+S",Spacecraft))}
sphere{0,800 pigment {color rgb <1,1,1>*0.23} finish {ambient 1 diffuse 0} QuatTrans(pxform("IAU_OBERON", "ECLIPJ2000",ET),spkezr("704",ET,"ECLIPJ2000","LT+S",Spacecraft))}
//sphere{0,800 pigment {color rgb <1,1,1>*0.32} finish {ambient 1 diffuse 0} QuatTrans(pxform("IAU_MIRANDA","ECLIPJ2000",ET),spkezr("705",ET,"ECLIPJ2000","LT+S",Spacecraft))}

#declare H=array[5] {1.3,2.2,1.2,1.4,3.4}
#local I=0;
#local AU=149597871;
#while(I<dimension_size(H,1))
  PrintNumber("Sat: ",701+I)
  #local Sp=spkezr(Spacecraft,ET,"ECLIPJ2000","LT+S",str(701+I,0,0))/AU;
  PrintVector("Sp: ",Sp)
  #local Ss=spkezr("SUN"     ,ET,"ECLIPJ2000","LT+S",str(701+I,0,0))/AU;
  PrintVector("Ss: ",Ss)
  #local theta=vangle(Sp,Ss);
  PrintNumber("theta: ",degrees(theta))
  #local p=2/3*((1-theta/pi)*cos(theta)+1/pi*sin(theta));
  PrintNumber("p: ",p)
  #local m=H[I]+2.5*log(pow(vlength(Ss),2)*pow(vlength(Sp),2)/(p*pow(1,4)));
  PrintNumber("m: ",m)
  #local I=I+1;
#end

#declare CamSky=<0,0,1>;
#declare Vertigo=10;
#declare CamAngle=39/Vertigo;
#declare CamTan=tan(radians(CamAngle)/2);
#declare CamObj="705";
#declare CamUp=1;
#declare CamRight=image_width/image_height;
#declare ObjPos=<-0.15,0,1>;
#declare ObjAxis=vnormalize(spkezr(CamObj,ET,"ECLIPJ2000","LT+S",Spacecraft));
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
#local junk=trace(InPlaceUranus,CameraLoc,vnormalize(spkezr("SUN",ET,"ECLIPJ2000","LT+S",Spacecraft)),norm);
PrintVector("junk: ",junk)
PrintVector("norm: ",norm)
#if(vlength(norm) = 0) 
SunFlare(spkezr("SUN",ET,"ECLIPJ2000","LT+S",Spacecraft),CameraLoc,5)
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
  QuatTrans(pxform("J2000","ECLIPJ2000",ET),<0,0,0>)
}

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


//VMBEST - highest resolution shots of Miranda
#declare VMBESTFirstShot=5006;
#declare VMBESTNShots=8;

#macro viewpoints(FirstShot,NShots,ET,Center,Frame)
  #local I=0;
  union {
  #while(I<NShots & ckgetcov(I+FirstShot,0)<ET)
    viewpoint(ckgetcov(I+FirstShot,0),Center,Frame)
    #local I=I+1;
  #end
  }
#end

#declare VMBEST=viewpoints(VMBESTFirstShot,VMBESTNShots,ET,"705","IAU_MIRANDA")

//I'm ready for my closeup...
object {
  SphBody(705,"Miranda",Gray*0.32) 
  texture {
    object {VMBEST
      SphTex(705,"Miranda",Gray*0.32)
      texture {pigment {color rgb 1} finish {ambient 1 diffuse 0}}
    }
  }
  QuatTrans(pxform("IAU_MIRANDA","ECLIPJ2000",ET),spkezr("705",ET,"ECLIPJ2000","LT+S",Spacecraft))
}
plane {
  QuatVectRotate(pxform("VG2_SCAN_PLATFORM","IAU_MIRANDA",ckgetcov(VMBESTFirstShot,0)),z),0
  texture {
    object {VMBEST
      texture {pigment {color rgbf <1,1,1,1>}}
      texture {pigment {color rgb 1} finish {ambient 1 diffuse 0}}
    }
  }
  QuatTrans(pxform("IAU_MIRANDA","ECLIPJ2000",ET),spkezr("705",ET,"ECLIPJ2000","LT+S",Spacecraft))
}  
cylinder {spkezr("705",ET,"ECLIPJ2000","LT+S",Spacecraft),spkezr("799",ET,"ECLIPJ2000","LT+S",Spacecraft),10 pigment {color rgb <0,1,1>}}

#include "Voyager.inc"
#local Z=QuatVectRotate(pxform("VG2_SCAN_PLATFORM","ECLIPJ2000",ETScan),z);
#local M=spkezr(CamObj,ET,"ECLIPJ2000","LT+S",Spacecraft);
PrintNumber("Offpoint: ",degrees(vangle(Z,M)))
union {
  object{VoyagerQSpice(SCQ)}
  union {

    cylinder {0, x,  0.02 pigment {color rgb x}} 
    cylinder {0,-x,  0.02 pigment {color rgb <1,1,1>-x}} 
    cylinder {0, y,  0.02 pigment {color rgb y}} 
    cylinder {0,-y,  0.02 pigment {color rgb <1,1,1>-y}} 
    cylinder {0, z*5,0.02 pigment {color rgb z}}
    cylinder {0,-z,  0.02 pigment {color rgb <1,1,1>-z}}
    pigment {color rgbf <0.5,0.5,1,0.5>}
    QuatTrans(SCQ,SPCenter)
  } 
//  union {
//    cylinder {0, x*5,0.5 pigment {color rgb x}} 
//    cylinder {0,-x*5,0.5 pigment {color rgb <1,1,1>-x}} 
//    cylinder {0, y*5,0.5 pigment {color rgb y}} 
//    cylinder {0,-y*5,0.5 pigment {color rgb <1,1,1>-y}} 
//    cylinder {0, z*5,0.5 pigment {color rgb z}}
//    cylinder {0,-z*5,0.5 pigment {color rgb <1,1,1>-z}}
//  } 
  PrintQuat("VG2_SC_BUS: ",pxform("VG2_SC_BUS","ECLIPJ2000",ET))
  QuatTrans(pxform("VG2_SC_BUS","ECLIPJ2000",ET),<0,0,0>)
}

union {
  textHud(etcal(ETScan),<3.9,-4.75>,<1,1,1>,0,-1)
  textHud(etcal(ET),<3.9,-4.55>,<1,1,1>,0,-1)
  textHud("Distance to Miranda: ",<-3.9,-4.75>,<1,1,1>,0,-1)
  textHudNumber(vlength(M)*1000,"m",<-2.9,-4.75>,<1,1,1>,-1)
  scale <0.175,0.175,Vertigo>/Vertigo
  no_shadow
  LocationLookAt(CameraLoc,CameraLook,CamSky)
}


