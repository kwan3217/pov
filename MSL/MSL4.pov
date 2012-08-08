#include "KwanMath.inc"
#include "LocLook.inc"
#include "MSLAeroshell2.inc"
#include "MarsAtmCospar2.inc"
#include "hud.inc"

#declare State=#include "msl_edl2.inc"

#macro Vec(I,J)
  (<State[I][J+0],State[I][J+1],State[I][J+2]>)
#end

#macro TTT(I) (State[I][1]) #end
#declare TT=TTT(frame_number);
#macro R(I)  (Vec(I, 2)) #end
#macro V(I)  (Vec(I, 5)) #end
#macro A(I)  (Vec(I, 8)) #end
#macro S(I)  (Vec(I,11)) #end
#macro E(I)  (Vec(I,14)) #end
#macro alt(I)(State[I][19]) #end
#macro rho(I)(MarsAtmRho(alt(I))) #end
#macro csound(I)(MarsAtmCsound(alt(I))) #end
#macro Alpha(I) 
  PrintNumber("Alpha(I) I:",I)
  #if(I<50*24)
    #local result=(State[50*24][21]);
  #else
    #local result=(State[I][21]);
  #end
(result)
#end
#macro bank(I) 
  #if(I<50*24)      
//    (0)
    #local result=(State[50*24][22]);
  #else
    #local result=(State[I][22]);
  #end
(result)
#end

#macro meanBank(I)
  #local J=max(0,I-24);
  #local acc=0;
  #local n=0;
  #while(J<min(I+24,9999))
    #local acc=acc+bank(I)*ASDR(I-24,I,I,I+24,0,1,J);
    #local n=n+ASDR(I-24,I,I,I+24,0,1,J);
    #local J=J+1;
  #end
  (acc/n)
#end

//Local vertical vector. In this model, we use a spherical reference surface 3396km in radius, so
//local vertical is parallel to planetocentric position
#macro L(I)
  (vnormalize(R(I)))
#end

//Local east vector, perpendicular to both local vertical (and therefore in local horizontal plane)
//and Mars north pole           
#macro Ea(I)
  (vnormalize(vcross(z,R(I))))
#end

//Local north vector, perpendicular to both local vertical (and therefore in local horizontal plane)
//and local east vector
#macro No(I)
  (vnormalize(vcross(R(I),Ea(I))))
#end
           
//Tangential vector, parallel to Vrel           
#macro T(I)
  (vnormalize(V(I)))
#end

//Side vector, perpendicular to both L and T, so in local horizon plane
#macro W(I)
  (vnormalize(vcross(L(I),T(I))))
#end

//Normal vector, perpendicular to both T and W, towards local vertical
#macro N(I)
  (vnormalize(vcross(W(I),T(I))))
#end

//Non-gravitational acceleration in drag frame. Components are parallel to T,W,N in that order
#macro AD(I)
  (<vdot(T(I),A(I)),vdot(W(I),A(I)),vdot(N(I),A(I))>)
#end

#declare GaleMesh=mesh2 {
  #include "gale.inc"
  regular_faces {
    640,640
  }
  pigment {color rgb <1.0,0.5,0.0>}
  translate -R(frame_number)
}

#macro agl(I)
  #local aglNormal=<0,0,0>;
  #local RR=R(I)-R(frame_number);
  #local aglPos=trace(GaleMesh,RR,-L(I),aglNormal);
  #if(vlength(aglNormal)>0) 
    #local Result=(vlength(aglPos-RR));
  #else
    #local aglPos=trace(GaleMesh,RR,L(I),aglNormal);
    #local Result=(-vlength(aglPos-RR));
    #if(vlength(aglNormal)>0)
    #else
      #local Result=alt(I);
    #end
  #end
  (Result)
#end

