//Station.inc
//Space Station Model

#warning "Parsing Space Station (station.inc)\n"
#ifndef(InternalBrightness)
#declare InternalBrightness=1;
#end

#include "metals.inc"
#warning "Parsing Astronaut (astrnaut.inc)\n"
#include "astrnaut.inc"
#warning "Done with Astronaut (astrnaut.inc)\n"

#declare TrussTexture=texture {
  pigment {color White}
}

#declare LockerTexture=texture {
  pigment {color White}
}

#declare JointTexture=texture {
  T_Brass_3C
}

#declare MainModuleTexture=texture {
  pigment {color White}
  normal {wrinkles 0.2}
}

#declare DockingRingTexture=texture {
  T_Chrome_1A
}

#declare PanelFrameworkTexture=texture {
  pigment {color White}
}

#declare PanelTexture=texture {
  pigment {color rgb<0.2,0,0.5>}
  finish {phong 1 reflection 0.2}
}

#declare GlassTexture=texture {
  pigment {color rgbf <1,1,1,0.97>}
  finish {reflection 0.1 phong 1}
}

#declare BigTrussRadius=0.03;
#declare SmallTrussRadius=0.015;
#declare JointRadius=0.05;
#declare TrussGap=0.1;
#declare ModuleRadius=2;
#declare MainModuleLength=10;
#declare DockingRingRadius=1;
#declare WindowRadius=0.5;
#declare MemberLength=1;
#declare TrussUnits=50;
#declare SolarTrussUnits=10;
#declare PanelLength=20;
#declare PanelWidth=3;
#declare PortholeRadius=0.5;
#declare LockerWidth=0.8;
#declare CenterPoolModule=<0,-ModuleRadius-0.3,-(MainModuleLength/2+ModuleRadius+ModuleRadius/5+1)>;

#declare Member=union {
  cylinder {
    <0,TrussGap,0>,<0,MemberLength-TrussGap,0>,BigTrussRadius
    texture {TrussTexture}
  }
  cone {
    <0,TrussGap,0>,BigTrussRadius,<0,0,0>,0
    texture {JointTexture}
  }
  cone {
    <0,MemberLength-TrussGap,0>,BigTrussRadius,<0,1,0>,0
    texture {JointTexture}
  }
}

#declare TrussCap=union {
  //circumferencial beams
  object {Member}
  object {Member rotate x*90}
  object {Member translate z*MemberLength}
  object {Member rotate x*90 translate y*MemberLength}
  //diagonal brace
  cylinder {
    <0,0,0>,<0,MemberLength,MemberLength>,SmallTrussRadius
  }
  //joints
  sphere {
    <0,0,0>,JointRadius
    texture {JointTexture}
  }
  sphere {
    <0,MemberLength,0>,JointRadius
    texture {JointTexture}
  }
  sphere {
    <0,MemberLength,MemberLength>,JointRadius
    texture {JointTexture}
  }
  sphere {
    <0,0,MemberLength>,JointRadius
    texture {JointTexture}
  }
}

#declare TrussUnit=union {
  //longitudinal beams
  object {Member rotate -z*90}
  object {Member rotate -z*90 translate <0,MemberLength,0>}
  object {Member rotate -z*90 translate <0,0,MemberLength>}
  object {Member rotate -z*90 translate <0,MemberLength,MemberLength>}

  //Diagonal beams
  cylinder {
    <0,0,0>,<MemberLength,MemberLength,0>,SmallTrussRadius
  }
  cylinder {
    <0,MemberLength,0>,<MemberLength,MemberLength,MemberLength>,SmallTrussRadius
  }
  cylinder {
    <0,MemberLength,MemberLength>,<MemberLength,0,MemberLength>,SmallTrussRadius
  }
  cylinder {
    <0,0,MemberLength>,<MemberLength,0,MemberLength>,SmallTrussRadius
  }
  object {TrussCap}
  texture {TrussTexture}
}

#declare I=0;
#declare Truss=union {
  #while (I<TrussUnits)
  object {
    TrussUnit
    translate x*I*MemberLength
  }
  #declare I=I+1;
  #end
  object {
    TrussCap
    translate x*I*MemberLength
  }
}

