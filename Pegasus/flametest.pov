#declare DensEnding2 = density {
  spherical
  warp {
    turbulence <0.5, 0.25, 0.25>
  }
  color_map {
    [ 0 color rgb <0, 0, 0>      ]
    [ 0.1 color rgb <1, 1, 0.5>  ]
    [ 0.875 color rgb <1, 1, 1>  ]
    [ 1 color rgb <1, 1, -1>     ]
  }
  scale <2.5, 2, 2>
  translate x*2
}

camera {
  location <0, 0, -40>
  look_at <0, 0, 0>
}

union {
  //*PMName Flame
  sphere {
    <0, 0, 0>, 1
    pigment {
      color rgbf <1, 1, 1, 1>
    }
    interior {
      media {
        density {
          DensEnding2
        }
        emission rgb <1, 1, 1>
      }
    }
    no_shadow
    hollow
  }
   
  scale <20, 2, 2>
}
