height_field {
  tga "moonheight.tga"
  pigment {
    image_map {
      png "moonmap.png"
      map_type 0
      interpolate 0
    }
    rotate x*90 
    translate -x*(3/1440)
  }
  
  scale <2,0.15,1>
}

light_source {
  <0,20,-20>
  color rgb 1.5
}

camera {
  location <-2,2,-5>
  look_at <0.85,0.05,0.475>
  angle 2.5
}