#declare Mach=vlength(V(frame_number))/csound(frame_number);
#declare Cheat=0.224e-10;
#declare mheat=0.879;
#declare nheat=4.22;
#declare MaxHeat=260;
#declare DynHeat=Cheat*pow(vlength(V(frame_number)),nheat)*pow(rho(frame_number),mheat);
PrintNumber("DynHeat: ",DynHeat)
#declare Heat=DynHeat/MaxHeat;
PrintNumber("Heat: ",Heat)
#declare EntryAlpha=-Alpha(frame_number);
PrintNumber("EntryAlpha: ",EntryAlpha)
#include "EntryFlame2.inc"
#declare I=1;

#if(frame_number>0) 
  cylinder {
    <0,0,0>,V(frame_number)/24,0.1
    pigment {color rgb <1,1,1>}
    no_shadow
  }
#end

#declare Vv=vdot(L(frame_number),V(frame_number));
#declare Fpa=asin(Vv/vlength(V(frame_number)));
#declare Ltot=sqrt(AD(frame_number).y*AD(frame_number).y+AD(frame_number).z*AD(frame_number).z);
#declare Dtot=AD(frame_number).x;

#declare LiftAxis=BLinterp(1,N(frame_number),2,vnormalize(AD(frame_number).y*W(frame_number)+AD(frame_number).z*N(frame_number)),abs(Dtot));

#switch(TT)
  #range(-999,260)
    #declare VehicleAxis=T(frame_number);
    #break
  #range(260,264)
    #declare VehicleAxis=vnormalize(Linterp(260,T(frame_number),264,-vnormalize(A(frame_number)),TT));
    #break
  #range(264,999)
    #declare VehicleAxis=-vnormalize(A(frame_number));
    #break
#end

light_source {
  vnormalize(S(frame_number))*1e6
  color rgb <1,1,1>
}

#macro RegularFaces(n_i,n_j)
  n_i*n_j*2
    #local I=0;
    #while(I<n_i)
      #local J=0;
      #while(J<n_j)
        <I*(n_j+1)+J,I*(n_j+1)+J+1,(I+1)*(n_j+1)+J>,
        <I*(n_j+1)+J+1,(I+1)*(n_j+1)+J+1,(I+1)*(n_j+1)+J>,
        #local J=J+1;
      #end
      #local I=I+1;
    #end
#end
                     
#declare EarthNormal=<0,0,0>;
#declare Earthpos=trace(GaleMesh,<0,0,0>,E(frame_number),EarthNormal);
#if(vlength(EarthNormal)>0)
  #declare EarthVecColor=<0,0,0>;
#else
  #declare EarthVecColor=<1,0,1>;
#end

object {GaleMesh}
                     
#declare SphereR=vlength(R(9999))-agl(9999);

sphere {
  -R(frame_number),SphereR-1000
//  -R(frame_number),vlength(R(frame_number))-alt(frame_number)-10000
  pigment {color rgb <1,0.5,0>}
} 

union {
  cone {
    No(9999)*100,0,No(9999)*1000,100
  }
  cone {
    L(9999)*10000,0,L(9999)*20000,2000
  }
  cone {
    -No(9999)*100,0,-No(9999)*1000,100
  }
  cone {
    Ea(9999)*100,0,Ea(9999)*1000,100
  }
  cone {
    -Ea(9999)*100,0,-Ea(9999)*1000,100
  }
  pigment {color rgb x}
  translate R(9999)-R(frame_number)
}

cylinder {
  0,vnormalize(E(frame_number))*4,0.1
  pigment {color rgb EarthVecColor}
  no_shadow
}

#include "MSLChute.inc"

union {
  union {
    object{Backshell}
    #if(TT<300)
    object{Heatshield  rotate <1,2,0>*pow(BLinterp(287.5,0,387.5,180,TT),2) translate -z*BLinterp(287.5,0,387.5,100*2.5,TT)}
    #end
    object {MSLChute(TT,frame_number) translate z*1.9}
    #if(Mach>6 & DynHeat>MaxHeat*0.01)
      object {EntryFlame} 
    #end
    #if(TT < 264)
    rotate -y*degrees(Alpha(frame_number)) rotate z*(degrees(bank(frame_number))-90)
    #end
  }
  LocationLookAt(<0,0,0>,-VehicleAxis,N(frame_number))
}

