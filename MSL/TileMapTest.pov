
#declare MarsColor=<1,0.3,1>;
#declare MarsContrast=0.1;

#declare GalePigment=pigment {     
  average              
  pigment_map {
    [1.0 image_map {tile_map {4 16[3 8 "MarsGale.png"]} map_type spherical }]
  //  [MarsContrast color rgb MarsColor]
  } 
  rotate x*90                 
  scale <1,-1,1>               
}

#declare MarsColor=<1,0,1,1>;

#declare MarsPigment=pigment {
  average            
  pigment_map {     
    [1.0 image_map {png "Mars2k.png" map_type spherical interpolate 2}]
    [MarsContrast color rgbt MarsColor]
  }
  rotate x*90
  scale <1,-1,1>                
}

#declare MtSharpPigment=pigment {
  average
  pigment_map {
    [1 
    image_map {
      jpeg "PIA15687.jpg"
      interpolate 2
      once
    }
    ][3 color rgbf <1,1,1,1>]
    
  }
  translate <-0.5,-0.5,-0.5>
  scale <1,-1,1>
  rotate y*90
  rotate -x*90
  scale <1,-1,1>
#declare MtSharpLat= -5.342778;
#declare MtSharpLon=137.827777;
  rotate -y*MtSharpLat
  rotate z*MtSharpLon
  scale 0.06
}    

union {
//  cylinder {0,x*2,0.05 pigment {color rgb x}}
  cylinder {0,y*2,0.05 pigment {color rgb y}}
  cylinder {0,z*2,0.05 pigment {color rgb z}}
  cylinder {0,-x*2,0.05 pigment {color rgb <1,1,1>-x}}
  cylinder {0,-y*2,0.05 pigment {color rgb <1,1,1>-y}}
  cylinder {0,-z*2,0.05 pigment {color rgb <1,1,1>-z}}
  sphere {
    0,1
    texture {pigment {MarsPigment}}
    texture {pigment {GalePigment}}
    texture {pigment {MtSharpPigment}}
  }
  rotate -z*MtSharpLon
  rotate y*MtSharpLat
}

camera {
  right -x*image_width/image_height
  sky z
  location <5,0,0>
  look_at <0,0,0>
  angle 1
}               

light_source {
  <20,0,20>*100000
  color rgb 1.5
}


