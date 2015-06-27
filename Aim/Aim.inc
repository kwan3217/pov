#include "metals.inc"
#include "LocLook.inc"

#ifndef(SofieDeploy) #declare SofieDeploy=0; #end
#ifndef(CipsDeploy) #declare CipsDeploy=0; #end
#include "AIM Bus.inc"
#ifndef(Deploy) #declare Deploy=1; #end
#ifndef(CipsOn) #declare CipsOn=0; #end
#ifndef(CipsColor) #declare CipsColor=<1,1,0,0.8>; #end

#declare GeBlack=texture {
  pigment {color rgb 0.75}
  finish {phong 1 phong_size 3}
	normal {wrinkles 1 scale 5}
}

#declare SilverTeflon=texture {
  T_Chrome_5A
	normal {bumps 1}
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
		pigment {rgb <0.5,0.25,0>}
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



#declare PanelTex=texture {
  pigment {
    color rgb <0.25,0.25,0.375>
  }
}

#declare PanelFace=prism {
  0,0.25,7
  < 0,   10.25>,
	<35,   10.25>,
	<50,    7.00>,
	<50,  - 7.00>,
	<35,  -10.25>,
	< 0,  -10.25>,
	< 0,   10.25>
}


#declare CellPattern=array[15][6] {
  { 0.0,12, 1, 0.0, 0, 0}, /*  0 */
  { 0.0, 7,-1, 7.5, 5, 1}, /*  1 */
	{ 0.2,12,-1, 0.0, 0, 0}, /*  2 */
	{ 0.0, 2, 1, 2.5,10,-1}, /*  3 */
	{ 0.0, 3,-1, 3.5, 9, 1}, /*  4 */
	{ 0.2,12, 1, 0.0, 0, 0}, /*  5 */
	{ 0.0, 8,-1, 8.5, 4,-1}, /*  6 */
	{ 0.2, 5,-1, 7.2, 5,-1}, /*  7 */
	{ 0.0,11,-1,11.5, 1, 1}, /*  8 */
  { 0.0, 8, 1, 8.5, 4,-1}, /*  9 */
  { 0.8,11, 1, 0.0, 0, 0}, /* 10 */
	{ 1.0, 4,-1, 5.5, 6, 1}, /* 11 */
	{ 1.3,10,-1, 0.0, 0, 0}, /* 12 */
	{ 2.0, 3, 1, 5.5, 5,-1}, /* 13 */
	{ 2.5, 8, 1, 0.0, 0, 0}, /* 14 */
}
#declare Seed=seed(1);
#declare PanelPart=union {
  object {
    PanelFace
    pigment {color rgb 1}
    translate y*0.25
  }
  object {
    PanelFace
    texture {PanelTex}
  }
	#declare Row=0;
	#while(Row<15) 
	  #declare Col=0;
		#while(Col<CellPattern[Row][1]) 
		  object {
			  Cell
				scale <1,1,-CellPattern[Row][2]>
				rotate z*2*(rand(Seed)-0.5)
				rotate x*2*(rand(Seed)-0.5)
				translate <Row*3.33,0,(Col+CellPattern[Row][0])*2*0.82-9.5>
			}
			#declare Col=Col+1;
		#end
		object{
		  StringEnd
  		translate <Row*3.33,0,(CellPattern[Row][0])*2*0.82-9.5>
    }			
		object{
		  StringEnd
  		translate <Row*3.33,0,(CellPattern[Row][0]+CellPattern[Row][1])*2*0.82-9.5>
    }			
    #if(CellPattern[Row][5]!=0)
	  	#declare Col=0;
			#while(Col<CellPattern[Row][4]) 
		  	object {
			  	Cell
					scale <1,1,-CellPattern[Row][5]>
  				translate <Row*3.33,0,(Col+CellPattern[Row][3])*2*0.82-9.5>
				}
				#declare Col=Col+1;
			#end
			object{
		  	StringEnd
  			translate <Row*3.33,0,(CellPattern[Row][3])*2*0.82-9.5>
    	}			
			object{
		  	StringEnd
  			translate <Row*3.33,0,(CellPattern[Row][3]+CellPattern[Row][4])*2*0.82-9.5>
    	}			
		#end
	  #declare Row=Row+1;
	#end
  cylinder {
    <23,0,0>,<23,-0.5,0>,1
    texture {WhitePlastic}
    scale <1/0.92,1,1>
  }
  cylinder {
    <23,0.75,0>,<23,-0.75,0>,0.5
    texture {BlackPaint}
    scale <1/0.92,1,1>
  }
  cylinder {
    <23,0,11.0>,<25,0,11.0>,0.75
    texture {Gold}
  }
  cylinder {
    <0.01,0,10.9>,<2,0,10.9>,0.75
    texture {Gold}
  }
  rotate y*180
  rotate -z*90
  translate -x*0.5
  scale <1,0.92,1>
}

