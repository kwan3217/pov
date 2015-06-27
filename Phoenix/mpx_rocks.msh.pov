#ifndef(MeshAmbient)#declare MeshAmbient=0.1;#end
#local mpx_rocks_Group=array[1] {
  mesh2 { //Group 0
    vertex_vectors { 
      4
      <250.746,0.0,250.746>,
      <250.746,0.0,-250.746>,
      <-250.746,0.0,250.746>,
      <-250.746,0.0,-250.746>
    }
    normal_vectors { 
      4
      <0.0,1.0,0.0>,
      <0.0,1.0,0.0>,
      <0.0,1.0,0.0>,
      <0.0,1.0,0.0>
    }
    uv_vectors {   
      4
      <4.99785E-4,0.999500453>,
      <4.99547E-4,4.999999999999449E-4>,
      <0.9995,0.999500215>,
      <0.9995,4.999999999999449E-4>
    }
    face_indices {   
      2
      <2,0,3>,
      <3,0,1>,
    }
  },
}
#declare mpx_rocks_GroupMaterial=array[1] {
  1,
}
#local mpx_rocks_GroupTexture=array[1] {
  1,
}
#declare mpx_rocks_Texture=array[2] {
  "",//Ignored
  "B_MPX/mpx_rocks.dds.png",
}
#declare mpx_rocks_Finish=array[2] {
  <0,0,0>,//Ignored
  <1.000000,1.000000,1.000000>,
}
#declare mpx_rocks_Pigment=array[2] {
  <0,0,0>,//Ignored
  <1.000000,1.000000,1.000000>
}
#macro OrbiterMesh(Group,GroupMaterial,GroupTexture,Texture,Finish,Pigment,AnimControl,AnimGroup,AnimParent,AnimType,AnimVec  )
  #local I=0;
  union {
    #while(I<dimension_size(Group,1))
      object {
        Group[I]
        texture {
          uv_mapping
          finish {ambient MeshAmbient*Finish[GroupMaterial[I]]}
          #if(GroupTexture[I]>0)
            pigment {image_map {png Texture[GroupTexture[I]]}}
          #else
            pigment {color rgb Pigment[GroupMaterial[I]]}
          #end
        }
        #if(AnimGroup[I]>=0)
          Animate(AnimGroup[I],AnimControl,AnimParent,AnimType,AnimVec)
        #end
      }
      #local I=I+1;
    #end
    rotate y*90
  }
#end
#include "transforms.inc"

#macro Animate(AnimGroup,AnimControl,AnimParent,AnimType,AnimVec)
  #switch(AnimType[AnimGroup])
    #case(0) //Translate
      translate AnimVec[AnimGroup][0]*AnimControl[AnimGroup]
      #break
    #case(1) //Scale
      translate -AnimVec[AnimGroup][0]
      scale AnimVec[AnimGroup][1]*AnimControl[AnimGroup]
      translate AnimVec[AnimGroup][0]
      #break
    #case(2) //Rotate
      translate -AnimVec[AnimGroup][0]
      Axis_Rotate_Trans(AnimVec[AnimGroup][1], AnimVec[AnimGroup][2].x*AnimControl[AnimGroup])
      translate AnimVec[AnimGroup][0]
      #break
  #end
  #if(AnimParent[AnimGroup]>=0)
    Animate(AnimParent[AnimGroup],AnimControl,AnimParent,AnimType,AnimVec)
  #end
#end
    
#macro AddTrans(A,V,Parent,Groups,AnimGroup,AnimParent,AnimType,AnimVec)
  #local I=0;
  #while(I<dimension_size(Groups,1))
    #declare AnimGroup[Groups[I]]=A;
    #local I=I+1;
  #end
  #declare AnimParent[A]=Parent;
  #declare AnimType[A]=0;
  #declare AnimVec[A][0]=<V.x,-V.z,V.y>;
#end

#macro AddScale(A,Vc,Vs,Parent,Groups,AnimGroup,AnimParent,AnimType,AnimVec)
  #local I=0;
  #while(I<dimension_size(Groups,1))
    #declare AnimGroup[Groups[I]]=A;
    #local I=I+1;
  #end
  #declare AnimParent[A]=Parent;
  #declare AnimType[A]=1;
  #declare AnimVec[A][0]=<Vc.x,-Vc.z,Vc.y>;
  #declare AnimVec[A][1]=<Vs.x,-Vs.z,Vs.y>;
#end

#macro AddRot(A,Vc,Vs,Amt,Parent,Groups,AnimGroup,AnimParent,AnimType,AnimVec)
  #local I=0;
  #while(I<dimension_size(Groups,1))
    #declare AnimGroup[Groups[I]]=A;
    #local I=I+1;
  #end
  #declare AnimParent[A]=Parent;
  #declare AnimType[A]=2;
  #declare AnimVec[A][0]=<Vc.x,-Vc.z,Vc.y>;
  #declare AnimVec[A][1]=<Vs.x,-Vs.z,Vs.y>;
  #declare AnimVec[A][2]=<Amt,Amt,Amt>;
#end
#macro mpx_rocks(AnimControl,AnimGroup,AnimParent,AnimType,AnimVec)
  OrbiterMesh(
    mpx_rocks_Group,mpx_rocks_GroupMaterial,mpx_rocks_GroupTexture,mpx_rocks_Texture,mpx_rocks_Finish,mpx_rocks_Pigment,
    AnimControl,AnimGroup,AnimParent,AnimType,AnimVec
  )
#end

#declare mpx_rocks_AnimGroup=array[dimension_size(mpx_rocks_Group,1)]
#local mpx_rocks_N_Anim=1;
#declare mpx_rocks_AnimParent=array[mpx_rocks_N_Anim]
#declare mpx_rocks_AnimType=array[mpx_rocks_N_Anim]
#declare mpx_rocks_AnimVec=array[mpx_rocks_N_Anim][3]

#local I=0;
#while(I<dimension_size(mpx_rocks_AnimGroup,1))
  #declare mpx_rocks_AnimGroup[I]=-1;
  #local I=I+1;
#end

#local I=0;
#while(I<mpx_rocks_N_Anim)
  #declare mpx_rocks_AnimParent[I]=-1;
  #declare mpx_rocks_AnimType[I]=-1;
  #declare mpx_rocks_AnimVec[I][0]=<0,0,0>;
  #declare mpx_rocks_AnimVec[I][1]=<0,0,0>;
  #declare mpx_rocks_AnimVec[I][2]=<0,0,0>;
  #local I=I+1;
#end
mpx_rocks(array[1] {clock},mpx_rocks_AnimGroup,mpx_rocks_AnimParent,mpx_rocks_AnimType,mpx_rocks_AnimVec)
light_source {
  <20,20,-20>*1000
  color 1
}
camera {
  location <0,2,-5>*0.5
  look_at <0,0,0>
}
