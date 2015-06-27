//Cassini.pov

#include "Cassini.inc"

object {
  Cassini
	OrientCassini(0.598014,-0.371229,0.657678,0.268381)
}

light_source {
  <20,0,-20>*1000
  color 1.5
}

light_source {
  <-20,0,-20>*1000
  color 1.5
}

camera {
  location <0,3,-10>*3
  look_at <0,0,0>
}



