#include "KwanMath.inc"
#include "metals.inc"

#declare WhitePlastic = texture {
   pigment {
      color rgb <1.2, 1.2, 1.2>
   }
   
   finish {
      phong 0.5
   }
}

#declare BrownPlastic=pigment {
  color rgb <0.5,0.25,0>
}
  
#declare Gold = texture {
   pigment {
      color rgb <1, 1, 0.2>
   }
   
   finish {
      phong 0
      
      reflection {
         rgb <0.3, 0.3, 0.3>
      }
   } 
   normal {
     wrinkles 
     scale 5
   }
}
#declare BlackPaint = texture {
   pigment {
      color rgb <0.05, 0.05, 0.05>
   }
}

#declare Aluminum=texture {
  T_Chrome_5C
}

#declare CellTex=texture {
  pigment {
    color rgb 0.05*<1,1,1>
  }
  finish {
    phong 1
  }
}

#declare Cell=union {
  box {
	  <0,0,-0.82>,<3.33,0.1,0.82>
		pigment {BrownPlastic}
	}
  intersection {
	  box {
  	  <0.01,0.1,-0.77>,<3.32,0.2,0.77>
    	texture {CellTex}
		}
		box {
		  -1,1
			scale 2.6
			rotate y*45
			translate <1.67,0,-1.64>
    	texture {CellTex}
    }			
	}
	translate y*0.25
	scale <1,-1,1>
}

#declare StringEnd=box {
  <0,0,-0.87>,<3.33,0.2,-0.77>
  pigment {rgb <1,1,1>}
  translate y*0.25
  scale <1,-1,1>
}

#declare CellPattern=array[8][3] {
  { 0.00,19, 1}, /*  0 */
  { 0.02,19,-1}, /*  1 */
  { 0.00,19, 1}, /*  0 */
  { 0.02,19,-1}, /*  1 */
  { 0.00,19, 1}, /*  0 */
  { 0.02,19,-1}, /*  1 */
  { 0.00,19, 1}, /*  0 */
  { 0.02,19,-1}, /*  1 */
}
#declare Seed=seed(1);
#declare PanelPart=union {
	#declare Row=0;
	#while(Row<8) 
	  #declare Col=0;
		#while(Col<CellPattern[Row][1]) 
		  object {
			  Cell
				scale <1,1,-CellPattern[Row][2]>
				rotate z*2*(rand(Seed)-0.5)
				rotate x*2*(rand(Seed)-0.5)
				translate <Row*3.33,0,(Col+CellPattern[Row][0])*2*0.82>
			}
			#declare Col=Col+1;
		#end
		object{
		  StringEnd
  		translate <Row*3.33,0,(CellPattern[Row][0])*2*0.82>
    }			
		object{
		  StringEnd
  		translate <Row*3.33,0,(CellPattern[Row][0]+CellPattern[Row][1])*2*0.82>
    }			
	  #declare Row=Row+1;
	#end
	translate -y*0.01      
	translate z*0.82
	scale <0.1*3/8,0.1,0.1/(19*0.164)>
	rotate x*180
        scale <13.5,1,18.75>
        rotate -x*90   
        rotate z*90
        translate -x*18.75/2
}

#declare Side=union {
  object {PanelPart}
  object {PanelPart translate y*(13.5+7)}
  union {
    box {
      <-18.75/2,0,0>,<18.75/2,34,0.5>
    }
    box {
      <18.75/2,0,-0.25>,<19.5/2,34,0.6>
    }
    box {
      <-18.75/2,0,-0.25>,<-19.5/2,34,0.6>
    }
    texture {Aluminum}
  }
  union {
    cylinder {
      <-17/2,13.5+2.5,-0.1>,<-17/2,13.5+2.5,0>,0.125
    }
    cylinder {
      <17/2,13.5+2.5,-0.1>,<17/2,13.5+2.5,0>,0.125
    }
    cylinder {
      <-12/2,13.5+2.5,-0.1>,<-12/2,13.5+2.5,0>,0.125
    }
    cylinder {
      <12/2,13.5+2.5,-0.1>,<12/2,13.5+2.5,0>,0.125
    }
    cylinder {
      <-7/2,13.5+2.5,-0.1>,<-7/2,13.5+2.5,0>,0.125
    }
    cylinder {
      <7/2,13.5+2.5,-0.1>,<7/2,13.5+2.5,0>,0.125
    }
    cylinder {
      <-17/2,13.5+3.5,-0.1>,<-17/2,13.5+3.5,0>,0.125
    }
    cylinder {
      <17/2,13.5+3.5,-0.1>,<17/2,13.5+3.5,0>,0.125
    }
    cylinder {
      <-12/2,13.5+3.5,-0.1>,<-12/2,13.5+3.5,0>,0.125
    }
    cylinder {
      <12/2,13.5+3.5,-0.1>,<12/2,13.5+3.5,0>,0.125
    }
    cylinder {
      <-7/2,13.5+3.5,-0.1>,<-7/2,13.5+3.5,0>,0.125
    }
    cylinder {
      <7/2,13.5+3.5,-0.1>,<7/2,13.5+3.5,0>,0.125
    }
    texture {BlackPaint}
  }
} 

