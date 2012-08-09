#declare Smooth=1;
#include "L1011-2.mesh2"
#include "metals.inc"
#include "Logo.inc"
#version unofficial MegaPov 1.11;

#declare Height=L1011_Max.y;
#declare Wingspan=(L1011_Max.x-L1011_Min.x);

#declare LogoTex1=LogoSameRot("svg/Orbital",1572,663,6,10,45)
#declare LogoTex2=LogoThruL   ("svg/USFlag",420,221,1.5,-22,10)

#declare StargazerText=text {
  ttf "arialni.ttf" "STARGAZER"
  10,0
  h_align_center v_align_center
  translate -z*12
}
#declare NNumber=text {
  ttf "arialni.ttf" "N14OSC"
  10,0
  h_align_center v_align_center
  translate -z*10
  scale 0.75
}

#declare TwoStargazers=union {
  union {
    object {
      StargazerText
    }
    object {
      StargazerText
      rotate y*180
    }
    scale 0.5
  }
  union {
    object {
      NNumber
    }
    object {
      NNumber
      rotate y*180
    }
    scale 0.4
    translate <-1.2,-1.3,0>
  }
  translate <-15.5,7.8>
}

#declare Window=box {
  <0,0,-20>,<0.25,0.4,20>
}

#declare Windows=union {
  #local I=0;
  #while(I<75)
    object {
      Window
      translate y*4
      translate x*(20-36/75*I)
    }
    #local I=I+1;
  #end
}

#declare LogoTex3=
  texture {
    pigment { 
      object {
        TwoStargazers 
	pigment {
	  object {
	    Windows
            color rgb 1
	    color rgbf <1,1,1,0.9>
	  }
	}
	pigment {color rgb 0.1 }
      }
    }
    finish {ambient 0.5 diffuse 1}
  }
  texture {LogoTex1 translate y*2.5}
  texture {LogoTex2}

#declare LogoTex=texture {
  LogoTex3
  rotate y*90
  scale 1/<Wingspan,Height,20>
  translate x*0.5
}

#declare L1011Tex=texture {
  material_map {
    png "L1011Front.png"
    once
    texture {
      pigment {color rgbf <1,1,1,0.9>}
      finish {phong 1 ambient 0.5 diffuse 1}
    }
    texture {
      pigment {color rgb <0.75,0,0>}
      finish {ambient 0.5 diffuse 1}
    }
    texture {
      T_Chrome_5A
    }
    texture {
      LogoTex
    }
  }
  translate -x*0.5
  scale <Wingspan,Height,20>
  rotate -y*90
}


#declare L1011=union {
  object {
    L1011Mesh
    rotate -y*90
    texture {L1011Tex}
    translate y*0.5
    translate x*5
  }
  cylinder {
    <-5,3.85,0>,<21.5,3.85,0>,2.85
    pigment {color rgb <1,1,1>}
    finish {ambient 0.5 diffuse 1}
  }
}



