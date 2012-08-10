//F1 Engine Flame

global_settings {max_trace_level 20}

#macro F1Flame(S)
union {
  intersection {
    sphere {
      <0,0,0>,1
      scale<1,50,1>
    }
    plane {
      y,0
    }
    hollow
    pigment {rgbf 1}
    interior {
      media{
        emission <1,1,0.8>/4/S
      }
    }
  }
  scale S
}
#end

#macro J2Flame(S)
union {
  intersection {
    sphere {
      <0,0,0>,1
      scale<1,50,1>
    }
    plane {
      y,0
    }
    hollow
    pigment {rgbf 1}
    interior {
      media{
        emission <0,0.5,1>/2/S
      }
    }
  }
  scale S
}
#end

