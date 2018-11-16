#include "voyager.mesh2"

#declare MeshToStd=transform {
  translate <-0.0306,105.19,5>
  scale 0.1
  scale 1.8288/1.7288
  rotate -z*90
  rotate y*180
}

#declare RBF=array[2] {39,674}
#declare Az=array[3] {676,677,678}
#declare ScanPlatform=array[77] {
 15, 29, 30, 31, 37, 38, 45,158,159,160,
161,162,164,165,166,167,168,169,171,213,
214,215,216,217,261,262,263,264,619,620,
621,622,623,624,626,627,628,629,630,631,
632,633,634,635,637,638,639,640,641,642,
643,644,646,647,648,649,650,651,652,653,
654,656,657,658,659,660,661,662,663,665,
666,667,668,670,671,672,673}

#declare VoyagerMainBus=union {
  #local I=0;
  #while(I<dimension_size(partArray,1))
    #local DoIt=1;
    #local J=0;
    #while(J<dimension_size(RBF,1))
      #if(I=RBF[J])
        #local DoIt=0;
      #end
      #local J=J+1;
    #end
    #local J=0;
    #while(J<dimension_size(Az,1))
      #if(I=Az[J])
        #local DoIt=0;
      #end
      #local J=J+1;
    #end
    #local J=0;
    #while(J<dimension_size(ScanPlatform,1))
      #if(I=ScanPlatform[J])
        #local DoIt=0;
      #end
      #local J=J+1;
    #end
#if(DoIt)
    object{partArray[I] 
    texture {materialArray[I]}
  }
#end
    #local I=I+1;
  #end
  transform MeshToStd
}  

#declare VoyagerScanPlatform=union {
  #local I=0;
  #while(I<dimension_size(ScanPlatform,1))
    object{partArray[ScanPlatform[I]] 
      texture {materialArray[ScanPlatform[I]]}
    }
    #local I=I+1;
  #end
  transform MeshToStd
}

#declare SPCenter=<0,3.435,-0.17>;
#declare ElAxis=vnormalize( y-z*0.055);
#declare AzAxis=vnormalize(-z-y*0.055);
#declare StdQ=QuatMult(AA(ElAxis,-13),AA(AzAxis,-17.5));
#declare SpiceNullQ=QuatMult(AA(z,90),QuatMult(AA(AzAxis,90),QuatMult(AA(-ElAxis,86.7-180),StdQ)));
#declare Voyager=union {
  object {VoyagerMainBus}
  union {
    object {VoyagerScanPlatform}
    cylinder {SPCenter,SPCenter+x,0.1 pigment {color rgb <1,0,0>}}
    cylinder {SPCenter,SPCenter+y,0.1 pigment {color rgb <0,1,0>}}
    cylinder {SPCenter,SPCenter+z,0.1 pigment {color rgb <0,0,1>}}
    translate -SPCenter QuatTrans(StdQ,SPCenter)
  }
  union {
    cylinder {0,AzAxis*3,0.02 pigment {color rgb <1,1,1>}}
    cylinder {0,ElAxis*3,0.02 pigment {color rgb <1,1,1>*0.2}}
    cylinder {0,vnormalize(vcross(ElAxis,AzAxis))*3,0.02 pigment {color rgb <1,0,0.5>}}
    translate SPCenter
  } 
}

#macro VoyagerQ(Q) 
  union {
    object {VoyagerMainBus}
  union {
    object {VoyagerScanPlatform}
    cylinder {SPCenter,SPCenter+x,0.1 pigment {color rgb <1,0,0>}}
    cylinder {SPCenter,SPCenter+y,0.1 pigment {color rgb <0,1,0>}}
    cylinder {SPCenter,SPCenter+z,0.1 pigment {color rgb <0,0,1>}}
    translate -SPCenter QuatTrans(StdQ,SPCenter)
  }
  }
#end

#macro VoyagerQSpice(QSpice) 
  union {
    object {VoyagerMainBus}
    union {
      object {VoyagerScanPlatform}
      cylinder {SPCenter,SPCenter+x,0.1 pigment {color rgb <1,0,0>}}
      cylinder {SPCenter,SPCenter+y,0.1 pigment {color rgb <0,1,0>}}
      cylinder {SPCenter,SPCenter+z,0.1 pigment {color rgb <0,0,1>}}
      translate -SPCenter QuatTrans(QuatMult(QSpice,SpiceNullQ),SPCenter)
    }
  }
#end

#macro VoyagerAE(Az,El) 
  union {
    object {VoyagerMainBus}
    object {VoyagerScanPlatform translate -SPCenter QuatTrans(SpiceNullQ,SPCenter)}
  }
#end
