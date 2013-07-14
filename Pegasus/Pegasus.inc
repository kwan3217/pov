#version unofficial Megapov 1.22;
#declare Deploy=0;

#include "Logo.inc"
#include "metals.inc"

#ifndef(PegasusClock) #declare PegasusClock=0; #end
#ifndef(FSSep)        #declare FSSep=95;       #end
#ifndef(ISep)         #declare ISep=97;        #end
#ifndef(FSep)         #declare FSep=105;       #end
#ifndef(SSSep)        #declare SSSep=115;      #end
#ifndef(TSSep)        #declare TSSep=552;      #end
#ifndef(FairingDeploy)#declare FairingDeploy=0;#end
#ifndef(LFinCommand)  #declare LFinCommand=0;  #end
#ifndef(RFinCommand)  #declare RFinCommand=0;  #end
#ifndef(VFinCommand)  #declare VFinCommand=0;  #end
#include "PegasusFin.inc"

#macro Band(Pos,Width,Radius)
  cylinder {
    <Pos-Width/2,0,0>,<Pos+Width/2,0,0>,Radius
  }
#end

#macro Wedge(Start,Stop)
  intersection {
    plane {
      -y,0
      rotate x*Start
    }
    plane {
      y,0
      rotate x*Stop
    }
  }
#end

#macro PartialBand(Pos,Width,Radius,Start,Stop)
  intersection {
    Band(Pos,Width,Radius)
    Wedge(Start,Stop)
  }
#end

#declare HingeBlock=union {
  box {
    <3.5, 0, -0.5>, <4.5, 3, 0.5>
  }
  box {
    <0, -0.5, -0.5>, <5, 0.5, 0.5>
    rotate z*degrees(atan(3/4))
  }
  cylinder {
    <4, 3, -0.5>, <4, 3, 0.5>, 0.5
  }
  cylinder {
    <4, 0, -0.5>, <4, 0, 0.5>, 0.5
  }
  cylinder {
    <0, 0, -0.5>, <0, 0, 0.5>, 0.5
  }
  box {
    <1.52942, -1.40023, -0.5>, <4.24816, 0.485171, 0.5>
    rotate z*30
  }
  box {
    <0, -0.5, -0.5>, <4, 0.5, 0.5>
  }
  translate -x*4
  rotate -x*90
  scale <2,1,1>
}

#macro HollowBand(Pos,Width,Inner_radius,Outer_radius)
  difference {
    cylinder {
      <Pos-Width/2,0,0>,<Pos+Width/2,0,0>,Outer_radius
    }
    cylinder {
      <Pos-Width/2-0.001,0,0>,<Pos+Width/2+0.001,0,0>,Inner_radius
    }
  }
#end

#macro HollowPartialBand(Pos,Width,Inner_radius,Outer_radius,Start,Stop)
  intersection {
    HollowBand(Pos,Width,Inner_radius,Outer_radius)
    Wedge(Start,Stop)
  }
#end

#macro RivetChain(Radius,Rivet_pos,N_rivet,Rivet_rad,Rivet_length,RivetTex)
  union {
    #local I=0;
    #while(I<N_rivet)
      cylinder {
        <Rivet_pos,0,Radius-Rivet_length>,<Rivet_pos,0,Radius+Rivet_length>,Rivet_rad
        rotate x*Linterp(0,0,N_rivet,360,I)
      }
      #local I=I+1;
    #end
    texture {RivetTex}
  }
#end

#macro FieldJoint(Pos,Width,Radius,Rivet_pos,N_rivet,Rivet_rad,Rivet_length,JointTex,RivetTex)
  union {
    object {
      Band(Pos,Width,127/2,Radius)
      texture {JointTex}
    }
    RivetChain(Radius,Rivet_pos,N_rivet,Rivet_rad,Rivet_length,RivetTex)
  }
#end

