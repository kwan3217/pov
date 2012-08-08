#include "KwanMath.inc"
#include "LocLook.inc"
#include "MarsAtmCospar2.inc"
#include "hud.inc"
#include "textures.inc"
#include "Jettison.inc"

//Data from od137 entry simulation. This is the 
//only one with a matching C kernel.
#furnsh "generic.tm"
#furnsh "relay.tm"
#furnsh "msl_od137.tm"

#declare fps=24;
#declare DT=1/fps;
#declare TTT=frame_number*DT;
//                 12345678901234567890123
#declare StartUTC="2012-08-06 05:10:47.417UTC";
#declare StartET=str2et(StartUTC);
PrintNumber("StartET: ",StartET)
#declare h0=val(substr(StartUTC,12,2));
#declare m0=val(substr(StartUTC,15,2));
#declare s0=val(substr(StartUTC,18,6));
#declare StartUTCSOD=h0*3600+m0*60+s0;
#declare h=floor((TTT+StartUTCSOD)/3600);
#declare m=floor(((TTT+StartUTCSOD)-h*3600)/60);
#declare s=(TTT+StartUTCSOD)-h*3600-m*60;
#declare Tebm0=238+14/24; //Time of first entry balance mass jettison
#declare dt_ebm=2;        //Time between entry balance mass jettisons
#declare Tinflate=256+21/24; //Time of start of parachute inflation
#declare Theatshield=277+6/24; //Time of heatshield jettison
#declare Tsep=374+17/24;  //Time of backshell jettison
#declare Tland=426+23/24;       //Time of touchdown
#declare Tflyaway=Tland+1;      //Time of descent stage flyaway start
#declare Tlastatt=431+9/24;     //Time of last attitude in CK kernel - after this, use a fixed attitude

#include "SpiceQuat.inc"

#declare MarsR=gdpool("BODY499_RADII",0)*1e3; //Values in kernel uses km...
#declare MarsGM=gdpool("BODY499_GM",0)*1e9;   //we use meters internally
#declare MarsJ2=gdpool("BODY499_J2",0);

#macro R(TT)  //Position vector in Mars centered, Mars body fixed, in meters
  (1000*spkezr("MSL",StartET+TT,"IAU_MARS","NONE","499")) 
#end
#macro RI(TT)  //Position vector in Mars centered, Mars body fixed, in meters
  (1000*spkezr("MSL",StartET+TT,"MARSIAU","NONE","499")) 
#end
#macro V(TT)  //Velocity vector in Mars centered, Mars body fixed, in m/s
  #local vel=<0,0,0>;
  #local junk=spkezr("MSL",StartET+TT,"IAU_MARS","NONE","499",vel);
  (1000*vel) 
#end
#macro VI(TT)  //Velocity vector in Mars centered inertial, in m/s
  #local vel=<0,0,0>;
  #local junk=spkezr("MSL",StartET+TT,"MARSIAU","NONE","499",vel);
  (1000*vel) 
#end
#macro AI(TT) //Total inertial acceleration
  #local xi  =TT;
  #local xim1=xi-DT;
  #local xip1=xi+DT;
  #local fxi  =VI(xi);
  #local fxim1=VI(xim1);
  #local fxip1=VI(xip1);

  #local AA=fxim1*(2*xi-xi  -xip1)/((xim1-xi)*(xim1-xip1));
  #local BB=fxi  *(2*xi-xim1-xip1)/((xi-xim1)*(xi  -xip1));
  #local CC=fxip1*(2*xi-xi  -xim1)/((xip1-xi)*(xip1-xim1));
  (AA+BB+CC)
#end
#macro J2(R) //J2 gravity acceleration
  #local r=vlength(R);
  #local coef=-3*MarsJ2*MarsGM*MarsR*MarsR/pow(2*r,5);
  (coef*<R.x*(1-5*R.z*R.z/(r*r)),
         R.y*(1-5*R.z*R.z/(r*r)),
         R.z*(3-5*R.z*R.z/(r*r))>)
#end
#macro TwoBody(R) //Two-body gravity acceleration
  (-MarsGM*R/pow(vlength(R),3))
