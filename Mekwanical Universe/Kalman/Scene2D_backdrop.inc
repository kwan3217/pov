plane {
  -y,0
  pigment {checker color rgb 1 color rgb 0.75}
}


camera {
  right x*16/9
  sky z
  location <0,-9,0.5>
  look_at <0,0,0.5>
}

light_source {
  <20,-20,20>*1000
  color rgb 1
//  area_light <0,2,0>,<0,0,2> 5 5 circular orient adaptive 1
}