#macro HollowFieldJoint(Pos,Width,Inner_radius,Outer_radius,Rivet_pos,N_rivet,Rivet_rad,Rivet_length,JointTex,RivetTex)
  union {
    object {
      HollowBand(Pos,Width,Inner_radius,Outer_radius)
      texture {JointTex}
    }
    RivetChain(Outer_radius,Rivet_pos,N_rivet,Rivet_rad,Rivet_length,RivetTex)
  }
#end

#declare WingBoxPod=union {
  cylinder {
    <0,0,0>,<30,0,0>,10
  }
  sphere {
    <0,0,0>,10
  }
  sphere {
    <30,0,0>,10
  }
  scale <1,1,1/6>
}

#declare Pegasus1WingBox = difference {
  union {
    box {
      <600,0,-64>,<870,63.5,64>
    }
    object {
      WingBoxPod
      translate <640,30,-64>
    }
    object {
      WingBoxPod
      translate <640,30,64>
    }
    object {
      WingBoxPod
      translate <780,30,-64>
    }
    object {
      WingBoxPod
      translate <780,30,64>
    }
    difference {
      box {
        <625,15,-64.5>,<685,50,64.5>
      }
      box {
        <625+2,15+2,63.5+2>,<685-2,50-2,-63.5-2>
      }
    }
    difference {
      box {
        <765,15,-64.5>,<825,50,64.5>
      }
      box {
        <765+2,15+2,63.5+2>,<825-2,50-2,-63.5-2>
      }
    }
    intersection {
      cylinder {
        <870,0,200>,<870,73.5,200>,263.5
      }
      cylinder {
        <0,-187.5295,-73.5>,<0,-187.5295,73.5>,261.0295
        matrix <1,0,0,
                0,1,0,
                370/335.3,0,1,
                970,0,0>
      }
      plane {
        z,0
      }
    } 
    intersection {
      plane {
        -z,0
      }
      cylinder {
        <870,0,-200>,<870,75.5,-200>,263.5
      }
      cylinder {
        <0,-187.5295,-73.5>,<0,-187.5295,73.5>,261.0295
        matrix <1,0,0,
                0,1,0,
               -370/335.3,0,1,
                970,0,0>
      }
    }
    intersection {
      cylinder {
        <0,0,200>,<0,73.5,200>,264
      }
      cylinder {
        <0,0,-200>,<0,75.5,-200>,264
      }
      cylinder {
        <0,-500,-73.5>,<0,-500,73.5>,573.5
      }
      translate x*600
    } 
  }
  cylinder {
    <0,0,0>,<1500,0,0>,127/2
  }
}

#declare Pegasus1Wing=intersection {
  prism {
    linear_spline -10,10,6
    <570.0,335.3>,<600,335.3>,<970,0>,<600.0,-335.3>,<570,-335.3>,<570.0,335.3>
  }
  plane {
    vnormalize(vnormalize(<335.3,0,-370>)+y*8),0
    translate x*970
  }
  plane {
    vnormalize(vnormalize(<335.3,0,-370>)-y*8),0
    translate x*970
  }
  plane {
    vnormalize(vnormalize(<335.3,0,370>)+y*8),0
    translate x*970
  }
  plane {
    vnormalize(vnormalize(<335.3,0,370>)-y*8),0
    translate x*970
  }
  plane {
    vnormalize(vnormalize(<-1,0,0>)+y*12),0
    translate x*570
  }
  plane {
    vnormalize(vnormalize(<-1,0,0>)-y*12),0
    translate x*570
  }
  bounded_by {
    box {<570,-10,-335.3>,<970,10,335.3>}
  }
  pigment {color rgb 1}
  finish {ambient 0.5}
  scale <1,1.39689,1>
  translate y*(127/2+10)
}

#declare DedicationRight=text {
  ttf "signature.ttf" "In Memory Of  Larry Myers"
  1,0
  h_align_center
  scale <5,5,100>
  translate -z*100
  translate <725,-5,0>
}

#declare DedicationLeft=text {
  ttf "signature.ttf" "In Memory Of Lyle Howe and Mike Raaf"
  1,0
  h_align_center
  scale <5,5,100>
  translate -z*100
  rotate y*180
  translate <725,-5,0>
}

