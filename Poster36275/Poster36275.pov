#version unofficial Megapov 1.22;

#macro linterp(x0,y0,x1,y1,X) 
  #local T=(X-x0)/(x1-x0);
  (y0*(1-T)+y1*T)
#end

#macro blinterp(x0,y0,x1,y1,X) 
  #if(X<x0)
    #local result=(y0);
  #else #if(X>x1)
    #local result=(y1);
  #else
    #local result=(linterp(x0,y0,x1,y1,X));
  #end #end
  (result)
#end

#macro PrintNumber(Label,Number)
  #debug concat(Label,str(Number,0,6),"\n")
#end

#declare f=1/298.257223563;
#declare a=6378137;

#declare PhaseName=array[6] {"Stage 1","Stage 2","Observe","Reentry","Parachute","Coast"};
#declare PhaseStart=array[6] {0,        12,      102,      519,621,-1};
#declare PhaseStop=array[6] {5.5,      45.2,    475.3,      524,873.9,-1};
//For printing
#declare SkyColor=<255,255,255>/255;
#declare SpaceColor=<97,162,207>/255;
#declare PhaseColor=array[6] {<1,0,0>,<1,0,0>,   <1,1,1>,  <1,1,0>, <0,1,0>,<0,0,1>};
//For displays
//#declare SpaceColor=<0,0,0>/255;
//#declare SkyColor=<97,162,207>/255;
//#declare PhaseColor=array[6] {<1,0,0>,<1,0,0>,   <1,1,1>,  <1,1,0>, <0,1,0>,<0,0,1>};

#include "36275_radar_data3.inc"

global_settings{
  right_handed
}

#macro l_lla2xyz(lat,lon,alt) 
  #local lla=<radians(lat),radians(lon),alt/a>;
  #local xyz=lla2xyz(lla,f)*a;
  #local xyz=<xyz.x,xyz.z,xyz.y>;
  (xyz)
#end


#declare ApogeeI=2725;
#declare BoostI=443;
#declare ReentryI=5180;
#declare Lon0=Data[ApogeeI][3];
#declare Lat0=Data[ApogeeI][2];
#declare Boostxyz=l_lla2xyz(Data[BoostI][2],Data[BoostI][3]-Lon0,Data[BoostI][1]);
#declare SubBoostxyz=l_lla2xyz(Data[BoostI][2],Data[BoostI][3]-Lon0,0);
#declare Apogeexyz=l_lla2xyz(Data[ApogeeI][2],Data[ApogeeI][3]-Lon0,Data[ApogeeI][1]);
#declare SubApogeexyz=l_lla2xyz(Data[ApogeeI][2],Data[ApogeeI][3]-Lon0,0);
#declare Reentryxyz=l_lla2xyz(Data[ReentryI][2],Data[ReentryI][3]-Lon0,Data[ReentryI][1]);
#declare SubReentryxyz=l_lla2xyz(Data[ReentryI][2],Data[ReentryI][3]-Lon0,0);
#declare LP1xyz=(Boostxyz+SubBoostxyz)/2;
#declare LP2xyz=(Apogeexyz+SubApogeexyz)/2;
#declare LP3xyz=(Reentryxyz+SubReentryxyz)/2;

#declare Angle=array[3] {4,5.5,4}

#declare Sky=<cos(radians(Lat0)),0,sin(radians(Lat0))>;

#declare T=clock*Data[dimension_size(Data,1)-1][0];
PrintNumber("T: ",T)

#if(max(T,1)<Data[BoostI][0])
  #declare Ang=Angle[0];
  #declare LPxyz=LP1xyz;
#else #if(T<Data[BoostI][0]+10)
  #declare Ang=linterp(Data[BoostI][0],Angle[0],Data[BoostI][0]+10,Angle[1],T);
  #declare LPxyz=linterp(Data[BoostI][0],LP1xyz,Data[BoostI][0]+10,LP2xyz,T);
#else #if(T<Data[ReentryI][0]-10)
  #declare Ang=Angle[1];
  #declare LPxyz=LP2xyz;
#else #if(T<Data[ReentryI][0])
  #declare Ang=linterp(Data[ReentryI][0]-10,Angle[1],Data[ReentryI][0],Angle[2],T);
  #declare LPxyz=linterp(Data[ReentryI][0]-10,LP2xyz,Data[ReentryI][0],LP3xyz,T);
#else
  #declare Ang=Angle[2];
  #declare LPxyz=LP3xyz;
#end
#end
#end
#end

//#declare LPxyz=<0,0,0>;

#declare PathR=1000*Ang*500/(Angle[1]*image_width);

