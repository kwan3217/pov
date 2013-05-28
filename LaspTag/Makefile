frames := $(shell seq -f "%03.0f" 0 119)

default: LaspTag1.mp4

BLURDIR := Blur
BLURS := $(addprefix $(BLURDIR)/lasp,$(frames))
BLURS := $(addsuffix .png, $(BLURS))
     
$(BLURS): $(BLURDIR)/%.png : Frames/%.png
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
FRAMES := $(addprefix $(FRAMEDIR)/lasp,$(frames))
FRAMES := $(addsuffix .png, $(FRAMES))
     
$(FRAMES): $(FRAMEDIR)/%.png : StarsCache.inc lasp.pov lasp.ini NewLASPLogoFull.inc snoe.inc
	megapov lasp.ini +sf$(patsubst $(FRAMEDIR)/lasp%.png,%,$@) +ef$(patsubst $(FRAMEDIR)/lasp%.png,%,$@)
     
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