#declare Dedications=union {
  object {DedicationLeft}
  object {DedicationRight}
}

#if(PegasusClock<(FSSep+60))  
  #declare Pegasus1=union {
    RivetChain(127/2,190,100,0.4,0.1,T_Chrome_4A)
    difference {
      union {
        cone {
          <47,0,0>,150/2,<170.5,0,0>,75/2
          open
        }
        cylinder {
          <220,125/2,0>,<800,125/2,0>,4
          rotate -x*20
        }
        sphere {
          <0,0,0>,4
          scale <2,1,1>
          translate <220,125/2,0>
          rotate -x*20
        }
        pigment {color rgb 1}
        finish {ambient 0.5}
      }
      box {<0,0,-2>,<1.5,2,2> color rgb 1}
    }
    union {
      object {Pegasus1WingBox}
      cylinder {
        <80,0,0>,<1000.5,0,0>,127.0/2
        open
      }
      sphere {
        <0,0,0>,1
        scale <30.5,63.5,63.5>
        translate <960,0,0>
        pigment {color rgb 0.1}
        finish {ambient 0.5}
      }
      //Wing bands
      union {
        Band(725,230,128/2)
        pigment {
          object {
            Dedications
            pigment {color rgb 1}
            pigment {color rgb 0.1}
          }
        }
        finish {ambient 0.5}
      }

      //Flight Sep back half (interstage)
      Band(1000.5-2.5,5,128/2)
      texture {
        pigment {color rgb 1}
        finish {ambient 0.5}
      }
      #ifndef(Quick)
        LogoThruL("svg/USFlag",          1900,1000,90, 250,  0)
        LogoSame ("AimLogo",             1265, 922,60, 440,  0) 
        LogoSame ("svg/Hampton",         1000,1000,26, 377, 15)
        LogoSame ("svg/NewLASPLogoFull", 1400, 456,34, 373,-10)
        LogoSame ("svg/ATKBlue",       1000, 377,60, 530,  0)
        LogoSame ("svg/VTRibbon",         761,1098,30, 830, 40)
        LogoSame ("svg/NASA Meatball",   1584,1280,60, 920,  0)
      #end
    }
    object {
      Pegasus1Fin
      translate -x*170
      rotate y*VFinCommand
      translate x*170
    }
    object {
      Pegasus1Fin
      translate -x*170
      rotate -y*LFinCommand
      translate x*170
      rotate x*(23+90)
    }
    object {
      Pegasus1Fin
      translate -x*170
      rotate y*RFinCommand
      translate x*170
      rotate -x*(23+90)
    }
    object {Pegasus1Wing}
    
    scale 0.01 //Convert to official scale of 1POVunit=1m
  }
#end