#end
#macro Ang(TT)     //Non-gravitational acceleration in inertial frame
  (AI(TT)-TwoBody(RI(TT))-J2(RI(TT)))
#end
#macro A(TT)       //Non-gravitational acceleration in rotating frame
  #local QQ=pxform("MARSIAU","IAU_MARS",StartET+TT);
  (QuatVectRotate(QQ,Ang(TT)))
#end

#macro S(TT) (1000*spkezr("SUN",StartET+TT,"IAU_MARS", "LT+S","MSL")) #end
#macro E(TT) (1000*spkezr("399",StartET+TT,"IAU_MARS","XLT+S","MSL")) #end
#macro MEX(TT) (1000*spkezr("-41",StartET+TT,"IAU_MARS","XLT+S","MSL")) #end //Mars Express
#macro MRO(TT) (1000*spkezr("-74",StartET+TT,"IAU_MARS","XLT+S","MSL")) #end //Mars Recon Orbiter
#macro ODY(TT) (1000*spkezr("-53",StartET+TT,"IAU_MARS","XLT+S","MSL")) #end //Mars Odyssey
#macro LT(TT) (vlength(E(TT))/299792458) #end
#declare hlt=floor((TTT+StartUTCSOD+LT(TTT))/3600);
#declare mlt=floor(((TTT+StartUTCSOD+LT(TTT))-hlt*3600)/60);
#declare slt=(TTT+StartUTCSOD+LT(TTT))-hlt*3600-mlt*60;
#macro Q(TT) (pxform("MSL_ROVER","IAU_MARS",StartET+min(TT,Tlastatt))) #end
#macro alt(TT)(vlength(R(TT))-3396000) #end
#macro rho(TT)
  (MarsAtmRho(alt(TT))) 
#end
#macro csound(TT)
  (MarsAtmCsound(alt(TT))) 
#end
//Tangential vector, parallel to Vrel           
#macro T(TT)
  (vnormalize(V(TT)))
#end

//Side vector, perpendicular to both L and T, so in local horizon plane
#macro W(TT)
  (vnormalize(vcross(L(TT),T(TT))))
#end

//Normal vector, perpendicular to both T and W, towards local vertical
#macro N(TT)
  (vnormalize(vcross(W(TT),T(TT))))
#end

//Heading vector, perpendicular to both W and L, in horizon plane, towards T
#macro H(TT)
  (vnormalize(vcross(W(TT),L(TT))))
#end

#macro Alpha(TT) 
  #local Z=QuatVectRotate(Q(TT),z);
  (vangle(Z,V(TT)))
#end

#macro bank(TT) 
  #local X=QuatVectRotate(Q(TT),x);
  #local Xp=X-vdot(X,H(TT))*H(TT);
  (atan2(vdot(Xp,W(TT)),vdot(Xp,L(TT))))
#end

//Local vertical vector. In this model, we use a spherical reference surface 3396km in radius, so
//local vertical is parallel to planetocentric position
#macro L(TT)
  (vnormalize(R(TT)))
#end

//Local east vector, perpendicular to both local vertical (and therefore in local horizontal plane)
//and Mars north pole           
#macro Ea(TT)
  (vnormalize(vcross(z,R(TT))))
#end

//Local north vector, perpendicular to both local vertical (and therefore in local horizontal plane)
//and local east vector
#macro No(TT)
  (vnormalize(vcross(R(TT),Ea(TT))))
#end

#macro CenterWorld(TT)
  translate -R(min(TT,Tland))
#end

#declare GaleMesh=mesh2 {
  #include "gale.inc"
  regular_faces {
    640,640
  }
  CenterWorld(TTT)
}

#macro agl(TT)
  #local aglNormal=<0,0,0>;
  #local RR=R(TT)-R(TTT);
  #local aglPos=trace(GaleMesh,RR,-L(TT),aglNormal);
  #if(vlength(aglNormal)>0) 
    #local Result=(vlength(aglPos-RR));
  #else
    #local aglPos=trace(GaleMesh,RR,L(TT),aglNormal);
    #local Result=(-vlength(aglPos-RR));
    #if(vlength(aglNormal)>0)
    #else
      #local Result=alt(TT);
    #end
  #end
  (Result)
