/***************************************************************************/
//		legs.inc
/***************************************************************************/
#ifndef (Height)
  #declare Height = 16*2;
  #end
#declare Size = Height/8;
/***************************************************************************/
#declare T = 0.25;	//threshold
#declare R = 1.5;	//radius
//#declare S = 0.83//1	//strength
/***************************************************************************/
#if (Gender = 1)
#declare Thigh =
blob{
  threshold T

  //hip
  sphere{ 0,R,S scale Size/2 translate <0,Size*0.0,0> }
  sphere{ 0,R,S scale Size/2 translate <0,-Size*0.5,-Size/16> }

  //thigh
  sphere{ 0,R,S scale <Size/3*0.85,Size,Size/3> translate <Size/8,-Size*1,Size/8> }
  sphere{ 0,R,S scale <Size/3*0.85,Size,Size/3> translate <-Size/8,-Size*1,Size/8> }
  sphere{ 0,R,S scale <Size/3*0.85,Size,Size/3> translate <Size/8,-Size*1,-Size/8> }
  sphere{ 0,R,S scale <Size/3*0.85,Size,Size/3> translate <-Size/8,-Size*1,-Size/8> }

  //knee
  sphere{ 0,R,S scale Size/3 translate <0,-Size*2,0> }

}
#end

#if (Gender = 2)
#declare Thigh =
blob{
  threshold T

  //hip
  sphere{ 0,R,S scale Size/2.1 translate <0,Size*0,-Size/16*1> }
  sphere{ 0,R,S scale Size/2.1 translate <0,-Size*0.5,-Size/16*1> }

  //thigh
  sphere{ 0,R,S scale <Size/3.25*0.95,Size,Size/3.25> translate <Size/16,-Size*1,Size/16> }
  sphere{ 0,R,S scale <Size/3.25*0.95,Size,Size/3.25> translate <-Size/16,-Size*1,Size/16> }
  sphere{ 0,R,S scale <Size/3.25*0.95,Size,Size/3.25> translate <Size/16,-Size*1,-Size/16> }
  sphere{ 0,R,S scale <Size/3.25*0.95,Size,Size/3.25> translate <-Size/16,-Size*1,-Size/16> }

  sphere{ 0,R,S scale <Size/3.25*0.9,Size*0.625,Size/3.25*1> translate <Size/16,-Size*1.1,Size/16> }
  sphere{ 0,R,S scale <Size/3.25*0.9,Size*0.625,Size/3.25*1> translate <-Size/16,-Size*1.1,Size/16> }
  sphere{ 0,R,S scale <Size/3.25*0.9,Size*0.625,Size/3.25*1> translate <Size/16,-Size*1.1,-Size/16> }
  sphere{ 0,R,S scale <Size/3.25*0.9,Size*0.625,Size/3.25*1> translate <-Size/16,-Size*1.1,-Size/16> }

  //knee
  sphere{ 0,R,S scale Size/3*<0.85,1,1> translate <0,-Size*1.75,0> }
  sphere{ 0,R,S scale Size/3*<0.85,1,1> translate <0,-Size*2,0> }

}
#end
/***************************************************************************/
#if (Gender = 1)
#declare Shin =
blob{
  threshold T
  
  //knee
  sphere{ 0,R,S scale Size/3*<0.85,1,1> translate <0,0,0> }
  sphere{ 0,R,S scale Size/3*<0.85,1,1> translate <0,-Size/6,Size/16> }
  sphere{ 0,R,S scale Size/3*<0.85,1,1> translate <0,Size/16,Size/16> }
  
  //top half of shin
  sphere{ 0,R,S scale <Size/3.5*0.95,Size/2,Size/3.5> translate <0,-Size/2,Size/8> }
  sphere{ 0,R,S scale <Size/3.95*0.95,Size/2,Size/3.5> translate <Size/8,-Size/2,-Size/8> }
  sphere{ 0,R,S scale <Size/3.95*0.95,Size/2,Size/3.5> translate <-Size/8,-Size/2,-Size/8> }

  //bottom half of shin
  sphere{ 0,R,S scale <Size/4*0.95,Size/2,Size/4> translate <0,-Size/1,Size/8> }
  sphere{ 0,R,S scale <Size/4.5*0.95,Size/2,Size/4> translate <Size/16,-Size/1,-Size/8> }
  sphere{ 0,R,S scale <Size/4.5*0.95,Size/2,Size/4> translate <-Size/16,-Size/1,-Size/8> }
  sphere{ 0,R,S scale <Size/3.5*0.95,Size/2,Size/3.5> translate <0,-Size*1.5,0> }
  
  //calf
  sphere{ 0,R,S scale <Size/3*0.95,Size/2,Size/3> translate <0,-Size/2,-Size/6> }
  
  //ankle
  sphere{ 0,R,S scale Size/4 translate <0,-Size*1.75,0> }
}
#end

