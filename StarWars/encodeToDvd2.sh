#!/bin/sh
#usage: encodeToDvd2.sh name sound
mencoder -audiofile $2 -oac lavc -ovc lavc -of mpeg -mpegopts format=dvd:tsaf:telecine \
  -vf scale=720:480 -srate 48000 -af lavcresample=48000 \
  -lavcopts vpass=1:vcodec=mpeg2video:vhq:vrc_buf_size=1835:vrc_maxrate=5000:vbitrate=3000:keyint=18:vstrict=0:acodec=ac3:abitrate=128:aspect=4/3 \
  -ofps 24000/1001 -o /dev/null "mf://Frames/*.png" -mf fps=23.976 &&
mencoder -audiofile $2 -oac lavc -ovc lavc -of mpeg -mpegopts format=dvd:tsaf:telecine \
  -vf scale=720:480 -srate 48000 -af lavcresample=48000 \
  -lavcopts vpass=2:vcodec=mpeg2video:vhq:vrc_buf_size=1835:vrc_maxrate=5000:vbitrate=3000:keyint=18:vstrict=0:acodec=ac3:abitrate=128:aspect=4/3 \
  -ofps 24000/1001 -o $1.mpg.int "mf://Frames/*.png" -mf fps=23.976 &&
mplayer $1.mpg.int -dumpvideo -dumpfile $1.m2v &&
mplayer $1.mpg.int -dumpaudio -dumpfile $1.ac3 &&
#rm -v $1.mpg.int &&
mplex -f 8 -o $1.mpg $1.m2v $1.ac3 &&
#rm -v $1.m2v $1.ac3 divx2pass.log &&
echo "Done!"

