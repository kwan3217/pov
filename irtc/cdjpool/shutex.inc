 //Space Shuttle Textures
//#debug "Parsing Space Shuttle Textures (shutex.inc)\n"
 
                         
//Layer 1 - Wing tops                        
#declare Layer1Tex = texture {
	pigment { 
    image_map {
      gif "layer1.gif" // the file to read (iff/gif/tga/png/sys)
      map_type 0 // 0=planar, 1=spherical, 2=cylindrical, 5=torus
      interpolate 2 // 0=none, 1=linear, 2=bilinear, 4=normalized distance
    }
    translate <-1/2,-1/2,0>
    rotate y*180
    scale <4.402,4.510,1>
    translate <0,-1.606,0>
  }
}

//Layer 2 - Cargo bay radiators
#declare Layer2Tex = texture {
	pigment { rgb < 0.8,0.8,0.9 > }
	finish { phong 0.9 reflection 0.5}
}

//Layer 3 - Fuselage and tail
#declare Layer3Tex = texture {  
//Bounding Box <X,-4.066,-0.925>-<X,1.987,1.347>
//Center <X,-1.040,0.211>
//Extent <X,6.053,2.272>
	pigment { 
    image_map {
      gif "layer3.gif" // the file to read (iff/gif/tga/png/sys)
      map_type 0 // 0=planar, 1=spherical, 2=cylindrical, 5=torus
      interpolate 2 // 0=none, 1=linear, 2=bilinear, 4=normalized distance
    }                      
    translate <-1/2,-1/2,0>
    rotate -y*90
    scale <1,6.053,2.272>
    translate <0,-1.040,0.211>
  }
}

//Layer 4 - Engines
#declare Layer4Tex = texture {
	pigment { rgb < 0.3, 0.3, 0.3 > }
	finish {phong 1}
}

//Layer 5 - Cargo bay
#declare Layer5Tex = texture {
	pigment { rgb < 1, 1, 1 > }
	normal { wrinkles 0.2 }
}

//Layer 6 - Oms pods
#declare Layer6Tex = texture {
	pigment { rgb < 1, 1, 1 > }
}

//Layer 7 - Heat shield
#declare Layer7Tex = texture {
	pigment { rgb < 0.1,0.1,0.1 > }
	finish { phong 0.9 }
}

//Layer 8 - Cockpit
#declare Layer8Tex = texture {
	pigment { 
    image_map {
      gif "layer8.gif" // the file to read (iff/gif/tga/png/sys)
      map_type 0 // 0=planar, 1=spherical, 2=cylindrical, 5=torus
      interpolate 2 // 0=none, 1=linear, 2=bilinear, 4=normalized distance
    }
    translate <-1/2,-1/2,0>
    rotate y*180
    scale <0.904,1.222,1>
    translate <0,1.217,0>
  }
}

//#debug "Done with Shuttle Textures (shutex.inc)\n"