#end

#declare RappelTime=max(0,(18.6-agl(TTT))/0.75);
PrintNumber("RappelTime: ",RappelTime)
#declare RappelOfs=0.863;
#declare MaxRappelDist=7.0;
#declare RappelDist=min(MaxRappelDist,7.5/MaxRappelDist*RappelTime);
PrintNumber("RappelDist: ",RappelDist)

//Non-gravitational acceleration in drag frame. Components are parallel to T,W,N in that order
#macro AD(I)
  (<vdot(T(I),A(I)),vdot(W(I),A(I)),vdot(N(I),A(I))>)
#end

#declare Mach=vlength(V(TTT))/csound(TTT);
#declare Cheat=0.224e-10;
#declare mheat=0.879;
#declare nheat=4.22;
#declare MaxHeat=260;
#macro MDynHeat(TT) 
  (Cheat*pow(vlength(V(TT)),nheat)*pow(rho(TT),mheat))
#end
#declare DynHeat=MDynHeat(TTT);
#declare DynScorch=0;
#declare DynScorchI=0;
#declare DynScorchT=DynScorchI/fps;
#while(DynScorchT<=TTT)
  #declare DynScorch=DynScorch+MDynHeat(DynScorchT)*DT;
  #declare DynScorchI=DynScorchI+1;
  #declare DynScorchT=DynScorchI/fps;
#end
#declare Heat=DynHeat/MaxHeat;
#declare Scorch=DynScorch/8000;
#declare EntryAlpha=-Alpha(TTT);
#include "EntryFlame5.inc"
#include "MSLAeroshell2.inc"

#if(TTT<(Tebm0-2))
cylinder {
  <0,0,0>,V(TTT)/fps,0.1
  pigment {color rgbt <1,1,1,BLinterp(Tebm0-7,1,Tebm0-2,0,TTT)>}
  no_shadow
}
#end

#declare Vv=vdot(L(TTT),V(TTT));
#declare Fpa=asin(Vv/vlength(V(TTT)));
#declare Ltot=sqrt(AD(TTT).y*AD(TTT).y+AD(TTT).z*AD(TTT).z);
#declare Dtot=AD(TTT).x;

#declare LiftAxis=BLinterp(1,N(TTT),2,vnormalize(AD(TTT).y*W(TTT)+AD(TTT).z*N(TTT)),abs(Dtot));

light_source {
  vnormalize(S(TTT))*1e6
  color rgb <1,1,1>
}

#macro Visible(V)
  #local Normal=<0,0,0>;
  #local Junk=trace(GaleMesh,<0,0,0>,vnormalize(V),Normal);
  (vlength(Normal)=0)
#end

#declare EarthVecColor=<1,0,1>*Visible(E(TTT));
#declare MEXVecColor=<0,1,1>*Linterp(0,0.5,1,1,Visible(MEX(TTT)));
#declare MROVecColor=<1,0.5,0>*Linterp(0,0.5,1,1,Visible(MRO(TTT)));
#declare ODYVecColor=<1,1,0>*Linterp(0,0.5,1,1,Visible(ODY(TTT)));

#declare MarsContrast=0;
#declare MarsBrilliance=0.5;
#declare MarsDiffuse=2;
#declare MarsColor=<1,0.3,0>;

#declare MarsPigment=pigment { 
  average
  pigment_map {
    [1.0 image_map {png "Mars2k.png" map_type spherical interpolate 2}]
    [MarsContrast color rgb MarsColor]
  }
  rotate x*90
  scale <1,-1,1>
}

#declare GalePigment=pigment {
  average
  pigment_map {
    [1.0 image_map {tile_map {4 16[3 8 "MarsGale.png"]} map_type spherical}]
    [MarsContrast color rgb MarsColor]
  }
  rotate x*90
  scale <1,-1,1>
}

