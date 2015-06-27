//Shuttle Boosters
#declare SRB_RAD       = 12.17/2
#declare SRB_SKIRT_RAD = 17.75/2
#declare ET_RAD        = 27.5/2
#declare LEFT_SRB_POS  = -ET_RAD - 0.5 - SRB_RAD
#declare RIGHT_SRB_POS = ET_RAD + 0.5 + SRB_RAD
#declare SRB_NOZZLETHROAT_RAD = 35/12
#declare SRB_NOZZLEEXIT_RAD   = 74.13/12

#declare SRB_BAND =
cylinder {
  <0,0,0>,
  <0,1,0>,
  SRB_RAD+0.1/12
  texture {
    pigment {color Black}
    finish {diffuse 0.6 phong 0.3 phong_size 20}
  }
}

#declare SRB_RED_BAND =
cylinder {
  <0,0,0>,
  <0,1,0>,
  SRB_RAD+0.1/12
  texture {
    pigment {color Red}
    finish {diffuse 0.6 phong 0.4 phong_size 30}
  }
}

#declare SRB_WHITE_BAND =
cylinder {
  <0,0,0>,
  <0,1,0>,
  SRB_RAD+0.1/12
  texture {
    pigment {color White}
    finish {diffuse 0.6 phong 0.4 phong_size 30}
  }
}

#declare SRB_BIG_BAND =
cylinder {
  <0,-0.5,0>,
  <0, 0.5,0>,
  SRB_RAD+10/12
  texture {
    pigment {color White}
    finish {diffuse 0.6 phong 0.3 phong_size 20}
  }
}

#declare SRB_MED_BAND =
cylinder {
  <0,-0.25,0>,
  <0, 0.25,0>,
  SRB_RAD+6/12
  texture {
    pigment {color White}
    finish {diffuse 0.6 phong 0.3 phong_size 20}
  }
}

#declare SRB_NOZZLE_BOOT =
torus
{
  SRB_RAD,
  1.5
  texture {SRB_BOOT_TEXTURE}
}


#declare SRB_FRUSTRUM =
cone {
  <0,0,0>,SRB_SKIRT_RAD
  <0,(1930.63-1837.29)/12,0>,SRB_RAD
  texture {SRB_TEXTURE}
}

#declare SRB_NOZZLE =
cone {
  <0,0,0>, SRB_NOZZLEEXIT_RAD
  <0,9.533,0>, SRB_NOZZLETHROAT_RAD
  texture {SRB_TEXTURE}
}

#declare SRB_ATTACH_POS =
cylinder {
  <-40,0,0>
  <60,0,0>
  0.5
  pigment {color Red}
}

// Right SRB
union {
  cylinder
  {
    <RIGHT_SRB_POS, BASE, 0>,
    <RIGHT_SRB_POS, BASE + 1837.29/12-395/12, 0>,
    12.17/2
    texture {SRB_TEXTURE}
  }
  sphere
  {
    <0, 0, 0>
    13.28/12
    translate <RIGHT_SRB_POS, BASE + (1837.29 - 200 - 13.28)/12,0>
    texture {SRB_TEXTURE}
  }
  cone
  {
    <0,0,0>,  SRB_RAD,
    <0,(395 - 200 - 9.28)/12,0>, 13/12
    translate <RIGHT_SRB_POS, BASE + (1837.29 - 395)/12,0>
    texture {SRB_TEXTURE}
  }

  intersection {
    torus {
        SRB_RAD - 3/12*(SRB_RAD*12-13)/185.72
        3/12
        translate < 0, 3/12, 0>
    }
    cone {
        < 0,      0, 0 >, SRB_RAD + 1/12,
        < 0, 15.477, 0 >, 1.167
    }
    translate <RIGHT_SRB_POS, BASE + (1837.29 - 395)/12,0>
    texture {SRB_TEXTURE}
  }

