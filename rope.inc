#declare MaxSeg=5;

#macro Rope(Pt1,Pt2,NSeg,Swing)
  #if(NSeg>0)
  #local SwingRad=vlength(Pt2-Pt1)/20;
	#local SwingPhase=NSeg;
	#local SwingFreq=(MaxSeg-NSeg)*1.2;
	#local PtM=(Pt2+Pt1)/2;
	#local SwingArg=SwingPhase+2*pi*SwingFreq*Swing;
	#local SwingV=SwingRad*<cos(SwingArg),0,sin(SwingArg)>;
	#local PtM=PtM+SwingV;
	cylinder {
	  -y*0.25,+y*0.25,4
		texture {DMFWood4 scale 2 rotate x*2 finish {ambient 0.5}}
		translate PtM
	}
	Rope(Pt1,PtM,NSeg-1,Swing)
	Rope(PtM,Pt2,NSeg-1,Swing)
	#else
	  cylinder {
		  Pt1,Pt2,0.1
			pigment {color rgb <1,1,0.25>}
			finish {ambient 0.5}
		}
	#end
#end