#macro Terrier(Fade)
  union {
    cylinder {
      <-10,0,0>,<-5,0,0>,1
      pigment {color rgbf <1,1,1,Fade>}
    }
    triangle {
      <-10,3,0>,<-7,0,0>,<-10,-3,0>
      pigment {color rgbf linterp(0,<1,0,0,0>,1,<1,1,1,1>,Fade)}
    }
    triangle {
      <-10,0,3>,<-7,0,0>,<-10,0,-3>
      pigment {color rgbf linterp(0,<1,0,0,0>,1,<1,1,1,1>,Fade)}
    }
  }    
#end

#macro BlackBrant(Fade)
  union {
    cylinder {
      <-5,0,0>,<0,0,0>,1
      pigment {color rgbf linterp(0,<0.1,0.1,0.1,0>,1,<1,1,1,1>,Fade)}
    }
    triangle {
      <-5,3,0>,<-2,0,0>,<-5,-3,0>
      pigment {color rgbf linterp(0,<1,0,0,0>,1,<1,1,1,1>,Fade)}
    }
    triangle {
      <-5,0,3>,<-2,0,0>,<-5,0,-3>
      pigment {color rgbf linterp(0,<1,0,0,0>,1,<1,1,1,1>,Fade)}
    }
  }    
#end

#macro Payload(Fade)
  union {
    cone {
      <0,0,0>,1,<1,0,0>,1.2
    }
    cone {
      <1,0,0>,1.2,<4,0,0>,1.2
    }
    cone {
      <4,0,0>,1.2,<5,0,0>,1.0
    }
    cone {
      <5,0,0>,1,<8,0,0>,1.0
    }
    pigment {color rgbf linterp(0,<0.5,0.5,0.5,0>,1,<1,1,1,1>,Fade)}
  }    
#end

#macro NoseCone(Fade)
  union {
    cone {
      <8,0,0>,1,<10,0,0>,0
      pigment {color rgbf linterp(0,<0.5,0.5,0.5,0>,1,<1,1,1,1>,Fade)}
    }    
  }
#end

#macro Parachute(Fade)
  union {
    difference {
      sphere {
        <20,0,0>,4
      }
      plane {
        x,20
      }
      pigment {color rgb <1,0.5,0>}
    }
    cylinder {
      <10,0,0>,<20,0,-3.8>,0.2
      pigment {color rgb <1,1,1>}
    }
    cylinder {
      <10,0,0>,<20,0, 3.8>,0.2
      pigment {color rgb <1,1,1>}
    }
    translate -2*x
  }
#end

//Draw rocket track
union {
#declare I=0;
#declare TTick=10;
#declare TBigTick=60;
#declare DeltaTTick=10;
#declare DeltaTBigTick=60;
//#while(max(T,1)>Data[I][0])
#while(I<dimension_size(Data,1)-1)
  #declare LPxyz0=l_lla2xyz(Data[I  ][2],Data[I  ][3]-Lon0,Data[I  ][1]);
  #declare LPxyz1=l_lla2xyz(Data[I+1][2],Data[I+1][3]-Lon0,Data[I+1][1]);
  union {
    #if(vlength(LPxyz0-LPxyz1)>0)
      cylinder {
        LPxyz0,LPxyz1,PathR
      }
      sphere {
        LPxyz1,PathR
      }
    #end
    #if(Data[I][0]>TTick)
      #if(Data[I][0]>TBigTick)
        sphere {
          LPxyz0,PathR*2
        }
        #declare TBigTick=TBigTick+DeltaTBigTick;
      #else
        sphere {
          LPxyz0,PathR*1.5
        }
      #end
      #declare TTick=TTick+DeltaTTick;
    #end
    #declare J=0;
    #declare Phase=5;
    #while(J<5)
      #if(Data[I][0]>=PhaseStart[J])
        #if(Data[I][0]<PhaseStop[J])
          #declare Phase=J;
        #end
      #end
      #declare J=J+1;
    #end
    pigment {color rgb PhaseColor[Phase]}
  }
  #declare I=I+1;
#end
  translate -LPxyz
  no_shadow
}

#declare T=clock*Data[dimension_size(Data,1)-1][0];

/*
sphere {
  LPxyzz,PathR*2
  pigment {color rgb <1,1,0>}
  translate -LPxyz
}
*/
#macro Vehicle(T)
#local I=0;
#while(Data[I][0]<T)
  #local I=I+1;
#end

#debug concat("T: ",str(T,0,6),"\n")
#debug concat("I: ",str(I,0,0),"\n")

