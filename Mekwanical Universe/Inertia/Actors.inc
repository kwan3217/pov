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

