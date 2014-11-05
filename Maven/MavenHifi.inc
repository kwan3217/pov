//Maven spacecraft model. Designed to be used in right-handed world.
//object X Y and Z axes are aligned to MAVEN_SPACECRAFT (-202000) spice frame

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

#macro Vector(V0,V1,R)
  cylinder {   
    V0,Linterp(0,V0,1,V1,0.75),R
  }
  cone {
    Linterp(0,V0,1,V1,0.75),R*2,V1,0
  }
#end

#declare MavenBus=union {
  box {
    <-1,-1,-1>,<1,1,1>
    pigment {color rgb 0.5}
  }
  sphere {
    #local Rhga=1.5;
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
      box {<-1,0,-0.1>,<1,2,0> rotate x*20 translate z*1 translate y*3}
      rotate z*I*180
      pigment {color rgb <0,0,1>}
    }
    #local I=I+1;
  #end
  cylinder {
    <1,0.5,1>,<3,0.5,1>,0.1
    pigment {color rgb <1,1,0>}
  }
  cylinder {
    <3,0.4,1>,<3,0.6,1>,0.15
    pigment {color rgb <0,1,1>}
  }
}

/*
APP and APP-mounted Instrument Frames
-------------------------------------------------------------------------------

   This section defines frames for the Articulated Payload Platform
   (APP) and instruments mounted on it -- IUVS, STATIC, and NGIMS.


APP Frames

   Four frames are defined for APP:

      -  MAVEN_APP_BP, ID -202501, is the APP base-plate frame defined
         as a fixed offset frame relative to and is nominally
         co-aligned with the s/c frame. This frame is called ``BP''
         in [5].

      -  MAVEN_APP_IG, ID -202503, is the APP inner gimbal frame
         defined as a CK-based frame and rotated by the inner gimbal
         angle about Y relative to the MAVEN_APP_BP frame. This frame
         does not exist in [5].

      -  MAVEN_APP_OG, ID -202505, is the APP outer gimbal frame
         defined as a CK-based frame and rotated by the outer gimbal
         angle about X relative to the MAVEN_APP_IG frame. This frame
         is called ``AR'' in [5].

      -  MAVEN_APP, ID -202507, is the APP platform frame defined as a
         fixed offset frame relative to the MAVEN_APP_OG frame and
         nominally rotated from it first by -90 degrees about X, then
         by -90 degrees about Z, and finally by +155 degrees about Y.
         This frame is called ``APP'' in [5] with its axes labeled as 
         I (=X), J (=Y), and K (=Z).

   Nominally at the gimbal angle pair 0.0/-155.0 the axes of the 
   MAVEN_APP frame point as follows:

      -  MAVEN_APP +X (APP +I) along s/c +Z

      -  MAVEN_APP +Y (APP +J) along s/c +X

      -  MAVEN_APP +Z (APP +K) along s/c +Y

   as seen on these diagrams (the MAVEN_APP_IG and MAVEN_APP_OG frames
   are not shown):

      +Z s/c side (0.0/-155.0 APP position):
      --------------------------------------

                                      ^ +Yapp
                                      |
                                      |
                         +Zapp     .__|__. APP
                              <-------o _|
                                      ^ +Xbp
                                      | 
                                      |  +Xsc
                           +Ybp       | ^ 
             ._________.____  <-------o-|-----.._________._________.
             |         |             .--|--.  ||         |         |>
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

                                                 +Zsc, +Zpb, and +Xapp 
                                                  are out of the page.

      +X APP side (0.0/-155.0 APP position):
      --------------------------------------

                                   Nadir FOV
                                       ._____.     .
                                       \     /  .-' `.  Limb FOV
                                .-------\   /.-'      `.
                STATIC       .-'  .-----'               `_.
                       -------.   |           IUVS      | |
                      |   |   |   |                     | |
                       -------'   |                     | |
                             `-.  `----  +Yapp   -------' |
                                `---.-- ^ ---.------------
                                    |   |    |   |       |--.
                                    `-- | .  |   |       |  |
                            +Zapp     _ | _| '   `_______.--'
                                <-------o   /                 NGIMS
                                     |_____|
                                       | |
                                       | |
                                      ~ ~ ~ 

                                        ^ +Xsc
                                        |
                                        |
                            +Ysc        |
                                <-------o
                                                  +Zsc and +Xapp are 
                                                    out of the page.


   The angles in the definitions of the fixed offset frames below are
   the opposites of the rotations described above because the rotations
   in the definitions are from the structure frames to the base frames.
*/

