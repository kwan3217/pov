#macro Clock(T)
  PrintNumber("T:      ",T)
  #local hour=T/3600;
  PrintNumber("Hour:   ",hour)
  #local minute=(T-floor(hour)*3600)/60;
  PrintNumber("Minute: ",minute)
  #local second=(T-floor(hour)*3600-floor(minute)*60);
  PrintNumber("Second: ",second)
  #local third= (T-floor(hour)*3600-floor(minute)*60-floor(second))*60;
  PrintNumber("Third:  ",third)
  #local hourHand=floor(Linterp(0,0,12,60,hour))*6;
  #local minuteHand=Linterp(0,0,60,360,floor(minute));
  #local secondHand=Linterp(0,0,60,360,floor(second));
  #local thirdHand=Linterp(0,0,60,360,third);
  difference {
    cylinder {
      <0,-0.1,0>,<0,0.1,0>,1
    }
    cylinder {
      <0,-0.101,0>,<0,0.101,0>,0.95
    }
    pigment {color rgb <1,1,1>}
  }
  #local I=0;
  union {
    #while(I<12)
      box {
        <-0.025,-0.1,0.9>,<0.025,0,0.975>
        rotate y*I*30
      }
      #local I=I+1;
    #end
    pigment {color rgb <1,1,1>}
  }
  cone {
    <0,0,0>,0.05,<0,0,1/3>,0
    translate <0,-0.1,0>
    rotate y*hourHand
    pigment {color rgb <1,1,1>}
  }
  cone {
    <0,0,0>,0.025,<0,0,2/3>,0
    rotate y*minuteHand
    pigment {color rgb <1,1,1>}
  }
  cylinder {
    <0,0,0>,<0,0,0.94>,0.015
    rotate y*secondHand
    translate <0,0.05,0>
    pigment {color rgb <1,0,0>}
  }
  cylinder {
    <0,0,0.5>,<0,0,0.97>,0.015
    rotate y*thirdHand
    translate <0,0.1,0>
    pigment {color rgb <0,0,1>}
  }
#end 
  
