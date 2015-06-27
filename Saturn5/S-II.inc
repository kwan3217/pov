#version unofficial MegaPov 0.71;

#include "J2.inc"

#declare UnitedU=union {
  box {
    <-10,4,-10>,<-6,30,10>
  }
  box {
    <10,4,-10>,<6,30,10>
  }
  box {
    <0,4,-10>,<10,0,10>
    matrix <1,0,0,
            1,1,0,
            0,0,1,
           -4,0,0>
  }
  box {
    <0,4,-10>,<-10,0,10>
    matrix <1,0,0,
           -1,1,0,
            0,0,1,
            4,0,0>
  }
  bounded_by {
    box {
      <-10,0,-10>,<10,30,10>
    }
  }
}

#declare UnitedN=union {
  box {
    <-10,0,-10>,<-6,30,10>
  }
  box {
    <10,0,-10>,<6,30,10>
  }
  box {
    <-1,-1,-10>,<1,1,10>
    matrix <2,0,0,
           -8,15,0,
            0,0,1,
            0,15,0>
  }
  bounded_by {
    box {
      <-10,0,-10>,<10,30,10>
    }
  }
}

#declare UnitedI=union {
  box {
    <-2,30,-10>,<2,0,10>
  }
  bounded_by {
    box {
      <-10,0,-10>,<10,30,10>
    }
  }
}

#declare UnitedT=union {
  box {
    <-2,30,-10>,<2,0,10>
  }
  box {
    <-10,26,-10>,<10,30,10>
  }
  bounded_by {
    box {
      <-10,0,-10>,<10,30,10>
    }
  }
}

#declare UnitedE=union {
  box {
    <-10,30,-10>,<-6,0,10>
  }
  box {
    <-10,26,-10>,<10,30,10>
  }
  box {
    <-10,0,-10>,<10,4,10>
  }
  box {
    <-10,13,-10>,<10,17,10>
  }
  bounded_by {
    box {
      <-10,0,-10>,<10,30,10>
    }
  }
}

#declare UnitedD=union {
  box {
    <-10,0,-10>,<-6,30,10>
  }
  box {
    <10,4,-10>,<6,26,10>
  }
  box {
    <0,4,-10>,<10,0,10>
    matrix <1,0,0,
            1,1,0,
            0,0,1,
           -4,0,0>
  }
  box {
    <0,4,-10>,<10,0,10>
    matrix <1,0,0,
           -1,1,0,
            0,0,1,
            0,26,0>
  }
  box {
    <-10,0,-10>,<0,4,10>
  }
  box {
    <-10,26,-10>,<0,30,10>
  }
  bounded_by {
    box {
      <-10,0,-10>,<10,30,10>
    }
  }
}

#declare UnitedS=union {
  box {
    <-10,26,-10>,<10,30,10>
  }
  box {
    <-10,0,-10>,<10,4,10>
  }
  box {
    <-10,13,-10>,<10,17,10>
  }
  box {
    <6,4,-10>,<10,13,10>
  }
  box {
    <-10,17,-10>,<-6,26,10>
  }
  box {
    <6,22,-10>,<10,26,10>
  }
  box {
    <-6,8,-10>,<-10,4,10>
  }
  bounded_by {
    box {
      <-10,0,-10>,<10,30,10>
    }
  }
}
#declare UnitedA=union {
  box {
    <-7,5,-10>,<7,9,10>
  }
  box {
    <-1,-1,-10>,<1,1,10>
    matrix <2,0,0,
           -4,15,0,
            0,0,1,
            4,15,0>
  }
  box {
    <-1,-1,-10>,<1,1,10>
    matrix <2,0,0,
            4,15,0,
            0,0,1,
           -4,15,0>
  }
  bounded_by {
    box {
      <-10,0,-10>,<10,30,10>
    }
  }
}


#declare UnitedStates=union {
  object {UnitedU translate y*(2335-36*0)}
  object {UnitedN translate y*(2335-36*1)}
  object {UnitedI translate y*(2335-36*2)}
  object {UnitedT translate y*(2335-36*3)}
  object {UnitedE translate y*(2335-36*4)}
  object {UnitedD translate y*(2335-36*5)}

  object {UnitedS translate y*(2335-36*7)}
  object {UnitedT translate y*(2335-36*8)}
  object {UnitedA translate y*(2335-36*9)}
  object {UnitedT translate y*(2335-36*10)}
  object {UnitedE translate y*(2335-36*11)}
  object {UnitedS translate y*(2335-36*12)}
  bounded_by {
    box {
      <-10,30,-10>,<10,-36*13+30,10>
      translate y*2335
    }
  }
  translate -z*396/2
}

