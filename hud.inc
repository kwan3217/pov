//S - string to print
//V - vector to place it at in HUD space
//C - Color to paint it
//Halign - 0: left align
//         1: right align
//       0.5: center align
//Valign - 0: bottom
//         1: top
//       0.5: center
//        -1: baseline

#macro textHud(S,V,C,Halign,Valign)
  #local Text=text {
    ttf "lucon.ttf"
    S 0 0

    #if(Valign=0)
      v_align_bottom
    #else 
      #if(Valign>=1)
        v_align_top
      #else 
        #if(Valign>0)
          v_align_center
        #else
          //v_align_baseline (for Valign < 0)
        #end 
      #end 
    #end 
  }

  #local th=max_extent(Text).x*Halign;

  object {
    Text
    translate -y*th
    scale <1,1,1>*0.02
//    rotate y*180
    rotate z*90
    translate <-V.x/9,V.y/9,0>+<0,0,0.36>
    pigment {color rgbt C}
    finish {ambient 1 diffuse 0}
  }
#end

#macro textHudNumber(N,U,V,C,Valign) 
  #if(abs(N)>1000) 
    textHud(str(N/1000,7,3),V,C,1,Valign)
    textHud(concat("k",U),V+<1,0>,C,0,Valign)
  #else
    textHud(str(N,7,3),V,C,1,Valign)
    textHud(concat(" ",U),V+<1,0>,C,0,Valign)
  #end

#end

