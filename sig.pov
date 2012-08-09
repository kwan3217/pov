#macro G(D,E,F)
  #local I=array[3]{D,E,F}
  #local B=0;
  triangle{
    #while(B<3)
      #while(I[B])
        A[mod(I[B],10)]+
        #local I[B]=div(I[B],10);
      #end
      <-5,-2,9>
      #local B=B+1;
    #end
  }
#end

#local A=array[7]{x,x*2,x*4,y,y*2,y*4,z}

light_source{
  -x*6-z*9,1
}

mesh{
  G(105,10,146)
  G(105,246,10)
  G(105,56,146)
  G(105,1256,246)
  G(1256,126,220)
  G(22156,2216,201)
  pigment{rgb 1}
}//TM