  intersection {
    torus {
        SRB_RAD - 1.5*(SRB_RAD*12-13)/185.72
        3/12
        translate < 0, 1.5, 0>
    }
    cone {
        < 0,      0, 0 >, SRB_RAD + 1/12,
        < 0, 15.477, 0 >, 1.167
    }
    translate <RIGHT_SRB_POS, BASE + (1837.29 - 395)/12,0>
    texture {SRB_TEXTURE}
  }

  intersection {
    torus {
        SRB_RAD - 3.0*(SRB_RAD*12-13)/185.72
        3/12
        translate < 0, 3.0, 0>
    }
    cone {
        < 0,      0, 0 >, SRB_RAD + 1/12,
        < 0, 15.477, 0 >, 1.167
    }
    translate <RIGHT_SRB_POS, BASE + (1837.29 - 395)/12,0>
    texture {SRB_TEXTURE}
  }

  intersection {
    torus {
        SRB_RAD - 4.5*(SRB_RAD*12-13)/185.72
        3/12
        translate < 0, 4.5, 0>
    }
    cone {
        < 0,      0, 0 >, SRB_RAD + 1/12,
        < 0, 15.477, 0 >, 1.167
    }
    translate <RIGHT_SRB_POS, BASE + (1837.29 - 395)/12,0>
    texture {SRB_TEXTURE}
  }

  intersection {
    torus {
        SRB_RAD - 6.0*(SRB_RAD*12-13)/185.72
        3/12
        translate < 0, 6.0, 0>
    }
    cone {
        < 0,      0, 0 >, SRB_RAD + 1/12,
        < 0, 15.477, 0 >, 1.167
    }
    translate <RIGHT_SRB_POS, BASE + (1837.29 - 395)/12,0>
    texture {SRB_TEXTURE}
  }

  object {SRB_RED_BAND translate <RIGHT_SRB_POS,BASE + (1837.29 - 411)/12>}
  object {SRB_BAND translate <RIGHT_SRB_POS,BASE + (1837.29 -  531.48)/12>}
  object {SRB_BAND translate <RIGHT_SRB_POS,BASE + (1837.29 -  691.48)/12>}
  object {SRB_BAND translate <RIGHT_SRB_POS,BASE + (1837.29 - 1011.48)/12>}
  object {SRB_BAND translate <RIGHT_SRB_POS,BASE + (1837.29 - 1331.48)/12>}
  object {SRB_BAND translate <RIGHT_SRB_POS,BASE + (1837.29 - 1575.92)/12>}
  object {SRB_BAND translate <RIGHT_SRB_POS,BASE + (1837.29 - 1698.00)/12>}
  object {SRB_BAND translate <RIGHT_SRB_POS,BASE + (1837.29 - 1823.85)/12>}
  object {SRB_FRUSTRUM translate <RIGHT_SRB_POS,BASE + (1837.29-1930.637)/12,0>}
  object {SRB_BIG_BAND translate <RIGHT_SRB_POS,BASE + (1837.29 - 1511)/12,0>}
  object {SRB_MED_BAND translate <RIGHT_SRB_POS,BASE + (1837.29 - 1657.5)/12,0>}
  object {SRB_MED_BAND translate <RIGHT_SRB_POS,BASE + (1837.29 - 1733)/12,0>}
  object {SRB_MED_BAND translate <RIGHT_SRB_POS,BASE + (1837.29 - 1777.6)/12,0>}
  object {SRB_MED_BAND translate <RIGHT_SRB_POS,BASE + (1837.29 - 1837.29)/12,0>}
  object {SRB_NOZZLE translate <RIGHT_SRB_POS,BASE + (1837.29 - 1989.6)/12,0>}
  object {SRB_NOZZLE_BOOT translate <RIGHT_SRB_POS,BASE + (1837.29 - 1930.6)/12,0>}
//  object {SRB_ATTACH_POS translate <0,BASE + (1837.29 - 1511)/12,0>}
}

