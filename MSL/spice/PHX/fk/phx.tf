KPL/FK

Phoenix Frame Definitions Kernel
===============================================================================

   This frame kernel contains frame definitions for the Phoenix Lander
   (PHX) including definitions for the frames used during cruise, EDL
   and surface operations, antenna and other structure frames and
   science payload frames.


Version and Date
-------------------------------------------------------------------------------

   Version 0.6 -- May 27, 2008 -- Boris Semenov, NAIF

      Changed the PHX_TOPO frame definition to be for the
      landing site coordinates specified in the LPF file
      lpf_uhf_PHX_ODY_052608_0330-0720.txt.

   Version 0.5 -- May 25, 2008 -- Boris Semenov, NAIF

      Changed the PHX_TOPO frame definition to be for the
      landing site coordinates specified in the LPF file
      lpf_acs_data_0525_0400.txt.

   Version 0.4 -- April 23, 2008 -- Boris Semenov, NAIF

      Filled in actual offsets for the RA tool frames. 

      Re-defined PHX_RA_CAMERA as a CK-based frame. 
   
      Added PHX_RA_CAMERA_EDGE/-84131 frame and name/ID mapping. 

      Added auxiliary payload frames for constraining coverage of the
      CAHVOR-derived SPKs. 

      Re-defined SSI frame chain.

   Version 0.3 -- December 26, 2007 -- Boris Semenov, NAIF

      Changed the PHX_TOPO frame definition to be for the
      GrnVly_LLB_102407 landing site. This change makes the
      GrnVly_LLB_102407-specific PHX_SURFACE_FIXED and PHX_LL frames
      because these frames are defined as fixed offsets w.r.t to the
      PHX_TOPO frame.

   Version 0.2 -- August 31, 2007 -- Boris Semenov, NAIF

      Changed the PHX_TOPO frame definition to be for the DAB1 landing
      site. This change makes the DAB1-specific PHX_SURFACE_FIXED and
      PHX_LL frames because these frames are defined as fixed offsets
      w.r.t to the PHX_TOPO frame.

   Version 0.1 -- March 20, 2007 -- Boris Semenov, NAIF

      Added PHX_MME_2000 frame.

   Version 0.0 -- June 20, 2006 -- Boris Semenov, NAIF

      Initial Release.


Contact Information
-------------------------------------------------------------------------------

   Boris V. Semenov, NAIF/JPL, (818)-354-8136, Boris.Semenov@jpl.nasa.gov


References
-------------------------------------------------------------------------------

   1. ``Frames Required Reading''

   2. ``Kernel Pool Required Reading''

   3. ``C-Kernel Required Reading''

   4. ``Phoenix Nomenclature, Coordinate Frames, and Phasing
      Documentation.''

   5. MGA boresight direction, e-mail from J. Delk, 06/06/06

   6. PHX Lander Configuration Drawing, 919L1240120, 10/04/05

   7. PHZ RA End Effector Interface Drawing,  10243730/B, 09/09/05

   8. PHX RA Optimized kinematics Parameters, 06/13/07


