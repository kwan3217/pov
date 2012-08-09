#declare Test=array[10];

#declare Test[2]=1;


#if(defined(Test[1]))
  #debug "Stuff1\n"
#end

#if(defined(Test[2]))
  #debug "Stuff2\n"
#end
