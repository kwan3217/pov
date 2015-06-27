#version unofficial Megapov 1.22;
#include "KwanMath.inc"
#include "LocLook.inc"
#declare Aeroshell=#include "MSL Aeroshell.inc"
#include "MarsAtmCospar2.inc"

global_settings {right_handed}

#declare State=#include "msl_edl.inc"

#macro Vec(I,J)
  (<State[I][J+0],State[I][J+1],State[I][J+2]>)
#end

#macro R(I)  (Vec(I, 2)) #end
#macro V(I)  (Vec(I, 5)) #end
#macro S(I)  (Vec(I, 8)) #end
#macro E(I)  (Vec(I,11)) #end
#macro L(I)  (Vec(I,14)) #end
#macro T(I)  (Vec(I,17)) #end
#macro W(I)  (Vec(I,20)) #end
#macro N(I)  (Vec(I,23)) #end
#macro AD(I) (Vec(I,26)) #end
#macro rho(I)(State[I][29]) #end
#macro agl(I)(State[I][30]) #end
#macro alt(I)(State[I][31]) #end
#macro csound(I)(State[I][33]) #end
#macro Dist(I)(State[I][34]) #end
#macro az(I)(State[I][35]) #end

#declare TT=frame_number/24;
#declare Mach=vlength(V(frame_number))/csound(frame_number);
#declare DynHeat=pow(vlength(V(frame_number)),3)*rho(frame_number)/2;
PrintNumber("DynHeat: ",DynHeat)
#declare Heat=BLinterp(1.7e8,0.12,7.5e8,1,DynHeat);
PrintNumber("Heat: ",Heat)
#include "EntryFlame.inc"
#declare I=1;

#if(frame_number>0) 
  cylinder {
    <0,0,0>,V(frame_number)/24,0.1
    pigment {color rgb <1,1,1>}
    no_shadow
  }
#end

cylinder {
  0,L(frame_number)*2,0.1
  pigment {color rgb <0,0.5,1>}
    no_shadow
}

cylinder {
  0,W(frame_number)*2,0.1
  pigment {color rgb <0,1,0>}
    no_shadow
}

cylinder {
  0,N(frame_number)*2,0.1
  pigment {color rgb <0,0,1>}
    no_shadow
}

#declare Vv=vdot(L(frame_number),V(frame_number));
#declare Fpa=asin(Vv/vlength(V(frame_number)));
#declare Ltot=sqrt(AD(frame_number).y*AD(frame_number).y+AD(frame_number).z*AD(frame_number).z);
#declare Dtot=AD(frame_number).x;
#declare LDperAlpha=0.93463; //An angle of attack of alpha_t generates an L/D of LDperAlpha*sin(alpha_t)

#declare LiftAxis=BLinterp(1,N(frame_number),2,vnormalize(AD(frame_number).y*W(frame_number)+AD(frame_number).z*N(frame_number)),abs(Dtot));
#declare LD=BLinterp(1,0.1,2,abs(Ltot/Dtot),abs(Dtot));

#declare AlpT=asin(LD/LDperAlpha);
#declare Aloc=AD(frame_number).x*T(frame_number)+AD(frame_number).y*W(frame_number)+AD(frame_number).z*N(frame_number);
#declare VehicleAxis=-LiftAxis*sin(AlpT)+T(frame_number)*cos(AlpT);

cylinder {
  0,vnormalize(E(frame_number))*4,0.1
  pigment {color rgb <1,0,1>}
    no_shadow
}

union {
  object{Aeroshell}
  object {EntryFlame}
  LocationLookAt(<0,0,0>,-VehicleAxis,LiftAxis)
}

