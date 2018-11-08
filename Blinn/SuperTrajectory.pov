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

//In the following, "frame" means frame from original movie, 
//https://www.youtube.com/watch?v=wNf9BPTjvYo. This one has a marked frame rate of 29.97f/s and is 2172 frames long, giving a total length of 72.43s

//From original movie:
//Frame 0-93 is title sequence
//Frame 94 is high above Solar system (about 115AU), immediately begins move down
//Frame 504, latitude stops changing
//Frame 508, distance stops changing
//Frame 708, Voyager 2 Launch 1977-08-20T14:29:45
//Frame 712, Voyager 1 Launch 1977-09-05T12:56
//Frame 862, Voyager 1 at Jupiter, 1979-03-05
//Frame 896, Voyager 2 at Jupiter, 1979-07-09T22:29:00
//Frame 1032, Voyager 1 at Saturn, 1980-11-12
//Frame 1111, Voyager 2 at Saturn, 1981-08-25T03:24:05
//Frame 1553, Voyager 2 at Uranus, 1986-01-24T17:59:47
//Frame 1910, Voyager 2 at Neptune, 1989-08-25T03:56:36
//Frame 1983, start moving back up
//Frame 2171, end of movie

//The movie does not seem to have a rubber clock. Event times are in 
//https://docs.google.com/spreadsheets/d/1F3CC-07yCPUcTB1RzHT03rYjxF8WNLfDVGk-truUkG8/edit?usp=sharing

#declare Frame0=94;
#declare Frame1=708;
#declare Frame2=1910;
#declare Frame3=2171;
#declare et0=str2et("1971-07-03 18:16:09 UTC");
#declare et1=str2et("1977-08-20 14:29:45 UTC");
#declare et2=str2et("1989-08-25 03:56:36 UTC");
#declare et3=str2et("1992-03-31 09:18:17 UTC");
#declare Frame=Linterp(0,Frame0,1,Frame3,clock);
#declare et=Linterp(0,et0,1,et3,clock);
#declare et0=str2et("1972-07-01 00:00:00 TDB"); //Official start of project
#declare et0_vgr1=str2et("1977-09-06 00:00:00 TDB");
#declare et0_vgr2=str2et("1977-08-21 00:00:00 TDB");
#declare et1=str2et("1990-01-01 00:00:00 TDB"); //Official start of Voyager Interstellar Mission

#macro Choreograph(frames,values,spds,accs,frame1)
  #local pos=values[0];
  #local vel=pos*0;
  #local frame=0;
  #local seg=0;
  #while(frame<frame1)
    //Check if we have ticked over into the next segment
    #if(frame>frames[seg])
      #local seg=seg+1;
    #end
    #local frame=frame+1;
  #end
#end

#declare CamAngle=45.9;
#declare CamUpDenom=2.96;
PrintNumber("ImWidth:     ",image_width)
PrintNumber("ImHeight:    ",image_height)
PrintNumber("CamAngle:    ",CamAngle)
#declare vg2_vel=<0,0,0>;
#declare vg2_pos=spkezr("-32",max(et,et0_vgr2),TrajFrame,"NONE","0",vg2_vel);
#declare CamLatFrame=array[4] {94,504,1983,2171}
#declare CamLatValue=array[4] {89,25.1,25.1,89}
#declare CamLatMaxSpd=array[4] {1,1,1,1}
#declare CamLatMaxAcc=array[4] {0.1,0.1,0.1,0.1}
#declare CamLat=radians(25.1);
PrintNumber("CamLat(deg): ",degrees(CamLat))
#declare CamLon=atan2(-vg2_vel.y,-vg2_vel.x);
//#declare CamLon=radians(-35.56);
PrintNumber("CamLon(deg): ",degrees(CamLon))
//#declare CamLook=<0.28,-0.15,0>;
#declare CamLook=spkezr("-32",max(et,et0_vgr2),TrajFrame,"NONE","0")/au;
#declare CamLook=<CamLook.x,CamLook.y,0>; //Force into equatorial plane
PrintVector("CamLook:     ",CamLook)
#declare CamDist=3.655;
PrintNumber("CamDist:     ",CamDist)
#declare etExtraZ0=str2et("1973-07-01 00:00:00 TDB");
#declare etExtraZ1=str2et("1975-07-01 00:00:00 TDB");
#declare ExtraZ=ASDR(94,504,1983,2171,100,0,Frame);
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
      

