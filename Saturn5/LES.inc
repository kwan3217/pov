#declare LESLeg = union {
   cylinder {
      <17, -282.46, 17>, <22, -390.54, 22>, 2
   }
   
   cylinder {
      <-21, -370, 21>, <21, -370, 21>, 1
   }
   
   cylinder {
      <-20, -350, 20>, <20, -350, 20>, 1
   }
   
   cylinder {
      <-20, -350, 20>, <21, -370, 21>, 1
   }
   
   cylinder {
      <20, -350, 20>, <0, -320, 13>, 1
   }
   
   cylinder {
      <20, -350, 20>, <13, -320, 0>, 1
   }
   
   cylinder {
      <17, -282, 17>, <0, -320, 13>, 1
   }
   
   cylinder {
      <17, -282, 17>, <13, -320, 0>, 1
   }
   
   cone {
      <22, -295, 0>, 10,
      <0, -260, 0>, 0.5
      open
   }
   
   cylinder {
      <6, -370, 21>, <21, -379, 21>, 1
   }
   
   cylinder {
      <21, -370, 6>, <21, -379, 21>, 1
   }
   
   box {
      <20, -390.54, -4>, <35, -420, 4>
      rotate y*(-45)
   }
   
   cylinder {
      <17, -282.46, 17>, <0, -245.57, 0>, 2
   }
   
   sphere {
      <17, -282.46, 17>, 2
   }
}

#declare LES = union {
   //*PMName LES
   
   torus {
      13, 1
      translate y*(-320)
   }
   
   object {
      LESLeg
   }
   
   object {
      LESLeg
      rotate y*90
   }
   
   object {
      LESLeg
      rotate y*180
   }
   
   object {
      LESLeg
      rotate y*270
   }
   
   cone {
      <0, -262.46, 0>, 13,
      <0, -282.46, 0>, 25.595
   }
   
   difference {
      cylinder {
         <0, -37.06, 0>, <0, -262.46, 0>, 13
      }
      
      cone {
         <0, -75, 0>, 0,
         <24.8492, -120.027, 0>, 7.0571
      }
      
      cone {
         <0, -75, 0>, 0,
         <-24.849, -120.03, 0>, 7.0571
      }
   }
   
   cone {
      <0, -2.9647, 0>, 3.86369,
      <0, -37.06, 0>, 13
   }
   
   sphere {
      <0, -4, 0>, 4
   }
   
   bounded_by {
      cylinder {
         <0, 0, 0>, <0, -420, 0>, 36
      }
   }
}