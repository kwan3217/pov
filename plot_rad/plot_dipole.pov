#include "KwanMath.inc"
#include "Stars.inc"
#include "plot_rad.inc"
#include "loadct39.inc"
#include "LocLook.inc"
#include "pieTorus.inc"

#version unofficial Megapov 1.22;


#declare AnimRate=24;
#declare AnimLength=180;  //Animation is exactly three minutes
#declare AnimFrames=AnimRate*AnimLength;

#declare CamSwitchSec=116;
#declare CamSwitch=CamSwitchSec/AnimLength;
#declare SatSwitch=30;

#declare sec=clock*AnimLength; 

PrintNumber("Sec: ",sec)

#declare FieldFadeIn=ASDR(-1,-1,15,17,0,1,sec);
#declare FrameFadeIn=ASDR(15,17,28,30,0,1,sec);
#declare DonutFadeIn=ASDR(31,33,56,58,0,1,sec);
#declare RhoBoardFadeIn=ASDR(17,19,56,58,0,1,sec);
#declare GlobeSplit=ASDR(10,12,18,20,0,1.2,sec);
#declare Sat=ASDR(SatSwitch,SatSwitch,9999,9999,0,1,sec);
#declare RhoDotFadeIn=ASDR(SatSwitch,SatSwitch,56,58,0,1,sec);
#declare BeltStart=138.4;
#declare RhoHudFadeIn=ASDR(56,58,BeltStart-5,BeltStart-3,0,1,sec);
#declare RhoHudHinge =ASDR(68,70,9999,9999,0,180,sec);
#declare RhoDotFadeIn=RhoDotFadeIn+ASDR(BeltStart-12,BeltStart-10,BeltStart+10,BeltStart+12,0,1,sec);
#declare RhoBoardFadeIn=RhoBoardFadeIn+ASDR(BeltStart-12,BeltStart-10,BeltStart+10,BeltStart+12,0,1,sec);
#declare OrbitRadFadeIn=ASDR(-1,-1,BeltStart,BeltStart+2,0,1,sec);
#declare SceneFade=ASDR(0,0.5,AnimLength-0.5,AnimLength,0,1,sec);
PrintNumber("SceneFade:",SceneFade)
PrintNumber("RhoBoardFadeIn: ",RhoBoardFadeIn)
PrintNumber("RhoHudFadeIn: ",RhoHudFadeIn)

#declare n_lines=dimension_size(plot_rad,1);
#declare Line=floor(Linterp(SatSwitch,0,AnimLength,n_lines-1,sec));
#declare SunVec=<plot_rad[max(Line,0)][7],plot_rad[max(Line,0)][9],plot_rad[max(Line,0)][8]>; //Components are in correct order, this converts right-handed vector to left.
#declare RotationRateDq=plot_rad[1][2]-plot_rad[0][2];
#declare RotationRateDt=((AnimLength-SatSwitch)/n_lines);
#declare RotationRate=RotationRateDq/RotationRateDt;

PrintNumber("RotationRate: ",RotationRate)

#if(Line>0)
  #declare thetaE=plot_rad[Line][2];  //GMST in degrees
#else
  #declare thetaE=plot_rad[0][2]+(sec-SatSwitch)*RotationRate;
#end

#if(GlobeSplit<0) #declare GlobeSplit=0; #end

#declare Globe=union {
  sphere {
    <0,0,0>,1
    scale <1,1-1/298,1>
    pigment {
      image_map {
        png "EarthMap0.png"
        map_type spheroid
        flatness 1/298
      } 
      rotate y*(180-thetaE) //Minus because left-handed
    }
    scale 6378.137
    finish {ambient 0}
  }
  sphere{
    0, 1
    scale <1,1-1/298,1>
    pigment{
      image_map {
        png "EarthLights0.png"
        map_type spheroid
        flatness 1/298
      }
    }
    scale 6378.138
    rotate y*(180-thetaE) //Minus because left-handed
    finish {ambient 1 diffuse 0}
    no_shadow 
    clipped_by { 
      plane {
        SunVec,0
      } 
    }
  }
}


