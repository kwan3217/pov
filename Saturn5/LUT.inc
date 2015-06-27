//LUT.inc
//Launch Umbilical Tower

#include "colors.inc"
#include "metals.inc"

#declare BoxGirder=difference {
  box {
    <-1,0,-1>,<1,1,1>
  }
  box {
    <-0.95,-0.01,-0.95>,<0.95,1.01,0.95>
  }
}

#declare FlangeGirder=union {
  box {
    <-0.05,0,-0.975>,<0.05,1,0.975>
  }
  box {
    <-1,0,-1>,<1,1,-0.95>
  }
  box {
    <-1,0,1>,<1,1,0.95>
  }
}

#declare Pipe=difference {
  cylinder {
    <0,0,0>,<0,1,0>,1
  }
  cylinder {
    <0,-0.01,0>,<0,1.01,0>,0.95
  }
}

#declare Diagonal=union {
  object {
    Pipe
    scale <0.5,24,0.5>
    translate y*2
    rotate -z*45
    translate <-20,0,-20>
  }
  box {
    <-19,0,-20.25>,<-17,3,-19.75>
  }
  box {
    <-3,17,-20.25>,<0,19,-19.75>
  }
}

#declare QuarterDeckAndPipe=union {
  object {
    FlangeGirder
    scale <0.5,40,0.5>
    rotate -z*90
    rotate x*90
    translate <-20,19.5,-20>
  }
  object {
    Diagonal
  }
  object {
    Diagonal
    scale <-1,1,1>
  }
  object {
    Pipe
    scale <0.25,28,0.25>
    rotate x*90
    rotate y*45
    translate <-20,19.5,0>
  }
}

#declare I=0;
#declare DeckAndPipe=union {
  #while(I<4)
  object {
    QuarterDeckAndPipe
    rotate y*I*90
  }
  #declare I=I+1;
  #end
  object {
    FlangeGirder
    scale <0.5,40,0.5>
    rotate x*90
    translate <-10,19.5,-20>
  }
  object {
    FlangeGirder
    scale <0.5,40,0.5>
    rotate x*90
    translate <10,19.5,-20>
  }
  union {
    #declare I=0;
    #while(I<500)
      cylinder {
        <-20+(I*40/500),0,-20>,<-20+(I*40/500),0,20>,0.01
      }
      #declare I=I+1;
    #end
    pigment {color rgb 0.5}
  }
  union {
    #declare I=0;
    #while(I<50)
      cylinder {
        <-20,0,-20+(I*40/50)>,<20,0,-20+(I*40/50)>,0.01
      }
      #declare I=I+1;
    #end
    pigment {color rgb 0.5}
  }
}

#declare FlangeSection=union {
  object {
    FlangeGirder
    scale <0.5,20,0.5>
    translate <-20,0,-20>
  }
  object {
    FlangeGirder
    scale <0.5,20,0.5>
    translate <-20,0,20>
  }
  object {
    FlangeGirder
    scale <0.5,20,0.5>
    translate <20,0,-20>
  }
  object {
    FlangeGirder
    scale <0.5,20,0.5>
    translate <20,0,20>
  }
  object {
    DeckAndPipe
  }
}

#declare BoxSection=union {
  object {
    BoxGirder
    scale <0.5,20,0.5>
    translate <-20,0,-20>
  }
  object {
    BoxGirder
    scale <0.5,20,0.5>
    translate <-20,0,20>
  }
  object {
    BoxGirder
    scale <0.5,20,0.5>
    translate <20,0,-20>
  }
  object {
    BoxGirder
    scale <0.5,20,0.5>
    translate <20,0,20>
  }
  object {
    DeckAndPipe
  }
}

#declare SlantColumn=object {
  BoxGirder
  scale <0.5,80,0.5>
  matrix <1,0,0,
          10/80,1,35.5/80,
          0,0,1,
          0,0,0>
  translate <-30,0,-55.5>
  pigment {
    gradient y
    color_map {
      [0 color White]
      [10/80 color White]
      [10/80 color Gray50]
      [30/80 color Gray50]
      [30/80 color Red]
      [1 color Red]
    }
    scale <1,80,1>
  }
}


#declare LUT=union {
object {
  SlantColumn
}

object {
  SlantColumn
  scale <-1,1,1>
}

object {
  SlantColumn
  scale <-1,1,-1>
}

object {
  SlantColumn
  scale <1,1,-1>
}

difference {
  box {
    <-30,0,-67.5>,<130,-22,67.5>
  }
  box {
    <-22.5,1,-22.5>,<22.5,-23,22.5>
    translate x*80
  }
  pigment {color rgb 0.5}
}


#declare I=0;
#while(I<15)
object {
  #if(I*20+80<279)
  FlangeSection
  #else
  BoxSection
  #end
  translate <0,80+I*20,0>
  pigment {color rgb <1,0,0>}
}
#declare I=I+1;
#end
  rotate -y*90
  translate <0,10,-80>
}

