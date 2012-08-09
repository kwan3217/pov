cylinder {
  -y,y,0.5
  pigment {color rgb <1,1,1>}
  finish {brilliance 1-clock}
}

light_source {
  <20,0,-5>*10000
  color rgb 1
}

text {
  ttf "arialn.ttf" str(1-clock,0,2)
  0,0
  pigment {color rgb <1,0,0>}
  finish {ambient 1 diffuse 0}
  scale 0.25
  translate y*1.2
}

camera {
  orthographic
  location <0,0,-5>
  look_at <0,0,0>
}
