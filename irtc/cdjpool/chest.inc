/***************************************************************************/
//		chest.inc
/***************************************************************************/
#declare Chest =
blob{
  threshold T
  
  //the shoulders
  #if(Gender = 1)
  sphere{ 0,R,S scale <Size,Size/2,Size/2> translate <Size/8,Size*2,-Size/8> }
  sphere{ 0,R,S scale <Size,Size/2,Size/2> translate <-Size/8,Size*2,-Size/8> }
  sphere{ 0,R,S scale Size/2.75 translate <Size*0.85,Size*1.9,0> }
  sphere{ 0,R,S scale Size/2.75 translate <-Size*0.85,Size*1.9,0> }
    #end
  #if(Gender = 2)
//  sphere{ 0,R,S scale <Size*0.75,Size/2.5,Size/2.75> translate <Size/2.25,Size*1.8,0> }
//  sphere{ 0,R,S scale <Size*0.75,Size/2.5,Size/2.75> translate <-Size/2.25,Size*1.8,0> }
  sphere{ 0,R,S scale <Size*0.75,Size/2.5,Size/2.5> translate <Size/5*0.5,Size*2,0> }
  sphere{ 0,R,S scale <Size*0.75,Size/2.5,Size/2.5> translate <-Size/5*0.5,Size*2,0> }
  sphere{ 0,R,S scale Size/3.90 translate <Size*0.85,Size*1.9,-Size*0.05> }
  sphere{ 0,R,S scale Size/3.90 translate <-Size*0.85,Size*1.9,-Size*0.05> }
    #end

  //the chest
  #if(Gender = 1)
  sphere{ 0,R,S scale <Size*0.6*0.95,Size*0.65,Size/3> translate <Size*0.25*0.95,Size*1.5,Size*0.3*0.85> }
  sphere{ 0,R,S scale <Size*0.6*0.95,Size*0.65,Size/3> translate <-Size*0.25*0.95,Size*1.5,Size*0.3*0.85> }
  sphere{ 0,R,S scale <Size*0.6*0.95,Size*0.65,Size/2>*0.85 translate <Size*0.25*0.85,Size*1.75,Size*0.1> }
  sphere{ 0,R,S scale <Size*0.6*0.95,Size*0.65,Size/2>*0.85 translate <-Size*0.25*0.85,Size*1.75,Size*0.1> }
  sphere{ 0,R,S scale <Size*0.6*0.95,Size*0.65,Size/2>*0.85 translate <Size*0.25*0.85,Size*1.5,Size*0.2> }
  sphere{ 0,R,S scale <Size*0.6*0.95,Size*0.65,Size/2>*0.85 translate <-Size*0.25*0.85,Size*1.5,Size*0.2> }
    #end
  #if(Gender = 2)
  sphere{ 0,R,S*2 scale Size*0.325+z*Size*0.1 translate <Size*0.2,Size*1.075,Size*Breasts*0.01> }
  sphere{ 0,R,S*2 scale Size*0.325+z*Size*0.1 translate <-Size*0.2,Size*1.075,Size*Breasts*0.01> }
  sphere{ 0,R,S*2 scale Size*0.325+z*Size*0.1 translate <Size*0.325,Size*1.4,Size*Breasts*0.35> }
  sphere{ 0,R,S*2 scale Size*0.325+z*Size*0.1 translate <-Size*0.325,Size*1.4,Size*Breasts*0.35> }
  sphere{ 0,R,S*2 scale Size*0.3375+z*Size*0.1 translate <Size*0.325,Size*1.6,Size*Breasts*0.05> }
  sphere{ 0,R,S*2 scale Size*0.3375+z*Size*0.1 translate <-Size*0.325,Size*1.6,Size*Breasts*0.05> }
  sphere{ 0,R,S*2 scale Size*0.3375+z*Size*0.1 translate <Size*0.3,Size*1.7,Size*Breasts*0.0126> }
  sphere{ 0,R,S*2 scale Size*0.3375+z*Size*0.1 translate <-Size*0.3,Size*1.7,Size*Breasts*0.0126> }
//  sphere{ 0,R,S*2 scale Size*0.325+z*Size*0.1 translate <Size*0.3,Size*1.85,Size*Breasts*0.0125> }
//  sphere{ 0,R,S*2 scale Size*0.325+z*Size*0.1 translate <-Size*0.3,Size*1.85,Size*Breasts*0.0125> }

  sphere{ 0,R,S*2 scale Size*0.35+z*Size*0.1 translate <Size*0.233,Size*1.3,Size*Breasts*0.35*0.85> }
  sphere{ 0,R,S*2 scale Size*0.35+z*Size*0.1 translate <Size*0.233,Size*1.5,Size*Breasts*0.05*0.85> }
  sphere{ 0,R,S*2 scale Size*0.35+z*Size*0.1 translate <Size*0.233,Size*1.6,Size*Breasts*0.026*0.85> }
//  sphere{ 0,R,S*2 scale Size*0.3+z*Size*0.1 translate <Size*0.233,Size*1.75,Size*Breasts*0.0125*0.85> }
  sphere{ 0,R,S*2 scale Size*0.35+z*Size*0.1 translate <Size*0.116,Size*1.3,Size*Breasts*0.35*0.7> }
  sphere{ 0,R,S*2 scale Size*0.35+z*Size*0.1 translate <Size*0.116,Size*1.5,Size*Breasts*0.05*0.7> }
  sphere{ 0,R,S*2 scale Size*0.35+z*Size*0.1 translate <Size*0.116,Size*1.6,Size*Breasts*0.026*0.7> }
//  sphere{ 0,R,S*2 scale Size*0.3+z*Size*0.1 translate <Size*0.116,Size*1.75,Size*Breasts*0.0125*0.7> }
  sphere{ 0,R,S*2 scale Size*0.35+z*Size*0.1 translate <Size*0,Size*1.3,Size*Breasts*0.35*0.55> }
  sphere{ 0,R,S*2 scale Size*0.35+z*Size*0.1 translate <Size*0,Size*1.5,Size*Breasts*0.05*0.55> }
  sphere{ 0,R,S*2 scale Size*0.35+z*Size*0.1 translate <Size*0,Size*1.6,Size*Breasts*0.026*0.55> }
//  sphere{ 0,R,S*2 scale Size*0.3+z*Size*0.1 translate <Size*0,Size*1.75,Size*Breasts*0.0125*0.55> }
  sphere{ 0,R,S*2 scale Size*0.35+z*Size*0.1 translate <-Size*0.116,Size*1.3,Size*Breasts*0.35*0.7> }
  sphere{ 0,R,S*2 scale Size*0.35+z*Size*0.1 translate <-Size*0.116,Size*1.5,Size*Breasts*0.05*0.7> }
  sphere{ 0,R,S*2 scale Size*0.35+z*Size*0.1 translate <-Size*0.116,Size*1.6,Size*Breasts*0.026*0.7> }
//  sphere{ 0,R,S*2 scale Size*0.3+z*Size*0.1 translate <-Size*0.116,Size*1.75,Size*Breasts*0.0125*0.7> }
  sphere{ 0,R,S*2 scale Size*0.35+z*Size*0.1 translate <-Size*0.233,Size*1.3,Size*Breasts*0.35*0.85> }
  sphere{ 0,R,S*2 scale Size*0.35+z*Size*0.1 translate <-Size*0.233,Size*1.5,Size*Breasts*0.05*0.85> }
  sphere{ 0,R,S*2 scale Size*0.35+z*Size*0.1 translate <-Size*0.233,Size*1.6,Size*Breasts*0.026*0.85> }
//  sphere{ 0,R,S*2 scale Size*0.3+z*Size*0.1 translate <-Size*0.233,Size*1.75,Size*Breasts*0.0125*0.85> }

    #end

  //the hips and abdomen
  #if(Gender = 1)
  sphere{ 0,R,S scale Size/2 translate <Size/2.75,Size*1.5,0> }
  sphere{ 0,R,S scale Size/2.15 translate <Size/2.75*0.85,Size*1.0,0> }
  sphere{ 0,R,S scale Size/2.15 translate <Size/3*0.75,Size*0.5,0> }
  sphere{ 0,R,S scale Size/2 translate <Size/5*0.85,Size*0.0,0> }
  sphere{ 0,R,S scale Size/2 translate <Size/2.5*0.85,Size*0.0,0> }
  sphere{ 0,R,S scale Size/2 translate <0,Size*1.5,Size*0.05> }
  sphere{ 0,R,S scale Size/2.5 translate <0,Size*1.25,Size*0.05> }
  sphere{ 0,R,S scale Size/2 translate <0,Size*1.0,Size*0.05> }
  sphere{ 0,R,S scale Size/2.5 translate <0,Size*0.75,Size*0.05> }
  sphere{ 0,R,S scale Size/2 translate <0,Size*0.5,Size*0.05> }
  sphere{ 0,R,S scale Size/2.5 translate <0,Size*0.25,Size*0.05> }
  sphere{ 0,R,S scale Size/2 translate <0,Size*0.0,Size*0.05> }
  sphere{ 0,R,S scale Size/2 translate <-Size/2.75,Size*1.5,0> }
  sphere{ 0,R,S scale Size/2.15 translate <-Size/2.75*0.85,Size*1.0,0> }
  sphere{ 0,R,S scale Size/2.15 translate <-Size/3*0.75,Size*0.5,0> }
  sphere{ 0,R,S scale Size/2 translate <-Size/5*0.85,Size*0.0,0> }
  sphere{ 0,R,S scale Size/2 translate <-Size/2.5*0.85,Size*0.0,0> }
    #end
  #if(Gender = 2)
  sphere{ 0,R,S scale Size/2.5 translate <Size/2.25*0.85,Size*1.5,0> }
  sphere{ 0,R,S scale Size/2.25*<1,1,0.875> translate <Size/4.25*0.85,Size*1.0,0> }
  sphere{ 0,R,S scale Size/2.25*<1,1,0.75> translate <Size/3.75*0.5,Size*0.5,0> }
  sphere{ 0,R,S scale Size/2.2 translate <Size/2.5*0.65,Size*0.2,-Size*0.03> }
  sphere{ 0,R,S scale Size/2.2 translate <Size/2.5*0.85,-Size*0.0,-Size*0.03> }
  sphere{ 0,R,S scale Size/2.5 translate <0,Size*1.5,0> }
  sphere{ 0,R,S scale Size/2.75 translate <0,Size*1.25,0> }
  sphere{ 0,R,S scale Size/2.5*<1,1,0.875> translate <0,Size*1.0,0> }
  sphere{ 0,R,S scale Size/2.75*<1,1,0.875> translate <0,Size*0.75,0> }
  sphere{ 0,R,S scale Size/2.5*<1,1,0.75> translate <0,Size*0.5,0> }
  sphere{ 0,R,S scale Size/2.75 translate <0,Size*0.25,0> }
  sphere{ 0,R,S scale Size/2.5 translate <0,Size*0.0,Size*0.05> }
  sphere{ 0,R,S scale Size/2.5 translate <-Size/2.25*0.85,Size*1.5,0> }
  sphere{ 0,R,S scale Size/2.25*<1,1,0.875> translate <-Size/4.25*0.85,Size*1.0,0> }
  sphere{ 0,R,S scale Size/2.25*<1,1,0.75> translate <-Size/3.75*0.5,Size*0.5,0> }
  sphere{ 0,R,S scale Size/2.2 translate <-Size/2.5*0.65,Size*0.2,-Size*0.03> }
  sphere{ 0,R,S scale Size/2.2 translate <-Size/2.5*0.85,-Size*0.0,-Size*0.03> }

    #end
}
/***************************************************************************/
#declare Back =
blob{
  threshold T

  //the shoulders
  #if(Gender = 1)
  sphere{ 0,R,S scale <Size,Size/2,Size/2> translate <Size/8,Size*2,-Size/8> }
  sphere{ 0,R,S scale <Size,Size/2,Size/2> translate <-Size/8,Size*2,-Size/8> }
  sphere{ 0,R,S scale Size/2.75 translate <Size*0.85,Size*1.9,0> }
  sphere{ 0,R,S scale Size/2.75 translate <-Size*0.85,Size*1.9,0> }
    #end
  #if(Gender = 2)
//  sphere{ 0,R,S scale <Size*0.75,Size/2.5,Size/2.75> translate <Size/2.25,Size*1.8,-Size/8> }
//  sphere{ 0,R,S scale <Size*0.75,Size/2.5,Size/2.75> translate <-Size/2.25,Size*1.8,-Size/8> }
  sphere{ 0,R,S scale <Size*0.75,Size/2.5,Size/2.5> translate <Size/5*0.5,Size*2,-Size*0.025> }
  sphere{ 0,R,S scale <Size*0.75,Size/2.5,Size/2.5> translate <-Size/5*0.5,Size*2,-Size*0.025> }
  sphere{ 0,R,S scale <Size*0.75,Size/2.5,Size/2.5> translate <Size/5*0.5,Size*1.9,-Size*0.05> }
  sphere{ 0,R,S scale <Size*0.75,Size/2.5,Size/2.5> translate <-Size/5*0.5,Size*1.9,-Size*0.05> }
  sphere{ 0,R,S scale Size/3.35 translate <Size*0.85,Size*1.9,-Size*0.05> }
  sphere{ 0,R,S scale Size/3.35 translate <-Size*0.85,Size*1.9,-Size*0.05> }
    #end

  //the hips and abdomen
  #if(Gender = 1)
  sphere{ 0,R,S scale Size/2 translate <Size/2,Size*1.5,-Size*0.15> }
  sphere{ 0,R,S scale Size/2.5 translate <Size/2.5*0.85,Size*1.0,-Size*0.15> }
  sphere{ 0,R,S scale Size/2.15 translate <Size/3*0.75,Size*0.5,-Size*0.175> }
  sphere{ 0,R,S scale Size/2.15 translate <Size/2.65*0.85,Size*0.1,-Size*0.175> }
  sphere{ 0,R,S scale Size/2.15 translate <Size/2.65*0.85,Size*0.0,-Size*0.175> }
  sphere{ 0,R,S scale Size/2 translate <0,Size*1.5,Size*0.05> }
  sphere{ 0,R,S scale Size/2 translate <0,Size*1.0,Size*0.05> }
  sphere{ 0,R,S scale Size/2 translate <0,Size*0.5,Size*0.0> }
  sphere{ 0,R,S scale Size/2 translate <0,Size*0.1,-Size*0.02> }
  sphere{ 0,R,S scale Size/2 translate <0,Size*0.0,-Size*0.02> }
  sphere{ 0,R,S scale Size/2 translate <-Size/2,Size*1.5,-Size*0.15> }
  sphere{ 0,R,S scale Size/2.5 translate <-Size/2.5*0.85,Size*1.0,-Size*0.15> }
  sphere{ 0,R,S scale Size/2.15 translate <-Size/3*0.75,Size*0.5,-Size*0.175> }
  sphere{ 0,R,S scale Size/2.15 translate <-Size/2.65*0.85,Size*0.1,-Size*0.175> }
  sphere{ 0,R,S scale Size/2.15 translate <-Size/2.65*0.85,Size*0.0,-Size*0.175> }
    #end
  #if(Gender = 2)
  sphere{ 0,R,S scale Size/2 translate <Size/2.25*0.85,Size*1.5,-Size*0.075> }
  sphere{ 0,R,S scale Size/2.25*<1,1,0.875> translate <Size/4.25*0.85,Size*1.0,-Size*0.075> }
  sphere{ 0,R,S scale Size/2.25*<1,1,0.75> translate <Size/3.75*0.5,Size*0.5,0> }
  sphere{ 0,R,S scale Size/2.2 translate <Size/2.5*0.65,Size*0.2,-Size/16*1> }
  sphere{ 0,R,S scale Size/2.2 translate <Size/2.5*0.85,-Size*0.1,-Size/16*1> }
  sphere{ 0,R,S scale Size/2.2 translate <Size/2.5*0.65,Size*0.2,-Size/16*3.65/2> }
  sphere{ 0,R,S scale Size/2.2 translate <Size/2.5*0.85,-Size*0.0,-Size/16*3.65/2> }
  sphere{ 0,R,S scale Size/2 translate <0,Size*1.5,-Size*0.075> }
  sphere{ 0,R,S scale Size/2.25*<1,1,0.875> translate <0,Size*1.0,-Size*0.075> }
  sphere{ 0,R,S scale Size/2.25*<1,1,0.75> translate <0,Size*0.5,-Size*0.075> }
  sphere{ 0,R,S scale Size/2 translate <0,Size*0.0,-Size*0.05> }
  sphere{ 0,R,S scale Size/2 translate <-Size/2.25*0.85,Size*1.5,-Size*0.075> }
  sphere{ 0,R,S scale Size/2.25*<1,1,0.875> translate <-Size/4.25*0.85,Size*1.0,-Size*0.075> }
  sphere{ 0,R,S scale Size/2.25*<1,1,0.75> translate <-Size/3.75*0.5,Size*0.5,0> }
  sphere{ 0,R,S scale Size/2.2 translate <-Size/2.5*0.65,Size*0.2,-Size/16*1> }
  sphere{ 0,R,S scale Size/2.2 translate <-Size/2.5*0.85,-Size*0.1,-Size/16*1> }
  sphere{ 0,R,S scale Size/2.2 translate <-Size/2.5*0.65,Size*0.2,-Size/16*3.65/2> }
  sphere{ 0,R,S scale Size/2.2 translate <-Size/2.5*0.85,-Size*0.0,-Size/16*3.65/2> }
  
    #end
}
