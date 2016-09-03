stkwanstation.mpg: Frames lores1.stamp
	ffmpeg -i Frames/scen%03d.png -y $@

stkwanstation.mp4: Frames hires1.stamp
	ffmpeg -r 15 -i Frames/scenHiRes%03d.png -y $@

lores1.stamp: all.ini scen1.pov
	kwanpov all.ini           +ki0 +kf0.08 +kfi1 +kff156 +iscen1.pov +oFrames/scen.png
	touch $@

hires1.stamp: all.ini hires.ini scen1.pov
	kwanpov all.ini hires.ini +ki0 +kf0.08 +kfi1 +kff156 +iscen1.pov +oFrames/scenHiRes.png
	touch $@

Frames:
	mkdir Frames

clean:
	$(RM) stkwanstation.mpg
	$(RM) stkwanstation.mp4
	$(RM) -rf Frames
	$(RM) *res[0-9].stamp

