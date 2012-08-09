#declare WriteMesh="phx_topo.mesh2";
object {
  #if(file_exists(WriteMesh))
    #include WriteMesh
  #else
    #include "phx_topo_data.inc"

    #declare Nx=dimension_size(phx_topo_data,2);
    #declare Ny=dimension_size(phx_topo_data,1);
                                          
    #macro Linterp(X0,Y0,X1,Y1,X)
      #local T=(X-X0)/(X1-X0);
      (T*Y1+(1-T)*Y0)
    #end                                   
    #macro Vec(Ix,Iy)
      #local Lat=radians(Linterp(0, 67.6,Ny, 68.7,Iy+0.5));
      #local Lon=radians(Linterp(0,231.5,Nx,236.5,Ix+0.5));
      #local R=3396000+phx_topo_data[Iy][Ix]+1.65;
      (<cos(Lat)*cos(Lon),cos(Lat)*sin(Lon),sin(Lat)>*R)
    #end 
    #macro UV(Ix,Iy)
      <Linterp(0,1,Nx,0,Ix+0.5),Linterp(0,0,Ny,1,Iy+0.5)>
    #end   
    #include "build_mesh.inc"
  #end
  #if(1)        
    finish {ambient 0.5 diffuse 2} 
    pigment {             
      uv_mapping
      image_map {
        png "landing_site_map.png"
      }
    }           
  #else
    pigment {color rgb <1,0.5,0>}
  #end
}

               
                                                                                
