//pooltabl.inc
          
//Pool table s 30 ball radii on the short sides, 60 on the long sides

//#debug "Parsing Pool Table (pooltabl.inc)\n"

#macro WireBox(v1,v2,r)  //V1 and v2 are vector corners, r is radius of wire
  //X
  cylinder {
    <v1.x,v1.y,v1.z>,<v2.x,v1.y,v1.z>,r
  }
  cylinder {
    <v1.x,v2.y,v1.z>,<v2.x,v2.y,v1.z>,r
  }
  cylinder {
    <v1.x,v1.y,v2.z>,<v2.x,v1.y,v2.z>,r
  }
  cylinder {
    <v1.x,v2.y,v2.z>,<v2.x,v2.y,v2.z>,r
  }
  //Y
  cylinder {
    <v1.x,v1.y,v1.z>,<v1.x,v2.y,v1.z>,r
  }  
  cylinder {
    <v1.x,v1.y,v2.z>,<v1.x,v2.y,v2.z>,r
  }  
  cylinder {
    <v2.x,v1.y,v1.z>,<v2.x,v2.y,v1.z>,r
  }  
  cylinder {
    <v2.x,v1.y,v2.z>,<v2.x,v2.y,v2.z>,r
  }  
  //Z
  cylinder {
    <v1.x,v1.y,v1.z>,<v1.x,v1.y,v2.z>,r
  }  
  cylinder {
    <v2.x,v1.y,v1.z>,<v2.x,v1.y,v2.z>,r
  }  
  cylinder {
    <v1.x,v2.y,v1.z>,<v1.x,v2.y,v2.z>,r
  }  
  cylinder {
    <v2.x,v2.y,v1.z>,<v2.x,v2.y,v2.z>,r
  }  
  
#end

#macro Pockets(v1,v2,r)
  //X    
  union {
    sphere {
      <v1.x,v1.y,v1.z>,r
    }
    sphere {
      <v2.x,v1.y,v1.z>,r
    }
    sphere {
      <v1.x,v2.y,v1.z>,r
    }
    sphere {
      <v2.x,v2.y,v1.z>,r
    }
    
    sphere {
      <v1.x,v1.y,v2.z>,r
    }
    sphere {
      <v2.x,v1.y,v2.z>,r
    }
    sphere {
      <v1.x,v2.y,v2.z>,r
    }
    sphere {
      <v2.x,v2.y,v2.z>,r
    }
    
    sphere {
      <(v1.x+v2.x)/2,v1.y,v2.z>,r
    }
    sphere {
      <(v1.x+v2.x)/2,v2.y,v1.z>,r
    }
    sphere {
      <(v1.x+v2.x)/2,v2.y,v2.z>,r
    }
    sphere {
      <(v1.x+v2.x)/2,v1.y,v1.z>,r
    }   
  }
   
#end


#declare ShortSide=30;
#declare HoleRadius=3;
#declare RailRadius=1.5;

//Floors and ceilings
#declare Floor=array[2] {-ShortSide/2,ShortSide/2}

//Walls
#declare WallX=array[2] {-ShortSide,ShortSide}
#declare WallZ=array[2] {-ShortSide/2,ShortSide/2}

#declare Hole=array[12] {
  <-ShortSide,-ShortSide/2,-ShortSide/2>,    //0
  <ShortSide,-ShortSide/2,-ShortSide/2>,     //1
  <0,-ShortSide/2,-ShortSide/2>,             //2
  <-ShortSide,ShortSide/2,-ShortSide/2>,     //3
  <ShortSide,ShortSide/2,-ShortSide/2>,      //4
  <0,ShortSide/2,-ShortSide/2>,              //5
  <-ShortSide,-ShortSide/2,ShortSide/2>,     //6
  <ShortSide,-ShortSide/2,ShortSide/2>,      //7
  <0,-ShortSide/2,ShortSide/2>,              //8
  <-ShortSide,ShortSide/2,ShortSide/2>,      //9
  <ShortSide,ShortSide/2,ShortSide/2>,       //10
  <0,ShortSide/2,ShortSide/2>                //11
}


#declare PoolTable=union {
  //Walls
  #ifdef(UseTransparentWalls)
  box {
    <-ShortSide,-ShortSide/2, -ShortSide/2>,
    <ShortSide,ShortSide/2, ShortSide/2>
    pigment {color White filter 1}
    finish {reflection 0.2}
  }
  #end 
  
  
  //Rails
  
  difference {     
    union {
      WireBox(<-ShortSide-RailRadius,-ShortSide/2-RailRadius,-ShortSide/2-RailRadius>,
              <+ShortSide+RailRadius,+ShortSide/2+RailRadius,+ShortSide/2+RailRadius>,RailRadius)
      Pockets(<-ShortSide-RailRadius,-ShortSide/2-RailRadius,-ShortSide/2-RailRadius>,
              <+ShortSide+RailRadius,+ShortSide/2+RailRadius,+ShortSide/2+RailRadius>,RailRadius)
    }
    Pockets(<-ShortSide,-ShortSide/2,-ShortSide/2>,<ShortSide,ShortSide/2,ShortSide/2>,HoleRadius+0.001)
    pigment {color Green}
  }          
  
  //Pockets
  difference {
    Pockets(<-ShortSide,-ShortSide/2,-ShortSide/2>,<ShortSide,ShortSide/2,ShortSide/2>,HoleRadius)
    Pockets(<-ShortSide,-ShortSide/2,-ShortSide/2>,<ShortSide,ShortSide/2,ShortSide/2>,HoleRadius-0.05)
    box {
      <-ShortSide,-ShortSide/2,-ShortSide/2>,<ShortSide,ShortSide/2,ShortSide/2>
    }
    pigment {DMFWood1 scale 10 rotate -x*5}
  }
}       

//#debug "Done with Pool Table (pooltabl.inc)\n"
