/***************************************************************************/
//		arms.inc
/***************************************************************************/
#if (Gender = 1)
#declare Upper_Arm =
blob{
  threshold T
  
  //the main arm
  sphere{ 0,R,S scale Size/2.75 translate <0,0,0> }
  sphere{ 0,R,S scale Size/2.75 translate <0,-Size/6,0> }
  sphere{ 0,R,S scale <Size/4*0.85,Size/2,Size/4> translate <Size/12,-Size/2,Size/12> }
  sphere{ 0,R,S scale <Size/4*0.85,Size/2,Size/4> translate <-Size/12,-Size/2,Size/12> }
  sphere{ 0,R,S scale <Size/4*0.85,Size/2,Size/4> translate <Size/12,-Size/2,-Size/12> }
  sphere{ 0,R,S scale <Size/4*0.85,Size/2,Size/4> translate <-Size/12,-Size/2,-Size/12> }
  sphere{ 0,R,S scale <Size/4*0.85,Size/2,Size/4> translate <Size/12,-Size/1.5,Size/12> }
  sphere{ 0,R,S scale <Size/4*0.85,Size/2,Size/4> translate <-Size/12,-Size/1.5,Size/12> }
  sphere{ 0,R,S scale <Size/4*0.85,Size/2,Size/4> translate <Size/12,-Size/1.5,-Size/12> }
  sphere{ 0,R,S scale <Size/4*0.85,Size/2,Size/4> translate <-Size/12,-Size/1.5,-Size/12> }
  
  //the biceps
  sphere{ 0,R,S scale <Size/4.75*0.85,Size/4,Size/4.75> translate <Size/32,-Size/1.25,Size/6> }
  sphere{ 0,R,S scale <Size/4.75*0.85,Size/4,Size/4.75> translate <Size/16,-Size/1.5,Size/6> }
  sphere{ 0,R,S scale <Size/4.75*0.85,Size/4,Size/4.75> translate <Size/32,-Size/1.75,Size/6> }
  sphere{ 0,R,S scale <Size/4.75*0.85,Size/4,Size/4.75> translate <-Size/32,-Size/1.25,Size/6> }
  sphere{ 0,R,S scale <Size/4.75*0.85,Size/4,Size/4.75> translate <-Size/16,-Size/1.5,Size/6> }
  sphere{ 0,R,S scale <Size/4.75*0.85,Size/4,Size/4.75> translate <-Size/32,-Size/1.75,Size/6> }
  
  //the elbow
  sphere{ 0,R,S scale Size/3.5 translate <0,-Size*1.25,0> }
}
#end

#if (Gender = 2)
#declare Upper_Arm =
blob{
  threshold T
  
  //the main arm
  sphere{ 0,R,S scale Size/3.5 translate <0,0,0> }
  sphere{ 0,R,S scale Size/3.5 translate <0,-Size/6,0> }
  sphere{ 0,R,S scale <Size/3.75,Size/2,Size/3.5> translate <0,-Size/2,0> }
  sphere{ 0,R,S scale <Size/3.75,Size/2,Size/3.5> translate <0,-Size/1.5,0> }
  
  //the biceps
  sphere{ 0,R,S scale <Size/5.5,Size/4,Size/5.75> translate <0,-Size/1.25,Size/7.5> }
  sphere{ 0,R,S scale <Size/5.5,Size/4,Size/5.75> translate <0,-Size/1.5,Size/7.5> }
  sphere{ 0,R,S scale <Size/5.5,Size/4,Size/5.75> translate <0,-Size/1.75,Size/7.5> }
  
  //the elbow
  sphere{ 0,R,S scale Size/4.5 translate <0,-Size*1.,0> }
  sphere{ 0,R,S scale Size/4.5 translate <0,-Size*1.25,0> }
}
#end
/***************************************************************************/
#if (Gender = 1)
#declare Forearm =
blob{
  threshold T
  
  //the joint
  sphere{ 0,R,S scale Size/3.5 translate <0,0,0> }
  
  //the rest of the forearm
  sphere{ 0,R,S scale <Size/5*0.85,Size/2,Size/4.5> translate <Size/16,-Size*1/3,Size/16> }
  sphere{ 0,R,S scale <Size/5*0.85,Size/2,Size/4.5> translate <-Size/16,-Size*1/3,Size/16> }
  sphere{ 0,R,S scale <Size/5*0.85,Size/2,Size/4.5> translate <Size/16,-Size*1/3,-Size/16> }
  sphere{ 0,R,S scale <Size/5*0.85,Size/2,Size/4.5> translate <-Size/16,-Size*1/3,-Size/16> }

  sphere{ 0,R,S scale <Size/7*0.85,Size/2,Size/5> translate <0,-Size*2/3,Size/20> }
  sphere{ 0,R,S scale <Size/7*0.85,Size/2,Size/5> translate <0,-Size*2/3,-Size/20> }
  sphere{ 0,R,S scale <Size/7*0.85,Size/2,Size/5> translate <Size/24,-Size*2/3,0> }
  sphere{ 0,R,S scale <Size/7*0.85,Size/2,Size/5> translate <-Size/24,-Size*2/3,0> }
  
  sphere{ 0,R,S scale <Size/8,Size/5.5,Size/5.5> translate <0,-Size*17/16,Size/24> }
}
#end

#if (Gender = 2)
#declare Forearm =
blob{
  threshold T
  
  //the joint
  sphere{ 0,R,S scale Size/4.5 translate <0,0,0> }
  
  //the rest of the forearm
  sphere{ 0,R,S scale <Size/6.05,Size/2,Size/5.0> translate <Size/16,-Size*1/3,Size/16> }
  sphere{ 0,R,S scale <Size/6.05,Size/2,Size/5.0> translate <-Size/16,-Size*1/3,Size/16> }
  sphere{ 0,R,S scale <Size/6.05,Size/2,Size/5.0> translate <Size/16,-Size*1/3,-Size/16> }
  sphere{ 0,R,S scale <Size/6.05,Size/2,Size/5.0> translate <-Size/16,-Size*1/3,-Size/16> }

  sphere{ 0,R,S scale <Size/6.5,Size/2,Size/6> translate <0,-Size*0.65,Size/20> }
  sphere{ 0,R,S scale <Size/6.5,Size/2,Size/6> translate <0,-Size*0.65,-Size/20> }
  sphere{ 0,R,S scale <Size/8.5,Size/2,Size/6> translate <Size/24,-Size*0.65,0> }
  sphere{ 0,R,S scale <Size/8.5,Size/2,Size/6> translate <-Size/24,-Size*0.65,0> }

  sphere{ 0,R,S scale <Size/8,Size/5.75,Size/5.75> translate <0,-Size*17/16,Size/32> }
}
#end
