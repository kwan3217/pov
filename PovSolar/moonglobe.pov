sphere {
  0,1.2
  pigment {
    // texture pigment {} attribute
// create a texture that lays an image's colors onto a surface
// image maps into X-Y plane from <0,0,0> to <1,1,0>
/*
image_map
{
  png "moonmap.png" // the file to read (iff/gif/tga/png/sys)
  map_type 1 // 0=planar, 1=spherical, 2=cylindrical, 5=torus
  interpolate 2 // 0=none, 1=linear, 2=bilinear, 4=normalized distance
  // [filter N V] // N=all or color index # (0...N), V= value (0.0...1.0)
  // [transmit N V] // N=all or color index # (0...N), V= value (0.0...1.0)
  // [use_color | use_index]
  // [once]
} // image_map
*/
  color rgb 0.5
  }
  normal {
  // texture normal {} attribute
// create a texture that has a bumpiness corresponding to color index
// image maps into X-Y plane from <0,0,0> to <1,1,0>
bump_map
{ // uses image color or index as bumpiness
  png "moonbump.png" // the file to read (iff/gif/tga/png/sys)
  map_type 1 // 0=planar, 1=spherical, 2=cylindrical, 5=torus
  interpolate 2 // 0=none, 1=linear, 2=bilinear, 4=normalized distance
  // [use_color | use_index]
  // [once]
  bump_size 8 // 0...3  
} // bump_map
  rotate y*(3/1440)
  rotate -y*180

  }     
  rotate y*clock*360
  translate -x*1.5
}        

sphere {
  0,1.2
  pigment {
    // texture pigment {} attribute
// create a texture that lays an image's colors onto a surface
// image maps into X-Y plane from <0,0,0> to <1,1,0>
image_map
{
  png "moonmap.png" // the file to read (iff/gif/tga/png/sys)
  map_type 1 // 0=planar, 1=spherical, 2=cylindrical, 5=torus
  interpolate 2 // 0=none, 1=linear, 2=bilinear, 4=normalized distance
  // [filter N V] // N=all or color index # (0...N), V= value (0.0...1.0)
  // [transmit N V] // N=all or color index # (0...N), V= value (0.0...1.0)
  // [use_color | use_index]
  // [once]
} // image_map    
  rotate y*180
  }       
  normal {
  // texture normal {} attribute
// create a texture that has a bumpiness corresponding to color index
// image maps into X-Y plane from <0,0,0> to <1,1,0>
bump_map
{ // uses image color or index as bumpiness
  png "moonbump.png" // the file to read (iff/gif/tga/png/sys)
  map_type 1 // 0=planar, 1=spherical, 2=cylindrical, 5=torus
  interpolate 2 // 0=none, 1=linear, 2=bilinear, 4=normalized distance
  // [use_color | use_index]
  // [once]
  bump_size 8 // 0...3
} // bump_map
  rotate y*(3/1440)
  rotate -y*180
  }     
  rotate y*clock*360
  translate x*1.5
}        
camera {
  location <0,0,-5>
  look_at <0,0,0>
//  angle 5 
  orthographic
}

light_source {
  <20,0,-20>*100000
  color rgb<1,1,1>*1.5
}