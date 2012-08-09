sphere {
  0,5
  pigment {
    image_map {
      tile_map {
        6,6
        [0,0 png "1test.png"]
        [0,2 png "1test.png"]
        [0,4 png "1test.png"]
        [1,1 png "2test.png"]
        [1,3 png "2test.png"]
        [2,0 png "3test.png"]
        [2,2 png "3test.png"]
        [2,4 png "3test.png"]
        [3,1 png "4test.png"]
        [3,3 png "4test.png"]
        [4,0 png "5test.png"]
        [4,2 png "5test.png"]
        [4,4 png "5test.png"]
      }
      map_type 0
    }
  }
}

light_source {
  <20,20,-20>*1000
  color 1.5
}

camera {
  location <0,2,-5>*2
  look_at <0,0,0>
}