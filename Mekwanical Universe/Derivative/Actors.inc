//#version unofficial Megapov 1.22;

#declare Left=0.0;
#declare Right=1.0;
#declare Center=0.5;

#macro Text(Font,String,Thick,Align)
  #local TextObj=text {
     ttf Font String Thick 0
    //Rotate and reflect so that text object is:
    //Baseline: Sits on +X axis
    //Ascent: Up +Y axis
    //Thickness: Text object extends from 0 to Thick in the +Z direction
    rotate x*90
//    translate -2*y*Thick
  }
  #local MinX=min_extent(TextObj);
  #local MaxX=max_extent(TextObj);
  object {
    TextObj
    translate -x*Align*(MaxX.x-MinX.x)
  }
#end

#declare Protractor=union {
  difference {
    cylinder {
      <0,-0.001,0>,<0,-0.06,0>,3
    }
    cylinder {
      <0,0.1,0>,<0,-0.2,0>,2.25
    }
    plane {
      x,-0.2
    }
  }
  box {
    <0,-0.001,-2.5>,<0.75,-0.06,2.5>
  }
  #local I=-90;
  #while(I<=90)
    box {
      <Linterp(0,2.9,1,2.8,(mod(I,10)=0)),-0.061,-0.005>,<3,-0.06,0.005>
      rotate -y*I
      pigment {color rgb 0.1}
    }
    #if(mod(I,10)=0)
      union {
        Text("verdana.ttf",str(abs(I),3,0),0.001,Center)
        translate -y*0.061
        scale <0.2,1,0.2>
        rotate y*90
        translate x*2.7
        rotate -y*I
        pigment {color rgb 0.1}
      }
    #end
    #local I=I+1;
  #end
  box {
    <0,-0.061,-0.005>,<0.6,-0.06,0.005>
    pigment {color rgb 0.1}
  }
  pigment {color rgb <1,0.9,0>}
  finish {phong 1}
}

#declare Ruler=union {
  difference {
    box {
      <-5.3,0,0>,<5.3,-0.06,-1>
    }
    plane {
      y,0
      rotate -x*11
    }
    translate -y*0.001
    pigment {color rgb <0,0.5,1>}
    finish {phong 1}
  }
  difference {
    union {
      #local I=-50;
      #while(I<=50)
        box {
          <-0.005,0,Linterp(0,-0.1,1,-0.25,(mod(I,10)=0))>,<0.005,-0.06,0>
          translate x*I/10
        }
        #if(mod(I,10)=0)
          union {
            Text("verdana.ttf",str(abs(I/10),1,0),0.001,Center)
            scale <0.3,1,0.3>
            translate <I/10,-0.061,-0.6>
          }
        #end
        #local I=I+1;
      #end
    }
    plane {
      y,0
      rotate -x*11
    }
    translate -y*0.002
    pigment {color rgb 0.1}
  }    
}

#macro Display(V,W,Tag,TagColor,Number,NumberColor,L,F,FadeN)
  union {
    Text("verdana.ttf",Tag,0,Left)
    scale 0.4
    translate V-0.03*y
    Fade(TagColor,FadeN)
  }
  union {
    Text("lucon.ttf",str(Number,L,F),0,Right)
    scale 0.4
    translate V+<W,-0.03,0>
    Fade(NumberColor,FadeN)
  }
#end

#macro AngleDisplay(Angle,FadeN)
  Display(<2.5,0,-3>,2.5,"Angle: ",<1,1,1,0>,Angle,<1,0.9,0,0>,5,1,FadeN)
#end

#macro RiseDisplay( Rise, FadeN)
  Display(<-7,0,3>,  3.5,"Rise: " ,<1,1,1,0>,Rise, <0,0.5,1,0>,8,3,FadeN)
#end

#macro RunDisplay(  Run,  FadeN)
  Display(<-7,0,2.5>,3.5,"Run: "  ,<1,1,1,0>,Run,  <1,0,0,0>,  8,3,FadeN)
#end

#macro SlopeDisplay(Slope,FadeN)
  Display(<-7,0,2>,  3.5,"Slope: ",<1,1,1,0>,Slope,<0,1,0,0>,  8,3,FadeN)
#end

#local T=sqrt(3)/2;
#local T1=1/16;
#local T2=1.0;
#local R=1;
#declare Pencil=union {
  intersection {
    prism {
      0,1,6
      <1,0>,<0.5,T>,<-0.5,T>,<-1,0>,<-0.5,-T>,<0.5,-T>
      scale <0.3,4.001,0.3>
      rotate -z*90
      pigment {color rgb <1,0,0>}
      finish {phong 1}
    }
    cone {
      Linterp(0,<0,0,0>,1,<4,0,0>,T1),Linterp(0,0,1,R,T1),
      Linterp(0,<0,0,0>,1,<4,0,0>,1.001),Linterp(0,0,1,R,1.001)
      pigment {color rgb <1,1,0.5>}
    }
    cylinder {
      <0,0,0>,<4.001,0,0>,Linterp(0,0,1,R,T1)
      inverse
    }
    plane {
      x,4
      pigment {color rgb <1,1,0.5>}
    }      
  }
  intersection {
    cone {
      Linterp(0,<0,0,0>,1,<4,0,0>,0),Linterp(0,0,1,R,0),
      Linterp(0,<0,0,0>,1,<4,0,0>,T2),Linterp(0,0,1,R,T2)
    } 
    cylinder {
      <0,0,0>,<4.001,0,0>,Linterp(0,0,1,R,T1)
    }
    pigment {color rgb <0.8,0,0>}
    finish {phong 1}
  }
}

#declare AllShapes_Z_Increment=0.001;
#declare AllShapes_Z_Scale=0.07;
#include "Truck.inc"
#declare Truck=object {
  Truck_IS
  scale <2.4/AllShapes_WIDTH,-1,2.4/AllShapes_WIDTH>
//  rotate -x*90
//  translate -y*0.06
}

#declare AllShapes_Z_Increment=0.001;
#declare AllShapes_Z_Scale=0.03;
#include "Steep Grade.inc"
#declare SteepGradeSign=union {
  object {
    SteepGradeSign_IS
    translate -x*AllShapes_CENTER_X
    scale <1.2/AllShapes_WIDTH,-1,1.2/AllShapes_WIDTH>
    translate z
  }
  cylinder {
    <0,0,0>,<0,0,2>,0.03
    pigment {color rgb <0.5,0.5,0.5>}
    finish {phong 1} 
  }
}

#macro TireSmoke(ClockN)
  disc {
    #local X=0.25-1.5*ClockN;
    #local Z=0.2+1.0*ClockN*ClockN;
    #local Y=-0.065+Linterp(0,0,1,0.004,ClockN);
    #local R=0.6*Linterp(0,0.1,1,1,ClockN);
    #local F=0.8*(1-ClockN);
    <X,Y,Z>,y,R
    Fade(<0.1,0.1,0.1,0>,F)
    no_shadow
  }
#end