Implementation Notes
-------------------------------------------------------------------------------

   This file is used by the SPICE system as follows: programs that make
   use of this frame kernel must ``load'' the kernel, normally during
   program initialization. The SPICELIB routine FURNSH loads a
   kernel file into the pool as shown below.

      CALL FURNSH ( 'frame_kernel_name; )     (FORTRAN)
      furnsh_c ( "frame_kernel_name" );       (C)
      cspice_furnsh, "frame_kernel_name"      (IDL)

   This file was created and may be updated with a text editor.


PHX NAIF ID Codes
========================================================================

   The following names and NAIF ID codes are assigned to the PHX
   lander, its structures and science instruments (the keywords
   implementing these name-ID mappings are located in the section "PHX
   NAIF ID Codes -- Definition Section" at the end of this file):

   PHX lander and landing site:
   ----------------------------
      PHX                        -84
      PHX_LANDING_SITE           -84900
      PHX_LANDER                 -84000

   PHX payload:
   ------------
      PHX_PAYLOAD                -84100

   PHX SSI and SSI targets and marks:
   ----------------------------------
      PHX_SSI_HEAD               -84111
      PHX_SSI_LEFT_EYE           -84112
      PHX_SSI_RIGHT_EYE          -84113
      PHX_SSI_CAL_TARGET_1       -84114
      PHX_SSI_CAL_TARGET_2       -84115
      PHX_SSI_CAL_TARGET_3       -84116
      PHX_SSI_REF_MARK_1         -84117
      PHX_SSI_REF_MARK_2         -84118
      PHX_SSI_REF_MARK_3         -84119

   RA and RA instruments:
   ----------------------
      PHX_RA_TORSO               -84121
      PHX_RA_SHOULDER            -84122
      PHX_RA_ELBOW               -84123
      PHX_RA_WRIST               -84124
      PHX_RA_CAMERA              -84125  (synonym: PHX_RAC)
      PHX_RA_CAMERA_EDGE         -84131  (synonym: PHX_RAC_EDGE) 
      PHX_RA_TECP                -84127
      PHX_RA_SCOOP               -84128
      PHX_RA_BLADE               -84129
      PHX_RA_ISAD                -84130

   MET and MET sensors:
   --------------------
      PHX_MET_MAST               -84140

   MARDI:
   ------
      PHX_MARDI                  -84200

   LIDAR:
   ------
      PHX_LIDAR                  -84300

   TEGA:
   -----
      PHX_TEGA                   -84500
      PHX_TEGA_TA                -84510
      PHX_TEGA_EGA               -84520

   MECA:
   -----
      PHX_MECA                   -84600

   Antennas:
   ---------
      PHX_MGA                    -84410
      PHX_LGA1                   -84420
      PHX_LGA_EDL_WPA            -84430
      PHX_UHF_HELIX              -84440
      PHX_UHF_MONOPOLE           -84450


Phoenix Lander Frames
-------------------------------------------------------------------------------

   The following Phoenix Lander frames are defined in this kernel file:

           Name                  Relative to           Type       NAIF ID
      ======================  ===================  ============   =======

   Non Built-in Mars Frames:
   -------------------------
      PHX_MME_2000            rel.to J2000         FIXED          -84910

   Surface/descent frames (-849xx):
   --------------------------------
      PHX_TOPO                rel.to IAU_MARS      FIXED          -84900
      PHX_SURFACE_FIXED       rel.to TOPO          FIXED          -84901
      PHX_MRD                 rel.to IAU_MARS      FIXED          -84902
      PHX_LL                  rel.to TOPO          FIXED          -84903

   Lander frames (-8400x):
   -----------------------
      PHX_LANDER_CRUISE       rel.to MME_2000      CK             -84000
      PHX_LANDER              CRUISE, LL, PAYLOAD  CK             -84001

   PAYLOAD frame (-84100):
   -----------------------
      PHX_PAYLOAD             rel.to LANDER/TOPO   CK             -84100

   Auxiliary Payload Frames (-8419x):
   ----------------------------------
      PHX_PAYLOAD_RAC         rel.to PAYLOAD       CK             -84190
      PHX_PAYLOAD_RAC_EDGE    rel.to PAYLOAD       CK             -84191
      PHX_PAYLOAD_SSI_LEFT    rel.to PAYLOAD       CK             -84192
      PHX_PAYLOAD_SSI_RIGHT   rel.to PAYLOAD       CK             -84193

   SSI frames (-8411x):
   --------------------
      PHX_SSI_REF_AZ          rel.to PAYLOAD       FIXED          -84114
      PHX_SSI_AZ              rel.to SSI_REF_AZ    CK             -84115
      PHX_SSI_REF_EL          rel.to SSI_AZ        FIXED          -84116
      PHX_SSI_HEAD            rel.to PAYLOAD       CK             -84111
      PHX_SSI_LEFT_EYE        rel.to PAYLOAD/SSI_HEAD  CK         -84112
      PHX_SSI_RIGHT_EYE       rel.to PAYLOAD/SSI_HEAD  CK         -84113

   Robotic arm frames (-8412x & -8413x):
   -------------------------------------
      PHX_RA_TORSO            rel.to PAYLOAD       CK             -84121
      PHX_RA_SHOULDER         rel.to RA_TORSO      CK             -84122
      PHX_RA_ELBOW            rel.to RA_SHOULDER   CK             -84123
      PHX_RA_WRIST            rel.to RA_ELBOW      CK             -84124
      PHX_RA_CAMERA_EDGE      rel.to RA_ELBOW/PAYLOAD  CK         -84131
      PHX_RA_CAMERA           rel.to RA_CAMERA_EDGE/PAYLOAD  CK   -84125
      PHX_RA_EFFECTOR         rel.to RA_WRIST      FIXED          -84126
      PHX_RA_TECP             rel.to RA_EFFECTOR   FIXED          -84127
      PHX_RA_SCOOP            rel.to RA_EFFECTOR   FIXED          -84128
      PHX_RA_BLADE            rel.to RA_EFFECTOR   FIXED          -84129
      PHX_RA_ISAD             rel.to RA_EFFECTOR   FIXED          -84130

   MET instrument frames (-8414x,-8415x):
   --------------------------------------
      PHX_MET_MAST            rel.to LANDER        FIXED          -84140

   MARDI frame (-84200):
   ---------------------
      PHX_MARDI               rel.to LANDER        FIXED          -84200

   LIDAR frame (-84300):
   ---------------------
      PHX_LIDAR               rel.to LANDER        FIXED          -84300

   TEGA frame (-84500):
   --------------------
      PHX_TEGA                rel.to LANDER        FIXED          -84500

   MECA frame (-84600):
   --------------------
      PHX_MECA                rel.to LANDER        FIXED          -84600

   Antenna frames (-844xx):
   ------------------------
      PHX_MGA                 rel.to CRUISE        FIXED          -84410
      PHX_LGA1                rel.to CRUISE        FIXED          -84420
      PHX_LGA_EDL_WPA         rel.to CRUISE        FIXED          -84430
      PHX_UHF_HELIX           rel.to LANDER        FIXED          -84440
      PHX_UHF_MONOPOLE        rel.to LANDER        FIXED          -84450

   The frame descriptions and definitions are provided in the sections
   below.


PHX Frame Hierarchy
-------------------------------------------------------------------------------

   The diagram below shows the Phoenix Lander frames hierarchy:


                             "J2000" INERTIAL
       +----------------------------+----------------------------+
       |                            |                            |
       | <--pck                     | <--pck                     | <--fixed
       V                            V                            V
   "IAU_EARTH"                  "IAU_MARS"                   "PHX_MME_2000"
  EARTH BFR(***)              MARS BFR(***)                 MME J2000 Inertial
  --------------      +--------------------------+          -----------------
                      |                          |               |
                      |  <--fixed                | <--fixed      |
                      V                          V               |
              "PHX_TOPO"                     "PHX_MRD"           |
       +-------------------------+           ---------           |
       |         |               |               |               |
       |         |      fixed--> |               |               |
       |         |               V               |               |
       |         |        "PHX_SURFACE_FIXED"    |               |
       |         |        -------------------    |               |
       |         |                               |               |
       |         |                               |               |
       |         |                               |               |
       |         | <--fixed                      | <--ck         | <--ck
       |         V                               V               V
       |     "PHX_LL"                           "PHX_LANDER_CRUISE"
       |     ----------            +-----------------------------------+
       |         |                 |           |           |           |
       |         |        fixed--> |  fixed--> |           |  fixed--> |
       |         |                 |           |           |           |
       |         |                 V           V           |           V
       |         |     "PHX_LGA_EDL_WPA"   "PHX_MGA"       |       "PHX_LGA1"
       |         |     -----------------   ---------       |       ----------
       |         |                                         |
       |         |                                         |
       |         |                                         |
       |         | <--ck(*)                                | <--ck(*)
       |         V                                         V
       |                             "PHX_LANDER"
       |         +----------------------------------------------------+
       |         ^       |        |        |        |        |        |
       |         |       | <-fxd  |        | <-fxd  | <--fxd |        | <--fxd
       |         |       V        |        V        V        |        V
       |         |   "PHX_MARDI"  |  "PHX_MECA"  "PHX_TEGA"  |  "PHX_LIDAR"
       |         |   -----------  |  ----------  ----------  |  ----------
       |         |                |                          |
       |         |                | <-fixed                  | <-fixed
       |         |                V                          V
       |         |           "PHX_UHF_HELIX"             "PHX_UHF_MONOPOLE"
       |         |           ---------------             ------------------
       |         |
       |         |
       |         |
       |         |                                             "PHX_MET_MAST"
       |         |                                             --------------
       |         |                                                     ^
       |         |                                            fixed--> |
       |         |                                                     |
       | <--ck   | <--ck(*)(**)                                        |
       V         V
       "PHX_PAYLOAD"                                 
    -------------------------------------------------------------------+
            |             |        |     |            |                |
            | <--ck       |        |     |            | <--fixed       |
            V             |        |     |            V                |
     "PHX_RA_TORSO"       |        |     |     "PHX_SSI_REF_AZ"        |
     --------------       |        |     |     -----------------       |
            |             |        |     |            |                |
            | <--ck       |        |     |            | <--ck          |
            V             |        |     |            V                |
     "PHX_RA_SHOULDER"    |        |     |      "PHX_SSI_AZ"           |
     -----------------    |        |     |      ------------           |
            |             |        |     |            |                |
            | <--ck       |        |     |            | <--fixed       |
            V             |        |     |            V                |
      "PHX_RA_ELBOW"      |        |     |     "PHX_SSI_REF_EL"        |
      ----------------+   |        |     |     -----------------       |
            |         |   |        |     |            |                |
            | ck(*)-->|   | <--ck  |     |            | <--ck          |
            |         V   V        |     |            V                |
            | "PHX_RA_CAMERA_EDGE" |     |      "PHX_SSI_HEAD"         |
            |  ------------------- |     |      +------------+         |
            |             |        |     |      |            |         |
            |    ck(*)--> |  ck--> |     |<--ck | <--ck(*)   |<--ck(*) | <--ck
            |             V        V     V      V            V         V
            |          "PHX_RA_CAMERA" "PHX_SSI_LEFT_EYE" "PHX_SSI_RIGHT_EYE"
            |          --------------- ------------------ -------------------
            |
            | <--ck
            V
       "PHX_RA_WRIST"
       --------------
            |
            | <--fixed
            V
     "PHX_RA_EFFECTOR"
     -------------------------------------------------------------+
            |                 |                 |                 |
            | <--fixed        | <--fixed        | <--fixed        | <--fixed
            V                 V                 V                 V
     "PHX_RA_SCOOP"     "PHX_RA_BLADE"     "PHX_RA_ISAD"     "PHX_RA_TECP"
     --------------     --------------     -------------     -------------


   (*)      In these cases transformation is fixed but it has to be
            stored in a CK to make SPICE "traverse" appropriate frame
            tree branch based on the time of interest and/or loaded 
            kernels.

   (**)     This "CK-connection" can go both ways.

   (***)    BFR -- body-fixed rotating frame.


Implementation of Frame Chains for Different Mission Phases
-------------------------------------------------------------------------------

   Different routes along the branches of the PHX frame hierarchy are
   implemented for different mission phases depending on the
   availability of the orientation data and the source, format and type
   of the data.

   This subsection summarizes mission phase specific implementations.


Cruise
------


     "J2000" Inertial
     ----------------
            |
            | <----------- Fixed transformation defined in this FK
            V
    "PHX_MME_2000" Inertial
    -----------------------
            |
            | <----------- CK segment containing TLM quaternions
            V
    "PHX_LANDER_CRUISE"
    -------------------
            |
            | <----------- CK segment representing fixed rotation defined
            |              by the lander design
            V
       "PHX_LANDER"
       ------------
            |
            | <----------- CK segment representing fixed rotation defined
            |              by the lander/payload design
            V
       "PHX_PAYLOAD"
       -------------


Entry-Descent-Landing
---------------------


     "J2000" Inertial
     ----------------
            |
            | <----------- PCK-based transformation
            V
      "IAU_MARS" BFR
      ----------------
            |
            | <----------- CK segment representing fixed rotation derived
            |              from TLM (based on s/c position at the time of
            V              parachute pre-deploy + 13 seconds)
        "PHX_MRD"
        ---------
            |
            | <----------- CK segment based on TLM Quaternion
            V
    "PHX_LANDER_CRUISE"
    -------------------
            |
            | <----------- CK segment representing fixed rotation defined
            |              by the lander design
            V
       "PHX_LANDER"
       ------------
            |
            | <----------- CK segment representing fixed rotation defined
            |              by the lander/payload design
            V
       "PHX_PAYLOAD"
       -------------


Surface Operations
------------------

   During surface operations the lander orientation is available from
   two different sources in two different forms:

      -  initial orientation is provided by the spacecraft team in the
         form of quaternion defining orientation of the PHX_LANDER
         frame with respect to the PHX_LL frame;

      -  updated orientation, based on the Sun and local horizon images
         taken on a daily basis, is provided by PAYLOAD Team of UofA
         in the form of quaternion defining orientation of the
         PHX_PAYLOAD frame with respect to the PHX_TOPO frame;

   To accommodate both data streams two frame chains can be implemented:

   Chain 1 (based on spacecraft team quaternion):


     "J2000" Inertial
     ----------------
            |
            | <----------- PCK-based transformation
            V
      "IAU_MARS" BFR
      --------------
            |
            | <----------- Fixed rotation based on the landing site
            |              coordinates
            V
        "PHX_TOPO"
        ----------
            |
            | <----------- Fixed rotation based on frame definitions
            V
         "PHX_LL"
         --------
            |
            | <----------- CK segment representing fixed rotation per
            |              initial quaternion provided by LMA
            V
       "PHX_LANDER"
       ------------
            |
            | <----------- CK segment representing fixed rotation defined
            |              by the lander/payload design
            V
       "PHX_PAYLOAD"
       -------------


   Chain 2 (based on PAYLOAD quaternion):


     "J2000" Inertial
     ----------------
            |
            | <----------- PCK-based transformation
            V
      "IAU_MARS" BFR
      --------------
            |
            | <----------- Fixed rotation based on the landing site
            |              coordinates
            V
        "PHX_TOPO"
        ----------
            |
            | <----------- CK segment representing fixed rotation per
            |              updated quaternion(s) provided by PAYLOAD
            V
       "PHX_PAYLOAD"
       -------------
            |
            | <----------- CK segment representing fixed rotation defined
            |              by the lander/payload design
            V
       "PHX_LANDER"
       ------------


MME ``2000'' Frame
------------------

   The PHX_MME_2000 frame is the Mars Mean Equator and IAU Vector of J2000
   inertial reference frame defined using Mars rotation constants
   from the IAU 2000 report. This frame defined as a fixed offset frame
   with respect to the J2000 frame.

   \begindata

      FRAME_PHX_MME_2000           = -84910
      FRAME_-84910_NAME            = 'PHX_MME_2000'
      FRAME_-84910_CLASS           = 4
      FRAME_-84910_CLASS_ID        = -84910
      FRAME_-84910_CENTER          = 499
      TKFRAME_-84910_SPEC          = 'MATRIX'
      TKFRAME_-84910_RELATIVE      = 'J2000'
      TKFRAME_-84910_MATRIX        = (

         0.6732521982472339       0.7394129276360180       0.0000000000000000
        -0.5896387605430040       0.5368794307891331       0.6033958972853946
         0.4461587269353556      -0.4062376142607541       0.7974417791532832

                                     )

   \begintext


PHX Topocentric Frame
-------------------------------------------------------------------------------

   This frame defines the z axis as the normal outward at the landing
   site, the x axis points at local north with the y axis completing
   the right handed frame (points at local west.)

   Orientation of the frame is given relative to the body fixed rotating
   frame 'IAU_MARS' (x - along the line of zero longitude intersecting
   the equator, z - along the spin axis, y - completing the right hand
   coordinate frame.)

   The transformation from 'PHX_TOPO' frame to 'IAU_MARS'
   frame is a 3-2-3 rotation with defined angles as the negative of
   the site longitude, the negative of the site colatitude, 180 degrees.

   The landing site Gaussian longitude and latitude upon which the
   definition is built are:

      Lon = 234.248710 degrees East
      Lat =  68.450673 degrees North

   These Gaussian coordinates correspond to the following areocentric
   coordinates (R, LON, LAT) = (3376.340, 234.248710, 68.218394) and Mars radii
   (Re, Re, Rp) = (3396.19, 3396.19, 3376.20).

   The coordinates specified above are given with respect to the
   'IAU_MARS' instance defined by the rotation/shape model from the
   the PCK file 'mars_iau2000_v0.tpc'.

   These keywords implement the frame definition.

   \begindata

      FRAME_PHX_TOPO             = -84900
      FRAME_-84900_NAME           = 'PHX_TOPO'
      FRAME_-84900_CLASS          =  4
      FRAME_-84900_CLASS_ID       =  -84900
      FRAME_-84900_CENTER         =  -84900

      TKFRAME_-84900_RELATIVE     = 'IAU_MARS'
      TKFRAME_-84900_SPEC         = 'ANGLES'
      TKFRAME_-84900_UNITS        = 'DEGREES'
      TKFRAME_-84900_AXES         = ( 3, 2, 3 )
      TKFRAME_-84900_ANGLES       = ( -234.24871, -21.549327, 180.000  )

   \begintext


PHX Surface Fixed Frame
-------------------------------------------------------------------------------

   The orientation of the SURFACE_FIXED frame is by definition the same
   as of the PHX_TOPO frame. Therefore this frame is defined as a zero
   offset frame relative to the PHX_TOPO frame.

   \begindata

      FRAME_PHX_SURFACE_FIXED     =  -84901
      FRAME_-84901_NAME           = 'PHX_SURFACE_FIXED'
      FRAME_-84901_CLASS          =  4
      FRAME_-84901_CLASS_ID       =  -84901
      FRAME_-84901_CENTER         =  -84

      TKFRAME_-84901_RELATIVE     = 'PHX_TOPO'
      TKFRAME_-84901_SPEC         = 'ANGLES'
      TKFRAME_-84901_UNITS        = 'DEGREES'
      TKFRAME_-84901_AXES         = ( 1,      2,      3     )
      TKFRAME_-84901_ANGLES       = ( 0.000,  0.000,  0.000 )

   \begintext


PHX Mars Relative Descent (MRD) Frame
-------------------------------------------------------------------------------

   This frame is the frame used by PHX AACS on-board software to
   control the lander attitude during "terminal descent" phase -- from
   the "parachute pre-deploy + 13 secs" time through the "surface
   touchdown" time.

   The frame is defined in [11] as follows:

     "The Mars Relative Descent Frame Local Vertical, Local Horizontal
      Coordinate system used by the Lander is a coordinate system fixed
      with respect to the MCMF [Mars body-fixed rotating frame -- BVS]
      and is based on the position of (Pmcmf) of the Lander and the
      north pole unit vector (Nmcmf) in the MCMF frame at parachute
      pre-deploy + 13 secs (pre-deploy is triggered when the spacecraft
      velocity magnitude is below a specified threshold.) The axes are
      defined as follows:

                           -Pmcmf            [points from the spacecraft
               +Zmrd = -----------------      in Mars body-fixed frame
                           |Pmcmf|            towards the center of the planet
                                              at the time "pre-deploy + 13
                                              sec" - BVS]


                         +Zmrd x Nmcmf       [points to local East from sub-
               +Ymrd = -----------------      spacecraft point computed at the
                        |+Zmrd x Nmcmf|       time "pre-deploy + 13 sec" in
                                              Mars body-fixed frame - BVS]


               +Xmrd =   +Ymrd x +Zmrd       [points to local North from sub-
                                              spacecraft point computed at the
                                              time "pre-deploy + 13 sec" in
                                              Mars body-fixed frame - BVS]
     "

   Since "parachute pre-deploy + 13 secs" time and position of the
   spacecraft position at that time are not known until the actual
   decent and landing, and assuming that the final landing location
   will not be very far from the sub-spacecraft point at "parachute
   pre-deploy + 13 secs" time, we can specify orientation of the
   PHX_MRD frame as a fixed, 180 degrees rotation about +X with respect
   to the PHX_TOPO frame. The nominal definition below implements this
   rotation:

   \begindata

      FRAME_PHX_MRD               =  -84902
      FRAME_-84902_NAME           = 'PHX_MRD'
      FRAME_-84902_CLASS          =  4
      FRAME_-84902_CLASS_ID       =  -84902
      FRAME_-84902_CENTER         =  -84

      TKFRAME_-84902_RELATIVE     = 'PHX_TOPO'
      TKFRAME_-84902_SPEC         = 'ANGLES'
      TKFRAME_-84902_UNITS        = 'DEGREES'
      TKFRAME_-84902_AXES         = (   1,      2,      3     )
      TKFRAME_-84902_ANGLES       = ( 180.000,  0.000,  0.000 )

   \begintext

   When the actual transformation from the "IAU_MARS" frame to the
   "PHX_MRD" frame, computed on-board and send down to Earth in
   channelized telemetry as a 3x3 transformation matrix, will become
   available, it should be inserted into the definition below as
   follows:

      TKFRAME_-84902_MATRIX       = (
               A-474(LVLH_MTRX_11)  A-475(LVLH_MTRX_12)  A-476(LVLH_MTRX_13)
               A-477(LVLH_MTRX_21)  A-478(LVLH_MTRX_22)  A-479(LVLH_MTRX_23)
               A-480(LVLH_MTRX_31)  A-481(LVLH_MTRX_32)  A-482(LVLH_MTRX_33)
                                    )

   where A-xxx are channel IDs and (LVLH_MTRX_xx) are channel names.

   (TBD: channels above must be verified against TLM dictionary.)

   Then, the definition should be "activated" by placing it between
   \begindata ... \begintext tokens:

   begindata

      FRAME_PHX_MRD               =  -84902
      FRAME_-84902_NAME           = 'PHX_MRD'
      FRAME_-84902_CLASS          =  4
      FRAME_-84902_CLASS_ID       =  -84902
      FRAME_-84902_CENTER         =  -84

      TKFRAME_-84902_RELATIVE     = 'IAU_MARS'
      TKFRAME_-84902_SPEC         = 'MATRIX'
      TKFRAME_-84902_MATRIX       = (
                d.dddddddd          d.dddddddd          d.dddddddd
                d.dddddddd          d.dddddddd          d.dddddddd
                d.dddddddd          d.dddddddd          d.dddddddd
                                     )

   begintext


PHX Landed Local Vertical, Local Horizontal (LL) Frame
-------------------------------------------------------------------------------

   This frame is the frame with respect to which the landed lander
   orientation is determined by the on-board GyroCompass process.

   The frame is defined in [11] as follows:

     "The Landed Local Vertical, Local Horizontal Coordinate System
      used by the Lander is a coordinate system [the origin of which is
      -- BVS] fixed with respect to the landed spacecraft. The
      coordinate frame is is related to the MCI [PHX_MME_2000 Inertial --
      BVS] frame by rotation of the right ascension of the Mars local
      meridian and the latitude of the landed spacecraft."

   The axes of this frame point as follows:

      +Z    points along local gravity vector (because the latitude of
            the landing is determined as [11]:

              "LAT = arcsin( -G local * W local )
                 where:
               LAT      = latitude of landed s/c
               -G local = gravity vector measured in s/c body frame
               w local  = Mars rotational rate measure in the s/ body frame"

      +X    points towards local North

      +Y    completes the right-hand frame (and, thus points towards
            local East)

   One principal axis of this frame is based on the measured gravity
   vector direction at the landing site, which can be computed using
   different assumptions:

      -  local gravity vector points towards the center of Mars; in
         this case the latitude defining the axis is planetocentric
         latitude;

      -  local gravity vector points along normal to the nominal Mars
         spheroid surface; in this case the latitude defining the axis
         is planetographic latitude;

      -  local gravity vector points along the gravitational potential
         vector computed using some Mars gravity field model.

   It's obvious that the first assumption is the most inaccurate of the
   three while the last one the most accurate, with the difference
   between planetocentric and planetographic latitudes at the nominal
   landing site being:

      delta = | LAT_plcen - LAT_plgraph | = | 67.5 - 67.738 | = 0.238 deg.

   In this file the PHX_LL frame is defined as a fixed offset frame
   with respect to the PHX_TOPO frame that is based on the
   planetographic latitude.

   \begindata

      FRAME_PHX_LL                =  -84903
      FRAME_-84903_NAME           = 'PHX_LL'
      FRAME_-84903_CLASS          =  4
      FRAME_-84903_CLASS_ID       =  -84903
      FRAME_-84903_CENTER         =  -84

      TKFRAME_-84903_RELATIVE     = 'PHX_TOPO'
      TKFRAME_-84903_SPEC         = 'ANGLES'
      TKFRAME_-84903_UNITS        = 'DEGREES'
      TKFRAME_-84903_AXES         = (   1,      2,      3     )
      TKFRAME_-84903_ANGLES       = ( 180.000,  0.000,  0.000 )

   \begintext


PHX Lander Frame
-------------------------------------------------------------------------------

   Two primary frames are defined for the Phoenix spacecraft -- the
   LANDER frame (or Mechanical frame) and the LANDER CRUISE frame.


Lander Frame
------------

   The LANDER frame is the one used in all solid modeling and design of
   the lander. This frame, also called "Lander Mechanical frame", is
   defined in [4] as follows:

     "+Xm = pointed towards foot of deployed lander leg #1 (0 degree leg)
      +Zm = normal to launch vehicle interface plane
      +Ym = +Zm x +Xm, parallel to landed solar array axis of symmetry

      The origin of the frame is centered on the launch vehicle separation
      plane."

   If someone would look at the normal landed spacecraft configuration,
   he/she would see:

      -  Z axis is vertical and points down (from the lander deck
         toward the lander "legs");

      -  X axis is parallel to the lander deck plane and lander solar
         array yoke and points away from the deck center toward the
         deck side opposite to the SSI;

      -  Y completes the right-handed frame and points along solar
         array axis of symmetry;

      -  origin of this frame is 940.8 millimeters above the lander
         deck.


Lander Cruise Frame
-------------------

   This frame is defined in [4] as follows:

     "+Xc = negative direction of thrust of TCMs
      +Zc = center line of REMs #3 and #4
      +Yc = +Zc x +Xc

      ...

      The +X axis of the cruise frame is aligned with the +Z axis of
      the mechanical [PHX_LANDER -- BVS] frame. The +Y axis is rotated
      +120 degrees from the +X axis of the mechanical frame, about the
      +X axis of the cruise frame."

   The PHX_LANDER frame can be transformed to the PHX_LANDER_CRUISE
   frame by two rotations, first by -90 degrees about Y, second by +150
   degrees about the new position of X.


Lander and Lander Cruise Frame Diagram
--------------------------------------

   This diagram illustrates the LANDER and LANDER CRUISE frames (top
   view of the lander deck):


                  .~ ~ ~ ~ ~ ~ ~.
                  |   +Y solar  |
                  `     panel   '
                   \           /   __ 
                    `.       .'   | _|
                      `--H--'     //
                      ___H_______//
                     /     ^+Ylnd \ 
                    /      |       \
                   /       |        \ 
             --  +Xlnd     |+Zlnd(in)
            | =====|<------x+Xcru(in)
             --    |     .' \       |
                   \   .'    \      /               _
               +Zcru <'       \   o==============='_' RA
                     \________ V /
                         H    +Ycru
                      .--H--.     \\_
                    .'       `.   |__|
                   /           \
                  .  -Y solar   .
                  |    panel    |
                  `~ ~ ~ ~ ~ ~ ~'


Lander Frame Definitions
------------------------

   Both lander frames are defined as CK frames for the following
   reasons:

      -  during cruise the s/c "flies" using the PHX_LANDER_CRUISE
         frame; the orientation of this frame is determined on-board
         with respect to the PHX_MME_2000 frame; this orientation is sent
         down in the chanellized telemetry, from which it is extracted
         and stored in the cruise CK file;
 
      -  during descent the s/c also "flies" using the
         PHX_LANDER_CRUISE frame; the orientation of this frame is
         determined on-board with respect to the Mars Relative Descent
         frame (PHX_MRD); this orientation is sent down in the
         chanellized telemetry, from which it is extracted and stored in
         the descent CK file(s);
 
      -  after landing the initial orientation of the PHX_LANDER_CRUISE
         frame is determined (by running GyroCompass process) with
         respect the Landed Local Vertical, Local Horizontal frame
         (PHX_LL); it is stored in the surface orientation CK file(s);
 
      -  after landing the orientation of the PHX_PAYLOAD frame
         (described and defined later in this file) can be determined
         with respect the local level or topocentric frame; this
         orientation is stored in the surface orientation CK file(s);
 
      -  for different periods (cruise, descent, surface ops) the
         PHX_LANDER frame can be specified as offset to the
         PHX_LANDER_CRUISE frame or the PHX_PAYLOAD frame depending on
         for which of these the orientation data is available.

   Also, should the landed orientation change during surface operations
   due to the RA or other activities, the change in orientation will be
   captured in the landed CK file(s).

   \begindata

      FRAME_PHX_LANDER           = -84001
      FRAME_-84001_NAME          = 'PHX_LANDER'
      FRAME_-84001_CLASS         =  3
      FRAME_-84001_CLASS_ID      = -84001
      FRAME_-84001_CENTER        = -84
      CK_-84001_SCLK             = -84
      CK_-84001_SPK              = -84


      FRAME_PHX_LANDER_CRUISE    = -84000
      FRAME_-84000_NAME          = 'PHX_LANDER_CRUISE'
      FRAME_-84000_CLASS         =  3
      FRAME_-84000_CLASS_ID      = -84000
      FRAME_-84000_CENTER        = -84
      CK_-84000_SCLK             = -84
      CK_-84000_SPK              = -84

   \begintext


Nominal Landed Orientation
--------------------------

   Nominally the lander should land in the upward horizontal position
   (with the angle between the local gravity vector and lander +Z axis
   less than 16 degrees) with the lander -X axis pointing toward the
   local North (within +/- 15 degrees).

   This diagram illustrates the nominal landed orientation:

                  .~ ~ ~ ~ ~ ~ ~.
                  |   +Y solar  |
                  `     panel   '
                   \           /   __
                    `.       .'   | _|
                      `--H--'     //                 West
                      ___H_______//                   ^
                     /     ^+Ylnd \                   |
                    /      |+Ytopo \                  |
                   /       |        \                 |
             --    |       |     +Xtopo                 
            | =====|<------*------> |                   ------> North
             --    |+Xlnd  +Zlnd(in)|
                   \       +Ztopo(out)             _
                    \             o==============='_' RA
                     \___________/
                         H       \\
                      .--H--.     \\_
                    .'       `.   |__|
                   /           \
                  .  -Y solar   .
                  |    panel    |
                  `~ ~ ~ ~ ~ ~ ~'


   For the nominal landing orientation the TOPO frame can be
   transformed to the LANDER frame by two rotations, first is 180
   degrees about X axis, second is 180 degrees about new position of Z
   axis.


PHX PAYLOAD Frame
-------------------------------------------------------------------------------

   The PAYLOAD frame is used to communicate all payload operations and
   alignments.

   The PAYLOAD frame is defined as a fixed offset frame relative to the
   LANDER frame. It is rotated from the LANDER frame by 180 degrees
   about +Z axis to so that its +X axis points toward the RA side of
   the deck:

   Side view:
   ----------
                 +Xlnd             
                      <----X   SSI      .o.
                           | .-.       // \\
                           | | |      //   \\
                     +Zlnd V `_'     //     \\
                             |x|    //       \\
                             |x|   //         \\     RA
                             |x|  //           \\  _
                   _______________o------>      .o| |
                   |______________|_| +Xpayload    `.
                   |              | |
                  /|___________\\_|_/
                 //\            \\V/ +Zpayload
                //  \____________\\
               //                 \\
             _//                   \\_
            |__|                   |__|

                   
   Top view:
   ---------
                  .~ ~ ~ ~ ~ ~ ~.
                  |   +Y solar  |
                  `     panel   '
                   \           /   __
                    `.       .'   | _|
                      `--H--'     //
                      ___H_______//
                     /     ^+Ylnd \
                    /      |       \
                   /       |        \ 
             --    |       |+Zlnd(in)
            | =====|<------x        |
             --    |+Xlnd    _      |
                   \        | |    /  +X payload   _
                    \    SSI| |   x------>========'_' RA
                     \______`-'___|+Zpayload(in)    
                         H       \|
                      .--H--.     |\_
                    .'       `.   V__|
                   /         +Ypayload
                  .  -Y solar   .
                  |    panel    |
                  `~ ~ ~ ~ ~ ~ ~'
                                  
   The origin of PAYLOAD frame is at the intersection of the RA torso
   joint rotation axis and the deck surface.

   Though the PAYLOAD frame is a fixed rotation from the LANDER frame,
   it is defined as a CK based frame. This is necessary to accommodate
   various kinds of landed orientation estimates that might become
   available during the landed phase of the mission  (see
   "Implementation of Frame Chains for Different Mission Phases"
   section of this file for details.)

   \begindata

      FRAME_PHX_PAYLOAD           = -84100
      FRAME_-84100_NAME           = 'PHX_PAYLOAD'
      FRAME_-84100_CLASS          =  3
      FRAME_-84100_CLASS_ID       = -84100
      FRAME_-84100_CENTER         = -84
      CK_-84100_SCLK              = -84
      CK_-84100_SPK               = -84

   \begintext


Auxiliary PAYLOAD Frames
-------------------------------------------------------------------------------

   All frames defined in this section -- PHX_PAYLOAD_RAC,
   PHX_PAYLOAD_RAC_EDGE, PHX_PAYLOAD_SSI_LEFT, and
   PHX_PAYLOAD_SSI_RIGHT -- are auxiliary frames with the same purpose:
   they provide a mechanism to restrict data availability for the SPK
   files containing discrete data extracted from the image labels
   and/or other products.

   These frames, used as the reference frames in the corresponding SPK
   files, are defined as CK-based frames. The CK files containing
   orientation for these frames always store the orientation as zero
   rotation with respect to the PHX_PAYLOAD frame but provide this
   orientation only for the time periods when the positions stored in
   the SPKs should be allowed to be computed.

   \begindata

      FRAME_PHX_PAYLOAD_RAC       = -84190
      FRAME_-84190_NAME           = 'PHX_PAYLOAD_RAC'
      FRAME_-84190_CLASS          =  3
      FRAME_-84190_CLASS_ID       = -84190
      FRAME_-84190_CENTER         = -84
      CK_-84190_SCLK              = -84
      CK_-84190_SPK               = -84

      FRAME_PHX_PAYLOAD_RAC_EDGE  = -84191
      FRAME_-84191_NAME           = 'PHX_PAYLOAD_RAC_EDGE'
      FRAME_-84191_CLASS          =  3
      FRAME_-84191_CLASS_ID       = -84191
      FRAME_-84191_CENTER         = -84
      CK_-84191_SCLK              = -84
      CK_-84191_SPK               = -84

      FRAME_PHX_PAYLOAD_SSI_LEFT  = -84192
      FRAME_-84192_NAME           = 'PHX_PAYLOAD_SSI_LEFT'
      FRAME_-84192_CLASS          =  3
      FRAME_-84192_CLASS_ID       = -84192
      FRAME_-84192_CENTER         = -84
      CK_-84192_SCLK              = -84
      CK_-84192_SPK               = -84

      FRAME_PHX_PAYLOAD_SSI_RIGHT = -84193
      FRAME_-84193_NAME           = 'PHX_PAYLOAD_SSI_RIGHT'
      FRAME_-84193_CLASS          =  3
      FRAME_-84193_CLASS_ID       = -84193
      FRAME_-84193_CENTER         = -84
      CK_-84193_SCLK              = -84
      CK_-84193_SPK               = -84

   \begintext


PHX SSI Frames
-------------------------------------------------------------------------------

   This section contains definitions of the SSI frames.


PHX SSI "Reference" AZ, SSI AZ, SSI "reference" EL, and SSI Head Frames
-----------------------------------------------------------------------

   The PHX_SSI_REF_AZ, PHX_SSI_SSI_AZ, PHX_SSI_REF_EL, and PHX_SSI_HEAD
   frames make up the frame chain that allows to capture misalignments
   of the SSI azimuth and elevation axes and rotation in the azimuth
   and elevation gimbals in separate frame chain links.

   The PHX_SSI_REF_AZ frame is intended to capture the fixed
   misalignment of the azimuth rotation axis with respect to the
   PAYLOAD frame. It is defined as a fixed offset frame.
   
   The PHX_SSI_AZ frame is intended to capture the time varying
   orientation in the azimuth gimbal, as rotation about Z axis with
   respect to the PHX_SSI_REF_AZ frame. It is defined as a CK-based
   frame.
   
   The PHX_SSI_REF_EL frame is intended to capture the fixed
   misalignment of the elevation rotation axis with respect to the
   SSI_AZ frame. It is defined as a fixed offset frame.
   
   The PHX_SSI_HEAD frame is intended to capture the time varying
   orientation in the elevation gimbal, as rotation about Y axis with
   respect to the PHX_SSI_REF_EL frame. It is defined as a CK-based
   frame.

   Nominally, all of these frames are co-aligned with the PAYLOAD frame
   in the reference position -- cameras looking level along the +X axis of
   the PAYLOAD frame. This reference position is achieved at the SSI hardware
   azimuth angle of 88.75 degrees (between AZ motor steps 308 and 309) 
   and SSI hardware elevation angle 0 degrees (AL motor step 0) or at
   AZ=0,EL=0 in PAYLOAD frame.

   This diagram illustrates these four frames:

      TBD

   The frame definitions below contains nominal alignment data.

   \begindata

      FRAME_PHX_SSI_REF_AZ            = -84114
      FRAME_-84114_NAME               = 'PHX_SSI_REF_AZ'
      FRAME_-84114_CLASS              = 4
      FRAME_-84114_CLASS_ID           = -84114
      FRAME_-84114_CENTER             = -84
      TKFRAME_-84114_RELATIVE         = 'PHX_PAYLOAD'
      TKFRAME_-84114_SPEC             = 'ANGLES'
      TKFRAME_-84114_UNITS            = 'DEGREES'
      TKFRAME_-84114_AXES             = (   2,       1,       3        )
      TKFRAME_-84114_ANGLES           = (   0.000,   0.000,   0.000    )

      FRAME_PHX_SSI_AZ                = -84115
      FRAME_-84115_NAME               = 'PHX_SSI_SSI_AZ'
      FRAME_-84115_CLASS              = 3
      FRAME_-84115_CLASS_ID           = -84115
      FRAME_-84115_CENTER             = -84
      CK_-84115_SCLK                  = -84
      CK_-84115_SPK                   = -84115

      FRAME_PHX_SSI_REF_EL            = -84116
      FRAME_-84116_NAME               = 'PHX_SSI_REF_EL'
      FRAME_-84116_CLASS              = 4
      FRAME_-84116_CLASS_ID           = -84116
      FRAME_-84116_CENTER             = -84
      TKFRAME_-84116_RELATIVE         = 'PHX_SSI_BASE'
      TKFRAME_-84116_SPEC             = 'ANGLES'
      TKFRAME_-84116_UNITS            = 'DEGREES'
      TKFRAME_-84116_AXES             = (   2,       1,       3        )
      TKFRAME_-84116_ANGLES           = (   0.000,   0.000,   0.000    )

      FRAME_PHX_SSI_HEAD              = -84111
      FRAME_-84111_NAME               = 'PHX_SSI_HEAD'
      FRAME_-84111_CLASS              = 3
      FRAME_-84111_CLASS_ID           = -84111
      FRAME_-84111_CENTER             = -84
      CK_-84111_SCLK                  = -84
      CK_-84111_SPK                   = -84111

   \begintext


PHX SSI Left Eye and Right Eye Camera Frames
-----------------------------------------------------------------------

   The SSI Left and Right eye camera frames -- PHX_SSI_LEFT_EYE and 
   PHX_SSI_RIGHT_EYE -- are defined as follows:

      -  Z axis is the camera boresight vector, defined as the view
         direction of the pixel (511.5,511.5);

      -  Y axis is the CCD row direction, in the plane containing the
         boresight and view direction of the pixel (511.5,0) and pointing
         from the center pixel toward the pixel (511.5,0);

      -  X axis completes the right-handed frame;

      -  origin is located at the nodal point of the camera.

   This diagram illustrates the Left and Right eye camera frames:

      TBD

   Since the orientation of these frames is computed with respect to 
   the PAYLOAD frame directly from the CAHVOR camera model parameters 
   provided in the image labels, these frames are defined as CK-based
   frames.

   \begindata

      FRAME_PHX_SSI_LEFT_EYE          = -84112
      FRAME_-84112_NAME               = 'PHX_SSI_LEFT_EYE'
      FRAME_-84112_CLASS              = 3
      FRAME_-84112_CLASS_ID           = -84112
      FRAME_-84112_CENTER             = -84
      CK_-84112_SCLK                  = -84
      CK_-84112_SPK                   = -84112

      FRAME_PHX_SSI_RIGHT_EYE         = -84113
      FRAME_-84113_NAME               = 'PHX_SSI_RIGHT_EYE'
      FRAME_-84113_CLASS              = 3
      FRAME_-84113_CLASS_ID           = -84113
      FRAME_-84113_CENTER             = -84
      CK_-84113_SCLK                  = -84
      CK_-84113_SPK                   = -84113

   \begintext


PHX Robotic Arm Frames
-------------------------------------------------------------------------------

   This FK defines a separate frame for each of the Robotic Arm (RA)
   joints (TORSO, SHOULDER, ELBOW, and WRIST) as well as for each of
   the instruments and tools mounted on the arm (RA CAMERA, SCOOP,
   TECP, BLADE, and ISAD).


RA Gimbal Frames Schematic Diagram
-------------------------------------------

   This diagram illustrates the RA joint frame (the RA is shown fully
   extended in the "zero" gimbal angle configuration):

   Top view:
   ---------

                                +Zpayload(in) x-----> +Xpayload
                                              |
                                              |
                                              |
                                              V +Ypayload
             +Zs
              ^                      +Ze                       +Zw
              |                       ^                        ^
         .____|_.                     |                        |
         |    | | +Xt +Xs             |                     .__|_______.
         | x--x-->-->                .|_____________________|_.|.      |
    +Zt(in)| +Ys(in)                 |x-----> +Xe           | |x-----> +Xw
         ._|____.                    |_+Ye(in)______________|_. +Yw(in)|
           | | |_____________________|_|                    .__________.
           V |                         |
        +Yt  ._________________________.


   Side view:
   ----------
                               +Ypayload(out) o-----> +Xpayload
                                              |
                                              |
                                              |
                                              V +Zpayload           Scoop
                                                             ____________
                                                            /           /
                                                            |          /
           .___                       _                     \     ____/
          /    \_____________________/ \_____________________\/ \/
      +Zs(in) X-----> +Xs     +Ze(in) X-----> +Xe      +Zw(in) X-----> +Xw
        /     | |___________________\ | /____________________\ | /
   +Yt(out)o-----> +Xt               \|/              |   `.  \|/ \
      /____|__|_|                     |                `.  .'  | \ \
           |  V                       V              RAC `'    V  \/ TECP
           |  +Ys                     +Ye                      +Yw
           V
         +Zt


RA TORSO Frame
-------------------------------------------

   The RA TORSO frame is a CK-based frame with orientation given
   relative to the PAYLOAD frame.

   The RA TORSO frame is defined as follows:

      -  +Z axis is along the torso joint rotation axis and point down
         toward the ground; nominally, this axis is co-aligned with the
         payload frame +Z axis;

      -  +X axis lies in the lander deck plane and points from the torso
         joint rotation axis toward the shoulder joint rotation axis;
         nominally, it is co-aligned with the payload frame +X axis for
         the torso joint in zero position;

      -  +Y completes the right-handed frame;

   The origin of the TORSO frame is located at the intersection of the torso
   rotation axis and the lander deck plane.

   \begindata

      FRAME_PHX_RA_TORSO         = -84121
      FRAME_-84121_NAME          = 'PHX_RA_TORSO'
      FRAME_-84121_CLASS         =  3
      FRAME_-84121_CLASS_ID      = -84121
      FRAME_-84121_CENTER        = -84

      CK_-84121_SCLK             = -84
      CK_-84121_SPK              = -84

   \begintext


RA SHOULDER Frame
-------------------------------------------

   The RA SHOULDER frame is a CK-based frame with orientation given
   relative to the RA TORSO frame.

   The RA SHOULDER frame is defined as follows:

      -  +Z axis is along the shoulder joint rotation axis and points
         in the direction of the -Y axis of the RA TORSO frame;

      -  +X is perpendicular to and intersects both the shoulder and
         the elbow joint rotation axes and points from the shoulder
         axis towards the elbow axis;

      -  +Y completes the right-handed frame;

   The origin of the SHOULDER frame is located in the middle of the
   shoulder gimbal.

   \begindata

      FRAME_PHX_RA_SHOULDER      = -84122
      FRAME_-84122_NAME          = 'PHX_RA_SHOULDER'
      FRAME_-84122_CLASS         =  3
      FRAME_-84122_CLASS_ID      = -84122
      FRAME_-84122_CENTER        = -84

      CK_-84122_SCLK             = -84
      CK_-84122_SPK              = -84

   \begintext


RA ELBOW Frame
-------------------------------------------

   The RA ELBOW frame is a CK-based frame with orientation given
   relative to the RA SHOULDER frame.

   The RA ELBOW frame is defined as follows:

      -  +Z axis is along the elbow joint rotation axis and points in
         the same direction as the +Z axis of the RA SHOULDER frame;

      -  +X is perpendicular to and intersects both the elbow and the
         wrist joint rotation axes and points from the elbow axis
         towards the wrist axis;

      -  +Y completes the right-handed frame;

   The origin of the ELBOW frame is located in the middle of the elbow
   gimbal.

   \begindata

      FRAME_PHX_RA_ELBOW         = -84123
      FRAME_-84123_NAME          = 'PHX_RA_ELBOW'
      FRAME_-84123_CLASS         =  3
      FRAME_-84123_CLASS_ID      = -84123
      FRAME_-84123_CENTER        = -84

      CK_-84123_SCLK             = -84
      CK_-84123_SPK              = -84

   \begintext



RA WRIST Frame
-------------------------------------------

   The RA WRIST frame is a CK-based frame with orientation given
   relative to the RA ELBOW frame.

   The RA WRIST frame is defined as follows:

      -  +Z axis is along the wrist joint rotation axis and points in
         the same direction as the +Z axis of the RA ELBOW frame;

      -  +Y is perpendicular to the wrist axis and points away from
         the scoop;

      -  +X completes the right-handed frame;

   The origin of the WRIST frame is located in the middle of the wrist
   gimbal.

   \begindata

      FRAME_PHX_RA_WRIST         = -84124
      FRAME_-84124_NAME          = 'PHX_RA_WRIST'
      FRAME_-84124_CLASS         =  3
      FRAME_-84124_CLASS_ID      = -84124
      FRAME_-84124_CENTER        = -84

      CK_-84124_SCLK             = -84
      CK_-84124_SPK              = -84

   \begintext



RA Science Instrument Frames Schematic Diagram
----------------------------------------------

   This diagram illustrates the RA instrument and tool frames (RA
   Effector Instruments side view with the wrist joint in "0" position; 
   tool frame offset angles are from [7]):
                                          /
                                         /   40 deg 
                                        / (ISAD angle)
                                         ______

                                  +Xisad
                         +Zisad     ^       ,-> +Zblade
                            <.     /     x-'  2 deg             (SCOOP angle)
                              `.  /.____||________________x-.  -----
                                `x/      |               /|  `-.   7.6 deg
                                 /       |              / |     `->
                                .        V +Xblade     /  |   +Zscoop
                                | +Zef^               /   V 
                                \  ___|__  __________/  +Xscoop
     ____________________________\/   |  \/      SCOOP
  +Ze(in)                        /    |   \
   x-----> +Xe               +Yef(in) x-----> +Xef
   | _________________________+Zw(in) |   /   +Xw
   |      |  |   ^+Yrac           \___|__/ \
   |      |  / */_                    |   \ \
   V  +Xrac(in)/  *__                 V    \ \ TECP
  +Ye     |/  x-     *__              +Yw   \ \
          /__   *--  +Zrac                   \_|
             *_    *>   /                      x +Ytecp(in)
    RA CAMERA   *__    x_ +Yrace(in)         .' \
                   *__/  *__        +Xtecp <'    \
                     /      *>                    V +Ztecp
             +Xrace V         +Zrace 

                                     -------          -----
                                      `-.   9.81 deg \    36.9 deg 
                                         `(RAC angle) \ (TECP angle)   
                                                       \ 

   Note that the RA CAMERA is mounted on the elbow link of the RA while
   the SCOOP and TECP are mounted on the wrist gimbal. (The ISAD and BLADE
   are mounted on the SCOOP.)


RA CAMERA EDGE and RA CAMERA Frames
-------------------------------------------
 
   While the RA CAMERA has fixed fixed orientation with respect to the
   RA ELBOW frame, both frames associated with it -- PHX_RA_CAMERA_EDGE
   and PHX_RA_CAMERA -- are defined as CK based frames to allow storing
   their orientation provided in the RAC image headers as deflected RA
   device orientation quaternion (for the RA_CAMERA_EDGE frame) or the
   CAHVOR parameters (for the RA_CAMERA frame) in the CK files.

   The RA CAMERA EDGE frame is defined as follows:

      -  +Z axis points along the camera boresight;

      -  +Y axis points in the same direction as the +Z axis of the RA
         ELBOW frame;

      -  +X completes the right-handed frame.

   The origin of the RA CAMERA frame is located in the middle of the RA
   camera eye entrance.

   The RA ELBOW frame can be transformed to the RA CAMERA EDGE frame by two
   rotations: first by +90 degrees about X axis, then by +99.81 degrees
   degrees about Y axis.

   If this frame would have been defined as a fixed offset frame, the
   following keywords providing its orientation would have been used in
   the definition:

      TKFRAME_-84131_RELATIVE    = 'PHX_RA_ELBOW'
      TKFRAME_-84131_SPEC        = 'ANGLES'
      TKFRAME_-84131_UNITS       = 'DEGREES'
      TKFRAME_-84131_AXES        = (   1,        2,      3     )
      TKFRAME_-84131_ANGLES      = ( -90.000,  -99.810,  0.000 )


   The RA CAMERA frame is defined as follows:

      -  +Z axis is the camera boresight vector, defined as the view
         direction of the pixel (255.5,127.5);

      -  +Y axis is the CCD row direction, in the plane containing the
         boresight and view direction of the pixel (255.5,0) and pointing
         from the center pixel toward the pixel (255.5,0);

      -  +X axis completes the right-handed frame;

   The origin of this frame is located at the nodal point of the camera.

   Nominally the RA CAMERA EDGE frame can be transformed to the RA CAMERA 
   frame by one rotation -- by +90 degrees about Z axis.

   If this frame would have been defined as a fixed offset frame, the
   following keywords providing its orientation would have been used in
   the definition:

      TKFRAME_-84125_RELATIVE    = 'PHX_RA_CAMERA_EDGE'
      TKFRAME_-84125_SPEC        = 'ANGLES'
      TKFRAME_-84125_UNITS       = 'DEGREES'
      TKFRAME_-84125_AXES        = (   3,      2,      1     )
      TKFRAME_-84125_ANGLES      = ( -90.000,  0.000,  0.000 )


   As stated above, instead of being defined as fixed offset frames
   these frame are defined as CK-based frames.

   \begindata

      FRAME_PHX_RA_CAMERA_EDGE    = -84131
      FRAME_-84131_NAME          = 'PHX_RA_CAMERA_EDGE'
      FRAME_-84131_CLASS         =  3
      FRAME_-84131_CLASS_ID      = -84131
      FRAME_-84131_CENTER        = -84

      CK_-84131_SCLK             = -84
      CK_-84131_SPK              = -84

      FRAME_PHX_RA_CAMERA         = -84125
      FRAME_-84125_NAME          = 'PHX_RA_CAMERA'
      FRAME_-84125_CLASS         =  3
      FRAME_-84125_CLASS_ID      = -84125
      FRAME_-84125_CENTER        = -84

      CK_-84125_SCLK             = -84
      CK_-84125_SPK              = -84

   \begintext


RA EFFECTOR Frame
-------------------------------------------

   The RA EFFECTOR frame is a fixed offset frame with orientation given
   relative to the RA WRIST frame.

   The RA EFFECTOR frame is defined as follows:

      -  +X axis points in the same direction as the wrist +X axis;

      -  +Y axis points is the same direction as the wrist +Z axis;

      -  +Z completes the right-handed frame.

   The origin of the EFFECTOR frame is located approximately at the
   middle of the wrist gimbal.

   The RA WRIST frame can be transformed to the RA EFFECTOR frame with
   two rotations: first of +90 degrees about +X axis, then by +0.11653962
   degrees about +Z (the THETA_offset_4 angle from [8]).

   Since the frame definition below contains the reverse
   transformation, from the RA EFFECTOR frame to the RA WRIST frame,
   the order of rotations is reversed and the sign of rotation angles
   is changed to the opposite one.

   \begindata

      FRAME_PHX_RA_EFFECTOR      =  -84126
      FRAME_-84126_NAME          = 'PHX_RA_EFFECTOR'
      FRAME_-84126_CLASS         =  4
      FRAME_-84126_CLASS_ID      =  -84126
      FRAME_-84126_CENTER        =  -84

      TKFRAME_-84126_RELATIVE    = 'PHX_RA_WRIST'
      TKFRAME_-84126_SPEC        = 'ANGLES'
      TKFRAME_-84126_UNITS       = 'DEGREES'
      TKFRAME_-84126_AXES        = (   1,        2,      3          )
      TKFRAME_-84126_ANGLES      = ( -90.000,    0.000, -0.11653962 )

   \begintext


RA TECP Frame
-------------------------------------------

   The RA TECP frame is a is a fixed offset frame with orientation
   given relative to the RA EFFECTOR frame.

   The RA TECP frame is defined as follows:

      -  +Z axis is along the probe center axis and points from the
         wrist joint rotation axis towards the end of the probe;

      -  +Y axis is along the wrist joint rotation axis and points in
         the same direction as the +Y axis of the RA EFFECTOR frame;

      -  +X completes the right-handed frame;

   The origin of the RA TECP frame is located at the TECP tip.

   The RA EFFECTOR frame can be transformed to the RA TECP frame by a
   single rotation of +126.9 degrees about Y axis.

   Since the frame definition below contains the reverse
   transformation, from the RA TECP frame to the RA EFFECTOR frame, the
   order of rotations is reversed and the signs of rotation angles are
   changed to the opposite ones.

   \begindata

      FRAME_PHX_RA_TECP          =  -84127
      FRAME_-84127_NAME          = 'PHX_RA_TECP'
      FRAME_-84127_CLASS         =  4
      FRAME_-84127_CLASS_ID      =  -84127
      FRAME_-84127_CENTER        =  -84

      TKFRAME_-84127_RELATIVE    = 'PHX_RA_EFFECTOR'
      TKFRAME_-84127_SPEC        = 'ANGLES'
      TKFRAME_-84127_UNITS       = 'DEGREES'
      TKFRAME_-84127_AXES        = (   1,        2,      3     )
      TKFRAME_-84127_ANGLES      = (   0.000, -126.900,  0.000 )

   \begintext


RA SCOOP Frame
-------------------------------------------

   The RA SCOOP frame is a fixed offset frame with orientation given
   relative to the RA EFFECTOR frame.

   The RA SCOOP frame is defined as follows:

      -  Z axis is parallel to the scoop edge outside surface,
         perpendicular to the blade edge and points away from the
         blade;

      -  Y axis is along the wrist joint rotation axis and points in the
         same direction as the +Y axis of the RA EFFECTOR frame;

      -  X completes the right-handed frame;

   The origin of the RA SCOOP frame is located in the middle of the
   blade edge.

   The RA EFFECTOR frame can be transformed to the RA SCOOP frame by a
   single rotation of +97.6 degrees about Y axis.

   Since the frame definition below contains the reverse
   transformation, from the RA SCOOP frame to the RA EFFECTOR frame,
   the order of rotations is reversed and the signs of rotation angles
   are changed to the opposite ones.

   \begindata

      FRAME_PHX_RA_SCOOP         =  -84128
      FRAME_-84128_NAME          = 'PHX_RA_SCOOP'
      FRAME_-84128_CLASS         =  4
      FRAME_-84128_CLASS_ID      =  -84128
      FRAME_-84128_CENTER        =  -84

      TKFRAME_-84128_RELATIVE    = 'PHX_RA_EFFECTOR'
      TKFRAME_-84128_SPEC        = 'ANGLES'
      TKFRAME_-84128_UNITS       = 'DEGREES'
      TKFRAME_-84128_AXES        = (   1,       2,      3     )
      TKFRAME_-84128_ANGLES      = (   0.000, -97.600,  0.000 )

   \begintext


RA BLADE Frame
-------------------------------------------

   The RA BLADE frame is a fixed offset frame with orientation given
   relative to the RA EFFECTOR frame.

   The RA BLADE frame is defined as follows:

      -  Z axis is parallel to the blade outside surface, perpendicular
         to the blade edge and points from the blade;

      -  Y axis is along the wrist joint rotation axis and points in
         the same direction as the +Y axis of the RA EFFECTOR frame;

      -  X completes the right-handed frame;

   The origin of the RA BLADE frame is located in the middle of the
   blade edge.

   The RA EFFECTOR frame can be transformed to the RA BLADE frame by a
   single rotation of +88 degrees about Y axis.

   Since the frame definition below contains the reverse
   transformation, from the RA BLADE frame to the RA EFFECTOR frame,
   the order of rotations is reversed and the signs of rotation angles
   are changed to the opposite ones.

   \begindata

      FRAME_PHX_RA_BLADE         =  -84129
      FRAME_-84129_NAME          = 'PHX_RA_BLADE'
      FRAME_-84129_CLASS         =  4
      FRAME_-84129_CLASS_ID      =  -84129
      FRAME_-84129_CENTER        =  -84

      TKFRAME_-84129_RELATIVE    = 'PHX_RA_EFFECTOR'
      TKFRAME_-84129_SPEC        = 'ANGLES'
      TKFRAME_-84129_UNITS       = 'DEGREES'
      TKFRAME_-84129_AXES        = ( 1,        2,      3     )
      TKFRAME_-84129_ANGLES      = ( 0.000,  -88.000,  0.000 )

   \begintext


RA ISAD Frame
-------------------------------------------

   The RA ISAD frame is a fixed offset frame with orientation given
   relative to the RA EFFECTOR frame.

   The RA ISAD frame is defined as follows:

      -  +Z axis is normal to the ISAD work surface;

      -  +Y axis is along the wrist joint rotation axis and points in
         the same direction as the +Y axis of the RA EFFECTOR frame;

      -  +X completes the right-handed frame;

   The origin of the RA ISAD frame is located in the middle of the
   ISAD work surface.

   The RA EFFECTOR frame can be transformed to the RA ISAD frame by a
   single rotation of -40 degrees about Y axis.

   Since the frame definition below contains the reverse
   transformation, from the RA ISAD frame to the RA EFFECTOR frame, the
   order of rotations is reversed and the signs of rotation angles are
   changed to the opposite ones.

   \begindata

      FRAME_PHX_RA_ISAD          =  -84130
      FRAME_-84130_NAME          = 'PHX_RA_ISAD'
      FRAME_-84130_CLASS         =  4
      FRAME_-84130_CLASS_ID      =  -84130
      FRAME_-84130_CENTER        =  -84

      TKFRAME_-84130_RELATIVE    = 'PHX_RA_EFFECTOR'
      TKFRAME_-84130_SPEC        = 'ANGLES'
      TKFRAME_-84130_UNITS       = 'DEGREES'
      TKFRAME_-84130_AXES        = ( 1,       2,      3     )
      TKFRAME_-84130_ANGLES      = ( 0.000,  40.000,  0.000 )

   \begintext


PHX MET Frames
-------------------------------------------------------------------------------

   Although the MET mast rotates about its hinge axis during
   deployment, it stays fixed with respect to the LANDER frame after it
   has been deployed. Therefore, the MET_MAST frame is defined as a
   fixed offset frame with deployed orientation specified relative to
   the LANDER frame.

   The MET mast frame is defined as follows:

      -  +Z axis is along the mast, from the hinge toward the end of
         the mast;

      -  +X axis away from the side of the mast on which the sensors are
         mounted;

      -  +Y axis is along the hinge rotation axis and points such that
         it completes the right-handed frame;

   The origin of the MET_MAST frame is located at the hinge center.

   This diagram illustrates the MET_MAST frame:

                  .~ ~ ~ ~ ~ ~ ~.
                  |   +Y solar  |
                  `     panel   '
                   \           /   __
                    `.      +Ymet | _|
                      `--H ^      //
               50.5deg|<>,'______//
                     / .'  ^+Ylnd \
                 +Zmeto    |       \
                 (out) \   |        \ 
             -     |    \  |        |
            | =====|<----\-x +Xlnd(in)
             --    +Xlnd  V         |
                   \      +Xmet     /              _
                    \             o==============='_' RA
                     \____________/  
                         H       \\
                      .--H--.     \\_
                    .'       `.   |__|
                   /           \
                  .  -Y solar   .
                  |    panel    |
                  `~ ~ ~ ~ ~ ~ ~'

   As seen on the diagram the MET_MAST +Z axis points up -- in the
   direction opposite to the LANDER frame +Z axis. The MET_MAST +Y axis is
   50.5 degrees off the LANDER +Y axis toward the LANDER -X axis.

   The following set of rotation angles defines the orientation of the
   MET_MAST frame:

      M = [ 0.0 ]  [ -50.5 ]  [ 180.0 ]
                 X          Z          Y

   where M is the matrix rotating vectors from the LANDER frame to the
   MET_MAST frame.

   Since the frame definition below contains the reverse
   transformation, i.e. from the mast frame to the LANDER fame, the
   order of rotations is reversed and the signs of rotation angles are
   changed to the opposite ones.

   \begindata

      FRAME_PHX_MET_MAST         =  -84140
      FRAME_-84140_NAME          = 'PHX_MET_MAST'
      FRAME_-84140_CLASS         =  4
      FRAME_-84140_CLASS_ID      =  -84140
      FRAME_-84140_CENTER        =  -84

      TKFRAME_-84140_RELATIVE    = 'PHX_LANDER'
      TKFRAME_-84140_SPEC        = 'ANGLES'
      TKFRAME_-84140_UNITS       = 'DEGREES'
      TKFRAME_-84140_AXES        = (   2,       3,      1     )
      TKFRAME_-84140_ANGLES      = ( 180.000,  50.500,  0.000 )

   \begintext


PHX MARDI Frame
-------------------------------------------------------------------------------

   The MARDI frame is a fixed offset frame with orientation given
   relative to the LANDER frame.

   The MARDI frame is defined as follows:

      -  +Z axis is along the camera boresight;

      -  +Y axis is along the detector (image) columns and points in
         the direction of increasing lines;

      -  +X completes the right-handed frame; it's along the detector
         (image) rows and points in the direction of increasing
         samples;

   The origin of the MARDI frame is located at the camera focal point.

   This diagram illustrates the MARDI frame:

                  .~ ~ ~ ~ ~ ~ ~.
                  |   +Y solar  |
                  `     panel   '
                   \           /   __
          +Ymardi(out)       .'   | _|
          +Zmardi(in) `--H--'     //
              <.      ___H_______//
                `.   /     ^+Ylnd \
                  `*/      |       \
                  //       |        \ 
             -   / |       |        |
            | ==/==|<------x +Xlnd(in)
             --v   +Xlnd            |
           +Xmardi \                /              _
                    \             o==============='_' RA
                     \____________/  
                         H       \\
                      .--H--.     \\_
                    .'       `.   |__|
                   /           \
                  .  -Y solar   .
                  |    panel    |
                  `~ ~ ~ ~ ~ ~ ~'

   The following rotations transform the lander frame into the MARDI
   frame (TBD, -50 deg is a guess based on [6] and -21.98 is taken from
   [6]):

      M = [ 0.0 ]  [ -21.98 ]  [ -50.0 ]
                 Z           X          Z

   where M is a matrix rotating vectors from the LANDER frame to the
   MARDI frame.

   Since the frame definition below contains the reverse
   transformation, i.e. from the MARDI frame to the LANDER frame, the
   order of rotations is reversed and the signs of rotation angles are
   changed to the opposite ones.

   \begindata

      FRAME_PHX_MARDI            =  -84200
      FRAME_-84200_NAME          = 'PHX_MARDI'
      FRAME_-84200_CLASS         =  4
      FRAME_-84200_CLASS_ID      =  -84200
      FRAME_-84200_CENTER        =  -84

      TKFRAME_-84200_RELATIVE    = 'PHX_LANDER'
      TKFRAME_-84200_SPEC        = 'ANGLES'
      TKFRAME_-84200_UNITS       = 'DEGREES'
      TKFRAME_-84200_AXES        = (   3,     1,      3      )
      TKFRAME_-84200_ANGLES      = ( 50.000, 21.980,  0.000  )

   \begintext


PHX LIDAR Frame
-------------------------------------------------------------------------------

   The LIDAR frame is a fixed offset frame with orientation given
   relative to the LANDER frame.

   The LIDAR frame is defined as follows:

      -  +Z axis is along the instrument boresight;

      -  +X axis is perpendicular to the Z axis and points away from
         the electronic connector side;

      -  +Y completes the right-handed frame;

   The origin of the LIDAR frame is located at the geometric center of
   the sensor unit.

   This diagram illustrates the LIDAR frame:

                  .~ ~ ~ ~ ~ ~ ~.
                  |   +Y solar  |
                  `     panel   '
                   \           /   __
                    `.       .'   | _|
                      `--H--'     //
                      ___H_______//
                     /     ^+Ylnd \
                    /      |    +Ylidar
                   / +Zlnd |   ^    \ 
             - +Xlnd  (in) |<>/40deg| 
            | =====|<------x /      |
             --    |     /`./       |
                   \     `.o +Zlidar/              _
                    \       `.(out)==============='_' RA
                     \________`.  /
                         H      `> +Xlidar
                      .--H--.     \\_
                    .'       `.   |__|
                   /           \
                  .  -Y solar   .
                  |    panel    |
                  `~ ~ ~ ~ ~ ~ ~'

   As seen on the diagram the LIDAR +Z axis points up -- in the
   direction opposite to the LANDER frame +Z axis. The LIDAR +Y axis is
   40 degrees off the LANDER +Y axis toward the LANDER -X axis.

   The following set of rotation angles defines the orientation of the
   LIDAR frame:

      M = [ 0.0 ]  [ -40.0 ]  [ 180.0 ]
                 X          Z          Y

   where M is the matrix rotating vectors from the LANDER frame to the
   LIDAR frame.

   Since the frame definition below contains the reverse
   transformation, i.e. from the LIDAR frame to the LANDER frame, the
   order of rotations is reversed and the signs of rotation angles are
   changed to the opposite ones.

   \begindata

      FRAME_PHX_LIDAR            =  -84300
      FRAME_-84300_NAME          = 'PHX_LIDAR'
      FRAME_-84300_CLASS         =  4
      FRAME_-84300_CLASS_ID      =  -84300
      FRAME_-84300_CENTER        =  -84

      TKFRAME_-84300_RELATIVE    = 'PHX_LANDER'
      TKFRAME_-84300_SPEC        = 'ANGLES'
      TKFRAME_-84300_UNITS       = 'DEGREES'
      TKFRAME_-84300_AXES        = (   2,       3,      1     )
      TKFRAME_-84300_ANGLES      = ( 180.000,  40.000,  0.000 )

   \begintext


PHX TEGA Frame
-------------------------------------------------------------------------------

   The TEGA frame is a fixed offset frame with orientation given
   relative to the LANDER frame.

   The TEGA frame is defined as follows:

      -  +Z axis is normal to the TEGA/TA mounting surface and points
         from that surface toward the top of the module;

      -  +X axis is perpendicular to the Z axis and points along the
         module center line toward the electronic connector side;

      -  +Y completes the right-handed frame;

   The origin of the TEGA frame is located at the TEGA/TA reference
   mounting hole.

   This diagram illustrates the TEGA frame:

                  .~ ~ ~ ~ ~ ~ ~.
                  |   +Y solar  |
                  `     panel   '
                   \           /   __
                    `.       .'   | _|
                      `--H--'     //
                      ___H_______//
                     /     ^+Ylnd \
                    /      |   .\  \
                   / +Zlnd | .'  \  \ 
             - +Xlnd  (in) | \   o +Ztega(out)
            | =====|<------x  \.' \ |
             --    |         .'    \|
                   \       <'    |<>\30.8deg       _
                    \  +Xtega     o==V============'_' RA
                     \____________/  +Ytega
                         H       \\
                      .--H--.     \\_
                    .'       `.   |__|
                   /           \
                  .  -Y solar   .
                  |    panel    |
                  `~ ~ ~ ~ ~ ~ ~'

   As seen on the diagram the TEGA +Z axis points up -- in the
   direction opposite to the LANDER +Z axis. The TEGA +Y axis is 30.8
   degrees off the LANDER -Y axis toward the LANDER -X axis.

   The following set of rotation angles defines the orientation of the
   TEGA frame:

      M = [ 0.0 ]  [ -149.2 ]  [ 180.0 ]
                 X           Z          Y

   where M is the matrix rotating vectors from the LANDER frame to the
   TEGA frame.

   Since the frame definition below contains the reverse
   transformation, i.e. from the TEGA frame to the LANDER frame, the
   order of rotations is reversed and the signs of rotation angles are
   changed to the opposite ones.

   \begindata

      FRAME_PHX_TEGA             =  -84500
      FRAME_-84500_NAME          = 'PHX_TEGA'
      FRAME_-84500_CLASS         =  4
      FRAME_-84500_CLASS_ID      =  -84500
      FRAME_-84500_CENTER        =  -84

      TKFRAME_-84500_RELATIVE    = 'PHX_LANDER'
      TKFRAME_-84500_SPEC        = 'ANGLES'
      TKFRAME_-84500_UNITS       = 'DEGREES'
      TKFRAME_-84500_AXES        = (   2,       3,      1     )
      TKFRAME_-84500_ANGLES      = ( 180.000, 149.200,  0.000 )

   \begintext


PHX MECA Frame
-------------------------------------------------------------------------------

   The MECA frame is a fixed offset frame with orientation given
   relative to the LANDER frame.

   The MECA frame is defined as follows:

      -  +Z axis is normal to the MECA mounting surface and points
         from that surface toward the top of the module;

      -  +X axis is perpendicular to the Z axis and points away from
         the sample compartments side;

      -  +Y completes the right-handed frame;

   The origin of the MECA frame is located at the MECA reference
   mounting hole.

   This diagram illustrates the MECA frame:

                  .~ ~ ~ ~ ~ ~ ~.
                  |   +Y solar  |
                  `     panel   '
                   \           /   __
                    `.       .'   | _|
                      `--H--'     //
                      ___H_______//
                     /   .'  \    \
                    /    \ +Zmeca(out)
                   /      o   .'    \ 
             - +Xlnd    .' \.'      |
            | =====|<-.'---x\       |
             --     <' +Zlnd \      |
                +Xmeca  (in)  V +Ymeca             _
                    \             o==============='_' RA
                     \____________/    
                         H       \\
                      .--H--.     \\_
                    .'       `.   |__|
                   /           \
                  .  -Y solar   .
                  |    panel    |
                  `~ ~ ~ ~ ~ ~ ~'

   As seen on the diagram the MECA +Z axis points up -- in the
   direction opposite to the LANDER +Z axis. The MECA +Y axis is 15.0
   degrees off the LANDER -Y axis toward the LANDER -X axis.

   The following set of rotation angles defines the orientation of the
   MECA frame:

      M = [ 0.0 ]  [ -165.0 ]  [ 180.0 ]
                 X           Z          Y

   where M is the matrix rotating vectors from the LANDER frame to the
   MECA frame.

   Since the frame definition below contains the reverse
   transformation, i.e. from the MECA frame to the LANDER frame, the
   order of rotations is reversed and the signs of rotation angles are
   changed to the opposite ones.

   \begindata

      FRAME_PHX_MECA             =  -84600
      FRAME_-84600_NAME          = 'PHX_MECA'
      FRAME_-84600_CLASS         =  4
      FRAME_-84600_CLASS_ID      =  -84600
      FRAME_-84600_CENTER        =  -84

      TKFRAME_-84600_RELATIVE    = 'PHX_LANDER'
      TKFRAME_-84600_SPEC        = 'ANGLES'
      TKFRAME_-84600_UNITS       = 'DEGREES'
      TKFRAME_-84600_AXES        = (   2,       3,      1     )
      TKFRAME_-84600_ANGLES      = ( 180.000, 165.000,  0.000 )

   \begintext


PHX Antenna Frames
-------------------------------------------------------------------------------

   The PHX Antenna frames are fixed offset frames with their
   orientation given relative either to the LANDER CRUISE frame or the
   LANDER Mechanical frame. The MGA and LGA1 are used only during the
   Cruise phase, and are specified with respect to the Lander Cruise
   frame. The Wrap Around Patch EDL LGA is used only during the EDL
   phase, and is specified with respect to the Lander Cruise frame. The
   UHF HELIX and UHF MONOPOLE antennas are used only during the landed
   phase and are specified with respect to the Lander Mechanical frame.
 
   All antenna frames are defined such that +Z axis is the antenna
   boresight and +X axis is lined up with the reference direction for
   the antenna pattern clock angle.


Medium Gain Antenna
-------------------

   The Phoenix Lander Medium Gain Antenna (MGA) is used only during the
   Cruise phase. In the PHX_LANDER_CRUISE frame, the antenna boresight
   boresight (+Z axis) points along this vector ([5]):

      -0.84339142950936  -0.16496406753543   0.51134895428888

   (In this version of the FK the +X and +Y axes are set arbitrarily
   produce in a right-handed frame.)

   The PHX_LANDER_CRUISE frame can be transformed to the PHX_MGA frame
   by two rotations: first by -168.93289225 degrees about the Z axis,
   then by 59.24627525 degrees about Y axis. Since the frame definition
   below contains the reverse transformation (i.e. from the PHX_MGA
   frame to the PHX_LANDER_CRUISE frame), the order and the signs of
   the rotations are reversed.

   \begindata

      FRAME_PHX_MGA              = -84410
      FRAME_-84410_NAME          = 'PHX_MGA'
      FRAME_-84410_CLASS         = 4
      FRAME_-84410_CLASS_ID      = -84410
      FRAME_-84410_CENTER        = -84

      TKFRAME_-84410_SPEC        = 'ANGLES'
      TKFRAME_-84410_RELATIVE    = 'PHX_LANDER_CRUISE'
      TKFRAME_-84410_ANGLES      = ( 0.0, 168.93289225, -59.24627525 )
      TKFRAME_-84410_AXES        = ( 1,     3,            2          )
      TKFRAME_-84410_UNITS       = 'DEGREES'

   \begintext


Cruise Low Gain Antenna
-----------------------

   The Phoenix Lander Cruise Low Gain Antenna (LGA1) is used only
   during the Cruise phase of the mission. Its boresight (+Z axis)
   points along the -X axis of the PHX_LANDER_CRUISE frame, and its +X
   axis is 22.5 degrees off the cruise frame -Z axis toward the cruise
   frame -Y axis, and +Y completes the right-handed frame.

   The PHX_LANDER_CRUISE frame can be transformed to the PHX_LGA1 frame
   by two rotations: first by -90 degrees about the Y axis, then by
   -157.5 degrees about Z axis. Since the frame definition below
   contains the reverse transformation (i.e. from the PHX_LGA1 frame to
   the PHX_LANDER_CRUISE frame), the signs of the rotations and the
   order of axes are reversed.

   \begindata

      FRAME_PHX_LGA1             = -84420
      FRAME_-84420_NAME          = 'PHX_LGA1'
      FRAME_-84420_CLASS         = 4
      FRAME_-84420_CLASS_ID      = -84420
      FRAME_-84420_CENTER        = -84

      TKFRAME_-84420_SPEC        = 'ANGLES'
      TKFRAME_-84420_RELATIVE    = 'PHX_LANDER_CRUISE'
      TKFRAME_-84420_ANGLES      = ( 0.0, 90.0, 157.5 )
      TKFRAME_-84420_AXES        = ( 1,    2,   3     )
      TKFRAME_-84420_UNITS       = 'DEGREES'

   \begintext


Wrap Around Patch EDL Antenna
-----------------------------

   The Phoenix Wrap Around Patch EDL Antenna (LGA_EDL_WPA) is used only
   during the EDL phase of the mission. With respect to the
   PHX_LANDER_CRUISE frame, its boresight (+Z axis) points along the
   cruise -X axis, +Y points in the direction of the cruise +Y axis,
   and +X completes the right-handed frame.

   The PHX_LANDER_CRUISE frame can be transformed into the
   PHX_LGA_EDL_WPA frame by a single -90 degree rotation about the Y
   axis. Since the frame definition below contains the reverse
   transformation (i.e. the PHX_LGA_EDL_WPA to PHX_LANDER_CRUISE), the
   sign of the rotation is reversed.

   \begindata

      FRAME_PHX_LGA_EDL_WPA      = -84430
      FRAME_-84430_NAME          = 'PHX_LGA_EDL_WPA'
      FRAME_-84430_CLASS         = 4
      FRAME_-84430_CLASS_ID      = -84430
      FRAME_-84430_CENTER        = -84

      TKFRAME_-84430_SPEC        = 'ANGLES'
      TKFRAME_-84430_RELATIVE    = 'PHX_LANDER_CRUISE'
      TKFRAME_-84430_ANGLES      = ( 0.0, 90.0,  0.0 )
      TKFRAME_-84430_AXES        = ( 3,    2,    1   )
      TKFRAME_-84430_UNITS       = 'DEGREES'

   \begintext


UHF HELIX Antenna
-----------------------

   The Phoenix Lander UHF HELIX Antenna (UHF_HELIX) is used only during
   the landed phase of the mission. With respect to the PHX_LANDER
   frame, its boresight +Z points along the -Z, +X points in the
   direction of +X, and +Y completes the right-handed frame.

   The PHX_LANDER frame can be transformed into the PHX_UHF_HELIX frame
   by a single 180 degree rotation about the X axis.

   \begindata

      FRAME_PHX_UHF_HELIX        = -84440
      FRAME_-84440_NAME          = 'PHX_UHF_HELIX'
      FRAME_-84440_CLASS         = 4
      FRAME_-84440_CLASS_ID      = -84440
      FRAME_-84440_CENTER        = -84

      TKFRAME_-84440_SPEC        = 'ANGLES'
      TKFRAME_-84440_RELATIVE    = 'PHX_LANDER'
      TKFRAME_-84440_ANGLES      = ( 0.0,  0.0, 180.0 )
      TKFRAME_-84440_AXES        = ( 3,    2,     1   )
      TKFRAME_-84440_UNITS       = 'DEGREES'

   \begintext


UHF MONOPOLE Antenna
-----------------------

   The Phoenix Lander UHF MONOPOLE Antenna (UHF_MONOPOLE) is used only
   during the landed phase of the mission.  With respect to the
   PHX_LANDER frame, its boresight +Z points along the -Z, +X points in
   the direction of +X, and +Y completes the right-handed frame.

   The PHX_LANDER frame can be transformed into the PHX_UHF_MONOPOLE
   frame by a single 180 degree rotation about the X axis.

   \begindata

      FRAME_PHX_UHF_MONOPOLE     = -84450
      FRAME_-84450_NAME          = 'PHX_UHF_MONOPOLE'
      FRAME_-84450_CLASS         = 4
      FRAME_-84450_CLASS_ID      = -84450
      FRAME_-84450_CENTER        = -84

      TKFRAME_-84450_SPEC        = 'ANGLES'
      TKFRAME_-84450_RELATIVE    = 'PHX_LANDER'
      TKFRAME_-84450_ANGLES      = ( 0.0,  0.0, 180.0 )
      TKFRAME_-84450_AXES        = ( 3,    2,     1   )
      TKFRAME_-84450_UNITS       = 'DEGREES'

   \begintext


PHX NAIF ID Codes -- Definition Section
-------------------------------------------------------------------------------

   This section contains name to NAIF ID mappings for PHX.

   \begindata

      NAIF_BODY_NAME += ( 'PHX'                          )
      NAIF_BODY_CODE += ( -84                            )

      NAIF_BODY_NAME += ( 'PHX_LANDING_SITE'             )
      NAIF_BODY_CODE += ( -84900                         )

      NAIF_BODY_NAME += ( 'PHX_LANDER'                   )
      NAIF_BODY_CODE += ( -84000                         )

      NAIF_BODY_NAME += ( 'PHX_PAYLOAD'                  )
      NAIF_BODY_CODE += ( -84100                         )

      NAIF_BODY_NAME += ( 'PHX_SSI_HEAD'                 )
      NAIF_BODY_CODE += ( -84111                         )

      NAIF_BODY_NAME += ( 'PHX_SSI_LEFT_EYE'             )
      NAIF_BODY_CODE += ( -84112                         )

      NAIF_BODY_NAME += ( 'PHX_SSI_RIGHT_EYE'            )
      NAIF_BODY_CODE += ( -84113                         )

      NAIF_BODY_NAME += ( 'PHX_SSI_CAL_TARGET_1'         )
      NAIF_BODY_CODE += ( -84114                         )

      NAIF_BODY_NAME += ( 'PHX_SSI_CAL_TARGET_2'         )
      NAIF_BODY_CODE += ( -84115                         )

      NAIF_BODY_NAME += ( 'PHX_SSI_CAL_TARGET_3'         )
      NAIF_BODY_CODE += ( -84116                         )

      NAIF_BODY_NAME += ( 'PHX_SSI_REF_MARK_1'           )
      NAIF_BODY_CODE += ( -84117                         )

      NAIF_BODY_NAME += ( 'PHX_SSI_REF_MARK_2'           )
      NAIF_BODY_CODE += ( -84118                         )

      NAIF_BODY_NAME += ( 'PHX_SSI_REF_MARK_3'           )
      NAIF_BODY_CODE += ( -84119                         )

      NAIF_BODY_NAME += ( 'PHX_RA_TORSO'                 )
      NAIF_BODY_CODE += ( -84121                         )

      NAIF_BODY_NAME += ( 'PHX_RA_SHOULDER'              )
      NAIF_BODY_CODE += ( -84122                         )

      NAIF_BODY_NAME += ( 'PHX_RA_ELBOW'                 )
      NAIF_BODY_CODE += ( -84123                         )

      NAIF_BODY_NAME += ( 'PHX_RA_WRIST'                 )
      NAIF_BODY_CODE += ( -84124                         )

      NAIF_BODY_NAME += ( 'PHX_RA_CAMERA'                )
      NAIF_BODY_CODE += ( -84125                         )

      NAIF_BODY_NAME += ( 'PHX_RAC'                      )
      NAIF_BODY_CODE += ( -84125                         )

      NAIF_BODY_NAME += ( 'PHX_RA_CAMERA_EDGE'           )
      NAIF_BODY_CODE += ( -84131                         )

      NAIF_BODY_NAME += ( 'PHX_RAC_EDGE'                 )
      NAIF_BODY_CODE += ( -84131                         )

      NAIF_BODY_NAME += ( 'PHX_RA_TECP'                  )
      NAIF_BODY_CODE += ( -84127                         )

      NAIF_BODY_NAME += ( 'PHX_RA_SCOOP'                 )
      NAIF_BODY_CODE += ( -84128                         )

      NAIF_BODY_NAME += ( 'PHX_RA_BLADE'                 )
      NAIF_BODY_CODE += ( -84129                         )

      NAIF_BODY_NAME += ( 'PHX_RA_ISAD'                  )
      NAIF_BODY_CODE += ( -84130                         )

      NAIF_BODY_NAME += ( 'PHX_MET_MAST'                 )
      NAIF_BODY_CODE += ( -84140                         )

      NAIF_BODY_NAME += ( 'PHX_MARDI'                    )
      NAIF_BODY_CODE += ( -84200                         )

      NAIF_BODY_NAME += ( 'PHX_LIDAR'                    )
      NAIF_BODY_CODE += ( -84300                         )

      NAIF_BODY_NAME += ( 'PHX_TEGA'                     )
      NAIF_BODY_CODE += ( -84500                         )

      NAIF_BODY_NAME += ( 'PHX_TEGA_TA'                  )
      NAIF_BODY_CODE += ( -84510                         )

      NAIF_BODY_NAME += ( 'PHX_TEGA_EGA'                 )
      NAIF_BODY_CODE += ( -84520                         )

      NAIF_BODY_NAME += ( 'PHX_MECA'                     )
      NAIF_BODY_CODE += ( -84600                         )

      NAIF_BODY_NAME += ( 'PHX_MGA'                      )
      NAIF_BODY_CODE += ( -84410                         )

      NAIF_BODY_NAME += ( 'PHX_LGA1'                     )
      NAIF_BODY_CODE += ( -84420                         )

      NAIF_BODY_NAME += ( 'PHX_LGA_EDL_WPA'              )
      NAIF_BODY_CODE += ( -84430                         )

      NAIF_BODY_NAME += ( 'PHX_UHF_HELIX'                )
      NAIF_BODY_CODE += ( -84440                         )

      NAIF_BODY_NAME += ( 'PHX_UHF_MONOPOLE'             )
      NAIF_BODY_CODE += ( -84450                         )

   \begintext