#declare MtSharpPigment=pigment {
  average
  pigment_map {
    [1 
    image_map {
      jpeg "PIA15687.jpg"
      interpolate 2
      once
    }
    ][0 color rgbf <1,1,1,1>]
    
  }
  translate <-0.5,-0.5,-0.5>
  scale <1,-1,1>
  rotate y*90
  rotate -x*90
  scale <1,-1,1>
#declare MtSharpLat= -5.414;
#declare MtSharpLon=137.815;
  rotate -y*MtSharpLat
  rotate z*MtSharpLon
  scale 0.058834
}    

object {
  GaleMesh
  texture {
    GalePigment CenterWorld(TTT)
    finish {brilliance MarsBrilliance diffuse MarsDiffuse ambient 0}
  }
  texture {
    MtSharpPigment scale 3396000 CenterWorld(TTT)
    finish {brilliance MarsBrilliance diffuse 1 ambient 0}
  }
  texture {
    pigment {
      Tiles_Ptrn()
      pigment_map {
        #if(TTT<Tland)
          #declare GridWidth=BLinterp(400,0.02,500,0.0,agl(TTT));
        #else
          #declare GridWidth=BLinterp(Tland+2,0.02,Tland+3,0,TTT);
        #end
        PrintNumber("GridWidth: ",GridWidth)
        [GridWidth color rgb <0,0,0> ]
        [GridWidth color rgbf<1,1,1,1>]
      }
      rotate x*94 scale 5
      CenterWorld(TTT)
    }
    finish {brilliance MarsBrilliance diffuse MarsDiffuse ambient 0}
  }
}
                     
#declare SphereR=vlength(R(Tland))-agl(Tland);

sphere {
  0,SphereR-1000
  pigment {MarsPigment}
  finish {brilliance MarsBrilliance diffuse MarsDiffuse ambient 0}
  CenterWorld(TTT)
} 

global_settings{max_trace_level 10}
/*
cylinder {
  0,vnormalize(E(TTT))*4,0.1
  pigment {color rgb EarthVecColor}
  no_shadow
}

cylinder {
  0,vnormalize(ODY(TTT))*4,0.1
  pigment {color rgb ODYVecColor}
  no_shadow
}

cylinder {
  0,vnormalize(MRO(TTT))*4,0.1
  pigment {color rgb MROVecColor}
  no_shadow
}

cylinder {
  0,vnormalize(MEX(TTT))*4,0.1
  pigment {color rgb MEXVecColor}
  no_shadow
}

cylinder {
  0,A(TTT)/9.80665,0.1
  pigment {color rgb <1,1,0>}
    no_shadow
}

*/
#if(TTT<Tland)
cone {
  L(Tland)*10000,0,L(Tland)*20000,2000
  pigment {color rgb <1,1,1>}
  translate R(Tland)
  CenterWorld(TTT)
  no_shadow
}
#end
/*
#if(TTT<Tebm0)
  union {
    cone {
      No(Tland)*100,0,No(Tland)*1000,100
    }
    cone {
      -No(Tland)*100,0,-No(Tland)*1000,100
    }
    cone {
      Ea(Tland)*100,0,Ea(Tland)*1000,100
    }
    cone {
      -Ea(Tland)*100,0,-Ea(Tland)*1000,100
    }
    pigment {color rgb x}
    translate R(Tland)
    CenterWorld(TTT)
    no_shadow
  }
  union {
    #local EllI=0;
    #while(EllI<=360)
      #local NN0=vnormalize(No(Tland)*3500*cos(radians(EllI+5))+Ea(Tland)*10000*sin(radians(EllI+5))+R(Tland))*SphereR;
      #local NN1=vnormalize(No(Tland)*3500*cos(radians(EllI+6))+Ea(Tland)*10000*sin(radians(EllI+6))+R(Tland))*SphereR;
      cylinder {
        NN0,NN1,500
      }
      sphere {
        NN1,500
      }
      #local EllI=EllI+1;
    #end
    pigment {color rgb <1,1,1>}
    CenterWorld(TTT)
    no_shadow
  }
#end
*/


#include "MSLChute5.inc"

