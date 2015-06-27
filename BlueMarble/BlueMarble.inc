/*******************************************************************************\
BlueMarble.inc -- Use the Blue Marble dataset to create a model of the earth

#macro CalcEarthMod(LCamLoc,Look,Angle)
Calculate which tiles are needed to properly portray the Earth given these
camera parameters. Output is an object variable called HardSurface (This may 
be extended someday to the cloud deck, ice deck, etc) which is a perfect spheroid
with the correct texture.

#macro UseEarthMod()
Put the calculated earth model into the scene, unrotated and at the origin
with the prime meridian towards +x, the north pole towards +y, and 90degE towards
+z.

#macro EarthMod(LCamLoc,Look,Angle) 
Calls CalcEarthMod and UseEarthMod sequentially

Hidden parameters: Change these before calling the CalcEarthMod macro.
AEarth, BEarth: Size of the spheroid used. Default values are for WGS-84 
ellipsoid in km.
UseShell[n], n=0-5: Consider using shell n. #undef these to not consider the 
given shell.

\*******************************************************************************/

#version unofficial MegaPov 1.11;

#ifndef(AEarth)
  #declare AEarth=6378.137;
#end
#ifndef(BEarth)
	#declare BEarth=6356.752;
#end
#declare UseShell0=0;
#declare UseShell1=0;
#declare UseShell2=0;
#declare UseShell3=0;
#declare UseShell4=0;
#declare UseShell5=0;

#include "KwanMath.inc"

#ifndef(UseTest)
  #declare UseTest=0;
#end

#macro NumLatRows(Shell)
  5*pow(2,Shell-1)
#end

#macro CenterLat(Shell,LatRow)
  #local Limit=NumLatRows(Shell);
  #local TileSize=180/Limit;
  (90-(LatRow+0.5)*TileSize)
#end

#macro CenterLon(Shell,LonRow)
  #local Limit=2*NumLatRows(Shell);
  #local TileSize=360/Limit;
  ((LonRow+0.5)*TileSize)-180
#end

#macro Center(Shell,LatRow,LonRow,Re)
  (LLtoXYZ(CenterLat(Shell,LatRow),CenterLon(Shell,LonRow),Re))
#end

#macro NearFar(Shell,LatRow,LonRow,Loc,Near,Far,Re)
  #local Corner=array[4];
  #local Corner[0]=Center(Shell,LatRow-0.5,LonRow-0.5,Re);
  #local Corner[1]=Center(Shell,LatRow-0.5,LonRow+0.5,Re);
  #local Corner[2]=Center(Shell,LatRow+0.5,LonRow-0.5,Re);
  #local Corner[3]=Center(Shell,LatRow+0.5,LonRow+0.5,Re);
  #declare Near=Corner[0];
  #local NearDist=vlength(Corner[0]-Loc);
  #declare Far=Near;
  #local FarDist=NearDist;
  #local I=1;
  #while(I<4)
    #local Dist=vlength(Corner[I]-Loc);
    #if(Dist<NearDist)
      #declare Near=Corner[I];
      #local NearDist=vlength(Corner[I]-Loc);
    #end
    #if(Dist>FarDist)
      #declare Far=Corner[I];
      #local FarDist=vlength(Corner[I]-Loc);
    #end
    #local I=I+1;
  #end
#end

#macro InHorizon(Shell,LatRow,LonRow,Loc,Re)
  #local verbose=1;
//  #if(verbose)PrintNumber("LatRow: ",LatRow) #end
//  #if(verbose)  PrintNumber("LonRow: ",LonRow) #end
  #local NearXYZ=<0,0,0>;
  #local FarXYZ=<0,0,0>;
  NearFar(Shell,LatRow,LonRow,Loc,NearXYZ,FarXYZ,Re)
//  #if(verbose)  PrintVector("Loc:  ",Loc) #end
//  #if(verbose)  PrintVector("Near: ",NearXYZ) #end
  #local Vec1=vnormalize(-NearXYZ);
  #local Vec2=vnormalize(Loc-NearXYZ);
//  #if(verbose)  PrintVector("Vec1: ",Vec1) #end
//  #if(verbose)  PrintVector("Vec2: ",Vec2) #end
//  #if(verbose)  PrintNumber("Dot:  ",vdot(Vec1,Vec2)) #end
  (vdot(Vec1,Vec2)<0)
