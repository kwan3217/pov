#!/bin/sh
#usage
#  ./MakeMpeg.sh framefile fps sound name
mencoder -audiofile $3 -oac lavc -ovc lavc -of mpeg -mpegopts format=dvd:tsaf \
  -noskip -srate 48000 -mf fps=$2 -af lavcresample=48000 \
  -lavcopts vpass=1:vcodec=mpeg2video:vhq:vrc_buf_size=1835:vrc_maxrate=5000:vbitrate=1000:keyint=18:vstrict=0:acodec=ac3:abitrate=112:aspect=16/9 -ofps $2 \
  -o $4.mpg "mf://$1/*.png" &&
mencoder -audiofile $3 -oac lavc -ovc lavc -of mpeg -mpegopts format=dvd:tsaf \
  -noskip -srate 48000 -mf fps=$2 -af lavcresample=48000 \
  -lavcopts vpass=2:vcodec=mpeg2video:vhq:vrc_buf_size=1835:vrc_maxrate=5000:vbitrate=1000:keyint=18:vstrict=0:acodec=ac3:abitrate=112:aspect=16/9 -ofps $2 \
  -o $4.mpg "mf://$1/*.png" &&
remux.sh "$4" &&
rm -v divx2pass.log &&
echo "Done!"



