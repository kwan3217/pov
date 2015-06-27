//Scene Starter

light_source {
  <20,20,-20>
  color rgb<1,1,1>*1.5
}

camera {
  location <0,2,-5>
  look_at<0,0,0>
}       

#declare OuterRad=3;
#declare InnerRad=clock*3; 
#declare Width=OuterRad-InnerRad;

disc {
  0,y,OuterRad,InnerRad
  pigment {
    wood  
    #declare Wavelength=Width*2;
    frequency 1/Wavelength 
    phase -(InnerRad/Wavelength)+0.5
    color_map {
      [0 color rgb <0,0,1>]    //outside first - Should be blue
      [0.05 color rgb <0,0,1>]
      [0.05 color rgb <0,1,0>]
      [0.95 color rgb <0,1,0>]
      [0.95 color rgb <1,0,0>]
      [1 color rgb <1,0,0>]    //Inside should be red
    }
    rotate x*90
  }
}