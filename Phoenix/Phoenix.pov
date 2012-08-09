#version unofficial Megapov 1.22;

#include "host.inc"
#debug concat("\u001b];Phoenix.pov - ",Host," Render - frame ",str(frame_number,0,0)," of ",str(final_frame,0,0),"\a")

global_settings {
  right_handed
}

#include "KwanMath.inc"
#include "PhxLoadVec.inc"

#declare MeshAmbient=0.5;

#include "OrbiterMesh.inc"

#declare BackshellR0=Rd;
#if(T>Tdrop)
  #declare BackshellR0=Rd;
  PrintVector("BackshellR0: ",BackshellR0)
  #declare BackshellVt=+20;
  #declare BackshellV_LVLH=Vd_Ground+x*BackshellVt;
  PrintVector("BackshellV_LVLH: ",BackshellV_LVLH)
  PrintVector("LanderV_LVLH:    ",V_LVLH)
  #declare BackshellV=<vdot(BackshellV_LVLH,<Sky.x,Ln.x,Le.x>),
                       vdot(BackshellV_LVLH,<Sky.y,Ln.y,Le.y>),
                       vdot(BackshellV_LVLH,<Sky.z,Ln.z,Le.z>)>;
  #declare V_Check   =<vdot(V_LVLH,<Sky.x,Ln.x,Le.x>),
                       vdot(V_LVLH,<Sky.y,Ln.y,Le.y>),
                       vdot(V_LVLH,<Sky.z,Ln.z,Le.z>)>;
  PrintVector("BackshellV: ",BackshellV)
  PrintVector("LanderV:    ",V)
  PrintVector("LanderV:    ",V_Check)
  #declare Tsep=T-Tdrop;
  PrintNumber("Tsep: ",Tsep)
  #declare BackshellR=R+Tsep*BackshellV;
#else
  #declare BackshellR=R;
#end
PrintVector("BackshellR: ",BackshellR)
PrintVector("LanderR:    ",R)
PrintVector("Diff:       ",BackshellR-R)


#if(T<Tdrop+2) 
  #include "mpx_backshell.msh.inc"
  #local Para=BLinterp(Tpara0,0,Tpara1,1,T);
  union {
    mpx_backshell(array[1] {Para},mpx_backshell_AnimGroup,mpx_backshell_AnimParent,mpx_backshell_AnimType,mpx_backshell_AnimVec)
    rotate -z*90
    Shear_Trans(M3,-M1,M2)
    translate BackshellR-R
  }
#end

#macro Engines()
 	#local x0=0.205;
  #local y0=0.556;
  #local x1=0.110;
  #local y1=0.611;
  #local vx0=0.05;
  #local vy0=0.0;
  #local vz=-sqrt(1-vx0*vx0-vy0*vy0);
  #local Z=-0.330;
  union {
    #local X=-x0;#local Y=y0;#local vx=-vx0;#local vy=vy0;
    cone {
      <X,Y,Z>,0.05,
      <X,Y,Z>+0.6*<vx,vy,vz>,0
    }
    #local X=-x1;#local Y=y1;#local vx=-vx0;#local vy=vy0;
    cone {
      <X,Y,Z>,0.05,
      <X,Y,Z>+0.6*<vx,vy,vz>,0
    }
    #local X= x1;#local Y=y1;#local vx= vx0;#local vy=vy0;
    cone {
      <X,Y,Z>,0.05,
      <X,Y,Z>+0.6*<vx,vy,vz>,0
    }
    #local X= x0;#local Y=y0;#local vx= vx0;#local vy=vy0;
    cone {
      <X,Y,Z>,0.05,
      <X,Y,Z>+0.6*<vx,vy,vz>,0
    }
    finish {ambient 1}
    pigment {color rgb <1,0.5,0>}
    rotate -x*90
    rotate y*30
  }
#end

#if(T<Ths)
#include "mpx_heatshield2.msh.inc"
#declare Heat=BLinterp(1.7e8,0.12,7.5e8,1,DynHeat);
#if(Heat>0.12)
  #include "EntryFlame.inc"
#end

union {
  union {
    mpx_heatshield2(array[1] {0},mpx_heatshield2_AnimGroup,mpx_heatshield2_AnimParent,mpx_heatshield2_AnimType,mpx_heatshield2_AnimVec)
    rotate -z*90
  }
  #if(Heat>0.12)
    object {EntryFlame rotate -z*90 translate -y*0.25}
  #end
  Shear_Trans(M3,-M1,M2)
}

#else
  #include "mpx_lander.msh.inc"
  #local Leg1=BLinterp(TLeg1-0.2,0,TLeg1,1,T);
  #local Leg2=BLinterp(TLeg2-0.2,0,TLeg2,1,T);
  #local Leg3=BLinterp(TLeg3-0.2,0,TLeg3,1,T);
  union {
    mpx_lander(array[4] {Leg1,Leg2,Leg3,0},mpx_lander_AnimGroup,mpx_lander_AnimParent,mpx_lander_AnimType,mpx_lander_AnimVec)
    #declare EnginePhaseStart=0.005;
    #if(T<408) 
      #declare EngineDuty=0.5;
    #else
      #declare EngineDuty=1.5;
    #end
    PrintNumber("Engine Duty: ",EngineDuty)
    #declare EnginePhase=mod(frame_number,3);
    PrintNumber("Engine Phase: ",EnginePhase)
    #declare EngineOn=(EnginePhase<EngineDuty) * (T<Tland) * (T>Teng);
    PrintNumber("Engines On: ",EngineOn)
    #if(EngineOn)
    union {
      Engines()
      rotate y*0
    }

    union {
      Engines()
      rotate y*120
    }
    union {
      Engines()
      rotate y*240
    }
    #end
    rotate y*30
    Shear_Trans(M3,-M1,M2)
  }
#end

union {
  #include "phx_topo.inc"
  translate -R
}

camera {
  right x*16/9
  location Loc+Look+Ofs
  look_at Look+Ofs
  sky Sky
  angle CamAngle
}

light_source {
  Sun
  <1,1,1>
}
/*
sphere {
  <0,0,0> 1
  translate RAverageA
  translate -R
  pigment {color rgb <1,0,0>}
}
*/
#if(T<250 | T>458.5)
union {
  cone {
    z*100,0,z*2000,200
  }
  cone {
    -z*100,0,-z*2000,200
  }
  cone {
    y*100,0,y*2000,200
  }
  cone {
    -y*100,0,-y*2000,200
  }
  translate x*FinalLLR.z
  rotate -y*degrees(FinalLLR.x)
  rotate z*degrees(FinalLLR.y)
  translate -R
  pigment {color rgb <1,0,0>}
}
#end
