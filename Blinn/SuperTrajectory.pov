#furnsh "generic/generic.tm"
//#furnsh "Voyager/vgr1.tm"
//#furnsh "Voyager/spk/voyager_1.ST+1991_a54418u.merged.bsp"
#furnsh "Voyager/vgr.tm"
#include "SpiceQuat.inc"
#include "KwanMath.inc"

#declare au=150000000; //Approximate km in 1 AU
#declare TrajFrame="ECLIPB1950";
#macro DrawTrajectory(body,et0,et1,dt,r,mark_r,mark_texture)
  #if(et1>et0)
    #local et=et0;
    #local x0=spkezr(body,et,TrajFrame,"NONE","0")/au;
    #local et=et+dt;
    union {
      #while(et<et1)
        #local x1=spkezr(body,et,TrajFrame,"NONE","0")/au;
        sphere {
          x0,r*pixsize*vlength(x0-CamLoc)
        }
        cylinder {
          x0,x1,r*pixsize*vlength(x0-CamLoc)
        }
        #local x0=x1;
        #local et=et+dt;
      #end
      #if(mark_r>0)
        #local x1=spkezr(body,et1,TrajFrame,"NONE","0")/au;
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

//Lower precision orbit for planets not actually visited
#macro DrawCircle(a,l0,ldot,et,r,mark_r,mark_texture)
  union {
    torus {
      a,r
      rotate x*90
    }
    PrintNumber("mark_r: ",mark_r)
    #if(mark_r>0)
      #local T=et/(86400*36525);
      #local l=radians(l0+ldot*T);
      sphere {
        <cos(l),sin(l),0>*a,mark_r
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

#declare et0=str2et("1972-07-01 00:00:00 TDB"); //Official start of project
#declare et0_vgr1=str2et("1977-09-06 00:00:00 TDB");
#declare et0_vgr2=str2et("1977-08-21 00:00:00 TDB");
#declare et1=str2et("1990-01-01 00:00:00 TDB"); //Official start of Voyager Interstellar Mission
#declare et=et0+clock*(et1-et0);

#declare CamAngle=45.9;
#declare CamUpDenom=2.96;
PrintNumber("ImWidth:     ",image_width)
PrintNumber("ImHeight:    ",image_height)
PrintNumber("CamAngle:    ",CamAngle)
#declare CamLat=radians(25.1);
PrintNumber("CamLat(deg): ",degrees(CamLat))
#declare CamLon=radians(-35.56);
PrintNumber("CamLon(deg): ",degrees(CamLon))
//#declare CamLook=<0.28,-0.15,0>;
#declare CamLook=spkezr("-32",max(et,et0_vgr2),TrajFrame,"NONE","0")/au;
#declare CamLook=<CamLook.x,CamLook.y,0>; //Force into equatorial plane
PrintVector("CamLook:     ",CamLook)
#declare CamDist=3.655;
PrintNumber("CamDist:     ",CamDist)
#declare etExtraZ0=str2et("1973-07-01 00:00:00 TDB");
#declare etExtraZ1=str2et("1975-07-01 00:00:00 TDB");
#declare ExtraZ=BLinterp(etExtraZ0,100,etExtraZ1,0,et);
#declare CamLoc=CamLook+<cos(CamLat)*cos(CamLon),cos(CamLat)*sin(CamLon),sin(CamLat)>*CamDist+ExtraZ*z;
PrintVector("CamLoc:      ",CamLoc)
#declare CamSky=z; //Use the Z axis of ECLIPB1950 as the sky, but express it in J2000 so we can use J2000 coords for sky and planets
PrintVector("CamSky:      ",CamSky)

#declare pixsize=radians(CamAngle/image_width);

#declare StarRatio=1000*45/CamAngle;
#declare LimitMag=6;
PrintNumber("LimitMag:    ",LimitMag)
//#declare Gamma=0;
#include "StarsRight.inc"
#declare StarFrame="J2000"
object {
  Stars
  QuatTrans(pxform(StarFrame,TrajFrame,0),CamLoc)
}

#debug concat(etcal(et),"\n")
#declare TrajRad=0.75;
DrawTrajectory("-31",et0_vgr1     ,et,86400,TrajRad,0,0)
DrawTrajectory("-32",et0_vgr2     ,et,86400,TrajRad,0,0)
#declare MarkRad=0.02;
         //a            L,             Ldot
DrawTrajectory("10"  ,et-  365.26*86400,et,86400,TrajRad,MarkRad*2,<1,1,0>) //Sun
DrawTrajectory( "1"  ,et-  365.26*86400,et,86400,TrajRad,MarkRad,<1,1,1>)   //Mercury
DrawTrajectory( "2"  ,et-  365.26*86400,et,86400,TrajRad,MarkRad,<1,1,0.5>) //Venus
DrawTrajectory( "3"  ,et-  365.26*86400,et,86400,TrajRad,MarkRad,<0,0.5,1>)      //Mercury
DrawTrajectory( "4"  ,et-  686   *86400,et,86400,TrajRad,MarkRad,<1,0.5,0.5>)      //Venus
DrawTrajectory( "3"  ,et-  365.26*86400,et,86400,TrajRad,MarkRad,<0,0.5,1>)      //Earth
DrawTrajectory( "4"  ,et-  686.98*86400,et,86400,TrajRad,MarkRad,<1,0.5,0.5>)      //Mars
DrawTrajectory( "5"  ,et- 4332.82*86400,et,86400*12,TrajRad,MarkRad,<1,0.5,0>) //Jupiter
DrawTrajectory( "6"  ,et-10755.70*86400,et,86400*30,TrajRad,MarkRad,<1,1,0>)
DrawTrajectory( "7"  ,et-30687.15*86400,et,86400*84,TrajRad,MarkRad,<0.5,1,0.5>)
DrawTrajectory( "8"  ,et-60190.03*86400,et,86400*16.5,TrajRad,MarkRad,<0.5,0.5,1>)
DrawTrajectory( "9"  ,et-90560   *86400,et,86400*24.8,TrajRad,MarkRad,<0.5,0.5,0.5>)

camera {
  right -x*4/CamUpDenom
  up y
  sky CamSky
  location CamLoc
  look_at CamLook
  angle CamAngle
}
      

