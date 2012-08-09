default: Kalman.mp4

FPS = 24
DIGITS=4
FRAMEDIR := Frames

Makefile.frames: Kalman.pov makeDep.pl
	./makeDep.pl $< > $@

sinclude Makefile.frames 

$(FRAMES_002_000): Actors.inc

FRAMES := $(addprefix $(FRAMEDIR)/Frame,$(FNUM))
FRAMES := $(addsuffix .png, $(FRAMES))


$(FRAMES): 
	megapov Kalman.ini +sf$(patsubst $(FRAMEDIR)/Frame%.png,%,$@) +ef$(patsubst $(FRAMEDIR)/Frame%.png,%,$@) > /dev/null 2>&1

$(FRAMES): | $(FRAMEDIR)
     
$(FRAMEDIR):
	mkdir $(FRAMEDIR)

FFMPEGFLAGS=-threads 9 -f image2 -r $(FPS) -i $(FRAMEDIR)/Frame%0$(DIGITS)d.png -vcodec libx264 -vpre medium -b 1000k -f mp4

Kalman.mp4: $(FRAMES) Kalman.mp3
	ffmpeg $(FFMPEGFLAGS)                      -pass 1 -y /dev/null
	ffmpeg  -i Kalman.mp3 $(FFMPEGFLAGS) -pass 2 -y $@
	mplayer -fs $@

clean:
	rm -rfv $(FRAMEDIR)
	$(RM) Kalman.mp4
	$(RM) Makefile.frames