#declare LPxyz0=l_lla2xyz(Data[I  ][2],Data[I  ][3]-Data[0][3],Data[I  ][1]);
#declare LPxyz1=l_lla2xyz(Data[I+1][2],Data[I+1][3]-Data[0][3],Data[I+1][1]);
#declare LPxyzz=linterp(Data[I][0],LPxyz0,Data[I+1][0],LPxyz1,T);
union {
#if(T<PhaseStart[1])
  union {
    Terrier(blinterp(6.2,0,12,1,T))
    translate -x*10*blinterp(6.2,0,12,1,T)
  }
#end
#if(T<80)
  union {
    BlackBrant(blinterp(70,0,80,1,T))
    translate -x*10*blinterp(70,0,80,1,T)
  }
#end
  union {
    Payload(0)
  }
#if(T<85)
  union {
    NoseCone(blinterp(75,0,85,1,T))
    translate x*10*blinterp(75,0,85,1,T)
  }
#end
 #if(T>PhaseStart[4]) Parachute(0) #end
  no_shadow 
  translate x*blinterp(0,10,80,-5,T)
  translate x*blinterp(PhaseStart[4],0,PhaseStop[4],5,T)
  scale PathR*2
  rotate -y*35
  rotate -y*blinterp(80,0,110,180-35,T)
  rotate y*(360*10+180-35)*blinterp(PhaseStop[2],0,PhaseStart[4],1,T)
  translate LPxyzz-LPxyz+y*10000
}
#end

Vehicle(T)
Vehicle(37)
union {Vehicle(800) translate z*3000}

#macro EarthMap(Level,J0,J1,K0,K1)
    image_map{
      tile_map{
        6*pow(2,Level),3*pow(2,Level)
#declare J=J0;
#while(J<=J1)
#declare K=K0;
#while(K<=K1)
#declare TileFn=concat("EarthMap.200404/",str(Level,1,0),"/",str(J,-3,0),"x",str(K,-3,0),".png");
#debug concat(TileFn,"\n")
        [K J png TileFn]
#declare K=K+1;
#end
#declare J=J+1;
#end
      }
      map_type spheroid
      flatness f
    }
#end

union {
  sphere {
    0,6378137
    scale <1,1,(1-f)>
  } 
  #include "N32W107.mesh2"
  #include "N32W106.mesh2"
  #include "N33W107.mesh2"
  #include "N33W106.mesh2"
/*
  texture {
    pigment {
      color rgb <1,0,1>
    }
  } */
  texture {
    finish { brilliance 1 ambient 0.5}
    pigment{
      EarthMap(6,59,61,70,79)      
//      EarthMap(1,0,5,0,11)
      rotate z*90
      rotate y*90
      rotate z*90
    }
    scale 6378137
  }
  rotate -z*Lon0
  translate -LPxyz
} 


#declare Loc=y*1000*1000-Sky*100000;
#declare ConeAxis=LPxyz+Loc;

#declare HorizonC=vlength(ConeAxis);
PrintNumber("HorizonC: ",HorizonC)
#declare HorizonA=6378137;
PrintNumber("HorizonA: ",HorizonA)
#declare HorizonB=sqrt(HorizonC*HorizonC-HorizonA*HorizonA);
PrintNumber("HorizonB: ",HorizonB)
#declare HorizonE=HorizonA*HorizonA/HorizonC;
PrintNumber("HorizonE: ",HorizonE)
#declare HorizonD=HorizonA*HorizonB/HorizonC;
PrintNumber("HorizonD: ",HorizonD)
PrintNumber("Check: d^2+e^2=a^2: ",sqrt(HorizonD*HorizonD+HorizonE*HorizonE))

cone {
  0,0,vnormalize(ConeAxis)*2*HorizonE/HorizonA,2*HorizonD/HorizonA
  no_shadow
  pigment {
    onion
    color_map { 
    [0 color rgb <0,0,0>]
    [1/2 color rgb <1,0,1>]
    [1/2 color rgb SkyColor]
#declare I=0;
#while(I<10)
    [(6378+I*10)/6378/2 color rgb linterp(1,SkyColor,0,SpaceColor,exp(-I))]
#declare I=I+1;
#end
    [(6478)/6378/2 color rgb SpaceColor]
    }
    scale 1.998
  }
  finish {brilliance 0 ambient 1 diffuse 0}
  scale 6378137
  translate -LPxyz
}


camera {
  up y
  right x*image_width/image_height
  sky Sky
  angle Ang
  location Loc
  look_at <0,0,0>
}

light_source {
  <20,20,0>*1000000*1000
  color rgb <1,1,1>
  shadowless
}

background {
  color rgb <0,0.5,1>
}

