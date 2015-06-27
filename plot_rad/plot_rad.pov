#include "KwanMath.inc"
#include "Stars.inc"
#include "plot_rad.inc"
#include "loadct39.inc"
#include "LocLook.inc"

#version unofficial Megapov 1.22
#declare Line=floor(frame_number*(dimension_size(plot_rad,1)-1)/final_frame);

#declare CamSwitch=114/176;

sphere {
  <0,0,0>,1
  scale y*(1-1/298)
  pigment {
    image_map {
      png "EarthMap0.png"
      map_type spheroid
      flatness 1/298
    } 
    rotate y*(180-plot_rad[Line][2]) //Minus because left-handed
  }
  scale 6378.137
  finish {ambient 0}

}

camera {
  right x*16/9
  #declare rho=5-clock;
  #declare theta=-radians(clock*60);
  #declare Move1Y=2-2*clock;
  #declare Move1pos=<rho*sin(theta),Move1Y,-rho*cos(theta)>;
  #if(clock>CamSwitch)
    #declare r0=sqrt(rho*rho+Move1Y*Move1Y);
    #declare r1=12;
    #declare r=Linterp(CamSwitch,r0,1,r1,clock);
    #declare Move2pos=Linterp(CamSwitch,Move1pos,1,r*<0,1,0>,clock);
    #declare pos=r*Move2pos/vlength(Move2pos);
  #else
    #declare pos=Move1pos;
  #end
  location pos*6378.137
  look_at <0,0,0>
}
#declare month_length=array[12] {31,   28,   31,   30,   31,   30,   31,   31,   30,   31,   30,   31};
#declare month_name=array[12]   {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"}

union {
  text {
    ttf "lucon.ttf"
    
    concat("Altitude: ",str(vlength(<plot_rad[Line][4],plot_rad[Line][6],plot_rad[Line][5]>)-6378.137,5,0),"km") 0.0001, 0
    pigment {color rgb <1,1,1>}
    scale 0.25
    finish {ambient 1 diffuse 0 specular 0}
    translate <-7.75,-4,10> 
  }
  #declare yyyy=floor(plot_rad[Line][0]/1000);
  #declare ddd=plot_rad[Line][0]-yyyy*1000;
  #declare mm=0;
  #declare dd=ddd;
  #while(dd>month_length[mm]) 
     #declare dd=dd-month_length[mm];
     #declare mm=mm+1;
  #end
  #declare hh=floor(plot_rad[Line][1]/100);
  #declare nn=plot_rad[Line][1]-hh*100;
  text {
    ttf "lucon.ttf"
    
    concat(str(yyyy,4,0),"-",month_name[mm],"-",str(dd,-2,0)," ",str(hh,-2,0),":",str(nn,-2,0),"UTC") 0.0001, 0
    pigment {color rgb <1,1,1>}
    scale 0.25
    finish {ambient 1 diffuse 0 specular 0}
    translate <-7.75,-3.75,10> 
  }
  text {
    ttf "lucon.ttf"
    #if(plot_rad[Line][3]>0)
      #declare Color=floor(45*ln(plot_rad[Line][3]-36));
      #declare Color=<loadct39[Color][0],loadct39[Color][1],loadct39[Color][2]>/255;
      #declare Counts=str(plot_rad[Line][3],-3,0);
    #else
      #declare Counts="---";
      #declare Color=<0.5,0.5,0.5>;
    #end
    concat("Counts: ",Counts) 0.0001, 0
    pigment {color rgb Color}
    scale 0.25
    finish {ambient 1 diffuse 0 specular 0}
    translate <-7.75,-4.25,10> 
  }
  LocationLookAt(pos*6378.137,<0,0,0>,<0,1,0>)
}

#declare I=0;
#while(I<=Line)
  sphere {
    #if(I<Line)
      #if(plot_rad[I][3]>0)
        #declare Color=floor(45*ln(plot_rad[I][3]-36));
        #declare Color=<loadct39[Color][0],loadct39[Color][1],loadct39[Color][2]>/255;
        #declare Rad=100;
      #else
        #declare Color=<0.5,0.5,0.5>;
        #declare Rad=50;
      #end
    #else
      #declare Color=<1,1,1>;
      #declare Rad=150;
    #end

    <plot_rad[I][4],plot_rad[I][6],plot_rad[I][5]>, Rad
    finish {ambient 1 diffuse 0 specular 0}
    pigment {color rgb Color}
    no_shadow
  }
     
  #declare I=I+1;
#end

#declare SunVec=<plot_rad[Line][7],plot_rad[Line][9],plot_rad[Line][8]>; //Components are in correct order, this converts right-handed vector to left.

light_source {
  SunVec*150000000
  color <1,1,1>*2
}

intersection {
  sphere{
    0, 1
    scale y*(1-1/298)
    pigment{
      image_map {
        png "EarthLights0.png"
        map_type spheroid
        flatness 1/298
      }
    }
    scale 6378.138
    rotate y*(180-plot_rad[Line][2]) //Minus because left-handed
    finish {ambient 1 diffuse 0}
    no_shadow 
  }
  plane {
    SunVec,0
    pigment {color rgb <1,0,0>}
  }
}

object {Stars}