#end

#macro InFov(Shell,LatRow,LonRow,Loc,Look,Angle,Re)
  #local Limit=cos(radians(Angle)*sqrt(2));
  #local NearXYZ=<0,0,0>;
  #local FarXYZ=<0,0,0>;
  NearFar(Shell,LatRow,LonRow,Loc,NearXYZ,FarXYZ,Re)
  #local Vec1=vnormalize(Loc-NearXYZ);
  #local Vec2=vnormalize(Loc-Look);
  (vdot(Vec1,Vec2)>Limit)
#end

#macro InTile(Shell,LatRow,LonRow,Loc,Re)
  #local TLat=CenterLat(Shell,LatRow);
  #local TLon=CenterLat(Shell,LonRow);
  #local LLat=XYZtoLat(Loc);
  #local LLon=XYZtoLon(Loc);
  #local Limit=NumLatRows(Shell);
  #local TileSize=180/Limit;
  ((abs(TLat-LLat)<(TileSize*0.5001))*(abs(TLon-LLon)<(TileSize*0.5001)))
#end

#macro ResOK(Shell,LatRow,LonRow,Loc,Angle,Pix,Re)
  #local Ratio=0.5;
  #local NearXYZ=<0,0,0>;
  #local FarXYZ=<0,0,0>;
  NearFar(Shell,LatRow,LonRow,Loc,NearXYZ,FarXYZ,Re)
  #local PixSubtend=tan(radians(Angle))*2/Pix;
  #local Limit=5*pow(2,Shell-1);
  #local MapPixSize=Re*pi/(Limit*270);
  #local NearDist=vlength(Loc-NearXYZ);
  #local MapSubtend=MapPixSize/NearDist;
  ((MapSubtend/PixSubtend)>Ratio)
#end

#macro TileOK(Shell,LatRow,LonRow,Loc,Look,Angle,Pix,Re)
//  #local Result=InTile(Shell,LatRow,LonRow,Loc,Re);
//  #if(!Result)
    #local Result=InHorizon(Shell,LatRow,LonRow,Loc,Re);
//    #if(Result)
//      #local Result=InFov(Shell,LatRow,LonRow,Loc,Look,Angle,Re);
//      #if(Result)
//        #local Result=ResOK(Shell,LatRow,LonRow,Loc,Angle,Pix,Re);
//      #end
//    #end
//  #end
  (Result)
#end

#macro MarkUsedTileMatx(TM,LatRow,LonCol,Radius)
  #local I=max(0,LatRow-Radius);
  #while(I<=min(LatRow+Radius,dimension_size(TM,1)-1))
    #local J=max(0,LonCol-Radius);
    #while(J<=min(LonCol+Radius,dimension_size(TM,2)-1))
      #declare TM[I][J]=1;
      #local J=J+1;
    #end
    #local I=I+1;
  #end
#end

#macro WriteTileMatx(TM,Oufn)
  #fopen ouf Oufn write
  #local rows=dimension_size(TM,1);
  #local cols=dimension_size(TM,2);
  #write(ouf,concat("#declare OldClock=",str(clock,0,6),";\n"))
  #write(ouf,concat("#declare TileMatx=array[",str(rows,1,0),"][",str(cols,1,0),"] {\n"))
  #local I=0;
  #while(I<dimension_size(TM,1))
    #local J=0;
    #local S="{";
    #while(J<dimension_size(TM,2))
      #if(defined(TM[I][J]))
        #local S=concat(S,str(TM[I][J],1,0),",");
      #else
        #local S=concat(S,"0,");
      #end
      #local J=J+1;
    #end
    #local S=concat(S,"},\n")
    #write(ouf,S)
    #local I=I+1;
  #end
  #write(ouf,"}\n")
  #fclose ouf
#end
    