#declare Pegasus2=union {
  HollowFieldJoint(1085.0,6,127/2,127.5/2,1083,100,0.5,0.2,T_Chrome_5A,T_Chrome_2A)
  union {
    HollowBand(1090.5,5,127/2,128/2)
    #include "Stage2Nozzle.inc"
    cylinder {
      <1110,125/2,0>,<1275,125/2,0>,4
    }
    sphere {
      <0,0,0>,4
      scale <2,1,1>
      translate <1110,125/2,0>
    }
    sphere {
      <0,0,0>,4
      scale <2,1,1>
      translate <1275,125/2,0>
    }
    HollowBand(1299.7-2.5,5,127/2,128/2)
    pigment {color rgb 1}
    finish {ambient 0.5}
  }
  cylinder {
    <1081.0,0,0>,<1299.7,0,0>,127.0/2
    open
    texture {
      pigment {color rgb 1}
      finish {ambient 0.5}
    }
    #ifndef(Quick)
    LogoSame("svg/Orbital",1500,653,120,(1299.7+1081)/2-120/2,0)
    #end
  }
  HollowFieldJoint(1302.7,6,127.0/2,127.5/2,1300.7,100,0.5,0.1,T_Chrome_5A,T_Chrome_2A)
  HollowFieldJoint(1308.7,6,126.5/2,127.0/2,1300.7,100,0.5,0.2,T_Gold_1A,T_Chrome_2A)
  union {
    object {
      HingeBlock
      scale <1,3,1>
      translate <1305,7.5,-63.5>
    }  
    object {
      HingeBlock
      scale <1,3,1>
      translate <1305,-7.5,-63.5>
    }  
    object {
      HingeBlock
      scale <1,3,1>
      translate <1305,7.5,-63.5>
      rotate x*180
    }  
    object {
      HingeBlock
      scale <1,3,1>
      translate <1305,-7.5,-63.5>
      rotate x*180
    }  
    texture {T_Chrome_4A}
  }
  cone {
    <1299.7,0,0>,127/2,
    <1340,0,0>,Linterp(1299.7,127/2,1354.1,99/2,1340)
    open
    texture {
      radial
      texture_map{
        [0.1 T_Chrome_5A]
        [0.1 pigment {color rgb 0.2}]
        [0.9 pigment {color rgb 0.2}]
        [0.9 T_Chrome_5A]
      }
      frequency 2
      rotate z*90
      rotate x*90
    }
  }
  cone {
    <1340,0,0>,Linterp(1299.7,127/2,1354.1,99/2,1340),
    <1347.5,0,0>,Linterp(1299.7,127/2,1354.1,99/2,1347.5)
    open
    pigment {color rgb 0.2}
  }
  cone {
    <1347.5,0,0>,Linterp(1299.7,127/2,1354.1,99/2,1347.5),
    <1354.1,0,0>,99/2
    open
    texture {T_Chrome_5A}
  }
  scale 0.01 //Convert to official scale of 1POVunit=1m
}  

#declare Pegasus3Engine=union {
  cone {
    <1299.7,0,0>,77/2,<1354.1,0,0>,55/2
    pigment {color rgb 0.2}
    finish {ambient 0.5}
  }
  union {
    cylinder {
      <1354.1,0,0>,<1419.6,0,0>,97/2
    }
    sphere {
      0,97/2
      scale <0.5,1,1>
      translate x*1419.6
    }
    pigment {color rgb 0.2}
    finish {ambient 0.5 phong 0.5}
  }
  #ifndef(Quick)
  union {
    cylinder {
      <1354.1,0,-99/2>,<1419.6,0,-99/2>,1
      rotate x*15
    }
    cylinder {
      <1354.1,0,-99/2>,<1419.6,0,-99/2>,0.5
      rotate -x*15
    }
    cylinder {
      <1354.1,0,-99/2>,<1419.6,0,-99/2>,0.5
      rotate x*195
    }
    cylinder {
      <1354.1,0,-99/2>,<1419.6,0,-99/2>,0.5
      rotate -x*195
    }
    cylinder {
      <1418.6,0,0>,<1420.6,0,0>,101/2
    }
    cylinder {
      <1354.1,0,0>,<1364.1,0,0>,99/2
    }
    cylinder {
      <1354.1,0,0>,<1355.1,0,0>,101/2
    }
    texture {T_Chrome_5A}
  }
  union {
    #declare I=0;
    #while(I<100)
      cylinder {
        <1367.1,0,-96/2>,<1367.1,0,-97.25/2>,0.25
        rotate x*I*3.6
      }
      cylinder {
        <1365.1,0,-96/2>,<1365.1,0,-97.25/2>,0.25
        rotate x*(I*3.6+1.8)
      }
      cylinder {
        <1414.1,0,-96/2>,<1414.1,0,-97.25/2>,0.25
        rotate x*(I*3.6+1.8)
      }
      #declare I=I+1;
    #end
    texture {T_Gold_5A}
  }
  #end
  scale 0.01 //Convert to official scale of 1POVunit=1m
}

#declare NameRight=text {
  ttf "signature.ttf" "Bryony"
  1,0
  h_align_center
  scale <15,15,100>
  translate -z*100
  rotate z*10
  translate x*1635
}

#declare NameLeft=text {
  ttf "signature.ttf" "Bryony"
  1,0
  h_align_center
  scale <15,15,100>
  translate -z*100
  rotate z*10
  rotate y*180
  translate x*1635
}