#if((TTT>(Tinflate-5))*(TTT<Tsep))
  object {
    #local Z=QuatVectRotate(Q(TTT),-z*0.95);
    #local X=QuatVectRotate(Q(TTT),x);
    MSLChute(TTT) 
    LocationLookAt(Z,A(TTT)+Z,X)
  }
#end

#local I=0;
#while(I<6)
  #declare EbmAngle=-(mod(I,2)*2-1)*(floor(I/2)*10+10);
  #declare Tebm=Tebm0+(5-I)*dt_ebm;
  #if(TTT<(Tebm+30))
  PrintNumber("EbmAngle: ",EbmAngle)
  Jettison(
    object {EntryBalanceMass(BLinterp(Tebm-0.25,0,Tebm,0.25,TTT)) translate -z rotate z*EbmAngle scale <1,1,-1>},
    2.25*<cos(radians(EbmAngle)),sin(radians(EbmAngle)),0>,
    1*0.1/25, //Ballistic coefficient
    <cos(radians(8.5))*cos(radians(EbmAngle)),cos(radians(8.5))*sin(radians(EbmAngle)),sin(radians(8.5))>,<0,-60,0>,Tebm,TTT
  )
  #end
  #local I=I+1;
#end

#if(Mach>6 & DynHeat>MaxHeat*0.01)
  object {EntryFlame scale <1,1,-1> QuatTrans(Q(TTT),<0,0,0>)} 
#end

#include "MSLDescentStage.inc"
#include "MSLRover.inc"
#include "DescentInt.inc"
#declare RoverCf=BLinterp(5,1,6,0,RappelTime);
#declare RoverCa=BLinterp(5,1,6,0,RappelTime);
#declare RoverAf=BLinterp(7,1,7.5,0,RappelTime);
#if(TTT<Tflyaway)
object {
  MSLDescentStage(Throttle*(NMLE>4),Throttle)
  scale <1,1,-1>
  QuatTrans(Q(TTT),R(TTT))
  CenterWorld(TTT)
}
#else
#include "Flyaway.inc"
  Flyaway(TTT)
#end
object {
  MSLRover(RoverCf,RoverCa,RoverAf) translate -z*RappelDist
  scale <1,1,-1>
  QuatTrans(Q(min(TTT,Tland)),<0,0,0>)
}

#if(TTT<Tsep+5)
#debug "Backshell\n"
Jettison(object {Backshell scale <1,1,-1>},-z*1,1*(pi*10*10)/(349+50),<0,0,0>,<0,0,0>,Tsep,TTT)
#end
#if(TTT<Theatshield+30)
#debug "Heatshield\n"
Jettison(object {Heatshield scale <1,1,-1>},z*0.5,1*(pi*2.25*2.25)/(382),z*2.7,<1,2,0>,Theatshield,TTT)
#end

//Sky

#declare AreoidR=vlength(R(TTT))-alt(TTT);  
#declare AGLR=vlength(R(TTT))-agl(TTT);
PrintNumber("AreoidR: ",AreoidR)
PrintNumber("AGLR: ",AGLR)
#declare ScaleHeight=11000; //meters
#declare HorizonAngle=acos(AGLR/vlength(R(TTT)));
#if(HorizonAngle<(150/3300))
#declare HorizonAngle=150/3300;
#end
PrintNumber("HorizonAngle: ",degrees(HorizonAngle))
#declare SkyTop=AreoidR+alt(TTT)+ScaleHeight;
PrintNumber("Alt: ",alt(TTT))
PrintNumber("SkyTop:",SkyTop)
#declare SkyLength=cos(HorizonAngle)*SkyTop;
PrintNumber("SkyLength: ",SkyLength)
#declare SkyWidth=sin(HorizonAngle)*SkyTop;
PrintNumber("SkyWidth: ",SkyWidth)
#declare PhoenixSky=<187,136,115>/255;
PrintNumber("hypot(SkyLength,SkyWidth): ",sqrt(SkyLength*SkyLength+SkyWidth*SkyWidth))
#if(TTT<(Tland+3))
cone {
  0,0,L(TTT)*cos(HorizonAngle),sin(HorizonAngle)
  open
  no_shadow
  hollow
  finish {ambient 1 diffuse 0}
  pigment {
    onion
    color_map {
      [0 color rgb <0,1,0>]
      [(MarsAtmAltTable[0]*1000+AreoidR)/SkyTop color rgb<1,0,1>]
#declare I=0;
#while(MarsAtmAltTable[I]*1000<alt(TTT))
      #declare LayerR=(MarsAtmAltTable[I]*1000+AreoidR)/SkyTop;
      #declare LayerColor=PhoenixSky*MarsAtmRhoTable[I]/MarsAtmRhoTable[6];
      [LayerR color rgb LayerColor]
/*
      PrintNumber("I:       ",I)
      PrintNumber("Layer R: ",LayerR)
      PrintVector("Layer C: ",LayerColor)
*/
  #declare I=I+1;
#end
    }
  }
  scale SkyTop
  CenterWorld(TTT)
}
background {color rgb LayerColor}
#end

