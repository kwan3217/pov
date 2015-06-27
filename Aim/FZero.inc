#macro FnToZero(x)
  (x)
#end

#macro FZero(a,b)
  #local A=a;
  #local B=b;
  #local FA=FnToZero(A);
  #local FB=FnToZero(B);
  #while(abs((FA+FB)/2))
    #local C=(A+B)/2;
    #local FC=FnToZero(C);
    #if(FC*FA>0)
      #local B=C;
      #local FB=FC;
    #else
      #local A=C;
      #local FA=FC;
    #end
  #end
end
