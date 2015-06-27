//Saturn IA

#version unofficial megapov 1.0;

#include "frustum.inc"

#declare USLogo=union {
  text {
    ttf "verdana.ttf","U",1,0
    h_align_center
    translate y*10
  }
  text {
    ttf "verdana.ttf","N",1,0
    h_align_center
    translate y*9
  }
  text {
    ttf "verdana.ttf","I",1,0
    h_align_center
    translate y*8
  }
  text {
    ttf "verdana.ttf","T",1,0
    h_align_center
    translate y*7
  }
  text {
    ttf "verdana.ttf","E",1,0
    h_align_center
    translate y*6
  }
  text {
    ttf "verdana.ttf","D",1,0
    h_align_center
    translate y*5
  }
  text {
    ttf "verdana.ttf","S",1,0
    h_align_center
    translate y*3
  }
  text {
    ttf "verdana.ttf","T",1,0
    h_align_center
    translate y*2
  }
  text {
    ttf "verdana.ttf","A",1,0
    h_align_center
    translate y*1
  }
  text {
    ttf "verdana.ttf","T",1,0
    h_align_center
    translate y*0
  }
  text {
    ttf "verdana.ttf","E",1,0
    h_align_center
    translate y*-1
  }
  text {
    ttf "verdana.ttf","S",1,0
    h_align_center
    translate y*-2
  }
  translate y*2
  scale 36.92
  translate <0,310,-40>
}

#declare KSLogo=union {
  text {
    ttf "verdana.ttf","K",1,0
    h_align_center
    translate y*10
  }
  text {
    ttf "verdana.ttf","W",1,0
    h_align_center
    translate y*9
  }
  text {
    ttf "verdana.ttf","A",1,0
    h_align_center
    translate y*8
  }
  text {
    ttf "verdana.ttf","N",1,0
    h_align_center
    translate y*7
  }
  text {
    ttf "verdana.ttf","S",1,0
    h_align_center
    translate y*4
  }
  text {
    ttf "verdana.ttf","Y",1,0
    h_align_center
    translate y*3
  }
  text {
    ttf "verdana.ttf","S",1,0
    h_align_center
    translate y*2
  }
  text {
    ttf "verdana.ttf","T",1,0
    h_align_center
    translate y*1
  }
  text {
    ttf "verdana.ttf","E",1,0
    h_align_center
    translate y*0
  }
  text {
    ttf "verdana.ttf","M",1,0
    h_align_center
    translate y*-1
  }
  text {
    ttf "verdana.ttf","S",1,0
    h_align_center
    translate y*-2
  }
  translate y*2
  scale 36.92
  translate <0,310,-40>
}

#declare WhitePatch=box {<-18,260,0>,<18,800,-40>}

#declare BlackCylinderUS=cylinder {
  <0,200,0>,<0,889.3,0>,35
  pigment {
    object {
       WhitePatch
       pigment {color rgb 1/10},
       pigment {
	 object {
	    USLogo
	    pigment {color rgb 1},
	    pigment {color rgb <1,0,0>}
	  }
       }
     }
  }
}

#declare BlackCylinderKS=cylinder {
  <0,200,0>,<0,889.3,0>,35
  pigment {
    object {
       WhitePatch
       pigment {color rgb 1/10},
       pigment {
	 object {
	    KSLogo
	    pigment {color rgb 1},
	    pigment {color rgb <1,0,0>}
	  }
       }
     }
  }
}

#declare WhiteCylinder=cylinder {
  <0,200,0>,<0,889.3,0>,35
  pigment {color rgb 1}
}

#declare SI=union {
  union {
    object {BlackCylinderUS translate -z*90 rotate y*000}  
    object {BlackCylinderKS translate -z*90 rotate y*090}  
    object {BlackCylinderUS translate -z*90 rotate y*180}  
    object {BlackCylinderKS translate -z*90 rotate y*270}  
    rotate -y*22.5
  }
  union {
    object {WhiteCylinder translate -z*90 rotate y*000}  
    object {WhiteCylinder translate -z*90 rotate y*090}  
    object {WhiteCylinder translate -z*90 rotate y*180}  
    object {WhiteCylinder translate -z*90 rotate y*270}  
    rotate y*22.5
  }
  cone {
    <0,200,0>,128.5,<0,400,0>,0
    pigment {color rgb 1}
  }
  cylinder {
    <0,0,0>,<0,200,0>,128.5
    pigment {
      radial color_map{[0.5 rgb 0.1][0.5 rgb 1]}
      frequency 2
    }
  }
  cylinder {
    <0,889.3,0>,<0,911.8,0>,128.5
    pigment {
      radial color_map{[0.5 rgb 0.1][0.5 rgb 1]}
      frequency 32
    }
  }
  cylinder {
    <0,911.8,0>,<0,934.3,0>,128.5
    pigment {
      radial color_map{[0.5 rgb 0.1][0.5 rgb 1]}
      frequency 32 phase 0.5
    }
  }
  cone {
    <0,934.3,0>,128.5,<0,970.3,0>,110
    pigment {color rgb 1}
  }
}

#declare SIV=union {
  cylinder {
    <0,970.3,0>,<0,1319.37,0>,110
  }  
  cone {
    <0,1319.37,0>,110,<0,1506.0,0>,60
  }  
  cylinder {
    <0,1506.0,0>,<0,1731.12,0>,60
  }  
  sphereFrust (
    <0,1731.12,0>,60,<0,1951.90,0>,15
  )
  pigment {color rgb 1}
}

#declare SaturnI=union {
  object {SI}
  object {SIV}
  scale 0.0254
}
#declare NaN=0;
#include "shot.inc"
#include "pos.inc"
#declare I=2;
#declare Seconds=frame_number;
#declare Width=min(exp(Seconds/75),60);
#while (I<Seconds*20)
//  #debug concat("I: ",str(I,0,0),"\n")
  #declare ThisPos=Position[I];
  #declare T=I/20;
  #declare SpherePos=vrotate(<ThisPos.x,ThisPos.z,ThisPos.y>,y*360*T/86400);
  #if(I=2) #declare FirstPos=SpherePos; #end
  sphere {SpherePos,Width*0.01 pigment {color rgb <1,1*(T>110),0>}}
  #declare I=I+2;
#end

sphere {
  0,6378.137
  pigment {
    image_map {
      png "/mnt/f/codebase/pov/BlueMarble/EarthMap/EarthMap0.png"
      map_type 1
    }
    rotate y*180
  }
}

background {color rgb <0.5,1,1>}
#declare CamLat=radians(25);
#declare CamLon=radians(-78);
#declare CamAlt=100;
#declare CamVec=<cos(CamLat)*cos(CamLon),sin(CamLat),cos(CamLat)*sin(CamLon)>*(6378.137+CamAlt);
#declare LookLat=radians(29);
#declare LookLon=radians(-78);
#declare LookAlt=100;
//#declare LookVec=<cos(LookLat)*cos(LookLon),sin(LookLat),cos(LookLat)*sin(LookLon)>*(6378.137+LookAlt);
#declare LookVec=(SpherePos+FirstPos)/2;
camera {
  sky CamVec
  location CamVec
  look_at LookVec
  angle Width
}

light_source {
  <0,0,-20>*100000
  color rgb 1
}

