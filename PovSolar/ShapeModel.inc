//ShapeModel.inc
//Irregular Shape Modeller for asteroids and small moons.
//Copyright © 2000 Kwan Systems
//You may use and modify this as you see fit for any non-commercial purpose
//otherwise contact me at chrisj@digiquill.com
//Chris Jeppesen - 3 Apr 2000
#include "KwanMath.inc"
/*Usage*************************\
#macro ShapeModel(Fn,Fn2,Smooth,Scale)
Parameters:
  Fn: File with shape model. Consists of a comma seperated list of numbers.
      First two are number of longitude and latitude samples, followed by lon,lat,rad triplets
      Triplets can be in any order. Lon goes from 0 to 360W. Lat goes from -90 to 90.
  Fn2: File to output shape model to.
  Smooth: Set to 1 to generate smooth triangles, 0 otherwise.
  Scale:Scale Factor of model. File radii are multiplied by this number to produce 
	      radii in km. Example: Enter 1 if file radii are already km, 0.001 for meters, etc
Produces:
  Include file with mesh of (smooth) triangles, longitude 0 at +X, longitude increasing towards the west.
\*******************************/

#macro strv(V,A,B)
  concat("<",str(V.x,A,B),",",str(V.y,A,B),",",str(V.z,A,B),">")
#end    

#macro ShapeModel(Fn,Fn2,Smooth,Scale)
  #warning concat("Parsing raw shape model ",Fn,"\n\n")
  #declare Lat=0;  
  #declare Lon=0;
  #declare Rad=0;
  #fopen Inf Fn read
  #fopen Ouf Fn2 write
  #declare I=0;
  #declare NumLon=0;
  #declare NumLat=0;
  #read(Inf,NumLon,NumLat)
  #declare GridSizeLon=360/(NumLon-1);
  #declare GridSizeLat=180/(NumLat-1);
  #declare ShapeGrid=array[NumLon][NumLat]
  //Read point file
  #while (I<NumLon)
    #declare J=0;
		PrintNumber("I: ",I)
    #while(J<NumLat)
      #read(Inf,Lon,Lat,Rad)  
      #local LonCell=Lon/GridSizeLon;
      #local LatCell=(Lat+90)/GridSizeLat;
      #declare ShapeGrid[LonCell][LatCell]=<cos(radians(Lat))*cos(radians(Lon)),
                                sin(radians(Lat)),
                                cos(radians(Lat))*sin(radians(Lon))>*Rad*Scale;
      #declare J=J+1;
    #end
    #declare I=I+1;
  #end             
  #fclose Inf
  
  #if(Smooth) 
  //Calculate body of normal grid               
  #warning "Calculating normals\n\n"
  #declare NormalGrid=array[NumLon][NumLat]
  #declare SouthNormal=<0,0,0>;
  #declare NorthNormal=<0,0,0>;
  #declare I=1;
    #while (I<NumLon)
      #declare J=1;
      #while(J<NumLat-1)                          
        #declare NormalGrid[I][J]= vnormalize(
           vcross(ShapeGrid[I][J]-ShapeGrid[I][J+1],ShapeGrid[I][J]-ShapeGrid[mod(I+1,NumLon)][J])+
           vcross(ShapeGrid[I][J]-ShapeGrid[mod(I+1,NumLon)][J],ShapeGrid[I][J]-ShapeGrid[I][J-1])+
           vcross(ShapeGrid[I][J]-ShapeGrid[mod(I-1,NumLon)][J],ShapeGrid[I][J]-ShapeGrid[I][J+1])+
           vcross(ShapeGrid[I][J]-ShapeGrid[I][J-1],ShapeGrid[I][J]-ShapeGrid[mod(I-1,NumLon)][J])
           );
        #declare J=J+1;
      #end
      #declare I=I+1;
    #end
    
    //Copy prime meridian values
    #declare J=1;
    #while(J<NumLat-1)  
      #declare NormalGrid[0][J]=NormalGrid[NumLon-1][J];
      #declare J=J+1;
    #end
  
    //Average all polar normals
    #declare I=0;
    #while(I<NumLon)
      #declare SouthNormal=(SouthNormal*I+vcross(ShapeGrid[0][0]-ShapeGrid[I][1],ShapeGrid[0][0]-ShapeGrid[mod(I+1,NumLon)][1]))/(I+1);
      #declare NorthNormal=(NorthNormal*I+vcross(ShapeGrid[0][NumLat-1]-ShapeGrid[I][NumLat-2],ShapeGrid[0][NumLat-1]-ShapeGrid[mod(I+1,NumLon)][NumLat-2]))/(I+1);
      #declare I=I+1;
    #end
    #declare SouthNormal=vnormalize(SouthNormal);
    #declare NorthNormal=vnormalize(NorthNormal);
  
    //Write polar normals
    #declare I=0;
    #while(I<NumLon)
      #declare NormalGrid[I][0]=SouthNormal;
      #declare NormalGrid[I][NumLat-1]=SouthNormal;
      #declare I=I+1;
    #end
  
    //Finally! the smooth mesh.
    #warning "Writing the smooth mesh\n\n"
    #write(Ouf,"mesh {\n")
      #declare I=0;
      #while(I<NumLon-1)
        #declare J=0;
        #while(J<NumLat-1) 
          #write(Ouf,concat("smooth_triangle {",strv(ShapeGrid[I  ][J  ],0,5),",",strv(NormalGrid[I  ][J  ],0,5),",",
                                                strv(ShapeGrid[I+1][J  ],0,5),",",strv(NormalGrid[I+1][J  ],0,5),",",
                                                strv(ShapeGrid[I  ][J+1],0,5),",",strv(NormalGrid[I  ][J+1],0,5),"}\n"))
          #write(Ouf,concat("smooth_triangle {",strv(ShapeGrid[I+1][J+1],0,5),",",strv(NormalGrid[I+1][J+1],0,5),",",
                                                strv(ShapeGrid[I+1][J  ],0,5),",",strv(NormalGrid[I+1][J  ],0,5),",",
                                                strv(ShapeGrid[I  ][J+1],0,5),",",strv(NormalGrid[I  ][J+1],0,5),"}\n"))
          #declare J=J+1;
        #end
        #declare I=I+1;
      #end
    #write(Ouf,"}\n")
  #else
    //No smoothing
    #warning "Writing the unsmoothed mesh\n\n"
    #write(Ouf,"mesh {\n")
      #declare I=0;
      #while(I<NumLon-1)
        #declare J=0;
        #while(J<NumLat-1) 
          #write(Ouf,"triangle {",strv(ShapeGrid[I  ][J  ],0,5),",",strv(ShapeGrid[I+1][J  ],0,5),",",strv(ShapeGrid[I  ][J+1],0,5),"}\n")
          #write(Ouf,"triangle {",strv(ShapeGrid[I+1][J+1],0,5),",",strv(ShapeGrid[I+1][J  ],0,5),",",strv(ShapeGrid[I  ][J+1],0,5),"}\n")
          #declare J=J+1;
        #end
        #declare I=I+1;
      #end
    #write(Ouf,"}\n")
  #end
  #fclose Ouf
  #warning "Done writing model.\n\n"
#end



