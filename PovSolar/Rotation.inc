//RotVec is an array of vectors in form <RA,De,W>
#macro Rotate(RotIndex)
  #ifdef(RotVec[RotIndex])
  rotate -y*(RotVec[RotIndex].z+90)
  rotate -z*(90-(RotVec[RotIndex].y))
  rotate -y*RotVec[RotIndex].x
  rotate  x*EarthTilt
	#end
#end

#macro RotateV(V,RotIndex)
  #ifdef(RotVec[RotIndex])
  #local Q=vrotate(V,-y*(RotVec[RotIndex].z+90));
  #local Q=vrotate(Q,-z*(90-RotVec[RotIndex].y));
  #local Q=vrotate(Q,-y*RotVec[RotIndex].x);
  #local Q=vrotate(Q,x*EarthTilt);
	#else
	#local Q=V;
	#end
	
  (Q)
#end