#if (Gender = 2)
#declare Shin =
blob{
  threshold T
  
  //knee
  sphere{ 0,R,S scale Size/3.5 translate <0,0,0> }
  sphere{ 0,R,S scale Size/3.5 translate <0,-Size/6,Size/16> }
  sphere{ 0,R,S scale Size/3.5 translate <0,Size/16,Size/16> }
  sphere{ 0,R,S scale Size/3.5 translate <0,Size/16,0> }
  
  //top half shin
  sphere{ 0,R,S scale <Size/4,Size/2,Size/4> translate <0,-Size/2,Size/16> }
  sphere{ 0,R,S scale <Size/4,Size/2,Size/4> translate <Size/16,-Size/2,-Size/16> }
  sphere{ 0,R,S scale <Size/4,Size/2,Size/4> translate <-Size/16,-Size/2,-Size/16> }
  //bottom half shin
  sphere{ 0,R,S scale <Size/4.5,Size/2,Size/4.5> translate <0,-Size/1,Size/12> }
  sphere{ 0,R,S scale <Size/4.5,Size/2,Size/4.5> translate <Size/16,-Size/1,-Size/12> }
  sphere{ 0,R,S scale <Size/4.5,Size/2,Size/4.5> translate <-Size/16,-Size/1,-Size/12> }
  sphere{ 0,R,S scale <Size/4.75,Size/2,Size/4.75> translate <0,-Size*1.5,0> }
  
  //calf
  sphere{ 0,R,S scale <Size/4,Size/2,Size/4> translate <0,-Size/2,-Size/8> }
  
  //ankle
  sphere{ 0,R,S scale Size/5 translate <0,-Size*1.75,0> }
}
#end
/***************************************************************************/
#if (Gender = 1)
#declare Foot =
blob{
  threshold T
  
  //ankle
  //sphere{ 0,R,S scale Size/3.25 translate <0,Size/4,0> }
  sphere{ 0,R,S scale Size/4 translate <0,0,0> }
  
  //heel
  //sphere{ 0,R,S scale Size/4.25 translate <0,0,-Size/8> }
  sphere{ 0,R,S scale Size/4.25 translate <0,-Size/8,-Size/8> }

  //foot
  sphere{ 0,R,S scale <Size/3.75,Size/4,Size/2.25> translate <0,-Size/12,Size/16> }
  sphere{ 0,R,S scale <Size/3.75,Size/6,Size/2.75> translate <0,-Size/4,Size*0> }
  sphere{ 0,R,S scale <Size/3.95,Size/8,Size/2> translate <0,-Size/6,Size*0.25> }
  sphere{ 0,R,S scale <Size/3.95,Size/8,Size/2.25> translate <0,-Size/4,Size*0.25> }
  sphere{ 0,R,S scale <Size/3.95,Size/8,Size/2.25> translate <0,-Size/3,Size*0.65> }
  sphere{ 0,R,S scale <Size/3.95,Size/8,Size/2.25> translate <0,-Size/3,Size*1.25*0.375> }
  sphere{ 0,R,S scale <Size/3.95,Size/8,Size/2.25> translate <0,-Size/3,Size*1.25*0.25> }
  sphere{ 0,R,S scale <Size/3.95,Size/8,Size/2.25> translate <0,-Size/3,Size*1.25*0.125> }
  sphere{ 0,R,S scale <Size/3.95,Size/8,Size/2.75> translate <0,-Size/3,Size*0> }
}
#end