#declare IUVS=union {
  union {
    prism {    
     -0.25, //top
     0.25, //bottom
    9 //nr points
    /*   0*/ <-64.32715000, 52.05665000>,
    /*   1*/ <-6.69299830, 52.05665000>, 
    /*   2*/ <50.01157100, 36.81149000>, 
    /*   3*/ <89.77769900, 36.81149000>, 
    /*   4*/ <89.77769900, 1.84606000>, 
    /*   5*/ <43.96062500, 1.84606000>, 
    /*   6*/ <43.96062500, 0.00000000>, 
    /*   7*/ <-64.32715000, 0.00000000>,
             <-64.32715000, 52.05665000>
      pigment{ color rgb <1,1,1>} 
    } 
    prism {

     -0.2, //top
     0.2, //bottom
    8 //nr points
    /*   0*/ <0.00000000, 3.00000000>,
    /*   1*/ <-28.06250000, -39.40620000>,
    /*   2*/ <28.06250000, -39.40620000>,
    /*   3*/ <10.71875000, -13.18750000>,
    /*   4*/ <71.18750000, -40.21880000>,
    /*   5*/ <89.78125000, 1.84375000>, 
    /*   6*/ <0.75000000, 1.84375000>, 
             <0.00000000, 3.00000000>
      pigment{ color rgb <1,0.6,0.6>*0.5} 
    }
    scale <1/64.32715,1,1/64.32715>
    rotate y*90  
    rotate -z*90   
    scale 0.5
  }
  union {Vector(0,x,0.03) pigment {color rgb x}}
  union {Vector(0,y,0.03) pigment {color rgb y}}
  union {Vector(0,z,0.03) pigment {color rgb z}}
}

//Maven APP and outer gimbal hardware
#macro MavenAPP(Q_mirror)
union {
  union {
    box {
      <-0.4,0,-0.8>,<0.4,0.1,0.8>
      pigment {color rgb <1,1,0>}
    }
    prism {

     -0.1, //top
     0.0, //bottom
    6 //nr points
    /*   0*/ < 0.8,-0.1>,
    /*   1*/ < 0.8,-0.7>,
    /*   2*/ <-0.8,-0.7>,
    /*   3*/ <-1.3,-0.5>,
    /*   4*/ <-1.3,-0.3>,
    /*   5*/ <-0.8,-0.1>
      pigment{ color rgb <1,0.5,0>} 
      rotate y*90  
      rotate -z*90   
    }
    //NGIMS - mounted on the yellow plate looking towards +X
    union {
      box {
        <0.4,0,-0.7>,<0.0,-0.1,-0.3>
      }
      cylinder {
        <0.35,-0.05,-0.7>,<0.35,-0.05,-0.8>,0.05
      }
      cone {
        <0.4,-0.05,-0.75>,0.025,<0.55,-0.05,-0.75>,0.05
      }
      pigment {color rgb <0,1,0>}
    }
    union {
      object {IUVS }
      union {Vector(0,y,0.03) QuatTrans(Q_mirror,<0,0,0>) pigment {color rgb 1}}
      translate <0.125,0.5,0>
    }
    translate y*0.3
  }  
  cylinder {
    y*0.15,y*0.3,0.2
    pigment {color rgb <0.5,0,1>}
  }
  cylinder {
    y*0.15,0,0.1
    pigment {color rgb <0.5,0,1>}
  }
  union {Vector(0,x,0.05) pigment {color rgb x}}
  union {Vector(0,y,0.05) pigment {color rgb y}}
  union {Vector(0,z,0.05) pigment {color rgb z}}
}
#end

#macro MavenHiFiQ(Q_mirror,Q_g)
  union {
    object {MavenBus}
    union {MavenAPP(Q_mirror) QuatTrans(Q_g,<3,0.5,1>)}
  }

#end

#macro MavenHiFi(TTT) 
  MavenHiFiQ(pxform("MAVEN_IUVS_SCAN","MAVEN_IUVS_BASE",TTT),
             pxform("MAVEN_IUVS_BASE","MAVEN_APP_BP",TTT))
#end