#declare Panel=union {
  #declare I=0;
  #while(I-1<PanelLength)
    cylinder {
      <-PanelWidth/2,I+PanelWidth/2,0>,
      <PanelWidth/2,I+PanelWidth/2,0>,
      SmallTrussRadius
      texture {PanelFrameworkTexture}
    }
    #declare I=I+1;
  #end
  box {
    <0,0,0>,<PanelWidth,PanelLength,SmallTrussRadius>
    texture {PanelTexture}
    translate <-PanelWidth/2,PanelWidth/2,-SmallTrussRadius/2>
  }
  cylinder {
    <0,0,0>,<0,PanelWidth/2+PanelLength,0>,BigTrussRadius
    texture {TrussTexture}
  }
}
#declare I=1;
#declare SolarTruss=union {
  #while (I<SolarTrussUnits-1)
  object {
    TrussUnit
    translate x*I*MemberLength
  }
  #declare I=I+1;
  #end
  object {
    TrussCap
    translate x*I*MemberLength
  }
  box {
    <0,0,0>,<MemberLength,MemberLength,MemberLength>
    texture {TrussTexture}
  }
  box {
    <0,0,0>,<MemberLength,MemberLength,MemberLength>
    texture {TrussTexture}
    translate x*(SolarTrussUnits-1)*MemberLength
  }
  object {
    Panel
    rotate y*-30
    translate <MemberLength/2,MemberLength,MemberLength/2>
  }
  object {
    Panel
    rotate y*-30
    translate <(MemberLength*(SolarTrussUnits-1))+MemberLength/2,MemberLength,MemberLength/2>
  }
  object {
    Panel
    scale <1,-1,1>
    rotate y*-30
    translate <MemberLength/2,0,MemberLength/2>
  }
  object {
    Panel
    scale <1,-1,1>
    rotate y*-30
    translate <(MemberLength*(SolarTrussUnits-1))+MemberLength/2,0,MemberLength/2>
  }
}

#declare DockingRing=union {
  difference {
    cylinder {
      <0,0,-1>,<0,0,0.5>,DockingRingRadius
    }
    cylinder {
      <0,0,-1.01>,<0,0,0.51>,DockingRingRadius-0.02
    }
    texture {DockingRingTexture}
  }
  torus {
    DockingRingRadius,0.04
    texture {JointTexture}
    rotate x*90
    translate z*0.46
  }
}

#declare MainModule = union {
  difference {
    cylinder {
      <0,0,0>,<0,0,MainModuleLength>,ModuleRadius
    }
    cylinder {
      <0,0,0>,<0,0,MainModuleLength>,ModuleRadius-0.05
      texture {MainModuleTexture}
    }
  }
  cone {
    <0,0,0>,ModuleRadius,<0,0,-ModuleRadius/5>,DockingRingRadius
  }
  cone {
    <0,0,MainModuleLength>,ModuleRadius,<0,0,MainModuleLength+ModuleRadius/5>,DockingRingRadius
  }
  object {DockingRing rotate y*180 translate z*-ModuleRadius/5}
  object {DockingRing translate z*(MainModuleLength+ModuleRadius/5)}
  texture {MainModuleTexture}
}

#declare Locker=intersection {
  cylinder {
    <0,0,0>,<0,0,MainModuleLength>,ModuleRadius-0.05
    texture {MainModuleTexture}
  }            
//  box {
//    <-0.95,-0.95,-0.95>,<0.95,0.95,0.95>
  superellipsoid {
    <0.02 0.02>
    scale 0.5
    translate <0.5,0.5,0.5>
    scale <ModuleRadius/2,ModuleRadius,LockerWidth>
    translate <-ModuleRadius,-ModuleRadius/2,0>
  }
  texture {LockerTexture}
}

#declare PoolBot=union {
  object {
    Locker
    pigment {
      image_map {
        gif "poolbot.gif"
        once
      }
      rotate -y*90
      scale <ModuleRadius/2,ModuleRadius,LockerWidth>
      scale <0.95,1,0.95>
      translate <-ModuleRadius,-ModuleRadius/2,0.025>
    }
  }
  height_field {
    gif "keyboard.gif"
    scale <11,0.3,3>
    scale 0.8/11
    rotate -x*45
    rotate -y*90
    pigment {color White}
    translate <-ModuleRadius/2+3*0.8*0.707/11,0.15,0>
  }

  texture {LockerTexture}
}  