#declare CipsFovSize=44*370/380;
#declare CipsFwdAngle=39;
#declare CipsSideAngle=19;

#declare CipsFOV=intersection {
  plane {
    -x,0
    rotate z*CipsFovSize/2
  }
  plane {
    x,0
    rotate -z*CipsFovSize/2
  }
  plane {
    z,0
    rotate x*CipsFovSize/2
  }
  plane {
    -z,0
    rotate -x*CipsFovSize/2
  }
  translate y*2.0*4.18
}

#declare CipsHollowFOV=difference {
  object {CipsFOV}
  object {CipsFOV translate y*600000}
}

#declare CipsSceneFOV=union {
  object {CipsFOV rotate  z*CipsFwdAngle}
  object {CipsFOV rotate -z*CipsFwdAngle} 
  object {CipsFOV rotate  x*CipsSideAngle} 
  object {CipsFOV rotate -x*CipsSideAngle} 
  translate <4,8.5*4.18,8>
  scale 0.0254
  rotate z*180
}

#declare CipsFOVCluster=object {
  CipsSceneFOV
  pigment {color rgbt CipsColor}
  finish {ambient 0.5}
  no_shadow
}

#declare CipsHollowFOVCluster=union {
  object {CipsHollowFOV rotate  z*CipsFwdAngle}
  object {CipsHollowFOV rotate -z*CipsFwdAngle}
  object {CipsHollowFOV rotate  x*CipsSideAngle}
  object {CipsHollowFOV rotate -x*CipsSideAngle}
  translate <4,8.5*4.18,8>
  scale 0.0254
  rotate z*180
}

#declare Panel=union {
  #local Deploy1=max(0,min(1,Linterp(0/4,0,1/4,1,Deploy)));
  #local Deploy2=max(0,min(1,Linterp(1/4,0,2/4,1,Deploy)));
  #local Deploy3=max(0,min(1,Linterp(2/4,0,3/4,1,Deploy)));
  #local Deploy4=max(0,min(1,Linterp(3/4,0,4/4,1,Deploy)));
  union {
    union {
      object {PanelPart translate z*43/4}
      rotate y*(1-Deploy1)*60
      translate z*43/2
    }
    object {PanelPart translate z*43/4}
    rotate y*(1-Deploy3)*60
    translate z*43/4
  }
  union {
    union {
      union {
        object {PanelPart translate z*43/4}
        rotate y*(1-Deploy1)*60
        translate z*43/2
      }
      object {PanelPart translate z*43/4}
      rotate y*(1-Deploy2)*60
      translate z*43/2
    }
    object {PanelPart translate z*43/4}
    rotate y*(1-Deploy3)*60
    translate z*43/4
    scale <1,1,-1>
  }
  object {PanelPart}
  rotate z*34*Deploy4
  translate -x*37/2
    
  
}

#declare Aim=union {
  object {AIMBusPlusInstruments rotate y*90}
  #declare SofiePoint0=<-8,42,-6>;
  #declare DeckNorm0=<0,-1,0>;
  object {Panel
    ScaleAlso2(0.0254,SofiePoint0,DeckNorm0)  //Convert to meters
    translate y*0.1
  }
  RotateAlso2(z*180,SofiePoint0,DeckNorm0)  //Rotate to standard position
}

#declare SofieFOV=intersection {
  plane {
    -x,0
    rotate z*1/60
    translate -x*2/3
  }
  plane {
    x,0
    rotate -z*1/60
    translate x*2/3
  }
  plane {
    z,0
    rotate x*3/60
    translate z*2
  }
  plane {
    -z,0
    rotate -x*3/60
    translate -z*2
  }
  plane {
    -y,0
  }
  finish {ambient 0.5}
  no_shadow
  rotate -z*90
  rotate -z*14
  scale 0.0254
  translate SofiePoint0
}

  
