exi_chase.mp4: Frames/exi_chase_[0-9][0-9][0-9][0-9].png
	ffmpeg -r 24 -i Frames/exi_chase_%04d.png -y exi_chase.mp4

exi_view.mp4: Frames/exi_view_[0-9][0-9][0-9][0-9].png
	ffmpeg -r 24 -i Frames/exi_view_%04d.png -y exi_view.mp4

exi_view.png: exi_view.pov exi_common.inc exi_view.ini exi_common.ini
	kwanpov `if [ -z ${STY} ]; then echo +d; else echo -d; fi` exi_common.ini exi_view.ini +w4096 +h3072 +kfi-1 +kff-1 +fn12 +o./exi_view.png
	mv exi_view0.png exi_view.png

exi_chase.png: exi_chase.pov exi_common.inc exi_view.ini exi_common.ini
	kwanpov `if [ -z ${STY} ]; then echo +d; else echo -d; fi` exi_common.ini exi_chase.ini +w1024 +h768 +kfi-1 +kff-1 +fn12 +o./exi_chase.png
	mv exi_chase0.png exi_chase.png

exi_red.png: exi_view.png
	convert exi_view.png -depth 12 -channel R -separate exi_red.png

