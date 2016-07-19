cdjtruck.mpg: lores0.stamp lores1.stamp lores2.stamp lores3.stamp
	ffmpeg -i Frames/Frames%04d.png -y cdjtruck.mpg

cdjtruck.mp4: hires0.stamp hires1.stamp hires2.stamp hires3.stamp
	ffmpeg -i Frames/FramesHiRes%03d.png -y cdjtruck.mp4

lores0.stamp: Frames truk0.ini truk0.pov truck.inc
	uberpov truk0.ini
	touch lores0.stamp
	
lores1.stamp: Frames truk1.ini truk1.pov truck.inc
	uberpov truk1.ini
	touch lores1.stamp
	
lores2.stamp: Frames truk2.ini truk2.pov truck.inc
	uberpov truk2.ini
	touch lores2.stamp
	
lores3.stamp: Frames truk3.ini truk3.pov truck.inc
	uberpov truk3.ini
	touch lores3.stamp
	
Frames:
	mkdir Frames

hires0.stamp: Frames truk0.ini truk0.pov truck.inc hires.ini
	uberpov truk0.ini hires.ini
	touch hires0.stamp
	
hires1.stamp: Frames truk1.ini truk1.pov truck.inc hires.ini
	uberpov truk1.ini hires.ini
	touch hires1.stamp
	
hires2.stamp: Frames truk2.ini truk2.pov truck.inc hires.ini
	uberpov truk2.ini hires.ini
	touch hires2.stamp
	
hires3.stamp: Frames truk3.ini truk3.pov truck.inc hires.ini
	uberpov truk3.ini hires.ini
	touch hires3.stamp
	
clean:
	$(RM) -rf Frames
	$(RM) cdjtruck.mpg
	$(RM) cdjtruck.mp4
	$(RM) lores[0-9].stamp
	$(RM) hires[0-9].stamp

