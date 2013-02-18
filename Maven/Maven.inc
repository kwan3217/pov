//Maven spacecraft model. Designed to be used in right-handed world.
//object X y and z axes are aligned to MAVEN spice frame

/*
Spacecraft Bus Frame
-------------------------------------------------------------------------------
 
   The spacecraft frame is defined by the s/c design as follows [from 5]:

      -  Z axis is perpendicular to the Launch Vehicle separation
         plane. The positive z direction is from the separation plane
         toward/through the High Gain Antenna.
 
      -  X axis is is in the Launch Vehicle separation plane extending
         from the origin through the scribe line on the outside
         diameter of the Launch Vehicle Ring (nominally toward the
         Articulating Payload Platform).

      -  Y axis completes the right handed frame;

      -  the origin of the frame is in the Launch Vehicle separation
         plane at the center point of the outside diameter of the
         Launch Vehicle Ring.

   These diagrams illustrate the s/c frame:

      +Z s/c side:
      ------------                 ._____. APP
                                   \_____|
                                      | 
                                      |
                                      |  +Xsc
                                      | ^ 
             ._________._________..-----|-----.._________._________.
             |         |         ||  .--|--.  ||         |         |>
       MAG .-|         |     +Ysc   /   |   \ ||         |         |-. MAG
          <  |         |        <-------o    |||         |         |  >
           `-|         |            \       / ||         |         |-'
            <|_________|_________|HGA'-----'  ||_________|_________|
                                  `-----------'
                                  .-'   |   `-.
                               .-'      |      `-.
                            .-'         @         `-.
                         .-'             SWEA        `-.
                  LPW .-'                               `-. LPW

                                                   +Zsc is out of the page.

      -X s/c side:
      ------------

          *.                            _                            .*
        MAG `o.                  HGA  .' `.                       .o' MAG
               `-.                  .'     `.                  .-'  
                  `-.               ---------               .-'
                     `-o_________..-----------.._________o-'
                                  |           |
                                  | +Zsc      |
                                  |     ^     |
                                  |     |     |
                                  |     |     |
                             +Ysc `-----|-----'
                                <-------x -'`-.
                               .-'      |      `-.
                            .-'         @         `-. 
                         .-'             SWEA        `-.
                  LPW .-'                               `-. LPW

                                                     +Xsc is into the page.

      -Y s/c side:
      ------------                 HGA  _
                                   .__.-*-.__.
                             Solar |    MAG  |
                             Array |         |            .___. 
                                  .-----------.===========|  .' APP
                                  |           |           `-'
                                  | +Zsc      |
                                  |     ^     |      
                                  |     |     |     
                                  |     |     | UHF
                                .-.-----|-----x           ---
                             .-'.'   `- x---.'-`> +Xsc    /
                          .-' .'          .'     `.      /
                       .-'   @           v         v    / 40 deg
                LPW .-'    SWEA    +Xuhf      +Zuhf  . /
                                                      `. 

                                           +Ysc, +Yuhf are into the page.
   Since the S/C bus attitude is provided by a C kernel (see [3] for
   more information), this frame is defined as a CK-based frame.

*/

#declare MavenBus=union {
  box {
    <-1,-1,-1>,<1,1,1>
    pigment {color rgb 0.5}
  }
  sphere {
    #local Rhga=1.0;
    (1+Rhga)*z,Rhga
    clipped_by {
      box {
        <-1,-1,1>,<1,1,1.3>
      }
    }
    pigment {color rgb 0.2}
  }
  #local I=0;
  #while(I<2)
    union {
      box {<-1,0,0.9>,<1,2,1> translate y}
      box {<-1,0,-0.1>,<1,2,0> rotate x*15 translate z*1 translate y*3}
      rotate z*I*180
      pigment {color rgb <0,0,1>}
    }
    #local I=I+1;
  #end
  cylinder {
    <1,0.5,1>,<2,0.5,1>,0.1
    pigment {color rgb <1,1,0>}
  }
}
 
  