#declare Names=union {
  object {NameRight}
  object {NameLeft}
}

#declare RCSHoles=union {
  cone {
    <1450,0,-61>,0,<1450,65,-62>,6
  }
  cone {
    <1450,0,-61>,0,<1450,-65,-62>,6
  }
  cone {
    <1450,0,-61>,0,<1450,0,-62-25>,10
  }
  pigment {color rgb <1,1,0>}
}

#declare RCSDecoration=union {
  HollowPartialBand(1450,20,127/2,127.5/2,8,24)
  HollowPartialBand(1450,20,127/2,127.5/2,-24,-8)
  HollowPartialBand(1450,10,127/2,127.5/2,-4,4)
}

#declare FairingDecoration=union {
  sphere {
    0,6
    scale <2,1,0.5>
    translate <1422.5,0,-126/2>
    clipped_by {
      box {
        <1422.5,-10,-126/2>,<1440,10,-126/2-5>
      }
    }
  }
  union {
    HollowPartialBand(1420,5,127/2,127.5/2,-12,12) 
    texture {T_Chrome_4A}
  }
}

#declare PegasusFairing=union {
  union {
    union {
      difference {
        union {
          cylinder {
            <1305.7,0,0>,<1585.5,0,0>,127/2
            open
          }
          object {RCSDecoration}
          object {RCSDecoration scale <1,1,-1>}
        }
        object {RCSHoles}
        object {RCSHoles scale <1,1,-1>}
      }
      HollowBand(1425,5,127/2,127.5/2)
      HollowBand(1580,5,127/2,127.5/2)
      HollowBand(1308.7,6,127/2,128/2)
      object {FairingDecoration}
      object {FairingDecoration scale <1,1,-1>}
      object {FairingDecoration translate x*(1580-1425)}
      object {FairingDecoration translate x*(1580-1425) scale <1,1,-1>}
    }
    sphere {
      0,1
      scale <155,127/2,127/2>
      translate <1585.5,0,0>
      clipped_by { plane {x,1585.5 inverse} }
      pigment {
        object {
          Names
          pigment {color rgb 1}
          pigment {color rgb 0.1}
        }
      }
      finish {ambient 0.5}
    }
  }
  union {
    object {
      HingeBlock
      scale 1.2
      rotate z*180
      scale <1,3,1>
      translate <1305,7.5,-63.5>
    }  
    object {
      HingeBlock
      scale 1.2
      rotate z*180
      scale <1,3,1>
      translate <1305,-7.5,-63.5>
    }  
    object {
      HingeBlock
      scale 1.2
      rotate z*180
      scale <1,3,1>
      translate <1305,7.5,-63.5>
      rotate x*180
    }  
    object {
      HingeBlock
      scale 1.2
      rotate z*180
      scale <1,3,1>
      translate <1305,-7.5,-63.5>
      rotate x*180
    }  
    texture {T_Chrome_4A}
  }
  union {
    cylinder {
      <1305.7,0,0>,<1585.5,0,0>,126/2
      open
    }
    sphere {
      0,1
      scale <153,126/2,126/2>
      translate <1585.5,0,0>
      clipped_by { plane {x,1585.5 inverse} }
    }
    texture {
      T_Chrome_5A
      normal {wrinkles 1 scale 10}
    }
  }
  pigment {color rgb 1}
  finish {ambient 0.5}
}

#declare PegasusFairingLeft=object {
  PegasusFairing
  clipped_by {box {<1299,-200,0>,<1700,200,-200> inverse} }
  #ifndef(Quick)
	  LogoThruL("svg/PegasusLeft",845,390,120,1445,10)
  #end
  translate <-1299.7,0,-127/2>
//  rotate -y*FairingDeploy*60
  translate -<-1299.7,0,-127/2>
  scale 0.01 //Convert to official scale of 1POVunit=1m
}

#declare PegasusFairingRight=object {
  PegasusFairing
  clipped_by {box {<1299,-200,0>,<1700,200,-200> } }
  #ifndef(Quick)
	  LogoThruR("svg/PegasusRight",845,390,120,1445,10)
  #end
  translate <-1299.7,0,127/2>