//Get the real horizon angle again for visibility calculations
#declare HorizonAngle=acos(AGLR/vlength(R(TTT)));

//Camera vectors for entry phase, before straighten up and fly right (SUFR) maneuver
#declare CameraSkyE=L(TTT)*cos(bank(TTT))+W(TTT)*sin(bank(TTT));
//#declare CameraSky=L(TTT);
#declare CameraLocE=(-T(TTT)*5+L(TTT)*3)*2;
#declare CameraLookE=L(TTT)*2;

//Camera vectors for descent phase, from after SUFR
#declare CameraSkyD=L(TTT);
#declare CameraHdgD=radians(330); //Compass heading that camera is looking from
#declare ADist=ASDR(Tinflate-4,Tinflate-2,Tinflate+10,Tinflate+15,0,30,TTT);
#declare NoDist=ASDR(Tinflate-4,Tinflate-2,Tinflate+10,Tinflate+15,10,40,TTT);
#declare CameraLocD=(cos(CameraHdgD)*No(TTT)+sin(CameraHdgD)*Ea(TTT))*NoDist+L(TTT)*2-vnormalize(V(TTT))*ADist-L(TTT)*(RappelDist+0)/2;
#declare CameraLookD=-vnormalize(V(TTT))*ADist-L(TTT)*(RappelDist+0)/2;

#declare CameraLocL=BLinterp(exp(0),CameraLocD,exp(10),MRO(TTT),exp(TTT-(Tland+2)));

#switch(TTT)
  #range(-999,Tebm0-7) 
    //Entry phase
    #declare CameraSky=CameraSkyE;
    #declare CameraLoc=CameraLocE;
    #declare CameraLook=CameraLookE;
    #break;
  #range(Tebm0-7,Tebm0-2)
    //Entry to Descent Transition
    #declare CameraSky=vnormalize(Linterp(Tebm0-7,CameraSkyE,Tebm0-2,CameraSkyD,TTT));
    #declare CameraLoc=Linterp(Tebm0-7,CameraLocE,Tebm0-2,CameraLocD,TTT);
    #declare CameraLook=Linterp(Tebm0-7,CameraLookE,Tebm0-2,CameraLookD,TTT);
    #break;
  #range(Tebm0-2,999)
    #declare CameraSky=CameraSkyD;
    #declare CameraLoc=CameraLocL;
    #declare CameraLook=CameraLookD;
    #break;
#end

camera {
  right -x*image_width/image_height
  sky CameraSky
  location CameraLoc//+R(TTT)*2
  look_at CameraLook
//  angle 35
}

#if(TTT>Tland)
  #declare VvColor=<1,1,1,0>;
  #declare Vv=0;
#else
  #if(Vv>0)
    #declare VvColor=<0,1,0,0>;
  #else
    #declare VvColor=<1,0,0,0>;
  #end
#end


