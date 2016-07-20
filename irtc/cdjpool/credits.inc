//Credits.inc  

#include "credits.txt"
                  
#declare YPos=-7+CreditClock;
#declare I=0;
                     
union {                     
#while(I<dimension_size(Credits,1))  
  #declare Size=val(Credits[I][0]);
  #declare Font=Credits[I][1] 
  #declare Text=Credits[I][2]      
  /*
  #warning concat("Size: ",str(Size,0,0),"\n")
  #warning concat("Font: ",Font,"\n")       
  #warning concat("Text: ",Text,"\n")
  */
  #if(strlen(Text)!=0)
    text {
      ttf Font,Text,1/100,0
      scale Size/800*CreditScale
      translate <-.075,YPos/100,0.12>*CreditScale
      pigment {color <1,1,1>} 
      finish {diffuse 0 specular 0 ambient 1} 
      no_shadow
    }
  #end
  #declare I=I+1;
  #declare YPos=YPos-Size/9;
#end   

/*
plane {
  z,0
  pigment {checker color rgbt<1,0,0,0.8>,rgbt<0,0,1,0.8>}
  translate <-7.5,YPos,12>
} 
*/
}



#warning concat("Total Credits Length: ",str(-(YPos-CreditClock+6),0,4),"\n")