#declare Antenna=union {
  cylinder {
    <-3,0,0>,<-3,0.1,0>,3
  }
  cylinder {
    <3,0,0>,<3,0.1,0>,3
  }          
  box {
    <-3,0,-3>,<3,0.1,3>
  }               
  cylinder {
    <0,0,0>,<0,-1,0>,1
  }
  difference {
    box {
      <-1.5,0.1,-1.5>,<1.5,0.3,1.5>
    }
    cylinder {
      <0,0,0>,<0,0.4,0>,1.3
    }
    translate -x*3
    texture {BlackPaint}
  }
  difference {
    box {
      <-1.5,0.1,-1.5>,<1.5,0.3,1.5>
    }
    cylinder {
      <0,0,0>,<0,0.4,0>,1.3
    }
    translate x*3
    texture {BlackPaint}
  }
  texture {Aluminum} 
  rotate y*90
}

#declare SNOE=union {
#declare I=0;
union {
#while(I<6)
  object {
    Side
    translate -z*(39/2*sqrt(3)/2)
    rotate y*I*60
  }  
#declare I=I+1;
#end
  scale 0.0254
}    

//side 0
union {
  box {
    <0,0,0>,<2,2,2>
    rotate -x*45
    translate <-8/2,17.2,0>
    texture {Aluminum}
  }                    
  box {
    <0,0,-0.1>,<5,3,0.1>
    translate <-12/2,17.2,0>
    texture {BlackPaint}
  }                     
  box {
    <-1,13.5,-0.1>,<1,15.5,0.1>
    texture {BlackPaint}
  }                     
  box {
    <-6,13.5,-0.1>,<-4,15.5,0.1>
    texture {BlackPaint}
  }                     
  box {
    <6,13.5,-0.1>,<4,15.5,0.1>
    texture {BlackPaint}
  }                     
  union {
    cylinder {
      <2,19,0>,<4,19,0>,1
    }
    sphere {
      <2,19,0>,1
    }
    sphere {
      <4,19,0>,1
    }
    texture {Aluminum}
  }
  translate -z*(39/2*sqrt(3)/2)
  rotate y*180
  scale 0.0254
}       

//side 2
union {
  cylinder {
    <-4,18.75,-0.1>,<-4,18.75,0.1>,1.5
  }
  cylinder {
    <4,18.75,-0.1>,<4,18.75,0.1>,1.5
  }           
  box {
    <-4,18.75-1.5,-0.1>,<4,18.75+1.5,0.1>
  }
  texture {BrownPlastic} 
  translate -z*(39/2*sqrt(3)/2)
  rotate y*60
  scale 0.0254
}            

//side 3
union {
  box {
    <-6,17.5,-0.1>,<6,20.5,0.1>
    texture {BlackPaint}
  }                     
  translate -z*(39/2*sqrt(3)/2)
  rotate y*0
  scale 0.0254
}            

 

polygon {      
  6
  #declare I=0;
  #while(I<6)
    ,18*<cos(radians(I*60)),sin(radians(I*60))>
    #declare I=I+1;
  #end
  rotate x*90
  translate y*33
  
  texture {Gold}
  scale 0.0254
}

polygon {      
  6
  #declare I=0;
  #while(I<6)
    ,18*<cos(radians(I*60)),sin(radians(I*60))>
    #declare I=I+1;
  #end
  rotate x*90
  translate y*1
  
  texture {Gold}
  scale 0.0254
}

object {
  Antenna  
  translate y*33.5
  scale 0.0254
}
object {
  Antenna  
  rotate x*180
  scale 0.0254
}

cylinder {
  <0,3,0>,<0,-3,0>,23.25/2
  open
  texture {Aluminum}    
  scale 0.0254
} 

}