#macro MakeShellTable(Shell,Re,CameraLoc,CameraLook,Angle,Pix,Table,UsedTiles)
  #declare UsedTiles=0;
  #if(Shell>0)
    #local Ratio=0.5;
    #local Limit=NumLatRows(Shell);
    #local PixSubtend=tan(radians(Angle*2/Pix));
    #local MapPixSize=Re*pi/(Limit*270);
    #local NearDist=vlength(CameraLoc)-Re;
    #local MapSubtend=MapPixSize/NearDist;
    #debug concat("Thinking about doing shell ",str(Shell,1,0),"\n")
    PrintNumber("PixSubtend (rad): ",PixSubtend)
    PrintNumber("MapPixSize (km):  ",MapPixSize)
    PrintNumber("Dist (km):        ",NearDist)
    PrintNumber("MapSubtend (rad): ",MapSubtend)
    PrintNumber("Ratio:            ",MapSubtend/PixSubtend)
    PrintNumber("Critical Ratio:   ",Ratio)
    #if((MapSubtend/PixSubtend)>Ratio)
      #if(file_exists(concat("/tmp/TileSave",str(Shell,1,0),".inc")))
        #debug "Reading TileSave\n"
        #include concat("/tmp/TileSave",str(Shell,1,0),".inc")
       	#if(OldClock>clock)
          #debug "TileSave out of sync: ignoring\n"
          #declare IgnoreMatx=1;
      	#else
          #debug "TileSave in sync: using\n"
          #declare IgnoreMatx=0;
      	#end
      #else
        #debug "Not Reading TileSave\n"
        #declare TileMatx=array[NumLatRows(Shell)][NumLatRows(Shell)*2];
        #declare IgnoreMatx=1;
      #end
      #debug concat("Doing shell ",str(Shell,1,0),"\n")
      #local First=true;
      #local LonTile=0;
      #while(LonTile<Limit*2)
        #local LatTile=0;
        #while(LatTile<Limit)
          #if(IgnoreMatx)
            #local CheckTile=1;
  	      #else
	          #local CheckTile=TileMatx[LatTile][LonTile];
	        #end
	        #if(CheckTile)
  	        #if(TileOK(Shell,LatTile,LonTile,CameraLoc,CameraLook,Angle,Pix,Re)) 
	            #local Table[UsedTiles][0]=LonTile;
 	            #local Table[UsedTiles][1]=LatTile;
  	          #declare UsedTiles=UsedTiles+1;
            #end
	        #end
          #set LatTile=LatTile+1;
        #end
        #set LonTile=LonTile+1;
      #end
      #local NumTiles=50*pow(pow(2,Shell-1),2);
      #local I=0;
      #debug "Marking used tiles\n"
      #declare NewTileMatx=array[NumLatRows(Shell)][NumLatRows(Shell)*2];
      #while(I<UsedTiles)
        MarkUsedTileMatx(NewTileMatx,Table[I][1],Table[I][0],1)
	      #local I=I+1;
      #end
      #if(UsedTiles>0)
        #debug "Writing used tiles\n"
        WriteTileMatx(NewTileMatx,concat("/tmp/TileSave",str(Shell,1,0),".inc"))
      #end
      #debug concat("Used ",str(UsedTiles,1,0)," of ",str(NumTiles,1,0)," (",str(UsedTiles/NumTiles*100,0,2),"%)\n")
    #else
      #local Table=array[1][1] {{0}};
      #debug concat("Not Doing shell ",str(Shell,1,0),"\n")
    #end
  #else
    #local Table=array[1][1] {{0}};
    #declare UsedTiles=0;
  #end
#end

#macro UseShellTable(Shell,MapName,Table,UsedTiles,MapType)
  #local T = 1.5;        // controls how fast the clouds become
                         // opaque towards the center (white areas)
                         // T=1 -> linear
                         // T<1 -> less transparency on the edges
                         // T>1 -> more transparency on the edges (better)
  #if(Shell>0)
    #if(UsedTiles>0)
      #debug concat("Doing shell ",str(Shell,1,0),"\n")
      #local Limit=NumLatRows(Shell);
      pigment{
        image_map{
      	  tile_map{
	          Limit*2,Limit
       	    #local Tile=0;
            #while(Tile<UsedTiles)
              #local LonTile=Table[Tile][0];
       	      #local LatTile=Table[Tile][1];
              #if(UseTest)
               	#local Filename=concat(str(Shell,1,0),"test.png");
       	      #else
              	#local Filename=concat("Earth",MapName,"/",str(Shell,1,0),"/",str(LonTile,-3,0),"x",str(LatTile,-3,0),".png");
      	      #end
              [LonTile LatTile png Filename]
              #set Tile=Tile+1;
      	    #end
       	  }
          map_type spheroid
      	  flatness (1-BEarth/AEarth)
      	  #if(MapType)
            #declare n=0;
      	    #while (n<256)
              transmit n,1-pow(n/(255),T)
              #declare n=n+1;
	          #end
      	  #end
        } 
      	rotate y*180
      }
    #else 
      pigment {color rgbf <1,1,1,1>}
    #end
  #else
    #debug "Doing shell 0\n"
    pigment {
      image_map {
        png concat("Earth",MapName,"/Earth",MapName,"0.png")
        map_type spheroid
      	flatness (1-BEarth/AEarth)
      }
      rotate y*180
    }
  #end
