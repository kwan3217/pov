#version unofficial MegaPov 0.71;

#include "F1.inc"

#declare FlagStar=object {
  prism {
    linear_spline
    0,1,10,
    #local Short=0.3249196962329;
    #local I=0;
    #while(I<5)
      <sin(radians(I*72)),cos(radians(I*72))>,
      <sin(radians(I*72+36))*Short,cos(radians(I*72+36))*Short>
      #if(I!=4) , #end
      #local I=I+1;
    #end
  }
  rotate -x*90
  translate z*0.5
  scale <3,3,45>
}

#declare BlueField=difference {
  box {
    <0,0,-20>,<60,42,20>
  }
  #local I=0;
  #local Ai=10;
  #local Bi=5;
  #local Aj=8;
  #local Bj=5;
  #local Ao=5;
  #local Bo=4;
  #while(I<6)
    #local J=0;
    #while(J<5)
      object {FlagStar translate <I*Ai+Bi,J*Aj+Bj,0> }
      #if(I<5 & J<4)
        object {FlagStar translate <I*Ai+Bi+Ao,J*Aj+Bj+Bo,0> }
      #end
      #declare J=J+1;
    #end
    #declare I=I+1;
  #end
  translate <-69,36,-396/2>
}

#declare Stripes=difference {
  union {
    #declare I=0;
    #while(I<7)
      box {
        <-69,I*12,-20>,<69,I*12+6,20>
      }
      #declare I=I+1;
    #end
  }
  box {
    <-0.01,0,-21>,<60,42.01,21>
    translate <-69,36,0>
  }
  translate -z*396/2
}

#declare FourFields=union {
  object {BlueField rotate y*000}
  object {BlueField rotate y*090}
  object {BlueField rotate y*180}
  object {BlueField rotate y*270}
  translate y*1113.75
  rotate y*22.5
}

#declare FourStripes=union {
  object {Stripes rotate y*000}
  object {Stripes rotate y*090}
  object {Stripes rotate y*180}
  object {Stripes rotate y*270}
  translate y*1113.75
  rotate y*22.5
}


#declare UsaU=union {
  box {
    <-25,60,-10>,<-13,25,10>
  }
  box {
    <25,60,-10>,<13,25,10>
  }
  difference {
    cylinder {
      <0,25,-10>,<0,25,10>,25
    }
    cylinder {
      <0,25,-10.01>,<0,25,10.01>,13
    }
    plane {
      y,25
      inverse
    }
  }
  translate <0,546.2,-396/2>
}

#declare UsaSHalf=union {
  difference {
    cylinder {
      <0,12,-10>,<0,12,10>,18
    }
    cylinder {
      <0,12,-10.01>,<0,12,10.01>,6
    }
    plane {
      x,0
      inverse
    }
    translate -x*7
  }
  difference {
    cylinder {
      <0,12,-10>,<0,12,10>,18
    }
    cylinder {
      <0,12,-10.01>,<0,12,10.01>,6
    }
    plane {
      -x,0
      inverse
    }
    plane {
      y,0
      rotate z*30
      translate y*9
    }
    translate x*7
  }
  box {
    <-7,-6,-10>,<0,6,10>
  }
  box {
    <-7,30,-10>,<7,18,10>
  }
}

#declare UsaS=union{
  object {UsaSHalf}
  object {UsaSHalf rotate z*180}
  translate y*30
  translate <0,456.2,-396/2>
}

#declare UsaA=union {
  box {
    <0,0,-10>,<12,60,10>
    matrix <1,0,0,
            19/60,1,0,
            0,0,1,
            0,0,0>
   translate -x*25
  }
  box {
    <0,0,-10>,<12,60,10>
    matrix <1,0,0,
            19/60,1,0,
            0,0,1,
            0,0,0>
   translate -x*25
   scale <-1,1,1>
  }
  box {
    <-13,12,-10>,<13,24,10>
  }
  translate <0,366.2,-396/2>
}

