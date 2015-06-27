#!/bin/bash -x
#ffmpeg -i $1.wav -ab 224 -ar 48000 $1.ac3
aspect=16/9
ifps=23.976
ofps=24000/1001
telecine=:telecine
lavcopts=vcodec=mpeg2video:vhq:vrc_buf_size=1835:vrc_maxrate=5000:vbitrate=3000:keyint=18:vstrict=0:acodec=ac3:abitrate=128:aspect=$aspect


mencoder -mf type=png:fps=$ifps -audiofile $1.wav -oac lavc -ovc lavc -of mpeg -mpegopts format=dvd:tsaf$telecine \
  -vf scale=720:480 -srate 48000 -af lavcresample=48000 \
  -lavcopts vpass=1:$lavcopts  -ofps $ofps \
  -o /dev/null "mf://Frames/$1*.png" &&
mencoder -mf type=png:fps=$ifps -audiofile $1.wav -oac lavc -ovc lavc -of mpeg -mpegopts format=dvd:tsaf$telecine \
  -vf scale=720:480 -srate 48000 -af lavcresample=48000 \
  -lavcopts vpass=2:$lavcopts  -ofps 24000/1001 \
  -o $1.mpg "mf://Frames/$1*.png" &&
#mplayer $1.mpg.int -dumpvideo -dumpfile $1.m2v &&
#mplayer $1.mpg.int -dumpaudio -dumpfile $1.ac3 &&
#rm -v $1.mpg.int &&
#mplex -f 8 -o $1.mpg $1.mpg.int $1.ac3 &&
rm -v  divx2pass.log &&
echo "Done!"



