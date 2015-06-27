/* y^2 + z^2 - x = 0 */
quadric {
  < 0, 1, 1>,
  < 0, 0, 0>,
  <-1, 0, 0>, 0
  scale <-2,1,1>
  pigment {rgbf 1}
  interior {  
    media{
      emission 0.75
      scattering {1, 0.5}
      density { planar
        color_map {
          [0.0 rgb 0]
          [0.6 rgb 0.1]
          [0.7 rgb <0.5,0.25,0>]
          [0.8 rgb <0.8, 0.8, 0.4>]
          [0.9 rgb <1,1,1>]
        }        
        scale 5     
        rotate -z*90
        translate x*(5*clock+0.5)
        warp{turbulence 0.5}
        translate -x*5*clock
        scale <2,1,1>
        
      }
    }
  }
  hollow  
  translate x*2
}

camera {
  location <0,2,-5>
  look_at <0,0,0>
}                

light_source {
  20
  rgb 1
}

