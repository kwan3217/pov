#macro textHud(S,V,C,Halign,Valign)
  #local Text=text {
    ttf "lucon.ttf"
    S 0 0
  }
  #if(Halign<=0)
//      h_align_left
// Do nothing, natural state
    #local th=0;
  #else
    #if(Halign>=1)
//      h_align_right
      #local th=max_extent(Text).x;
    #else
//        h_align_center
      #local th=max_extent(Text).x/2;
    #end
  #end

  #if(Valign=0)
    v_align_bottom
  #else
    #if(Valign>=1)
      v_align_top
    #else
      #if(Valign>0)
        v_align_center
      #else
        //v_align_baseline (for Valign<0
      #end
    #end
  #end 

  object {
    Text
    translate -x*th
    scale <1,-1,1>*0.05
    rotate z*180
    translate <-V.x/9,V.y/9,0>+<0,0,0.36>
    pigment {color rgbt C}
    finish {ambient 1 diffuse 0}
  }
#end

#macro textHudNumber(N,U,V,C,Valign) 
  #if(abs(N)>1000) 
    textHud(str(N/1000,7,3),V,C,1,Valign)
    textHud(concat("k",U),V,C,0,Valign)
  #else
    textHud(str(N,7,3),V,C,1,Valign)
    textHud(concat(" ",U),V,C,0,Valign)
  #end

#end

