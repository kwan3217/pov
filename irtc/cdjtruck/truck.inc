// ==== Standard POV-Ray Includes ====
#include "metals.inc"
#include "colors.inc"


#declare Tire=union {
  cylinder {
    <0,1,-0.125>,<0,1,0.125>,0.75
    pigment {rgb <0.2, 0.2,0.2>}
  }
  cylinder {
    <0,1,-0.15>,<0,1,0.15>,0.35
    texture {T_Chrome_5E}
  }
}

#declare Box= union {
  //windshield
  box {
    <-0.75,1.9,0.05>,<0,2.8,1.95>
    pigment {Blue}
  }
  //roof of cab
  box {
    <-0.80,2.8,0.00>,<0,2.9,2.00>
    pigment {Yellow}
  }
  difference {
    box {
      <-1.5,1,0.00>,<3.75,3.1,2.00>
    }
    //truck bed
    box {
      <0.5,2.1,0.1>,<4,3.2,1.9>
    }
    //Cab
    box {
      <-2,2.2,-0.5>,<0,3.2,2.5>
    }
    box {
      <-2,2.9,-0.5>,<0.2,3.2,2.5>
    }
    //seperation between bed and cab
    box {
      <0.1,0.0,-0.5>,<0.25,3.2,2.5>
    }
    //wheelwells
    cylinder {
      <-0.5,1,-0.5>,<-0.5,1,0.4>,0.8
    }
    cylinder {
      <-0.5,1,1.6>,<-0.5,1,2.5>,0.8
    }
    //space for roundness of hood
    box {
      <-1.6,1.9,-0.5>,<0,2.3,0.3>
    }
    box {
      <-1.6,1.9,1.7>,<0,2.3,2.5>
    }
    plane {
      y,0
      rotate z*12
      translate y*0.8
    }
  }
  cylinder {
    <-1.5,1.9,0.3>,<0,1.9,0.3>,0.3
  }
  cylinder {
    <-1.5,1.9,1.7>,<0,1.9,1.7>,0.3
  }
  pigment {rgb <1,1,0>}
}

#declare Truck=union {
  text
  {
    ttf          
    "times.ttf",  
    "Zonka",   
    0.01,           
    0            
    translate <0.5,2,-0.01>
  }
  text
  {
    ttf          
    "times.ttf",  
    "Zonka",   
    0.01,           
    0
    rotate y*180            
    translate <3.25,2,2.01>
  }
  object {Tire translate <-0.5,-0.2,0>}
  object {Tire translate <3,-0.2,0>}
  object {Tire translate <-0.5,-0.2,2>}
  object {Tire translate <3,-0.2,2>}
  object {Box}
  cylinder {
    <-1.6,1.5,0.25>,<-1,1.5,0.25>,0.2
    texture {T_Chrome_5E}
  }
  cylinder {
    <-1.6,1.5,1.75>,<-1,1.5,1.75>,0.2
    texture {T_Chrome_5E}
  }
  //radiator frame
  cylinder {
    <-1.5,1,0.6>,<-1.5,2,0.6>,0.03
    texture {T_Chrome_5E}
  }
  cylinder {
    <-1.5,1,1.4>,<-1.5,2,1.4>,0.03
    texture {T_Chrome_5E}
  }
  cylinder {
    <-1.5,2,0.6>,<-1.5,2,1.4>,0.03
    texture {T_Chrome_5E}
  }
  cylinder {
    <-1.5,1,0.6>,<-1.5,1,1.4>,0.03
    texture {T_Chrome_5E}
  }
  #declare I=1.05
  #while(I<1.99)
    cylinder {
      <-1.5015,I,0.6>,<-1.5015,I,1.4>,0.015
      texture {T_Chrome_5E}
    }
    #declare I=I+0.05
  #end
  //radiator grill
  box {
    <-1.51,2,0.6>,<-1.5,1,1.4>
    pigment {Gray10}
  }
  //drive train
  union {
    //drive shaft
    cylinder {
      <-0.5,0.9,1>,<3,0.9,1>,0.1
    }
    //front axle
    cylinder {
      <-0.5,0.9,0>,<-0.5,0.9,2>,0.1
    }
    //rear axle
    cylinder {
      <3,0.9,0>,<3,0.9,2>,0.1
    }
    //differential
    sphere {
      <3,0.9,1>,0.25
    }
    cone {
      <3,0.9,1>,0.25,<2.5,0.9,1>,0
    }
    //oilpan
    box {
      <-1,0.75,0.7>,<-0.25,1,1.3>
    }
    texture {T_Chrome_5E}
  }
  //frame
  union {
    box {
      <-1.5,0.8,0.3>,<3.6,1,0.4>
    }
    box {
      <-1.5,0.8,1.7>,<3.6,1,1.6>
    }
    pigment {Gray50}
  }
  //bumper
  union {
    box {
      <-1.5,0.8,0>,<-1.6,1,2>
    }
    box {
      <3.6,0.8,0>,<3.7,1,2>
    }
    texture {T_Chrome_5E}
  }
  translate <-2,-1.55,-1.0>
}
