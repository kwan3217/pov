//Copy-pasta of Kwan Logo, scaled for use in cdjmath.pov. This appears to be artifact-compatible with what I did 18+ years ago.
#local KwanN=16;
#local KwanW="/h>m8X=X7KJXFXWhjhKMa$Q$AD390$&<";
#local KwanA=0;
#macro KwanK()
  #declare KwanA=KwanA+1;
  #local result=  asc(substr(KwanW,KwanA,1))*2/KwanN-4;
  (result/2)
#end
#declare KwanCircle=difference {
  cylinder{-y/8,y/8,2}
  prism{
    -KwanN,KwanN,KwanN
    #while(KwanA<KwanN*2)
      #local A1=KwanK()-34/KwanN;
      #local A2=KwanK()-44/KwanN;
      #debug concat(str((A1+2)*250,0,6)," ",str(1000-(A2+2)*250,0,6),"\n")
      <A1,A2>
    #end
  }
  scale y*20
  rotate -x*90
  scale 0.5
} 


