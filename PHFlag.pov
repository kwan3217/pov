/*
MALACAÑAN PALACE
MANILA

BY THE PRESIDENT OF THE PHILIPPINES
EXECUTIVE ORDER NO. 23

DESCRIPTION AND SPECIFICATIONS OF THE FILIPINO FLAG

Whereas, section one, Article XIII of the Constitution prescribes what the 
Philippine National Flag should be without giving descriptions and 
specifications; Whereas, Act Numbered Two thousand nine hundred and twenty-eight
describes the construction of the Filipino Flag without the necessary 
specifications of the elements of the flag; Whereas, compliance with this Act 
has not been uniformly carried out and has caused the making of Filipino flags
in disproportionate sizes with incorrect proportions of the different 
allegorical symbols of the flag; and Whereas, to avoid irregularities and 
discrepancies, it is necessary to follow the Constitutional provisions and Act 
Numbered Two thousand nine hundred and twenty-eight with uniformity; Now, there,
I, Manuel L. Quezon, President of the Philippines, do hereby promulgate and 
order that the following specifications for the Philippine National Flag be 
strictly observed by all civil and military branches of the Government:

   1. The maximum length of the flag is twice its width; the minimum length is 
	    twice the altitude of the equilateral triangle,
   2. Any side of the equilateral triangle is as long as the width of the flag.
   3. (See accompanying illustration.) Solid golden sunburst without any 
	    markings - Sun with eight rays, equally spaced; Arc x with Sun ray = Free 
			arc y; two opposite rays in horizontal axis and two in vertical axis; 
			sun's diameter D = W/5; each ray has one major beam, twice as broad as 
			the minor beam on either side; length of major beam R = 5/9D; length of 
			minor beam r = 4/5R.
   4. Three five-pointed golden stars of equal size, each star with one point 
	    directed to the vertex of the angle enclosing it; diameter of 
			circumscribed circle of each str = 5/9D, diameter of inscribed circle of
			each star = 2/9D; distance from each corner = D/2.
			[This does not make a perfect pentagram - minor radius is a little bigger
			than it should be. This gives a ratio of exactly 2/5=0.4, when a perfect
			pentagram is ~0.381965]
   5. Canvas-trimmed edge to the left of the triangle is approximately D/5 wide
	    - not counted in measuring length of flag.
   6. Flags made of silk will be trimmed on three edges with a knotted fringe of
	    yellow silk D/5 wide. 

Done at the City of Manila, this twenty-fifth day of March, in the year of Our 
Lord, nineteen hundred and thirty-six, and of the Commonwealth of the 
Philippines, the first.

MANUEL L. QUEZON
President of the Philippines

By the President:
Elpidio Quirino
Secretary of the Interior 

*/
#include "PovSolar/Math.inc"

#declare OfficialBlue=<0,97,243>/255; //From CMYK 100-60-0-5
#declare OfficialRed=<230,22,80>/255; //from CMYK 0-90-65-10
#declare OfficialGold=<255,209,38>/255; //From CMYK 0-18-85-0
#declare USBlue=color rgb <0,0,160>/255; //#0000A0
#declare USRed=color rgb <192,0,0>/255; //#C00000

#declare Blue=USBlue;
#declare Red=USRed;
#declare Gold=OfficialGold;
#declare White=color rgb <1,1,1>;

#declare AtPeace=true;

//Star formulas from http://mathworld.wolfram.com/Pentagram.html
#macro Star(StarRadius)
  #local RealRho=StarRadius;
  #local RealR=0.4*RealRho;
	
	#local I=0;
	#while(I<5)
	  #local Theta=radians(I*72);
	  <sin(Theta),cos(Theta)>*RealRho
	  #local Theta=radians(I*72+36);
		<sin(Theta),cos(Theta)>*RealR
	  #local I=I+1;
  #end
#end	

#declare s2=sqrt(2);
#declare s3=sqrt(3);
#declare W=1;
#declare A=W*s3/2;
#declare D=W/5;
#declare R=D/2;
PrintNumber("W: ",W)
PrintNumber("A: ",A)
PrintNumber("D: ",D)
PrintNumber("R: ",R)

#declare NRays=8;
#declare RayWidth=360/(NRays*2);
#declare RaySpacing=360/NRays;

#declare MajorRayLen=D*5/9;
#declare MinorRayLen=D*4/9;

#declare MagicA=(R+MajorRayLen)*s2/2;
#declare MagicC=R+MinorRayLen;
#declare MagicB=sqrt(MagicC*MagicC-MagicA*MagicA);
PrintNumber("MagicA: ",MagicA)
PrintNumber("MagicB: ",MagicB)
PrintNumber("MagicC: ",MagicC)

#declare MagicAngle1=degrees(atan(MagicB/MagicA));
#declare MagicAngle2=MagicAngle1-RayWidth*1.5;
PrintNumber("MagicAngle1: ",MagicAngle1)
PrintNumber("MagicAngle2: ",MagicAngle2)


#declare Ray=intersection {
  box {
	  (x+y)*s2/2*(R+MajorRayLen),(-x-y)*s2/2*(R+MajorRayLen)+z
		rotate z*45
  }
	plane {
	  -x,0
		rotate z*RayWidth/2
	}
	plane {
	  x,0
		rotate -z*RayWidth/2
	}
	union {
	  plane {
		  -x,0
			rotate z*MagicAngle2
		}
		plane {
		  x,0
			rotate z*(RayWidth/2-MagicAngle2)
		}
	}
	union {
	  plane {
		  x,0
			rotate -z*MagicAngle2
		}
		plane {
		  -x,0
			rotate -z*(RayWidth/2-MagicAngle2)
		}
	}
}

#declare Sun=union {
  cylinder {
	  <0,0,0>,<0,0,1>,R
	}
  #local I=0;
  #while(I<NRays)
	  object {Ray rotate z*I*RaySpacing}
	  #local I=I+1;
  #end
}

#declare PHFlag=union {
  union {
    object {Sun translate x*(D/2+R+MajorRayLen)}
	  prism {0,1 10,Star(R*5/9) rotate x*90 rotate z*90 translate x*W}
  	finish {ambient 1 diffuse 0}
  	pigment {color OfficialGold}
	}
}

object {PHFlag}

background {color rgb <1,1,1>}

camera {
  orthographic	
  location <W,0,-W>
	look_at <W,0,0>
  up y*W
	right x*W*2
}