//Sky
#declare AeroidR=vlength(R(frame_number))-alt(frame_number);
PrintNumber("AeroidR: ",AeroidR)
#declare ScaleHeight=11000; //meters
#declare HorizonAngle=acos(AeroidR/vlength(R(frame_number)));
PrintNumber("HorizonAngle: ",degrees(HorizonAngle))
#declare SkyTop=AeroidR+alt(frame_number)+ScaleHeight;
PrintNumber("Alt: ",alt(frame_number))
PrintNumber("SkyTop:",SkyTop)
#declare SkyLength=cos(HorizonAngle)*SkyTop;
PrintNumber("SkyLength: ",SkyLength)
#declare SkyWidth=sin(HorizonAngle)*SkyTop;
PrintNumber("SkyWidth: ",SkyWidth)
#declare PhoenixSky=<187,136,115>/255;
PrintNumber("hypot(SkyLength,SkyWidth): ",sqrt(SkyLength*SkyLength+SkyWidth*SkyWidth))
cone {
  0,0,vnormalize(R(frame_number))*cos(HorizonAngle),sin(HorizonAngle)
  open
  no_shadow
  finish {ambient 1 diffuse 0}
  pigment {
    onion
    color_map {
      [0 color rgb <0,1,0>]
      [(MarsAtmH[0]*1000+AeroidR)/SkyTop color rgb<1,0,1>]
#declare I=0;
#while(MarsAtmH[I]*1000<alt(frame_number))
      #declare LayerR=(MarsAtmH[I]*1000+AeroidR)/SkyTop;
      #declare LayerColor=PhoenixSky*MarsAtmRho[I]/MarsAtmRho[6];
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
  0,Aloc/9.80665,0.1
  pigment {color rgb <1,1,0>}
    no_shadow
}

light_source {
  vnormalize(S(frame_number))*1e6
  color rgb <1,1,1>
}


sphere {
  -R(frame_number),vlength(R(frame_number))-agl(frame_number)
//  -R(frame_number),vlength(R(frame_number))-alt(frame_number)-10000
  pigment {color rgb <1,0.5,0>}
}

#declare CameraLoc=(-W(frame_number)*5+L(frame_number)*0.5)*10;
//#declare CameraLoc=vnormalize(vnormalize(R(frame_number))*50-W(frame_number)*40)*50;
#declare CameraLook=<0,0,0>;
#declare CameraSky=vnormalize(L(frame_number));

camera {
  right x*16/9
  sky CameraSky
  location CameraLoc
  look_at CameraLook
  angle 35
}

#macro textHud(S,V,C,Halign,Valign)
  text {
    ttf "lucon.ttf"
    S 0 0
    #if(Halign<=0)
      h_align_left
    #else
      #if(Halign>=1)
        h_align_right
      #else
        h_align_center
      #end
    #end
    #if(Valign=0)
      v_align_bottom
    #else
      #if(Valign>=1)
        v_align_top
      #else
        #if(Valign>0)
          v_align_center
        #else
          //v_align_baseline (for Valign<0
        #end
      #end
    #end
    scale 0.05
    rotate z*90
    translate <-V.x/9,V.y/9,1>
    pigment {color rgb C}
    finish {ambient 1 diffuse 0}
  }
#end

#macro textHudNumber(N,U,V,C,Valign) 
  #if(abs(N)>1000) 
    textHud(str(N/1000,7,3),V,C,1,Valign)
    textHud(concat("k",U),V,C,0,Valign)
  #else
    textHud(str(N,7,3),V,C,1,Valign)
    textHud(concat(" ",U),V,C,0,Valign)
  #end

#end

#declare utcOffset=11*3600+29*60+52.353;
#declare h=floor((State[frame_number][1]+utcOffset)/3600);
#declare m=floor(((State[frame_number][1]+utcOffset)-h*3600)/60);
#declare s=(State[frame_number][1]+utcOffset)-h*3600-m*60;

union {
  union {
    textHud(concat(str(h,-2,0),":",str(m,-2,0),":",str(s,-6,3)," (",str(State[frame_number][1],7,3),"s)"),
            <-16,-9>,<1,1,1>,0,-1)           
    textHud("Earth above horizon: ",<-16,-8.5>,<1,0,1>,0,-1)
    textHudNumber(degrees(asin(vdot(L(frame_number),vnormalize(E(frame_number))))+HorizonAngle),"deg",<-9,-8.5>,<1,0,1>,-1)
    textHud("AGL: ",                     <-16,8.5>,<1,0,0>,0,-1)
    textHudNumber(agl(frame_number), "m",<-12,8.5>,<1,0,0>,  -1)

    textHud("Alt: ",                     <-16,8.0>,<1,0,0>,0,-1)
    textHudNumber(alt(frame_number), "m",<-12,8.0>,<1,0,0>,  -1)
    textHud("Acc: ",                     <-16,7.5>,<1,1,0>,0,-1)
    textHudNumber(vlength(AD(frame_number))/9.80665, "g",<-12,7.5>,<1,1,0>,  -1)
    textHud("Vrel:",                     <11.5,8.5>,<1,1,1>,0,-1)
    textHudNumber(vlength(V(frame_number)), "m/s",<15,8.5>,<1,1,1>,  -1)
    textHud("Fpa: ",                     <11.5,8.0>,<0.5,0.5,0.5>,0,-1)
    textHudNumber(degrees(Fpa), "deg",<15,8.0>,<0.5,0.5,0.5>,  -1)
#if(abs(Dtot)>1)
    textHud("L/D: ",                     <11.5,7.5>,BLinterp(1,<0,0,0>,2,<0.5,0.5,0.5>,abs(Dtot)),0,-1)
    textHudNumber(LD, "",<15,7.5>,BLinterp(1,<0,0,0>,2,<0.5,0.5,0.5>,abs(Dtot)),  -1)
    textHud("AlpT:",                     <11.5,6.5>,BLinterp(1,<0,0,0>,2,<0.5,0.5,0.5>,abs(Dtot)),0,-1)
    textHudNumber(degrees(AlpT), "deg",<15,6.5>,BLinterp(1,<0,0,0>,2,<0.5,0.5,0.5>,abs(Dtot)),  -1)
#end
    textHud("Vv:  ",                     <11.5,7.0>,<1,1,1>,0,-1)
    textHudNumber(Vv, "m/s",<15,7.0>,<1,1,1>,  -1)
    textHud("Mach:",                     <11.5,6.0>,<1,1,1>,0,-1)
    textHudNumber(vlength(V(frame_number))/csound(frame_number), "",<15,6.0>,<1,1,1>,  -1)
    scale <0.175,0.175,1>
    no_shadow
  }
  LocationLookAt(CameraLoc,CameraLook,CameraSky)
}


