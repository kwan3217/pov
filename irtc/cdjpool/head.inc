/***************************************************************************/
//		head.inc
/***************************************************************************/
#declare Head =
union{
blob{
  threshold T
  
  //nose
  sphere{ 0,R,-S scale <Size/1,Size/50,Size/40> translate <0,-Size*0.03,Size*0.02> }
  sphere{ 0,R,S scale <Size/32,Size/28,Size/24> translate <0,Size*0.03,0> }
  sphere{ 0,R,S scale Size/24 translate <0,Size*0.02,-Size*0.02> }
  sphere{ 0,R,S*2 scale Size/32 translate <Size*0.0375,Size*0.02,-Size*0.05> }
  sphere{ 0,R,S*2 scale Size/32 translate <-Size*0.0375,Size*0.02,-Size*0.05> }
  sphere{ 0,R,S scale <Size/28,Size/16,Size/16> translate <0,Size*0.075,-Size*0.05> }
  sphere{ 0,R,S scale <Size/24,Size/16,Size/16> translate <0,Size*0.15,-Size*0.09> }
  
  //cheek bones
  sphere{ 0,R,S scale Size/5.5 translate <Size*0.05,Size*0.1,-Size*0.25> }
  sphere{ 0,R,S scale Size/5.5 translate <-Size*0.05,Size*0.1,-Size*0.25> }
  
  //cheeks
  sphere{ 0,R,S scale Size/5.5 translate <Size*0.1,Size*0.15,-Size*0.35> }
  sphere{ 0,R,S scale Size/5.5 translate <-Size*0.1,Size*0.15,-Size*0.35> }
  
/*
  //section behind the nose
//  sphere{ 0,R,S scale Size/5.5 translate <Size*0,Size*0.25,-Size*0.275> }
//  sphere{ 0,R,S scale Size/5.25 translate <Size*0.15,Size*0.3,-Size*0.35> }
//  sphere{ 0,R,S scale Size/5.25 translate <-Size*0.15,Size*0.3,-Size*0.35> }
*/
  //brow and forehead
  sphere{ 0,R,S scale Size/5.25 translate <Size*0,Size*0.25,-Size*0.30> }
  sphere{ 0,R,S scale Size/5.25 translate <Size*0.025,Size*0.25,-Size*0.30> }
  sphere{ 0,R,S scale Size/5.25 translate <-Size*0.025,Size*0.25,-Size*0.30> }
  
  //back of skull
  sphere{ 0,R,S scale Size/4.25 translate <Size*0.0,Size*0.3,-Size*0.30> }
  sphere{ 0,R,S scale Size/4.25 translate <Size*0.025,Size*0.25,-Size*0.45> }
  sphere{ 0,R,S scale Size/4.25 translate <-Size*0.025,Size*0.25,-Size*0.45> }
  
  //chin and cheeks
  sphere{ 0,R,S scale Size/7 translate <Size*0.0,-Size*0.05,-Size*0.15> }
  sphere{ 0,R,S scale Size/8 translate <Size*0.05,-Size*0,-Size*0.20> }
  sphere{ 0,R,S scale Size/8 translate <-Size*0.05,-Size*0,-Size*0.20> }
  sphere{ 0,R,S scale Size/8 translate <Size*0.1,Size*0,-Size*0.25> }
  sphere{ 0,R,S scale Size/8 translate <-Size*0.1,Size*0,-Size*0.25> }
  
  //eye sockets
  sphere{ 0,R,-S
    scale <Size/12,Size/24,Size/24>
    translate <Size/5.,Size/3.75,Size/1.80>
    translate <0,0,-Size*0.675>
    scale 3/5
  }
  sphere{ 0,R,-S
    scale <Size/12,Size/24,Size/24>
    translate <-Size/5.,Size/3.75,Size/1.80>
    translate <0,0,-Size*0.675>
    scale 3/5
  }
//  scale 5/3
//  translate <0,0,Size*0.65>
}

sphere{ 0,1
  scale <Size/12,Size/18,Size/18>
  texture{ Eye_Texture scale Size/12 }
  translate <Size/5.,Size/3.75,Size/1.85>
  translate <0,0,-Size*0.685>
  scale 3/5
}
sphere{ 0,1
  scale <Size/12,Size/18,Size/18>
  texture{ Eye_Texture scale Size/12 }
  translate <-Size/5.,Size/3.75,Size/1.85>
  translate <0,0,-Size*0.685>
  scale 3/5
}
  scale 5/3
  translate <0,0,Size*0.65>
}
/***************************************************************************/
#declare Neck =
blob{
  threshold T
  
  //neck
  sphere{ 0,R,S scale Size*0.2 translate <0,         -Size*0.2,Size*0.125> }
  sphere{ 0,R,S scale Size*0.2 translate <0,         -Size*0.2,-Size*0.125> }
  sphere{ 0,R,S scale Size*0.2 translate <Size*0.125 ,-Size*0.2,Size*0.0> }
  sphere{ 0,R,S scale Size*0.2 translate <-Size*0.125,-Size*0.2,-Size*0.0> }
  sphere{ 0,R,S scale Size*0.2 translate <0,         0,        Size*0.05> }
  sphere{ 0,R,S scale Size*0.2 translate <0,         0,        -Size*0.05> }
  sphere{ 0,R,S scale Size*0.2 translate <Size*0.075 ,0,        Size*0.0> }
  sphere{ 0,R,S scale Size*0.2 translate <-Size*0.075,0,        -Size*0.0> }
  sphere{ 0,R,S scale Size*0.2 translate <Size*0.0,  Size*0.25,Size*0.075> }
  sphere{ 0,R,S scale Size*0.2 translate <Size*0.0,  Size*0.25,-Size*0.075> }
  sphere{ 0,R,S scale Size*0.2 translate <Size*0.075, Size*0.25,Size*0.0> }
  sphere{ 0,R,S scale Size*0.2 translate <-Size*0.075,Size*0.25,-Size*0.0> }
}
/***************************************************************************/
#if (Gender = 1)
#declare Hair =
blob{
  threshold T
  
  //top
  sphere{ 0,R,S scale Size/4.2 translate <Size*0.0,Size*0.35,-Size*0.35> }
  sphere{ 0,R,S scale Size/4.2 translate <Size*0.025,Size*0.30,-Size*0.50> }
  sphere{ 0,R,S scale Size/4.2 translate <-Size*0.025,Size*0.30,-Size*0.50> }
  sphere{ 0,R,S scale Size/4.25 translate <Size*0.0,Size*0.32,-Size*0.28> }
  sphere{ 0,R,S scale Size/4.25 translate <Size*0.01,Size*0.3,-Size*0.45> }
  sphere{ 0,R,S scale Size/4.25 translate <Size*0.01,Size*0.3,-Size*0.45> }

  sphere{ 0,R,-S scale <Size/1,Size/5,Size/5> translate <Size*0.025,-Size*0.025,-Size*0.70> }
//  sphere{ 0,R,S scale Size/4.2 translate <-Size*0.02,Size*0.32,-Size*0.33> }
//  sphere{ 0,R,S scale Size/2 translate <0,Size*0.5,Size*0.05> }
//  sphere{ 0,R,S scale Size/2 translate <0,Size*0.5,-Size*0.25> }
  scale 5/3
  translate <0,-Size*0.1,Size*0.65>
}
#end
#if (Gender = 2)
#declare Hair =
blob{
  threshold T
  
  //top
  sphere{ 0,R,S scale Size*4 translate <0,0,0> }
}
#end
