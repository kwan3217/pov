//39.9995,537.1304,155.0967,651.9893,297.0747,651.9893,"curveto",
//439.0469,651.9893,554.1426,537.1304,554.1426,395.4404,"curveto",
//554.1426,253.751,439.0469,138.8926,297.0747,138.8926,"curveto",
//155.0967,138.8926,39.9995,253.751,39.9995,395.4404,"curveto",

#declare R=0.25;

#macro bezierseg(x0,ax,bx,cx,y0,ay,by,cy,t1,t2)
  #local P1=<ax*pow(t1,3)+bx*pow(t1,2)+cx*t1+x0,ay*pow(t1,3)+by*pow(t1,2)+cy*t1+y0,0>;
  #local P2=<ax*pow(t2,3)+bx*pow(t2,2)+cx*t2+x0,ay*pow(t2,3)+by*pow(t2,2)+cy*t2+y0,0>;
  #local Pmidflat=(P1+P2)/2;
  #local tmid=(t2+t1)/2;
  #local Pmidcurve=<ax*pow(tmid,3)+bx*pow(tmid,2)+cx*tmid+x0,ay*pow(tmid,3)+by*pow(tmid,2)+cy*tmid+y0,0>;
  #if(vlength(Pmidflat-Pmidcurve)>(R/10))
    bezierseg(x0,ax,bx,cx,y0,ay,by,cy,t1,tmid)
    bezierseg(x0,ax,bx,cx,y0,ay,by,cy,tmid,t2)
  #else
    cylinder {
      P1,P2,R
    }
    sphere {
      P2,R
    }
  #end
#end

#macro bezier(x0,y0,x1,y1,x2,y2,x3,y3)
  #local cx=3*(x1-x0);
  #local bx=3*(x2-x1)-cx;
  #local ax=x3-x0-cx-bx;
  #local cy=3*(y1-y0);
  #local by=3*(y2-y1)-cy;
  #local ay=y3-y0-cy-by;
  bezierseg(x0,ax,bx,cx,y0,ay,by,cy,0,1)
#end
  
  

#fopen inf "Test2.txt" read  

#declare Engraving= 
union {
  union {
#while(defined(inf))
  #read(inf,A1,A2,A3,A4,A5,A6,A7)
  #declare Draw=true;
  #switch(asc(A7))
    #case(asc("m")) //moveto
      }
      union {
      #declare CurrentX=A1;
      #declare CurrentY=A2;
      #break
    #case(asc("l")) //lineto 
      #if(vlength(<CurrentX,CurrentY,0>-<A1,A2,0>)>0)
      cylinder {
        <CurrentX,CurrentY,0>,<A1,A2,0>,R
      }
      #end
      #declare CurrentX=A1;
      #declare CurrentY=A2;
      #break
    #case(asc("c")) //curveto
      bezier(CurrentX,CurrentY,A1,A2,A3,A4,A5,A6)
      #declare CurrentX=A5;
      #declare CurrentY=A6;
      #break         
    #case(asc("%")) //Comment
      #declare Draw=false;    
      #debug concat(A7,"\n")
      #break
  #end      
  #if(Draw)
    sphere {
      <CurrentX,CurrentY,0>,R
    }
  #end
#end      
}       
}

#declare DiskCenter=<(39.9995+554.1426)/2,(537.1304+253.751)/2,0>;
#declare DiskRadius=(554.1426-39.9995)/2;

#declare Disk=cylinder {
  DiskCenter,DiskCenter+z*10,DiskRadius
}

union {
  object{Disk}
  object{Engraving}      
  bounded_by {Disk}
  pigment {color rgb <1,1,0>}
  translate -DiskCenter
}

camera {
  location <50,50,-1000>
  look_at <50,50,0>   
  angle 30
}

light_source {
  <20,20,-20>*10000
  color rgb 2
}                

background {rgb <0,0.5,1>}
                   
                   
                   


