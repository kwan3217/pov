plane {
  z,0
  pigment {checker}
}

light_source {
  -z*1000000
  color 1.5
}

camera {
  up y*1
  right x*2
  location -z*10
  look_at 0
}
