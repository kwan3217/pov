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
        #if(dimension_size(AnimGroup,1)>I)
          #if(AnimGroup[I]>=0)
            Animate(AnimGroup[I],AnimControl,AnimParent,AnimType,AnimVec)
          #end
        #end
      }
      #local I=I+1;
    #end
    rotate y*90
  }
#end

#include "transforms.inc"
#macro Linterp(X0,Y0,X1,Y1,X)
  #local T=(X-X0)/(X1-X0);
  (T*Y1+(1-T)*Y0)
#end

#macro Animate(AnimGroup,AnimControl,AnimParent,AnimType,AnimVec)
  #switch(AnimType[AnimGroup])
    #case(0) //Translate
      translate AnimVec[AnimGroup][0]*AnimControl[AnimGroup]
      #break
    #case(1) //Scale
      translate -AnimVec[AnimGroup][0]
      scale Linterp(0,<1,1,1>,1,AnimVec[AnimGroup][1],AnimControl[AnimGroup])
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

