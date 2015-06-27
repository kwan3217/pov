sphere {
  0,1
  pigment {color rgb <0,0,1>}
  finish {
    ambient 1
    diffuse -1
    brilliance 0.5
  }
}

light_source {
  <20,20,-20>*10000
  color rgb 1
}

camera {
  location <0,2,-5>
  look_at <0,0,0>
}
