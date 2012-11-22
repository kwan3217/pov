#local N=16;#local W="/h>m8X=X7KJXFXWhjhKMa$Q$AD390$&<";#macro K()#declare A=A+1
;((asc(substr(W,A,1))*2/N-4)/2)#end#local A=0;camera{orthographic up y*4 right x
*4direction z location y*3look_at 0sky z}plane{y,0pigment{checker}finish{ambient
1diffuse 0}}difference {cylinder{-y/8,y/8,2}prism{-N,N,N#while(A<N*2)<K(),K()>-<
34,44>/N#end}pigment{color x+y/2}finish {ambient 1 diffuse 0}} //http://ryooki.digiquill.com/ Kwan Systems! 2001

