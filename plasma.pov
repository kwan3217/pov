difference {
  sphere {
    0,1
  }
  plane {
    x,0
  }
  pigment {     
    gradient x
    color_map {
      [ 0.0  color rgbt<1.00,1,1,1>]
      [ 0.2  color rgbt<1.00,1,1,1>]
      [ 0.5  color rgbt<1.00,0.5,0,0.5>]
      [ 0.6  color rgbt<1.00,1,0,0.25>]
      [ 0.8  color rgbt<1.00,1,1,0>]
      [ 1.0  color rgbt<1.00,1,1,0>]
    } // color_map
    scale 1.2
    translate -x*(0.21-clock*5)
    turbulence 0.21
    translate -x*clock*5
  } 
  scale <10,1,1>
  translate -5*x
  finish {ambient 1 diffuse 0}
}         

background {rgb <0,0.5,1>}

camera {
  location <0,0,-5>*2
  look_at 0
}

light_source {
  <20,20,-20>*100
  color rgb 1.5
}

   