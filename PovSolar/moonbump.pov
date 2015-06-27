height_field {
  png "moonbump.png"
  pigment {
    image_map {
      png "moonmap.png"
      map_type 0
      interpolate 2
    }
    rotate x*90
    translate x*0.5
  }
  
  scale <2,0.10,1>
}

light_source {
  <0,20,-20>
  color rgb 1.5
}

camera {
  location <-2,2,-5>
  look_at <1.5,0.05,0.5>
  angle 5
}