#include "phx_topo.inc"

#declare Lat=radians(68.15);
#declare Lon=radians(234);
#declare R=3396000+50000;
camera {
  location (<cos(Lat)*cos(Lon),cos(Lat)*sin(Lon),sin(Lat)>*R)
  look_at (<cos(Lat)*cos(Lon),cos(Lat)*sin(Lon),sin(Lat)>*(R-50000))
}           

light_source {
  (<cos(Lat)*cos(Lon),cos(Lat)*sin(Lon),sin(Lat)>*R)
  color rgb 1
}
               
                                                                                