union {
  textHud(concat("06 Aug 2012 ",str(h,-2,0),":",str(m,-2,0),":",str(s,-6,3),"UTC SCET (",str(TTT,7,3),"s)"),
          <-16,-8.5>,<1,1,1>,0,-1)           
  textHud(concat("05 Aug 2012 ",str(hlt+6,-2,0),":",str(mlt,-2,0),":",str(slt,-6,3),"pm MDT ERT"),
          <-16,-9>,<1,1,1>,0,-1)           
/*
  textHud("Earth: ",<-16,-8.0>,EarthVecColor,0,-1)
  textHudNumber(degrees(asin(vdot(L(TTT),vnormalize(E(TTT))))+HorizonAngle),"deg above horizon",<-9,-8.0>,EarthVecColor,-1)
  textHudNumber(LT(TTT),"light seconds",<-2,-8.0>,EarthVecColor,-1)
  textHud("Mars Express       ",<-16,-7.5>,MEXVecColor,0,-1)
  textHudNumber(degrees(asin(vdot(L(TTT),vnormalize(MEX(TTT))))+HorizonAngle),"deg above horizon",<-9,-7.5>,MEXVecColor,-1)
  textHudNumber(vlength(MEX(TTT)),"m",<-2,-7.5.0>,MEXVecColor,-1)
  textHud("Mars Recon Orbiter ",<-16,-7.0>,MROVecColor,0,-1)
  textHudNumber(degrees(asin(vdot(L(TTT),vnormalize(MRO(TTT))))+HorizonAngle),"deg above horizon",<-9,-7.0>,MROVecColor,-1)
  textHudNumber(vlength(MRO(TTT)),"m",<-2,-7.0.0>,MROVecColor,-1)
  textHud("Mars Odyssey       ",<-16,-6.5>,ODYVecColor,0,-1)
  textHudNumber(degrees(asin(vdot(L(TTT),vnormalize(ODY(TTT))))+HorizonAngle),"deg above horizon",<-9,-6.5>,ODYVecColor,-1)
  textHudNumber(vlength(ODY(TTT)),"m",<-2,-6.5.0>,ODYVecColor,-1)
*/
  textHud("AGL: ",                     <-16,8.5>,BLinterp(Tland+2,<1,0,0,0>,Tland+4,<1,0,0,1>,TTT),0,-1)
  textHudNumber(agl(TTT)-RappelDist-RappelOfs, "m",<-12,8.5>,BLinterp(Tland+2,<1,0,0,0>,Tland+4,<1,0,0,1>,TTT),  -1)

  textHud("Acc: ",                     <-16,8.0>,BLinterp(Tland+2,<1,1,0,0>,Tland+4,<1,1,0,1>,TTT),0,-1)
  textHudNumber(vlength(AD(TTT))/9.80665, "g",<-12,8.0>,BLinterp(Tland+2,<1,1,0,0>,Tland+4,<1,1,0,1>,TTT),  -1)
/*
  textHud("Heat:",                     <-16,7.5>,<1,0.5,0>,0,-1)
  textHudNumber(DynHeat, "W/cm^2",<-12,7.5>,<1,0.5,0>,  -1)
*/
  textHud("Vv:  ",                     <11.5,8.5>,BLinterp(Tland+2,<1,1,1,0>,Tland+4,<1,1,1,1>,TTT),0,-1)
  textHudNumber(Vv, "m/s",<15,8.5>,BLinterp(Tland+2,VvColor,Tland+4,VvColor+<0,0,0,1>,TTT),  -1)
  textHud("Vrel:",                     <11.5,8.0>,BLinterp(Tsep+2,<1,1,1,0>,Tsep+4,<1,1,1,1>,TTT),0,-1)
  textHudNumber(vlength(V(TTT)), "m/s",<15,8.0>,BLinterp(Tsep+2,<1,1,1,0>,Tsep+4,<1,1,1,1>,TTT),  -1)
  textHud("Mach:",                     <11.5,7.5>,BLinterp(Tsep+2,<1,1,1,0>,Tsep+4,<1,1,1,1>,TTT),0,-1)
  textHudNumber(vlength(V(TTT))/csound(TTT), "",<15,7.5>,BLinterp(Tsep+2,<1,1,1,0>,Tsep+4,<1,1,1,1>,TTT),  -1)
  scale <0.175,0.175,1>
  no_shadow
  LocationLookAt(CameraLoc,CameraLook,CameraSky)
}

