frames := $(shell seq -f "%03.0f" 0 333)

default: hd.mp4

COMPDIR := Blur
COMPS := $(addprefix $(BLURDIR)/compose,$(frames))
COMPS := $(addsuffix .png, $(BLURS))
     
$(COMPS): $(COMPDIR)/%.png : Frames/%.png
	for i in {000..333}; do composite -dissolve 50x100 -geometry 640x480 Frames/VoyagerUranusSpice_$i.png -geometry 640x480  Originals/V2U/frame00$((10#$i+200)).png compose/compose$i.png; echo $i; done
	convert $< -blur 100x30 png24:$@
     
$(BLURS): | $(BLURDIR)
     
$(BLURDIR):
	mkdir $(BLURDIR)

SOFTDIR := Soft
SOFTS := $(addprefix $(SOFTDIR)/lasp,$(frames))
SOFTS := $(addsuffix .png, $(SOFTS))
     
$(SOFTS): $(SOFTDIR)/%.png : Frames/%.png $(BLURDIR)/%.png 
	composite -blend 100x100 $^ png24:$@
     
$(SOFTS): | $(SOFTDIR)
     
$(SOFTDIR):
	mkdir $(SOFTDIR)

FRAMEDIR := Frames
FRAMES := $(addprefix $(FRAMEDIR)/VoyagerUranusSpice,$(frames))
FRAMES := $(addsuffix .png, $(FRAMES))
     
$(FRAMES): $(FRAMEDIR)/%.png : StarsCache.inc lasp.pov lasp.ini NewLASPLogoFull.inc snoe.inc
	megapov VoyagerSpice.ini +sf$(patsubst $(FRAMEDIR)/VoyagerUranusSpice_%.png,%,$@) +ef$(patsubst $(FRAMEDIR)/lasp%.png,%,$@)
     
$(FRAMES): | $(FRAMEDIR)
     
$(FRAMEDIR):
	mkdir $(FRAMEDIR)

LaspTag1.mp4: $(SOFTS) f2_44100.ogg
	ffmpeg -r 24 -f image2 -i Soft/lasp%03d.png -i f2_44100.ogg -vb 4000k -ab 128k -strict experimental -pass 1 -y LaspTag1.mp4
	ffmpeg -r 24 -f image2 -i Soft/lasp%03d.png -i f2_44100.ogg -vb 4000k -ab 128k -strict experimental -pass 2 -y LaspTag1.mp4
	$(RM) ffmpeg2pass-0.log

clean:
	$(RM) -rfv $(SOFTDIR) $(BLURDIR) $(FRAMEDIR)
	$(RM) LaspTag1.mp4
	$(RM) StarsCache.inc
	$(RM) Memory.Log

StarsCache.inc:
	echo '#include "Stars.inc"' > /tmp/stars.pov
	megapov +L../PovSolar +L.. +i/tmp/stars.pov -o -f +kfi-1 +kff-1 -d
	$(RM) /tmp/stars.pov

compose.mp4:
	for i in {000..333}; do composite -dissolve 50x100 -geometry 640x480 Frames/VoyagerUranusSpice_$i.png -geometry 640x480  Originals/V2U/frame00$((10#$i+200)).png compose/compose$i.png; echo $i; done
	ffmpeg -f image2 -i compose/compose%03d.png -vb 1000k -y compose.mp4

sd.mp4:
	for i in {000..333}; do convert Frames/VoyagerUranusSpice_$i.png -resize 640x480 sd/sd$i.png; echo $i; done
	ffmpeg -f image2 -i sd/sd%03d.png -vb 1000k -y sd.mp4

hd.mp4:
	for i in {000..333}; do convert Frames/VoyagerUranusSpice_$i.png -resize 1440x1080 hd/hd$i.png; echo $i; done
	ffmpeg -f image2 -i hd/hd%03d.png -vb 2500k -y hd.mp4