#declare Usa=union {
  object {UsaU}
  object {UsaS}
  object {UsaA}
}

#declare Usa4=union {
  object {Usa rotate y*  0}
  object {Usa rotate y* 90}
  object {Usa rotate y*180}
  object {Usa rotate y*270}
  rotate y*22.5
}

#declare QuadMarksBlock=union {
  #declare I=0;
  #while(I<4)
    box{
      <-(2.5+(I+1)*3),370,-10.01>,<(2.5+(I+1)*3),398,10.01>
      translate -z*396/2
      rotate -y*(90+90*(I+1))
    }
    #declare I=I+1;
  #end
}

#declare QuadMarksField=union {
  #declare I=0;
  #while(I<4)
    box{
      <-(1.5+(I+1)*3),371,-10.01>,<(1.5+(I+1)*3),397,10.01>
      translate -z*396/2
      rotate -y*(90+90*(I+1))
    }
    #declare I=I+1;
  #end
}

#declare QuadMarksNumerals=union {
  #declare I=0;
  #while(I<4)
    #declare J=0;
    union {
      #while(J<(I+1))
        box {
          <J*6,374,-10.02>,<J*6+3,394,10.02>
        }
        #declare J=J+1;
      #end
      translate -x*(1.5+(J-1)*3)
      translate -z*396/2
      rotate -y*(90+90*(I+1))
    }
    #declare I=I+1;
  #end
}

#declare QuadMarksBlack=union {
  difference {
    object {QuadMarksBlock}
    object {QuadMarksField}
  }
  object {QuadMarksNumerals}
}

#declare QuadMarksWhite=difference {
  object {QuadMarksField}
  object {QuadMarksNumerals}
}

#declare Serial=text {
  ttf "verdanab.ttf"
  "S-lC-3"
  20/9,0
  scale 9
  translate -z*(396/2+10)
  translate -x*20
  translate y*384
  rotate -y*23.5
}

#declare Serial4=union {
  #declare I=0;
  #while(I<4)
    object {Serial rotate y*I*90}
    #declare I=I+1;
  #end
}

#declare RP1White=union {
  object {QuadMarksWhite}
  object {Serial4}
}

#declare RoundCorner=difference {
  cylinder {
    <0,0,0>,<0,0,-4>,6
  }
  cylinder {
    <0,0,0.001>,<0,0,-5>,3
  }
  plane {
    y,0
  }
  plane {
    x,0
  }
  bounded_by{box{<0,0,0>,<6,6,-4>}}
}

#declare FinLetterBox=difference {
  box {
    <0,0,0>,<22,32,-4>
  }
  box {
    <1,1,0.001>,<21,31,-5>
  }
}


#declare FinABlack=union {
  object {FinLetterBox}
  box {
    <0,0,0>,<3,24,-4>
    matrix <1,0,0,
          -5/24,1,0,
           0,0,1,
           15,4,0>
  }
  box {
    <0,0,0>,<3,24,-4>
    matrix <1,0,0,
           5/24,1,0,
           0,0,1,
           4,4,0>
  }
  box {
    <6,9,0>,<16,12,-4>
  }
}

#declare FinBBlack=union {
  object {FinLetterBox}
  box {
    <4,4,0>,<7,28,-4>
  }
  box {
    <7,4,0>,<12,7,-4>
  }
  box {
    <7,25,0>,<12,28,-4>
  }
  box {
    <7,14.5,0>,<12,17.5,-4>
  }
  object {
    RoundCorner rotate -z*90 translate <12,10,0>
  }
  object {
    RoundCorner rotate -z*90 translate <12,20.5,0>
  }
  object {
    RoundCorner translate <12,11.5,0>
  }
  object {
    RoundCorner translate <12,22,0>
  }
  box {
    <15,11.5,0>,<18,10,-4>
  }
  box {
    <15,20.5,0>,<18,22,-4>
  }
}

