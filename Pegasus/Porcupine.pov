#declare Smooth=1;
#include "L1011-2a.mesh2"

object {
  L1011Mesh
  pigment {color rgb <1,1,0>}
}
#local VectorLen=1;
#local VectorRad=0.01;
#local I=0;
union {
#while(I<dimension_size(L1011_normal_indices,1))
  #declare FaceIndex=L1011_face_indices[I];
  #declare FaceVectors=array[3] {
    L1011_vertex_vectors[FaceIndex.x],
    L1011_vertex_vectors[FaceIndex.y],
    L1011_vertex_vectors[FaceIndex.z]
  }
  #declare NormalIndex=L1011_normal_indices[I];
  #declare NormalVectors=array[3] {
    L1011_normal_vectors[NormalIndex.x],
    L1011_normal_vectors[NormalIndex.y],
    L1011_normal_vectors[NormalIndex.z]
  }
  #local J=0;
  #while(J<3)
    cylinder {
      FaceVectors[J],FaceVectors[J]+NormalVectors[J]*VectorLen,VectorRad
    }
    #local J=J+1;
  #end
  #local I=I+1;
#end
  pigment {color rgb <0,1,0>}
  translate -x*(L1011_Min.x+L1011_Max.x)/2
  translate -z*(L1011_Min.z+L1011_Max.z)/2
  translate -y*(L1011_Min.y+L1011_Max.y)/2
}
#local I=0;
union {
#while(I<dimension_size(L1011_normal_indices,1))
  #declare FaceIndex=L1011_face_indices[I];
  #declare FaceVectors=array[3] {
    L1011_vertex_vectors[FaceIndex.x],
    L1011_vertex_vectors[FaceIndex.y],
    L1011_vertex_vectors[FaceIndex.z]
  }
  #declare NormalIndex=L1011_normal_indices[I];
  #declare NormalVectors=array[3] {
    L1011_normal_vectors[NormalIndex.x],
    L1011_normal_vectors[NormalIndex.y],
    L1011_normal_vectors[NormalIndex.z]
  }
  #local J=0;
  #while(J<3)
    cylinder {
      FaceVectors[J],FaceVectors[J]-NormalVectors[J]*VectorLen,VectorRad
    }
    #local J=J+1;
  #end
  #local I=I+1;
#end
  pigment {color rgb <1,0,0>}
  translate -x*(L1011_Min.x+L1011_Max.x)/2
  translate -z*(L1011_Min.z+L1011_Max.z)/2
  translate -y*(L1011_Min.y+L1011_Max.y)/2
}
#local I=0;
union {
#while(I<dimension_size(L1011_normal_indices,1))
  #declare FaceIndex=L1011_face_indices[I];
  #declare FaceVectors=array[3] {
    L1011_vertex_vectors[FaceIndex.x],
    L1011_vertex_vectors[FaceIndex.y],
    L1011_vertex_vectors[FaceIndex.z]
  }
  #declare FaceCenter=(FaceVectors[0]+FaceVectors[1]+FaceVectors[2])/3;
  #declare Normal=vnormalize(vcross(FaceVectors[1]-FaceVectors[0],FaceVectors[2]-FaceVectors[1]));
  cylinder {
    FaceCenter,FaceCenter+Normal*VectorLen,VectorRad
  }
  #local I=I+1;
#end
  pigment {color rgb <0,0,1>}
  translate -x*(L1011_Min.x+L1011_Max.x)/2
  translate -z*(L1011_Min.z+L1011_Max.z)/2
  translate -y*(L1011_Min.y+L1011_Max.y)/2
}


light_source {
  <20,20,-20>*100000
  color rgb 1
}

camera {
  location <0,2,-5>*10
  look_at <0,0,0>
  angle 20
}
