#version unofficial Megapov 1.22;

#include "host.inc"
#debug concat("\u001b];Phoenix.pov - ",Host," Render - frame ",str(frame_number,0,0)," of ",str(final_frame,0,0),"\a")

global_settings {
  right_handed
}

#include "KwanMath.inc"
#include "PhxLoadVec.inc"

#declare I=0;
#declare Aeroid=1500;
#fopen ouf "PhxAtmTable2.csv" write
#write(ouf,"I,T,Alt m,Temp K,Dens kg/m^3,Pres Pa,Vs m/s,DynPres Pa,DynHeat W/m^2,Mach,Vrel m/s,MolWt kg/kmol\n")
#while(I<dimension_size(phx_IAU_MARS_blend,1))
  #declare R  =<phx_IAU_MARS_blend[I     ][ 1],phx_IAU_MARS_blend[I     ][ 2],phx_IAU_MARS_blend[I     ][ 3]>;
  #declare V  =<phx_IAU_MARS[I     ][ 5],phx_IAU_MARS[I     ][ 6],phx_IAU_MARS[I     ][ 7]>;
  #declare CurrentLLA=xyz2lla(<R.x,R.z,R.y>/AMars,FMars);
  #declare EllCurrent=CurrentLLA.z*AMars;
  #declare MOLACurrent=EllCurrent-Aeroid;
  #declare T=I/30;
  #declare TT=Temp(MOLACurrent);
  #declare Dens=Density(MOLACurrent);
  #declare Pres=Pressure(MOLACurrent);
  #declare Vs=Vsound(MOLACurrent);
  #declare DynPres=pow(vlength(V),2)*Dens/2;
  #declare DynHeat=pow(vlength(V),3)*sqrt(Dens)/2;
  #declare Mach=vlength(V)/Vs;
  #write(ouf,I,",",T,",",MOLACurrent,",",TT,",",Dens,",",Pres,",",Vs,",",DynPres,",",DynHeat,",",Mach,",",vlength(V),",",MolWeight(MOLACurrent),"\n")
  #declare I=I+1;
#end  
#fclose ouf