#declare FinCBlack=union {
  object {FinLetterBox}
  box {
    <4,10,0>,<7,22,-4>
  }
  box {
    <10,4,0>,<12,7,-4>
  }
  box {
    <10,25,0>,<12,28,-4>
  }
  object {
    RoundCorner rotate -z*90 translate <12,10,0>
  }
  object {
    RoundCorner translate <12,22,0>
  }
  object {
    RoundCorner rotate -z*180 translate <10,10,0>
  }
  object {
    RoundCorner rotate -z*270 translate <10,22,0>
  }
  box {
    <4,22,0>,<7,10,-4>
  }
}

#declare FinDBlack=union {
  object {FinLetterBox}
  box {
    <4,4,0>,<7,28,-4>
  }
  box {
    <7,4,0>,<12,7,-4>
  }
  box {
    <7,25,0>,<12,28,-4>
  }
  object {
    RoundCorner rotate -z*90 translate <12,10,0>
  }
  object {
    RoundCorner translate <12,22,0>
  }
  box {
    <15,22,0>,<18,10,-4>
  }
}

#declare LetterPos=<239+44+27,82+44,0>;
#declare Letters=array[4] {FinCBlack,FinBBlack,FinABlack,FinDBlack}
#macro TwoFinBlack(Letter)
union {
  object {Letter}
  object {Letter rotate y*180 translate x*22}
  translate LetterPos
}
#end

#declare TwoFinWhite=box {
  <0,0,-4>,<22,32,4>
  translate LetterPos
}

#declare Fin=difference {
  prism {
    linear_spline 0,1,4
    <62,246>,<261,246>,<261,142>,<0,0>
    #local Scl=44/(261-177);
    translate -y*0.5
    scale <1,6/Scl,1>
  }
  cylinder {
    <0,4/Scl,187>,<262,4/Scl,187>,2/Scl
  }
  cylinder {
    <0,-4/Scl,187>,<262,-4/Scl,187>,2/Scl
  }
  #local I=0;
  #while(I<20)
    cylinder {
      <I*20,3.5/Scl,187>,<I*20-42,3.5/Scl,0>,0.6/Scl
    }
    cylinder {
      <I*20,-3.5/Scl,187>,<I*20-42,-3.5/Scl,0>,0.6/Scl
    }
    cylinder {
      <I*20,3.5/Scl,187>,<I*20,3.5/Scl,247>,0.6/Scl
    }
    cylinder {
      <I*20,-3.5/Scl,187>,<I*20,-3.5/Scl,247>,0.6/Scl
    }
    #local I=I+1;
  #end
  translate -z*246
  scale Scl
  rotate x*90
  translate <239,82,0>
}

#declare S1CFairing=union {
  cone {
    <0,48.5,-182>,101.17,<0,420,-182>,0
    open
  }
  #declare I=0;
  #while(I<19)
    cylinder {
      <101.17,48.5,0>,<0,420,0>,0.5
      rotate y*I*10
      translate -z*182
    }
    #declare I=I+1;
  #end
  clipped_by {
    cylinder {
      <0,0,0>,<0,420,0>,396/2
      inverse
    }
  }
  texture {
    gradient y texture_map{
      [0.5 pigment {radial color_map {[0.5 rgb 0.2][0.5 White]} frequency 4}]
      [0.5 T_Chrome_3A]
    }
    scale <1,500,1> translate y*(116-500)
  }
}

#ifndef(ShowInterstage) #declare ShowInterstage=true; #end

