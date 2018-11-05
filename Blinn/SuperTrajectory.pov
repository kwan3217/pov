#furnsh "generic/generic.tm"
#furnsh "Voyager/vgr2.tm"
#include "SpiceQuat.inc"

#declare au=150000000; //Approximate km in 1 AU

#macro DrawTrajectory(body,et0,et1,dt,r,mark_r,mark_texture)
  #local et=et0;
  #local x0=spkezr(body,et,"ECLIPB1950","NONE","0")/au;
  #local et=et+dt;
  union {
    #while(et<et1)
      #local x1=spkezr(body,et,"ECLIPB1950","NONE","0")/au;
      sphere {
        x0,r
      }
      cylinder {
        x0,x1,r
      }
      #local x0=x1;
      #local et=et+dt;
    #end
    #if(mark_r>0)
      #local x1=spkezr(body,et1,"ECLIPB1950","NONE","0")/au;
      sphere {
        x1,mark_r
        texture {mark_texture}
      }
    #end
    finish {ambient 1 diffuse 0 specular 0}
    pigment {color rgb <1,1,1>}
  }
#end

#declare CamAngle=45;
#declare StarRatio=1440*45/CamAngle;
#include "StarsRight.inc"
object {
  Stars
  QuatTrans(pxform("J2000","ECLIPB1950",0),<0,0,0>)
}

#declare et0_vgr1=str2et("1977-09-06 00:00:00 TDB");
#declare et0_vgr2=str2et("1977-08-21 00:00:00 TDB");
#declare et1=str2et("1990-01-01 00:00:00 TDB");
DrawTrajectory("-32",et0_vgr2,et1,86400,0.05,0,0)
cylinder {
  0,x*10,0.1
  pigment {color rgb x}
  finish {ambient 1 diffuse 0 specular 0}
}

cylinder {
  0,y*10,0.1
  pigment {color rgb y}
  finish {ambient 1 diffuse 0 specular 0}
}

cylinder {
  0,z*10,0.1
  pigment {color rgb z}
  finish {ambient 1 diffuse 0 specular 0}
}

camera {
  right -x*image_width/image_height
  up y
  sky z
  location <-10,-10,10>*5
  look_at <0,0,0>
  angle CamAngle
}
      

