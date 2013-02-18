#macro Matrix(Row1,Row2,Row3,Row4)
  matrix <Row1.x,Row1.y,Row1.z,
          Row2.x,Row2.y,Row2.z,
	  Row3.x,Row3.y,Row3.z,
	  Row4.x,Row4.y,Row4.z>
#end

#macro MatrixV(Row1,Row2,Row3,Row4,V)
  (<Row1.x*V.x+Row2.x*V.y+Row3.x*V.z+Row4.x,	  
    Row1.y*V.x+Row2.y*V.y+Row3.y*V.z+Row4.y,
    Row1.z*V.x+Row2.z*V.y+Row3.z*V.z+Row4.z>)
#end

#macro RotateAlso(RotVec,AlsoVec)
  rotate RotVec
  #declare AlsoVec=vrotate(AlsoVec,RotVec);
#end

#macro TranslateAlso(TraVec,AlsoVec)
  translate TraVec
  #declare AlsoVec=AlsoVec+TraVec;
#end

#macro ScaleAlso(ScaVec,AlsoVec)
  scale ScaVec
  #declare AlsoVec=AlsoVec*ScaVec;
#end

#macro MatrixAlso(Row1,Row2,Row3,Row4,AlsoVec)
  Matrix(Row1,Row2,Row3,Row4)
  #declare AlsoVec=MatrixV(Row1,Row2,Row3,Row4,AlsoVec);
#end

#macro RotateAlso2(RotVec,AlsoVec1,AlsoVec2)
  rotate RotVec
  #declare AlsoVec1=vrotate(AlsoVec1,RotVec);
  #declare AlsoVec2=vrotate(AlsoVec2,RotVec);
#end

#macro TranslateAlso2(TraVec,AlsoVec1,AlsoVec2)
  translate TraVec
  #declare AlsoVec1=AlsoVec1+TraVec;
  #declare AlsoVec2=AlsoVec2+TraVec;
#end

#macro ScaleAlso2(ScaVec,AlsoVec1,AlsoVec2)
  scale ScaVec
  #declare AlsoVec1=AlsoVec1*ScaVec;
  #declare AlsoVec2=AlsoVec2*ScaVec;
#end

#macro MatrixAlso2(Row1,Row2,Row3,Row4,AlsoVec1,AlsoVec2)
  Matrix(Row1,Row2,Row3,Row4)
  #declare AlsoVec1=MatxVect(Row1,Row2,Row3,Row4,AlsoVec1);
  #declare AlsoVec2=MatxVect(Row1,Row2,Row3,Row4,AlsoVec2);
#end

#macro LocationLookAt(Location,LookAt,Sky)
  //Location and LookAt are locations with definite distances from the origin
  //Sky is just a direction, equavalently a location an infinite distance away
  //Puts old origin at Location
  //Points +z axis along line from Location towards LookAt
  //Points +y towards Sky as much as possible
  #local NX=vnormalize(LookAt-Location);
  #local NZ=vnormalize(vcross(NX,Sky));
  #local NY=vcross(NZ,NX);
  Matrix(-NZ,NY,NX,Location)
#end

#macro LocationLookAtV(Location,LookAt,Sky,V)
  #local NX=vnormalize(LookAt-Location);
  #local NZ=vnormalize(vcross(NX,Sky));
  #local NY=vcross(NZ,NX);
  (MatrixV(-NZ,NY,NX,Location,V))
#end

#macro LocationLookAtAlso(Location,LookAt,Sky,AlsoVec)
  #local NX=vnormalize(LookAt-Location);
  #local NZ=vnormalize(vcross(NX,Sky));
  #local NY=vcross(NZ,NX);
  MatrixAlso(-NZ,NY,NX,Location,AlsoVec)
#end

#macro LocationLookAtAlso2(Location,LookAt,Sky,AlsoVec1,AlsoVec2)
  #local NX=vnormalize(LookAt-Location);
  #local NZ=vnormalize(vcross(NX,Sky));
  #local NY=vcross(NZ,NX);
  MatrixAlso2(-NZ,NY,NX,Location,AlsoVec1,AlsoVec2)
#end