//  rotate y*FairingDeploy*60
  translate -<-1299.7,0,127/2>
  scale 0.01 //Convert to official scale of 1POVunit=1m
}

#declare Pegasus1Inter=union {
  cylinder {
    <1000.5,0,0>,<1081.0,0,0>,127.0/2
    open
  }
  HollowBand(1079,2,127/2,128/2)
  pigment {color rgb 1}
  finish {ambient 0.5}
  scale 0.01 //Convert to official scale of 1POVunit=1m
}

#declare Avionics=union {
  cylinder {
    <1419.6,0,0>,<1475.5,0,0>,97/2
    open
    pigment {color rgb 1/3}
    finish {ambient 0.5}
  }
  union {
    cylinder {
      <1475.5,0,0>,<1485.5,0,0>,97/2
      open
    }
    #local I=0;
    #while(I<50)
      box {
        <1485.5,-2,-97/2-6>,<1487.5,2,-97/2+6>
        rotate x*Linterp(0,0,50,360,I)
      }
      #local I=I+1;
    #end
    cylinder {
      <1487.5,0,0>,<1497.5,0,0>,97/2
      open
    }
    texture {T_Chrome_5A}
  }
  union {
    box {
      <1429,-10,-90/2>,<1460,10,-110/2>
      texture {T_Chrome_5A}
      rotate x*90
    }   
    box {
      <1429,-10,-90/2>,<1470,10,-110/2>
      texture {T_Chrome_5A}
      rotate x*120
    }   
    box {
      <1429,-10,-90/2>,<1470,10,-110/2>
      texture {T_Chrome_5A}
      rotate x*60
    }   
    box {
      <1429,-10,-90/2>,<1470,10,-110/2>
      rotate x*270
    }   
    cylinder {
      <1439,0,-107/2>,<1470,0,-107/2>,5
      rotate x*10
    }   
    cylinder {
      <1439,0,-107/2>,<1470,0,-107/2>,5
      rotate x*170
    }   
    cylinder {
      <1439,0,-107/2>,<1470,0,-107/2>,5
      rotate x*190
    }   
    cylinder {
      <1439,0,-107/2>,<1470,0,-107/2>,5
      rotate x*350
    }   
    texture {T_Chrome_5A}
  }
  torus {
    98/2,1
    rotate z*90
    translate x*1424.7
    pigment {color rgb 1}
  }
  scale 0.01 //Convert to official scale of 1POVunit=1m
}

#declare Pegasus3=union {
  object {Pegasus3Engine}
  object {Avionics}
}

#ifndef(PegasusClock)
  #declare PegasusClock=550;
#end

#declare EngineOn=false;
#ifndef(LitStage) #declare LitStage=0; #end
#if(LitStage=1)
  #declare EngineOn=true;
  #declare FlamePoint=0.47;
#end

#if(LitStage=2)
  #declare EngineOn=true;
  #declare FlamePoint=9.95;
#end

#if(LitStage=3)
  #declare EngineOn=true;
  #declare FlamePoint=12.997;
#end
PrintNumber("EngineOn: ",EngineOn)
PrintNumber("LitStage: ",LitStage)

#include "flame2.inc"

#declare Pegasus=union {
  #if(EngineOn) object {Flame translate x*(FlamePoint)} #end
  #ifdef(Pegasus1)#if(PegasusClock<FSSep) object {Pegasus1} #end #end
  #if(PegasusClock<ISep) object {Pegasus1Inter} #end

  #if(FairingDeploy>0) 
    #include "Aim/Aim.inc"
  #end
  #if(FairingDeploy<1)
    object {PegasusFairingLeft} 
    object {PegasusFairingRight} 
  #end

  #if(PegasusClock<SSSep) object {Pegasus2} #end
  #if(PegasusClock<TSSep) object {Pegasus3} #end
  #ifdef(Aim) object {Aim rotate z*90 translate 14.975*x} #end
}


