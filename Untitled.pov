#declare _=function(a,b,x){((a^2)+(b^2))^.5-x}#default {pigment{color rgb 1}}
union{plane{y,-3}plane{-x,-3}finish{reflection 1 ambient 0}}isosurface{ //ABX
function{_(x-2,y,1)|_((x+y)*.7,z,.1)|_((x+y+2)*.7,z,.1)|_(x/2+y*.8+1.5,z,.1)}
contained_by{box{<0,-3,-.1>,<3,0,.1>}}translate z*15finish{ambient 1}}//POV35