//Poolball.inc
//requires: BallNumber
#warning "Parsing Pool Ball (poolball.inc)\n"

#declare NumberHeight=0.353;
#declare NumberWidth=0.24;
#if (mod(BallNumber,10)=1) #declare NumberWidth=0.131; #end
#declare OneWidth=0.15;
#declare BallFinish=finish {phong 1 reflection 0.2}

#switch(mod(BallNumber,7))
  #case(1)
    #declare BallColor=<1,1,0>; //Yellow
    #break
  #case(2)
    #declare BallColor=<0,0,1>; //Blue
    #break
  #case(3)
    #declare BallColor=<1,0,0>; //Red
    #break
  #case(4)
    #declare BallColor=<0.75,0,1.0>; //Purple
    #break
  #case(5)
    #declare BallColor=<1,0.5,0>; //Orange
    #break
  #case(6)
    #declare BallColor=<0,1,0>; //Green
    #break
  #case(0)
    #declare BallColor=<0.05,0.05,0.05>; //black
    #break
#end

#if (BallNumber>9)
  #declare NumberWidth=NumberWidth+OneWidth+0.10;
#end

#declare WhiteSpot= intersection {
  sphere {
    0,1
  }
  cylinder {
    <0,0,-1.5>,<0,0,1.5>,0.3
  }
  pigment {color <1,1,1>}
  finish {phong 1 reflection 0.5}
}

 #declare NumberHalf=  text {
    ttf "arial.ttf",
    str(BallNumber,0,0),
    1.5,
    0
    pigment {color <0.05,0.05,0.05>}
    finish {phong 1 reflection 0.5}
    translate -z*1.5
    scale <0.5,0.5,1>
    translate -y*NumberHeight/2
    translate -x*NumberWidth/2
  }


#declare Number=union {
  object {NumberHalf}
  object {NumberHalf rotate y*180}
}


#declare NumberSpot=union {
  difference {
    object {WhiteSpot}
    object {Number}
    pigment {color <1,1,1>}
      finish {BallFinish}
  }
  intersection {
    object {
      WhiteSpot
      pigment {color <0.05,0.05,0.05>}
      finish {BallFinish}
    }
    object {
      Number
      pigment {color <0.05,0.05,0.05>}
      finish {BallFinish}
    }
    pigment {color <0.05,0.05,0.05>}
      finish {BallFinish}
  }
}

#declare StripeBall=union {
  difference {
    sphere {
      0,1
    }
    box {
      <-2,-1/2,-2>,<2,1/2,2>
    }
    pigment {color <1,1,1>}
    finish {BallFinish}
  }
  intersection {
    sphere {
      0,1
    }
    box {
      <-2,-1/2,-2>,<2,1/2,2>
    }
    pigment {color BallColor}
    finish {BallFinish}
  }
}

#if (BallNumber=0)
  #declare BallColor=<1,1,1>;
  #declare Ball=sphere {
    0,1
    pigment {color <1,1,1>}
    finish {BallFinish}
  }
#else
#if (BallNumber>7)
  #declare Ball=union {
    difference {
      object {StripeBall}
      cylinder {
        <0,0,-1.01>,<0,0,1.01>,0.3
        pigment {color White}
      }
    }
    object {
      NumberSpot
    }
//    bounded_by {
      sphere {0,1}
//    }
  }
#else
  #declare Ball=union {
    difference {
      sphere {
        0,1
        pigment {color BallColor}
        finish {BallFinish}
      }
      cylinder {
        <0,0,-1.01>,<0,0,1.01>,0.3
        pigment {color White}
      }
    }
    object {
      NumberSpot
    }
//    bounded_by {
//      sphere {0,1}
//    }
  }
#end
#end

#warning "Done with Pool Ball (poolball.inc)\n"