#if(FieldFadeIn>0)
#declare Field=union {
  #declare B=0;
  #declare n_B=8;
  #while(B<n_B)
    union {
      #declare B=B+1;
      #declare L=1;
      #declare n_L=7;
      #while(L<=n_L)
        torus {
          L/2,0.01
          rotate x*90
          translate x*L/2
        }
        #declare L=L+1;
      #end
      rotate y*B*360/n_B
      
    }
  #end
  scale 6378.137
  rotate -z*(90-80.02)
  rotate -y*(-72.21)
  translate <-399.763,215.360,332.834>
  rotate y*(-thetaE) //Minus because left-handed
  no_shadow
}

object {
  Field
  pigment {rgbt <0,0.5,1,1-FieldFadeIn>}
}

#end

#if(FrameFadeIn>0)
#declare Frame=union {
  cylinder {
    -y*100,y*100,0.01
    pigment {color rgbt <1,0,0,1-FrameFadeIn>}
  }
  #declare B=0;
  #declare n_B=8;
  #while(B<n_B)
    cylinder {
      -x*7,x*7,0.01
      pigment {color rgbt <0,1,0,1-FrameFadeIn>}
      rotate y*B*180/n_B
    }
    #declare B=B+1;
  #end
  #declare L=1;
  #declare n_L=7;
  #while(L<=n_L)
    torus {
      L,0.01
      pigment {color rgbt <0,1,0,1-FrameFadeIn>}
    }
    #declare L=L+1;
  #end
  scale 6378.137
  rotate -z*(90-80.02)
  rotate -y*(-72.21)
  translate <-399.763,215.360,332.834>
  rotate y*(-thetaE) //Minus because left-handed
  no_shadow
}

object {
  Frame
  pigment {rgbt <0,0.5,1,1-FieldFadeIn>}
}

#end
#if(GlobeSplit>0) 
  intersection {
    object {Globe}
    plane {y,0 pigment {color rgb <1,0,0>}}
    sphere {0,6000
      pigment {color rgb <1,0,0>}
      inverse
    }
  }
  difference {
    object{Globe}
    plane{y,0}
    translate y*6378.137*GlobeSplit
  }
  union {
    box {
      <-0.1,0,-0.1>,<0.1,0.6,0.1>
      pigment {color rgb <1,0,0>}
    }
    box {
      <-0.1,0,-0.1>,<0.1,-0.6,0.1>
      pigment {color rgb 1/3}
    }
    scale 6378.137
    rotate -z*(90-80.02)
    rotate -y*(-72.21)
    translate <-399.763,215.360,332.834>
    rotate y*(-thetaE) //Minus because left-handed
  }
#else 
  object {
    Globe
  }
#end

camera {
  right x*16/9
  #declare rho=5-clock;
  #declare theta=radians(clock*60);
  #declare Move1Y=2-2*clock;
  #declare Move1pos=<rho*sin(theta),Move1Y,-rho*cos(theta)>;
  #if(clock>CamSwitch)
    #declare r0=sqrt(rho*rho+Move1Y*Move1Y);
    #declare r1=12;
    #declare r=Linterp(CamSwitch,r0,1,r1,clock);
    #declare Move2pos=Linterp(CamSwitch,Move1pos,2,r*<0,1,0>,clock);
    #declare pos=r*Move2pos/vlength(Move2pos);
  #else
    #declare pos=Move1pos;
  #end
  location pos*6378.137
  look_at <0,0,0>
}

#if(SceneFade<1)
  sphere {
    pos*6378.137,0.0001 hollow
    pigment {color rgbf <1,1,1,SceneFade>}
    finish {ambient 0 diffuse 0 specular 0}
  }
#end


/*
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

*/

