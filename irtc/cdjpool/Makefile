cdjpool.mpg: Frames lores0.stamp lores1.stamp lores2.stamp lores3.stamp lores4.stamp lores5.stamp lores6.stamp lores7.stamp lores8.stamp lores9.stamp
	ffmpeg -i Frames/scen%03d.png -y $@

cdjpool.mp4: Frames hires0.stamp hires1.stamp hires2.stamp hires3.stamp hires4.stamp hires5.stamp hires6.stamp hires7.stamp hires8.stamp hires9.stamp
	ffmpeg -i Frames/scenHiRes%03d.png -y $@

lores0.stamp: all.ini scen0.pov 
	uberpov all.ini +ki0 +kf8 +iscen0.pov +oFrames/scen0.png
	touch $@
	
lores1.stamp: all.ini scen1.pov
	uberpov all.ini +ki0 +kf1 +iscen1.pov +oFrames/scen1.png
	touch $@
	
lores9.stamp: all.ini scen9.pov
	uberpov all.ini +ki0 +kf21 +iscen9.pov +oFrames/scen9.png
	touch $@

lores%.stamp: scen%.pov all.ini
	uberpov all.ini +ki-1 +kf8 +i$< +oFrames/scen$*.png
	touch $@
	
hires0.stamp: all.ini hires.ini scen0.pov
	uberpov all.ini hires.ini +ki0 +kf8 +iscen0.pov +oFrames/scenHiRes0.png
	touch $@
	
hires1.stamp: all.ini hires.ini scen1.pov
	uberpov all.ini hires.ini +ki0 +kf1 +iscen1.pov +oFrames/scenHiRes1.png
	touch $@
	
hires9.stamp: all.ini hires.ini scen9.pov
	uberpov all.ini hires.ini +ki0 +kf21 +iscen9.pov +oFrames/scenHiRes9.png
	touch $@

hires%.stamp: scen%.pov hires.ini all.ini
	uberpov all.ini hires.ini +ki-1 +kf8 +i$< +oFrames/scenHiRes$*.png
	touch $@
	
Frames:
	mkdir Frames

clean:
	$(RM) cdjpool.mpg
	$(RM) cdjpool.mp4
	$(RM) -rf Frames


