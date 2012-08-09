#include "PovSolar/Math.inc"

#local N=16;
#local W="/h>m8X=X7KJXFXWhjhKMa$Q$AD390$&<";
#macro K()
  #declare A=A+1;
	#local result=  asc(substr(W,A,1))*2/N-4;
	(result/2)
#end

#local A=0;

camera {
  orthographic
  up y*4
  right x*4
  direction z
  location y*3 
  look_at 0.000001
  sky z 
}

plane {
  y,0
	pigment {checker}
  finish {ambient 1 diffuse 0}
}

difference {
  cylinder{-y/8,y/8,2}
  prism{
    -N,N,N
    #while(A<N*2)
			#if(A=0)
			  #debug "M "
			#else
			  #debug "L "
			#end
		  #local A1=K()-34/N;
		  #local A2=K()-44/N;
			#debug concat(str((A1+2)*250,0,6)," ",str(1000-(A2+2)*250,0,6),"\n")
      <A1,A2>
    #end
	  #debug "z\n"
  }
  pigment{color x+y/2}
  finish {ambient 1 diffuse 0}
} //http://ryooki.digiquill.com/ Kwan Systems! 2001