#declare S1C=union {  //S-1C Stage
  //Fairings and fins
  #local I=0;
  #while(I<4)
    union {
      object {S1CFairing}
      object {
        Fin
        texture {
          object {
            TwoFinWhite
            texture {T_Chrome_3A}
            texture {
              object {
                TwoFinBlack(Letters[I])
                texture {pigment {color rgb 1}}
                texture {pigment {color rgb 0.2}}
              }
            }
          }
        }
      }
      rotate y*(45+I*90)
    }
    #local I=I+1;
  #end
  //Center Engine
  object {F1 rotate y*45}
  object {F1 translate -x*182 rotate y*045}
  object {F1 translate -x*182 rotate y*135}
  object {F1 translate -x*182 rotate y*225}
  object {F1 translate -x*182 rotate y*315}
  //Thrust Structure
  union {
    cylinder {
      <0,116,0>,<0,345.7,0>,396.8/2
      open
    }
    Stringers(116+12,345.7,396.8/2,216)
    pigment {
      radial color_map{[0.5 rgb 0.2][0.5 White]}
      frequency 4
      phase 0.5
    }
  }
  //RP1 Tank
  object {
    Hemisphere
    scale <1,-1,1>
    scale <396/2,120.7,396/2>
    translate <0,345.7,0>
    pigment { color rgb<0.5,0.5,0.6>}
  }
  cylinder {
    <0,345.7,0>,<0,628.8>,396/2
    open
    pigment {
      object {Usa4
        pigment {
          object {RP1White
            pigment {
              object {QuadMarksBlack
                pigment {
                  radial color_map{[0.5 rgb 0.2][0.5 White]}
                  frequency 4
                  phase 0.5
                }
                pigment {color rgb 0.2}
              }
            }
            pigment {color White}
          }
        }
        pigment {color Red}
      }
    }
  }
  object {
    Hemisphere
    scale <396/2,113.2,396/2>
    translate <0,628.8,0>
    pigment { color rgb<0.5,0.5,0.6>}
  }
  //Intertank
  union {
    cylinder {
      <0,628.8,0>,<0,885.2,0>,396.8/2
      open
    }
    Stringers(628.8,885.2,396.8/2,108)
    pigment {color rgb 1}
  }
  //Lox Tank
  object {
    Hemisphere
    scale <1,-1,1>
    scale <396/2,113.2,396/2>
    translate <0,885.2,0>
    pigment { color rgb<0.5,0.5,0.6>}
  }
  cylinder {
    <0,885.2,0>,<0,1420.3,0>,396/2
    open
    pigment {
      object {FourFields
        pigment {
          object {FourStripes
            pigment {color rgb 1 }
            pigment {color rgb <1,0,0> }
          }
        }
        pigment {color Blue}
      }
    }
  }
  object {
    Hemisphere
    scale <396/2,120.7,396/2>
    translate <0,1420.3,0>
    pigment { color rgb<0.5,0.5,0.6>}
  }
  //Forward Skirt
  union {
    Stringers(1420.3,1564,396.8/2,216)
    cylinder {
      <0,1420.3,0>,<0,1541,0>,396.8/2
      open
    }
    pigment {
      radial color_map{[0.5 rgb 0.2][0.5 White]}
      frequency 4
      phase 0.5
    }
  }
  //Interstage 1-2 small
  cone {
    <0,1541.3,0>,396/2,<0,1564,0>,397/2
    open
    pigment {
      radial color_map{[0.5 rgb 0.2][0.5 White]}
      frequency 4
      phase 0.5
    }
  }
}

#declare LH2Line=cone {
  <0,1722,396.8/2>,0,<0,1722+72,396.8/2+6>,12
  clipped_by {
    plane {y,1760}
  }
  pigment {color White}
}


//flight seperation of interstage is between cones
#declare Interstage=union {
  cone {
    <0,1564,0>,397/2,<0,1760,0>,396/2
    open
  }
  Stringers(1564,1760,396/2,216)
  object {LH2Line rotate y*45}
  object {LH2Line rotate y*80}
  object {LH2Line rotate y*135}
  object {LH2Line rotate y*225}
  object {LH2Line rotate y*315}
  pigment {
    radial color_map{[0.5 rgb 0.2][0.5 White]}
    frequency 4
    phase 0.5
  }
}
