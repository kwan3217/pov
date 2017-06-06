stkwantruck.mpg: lores1.stamp
	ffmpeg -i Frames/Frames%04d.png -y stkwantruck.mpg

stkwantruck.mp4: hires1.stamp
	ffmpeg -framerate 30000/1001 -i Frames/FramesHiRes%03d.png -y stkwantruck.mp4

lores1.stamp: Frames truk1.ini truk1.pov truck.inc
	uberpov truk1.ini
	touch lores1.stamp

Frames:
	mkdir Frames

hires1.stamp: Frames truk1.ini truk1.pov truck.inc hires.ini
	uberpov truk1.ini hires.ini
	touch hires1.stamp

clean:
	$(RM) -rf Frames
	$(RM) stkwantruck.mpg
	$(RM) stkwantruck.mp4
	$(RM) lores[0-9].stamp
	$(RM) hires[0-9].stamp