#declare I=0;
#while(I<=Line)
  #if(I<Line)
    #if(plot_rad[I][3]>38.1)
      #declare Color=floor(45*ln(plot_rad[I][3]-38));
      #if(Color<0) #declare Color=0; #end
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
  #if(OrbitRadFadeIn>0) 
  sphere {
    <plot_rad[I][4],plot_rad[I][6],plot_rad[I][5]>, Rad
    finish {ambient 1 diffuse 0 specular 0}
    pigment {color rgbt <Color.x,Color.y,Color.z,(1-OrbitRadFadeIn)>}
    no_shadow
  }
  #end
  #if(OrbitRadFadeIn<1)
    #if(I=Line)
      sphere {
        <plot_rad[I][4],plot_rad[I][6],plot_rad[I][5]>, 150
        finish {ambient 1 diffuse 0 specular 0}
        pigment {color rgb <1,1,1>}
        no_shadow
      }
    #else
      sphere {
        <plot_rad[I][4],plot_rad[I][6],plot_rad[I][5]>, 50
        finish {ambient 1 diffuse 0 specular 0}
        pigment {color rgb <0.5,0.5,0.5>}
        no_shadow
      }
    #end
  #end
  #if(RhoDotFadeIn>0) 
    sphere {
      <plot_rad[I][13],plot_rad[I][12],0>, Rad/2
      pigment {color rgbt <Color.x,Color.y,Color.z,(1-RhoDotFadeIn)>}
      finish {ambient 1 diffuse 0 specular 0}
      no_shadow
//      rotate y*(thetaE-72)
      rotate -z*(90-80.02)
      rotate -y*(-72.21)
      translate <-399.763,215.360,332.834>
      rotate y*(-thetaE) //Minus because left-handed
    }
  #end
  #declare I=I+1;
#end

#if(RhoHudFadeIn>0)
  union {
    cylinder {
      -z,z,6378.137
      pigment {color rgbt <0,1,0,(1-RhoHudFadeIn)>}
      finish {ambient 1 diffuse 0 specular 0}
      rotate -z*(90-80.02)
      rotate -y*(-72.21)
      translate -<-399.763,215.360,332.834>
      rotate y*(-72.21)
      rotate z*(90-80.02)
    }
    #declare I=0;
    #while(I<=Line)
      #if(I<Line)
        #if(plot_rad[I][3]>38.1)
          #declare Color=floor(45*ln(plot_rad[I][3]-38));
          #if(Color<0) #declare Color=0; #end
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
      sphere {
        <plot_rad[I][13],plot_rad[I][12],0>, Rad*2
        pigment {color rgbt <Color.x,Color.y,Color.z,(1-RhoHudFadeIn)>}
        finish {ambient 1 diffuse 0 specular 0}
      }
      #if(RhoHudHinge>0)
        sphere {
          <plot_rad[I][13],plot_rad[I][12],0>, Rad*2
          pigment {color rgbt <Color.x,Color.y,Color.z,(1-RhoHudFadeIn)>}
          finish {ambient 1 diffuse 0 specular 0}
          rotate y*RhoHudHinge
        }
      #end
      #declare I=I+1;
    #end
    union {
      #declare L=1; 
      cylinder {
        <0,-4,0>,<0,2,0>,0.02
        pigment {color rgbt <1,0,0,(1-RhoHudFadeIn)>}
        finish {ambient 1 diffuse 0 specular 0}
      }
      #while(L<=7)
        cylinder {
          <L,-4,0>,<L,2,0>,0.02
        }   
        #if(RhoHudHinge>0)
          cylinder {
            <L,-4,0>,<L,2,0>,0.02
            rotate y*RhoHudHinge
          }   
        #end
        #declare L=L+1;
      #end
      #declare Z=-4;
      #while(Z<=2)
        cylinder {
          <0,Z,0>,<7,Z,0>,0.02
          #if(Z=0) 
            pigment {color rgbt <0,1,0,(1-RhoHudFadeIn)>} 
            finish {ambient 1 diffuse 0 specular 0}
          #end
        }
        #if(RhoHudHinge>0)
          cylinder {
            <0,Z,0>,<7,Z,0>,0.02
            rotate y*RhoHudHinge
            #if(Z=0) 
              pigment {color rgbt <0,1,0,(1-RhoHudFadeIn)>} 
              finish {ambient 1 diffuse 0 specular 0}
            #end
          }
        #end
        #declare Z=Z+1;
      #end
      pigment {color rgbt <0,0,1,(1-RhoHudFadeIn)>}
      finish {ambient 1 diffuse 0 specular 0}
      scale 6378.137
    }
    no_shadow
    scale 0.5/6378.137
    translate <5.2,-2.9,10>
    LocationLookAt(pos*6378.137,<0,0,0>,<0,1,0>)
  }
