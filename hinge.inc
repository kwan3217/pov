union {
   box {
      <3.5, 0, -0.5>, <4.5, 3, 0.5>
   }
   
   box {
      <0, -0.5, -0.5>, <5, 0.5, 0.5>
      rotate z*degrees(atan(3/4))
   }
   
   cylinder {
      <4, 3, -0.5>, <4, 3, 0.5>, 0.5
   }
   
   cylinder {
      <4, 0, -0.5>, <4, 0, 0.5>, 0.5
   }
   
   cylinder {
      <0, 0, -0.5>, <0, 0, 0.5>, 0.5
   }
   
   box {
      <1.52942, -1.40023, -0.5>, <4.24816, 0.485171, 0.5>
      rotate z*30
   }
   
   box {
      <0, -0.5, -0.5>, <4, 0.5, 0.5>
   }
   
   pigment {
      color rgb <0.3, 1, 0.3>
   }
}

light_source {
   <4, 5, -5>, rgb <1, 1, 1>
}

camera {
   perspective
   location <2.33333, 1.46667, -5>
   sky <0, 1, 0>
   direction <0, 0, 1>
   right <1.33333, 0, 0>
   up <0, 1, 0>
   look_at <2.23333, 1.23333, -0.133333>
}
