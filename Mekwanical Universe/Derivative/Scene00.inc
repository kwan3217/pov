#version unofficial Megapov 1.22;

#local ShotTime=array[2] {4,1}

CalcShotTime(ShotTime)

#switch(Shot)
  #case(0)
    text {
      ttf "verdana.ttf" 
      "Derivatives" 0 0
      h_align_center
      rotate -y*90
      rotate -z*90
      translate <0,-0.001,1>
      Fade(<0.1,0.1,0.1,0>,ASDR(0,0.25,0.75,1,0,1,ShotClockN))
    }
    text {
      ttf "verdana.ttf" 
      concat(chr(169)," 2010 Kwan Heavy Industries") 0 0
      h_align_center
      scale 0.5
      rotate -y*90
      rotate -z*90
      translate <0,-0.001,-1>
      Fade(<0.1,0.1,0.1,0>,ASDR(0,0.25,0.75,1,0,1,ShotClockN))
    }
    #break
#end

plane {
  -y,0
  pigment {checker color rgb 1 color rgb 0.75}
}


camera {
  right x*16/9
  sky z
  location <0,-9,0.5>
  look_at <0,0,0.5>
}

light_source {
  <20,-20,20>*1000
  color rgb 1
}