// Left SRB
union {
  cylinder
  {
    <LEFT_SRB_POS, BASE, 0>,
    <LEFT_SRB_POS, BASE + 1837.29/12-395/12, 0>,
    12.17/2
    texture {SRB_TEXTURE}
  }
  sphere
  {
    <0, 0, 0>
    13.28/12
    translate <LEFT_SRB_POS, BASE + (1837.29 - 200 - 13.28)/12,0>
    texture {SRB_TEXTURE}
  }
  cone
  {
    <0,0,0>,  SRB_RAD,
    <0,(395 - 200 - 9.28)/12,0>, 13/12
    translate <-(ET_RAD + 0.5 + SRB_RAD), BASE + (1837.29 - 395)/12,0>
    texture {SRB_TEXTURE}
  }

  intersection {
    torus {
        SRB_RAD - 3/12*(SRB_RAD*12-13)/185.72
        3/12
        translate < 0, 3/12, 0>
    }
    cone {
        < 0,      0, 0 >, SRB_RAD + 1/12,
        < 0, 15.477, 0 >, 1.167
    }
    translate <LEFT_SRB_POS, BASE + (1837.29 - 395)/12,0>
    texture {SRB_TEXTURE}
  }

  intersection {
    torus {
        SRB_RAD - 1.5*(SRB_RAD*12-13)/185.72
        3/12
        translate < 0, 1.5, 0>
    }
    cone {
        < 0,      0, 0 >, SRB_RAD + 1/12,
        < 0, 15.477, 0 >, 1.167
    }
    translate <LEFT_SRB_POS, BASE + (1837.29 - 395)/12,0>
    texture {SRB_TEXTURE}
  }

  intersection {
    torus {
        SRB_RAD - 3.0*(SRB_RAD*12-13)/185.72
        3/12
        translate < 0, 3.0, 0>
    }
    cone {
        < 0,      0, 0 >, SRB_RAD + 1/12,
        < 0, 15.477, 0 >, 1.167
    }
    translate <LEFT_SRB_POS, BASE + (1837.29 - 395)/12,0>
    texture {SRB_TEXTURE}
  }

  intersection {
    torus {
        SRB_RAD - 4.5*(SRB_RAD*12-13)/185.72
        3/12
        translate < 0, 4.5, 0>
    }
    cone {
        < 0,      0, 0 >, SRB_RAD + 1/12,
        < 0, 15.477, 0 >, 1.167
    }
    translate <LEFT_SRB_POS, BASE + (1837.29 - 395)/12,0>
    texture {SRB_TEXTURE}
  }

  intersection {
    torus {
        SRB_RAD - 6.0*(SRB_RAD*12-13)/185.72
        3/12
        translate < 0, 6.0, 0>
    }
    cone {
        < 0,      0, 0 >, SRB_RAD + 1/12,
        < 0, 15.477, 0 >, 1.167
    }
    translate <LEFT_SRB_POS, BASE + (1837.29 - 395)/12,0>
    texture {SRB_TEXTURE}
  }

