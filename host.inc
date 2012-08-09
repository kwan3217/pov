#declare syscmd="echo \\#declare Host=\\\"`hostname`\\\""
#system syscmd
#declare Host=concat(strupr(substr(Host,1,1)),substr(Host,2,strlen(Host)-1))

#if( strcmp(Host,"Omoikane")=0)
  #declare Host=concat(Host,str(pid,0,0))
#end
