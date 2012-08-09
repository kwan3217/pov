#include "colors.inc"

#ifndef(Moon)
#declare Pos=0;
#declare Vel=1;

#declare Probe=array[2][25292]
#declare Moon=array[2][25292]

#include "d:\\probe.inc"
#include "d:\\moon.inc"
#include "shuttlep.inc"
#end

#declare Ea=0;
#declare Mo=1;
#declare ObjDetail=array[2] {99,99}
#declare AEarth=6378.135;
#declare BEarth=6356.752;       

#declare AMoon=1737.15;
#declare FMoon=1;
#declare BMoon=AMoon*FMoon;       

#declare StepNum=clock*25292;      

#declare Indexes = 256;  // number of entries in the gif color map

#declare T = 1.5;        // controls how fast the clouds become
                        // opaque towards the center (white areas)
                        // T=1 -> linear
                        // T<1 -> less transparency on the edges
                        // T>1 -> more transparency on the edges (better)


#if(ObjDetail[Ea]>=1)
#ifndef(EarthPigment)
#declare EarthPigment=pigment{
  image_map {
    png "d:\\pov\\PovSolar\\EarthMap.png" 
    map_type 1 
    interpolate 2
  }
}
#end
#end

#ifndef(EarthModel)
#declare EarthModel=union {
  //Surface
  sphere {
    0,1
    #if(ObjDetail[Ea]>=3)
      texture {
        material_map {  
          png "d:\\pov\\PovSolar\\EarthOcean.png"  //0 (Black) is land, 1 (white) is ocean
          map_type 1
          texture {   //Land
            pigment {EarthPigment}
            finish {ambient 0}
            #if(ObjDetail[Ea]>=4)
              normal {
                bump_map {
                  png "d:\\pov\\PovSolar\\EarthBump.png"
                  map_type 1 
                  interpolate 4 
                  bump_size 3
                }
              }
            #end
          }
          texture {  //Ocean
            pigment {EarthPigment}
            finish {
              ambient 0 
              diffuse 1 
              specular 0.5 
              roughness 0.01
            }
          }
        }
      }  
    #else 
      #if(ObjDetail[Ea]>=1)
        pigment {EarthPigment}
      #else
        pigment {color <0,0,1>}
      #end
    #end
  }
  //Cloud map (above Surface)
  #if(ObjDetail[Ea]>=2)
    sphere{
      0, 1.005
      pigment{
        image_map {
          png "d:\\pov\\povsolar\\EarthCloud.png" 
          map_type 1 
          interpolate 2
          #declare n=0;
          #while (n<Indexes)
            transmit n,1-pow(n/(Indexes-1),T)
            #declare n=n+1;
          #end
        }
      }
      finish {ambient 0 diffuse 1}
    } 
  #end
  //Night Map (Vert Slightly above Surface)
  #local T=1;
  #if(ObjDetail[Ea]>=2)
    sphere{
      0, 1.00001
      pigment{
        image_map {
          png "d:\\pov\\povsolar\\EarthNight.png" 
          map_type 1 
          interpolate 2  
          #declare n=0;
          #while (n<Indexes)
            transmit n,1-pow(n/(Indexes-1),T)
            //transmit all 0.9
            #declare n=n+1;
          #end
        }
      }
      finish {ambient 0.5 diffuse -20}
      no_shadow
    } 
  #end
  scale <AEarth,BEarth,AEarth>
  rotate y*180
}
#end    

#declare MoonModel=sphere {
  <0,0,0>,AMoon
  #if(ObjDetail[Mo]>=1)
    pigment {
      image_map {
        //Image from David Seal's Site http://maps.jpl.nasa.gov/textures/ear1ccc2.jpg
        png "d:\\pov\\PovSolar\\MoonMap.png" 
        map_type 1 
        interpolate 4
      }
    }
    #if(ObjDetail[Mo]>=4)
      normal {
        bump_map {
          png "d:\\pov\\PovSolar\\MoonBump.png"
          map_type 1 
          interpolate 4 
          bump_size 3
        }
      }
    #end
  #else
    pigment {color rgb<1,1,1>}
  #end
  scale <1, BMoon/AMoon,1>
  rotate y*180
}


object {
  EarthModel  
  rotate -y*360*StepNum/(86400/20)
}

object {
  MoonModel
  rotate -y*360*StepNum/(86400/20*27.3)
  translate Moon[Pos][StepNum]
}
      
/*      
#declare I=1;
#while(I<StepNum)
  cylinder {
    Probe[Pos][I-1],Probe[Pos][I],300
    pigment {color Yellow}
  }
  #declare I=I+1;
#end
*/
          
#macro LocationLookAt(Location,LookAt) 
  #local NY=vnormalize(LookAt-Location);
  #local NX=vnormalize(vcross(NY,-y)); // z is down in this example
  #local NZ=vcross(NX,NY);
  matrix < NX.x,NX.y,NX.z, NY.x,NY.y,NY.z, NZ.x,NZ.y,NZ.z, Location.x,Location.y,Location.z >
#end

          
          
object {
  Orbiter 
  scale 1/1000
  LocationLookAt(Probe[Pos][StepNum],Probe[Pos][StepNum]+Probe[Vel][StepNum])
}


camera { 
  location Probe[Pos][StepNum]+vnormalize(Probe[Pos][StepNum])*0.5
//  look_at Moon[Pos][StepNum]
  look_at Probe[Pos][StepNum]
}

light_source {
  <1,0,-1>*1e9
  color White*1.5
}