//Sky
#declare AreoidR=vlength(R(frame_number))-alt(frame_number);  
#declare AGLR=vlength(R(frame_number))-agl(frame_number);
PrintNumber("AreoidR: ",AreoidR)
PrintNumber("AGLR: ",AGLR)
#declare ScaleHeight=11000; //meters
#declare HorizonAngle=acos(AGLR/vlength(R(frame_number)));
//#if(HorizonAngle<50/3300)
//#declare HorizonAngle=50/3300;
//#end
PrintNumber("HorizonAngle: ",degrees(HorizonAngle))
#declare SkyTop=AreoidR+alt(frame_number)+ScaleHeight;
PrintNumber("Alt: ",alt(frame_number))
PrintNumber("SkyTop:",SkyTop)
#declare SkyLength=cos(HorizonAngle)*SkyTop;
PrintNumber("SkyLength: ",SkyLength)
#declare SkyWidth=sin(HorizonAngle)*SkyTop;
PrintNumber("SkyWidth: ",SkyWidth)
#declare PhoenixSky=<187,136,115>/255;
PrintNumber("hypot(SkyLength,SkyWidth): ",sqrt(SkyLength*SkyLength+SkyWidth*SkyWidth))
cone {
  0,0,L(frame_number)*cos(HorizonAngle),sin(HorizonAngle)
  open
  no_shadow
  finish {ambient 1 diffuse 0}
  pigment {
    onion
    color_map {
      [0 color rgb <0,1,0>]
      [(MarsAtmAltTable[0]*1000+AreoidR)/SkyTop color rgb<1,0,1>]
#declare I=0;
#while(MarsAtmAltTable[I]*1000<alt(frame_number))
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
  translate -R(frame_number)

}

background {color rgb LayerColor}

cylinder {
  0,A(frame_number)/9.80665,0.1
  pigment {color rgb <1,1,0>}
    no_shadow
}

union {
  #local EllI=0;
  #while(EllI<=360)
    #local NN0=vnormalize(No(9999)*10000*cos(radians(EllI  ))+Ea(9999)*15000*sin(radians(EllI  ))+R(9999))*SphereR;
    #local NN1=vnormalize(No(9999)*10000*cos(radians(EllI+1))+Ea(9999)*15000*sin(radians(EllI+1))+R(9999))*SphereR;
    cylinder {
      NN0,NN1,500
    }
    sphere {
      NN1,500
    }
    #local EllI=EllI+1;
  #end
  pigment {color rgb <1,1,1>}
  translate -R(frame_number)
  no_shadow
}

//Camera vectors for entry phase, before straighten up and fly right (SUFR) maneuver
#declare CameraSkyE=L(frame_number)*cos(meanBank(frame_number))+W(frame_number)*sin(meanBank(frame_number));
//#declare CameraSky=L(frame_number);
#declare CameraLocE=(-T(frame_number)*5+L(frame_number)*3)*2;
#declare CameraLookE=L(frame_number)*2;

//Camera vectors for descent phase, from after SUFR
#declare CameraSkyD=L(frame_number);
#declare ADist=ASDR(260,263,273.5,278,0,30,TT);
#declare NoDist=ASDR(260,263,273.5,278,10,40,TT);
#declare CameraLocD=No(frame_number)*NoDist+L(frame_number)*2-vnormalize(V(frame_number))*ADist;
#declare CameraLookD=-vnormalize(V(frame_number))*ADist;

#switch(TTT(frame_number))
  #range(-999,243) 
    //Entry phase
    #declare CameraSky=CameraSkyE;
    #declare CameraLoc=CameraLocE;
    #declare CameraLook=CameraLookE;
    #break;
  #range(243,248)
    //Entry to Descent Transition
    #declare CameraSky=vnormalize(Linterp(243,CameraSkyE,248,CameraSkyD,TTT(frame_number)));
    #declare CameraLoc=Linterp(243,CameraLocE,248,CameraLocD,TTT(frame_number));
    #declare CameraLook=Linterp(243,CameraLookE,248,CameraLookD,TTT(frame_number));
    #break;
  #range(248,999)
    #declare CameraSky=CameraSkyD;
    #declare CameraLoc=CameraLocD;
    #declare CameraLook=CameraLookD;
    #break;
#end

camera {
  right -x*image_width/image_height
  sky CameraSky
  location CameraLoc
  look_at CameraLook
//  angle 35
}

#declare utcOffset=5*3600+11*60+18.117;
#declare h=floor((State[frame_number][1]+utcOffset)/3600);
#declare m=floor(((State[frame_number][1]+utcOffset)-h*3600)/60);
#declare s=(State[frame_number][1]+utcOffset)-h*3600-m*60;

union {
  union {
    textHud(concat(str(h,-2,0),":",str(m,-2,0),":",str(s,-6,3)," (",str(State[frame_number][1],7,3),"s)"),
            <-16,-9>,<1,1,1>,0,-1)           
    textHud("Earth above horizon: ",<-16,-8.5>,EarthVecColor,0,-1)
    textHudNumber(degrees(asin(vdot(L(frame_number),vnormalize(E(frame_number))))+HorizonAngle),"deg",<-9,-8.5>,EarthVecColor,-1)
    textHud("AGL: ",                     <-16,8.5>,<1,0,0>,0,-1)
    textHudNumber(agl(frame_number), "m",<-12,8.5>,<1,0,0>,  -1)

    textHud("Alt: ",                     <-16,8.0>,<1,0,0>,0,-1)
    textHudNumber(alt(frame_number), "m",<-12,8.0>,<1,0,0>,  -1)
    textHud("Acc: ",                     <-16,7.5>,<1,1,0>,0,-1)
    textHudNumber(vlength(AD(frame_number))/9.80665, "g",<-12,7.5>,<1,1,0>,  -1)
    textHud("Heat:",                     <-16,7.0>,<1,0.5,0>,0,-1)
    textHudNumber(DynHeat, "W/cm^2",<-12,7.0>,<1,0.5,0>,  -1)
    textHud("Vrel:",                     <11.5,8.5>,<1,1,1>,0,-1)
    textHudNumber(vlength(V(frame_number)), "m/s",<15,8.5>,<1,1,1>,  -1)
    textHud("Fpa: ",                     <11.5,8.0>,<0.5,0.5,0.5>,0,-1)
    textHudNumber(degrees(Fpa), "deg",<15,8.0>,<0.5,0.5,0.5>,  -1)
#if(abs(Dtot)>1)
    textHud("L/D: ",                     <11.5,7.5>,BLinterp(1,<0,0,0>,2,<0.5,0.5,0.5>,abs(Dtot)),0,-1)
    textHudNumber(Ltot/-Dtot, "",<15,7.5>,BLinterp(1,<0,0,0>,2,<0.5,0.5,0.5>,abs(Dtot)),  -1)
    textHud("AlpT:",                     <11.5,6.5>,BLinterp(1,<0,0,0>,2,<0.5,0.5,0.5>,abs(Dtot)),0,-1)
    textHudNumber(degrees(Alpha(frame_number)), "deg",<15,6.5>,BLinterp(1,<0,0,0>,2,<0.5,0.5,0.5>,abs(Dtot)),  -1)
#end
    textHud("Vv:  ",                     <11.5,7.0>,<1,1,1>,0,-1)
    textHudNumber(Vv, "m/s",<15,7.0>,<1,1,1>,  -1)
    textHud("Mach:",                     <11.5,6.0>,<1,1,1>,0,-1)
    textHudNumber(vlength(V(frame_number))/csound(frame_number), "",<15,6.0>,<1,1,1>,  -1)
    textHud("Bank:",                     <11.5,5.5>,<1,1,1>,0,-1)
    textHudNumber(degrees(bank(frame_number)), "deg",<15,5.5>,<1,1,1>,  -1)
    scale <0.175,0.175,1>
    no_shadow
  }
  LocationLookAt(CameraLoc,CameraLook,CameraSky)
}