#declare UnitedStates4=union {
  object {UnitedStates rotate y* 90}
  object {UnitedStates rotate y*180}
  object {UnitedStates rotate y*270}
  object {UnitedStates rotate y*360}
  rotate -y*22.5
}

#declare LH2Line=union {
  cylinder {
    <0,1722+72,396.8/2+6>,<0,2015.75-72,396.8/2+6>,12
  }
  cone {
    <0,1722,396.8/2>,0,<0,1722+72,396.8/2+6>,12
    clipped_by {
      plane {y,-1760 rotate z*180}
    }
  }
  sphere {
    <0,1722+72,396.8/2+6>,12
  }
  cone {
    <0,2015.75,396.8/2>,0,<0,2015.75-72,396.8/2+6>,12
  }
  sphere {
    <0,2015.75-72,396.8/2+6>,12
  }
  box {
    <-12,1722+72,395/2>,<12,2015.75-72,396.8/2+6>
  }
  bounded_by {
    box {
      <-12,1722,395/2>,<12,2015.72,396.8/2+18>
    }
  }

  pigment {color White}

}

#declare S2=union {
  //S-2 Stage
  //Aft skirt
  union {
    cylinder {
      <0,1760,0>,<0,1803.33,0>,396.8/2
      open
    }
    Stringers(1760,1803.33,396.8/2,216)
    pigment {
      radial color_map{[0.5 rgb 0.2][0.5 White]}
      frequency 4
      phase 0.5
    }
  }
  cone {
    <0,1787,0>,396/2,<0,1676,0>,105
    pigment {color White}
  }

  object {J2 translate <0,1676,0> rotate y*45}
  object {J2 translate <0,1676,105> rotate y*45}
  object {J2 translate <0,1676,105> rotate y*135}
  object {J2 translate <0,1676,105> rotate y*225}
  object {J2 translate <0,1676,105> rotate y*315}
  object {LH2Line rotate y*45}
  object {LH2Line rotate y*135}
  object {LH2Line rotate y*225}
  object {LH2Line rotate y*315}
  object {LH2Line rotate y*80}

  union {
    cylinder {
      <0,1803.33,0>,<0,1846.67,0>,396.8/2
      open
    }
    Stringers(1803.33,1846.67,396.8/2,216)
    pigment {color rgb 0.2}
  }
  union {
    cylinder {
      <0,1890,0>,<0,1846.67,0>,396.8/2
      open
    }
    Stringers(1846.67,1890,396.8/2,216)
    pigment {color White}
  }
  //Propellant Tank
  cylinder {
    <0,1890,0>,<0,2387,0>,396/2
    open
    pigment {
      object {UnitedStates4
        color White
        color Red
      }
    }
  }
  //Forward Skirt
  union {
    cylinder {
      <0,2387,0>,<0,2519,0>,396.8/2
      open
    }
    Stringers(2387,2519,396.8/2,216)
    pigment {color White}
  }
  //Interstage 2-3
  union {
    cone {
      <0,2519,0>,396.8/2,<0,2632.75,0>,328.8/2
      open
    }
    #local I=0;
    #while(I<216)
      cylinder {
        <0,2519,396.8/2>,<0,2632.75,328.8/2>,1.5
        rotate y*I*360/216
      }
      #declare I=I+1;
    #end
    pigment {
      radial color_map{[0.5 rgb 0.2][0.5 White]}
      frequency 2
    }
  }
  union {
    cone {
      <0,2632.75,0>,328.8/2,<0,2746.5,0>,260.8/2
      open
    }
    #local I=0;
    #while(I<216)
      cylinder {
        <0,2632.75,328.8/2>,<0,2746.5,260.8/2>,1.5
        rotate y*I*360/216
      }
      #declare I=I+1;
    #end
    pigment {
      radial color_map{[0.5 rgb 0.2][0.5 White]}
      frequency 1
      phase 0.75
    }
  }
  //Ullage
  #declare I=0;
  #while(I<4)
    union {
      cylinder {
        <0,2519,-328.8/2-6>,<0,2632.75,-328.8/2-6>,6
      }
      box {
        <-6,2519,-328.8/2-6>,<6,2632.75,-326.8/2>
      }
      sphere {
        <0,2632.75,-328.8/2-6>,6
      }
      cylinder {
        <0,2632.75,-328.8/2-6>,<0,2640,-300/2>,6
      }
      pigment {color White}
      rotate y*(I*90+45)
    }
    #declare I=I+1;
  #end
  bounded_by {
    cylinder {
      <0,1676,0>,<0,2747>,420
    }
  }
}
