//#version unofficial MegaPov 0.71;
//Requires partial illumination patch

//SaturnMod.inc       
#declare Seed=seed(1);

/* Detail         What it means
    -1            Don't include planet model at all
     0            solid colored sphere
     1            textured sphere, no rings
     2            1 and solid colored rings
     3            2 and textured rings
     4            3 and partially illuminated rings
*/

//Sunside is 0 if you are on the sunny side,
//           1 if the sunny side is south and you are north
//          -1 conversely
//   --OR--
//set SaturnPole to the direction of the Saturn North Pole
//    CameraPos to the location statement in the camera
//    SunPos to the location of the center of the sun
//    SaturnPos to the location of the center of Saturn.
#ifndef(SunSide) 
  #ifdef(SaturnPole)
    #declare SaturnRingSunPos=SunPos-SaturnPos;
//    PrintVector("SaturnRingSunPos",SaturnRingSunPos)
    #declare SaturnRingCameraPos=CameraPos-SaturnPos;
//    PrintVector("SaturnRingCameraPos",SaturnRingCameraPos)
    #declare SaturnRingSunSide=vdot(vnormalize(SaturnPole),vnormalize(SaturnRingSunPos));
//    PrintNumber("SaturnRingSunSide",SaturnRingSunSide)
    #declare SaturnRingCameraSide=vdot(vnormalize(SaturnPole),vnormalize(SaturnRingCameraPos));
//    PrintNumber("SaturnRingCameraSide",SaturnRingCameraSide)
    #declare SaturnRingSunSide=(SaturnRingSunSide/abs(SaturnRingSunSide));
//    PrintNumber("SaturnRingSunSide",SaturnRingSunSide)
    #declare SaturnRingCameraSide=(SaturnRingCameraSide/abs(SaturnRingCameraSide));
//    PrintNumber("SaturnRingCameraSide",SaturnRingCameraSide)
    #if(SaturnRingSunSide=SaturnRingCameraSide)
      #declare SunSide=0;
    #else
      #declare SunSide=SaturnRingSunSide;
    #end    
//    PrintNumber("SunSide",SunSide)
  #else
    #declare SunSide=0;
  #end
#end

#if(ObjDetail[Sa]>=3)
  #ifndef (SpokePos) #declare SpokePos=0; #end
  #declare SpokePigment=pigment {
    radial
    color_map {
      [0.0 color rgbt <1,1,1,0.1>]
      [0.2 color rgbt <0,0,0,0.0>]
      [0.8 color rgbt <0,0,0,0.0>]
      [1.0 color rgbt <1,1,1,0.1>]
    }
    frequency 6 turbulence 3.75
    translate y*SpokePos
  }

  #declare SpokeWeight=0.2;

  #declare Ring=union {
    #if(SunSide!=0) 
      disc{
        <0,-SunSide*0.0001,0>,y,14.0154,7.4400
	#declare Opacity=0.05;
	#declare BacklightColor=<0.5,0.45,0.4>;
        pigment {color rgbt BacklightColor/Opacity+<0,0,0,1-Opacity>}
        finish {ambient 0 diffuse 1 specular 0}
        double_illuminate
      }
    #end 
    #declare DeltaR=(14.0154-7.4400)/915;
    #declare LitVal=array[61]
    #declare TranVal=array[61]
    #declare TranGamma=2.5;
    #fopen Inf "Data/SaturnRing.txt" read
    #declare I=0;
    #declare BOuter=5;
    #declare BInner=10;
    #while(I<15)
      #declare J=0;
      #while(J<61)
        #declare LitVal[J]=0;
        #declare TranVal[J]=0;
        #read(Inf,LitVal[J])
        #read(Inf,TranVal[J])
        #declare J=J+1;
      #end
      #declare OuterRad=14.0154-DeltaR*(I*61);
      #declare InnerRad=14.0154-DeltaR*(((I+1)*61));
      #declare Width=OuterRad-InnerRad;
      #declare Wavelength=Width*2;
      disc {
        0,y,OuterRad,InnerRad
        #if((I>=BOuter) * (SpokeWeight>0) * (I<=BInner) *( abs(SunSide)=0))
        pigment { average pigment_map { [SpokeWeight SpokePigment][1-SpokeWeight
        #else
        pigment {
        #end
          wood
          frequency 1/Wavelength
          phase -(InnerRad/Wavelength)+0.5
          color_map {
            #declare J=0;
            #while(J<61)
              [J/61     rgbt <1*LitVal[J]*2,0.88*LitVal[J]*2,0.82*LitVal[J]*2,TranVal[J]>]
//              #declare K=0;
//              #while(K<2)
//                [(J+K/2)/61 rgbt<1*LitVal[J]*2,0.88*LitVal[J]*2,0.82*LitVal[J]*2,TranVal[J]>+(0.5*rand(Seed)-0.25)]
//                #declare K=K+1;
//              #end
              #declare J=J+1;
            #end
          }
          rotate x*90
        #if(!((I>=BOuter)*(I<=BInner)*(abs(SunSide)=0)))
        }
        #else
        ] }}
        #end
        finish {
          ambient 0
        }
      }
      #declare I=I+1;
    #end
    #fclose Inf
  }
#else
  #if(ObjDetail[Sa]>=2)
    #declare Ring=disc {
      0,y,14.0154,7.4400
      pigment {color rgb<1,1,0>}
    }
  #end
#end

#declare SaturnModel=
#if(ObjDetail[Sa]>=2)
  union {
    object { Ring scale 10000 rotate x*90}
#end
    sphere {
      <0,0,0>,ASaturn/10000
      #if(ObjDetail[Sa]>=1)
        pigment {
          image_map {
            png "Data/SaturnMap.png"
            map_type spherical
          }
        }
      #else
        pigment {color rgb<1,1,0>}
      #end
      finish { ambient 0 }
      scale <1, BSaturn/ASaturn,1>
      scale 10000
    }
#if(ObjDetail[Sa]>=2)
  }
#end




