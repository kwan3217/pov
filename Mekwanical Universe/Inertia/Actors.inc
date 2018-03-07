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

#macro Vector(V0,V1,R)
  #if(vlength(V0-V1)>0)
    cylinder {
      V0,V0+(V1-V0)*0.8,R
    }
    cone {
      V0+(V1-V0)*0.8,R*2,V1,0
    }
  #end
#end

#macro Frame(Progress,Fade)
  #local XProgress =BLinterp(0/5,0,2/5,1,Progress);
  #local YProgress =BLinterp(1/5,0,3/5,1,Progress);
  #local ZProgress =BLinterp(2/5,0,4/5,1,Progress);
  #local XYProgress=BLinterp(3/5,0,5/5,1,Progress);
  PrintNumber("Frame Progress:   ",Progress)
  PrintNumber("Frame XProgress:  ",XProgress)
  PrintNumber("Frame YProgress:  ",YProgress)
  PrintNumber("Frame ZProgress:  ",ZProgress)
  PrintNumber("Frame XYProgress: ",XYProgress)
  #local PartVector=array[3] {x,y,z};
  #local PartProgress=array[3] {XProgress, YProgress, ZProgress};
  #local I=0;
  #while(I<3)
    #if(PartProgress[I]>0)
      #local PartHead=PartProgress[I]*10-5;
      #local PartTail=PartHead-1;
      PrintNumber("PartHead: ",PartHead)
      PrintNumber("PartTail: ",PartTail)
      union {
        cone {
          PartVector[I]*PartHead,0,PartVector[I]*PartTail,0.2
        }
        #if(PartTail>-5)
          cylinder {
            -5*PartVector[I],PartVector[I]*PartTail,0.1
          }
        #end
        pigment {color rgbt PartVector[I]+t*(1-Fade)}
      }
    #end
    #local I=I+1;
  #end
  #if(XYProgress*Fade>0)
  plane {
    z,0
    pigment {checker color rgbt <1,1,1,(1-XYProgress*Fade*0.2)> color rgbt <0,0,1,(1-XYProgress*Fade*0.2)>}
    clipped_by {
      box {<-5,-5,-0.01>,<5,5,0.01>}
    }
  }
  #end
#end

#macro Particle(R,V,M,RColor,VColor,LColor,MColor,PColor,FadeR,FadeV,FadeL,FadeM,FadeP)
  //R - position vector
  //V - velocity vector
  //(L) - angular momentum vector, calculated internally
  //M - radius of point mass
  //(P) - parallelogram, drawn internally
  //xColor - RGB components color of part x (where x is R,V,L,M,P)
  //Fadex  - Fade component of part x (1 is completely opaque, 0 completely transparent)
  #local L=vcross(R,V);
  #if((FadeR>0)*(vlength(R)>0))
    union {
      Vector(0,R,0.1)
      pigment {color rgbt RColor+t*(1-FadeR)}
    }
  #end
  #if((FadeV>0)*(vlength(V)>0))
    union {
      Vector(R,R+V,0.1)
      pigment {color rgbt VColor+t*(1-FadeV)}
    }
  #end
  #if((FadeL>0)*(vlength(L)>0))
    union {
      Vector(0,L,0.1)
      pigment {color rgbt LColor+t*(1-FadeL)}
    }
  #end
  #if((FadeM>0)*(M>0))
    sphere {
      R,M
      pigment {color rgbt MColor+t*(1-FadeM)}
    }
  #end
  #if((FadeP>0)*(vlength(L)>0))
    union {
      triangle {
        0,R,R+V
      }
      triangle {
        0,R+V,V
      }
      pigment {color rgbt PColor+t*(1-FadeP)}
    }
  #end
#end