  object {SRB_RED_BAND translate <LEFT_SRB_POS,BASE + (1837.29 - 411)/12>}
  object {SRB_BAND translate <LEFT_SRB_POS,BASE + (1837.29 - 531.48)/12>}
  object {SRB_BAND translate <LEFT_SRB_POS,BASE + (1837.29 -  691.48)/12>}
  object {SRB_BAND translate <LEFT_SRB_POS,BASE + (1837.29 - 1011.48)/12>}
  object {SRB_BAND translate <LEFT_SRB_POS,BASE + (1837.29 - 1331.48)/12>}
  object {SRB_BAND translate <LEFT_SRB_POS,BASE + (1837.29 - 1575.92)/12>}
  object {SRB_BAND translate <LEFT_SRB_POS,BASE + (1837.29 - 1698.00)/12>}
  object {SRB_BAND translate <LEFT_SRB_POS,BASE + (1837.29 - 1823.85)/12>}
  object {SRB_FRUSTRUM translate <LEFT_SRB_POS,BASE + (1837.29 - 1930.637)/12,0>}
  object {SRB_BIG_BAND translate <LEFT_SRB_POS,BASE + (1837.29 - 1511)/12,0>}
  object {SRB_MED_BAND translate <LEFT_SRB_POS,BASE + (1837.29 - 1657.5)/12,0>}
  object {SRB_MED_BAND translate <LEFT_SRB_POS,BASE + (1837.29 - 1733)/12,0>}
  object {SRB_MED_BAND translate <LEFT_SRB_POS,BASE + (1837.29 - 1777.6)/12,0>}
  object {SRB_MED_BAND translate <LEFT_SRB_POS,BASE + (1837.29 - 1837.29)/12,0>}
  object {SRB_BIG_BAND translate <LEFT_SRB_POS,BASE + (1837.29 - 1511)/12,0>}
  object {SRB_MED_BAND translate <LEFT_SRB_POS,BASE + (1837.29 - 1657.5)/12,0>}
  object {SRB_MED_BAND translate <LEFT_SRB_POS,BASE + (1837.29 - 1733)/12,0>}
  object {SRB_MED_BAND translate <LEFT_SRB_POS,BASE + (1837.29 - 1777.6)/12,0>}
  object {SRB_MED_BAND translate <LEFT_SRB_POS,BASE + (1837.29 - 1837.29)/12,0>}
  object {SRB_NOZZLE translate <LEFT_SRB_POS,BASE + (1837.29 - 1989.6)/12,0>}
  object {SRB_NOZZLE_BOOT translate <LEFT_SRB_POS,BASE + (1837.29 - 1930.6)/12,0>}
}
// ET ================================================================================================

#declare ET_ATTACH_POS =
cylinder {
  <-60*12,0,0>
  < 60*12,0,0>
  0.5*12
  pigment {color Blue}
}

#declare TOP_ANGLE=40*pi/180.00     // in degrees
#declare ET_RADIUS=13.75
#declare SHAPE_HEIGHT=ET_RADIUS*sin(TOP_ANGLE)/(1.0 - cos(TOP_ANGLE))
#declare DISTANCE_X=ET_RADIUS*cos(TOP_ANGLE)/(1.0 - cos(TOP_ANGLE))
#declare TOT_RADIUS=ET_RADIUS/(1.0 - cos(TOP_ANGLE))
#declare NUM_POINTS=7

union {
  cone {
    <0, 2173 - 327.61, 0>, 2.5,
    <0, 2173 - 315.61, 0>, 0.25
  }
  #declare POINT=1
  lathe {
    quadratic_spline
    NUM_POINTS+3,
    <TOT_RADIUS*cos(TOP_ANGLE)-DISTANCE_X,TOT_RADIUS*sin(TOP_ANGLE)>
    <TOT_RADIUS*cos(TOP_ANGLE)-DISTANCE_X,TOT_RADIUS*sin(TOP_ANGLE)>
    #while (POINT <= NUM_POINTS)
      #declare ANGLE=TOP_ANGLE * (NUM_POINTS-POINT)/(NUM_POINTS-1)
      <TOT_RADIUS*cos(ANGLE)-DISTANCE_X,TOT_RADIUS*sin(ANGLE)>
      #declare POINT=POINT+1
    #end
    <ET_RADIUS,0>
    scale <12,12,12>
    translate <0, 2173 - (327.61+SHAPE_HEIGHT*12),0>
    sturm
  }
  cylinder {
    <0, 2173 - (327.61+SHAPE_HEIGHT*12), 0>,
    <0, 2173 - 2090, 0>,
    165.0
  }
  sphere {
    <0, 0, 0>,165.0
    scale <1,0.5,1>
    translate <0, 2173 - 2090, 0>
  }
//  object {ET_ATTACH_POS translate <0,(2173 - 2058), -201>}
  scale <1/12, 1/12, 1/12>
  texture {
    pigment {color rgb<237/255, 100/255, 14/255>}
    finish {diffuse 0.7}
  }
  translate <0, BASE + (211.29)/12,0>
}
