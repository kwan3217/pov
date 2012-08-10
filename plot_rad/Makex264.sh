#!/bin/sh
#usage
#  ./MakeMpeg.sh framefile fps sound name

opts='bitrate=2000:subq=6:partitions=all:8x8dct:me=umh:frameref=5:bframes=3:b_pyramid:weight_b:threads=auto'

mencoder -ovc x264 -of rawvideo -noskip -mf fps=$2 -ofps $2 -x264encopts pass=1:$opts \
  -o "$4.int.264" "mf://$1/*.png" &&
mencoder -ovc x264 -of rawvideo -noskip -mf fps=$2 -ofps $2 -x264encopts pass=2:$opts \
  -o "$4.264" "mf://$1/*.png" &&
rm -fv divx2pass.log "$4.int.264" "$4.mp4" &&
MP4Box -fps $2 -add "$4.264" -add "$3" "$4.mp4" &&
rm -fv "$4.264" &&
mkvmerge -o "$4.mkv" "$4.mp4" &&
echo "Done!"



