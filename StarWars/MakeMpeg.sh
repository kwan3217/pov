#!/bin/sh
#usage
#  ./MakeMpeg.sh framefile sound name
mencoder -audiofile $2 -oac lavc -ovc lavc -of mpeg -mpegopts format=dvd:tsaf \
  -vf scale=720:480 -noskip -srate 48000 -mf fps=30000/1001 -af lavcresample=48000 \
  -lavcopts vpass=1:vcodec=mpeg2video:vhq:vrc_buf_size=1835:vrc_maxrate=5000:vbitrate=3000:keyint=18:vstrict=0:acodec=ac3:abitrate=128:aspect=4/3 -ofps 30000/1001 \
  -o /dev/null "mf://$1/*.png" &&
mencoder -audiofile $2 -oac lavc -ovc lavc -of mpeg -mpegopts format=dvd:tsaf \
  -vf scale=720:480 -noskip -srate 48000 -mf fps=30000/1001 -af lavcresample=48000 \
  -lavcopts vpass=2:vcodec=mpeg2video:vhq:vrc_buf_size=1835:vrc_maxrate=5000:vbitrate=3000:keyint=18:vstrict=0:acodec=ac3:abitrate=128:aspect=4/3 -ofps 30000/1001 \
  -o $3.mpg "mf://$1/*.png" &&
remux.sh "$3" &&
rm -v divx2pass.log &&
echo "Done!"



