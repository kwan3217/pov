#version unofficial Megapov 1.22;

#local Phase=-cos(pi*ShotClockS)*2;
#local vphase=-sin(pi*ShotClockS);
#local State=<vphase*1.5,0,Phase>;
sphere {
  <0,0,Phase>,1
  translate -x*5
  pigment {color rgb <1,0,0>}
}
box {
  <-0.05-0.01*Phase,-0.001,10>,<0.05+0.01*Phase,-0.01,Phase>
  translate -x*5
  pigment {color rgb <1,1,0.5-Phase*0.15>}
}

union {
  union {
    cylinder {
      <-3,0,-2.5>,<-3,0,2.5>,0.05
    }
    cone {
      <-3,0,-2.5>,0.1,<-3,0,-3>,0
    }
    cone {
      <-3,0, 2.5>,0.1,<-3,0, 3>,0
    }
    Fade(<0,0,1,0>,ASDR(0,0.05,0.95,1,0,1,ShotClockN))
  }
  cylinder {
    <-3,0,0>,<100,0,0>,0.05
    Fade(<0,1,0,0>,ASDR(0,0.05,0.95,1,0,1,ShotClockN))
  }
  plane {
    -y,0
    pigment {checker color rgb 1 color rgb 0.75}
  }
  #local LastPhase=-2;
  #local Delta=1/24;
  #local I=Delta;
  merge {
  #while(I<ShotClockS)
    #local ThisPhase=-cos(pi*I)*2;
    cylinder {
      <I-Delta-3,0,LastPhase>,<I-3,0,ThisPhase>,0.05
    }
    sphere {
      <I-3,0,ThisPhase>,0.05
    }
    #local LastPhase=ThisPhase;
    #local I=I+Delta;
  #end
    Fade(<1,0,0,0>,ASDR(0,0.05,0.95,1,0,1,ShotClockN))
  }
  #if(ShotClockS>10)
    translate -x*(ShotClockS-10)
  #end
}

camera {
  right x*16/9
  sky z
  location <0,-9,0.5>
  look_at <0,0,0.5>
}

light_source {
  <20,-20,20>*1000
  color rgb 1
//  area_light <0,2,0>,<0,0,2> 5 5 circular orient adaptive 1
}


