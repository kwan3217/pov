#macro roundprism(h1,h2,p,R)
   #local ctr=0;
   #local n=dimension_size(p,1);
   #local ap=array[n]
   #local ams=array[n]
   #local ang=array[n]
   #while (ctr<n)
      #local ps=p[mod(ctr-1+n,n)];
      #local pm=p[ctr];
      #local pe=p[mod(ctr+1,n)];
      #local a1=mod(atan2(pm.x-ps.x,pm.y-ps.y)*180/pi+360,360);
      #local a2=mod(atan2(pe.x-pm.x,pe.y-pm.y)*180/pi+360,360);
      #local am=mod(a2-a1+360,360);
      #if (am<180) #local am=180-am; #end
      #local ab=(mod(a1+180,360)+a2)/2;
      #if (floor((max(mod(a1+180,360),a2)-min(mod(a1+180,360),a2))/180) != floor(am/180))
         #local ab=mod(ab+180,360); #end
      #local bv=<sin(ab*pi/180),cos(ab*pi/180)>;
      #local sam=am; #if (sam>180) #local sam=sam-180; #end
      #local l=1/sin((sam/2)*pi/180)*R;
      #local ap[ctr]=pm+bv*l;
      #local ams[ctr]=am;
      #local ang[ctr]=a1;
      #local ctr=ctr+1;
   #end
   #local ctr=0;
   prism { h1,h2,n+1            
   #while (ctr<n)
      ap[ctr]
      #local ctr=ctr+1;
   #end
   ap[0] }
   #local ctr=0;
   #while (ctr<n)
      sphere { <ap[ctr].x,h1+R,ap[ctr].y>,R }
      sphere { <ap[ctr].x,h2-R,ap[ctr].y>,R }
      cylinder { <ap[ctr].x,h1+R,ap[ctr].y>,<ap[ctr].x,h2-R,ap[ctr].y>,R }
      cylinder { <ap[ctr].x,h1+R,ap[ctr].y>,<ap[mod(ctr+1,n)].x,h1+R,ap[mod(ctr+1,n)].y>,R }
      cylinder { <ap[ctr].x,h2-R,ap[ctr].y>,<ap[mod(ctr+1,n)].x,h2-R,ap[mod(ctr+1,n)].y>,R }
      box { <-R,h1+R,0>,<0,h2-R,sqrt(pow(ap[mod(ctr+1,n)].x-ap[ctr].x,2)
                                    +pow(ap[mod(ctr+1,n)].y-ap[ctr].y,2))>
            rotate atan2(ap[mod(ctr+1,n)].x-ap[ctr].x,ap[mod(ctr+1,n)].y-ap[ctr].y)*180/pi*y
            translate <ap[ctr].x,0,ap[ctr].y> }
      #if (ams[ctr]>180)
         difference {
            intersection {
               cylinder { <p[ctr].x,h1-R,p[ctr].y>*2-<ap[ctr].x,h1-R,ap[ctr].y>,
                          <p[ctr].x,h2+R,p[ctr].y>*2-<ap[ctr].x,h2+R,ap[ctr].y>,R inverse }
               prism { h1,h2,4 ap[ctr],ap[mod(ctr-1+n,n)],ap[mod(ctr+1,n)],ap[ctr] }
               plane { -z,0 rotate ang[ctr]*y translate <p[ctr].x,0,p[ctr].y>*2-<ap[ctr].x,0,ap[ctr].y> }
               plane { -z,0 rotate (180+ang[mod(ctr+1,n)])*y translate <p[ctr].x,0,p[ctr].y>*2-<ap[ctr].x,0,ap[ctr].y> }
            }
            intersection {
               torus { R*2,R translate <p[ctr].x,h1+R,p[ctr].y>*2-<ap[ctr].x,h1+R,ap[ctr].y> inverse }
               cylinder { <p[ctr].x,h1+R,p[ctr].y>*2-<ap[ctr].x,h1+R,ap[ctr].y>,
                          <p[ctr].x,h1-R*2,p[ctr].y>*2-<ap[ctr].x,h1-R*2,ap[ctr].y>,R*2 }
            }
            intersection {
               torus { R*2,R translate <p[ctr].x,h2-R,p[ctr].y>*2-<ap[ctr].x,h2-R,ap[ctr].y> inverse }
               cylinder { <p[ctr].x,h2-R,p[ctr].y>*2-<ap[ctr].x,h2-R,ap[ctr].y>,
                          <p[ctr].x,h2+R*2,p[ctr].y>*2-<ap[ctr].x,h2+R*2,ap[ctr].y>,R*2 }
            }
         }
      #end
      #local ctr=ctr+1;
   #end
#end