#declare PoolModule = union {
  difference {
    union {
      object {
        DockingRing
        rotate y*-90
        translate <-ModuleRadius,0,(MainModuleLength/4)>
      }
      object {
        DockingRing
        rotate y*-90
        translate <-ModuleRadius,0,(MainModuleLength*3/4)>
      }
      object {
        MainModule
        texture {MainModuleTexture}
        texture {
          pigment {
            image_map {
              gif "flags.gif" // the file to read (iff/gif/tga/png/sys)
              map_type 0 // 0=planar, 1=spherical, 2=cylindrical, 5=torus
              interpolate 2 // 0=none, 1=linear, 2=bilinear, 4=normalized distance         
              once
            }         
            translate -y/2
            translate -x/2
            scale <1,728/780,1>
            scale 2              
            rotate -y*90                     
            translate z*MainModuleLength*3/4
          }                    
          normal {wrinkles 0.2}
        }
        texture {
          pigment {
            image_map {
              gif "sskwan.gif" // the file to read (iff/gif/tga/png/sys)
              map_type 0 // 0=planar, 1=spherical, 2=cylindrical, 5=torus
              interpolate 2 // 0=none, 1=linear, 2=bilinear, 4=normalized distance         
              once
            }         
            translate -y/2
            translate -x/2
            scale <1,236/178,1>
            scale 2              
            rotate -y*90                     
            translate z*MainModuleLength/4
          }                    
          normal {wrinkles 0.2}
        }
      }       
    }
    cylinder {
      <-ModuleRadius-0.1,0,MainModuleLength/2>,<ModuleRadius+0.1,0,MainModuleLength/2>,PortholeRadius
      texture {MainModuleTexture}
    }
    cylinder {
      <0,0,MainModuleLength/4>,<-ModuleRadius-0.1,0,MainModuleLength/4>,DockingRingRadius-0.001
      texture {DockingRingTexture}
    }
    cylinder {
      <0,0,MainModuleLength*3/4>,<-ModuleRadius-0.1,0,MainModuleLength*3/4>,DockingRingRadius-0.001
      texture {DockingRingTexture}
    }
  }
  difference {
    cylinder {
      <-ModuleRadius-0.1,0,MainModuleLength/2>,<ModuleRadius+0.1,0,MainModuleLength/2>,PortholeRadius
      texture {MainModuleTexture}
    }
    cylinder {
      <-ModuleRadius-0.2,0,MainModuleLength/2>,<ModuleRadius+0.2,0,MainModuleLength/2>,PortholeRadius-0.05
      texture {MainModuleTexture}
    }
    cylinder {
      <0,0,0>,<0,0,MainModuleLength>,ModuleRadius-0.05
      texture {MainModuleTexture}
    }
    texture {MainModuleTexture}
  }
  disc {
    <-ModuleRadius-0.1,0,MainModuleLength/2>,x,PortholeRadius-0.05
    texture {
      GlassTexture
    }
  }
  disc {
    <ModuleRadius+0.1,0,MainModuleLength/2>,x,PortholeRadius-0.05
    texture {
      GlassTexture
    }
  }
  object {
    Astronaut      
#ifdef(AstronautRotate)
    rotate AstronautRotate
#end
    //rotate y*180
    translate z*MainModuleLength/4
  } 
  object {
    PoolBot
    translate z*(MainModuleLength/2+PortholeRadius)
  }
/*    
#declare I=0;        
#while(I<8)
  #if(I<1 | I>6)
  object {
    Locker
    translate z*LockerWidth*I
  }             
  #end
  #if(I<3 | I>4)
  object {
    Locker
    rotate z*90
    translate z*LockerWidth*I
  }   
  object {
    Locker
    rotate z*180
    translate z*LockerWidth*I
  }             
  object {
    Locker
    rotate z*270
    translate z*LockerWidth*I
  }
  #end
  #declare I=I+1;
#end
*/
}

#declare ShuttlePoint=<2.5,-ModuleRadius-0.3,MainModuleLength/2+ModuleRadius/5+0.5>;
#ifndef(ShuttleOfs)
#declare ShuttleOfs=0;
#end

#ifdef(UseShuttle)
#declare Shuttle=union {
  #include "shuttle.inc"
}                
#end

#declare Station=union {
  #ifndef(SimpleStation)
  object {
    Truss
    translate x*-(MemberLength/2*TrussUnits)
  }
  #end
  object {
    MainModule
    translate <-2.5,-ModuleRadius-0.3,-MainModuleLength/2>
  }
  object {
    MainModule
    translate <2.5,-ModuleRadius-0.3,-MainModuleLength/2>
  }
  object {
    PoolModule
    translate -z*MainModuleLength/2
    rotate y*90                 
    translate CenterPoolModule
  }
  light_source {
    <0,ModuleRadius*0.65,-ModuleRadius*0.65>+CenterPoolModule,
    color White*InternalBrightness/2
    area_light <MainModuleLength,0,0>,<0,0,-ModuleRadius>,25,1
    adaptive 0
    shadowless
    looks_like {
      cylinder {
        <-MainModuleLength/2,0,0>,<MainModuleLength/2,0,0>,0.02
        finish {ambient 1} 
        pigment {color <0.9,0.9,1>}
      }
    }
  }
  light_source {
    <0,ModuleRadius*0.65,ModuleRadius*0.65>+CenterPoolModule,
    color White*InternalBrightness/2
    area_light <MainModuleLength,0,0>,<0,0,-ModuleRadius>,25,1
    adaptive 0
    shadowless
    looks_like {
      cylinder {
        <-MainModuleLength/2,0,0>,<MainModuleLength/2,0,0>,0.02
        finish {ambient 1} 
        pigment {color <0.9,0.9,1>}
      }
    }
  }   
  #ifndef(SimpleStation)
  object {
    SolarTruss
    translate <0,-MemberLength/2,-MemberLength/2>
    rotate x*15
    translate <0,MemberLength/2,MemberLength/2>
    translate x*(MemberLength/2*TrussUnits)
  }
  object {
    SolarTruss
    translate <0,-MemberLength/2,-MemberLength/2>
    rotate x*15
    translate <0,MemberLength/2,MemberLength/2>
    translate -x*(MemberLength/2*TrussUnits)
    translate -x*(MemberLength*SolarTrussUnits)
  }
#ifdef(Shuttle)
  object {
    Shuttle
    scale 4.5
    rotate y*180
    translate ShuttlePoint+ShuttleOfs
    pigment {color White}
  }            
#end
#end
}
#warning "Done with Space Station (station.inc)\n"
