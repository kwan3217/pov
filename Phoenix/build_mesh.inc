#fopen ouf WriteMesh write

#write(ouf,"mesh2 {\n")
#write(ouf,"  vertex_vectors {\n")
#write(ouf,"    ",Nx*Ny,"\n")
#declare Iy=0;
#while(Iy<Ny)
  #declare Ix=0;
  #while(Ix<Nx)              
    #local V=Vec(Ix,Iy);
#write(ouf,"    <"str(V.x,0,6),",",str(V.y,0,6),",",str(V.z,0,6)">\n")
    #declare Ix=Ix+1;
  #end
  #declare Iy=Iy+1; 
#end
#write(ouf,"  }\n")
#write(ouf,"  uv_vectors {\n")
#write(ouf,"    ",Nx*Ny,"\n")
#declare Iy=0;
#while(Iy<Ny)       
  #declare Ix=0;
  #while(Ix<Nx)          
    #local V=UV(Ix,Iy);
#write(ouf,"    <"str(V.u,0,6),",",str(V.v,0,6)">\n")
    #declare Ix=Ix+1;
  #end
  #declare Iy=Iy+1; 
#end
#write(ouf,"  }\n")
#write(ouf,"  face_indices {\n")
#write(ouf,"    ",(Nx-1)*(Ny-1)*2,"\n")
#declare Iy=0;
#while(Iy<Ny-1)       
  #declare Ix=0;
  #while(Ix<Nx-1) 
#write(ouf,"        <",str(Iy*Nx+Ix,  0,0),",",str( Iy   *Nx+Ix+1,0,0),",",str((Iy+1)*Nx+Ix,0,0),">\n")
#write(ouf,"        <",str(Iy*Nx+Ix+1,0,0),",",str((Iy+1)*Nx+Ix+1,0,0),",",str((Iy+1)*Nx+Ix,0,0),">\n")
    #declare Ix=Ix+1;
  #end
  #declare Iy=Iy+1; 
#end
#write(ouf,"  }\n")
#write(ouf,"}\n")
                   
#fclose ouf
#include WriteMesh