#end

#if(RhoBoardFadeIn>0) 
  #declare L=1; 
  union {
    cylinder {
      <0,-4,0>,<0,4,0>,0.01
      pigment {color rgbt <1,0,0,(1-RhoBoardFadeIn)>}
    }
    #while(L<=7)
      cylinder {
        <L,-4,0>,<L,4,0>,0.01
      }   
      #declare L=L+1;
    #end
    #declare Z=-4;
    #while(Z<=4)
      cylinder {
        <0,Z,0>,<7,Z,0>,0.01
        #if(Z=0) pigment {color rgbt <0,1,0,(1-RhoBoardFadeIn)>} #end
      }
      #declare Z=Z+1;
    #end
    pigment {color rgbt <0,0,1,(1-RhoBoardFadeIn)>}
    scale 6378.137
//    rotate y*(thetaE-72)
    rotate -z*(90-80.02)
    rotate -y*(-72.21)
    translate <-399.763,215.360,332.834>
    rotate y*(-thetaE) //Minus because left-handed
  }
#end

#if(DonutFadeIn>0) 
  torus {
    plot_rad[Line][13] 50
    translate y*plot_rad[Line][12]
    #if(plot_rad[Line][3]>38.1)
      #declare Color=floor(45*ln(plot_rad[Line][3]-38));
      #if(Color<0) #declare Color=0; #end
      #declare Color=<loadct39[Color][0],loadct39[Color][1],loadct39[Color][2],255*(1-DonutFadeIn)>/255;
    #else 
      #declare Color=<0.5,0.5,0.5,(1-DonutFadeIn)>;
    #end
    pigment {color rgbt Color}
    rotate -z*(90-80.02)
    rotate -y*(-72.21)
    translate <-399.763,215.360,332.834>
    rotate y*(-thetaE) //Minus because left-handed
    finish {ambient 1 diffuse 0 specular 0}
    no_shadow
  }
#end

#if(BeltStart<sec) 
  union {
    #declare I=0;
    #while(I<=Line)
      #declare IP1=min(I+1,Line);
      #declare IM1=max(I-1,0);
      #if(/*abs(plot_rad[I][3]-plot_rad[IM1][3])<10 & abs(plot_rad[I][3]-plot_rad[IP1][3])<10 &*/ plot_rad[I][3]>38.1)
        #declare ColorIdx=floor(45*ln(plot_rad[I][3]-38));
        #if(ColorIdx<0) #declare ColorIdx=0; #end
        #if(ColorIdx>60)
          #declare Color=<loadct39[ColorIdx][0],loadct39[ColorIdx][1],loadct39[ColorIdx][2]>/255;
          #declare Rad=100;
          #declare Size=(sec-BeltStart)*RotationRate-(255-ColorIdx);
          #if(Size>0)
            union {
              pieTorus(plot_rad[I][13],Rad/2,Size)
              translate y*plot_rad[I][12]
              scale <1,1,-1>
              pigment {color rgb <Color.x,Color.y,Color.z>}
            }
          #end
        #end
      #end
      #declare I=I+3;
    #end
    rotate -z*(90-80.02)
    rotate -y*(-72.21)
    translate <-399.763,215.360,332.834>
    rotate y*(-thetaE) //Minus because left-handed
  }
#end

light_source {
  SunVec*150000000
  color <1,1,1>*2
  shadowless
}

object {Stars}