#if (Gender = 2)
#declare Foot =
blob{
  threshold T
  
  //ankle
  //sphere{ 0,R,S scale Size/3.25 translate <0,Size/4,0> }
  sphere{ 0,R,S scale Size/4 translate <0,0,0> }
  
  //heel
  //sphere{ 0,R,S scale Size/4.25 translate <0,0,-Size/8> }
  sphere{ 0,R,S scale Size/4.25 translate <0,-Size/8,-Size/8> }

  //foot
  sphere{ 0,R,S scale <Size/3.75,Size/4,Size/2.25> translate <0,-Size/12,Size/16> }
  sphere{ 0,R,S scale <Size/3.75,Size/6,Size/2.75> translate <0,-Size/4,Size*0> }
  sphere{ 0,R,S scale <Size/3.95,Size/7,Size/2> translate <0,-Size/6,Size*0.25> }
  sphere{ 0,R,S scale <Size/3.95,Size/8,Size/2.25> translate <0,-Size/4,Size*0.25+0.2*Size> }
  sphere{ 0,R,S scale <Size/3.95,Size/8,Size/2.25> translate <0,-Size/3,Size*0.625+0.05*Size> }
  sphere{ 0,R,S scale <Size/3.95,Size/8,Size/2.25> translate <0,-Size/3,Size*1.25*0.375+0.2*Size> }
  sphere{ 0,R,S scale <Size/3.95,Size/8,Size/2.25> translate <0,-Size/3,Size*1.25*0.25+0.2*Size> }
  sphere{ 0,R,S scale <Size/3.95,Size/8,Size/2.25> translate <0,-Size/3,Size*1.25*0.125+0.2*Size> }
  sphere{ 0,R,S scale <Size/3.95,Size/8,Size/2.75> translate <0,-Size/3,-Size*0.125+0.2*Size> }
  scale <0.9,1,0.9>
}
#end
/*
#if (Gender = 2)
#declare Foot =
blob{
  threshold T
  
  //ankle
  sphere{ 0,R,S scale Size/4.5 translate <0,0,0> }
  
  //heel
  sphere{ 0,R,S scale Size/4.5 translate <0,-Size/8,-Size/8> }

  //foot
  sphere{ 0,R,S scale <Size/4.25,Size/4,Size/4> translate <0,-Size/16,-Size/16> }
  sphere{ 0,R,S scale <Size/4.25,Size/6,Size/2.75> translate <0,-Size/4,Size*0> }
  sphere{ 0,R,S scale <Size/4.55,Size/8,Size/2> translate <0,-Size/5,Size*0.25+0.2*Size> }
  sphere{ 0,R,S scale <Size/4.55,Size/8,Size/2.5> translate <0,-Size/4,Size*0.25+0.2*Size> }
  sphere{ 0,R,S scale <Size/4.55,Size/8,Size/2.5> translate <0,-Size/3,Size*0.625+0.2*Size> }
  sphere{ 0,R,S scale <Size/4.55,Size/8,Size/2.25> translate <0,-Size/3,Size*1.25*0.375+0.2*Size> }
  sphere{ 0,R,S scale <Size/4.55,Size/8,Size/2.25> translate <0,-Size/3,Size*1.25*0.25+0.2*Size> }
  sphere{ 0,R,S scale <Size/4.55,Size/8,Size/2.25> translate <0,-Size/3,Size*1.25*0.125+0.2*Size> }
  sphere{ 0,R,S scale <Size/4.55,Size/8,Size/2.75> translate <0,-Size/3,-Size*0.125+0.2*Size> }
}
#end
*/