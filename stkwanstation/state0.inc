//State vector for clock=0.000000
           
#declare S3O2=(sqrt(3))+0.001;

#declare XFac=sqrt(8/3)+0.001;
#declare PosYFac=2*sqrt(3)/3+0.001;
#declare NegYFac=-PosYFac/2;
#declare ZFac=1.001;

#declare BallPos=array[15] {
  <-15,0,0>,
  <15+0,0,0>,
  <15+XFac,-NegYFac,-ZFac>,
  <15+XFac,-NegYFac,ZFac>,
  <15+XFac*2,-NegYFac*2,ZFac*2>,
 
  <15+XFac*2,-NegYFac*2,-ZFac*2>,
  <15+XFac*3,-NegYFac,-ZFac>,
  <15+XFac*4,0,0>
  <15+XFac*2,-NegYFac*2,0>,
  <15+XFac,-PosYFac,0>,

  <15+XFac*2,-NegYFac*2-S3O2*2,0>,
  <15+XFac*3,-PosYFac,0>,
  <15+XFac*3,-NegYFac,ZFac>,
  <15+XFac*2,-NegYFac*2-S3O2,-ZFac>,
  <15+XFac*2,-NegYFac*2-S3O2,ZFac>,
}

#declare BallSpd=array[15] {
  <40,0,0>,
  <0,0,0>,
  <0,0,0>,
  <0,0,0>,
  <0,0,0>,
  <0,0,0>,
  <0,0,0>,
  <0,0,0>,
  <0,0,0>,
  <0,0,0>,
  <0,0,0>,
  <0,0,0>,
  <0,0,0>,
  <0,0,0>,
  <0,0,0>
}
                  
#declare BallFree=array[15] {
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1
}
                  
#declare CueAt=BallPos[0];
#declare AimPoint=BallPos[0]+BallSpd[0];
//ChooseShot(8,14)