#end

#macro EarthTex()
  #ifdef(Shell0) texture {Shell0}  #end
  #ifdef(Shell1) texture {Shell1}  #end
  #ifdef(Shell2) texture {Shell2}  #end
  #ifdef(Shell3) texture {Shell3}  #end
  #ifdef(Shell4) texture {Shell4}  #end
  #ifdef(Shell5) texture {Shell5}  #end
#end

#macro CalcEarthMod(LCamLoc,Look,Angle)
  #local UseTest=0;

  #ifdef(UseShell0)
    #local Tiles0=0;
    #local Table0=array[pow(NumLatRows(0),2)*2][2];
    MakeShellTable(0,AEarth,LCamLoc,Look,Angle,image_width,Table0,Tiles0)
    #declare Shell0=texture {UseShellTable(0,"Map",Table0,Tiles0,0) finish { brilliance 0 ambient 0.5}}
  #end
	
  #ifdef(UseShell1)
    #local Tiles1=0;
    #local Table1=array[pow(NumLatRows(1),2)*2][2];
    MakeShellTable(1,AEarth,LCamLoc,Look,Angle,image_width,Table1,Tiles1)
    #declare Shell1=texture {UseShellTable(1,"Map",Table1,Tiles1,0) finish { brilliance 0 ambient 0.5}}
  #end
	
  #ifdef(UseShell2)
    #local Tiles2=0;
    #local Table2=array[pow(NumLatRows(2),2)*2][2];
    MakeShellTable(2,AEarth,LCamLoc,Look,Angle,image_width,Table2,Tiles2)
    #declare Shell2=texture {UseShellTable(2,"Map",Table2,Tiles2,0) finish { brilliance 0 ambient 0.5}}
  #end
	
  #ifdef(UseShell3)
    #local Tiles3=0;
    #local Table3=array[pow(NumLatRows(3),2)*2][2];
    MakeShellTable(3,AEarth,LCamLoc,Look,Angle,image_width,Table3,Tiles3)
    #declare Shell3=texture {UseShellTable(3,"Map",Table3,Tiles3,0) finish { brilliance 0 ambient 0.5}}
  #end
	
  #ifdef(UseShell4)
    #local Tiles4=0;
    #local Table4=array[pow(NumLatRows(4),2)*2][2];
    MakeShellTable(4,AEarth,LCamLoc,Look,Angle,image_width,Table4,Tiles4)
    #declare Shell4=texture {UseShellTable(4,"Map",Table4,Tiles4,0) finish { brilliance 0 ambient 0.5}}
  #end
	
  #ifdef(UseShell5)
    #local Tiles5=0;
    #local Table5=array[pow(NumLatRows(5),2)*2][2];
    MakeShellTable(5,AEarth,LCamLoc,Look,Angle,image_width,Table5,Tiles5)
    #declare Shell5=texture {UseShellTable(5,"Map",Table5,Tiles5,0) finish { brilliance 0 ambient 0.5}}
  #end
	
  #declare HardSurface=union {
	  sphere {
      0,1
      scale <1,BEarth/AEarth,1>
		//	pigment {color rgb <1,0.5,0>}
		}
/*	
  	object {
  		#include "HiResDEM/5-026x023.mesh2"
			scale 1/AEarth
//			pigment {color rgb <0.5,0,1>}
		}
		object {
  		#include "HiResDEM/5-025x023.mesh2"
			scale 1/AEarth
//			pigment {color rgb <1,0,0>}
		} 
		*/
    EarthTex()
    scale AEarth
  }

#end

#macro UseEarthMod()
  union {
    object {HardSurface}
  }
#end

#macro EarthMod(CamLoc,Look,Angle)
  CalcEarthMod(CamLoc,Look,Angle)
  UseEarthMod()
#end
