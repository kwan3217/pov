#include "KwanMath.inc"
#include "LocLook.inc"
#include "hud.inc"
#include "textures.inc"
#include "StarsRight.inc"

#version unofficial Megapov 1.22;

#furnsh "generic/generic.tm"
#furnsh "Voyager/vgr2.tm"

#declare RubberClockCal=array[12] {
"1986-Jan-24 02:55:39TDB",
"1986-Jan-24 05:12:27TDB",
"1986-Jan-24 08:41:14TDB",
"1986-Jan-24 10:36:25TDB",

"1986-Jan-24 10:58:01TDB",
"1986-Jan-24 12:38:48TDB",
"1986-Jan-24 13:22:00TDB",
"1986-Jan-24 14:48:24TDB",

"1986-Jan-24 15:24:23TDB",
"1986-Jan-24 17:48:23TDB",
"1986-Jan-24 19:07:34TDB",
"1986-Jan-24 22:06:49TDB"
}

#declare I=0;
#declare RubberClockET=array[dimension_size(RubberClockCal,1)];
#while(I<dimension_size(RubberClockCal,1))
  #declare RubberClockET[I]=str2et(RubberClockCal[I]);
  #declare I=I+1;
#end

#declare RubberClockOrigFrame=array[dimension_size(RubberClockCal,1)] {
 832,1197,1652,1767
2643,2781,3617,3848
4560,4741,6261,6727
}

#declare OrigFrame=Linterp(0,RubberClockOrigFrame[0],1,RubberClockOrigFrame[dimension_size(RubberClockCal,1)-1],clock);
#declare ET=Tableterp(RubberClockOrigFrame,RubberClockET,OrigFrame);

#declare NWnd=ckcov("Voyager/ck/vg2_ura_version1_type1_iss_sedr.bc",-32100,"INTERVAL",0,"TDB",10000);
PrintNumber("NWnd: ",NWnd)

PrintNumber(concat("This ET: ",etcal(ET)," "),ET)

#declare I=0;
#while(ckgetcov(I,0)<ET) 
  #declare I=I+1;
#end
#declare ETScan=ckgetcov(I-1,0);
PrintNumber("ETScanI: ",I)
PrintNumber(etcal(ETScan),ETScan)
#declare SCQ=pxform("VG2_SCAN_PLATFORM","VG2_SC_BUS",ETScan);
//#declare SCQ=pxform("VG2_AZ_EL","VG2_SC_BUS",ETScan);
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
#macro Spherical(ShapeNum,ShapeName,Color)  
  #local PlA=gdpool(concat("BODY",str(ShapeNum,0,0),"_RADII"),0);
  #local PlB=gdpool(concat("BODY",str(ShapeNum,0,0),"_RADII"),2);
  sphere {
    <0,0,0>,1
    scale <1,1,PlB/PlA>
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
      }
    #else
      #debug concat("Map ",MapName," Not Found, using base color\n")
      pigment {color Color}
    #end
    finish {ambient 0 #ifdef(Diffuse) diffuse Diffuse #end brilliance Brilliance}
    scale PlA
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
object {Spherical(705,"Miranda",Gray*0.32) QuatTrans(pxform("IAU_MIRANDA","ECLIPJ2000",ET),spkezr("705",ET,"ECLIPJ2000","LT+S",Spacecraft))}
*/

sphere{0,800 pigment {color rgb <1,1,1>*0.39} finish {ambient 1 diffuse 0} QuatTrans(pxform("IAU_ARIEL",  "ECLIPJ2000",ET),spkezr("701",ET,"ECLIPJ2000","LT+S",Spacecraft))}
sphere{0,800 pigment {color rgb <1,1,1>*0.21} finish {ambient 1 diffuse 0} QuatTrans(pxform("IAU_UMBRIEL","ECLIPJ2000",ET),spkezr("702",ET,"ECLIPJ2000","LT+S",Spacecraft))}
sphere{0,800 pigment {color rgb <1,1,1>*0.27} finish {ambient 1 diffuse 0} QuatTrans(pxform("IAU_TITANIA","ECLIPJ2000",ET),spkezr("703",ET,"ECLIPJ2000","LT+S",Spacecraft))}
sphere{0,800 pigment {color rgb <1,1,1>*0.23} finish {ambient 1 diffuse 0} QuatTrans(pxform("IAU_OBERON", "ECLIPJ2000",ET),spkezr("704",ET,"ECLIPJ2000","LT+S",Spacecraft))}
sphere{0,800 pigment {color rgb <1,1,1>*0.32} finish {ambient 1 diffuse 0} QuatTrans(pxform("IAU_MIRANDA","ECLIPJ2000",ET),spkezr("705",ET,"ECLIPJ2000","LT+S",Spacecraft))}

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
#declare CamAngle=39;
#declare CamTan=tan(radians(CamAngle)/2);
#declare CamObj="799";
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
#declare ScDist=45;
#declare CameraLoc=-ScDist*(ScPos.x*CamHoriz*CamRight*0.56+ScPos.y*CamVert*CamUp*0.725+ScPos.z*CamAxis);
#declare CameraLook=CameraLoc+CamAxis;

#local norm=<0,0,0>;
#local junk=trace(InPlaceUranus,CameraLoc,vnormalize(spkezr("SUN",ET,"ECLIPJ2000","LT+S",Spacecraft)),norm);
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
object {
  Stars
  QuatTrans(pxform("J2000","ECLIPJ2000",ET),<0,0,0>)
}

#include "Voyager.inc"
union {
  object{VoyagerQSpice(SCQ)}
  union {
    cylinder {0, x,0.1 pigment {color rgb x}} 
    cylinder {0,-x,0.1 pigment {color rgb <1,1,1>-x}} 
    cylinder {0, y,0.1 pigment {color rgb y}} 
    cylinder {0,-y,0.1 pigment {color rgb <1,1,1>-y}} 
    cylinder {0,z*5,0.1 pigment {color rgb z}}
    cylinder {0,-z,0.1 pigment {color rgb <1,1,1>-z}}
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
